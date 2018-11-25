#include "../global.h"

/*
 * additive_expr语法分析程序
 */
void additive_expr ()
{
	if (sym == minus) /* 这里减号看作负号 */
	{
		getSym ();
		term ();
		gen (opr, 0, 1);
	}
	else
	{
		term ();
	}

	while (sym == plus || sym == minus || sym == modsym)
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
			case modsym:
				gen (opr, 0, 6);
				break;
			default: /* 不合法的运算符 */
				error (30);
		}
	}
}