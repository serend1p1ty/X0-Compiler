#include "../global.h"

/*
* ConstDeclarationStat syntactical analyzer
*/
void ConstDeclarationStat (int* ptr_offset)
{
	if (sym == cstsym)
	{
		ReadSymbol ();
	}
	else /* the lack of 'const' */
	{
		ErrorHandler (52);
	}

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
		if (sym == eql)
		{
			ReadSymbol ();
			int sizeArray[MAX_DIMENSION] = { 0 };
			int dimension = 0;
			if (sym == intnum || sym == doublenum)
			{
				ReadSymbol ();
				switch (typeSym)
				{
					case 1:
						EnterTable (constIntVar, *ptr_offset, sizeArray, 
							dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 2:
						EnterTable (constDoubleVar, *ptr_offset, sizeArray, 
							dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 3:
						EnterTable (constCharVar, *ptr_offset, sizeArray, 
							dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 4:
						EnterTable (constBoolVar, *ptr_offset, sizeArray, 
							dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
				}
			}
			else if (sym == truesym || sym == falsesym)
			{
				ReadSymbol ();
				switch (typeSym)
				{
					case 1:
						EnterTable (constIntVar, *ptr_offset, sizeArray, 
							dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 2:
						EnterTable (constDoubleVar, *ptr_offset, sizeArray, 
							dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 3:
						EnterTable (constCharVar, *ptr_offset, sizeArray, 
							dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 4:
						EnterTable (constBoolVar, *ptr_offset, sizeArray, 
							dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
				}
			}
			else /* the lack of number can be assigned */
			{
				ErrorHandler (7);
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
		else /* the lack of '=' */
		{
			ErrorHandler (11);
		}
	}
	else /* the lack of identifier */
	{
		ErrorHandler (6);
	}
}

/*
 * ConstDeclarationList syntactical analyzer
 */
void ConstDeclarationList (int* ptr_offset)
{
	/* execute ConstDeclarationStat syntactical analyzer if sym belong to first(ConstDeclarationStat) */
	while (sym == cstsym)
	{
		ConstDeclarationStat (ptr_offset);
	}
}