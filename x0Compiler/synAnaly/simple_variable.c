#include "../global.h"

/*
 * simpleVariable syntactical analyzer
 * store information of simpleVariable in ptr_kind, ptr_offset, ptr_size1 and ptr_size2
 */
void simpleVariable (enum objectKind* ptr_kind, int* ptr_offset)
{
	if (sym == ident)
	{
		int pos = findPosition_V1 (id);
		if (pos == -1)	/* the identifier hasn't been declared */
		{
			error (24);
		}
		*ptr_kind = table[pos].kind;
		*ptr_offset = table[pos].offset;
		
		readSymbol ();
		if (sym == lbracket)
		{
			/* identifier isn't array */
			if (table[pos].kind != intArray && table[pos].kind != charArray
				&& table[pos].kind != boolArray && table[pos].kind != doubleArray)
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
						if (tempNum >= table[pos].size[currentDimension++])
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
			if (table[pos].kind != intVar && table[pos].kind != charVar
				&& table[pos].kind != boolVar && table[pos].kind != doubleVar
				&& table[pos].kind != constIntVar && table[pos].kind != constCharVar
				&& table[pos].kind != constBoolVar && table[pos].kind != constDoubleVar)
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