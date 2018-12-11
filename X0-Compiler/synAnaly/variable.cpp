#include "../global.h"

/*
 * variable syntactical analyzer
 */
void variable (ObjectKind* ptr_kind, int* ptr_offset, int* ptr_IncOrDec)
{
	if (sym == ident)
	{
		SimpleVariable (ptr_kind, ptr_offset);
		if (sym == incsym)
		{
			/* Increasing or decreasing variable must be int or char */
			if (*ptr_kind != intVar && *ptr_kind != intArray
				&& *ptr_kind != charVar && *ptr_kind != charArray)
			{
				ErrorHandler (49);
			}

			*ptr_IncOrDec = 1;
			ReadSymbol ();
		}
		else if (sym == decsym)
		{
			/* Increasing or decreasing variable must be int or char */
			if (*ptr_kind != intVar && *ptr_kind != intArray
				&& *ptr_kind != charVar && *ptr_kind != charArray)
			{
				ErrorHandler (49);
			}

			*ptr_IncOrDec = 2;
			ReadSymbol ();
		}
		else
		{
			*ptr_IncOrDec = 5;
		}
	}
	else if (sym == incsym || sym == decsym)
	{
		if (sym == incsym)
		{
			*ptr_IncOrDec = 3;
		}
		else
		{
			*ptr_IncOrDec = 4;
		}
		ReadSymbol ();
		SimpleVariable (ptr_kind, ptr_offset);

		/* Increasing or decreasing variable must be int or char */
		if (*ptr_kind != intVar && *ptr_kind != intArray
			&& *ptr_kind != charVar && *ptr_kind != charArray)
		{
			ErrorHandler (49);
		}
	}
	else /* the lack of identifier */
	{
		ErrorHandler (6);
	}
}