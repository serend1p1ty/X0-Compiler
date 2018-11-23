#include "../global.h"

/*
 * simple_expr语法分析程序
 */
void simple_expr ()
{
	additive_expr ();
	if (sym == great || sym == less || sym == greateql
		|| sym == lesseql || sym == eqleql || sym == neql)
	{
		enum symbol tempSym = sym; /* 保存此时的sym */
		getSym ();
		additive_expr ();

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
			default:
				printf ("不是正确的比较符号\n");
		}

	}
}