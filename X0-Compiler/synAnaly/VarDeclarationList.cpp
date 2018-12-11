#include "../global.h"

/*
* VarDeclarationStat syntactical analyzer
*/
void VarDeclarationStat (int* ptr_offset)
{
	DataType dt = type ();

	if (sym == ident)
	{
		ReadSymbol ();
		if (sym == lbracket)
		{
			int size[MAX_DIMENSION] = { 0 };
			int d = 0;
			int space = 1; /* the space distributed to this array */
			while (sym == lbracket)
			{
				ReadSymbol ();
				if (sym == intnum)
				{
					size[d++] = intNum;
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

			if (dt == Char) /* char array is declared */
			{
				EnterTable (charArray, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else if (dt == Int) /* int array is declared */
			{
				EnterTable (intArray, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else if (dt == Bool) /* bool array is declared */
			{
				EnterTable (boolArray, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + space;
			}
			else /* double array is declared */
			{
				EnterTable (doubleArray, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + space;
			}
		}
		else
		{
			int size[MAX_DIMENSION] = { 0 };
			int d = 0;
			if (dt == Char) /* char variable is declared */
			{
				EnterTable (charVar, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (dt == Int) /* int variable is declared */
			{
				EnterTable (intVar, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (dt == Bool) /* bool variable is declared */
			{
				EnterTable (boolVar, *ptr_offset, size, d, 0);
				*ptr_offset = *ptr_offset + 1;
			}
			else /* double variable is declared */
			{
				EnterTable (doubleVar, *ptr_offset, size, d, 0);
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