#include "../global.h"

/*
 * repeatStat语法分析程序
 */
void repeatStat ()
{
	if (sym == reptsym)
	{
		getSym ();

		if (sym == lbrace)
		{
			getSym ();

			int pos = iterCode; /* 记录下statementList第一条代码的位置 */

			statementList ();

			if (sym == rbrace)
			{
				getSym ();

				if (sym == untlsym)
				{
					getSym ();

					if (sym == lparen)
					{
						getSym ();
						expression ();
						gen (jpc, 0, pos);

						if (sym == rparen)
						{
							getSym ();

							if (sym == semic)
							{
								getSym ();
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
	else /* 缺少do */
	{
		error (39);
	}
}