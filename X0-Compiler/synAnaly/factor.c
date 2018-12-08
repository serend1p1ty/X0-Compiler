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
	else if (sym == ident && FindPosition_V1 (id, tableNum) == -1)
	{
		FunctionCall ();
	}
	else if ((sym == ident && FindPosition_V1 (id, tableNum) != -1)
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
				GenerateINTCode (add, offset, 1, tableNum);
				GenerateINTCode (lod, offset, tableNum, 0);
				GenerateINTCode (tad, -1, 0, 0);
				break;
			case 2:
				GenerateINTCode (add, offset, -1, tableNum);
				GenerateINTCode (lod, offset, tableNum, 0);
				GenerateINTCode (tad, 1, 0, 0);
				break;
			case 3:
				GenerateINTCode (add, offset, 1, tableNum);
				GenerateINTCode (lod, offset, tableNum, 0);
				break;
			case 4:
				GenerateINTCode (add, offset, -1, tableNum);
				GenerateINTCode (lod, offset, tableNum, 0);
				break;
			case 5:
				GenerateINTCode (lod, offset, tableNum, 0);
				break;
		}
	}
	else if (sym == intnum)
	{
		GenerateINTCode (lit, 1, intNum, 0);
		ReadSymbol ();
	}
	else if (sym == doublenum)
	{
		GenerateINTCode (lit, 2, 0, doubleNum);
		ReadSymbol ();
	}
	else if (sym == truesym || sym == falsesym)
	{
		GenerateINTCode (lit, 1, sym == truesym, 0); /* the value of 'true' is 1, value of 'false' is 0 */
		ReadSymbol ();
	}
	else /* sym isn't belong to first(factor) */
	{
		ErrorHandler (15);
	}

	/* logic inversion operator has appeared */
	if (flag)
	{
		GenerateINTCode (opr, 18, 0, 0);
	}
}