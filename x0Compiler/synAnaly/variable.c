#include "../global.h"

/*
 * variable syntactical analyzer
 */
void variable (int* ptr_offset, int* ptr_isArray, int* ptr_IncOrDec, int* ptr_identType, int* ptr_size)
{
	if (sym == ident)
	{
		simpleVariable (ptr_offset, ptr_isArray, ptr_identType, ptr_size);

		if (sym == incsym)
		{
			/* auto-adding or auto-decreasing variable must be INT */
			if (*ptr_identType != 1)
			{
				error (50);
			}

			*ptr_IncOrDec = 1;
			getSym ();
		}
		else if (sym == decsym)
		{
			/* auto-adding or auto-decreasing variable must be INT */
			if (*ptr_identType != 1)
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
		simpleVariable (ptr_offset, ptr_isArray, ptr_identType, ptr_size);

		/* auto-adding or auto-decreasing variable must be INT */
		if (*ptr_identType != 1)
		{
			error (50);
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}