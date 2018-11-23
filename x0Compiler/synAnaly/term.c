#include "../global.h"

/*
 * term语法分析程序
 */
void term ()
{
	factor ();
	while (sym == times || sym == slash)
	{
		enum symbol tempSym = sym; /* 保存此时的符号 */
		getSym ();
		factor ();

		switch (tempSym)
		{
			case times:
				gen (opr, 0, 4);
				break;
			case slash:
				gen (opr, 0, 5);
				break;
			default:
				printf ("符号应该为*或/\n");
		}
	}
}