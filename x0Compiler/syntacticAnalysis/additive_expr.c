#include "../global.h"

/*
 * additive_exprÓï·¨·ÖÎö³ÌĞò
 */
void additive_expr ()
{
	term ();
	while (sym == plus || sym == minus)
	{
		getSym ();
		term ();
	}
}