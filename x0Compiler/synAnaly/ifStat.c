#include "../global.h"

/*
 * if语句语法分析程序
 */
void ifStat ()
{
	if (sym == ifsym)
	{
		getSym ();
		if (sym == lparen)
		{
			getSym ();
			expression ();

			int pos1 = iterCode; /* 保存现在的iterCode值，回填的时候使用 */
			gen (jpc, 0, 0);  /* 跳转的位置还不确定，待会回填 */

			if (sym == rparen)
			{
				getSym ();
				statement ();

				if (sym == elsesym)
				{
					int pos2 = iterCode; /* 保存现在的iterCode值，回填的时候使用 */
					gen (jmp, 0, 0);  /* 跳转的位置还不确定，待会回填 */
					
					code[pos1].offset = iterCode; /* 回填 */

					getSym ();
					statement ();

					code[pos2].offset = iterCode; /* 回填 */
				}
				else
				{
					code[pos1].offset = iterCode; /* 回填 */
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
	else /* 缺少if */
	{
		error (17);
	}
}