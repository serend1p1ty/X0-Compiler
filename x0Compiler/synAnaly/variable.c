#include "../global.h"

/*
 * variable syntactical analyzer
 * store information of variable in  ptr_kind, ptr_offset, ptr_size1, ptr_size2 and ptr_IncOrDec
 */
void variable (enum objectKind* ptr_kind, int* ptr_offset, int* ptr_size1, int* ptr_size2, int* ptr_IncOrDec)
{
	if (sym == ident)
	{
		simpleVariable (ptr_kind, ptr_offset, ptr_size1, ptr_size2);

		if (sym == incsym)
		{
			/* auto-adding or auto-decreasing variable must be INT or CHAR */
			if (*ptr_kind != intVar && *ptr_kind != intArray
				&& *ptr_kind != charVar && *ptr_kind != charArray)
			{
				error (50);
			}

			*ptr_IncOrDec = 1;
			getSym ();
		}
		else if (sym == decsym)
		{
			/* auto-adding or auto-decreasing variable must be INT or CHAR */
			if (*ptr_kind != intVar && *ptr_kind != intArray
				&& *ptr_kind != charVar && *ptr_kind != charArray)
			{
				error (50);
			}

			*ptr_IncOrDec = 2;
			getSym ();
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

		getSym ();
		simpleVariable (ptr_kind, ptr_offset, ptr_size1, ptr_size2);

		/* auto-adding or auto-decreasing variable must be INT or CHAR */
		if (*ptr_kind != intVar && *ptr_kind != intArray
			&& *ptr_kind != charVar && *ptr_kind != charArray)
		{
			error (50);
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}