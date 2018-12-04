#include "../global.h"

/*
 * simpleVariable syntactical analyzer
 */
void simpleVariable (int* ptr_offset, int* ptr_isArray, int* ptr_identType, int* ptr_size)
{
	if (sym == ident)
	{
		int pos = findPosition (id);

		if (pos == -1)	/* the identifier hasn't been declared */
		{
			error (24);
		}

		getSym ();

		if (sym == lbracket)
		{
			getSym ();
			expression ();

			if (sym == rbracket)
			{
				/* identifier isn't INT/CHAR/BOOL/DOUBLE array */
				if (table[pos].kind != intArray && table[pos].kind != charArray
					&& table[pos].kind != boolArray && table[pos].kind != doubleArray)
				{
					error (26);
				}

				*ptr_offset = table[pos].offset;
				*ptr_isArray = 1;
				*ptr_size = table[pos].size;

				switch (table[pos].kind)
				{
					case intArray:
						*ptr_identType = 1;
						break;
					case doubleArray:
						*ptr_identType = 2;
						break;
					case charArray:
						*ptr_identType = 3;
						break;
					case boolArray:
						*ptr_identType = 4;
						break;
				}

				getSym ();
			}
			else /* the lack of ']' */
			{
				error (9);
			}
		}
		else
		{
			/* identifier isn't INT/CHAR/BOOL/DOUBLE variable */
			if (table[pos].kind != intVar && table[pos].kind != charVar
				&& table[pos].kind != boolVar && table[pos].kind != doubleVar)
			{
				error (25);
			}

			*ptr_offset = table[pos].offset;
			*ptr_isArray = 0;
			*ptr_size = table[pos].size;

			switch (table[pos].kind)
			{
				case intVar:
					*ptr_identType = 1;
					break;
				case doubleVar:
					*ptr_identType = 2;
					break;
				case charVar:
					*ptr_identType = 3;
					break;
				case boolVar:
					*ptr_identType = 4;
					break;
			}
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}