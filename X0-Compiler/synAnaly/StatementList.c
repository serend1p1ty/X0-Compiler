#include "../global.h"

/*
 * statement syntactical analyzer
 */
void statement ()
{
	if (sym == ifsym) /* 'if' statement */
	{
		IfStat ();
	}
	else if (sym == whilesym) /* 'while' statement */
	{
		WhileStat ();
	}
	else if (sym == readsym) /* 'read' statement */
	{
		ReadStat ();
	}
	else if (sym == writesym) /* 'write' statement */
	{
		WriteStat ();
	}
	else if (sym == lbrace)	/* 'compound' statement */
	{
		CompoundStat ();
	}
	else if (sym == semic || sym == ident || sym == doublenum
		|| sym == lparen || sym == intnum || sym == minus
		|| sym == incsym || sym == decsym || sym == oddsym
		|| sym == notsym || sym == truesym || sym == falsesym)	/* 'expression' statement */
	{
		ExpressionStat ();
	}
	else if (sym == forsym) /* 'for' statement */
	{
		ForStat ();
	}
	else if (sym == brksym) /* 'break' statement */
	{
		BreakStat ();
	}
	else if (sym == exitsym) /* 'exit' statement */
	{
		ExitStat ();
	}
	else if (sym == ctnsym) /* 'continue' statement */
	{
		ContinueStat ();
	}
	else if (sym == swtcsym) /* 'switch' statement */
	{
		SwitchStat ();
	}
	else if (sym == dosym) /* do-while statement */
	{
		DoWhileStat ();
	}
	else if (sym == retsym) /* 'return' statement */
	{
		ReturnStat ();
	}
	else if (sym == reptsym) /* repeat-until statement */
	{
		RepeatStat ();
	}
	else /* sym isn't belong to first(statement) */
	{
		ErrorHandler (19);
	}
}

/*
 * StatementList syntactical analyzer
 */
void StatementList ()
{
	/* execute 'statement' syntactical analyzer if sym belong to first('statement') */
	while (sym == ifsym || sym == whilesym || sym == readsym
		|| sym == writesym || sym == lbrace || sym == semic
		|| sym == ident || sym == lparen || sym == intnum
		|| sym == doublenum || sym == minus || sym == forsym
		|| sym == incsym || sym == decsym || sym == oddsym
		|| sym == notsym || sym == brksym || sym == exitsym
		|| sym == ctnsym || sym == swtcsym || sym == dosym 
		|| sym == reptsym || sym == truesym || sym == falsesym || sym == retsym)
	{
		statement ();
	}
}