#include "../global.h"

/*
 * expression syntactical analyzer
 */
void expression ()
{
	if (sym == ident) /* need to read more symbols to determine whether current statement is assignment statement */
	{
		backup (); /* backup the status of lexical analysis */
		int offset;
		ObjectKind kind;
		SimpleVariable (&kind, &offset);
		if (sym == eql) /* current statement is assignment statement */
		{
			/* constant can't be modified */
			if (kind == constIntVar || kind == constCharVar
				|| kind == constBoolVar || kind == constDoubleVar)
			{
				ErrorHandler (32);
			}
			
			ReadSymbol ();
			expression ();
			GenerateINTCode (sto, offset, tableNum, 0); /* store the top element in the specfic variable */
		}
		else /* current statement is ValueExpr */
		{
			recover (); /* recover the status of lexical analysis from backups */
			ValueExpr ();
		}
	}
	else if (sym == lparen || sym == intnum || sym == ident || sym == minus
			|| sym == incsym || sym == decsym || sym == oddsym || sym == notsym
			|| sym == truesym || sym == falsesym || sym == doublenum) /* sym belong to first(ValueExpr) */
	{
		ValueExpr ();
	}
	else /* sym isn't belong to first(expression) */
	{
		ErrorHandler (12);
	}
}