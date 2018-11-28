#include "../global.h"

/*
 * simpleValue语法分析程序
 */
void simpleValue ()
{
	if (sym == oddsym)
	{
		getSym ();
		additiveExpr ();
		gen (opr, 0, 20);
	}
	else
	{
		additiveExpr ();
		if (sym == great || sym == less || sym == greateql
			|| sym == lesseql || sym == eqleql || sym == neql)
		{
			enum symbol tempSym = sym; /* 保存此时的sym */
			getSym ();
			additiveExpr ();

			/* >, <, >=, <=, ==, != */
			switch (tempSym)
			{
				case great:
					gen (opr, 0, 12);
					break;
				case less:
					gen (opr, 0, 10);
					break;
				case greateql:
					gen (opr, 0, 11);
					break;
				case lesseql:
					gen (opr, 0, 13);
					break;
				case eqleql:
					gen (opr, 0, 8);
					break;
				case neql:
					gen (opr, 0, 9);
					break;
				default: /* 不合法的运算符 */
					error (30);
			}
		}
	}
}