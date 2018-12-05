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
				enter (charVar, *ptr_offset, 1, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 1) /* INT variable is declared */
			{
				enter (intVar, *ptr_offset, 1, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else if (typeSym == 4) /* BOOL variable is declared */
			{
				enter (boolVar, *ptr_offset, 1, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else /* DOUBLE variable is declared */
			{
				enter (doubleVar, *ptr_offset, 1, 1);
				*ptr_offset = *ptr_offset + 1;
			}

			getSym ();
		}
		else if (sym == lbracket)
		{
			getSym ();

			if (sym == intnum)
			{
				int tempNum1 = intNum;
				getSym ();

				if (sym == rbracket)
				{
					getSym ();

					if (sym == semic)
					{
						/* CHAR 1-dimension array is declared */
						if (typeSym == 3)
						{
							enter (charArray, *ptr_offset, intNum, 1);
							*ptr_offset = *ptr_offset + intNum;
						}
						else if(typeSym == 1) /* INT 1-dimension array is declared */
						{
							enter (intArray, *ptr_offset, intNum, 1);
							*ptr_offset = *ptr_offset + intNum;
						}
						else if (typeSym == 4) /* BOOL 1-dimension array is declared */
						{
							enter (boolArray, *ptr_offset, intNum, 1);
							*ptr_offset = *ptr_offset + intNum;
						}
						else /* DOUBLE 1-dimension array is declared */
						{
							enter (doubleArray, *ptr_offset, intNum, 1);
							*ptr_offset = *ptr_offset + intNum;
						}
						
						getSym ();
					}
					else if (sym == lbracket)
					{
						getSym ();

						if (sym == intnum)
						{
							int tempNum2 = intNum;
							getSym ();

							if (sym == rbracket)
							{
								getSym ();

								if (sym == semic)
								{
									/* CHAR 2-dimension array is declared */
									if (typeSym == 3)
									{
										enter (charArray, *ptr_offset, tempNum1, tempNum2);
										*ptr_offset = *ptr_offset + tempNum1 * tempNum2;
									}
									else if (typeSym == 1) /* INT 2-dimension array is declared */
									{
										enter (intArray, *ptr_offset, tempNum1, tempNum2);
										*ptr_offset = *ptr_offset + tempNum1 * tempNum2;
									}
									else if (typeSym == 4) /* BOOL 2-dimension array is declared */
									{
										enter (boolArray, *ptr_offset, tempNum1, tempNum2);
										*ptr_offset = *ptr_offset + tempNum1 * tempNum2;
									}
									else /* DOUBLE 2-dimension array is declared */
									{
										enter (doubleArray, *ptr_offset, tempNum1, tempNum2);
										*ptr_offset = *ptr_offset + tempNum1 * tempNum2;
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