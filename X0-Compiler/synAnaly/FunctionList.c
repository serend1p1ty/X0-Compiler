#include "../global.h"

/* 
 * parameter syntactical analyzer 
 */
void parameter (int* ptr_offset)
{
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
		int size[MAX_DIMENSION] = { 0 };
		int dimension = 0;
		if (typeSym == 3)
		{
			EnterTable (charVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else if (typeSym == 1)
		{
			EnterTable (intVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else if (typeSym == 4)
		{
			EnterTable (boolVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else
		{
			EnterTable (doubleVar, *ptr_offset, size, dimension, 0);
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
	int parameterNum = 0;
	if (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		parameter (ptr_offset);
		parameterNum++;
		while (sym == comma)
		{
			ReadSymbol ();
			parameter (ptr_offset);
			parameterNum++;
		}
	}
	return parameterNum;
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
			tableNum++;		/* Create a new symbol table */
			iterFctInfo++;  /* Create a new FunctionInfo */
			strcpy (fctInfo[iterFctInfo].name, id);
			fctInfo[iterFctInfo].startINTCode = iterCode;
			fctInfo[iterFctInfo].posSymTables = tableNum;

			switch (tempSym)
			{
				case voidsym:
					fctInfo[iterFctInfo].retType = Void;
					break;
				case intsym:
					fctInfo[iterFctInfo].retType = Int;
					break;
				case dblsym:
					fctInfo[iterFctInfo].retType = Double;
					break;
				case charsym:
					fctInfo[iterFctInfo].retType = Char;
					break;
				case bolsym:
					fctInfo[iterFctInfo].retType = Bool;
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
				fctInfo[iterFctInfo].parameterNum = ParameterNum;
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
						GenerateINTCode (ini, iterFctInfo, 0, 0);

						StatementList ();

						if (sym == rbrace)
						{
							ReadSymbol ();

							/* return to the location where current function is called */
							GenerateINTCode (opr, 0, iterFctInfo, 0);
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
	else /* the lack of 'void' */
	{
		ErrorHandler (55);
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