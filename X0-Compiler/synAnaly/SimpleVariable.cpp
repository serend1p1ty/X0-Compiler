#include "../global.h"

/*
 * SimpleVariable syntactical analyzer
 * store information of SimpleVariable in ptr_kind, ptr_offset
 */
void SimpleVariable (ObjectKind* ptr_kind, int* ptr_offset)
{
	if (sym == ident)
	{
		int pos = FindPosition (id, fctNum - 1);

		if (pos == -1)	/* the identifier hasn't been declared */
		{
			ErrorHandler (23);
		}
		
		*ptr_kind = fctInfo[fctNum - 1].symTable[pos].kind;
		*ptr_offset = fctInfo[fctNum - 1].symTable[pos].offset;
		ReadSymbol ();
		if (sym == lbracket)
		{
			/* identifier isn't array */
			if (*ptr_kind != intArray && *ptr_kind != charArray
				&& *ptr_kind != boolArray && *ptr_kind != doubleArray)
			{
				ErrorHandler (25);
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
						if (tempNum >= fctInfo[fctNum - 1].symTable[pos].size[currentDimension++])
						{
							ErrorHandler (50);
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
			if (*ptr_kind != intVar && *ptr_kind != charVar
				&& *ptr_kind != boolVar && *ptr_kind != doubleVar
				&& *ptr_kind != constIntVar && *ptr_kind != constCharVar
				&& *ptr_kind != constBoolVar && *ptr_kind != constDoubleVar)
			{
				ErrorHandler (24);
			}
		}
	}
	else /* the lack of identifier */
	{
		ErrorHandler (6);
	}
}