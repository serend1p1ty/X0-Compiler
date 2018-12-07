#include "../global.h"

/*
 * ReadStat syntactical analyzer
 */
void ReadStat ()
{
	if (sym == readsym)
	{
		ReadSymbol ();
		
		enum objecKind kind;
		int offset;
		int IncOrDec;	/* 1: Increase after variable   2: decrease after variable
					     * 3: Increase before variable  4: decrease before variable
					     * 5: without Increase or decrease */
		variable (&kind, &offset, &IncOrDec);

		/* 'read' function can't read Increasing or decreasing variable */
		if (IncOrDec != 5)
		{
			ErrorHandler (33);
		}

		/* constant can't be read */
		if (kind == constIntVar || kind == constCharVar
			|| kind == constBoolVar || kind == constDoubleVar)
		{
			ErrorHandler (53);
		}

		/* read a variable using scanf function */
		switch (kind)
		{
			case intVar:
				GenerateINTCode (opr, 14, 1, 0);
				break;
			case intArray:
				GenerateINTCode (opr, 14, 1, 0);
				break;
			case doubleVar:
				GenerateINTCode (opr, 14, 2, 0);
				break;
			case doubleArray:
				GenerateINTCode (opr, 14, 2, 0);
				break;
			case charVar:
				GenerateINTCode (opr, 14, 3, 0);
				break;
			case charArray:
				GenerateINTCode (opr, 14, 3, 0);
				break;
			case boolVar:
				GenerateINTCode (opr, 14, 4, 0);
				break;
			case boolArray:
				GenerateINTCode (opr, 14, 4, 0);
				break;
		}

		GenerateINTCode (sto, offset, tableNum, 0); /* store the value of top element in variable */
		
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