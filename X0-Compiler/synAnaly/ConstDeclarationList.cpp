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
		ErrorHandler (51);
	}

	DataType dt = type ();
	if (sym == ident)
	{
		ReadSymbol ();
		if (sym == eql)
		{
			ReadSymbol ();
			int size[MAX_DIMENSION] = { 0 };
			int d = 0;
			if (sym == intnum || sym == doublenum)
			{
				ReadSymbol ();
				switch (dt)
				{
					case Int:
						EnterTable (constIntVar, *ptr_offset, size, 
							d, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case Double:
						EnterTable (constDoubleVar, *ptr_offset, size, 
							d, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case Char:
						EnterTable (constCharVar, *ptr_offset, size, 
							d, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
					case Bool:
						EnterTable (constBoolVar, *ptr_offset, size, 
							d, sym == intnum ? intNum : doubleNum);
						*ptr_offset = *ptr_offset + 1;
						break;
				}
			}
			else if (sym == truesym || sym == falsesym)
			{
				ReadSymbol ();
				switch (dt)
				{
					case Int:
						EnterTable (constIntVar, *ptr_offset, size, 
							d, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case Double:
						EnterTable (constDoubleVar, *ptr_offset, size, 
							d, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case Char:
						EnterTable (constCharVar, *ptr_offset, size, 
							d, sym == truesym ? 1 : 0);
						*ptr_offset = *ptr_offset + 1;
						break;
					case Bool:
						EnterTable (constBoolVar, *ptr_offset, size, 
							d, sym == truesym ? 1 : 0);
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