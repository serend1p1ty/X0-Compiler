#include "../global.h"

/*
 * declarationStat syntactical analyzer
 */
void declarationStat (int* ptr_offset)
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
		getSym ();

		if (sym == semic)
		{
			/* CHAR variable is declared */
			if (typeSym == 3)
			{
				enter (charVar, *ptr_offset, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 1) /* INT variable is declared */
			{
				enter (intVar, *ptr_offset, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 4) /* BOOL variable is declared */
			{
				enter (boolVar, *ptr_offset, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else /* DOUBLE variable is declared */
			{
				enter (doubleVar, *ptr_offset, 1);
				*ptr_offset = *ptr_offset + 1;
			}

			getSym ();
		}
		else if (sym == lbracket)
		{
			getSym ();
			if (sym == intnum)
			{
				getSym ();
				if (sym == rbracket)
				{
					getSym ();
					if (sym == semic)
					{
						/* CHAR array is declared */
						if (typeSym == 3)
						{
							enter (charArray, *ptr_offset, intNum);
							*ptr_offset = *ptr_offset + intNum;
						}
						else if(typeSym == 1) /* INT array is declared */
						{
							enter (intArray, *ptr_offset, intNum);
							*ptr_offset = *ptr_offset + intNum;
						}
						else if (typeSym == 4) /* BOOL array is declared */
						{
							enter (boolArray, *ptr_offset, intNum);
							*ptr_offset = *ptr_offset + intNum;
						}
						else /* DOUBLE array is declared */
						{
							enter (doubleArray, *ptr_offset, intNum);
							*ptr_offset = *ptr_offset + intNum;
						}
						
						getSym ();
					}
					else /* the lack of ';' */
					{
						error (10);
					}
				}
				else /* the lack of ']' */
				{
					error (9);
				}
			}
			else /* the lack of INT number */
			{
				error (8);
			}
		}
		else /* the lack of ';' or '[' */
		{
			error (7);
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}