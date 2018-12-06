#include "../global.h"

/*
 * var_declaration_stat syntactical analyzer
 */
void var_declaration_stat (int* ptr_offset)
{	
	/* 
	 * current type of symbol, 1: INT, 2: DOUBLE, 3: CHAR, 4: BOOL
	 */
	int typeSym;

	switch (sym)
	{
		case intsym:
			typeSym = 1;
			break;
		case charsym:
			typeSym = 3;
			break;
		case bolsym:
			typeSym = 4;
			break;
		case dblsym:
			typeSym = 2;
			break;
	}

	type ();

	if (sym == ident)
	{
		readSymbol ();
		
		if (sym == lbracket)
		{
			int size[MAX_DIMENSION] = { 0 };
			int dimension = 0;
			int space = 1; /* the space distributed to this array */

			while (sym == lbracket)
			{
				readSymbol ();

				if (sym == intnum)
				{
					size[dimension++] = intNum;
					space *= intNum;
					readSymbol ();

					if (sym == rbracket)
					{
						readSymbol ();
					}
					else /* the lack of ']' */
					{
						error (9);
					}
				}
				else /* the lack of integer */
				{
					error (8);
				}
			}

			if (typeSym == 3) /* CHAR array is declared */
			{
				enter (charArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else if (typeSym == 1) /* INT array is declared */
			{
				enter (intArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else if (typeSym == 4) /* BOOL array is declared */
			{
				enter (boolArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else /* DOUBLE array is declared */
			{
				enter (doubleArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
		}
		else
		{
			int size[MAX_DIMENSION] = { 0 };
			int dimension = 0;

			if (typeSym == 3) /* CHAR variable is declared */
			{
				enter (charVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 1) /* INT variable is declared */
			{
				enter (intVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 4) /* BOOL variable is declared */
			{
				enter (boolVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else /* DOUBLE variable is declared */
			{
				enter (doubleVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
		}

		if (sym == semic)
		{
			readSymbol ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}

	}
	else /* the lack of identifier */
	{
		error (6);
	}
}