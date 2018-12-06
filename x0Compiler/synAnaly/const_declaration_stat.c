#include "../global.h"

/*
 * constDeclarationStat syntactical analyzer
 */
void constDeclarationStat (int* ptr_offset)
{
	if (sym == cstsym)
	{
		readSymbol ();
	}
	else /* the lack of 'const' */
	{
		error (52);
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
		readSymbol ();

		if (sym == eql)
		{
			readSymbol ();
			int size[MAX_DIMENSION] = { 0 };
			int dimension = 0;

			if (sym == intnum || sym == doublenum)
			{
				readSymbol ();
				
				switch (typeSym)
				{
					case 1:
						enter (constIntVar, *ptr_offset, size, dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 2:
						enter (constDoubleVar, *ptr_offset, size, dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 3:
						enter (constCharVar, *ptr_offset, size, dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 4:
						enter (constBoolVar, *ptr_offset, size, dimension, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
				}
			}
			else if (sym == truesym || sym == falsesym)
			{
				readSymbol ();

				switch (typeSym)
				{
					case 1:
						enter (constIntVar, *ptr_offset, size, dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 2:
						enter (constDoubleVar, *ptr_offset, size, dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 3:
						enter (constCharVar, *ptr_offset, size, dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case 4:
						enter (constBoolVar, *ptr_offset, size, dimension, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
				}
			}
			else /* the lack of number can be assigned */
			{
				error (7);
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
		else /* the lack of '=' */
		{
			error (11);
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}