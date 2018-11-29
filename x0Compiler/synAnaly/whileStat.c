#include "../global.h"

/*
 * while语句语法分析程序
 */
void whileStat ()
{
	int startBreakNum = iterBreakList; /* 记录while语句分析开始时需要回填的break语句数量 */

	int startContinueNum = iterCtnList; /* 记录while语句分析开始时需要回填的continue语句数量 */

	if (sym == whilesym)
	{
		getSym ();

		if (sym == lparen)
		{
			int pos1 = iterCode; /* 保存现在的iterCode值 */

			getSym ();
			expression ();

			if (sym == rparen)
			{
				int pos2 = iterCode; /* 保存现在的iterCode值，回填的时候使用 */

				gen (jpc, 0, 0);  /* 跳转的位置还不确定，待会回填 */
				
				getSym ();
				statement ();

				/* 回填continue语句 */
				for (int i = startContinueNum; i < iterCtnList; i++)
				{
					int pos = continueList[i];
					code[pos].offset = iterCode;
				}

				iterCtnList = startContinueNum; /* 将iterCtnList设置为刚开始的值 */

				gen (jmp, 0, pos1);
				code[pos2].offset = iterCode;
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
	else /* 缺少while */
	{
		error (21);
	}

	/* 回填break语句 */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].offset = iterCode;
	}

	iterBreakList = startBreakNum; /* 将iterBreakList设置为刚开始的值 */
}