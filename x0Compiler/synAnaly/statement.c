#include "../global.h"

/*
 * statement syntactical analyzer
 */
void statement ()
{
	if (sym == ifsym) /* if statement */
	{
		ifStat ();
	}
	else if (sym == whilesym) /* while statement */
	{
		whileStat ();
	}
	else if (sym == readsym) /* read statement */
	{
		readStat ();
	}
	else if (sym == writesym) /* write statement */
	{
		writeStat ();
	}
	else if (sym == lbrace)	/* compound statement */
	{
		compoundStat ();
	}
	else if (sym == semic || sym == ident || sym == doublenum
		|| sym == lparen || sym == intnum || sym == minus
		|| sym == incsym || sym == decsym || sym == oddsym
		|| sym == notsym || sym == truesym || sym == falsesym)	/* expression statement */
	{
		expressionStat ();
	}
	else if (sym == forsym) /* for statement */
	{
		forStat ();
	}
	else if (sym == brksym) /* break statement */
	{
		breakStat ();
	}
	else if (sym == exitsym) /* exit statement */
	{
		exitStat ();
	}
	else if (sym == ctnsym) /* continue statement */
	{
		continueStat ();
	}
	else if (sym == swtcsym) /* switch statement */
	{
		switchStat ();
	}
	else if (sym == dosym) /* do-while statement */
	{
		dowhileStat ();
	}
	else if (sym == reptsym) /* repeat-until statement */
	{
		repeatStat ();
	}
	else /* sym isn't belong to first(statement) */
	{
		error (19);
	}
}