#include "../global.h"

/*
 * expression syntactical analyzer
 */
void expression ()
{
	if (sym == ident) /* need to read more symbols to determine whether current statement is assignment statement */
	{
		if (FindPosition (id, fctNum - 1) != -1)
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
					ErrorHandler (31);
				}

				ReadSymbol ();
				expression ();
				GenINTCode (sto, offset, fctNum - 1); /* store the top element in the specfic variable */
			}
			else /* current statement is ValueExpr */
			{
				recover (); /* recover the status of lexical analysis from backups */
				ValueExpr ();
			}
		}
		else /* we are sure current statement is ValueExpr if the identifier a function */
		{
			ValueExpr ();
		}
	}
	else
	{
		ValueExpr ();
	}
}