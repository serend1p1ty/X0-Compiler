#include "../global.h"

/*
 * additive_expr语法分析程序
 */
void additive_expr ()
{
	term ();
	while (sym == plus || sym == minus)
	{
		enum symbol tempSym = sym; /* 保存此时的符号 */
		getSym ();
		term ();

		switch (tempSym)
		{
			case plus:
				gen (opr, 0, 2);
				break;
			case minus:
				gen (opr, 0, 3);
				break;
			default:
				printf ("符号应该为+或-\n");
		}
	}
}