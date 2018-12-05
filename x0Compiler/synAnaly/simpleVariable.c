#include "../global.h"

/*
 * simpleVariable syntactical analyzer
 * store information of simpleVariable in  ptr_kind, ptr_offset, ptr_size1 and ptr_size2
 */
void simpleVariable (enum objectKind* ptr_kind, int* ptr_offset, int* ptr_size1, int*ptr_size2)
{
	if (sym == ident)
	{
		int pos = findPosition (id);

		if (pos == -1)	/* the identifier hasn't been declared */
		{
			error (24);
		}

		*ptr_kind = table[pos].kind;
		*ptr_offset = table[pos].offset;
		*ptr_size1 = table[pos].size1;
		*ptr_size2 = table[pos].size2;
		getSym ();

		if (sym == lbracket)
		{
			getSym ();
			
			/* check whether array subscript is out of bound if 'expression' is a number */
			backup ();
			if (sym == intnum)
			{
				int tempNum = intNum;
				getSym ();

				if (sym == rbracket)
				{
					/* array subscript is out of bound */
					if (tempNum >= table[pos].size1)
					{
						error (51);
					}
				}
			}
			recover ();
			
			expression ();

			if (sym == rbracket)
			{
				/* identifier isn't INT/CHAR/BOOL/DOUBLE array */
				if (table[pos].kind != intArray && table[pos].kind != charArray
					&& table[pos].kind != boolArray && table[pos].kind != doubleArray)
				{
					error (26);
				}

				getSym ();

				if (sym == lbracket)
				{
					getSym ();

					/* check whether array subscript is out of bound if 'expression' is a number */
					backup ();
					if (sym == intnum)
					{
						int tempNum = intNum;
						getSym ();

						if (sym == rbracket)
						{
							/* array subscript is out of bound */
							if (tempNum >= table[pos].size2)
							{
								error (51);
							}
						}
					}
					recover ();

					expression ();

					if (sym == rbracket)
					{
						getSym ();
					}
					else /* the lack of ']' */
					{
						error (9);
					}
				}
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
		}
	}
	else /* the lack of identifier */
	{
		error (6);
	}
}