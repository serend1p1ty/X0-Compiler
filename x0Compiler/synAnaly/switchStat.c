#include "../global.h"

/*
 * switchStat语法分析程序
 */
void switchStat ()
{
	int startBreakNum = iterBreakList; /* 记录switch语句分析开始时需要回填的break语句数量 */
	
	if (sym == swtcsym)
	{
		getSym ();

		if (sym == lparen)
		{
			getSym ();
			expression ();

			if (sym == rparen)
			{
				getSym ();

				if (sym == lbrace)
				{
					getSym ();
					int pos1 = -1; /* 上一个case语句待回填的jpc位置 */
					int pos2 = -1; /* 上一个case语句待回填的jmp位置 */

					while (sym == cassym)
					{
						if (pos1 != -1)
						{
							code[pos1].offset = iterCode; /* 回填 */
						}
						
						getSym ();

						if (sym == number)
						{
							gen (lit, 0, num);
							gen (opr, 0, 21);
							gen (jpc, 0, 0);
							pos1 = iterCode - 1;
							getSym ();

							if (sym == colonsym)
							{
								getSym ();

								if (pos2 != -1)
								{
									code[pos2].offset = iterCode; /* 回填 */
								}

								statementList ();
								gen (jmp, 0, 0);
								pos2 = iterCode - 1;
							}
							else /* 缺少: */
							{
								error (38);
							}
						}
						else /* 缺少数字 */
						{
							error (8);
						}
					}

					if (pos1 != -1)
					{
						code[pos1].offset = iterCode; /* 回填 */
					}

					if (pos2 != -1)
					{
						code[pos2].offset = iterCode; /* 回填 */
					}

					if (sym == defausym)
					{
						getSym ();

						if (sym == colonsym)
						{
							getSym ();
							statementList ();
						}
						else /* 缺少: */
						{
							error (38);
						}
					}

					if (sym == rbrace)
					{
						getSym ();
					}
					else /* 缺少} */
					{
						error (4);
					}
				}
				else /* 缺少{ */
				{
					error (5);
				}
			}
			else /* 缺少) */
			{
				error (14);
			}
		}
		else /* 缺少( */
		{
			error (16);
		}
	}
	else /* 缺少switch */
	{
		error (37);
	}

	/* 回填break语句 */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].offset = iterCode;
	}

	iterBreakList = startBreakNum; /* 将iterBreakList设置为刚开始的值 */
}