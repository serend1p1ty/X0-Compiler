#include "../global.h"

/*
 * exitStat语法分析程序
 */
void exitStat ()
{
	if (sym == exitsym)
	{
		getSym ();

		if (sym == lparen)
		{
			getSym ();

			if (sym == number)
			{
				getSym ();

				if (sym == rparen)
				{
					getSym ();

					if (sym == semic)
					{
						getSym ();
						gen (opr, 0, 7);
					}
					else /* 缺少; */
					{
						error (10);
					}
				}
				else /* 缺少) */
				{
					error (14);
				}
			}
			else /* 缺少数字 */
			{
				error (8);
			}
		}
		else /* 缺少( */
		{
			error (16);
		}
	}
	else /* 缺少exit */
	{
		error (35);
	}
}