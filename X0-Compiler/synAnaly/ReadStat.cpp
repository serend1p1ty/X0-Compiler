#include "../global.h"

/*
 * ReadStat syntactical analyzer
 */
void ReadStat ()
{
	if (sym == readsym)
	{
		ReadSymbol ();
		
		ObjectKind kind;
		int offset;
		int IncOrDec;	/* 1: Increase after variable   2: decrease after variable
					     * 3: Increase before variable  4: decrease before variable
					     * 5: without Increase or decrease */
		variable (&kind, &offset, &IncOrDec);

		/* 'read' function can't read Increasing or decreasing variable */
		if (IncOrDec != 5)
		{
			ErrorHandler (32);
		}

		/* constant can't be read */
		if (kind == constIntVar || kind == constCharVar
			|| kind == constBoolVar || kind == constDoubleVar)
		{
			ErrorHandler (52);
		}

		/* read a variable using scanf function */
		switch (kind)
		{
			case intVar:
			case intArray:
				GenINTCode (opr, 14, Int);
				break;
			case doubleVar:
			case doubleArray:
				GenINTCode (opr, 14, Double);
				break;
			case charVar:
			case charArray:
				GenINTCode (opr, 14, Char);
				break;
			case boolVar:
			case boolArray:
				GenINTCode (opr, 14, Bool);
				break;
		}

		GenINTCode (sto, offset, fctNum - 1); /* store the value of top element in the specific variable */
		
		if (sym == semic)
		{
			ReadSymbol ();
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
	else /* the lack of 'read' */
	{
		ErrorHandler (18);
	}
}