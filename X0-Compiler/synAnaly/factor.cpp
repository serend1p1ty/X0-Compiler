#include "../global.h"

/*
 * factor syntactical analyzer
 */
void factor ()
{
	int flag = 0; /* flag = 1 means logical inversion operator has appeared */

	if (sym == notsym)
	{
		flag = 1;
		ReadSymbol ();
	}

	if (sym == lparen)
	{
		ReadSymbol ();
		expression ();
		if (sym == rparen)
		{
			ReadSymbol ();
		}
		else /* the lack of ')' */
		{
			ErrorHandler (14);
		}
	}
	/* current statement is FunctionCall if the identifier has been declared in symbol table */
	else if (sym == ident && FindPosition (id, fctNum - 1) == -1)
	{
		FunctionCall ();
	}
	else if ((sym == ident && FindPosition (id, fctNum - 1) != -1)
		     || sym == incsym || sym == decsym)
	{
		ObjectKind kind;
		int offset;
		int IncOrDec;	/* 1: Increase after variable   2: decrease after variable
					     * 3: Increase before variable  4: decrease before variable
					     * 5: without Increase or decrease */
		variable (&kind, &offset, &IncOrDec);

		switch (IncOrDec)
		{
			case 1:
				GenINTCode (add, offset, fctNum - 1);
				GenINTCode (lod, offset, fctNum - 1);
				GenINTCode (tad, -1, 0);
				break;
			case 2:
				GenINTCode (sub, offset, fctNum - 1);
				GenINTCode (lod, offset, fctNum - 1);
				GenINTCode (tad, 1, 0);
				break;
			case 3:
				GenINTCode (add, offset, fctNum - 1);
				GenINTCode (lod, offset, fctNum - 1);
				break;
			case 4:
				GenINTCode (sub, offset, fctNum - 1);
				GenINTCode (lod, offset, fctNum - 1);
				break;
			case 5:
				GenINTCode (lod, offset, fctNum - 1);
				break;
		}
	}
	else if (sym == intnum)
	{
		GenINTCode (lit, intNum, 0);
		ReadSymbol ();
	}
	else if (sym == doublenum)
	{
		GenINTCode (lit, 0, doubleNum);
		ReadSymbol ();
	}
	else if (sym == truesym || sym == falsesym)
	{
		GenINTCode (lit, sym == truesym, 0); /* the value of 'true' is 1, value of 'false' is 0 */
		ReadSymbol ();
	}
	else /* syntax error of 'factor' */
	{
		ErrorHandler (15);
	}

	/* logic inversion operator has appeared */
	if (flag)
	{
		GenINTCode (opr, 18, 0); /* logic inversion */
	}
}