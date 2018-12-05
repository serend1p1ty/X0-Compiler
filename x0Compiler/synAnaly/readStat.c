#include "../global.h"

/*
 * readStat syntactical analyzer
 */
void readStat ()
{
	if (sym == readsym)
	{
		getSym ();
		
		int size1;
		int size2;
		int offset;
		enum objectKind kind;
		int IncOrDec;
		variable (&kind, &offset, &size1, &size2, &IncOrDec);

		/* 'read' function can't read auto-adding or auto-decreasing variable */
		if (IncOrDec != 5)
		{
			error (33);
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
		
		/* store the value of top element in variable */
		if (kind == intArray || kind == charArray
			|| kind == boolArray || kind == doubleArray)
		{
			gen (sto2, offset, 0, 0);
		}
		else
		{
			gen (sto, offset, 0, 0);
		}

		if (sym == semic)
		{
			getSym ();
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