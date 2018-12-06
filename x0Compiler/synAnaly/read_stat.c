#include "../global.h"

/*
 * read_stat syntactical analyzer
 */
void read_stat ()
{
	if (sym == readsym)
	{
		readSymbol ();
		
		enum objecKind kind;
		int offset;
		int IncOrDec;	/* 1: Increase after variable   2: decrease after variable
					     * 3: Increase before variable  4: decrease before variable
					     * 5: without Increase or decrease */
		variable (&kind, &offset, &IncOrDec);

		/* 'read' function can't read Increasing or decreasing variable */
		if (IncOrDec != 5)
		{
			error (33);
		}

		/* constant can't be read */
		if (kind == constIntVar || kind == constCharVar
			|| kind == constBoolVar || kind == constDoubleVar)
		{
			error (53);
		}

		/* read a variable using scanf function */
		switch (kind)
		{
			case intVar:
				gen (opr, 14, 1, 0);
				break;
			case intArray:
				gen (opr, 14, 1, 0);
				break;
			case doubleVar:
				gen (opr, 14, 2, 0);
				break;
			case doubleArray:
				gen (opr, 14, 2, 0);
				break;
			case charVar:
				gen (opr, 14, 3, 0);
				break;
			case charArray:
				gen (opr, 14, 3, 0);
				break;
			case boolVar:
				gen (opr, 14, 4, 0);
				break;
			case boolArray:
				gen (opr, 14, 4, 0);
				break;
		}

		gen (sto, offset, 0, 0); /* store the value of top element in variable */
		
		if (sym == semic)
		{
			readSymbol ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else /* the lack of 'read' */
	{
		error (18);
	}
}