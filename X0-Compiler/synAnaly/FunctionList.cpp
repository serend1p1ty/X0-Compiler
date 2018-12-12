#include "../global.h"

/* 
 * parameter syntactical analyzer 
 */
void parameter (int* ptr_offset)
{
	DataType dt = type ();

	if (sym == ident)
	{
		int size[MAX_DIMENSION] = { 0 };
		int d = 0;
		if (dt == Char)
		{
			EnterTable (charVar, *ptr_offset, size, d, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else if (dt == Int)
		{
			EnterTable (intVar, *ptr_offset, size, d, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else if (dt == Bool)
		{
			EnterTable (boolVar, *ptr_offset, size, d, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else
		{
			EnterTable (doubleVar, *ptr_offset, size, d, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		ReadSymbol ();
	}
	else /* the lack of identifier */
	{
		ErrorHandler (6);
	}
}

/*
 * ParameterList syntactical analyzer
 */
int ParameterList (int* ptr_offset)
{
	int paraNum = 0;
	if (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		parameter (ptr_offset);
		paraNum++;
		while (sym == comma)
		{
			ReadSymbol ();
			parameter (ptr_offset);
			paraNum++;
		}
	}
	return paraNum;
}

/*
 * function syntactical analyzer
 */
void function ()
{
	if (sym == voidsym || sym == intsym || sym == charsym
		|| sym == dblsym || sym == charsym)
	{
		Symbol tempSym = sym;
		ReadSymbol ();
		if (sym == ident)
		{
			fctNum++;
			strcpy (fctInfo[fctNum - 1].name, id);
			fctInfo[fctNum - 1].startINTCode = codeNum;
			fctInfo[fctNum - 1].tableSize = 0;

			switch (tempSym)
			{
				case voidsym:
					fctInfo[fctNum - 1].retType = retVoid;
					break;
				case intsym:
					fctInfo[fctNum - 1].retType = retInt;
					break;
				case dblsym:
					fctInfo[fctNum - 1].retType = retDouble;
					break;
				case charsym:
					fctInfo[fctNum - 1].retType = retChar;
					break;
				case bolsym:
					fctInfo[fctNum - 1].retType = retBool;
					break;
				default:
					break;
			}

			ReadSymbol ();
			if (sym == lparen)
			{
				ReadSymbol ();
				int offset = 3;
				int ParameterNum = ParameterList (&offset);
				fctInfo[fctNum - 1].paraNum = ParameterNum;
				if (sym == rparen)
				{
					ReadSymbol ();
					if (sym == lbrace)
					{
						ReadSymbol ();

						/* offset is increasing when analysing ConstDeclarationList */
						ConstDeclarationList (&offset);

						/* offset is increasing when analysing VarDeclarationList */
						VarDeclarationList (&offset);

						/* initialize a space in the stack for current activity record */
						GenINTCode (ini, fctNum - 1, 0);

						StatementList ();

						if (sym == rbrace)
						{
							ReadSymbol ();

							/* return to the location where current function is called */
							GenINTCode (opr, 0, fctNum - 1);
						}
						else /* the lack of '}' */
						{
							ErrorHandler (4);
						}
					}
					else /* the lack of '{' */
					{
						ErrorHandler (5);
					}
				}
				else /* the lack of ')' */
				{
					ErrorHandler (14);
				}
			}
			else /* the lack of '(' */
			{
				ErrorHandler (16);
			}
		}
		else /* the lack of identifier */
		{
			ErrorHandler (6);
		}
	}
	else /* illegal return type of function */
	{
		ErrorHandler (54);
	}
}

/*
 * FunctionList syntactical analyzer
 */
void FunctionList ()
{
	while (sym == voidsym || sym == intsym || sym == charsym
		   || sym == dblsym || sym == charsym)
	{
		function ();
	}
}