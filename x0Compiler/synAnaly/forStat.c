#include "../global.h"

/*
 * for语句语法分析程序
 */
void forStat ()
{
	if (sym == forsym)
	{
		getSym ();

		if (sym == lparen)
		{
			getSym ();
			expression ();
			int L0 = iterCode; /* 跳转标号 */

			if (sym == semic)
			{
				getSym ();
				expression ();

				int pos1 = iterCode; /* 保存现在的iterCode值，回填的时候使用 */
				gen (jpc, 0, 0);  /* 跳转的位置还不确定，待会回填 */
				gen (jmp, 0, 0);

				int L1 = iterCode; /* 跳转标号 */

				if (sym == semic)
				{
					getSym ();
					expression ();
					gen (jmp, 0, L0);

					int L2 = iterCode; /* 跳转标号 */

					if (sym == rparen)
					{
						getSym ();
						statement ();
						gen (jmp, 0, L1);
						
						/* 回填 */
						code[pos1].offset = iterCode;
						code[pos1 + 1].offset = L2;
					}
					else /* 缺少) */
					{
						error (14);
					}
				}
				else /* 缺少; */
				{
					error (10);
				}
			}
			else /* 缺少; */
			{
				error (10);
			}
		}
		else /* 缺少( */
		{
			error (16);
		}
	}
	else /* 缺少for */
	{
		error (31);
	}
}