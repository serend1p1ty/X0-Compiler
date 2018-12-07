#include "../global.h"

/*
 * SimpleVariable syntactical analyzer
 * store information of SimpleVariable in ptr_kind, ptr_offset, ptr_size1 and ptr_size2
 */
void SimpleVariable (ObjectKind* ptr_kind, int* ptr_offset)
{
	if (sym == ident)
	{
		int pos = FindPosition_V1 (id, tableNum);

		if (pos == -1)	/* the identifier hasn't been declared */
		{
			ErrorHandler (24);
		}
		
		*ptr_kind = symTables[tableNum][pos].kind;
		*ptr_offset = symTables[tableNum][pos].offset;	
		ReadSymbol ();
		if (sym == lbracket)
		{
			/* identifier isn't array */
			if (symTables[tableNum][pos].kind != intArray && symTables[tableNum][pos].kind != charArray
				&& symTables[tableNum][pos].kind != boolArray && symTables[tableNum][pos].kind != doubleArray)
			{
				ErrorHandler (26);
			}
			
			/* check whether array subscript is out of bound if subscript is a number */
			backup ();
			int currentDimension = 0;
			while (sym == lbracket)
			{
				ReadSymbol ();
				if (sym == intnum)
				{
					int tempNum = intNum;
					ReadSymbol ();
					if (sym == rbracket)
					{
						/* array subscript is out of bound */
						if (tempNum >= symTables[tableNum][pos].sizeArray[currentDimension++])
						{
							ErrorHandler (51);
						}

						ReadSymbol ();
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			recover ();
			
			while (sym == lbracket)
			{
				ReadSymbol ();
				expression ();
				if (sym == rbracket)
				{
					ReadSymbol ();
				}
				else /* the lack of ']' */
				{
					ErrorHandler (9);
				}
			}
		}
		else
		{
			/* identifier isn't {const} variable */
			if (symTables[tableNum][pos].kind != intVar && symTables[tableNum][pos].kind != charVar
				&& symTables[tableNum][pos].kind != boolVar && symTables[tableNum][pos].kind != doubleVar
				&& symTables[tableNum][pos].kind != constIntVar && symTables[tableNum][pos].kind != constCharVar
				&& symTables[tableNum][pos].kind != constBoolVar && symTables[tableNum][pos].kind != constDoubleVar)
			{
				ErrorHandler (25);
			}
		}
	}
	else /* the lack of identifier */
	{
		ErrorHandler (6);
	}
}