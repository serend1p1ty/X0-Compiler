#include "../global.h"

/*
 * expression syntactical analyzer
 */
void expression ()
{
	if (sym == ident) /* need to read more symbols to determine whether current statement is assignment statement */
	{
		backup (); /* backup the status of lexical analysing */
		int offset;
		enum objectKind kind;
		simple_variable (&kind, &offset);
		if (sym == eql) /* current statement is assignment statement */
		{
			/* constant can't be modified */
			if (kind == constIntVar || kind == constCharVar
				|| kind == constBoolVar || kind == constDoubleVar)
			{
				error (32);
			}
			
			readSymbol ();
			expression ();
			gen (sto, offset, tableNum, 0); /* store the top element in the specfic variable */
		}
		else /* current statement is value_expr */
		{
			recover (); /* recover the status of lexical analysing from backups */
			value_expr ();
		}
	}
	else if (sym == lparen || sym == intnum || sym == ident || sym == minus
			|| sym == incsym || sym == decsym || sym == oddsym || sym == notsym
			|| sym == truesym || sym == falsesym || sym == doublenum) /* sym belong to first(value_expr) */
	{
		value_expr ();
	}
	else /* sym isn't belong to first(expression) */
	{
		error (12);
	}
}