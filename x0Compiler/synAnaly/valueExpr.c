#include "../global.h"

/*
 * valueExpr语法分析程序
 */
void valueExpr ()
{
	simpleValue ();

	while (sym == andsym || sym == orsym || sym == xorsym)
	{
		enum symbol tempSym = sym; /* 保存此时的sym */
		getSym ();
		simpleValue ();

		switch (tempSym)
		{
			case andsym:
				gen (opr, 0, 16);
				break;
			case orsym:
				gen (opr, 0, 17);
				break;
			case xorsym:
				gen (opr, 0, 19);
				break;
			default: /* 不合法的运算符 */
				error (30);
		}
	}
}