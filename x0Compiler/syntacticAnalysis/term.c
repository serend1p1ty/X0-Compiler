#include "../global.h"

/*
 * termÓï·¨·ÖÎö³ÌĞò
 */
void term ()
{
	factor ();
	while (sym == times || sym == slash)
	{
		getSym ();
		factor ();
	}
}