#include "../global.h"

/*
* VarDeclarationStat syntactical analyzer
*/
void VarDeclarationStat (int* ptr_offset)
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
		ReadSymbol ();
		if (sym == lbracket)
		{
			int size[MAX_DIMENSION] = { 0 };
			int dimension = 0;
			int space = 1; /* the space distributed to this array */
			while (sym == lbracket)
			{
				ReadSymbol ();
				if (sym == intnum)
				{
					size[dimension++] = intNum;
					space *= intNum;
					ReadSymbol ();
					if (sym == rbracket)
					{
						ReadSymbol ();
					}
					else /* the lack of ']' */
					{
						ErrorHandler (9);
					}
				}
				else /* the lack of integer */
				{
					ErrorHandler (8);
				}
			}

			if (typeSym == 3) /* CHAR array is declared */
			{
				EnterTable (charArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else if (typeSym == 1) /* INT array is declared */
			{
				EnterTable (intArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else if (typeSym == 4) /* BOOL array is declared */
			{
				EnterTable (boolArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else /* DOUBLE array is declared */
			{
				EnterTable (doubleArray, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + space;
			}
		}
		else
		{
			int size[MAX_DIMENSION] = { 0 };
			int dimension = 0;
			if (typeSym == 3) /* CHAR variable is declared */
			{
				EnterTable (charVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 1) /* INT variable is declared */
			{
				EnterTable (intVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 4) /* BOOL variable is declared */
			{
				EnterTable (boolVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else /* DOUBLE variable is declared */
			{
				EnterTable (doubleVar, *ptr_offset, size, dimension, 0);
				*ptr_offset = *ptr_offset + 1;
			}
		}

		if (sym == semic)
		{
			ReadSymbol ();
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}

	}
	else /* the lack of identifier */
	{
		ErrorHandler (6);
	}
}

/*
 * VarDeclarationList syntactical analyzer
 */
void VarDeclarationList (int* ptr_offset)
{	
	/* execute VarDeclarationStat syntactical analyzer if sym belong to first(VarDeclarationStat) */
	while (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		VarDeclarationStat (ptr_offset);
	}
}