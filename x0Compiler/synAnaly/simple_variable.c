#include "../global.h"

/*
 * simple_variable syntactical analyzer
 * store information of simple_variable in ptr_kind, ptr_offset, ptr_size1 and ptr_size2
 */
void simple_variable (enum objectKind* ptr_kind, int* ptr_offset)
{
	if (sym == ident)
	{
		int pos = find_position_v1 (id, tableNum);
		if (pos == -1)	/* the identifier hasn't been declared */
		{
			error (24);
		}
		*ptr_kind = functionTable[tableNum][pos].kind;
		*ptr_offset = functionTable[tableNum][pos].offset;
		
		readSymbol ();
		if (sym == lbracket)
		{
			/* identifier isn't array */
			if (functionTable[tableNum][pos].kind != intArray && functionTable[tableNum][pos].kind != charArray
				&& functionTable[tableNum][pos].kind != boolArray && functionTable[tableNum][pos].kind != doubleArray)
			{
				error (26);
			}
			
			/* check whether array subscript is out of bound if subscript is a number */
			backup ();
			int currentDimension = 0;
			while (sym == lbracket)
			{
				readSymbol ();
				if (sym == intnum)
				{
					int tempNum = intNum;
					readSymbol ();
					if (sym == rbracket)
					{
						/* array subscript is out of bound */
						if (tempNum >= functionTable[tableNum][pos].size[currentDimension++])
						{
							error (51);
						}
						readSymbol ();
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
				readSymbol ();
				expression ();
				if (sym == rbracket)
				{
					readSymbol ();
				}
				else /* the lack of ']' */
				{
					error (9);
				}
			}
		}
		else
		{
			/* identifier isn't {const} variable */
			if (functionTable[tableNum][pos].kind != intVar && functionTable[tableNum][pos].kind != charVar
				&& functionTable[tableNum][pos].kind != boolVar && functionTable[tableNum][pos].kind != doubleVar
				&& functionTable[tableNum][pos].kind != constIntVar && functionTable[tableNum][pos].kind != constCharVar
				&& functionTable[tableNum][pos].kind != constBoolVar && functionTable[tableNum][pos].kind != constDoubleVar)
			{
				error (25);
			}
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}