#include "../global.h"

/*
 * while语句语法分析程序
 */
void while_stat ()
{
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
}