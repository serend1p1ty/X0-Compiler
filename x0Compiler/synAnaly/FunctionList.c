#include "../global.h"

void Parameter (int* ptr_offset)
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
			enter (charVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else if (typeSym == 1)
		{
			enter (intVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else if (typeSym == 4)
		{
			enter (boolVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		else
		{
			enter (doubleVar, *ptr_offset, size, dimension, 0);
			*ptr_offset = *ptr_offset + 1;
		}
		readSymbol ();
	}
	else
	{
		error (6);
	}
}

int ParameterList (int* ptr_offset)
{
	int ParameterNum = 0;
	if (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		Parameter (ptr_offset);
		ParameterNum++;
		while (sym == comma)
		{
			readSymbol ();
			Parameter (ptr_offset);
			ParameterNum++;
		}
	}
	return ParameterNum;
}

void Function ()
{
	if (sym == voidsym)
	{
		readSymbol ();
		if (sym == ident)
		{
			/* Create a new symbol table */
			tableNum++;
			iterFctInfo++;
			strcpy (fctInfo[iterFctInfo].name, id);
			fctInfo[iterFctInfo].startINTCode = iterCode;
			fctInfo[iterFctInfo].posSymTables = tableNum;

			readSymbol ();
			if (sym == lparen)
			{
				readSymbol ();
				int offset = 3;
				int ParameterNum = ParameterList (&offset);
				fctInfo[iterFctInfo].parameterNum = ParameterNum;
				if (sym == rparen)
				{
					readSymbol ();
					if (sym == lbrace)
					{
						readSymbol ();
						const_declaration_list (&offset);	/* offset is increasing when analysing const_declaration_list */
						var_declaration_list (&offset);		/* offset is increasing when analysing var_declaration_list */
						gen (ini, offset, iterFctInfo, 0);	/* initialize a space in the stack for current activity record */
						statement_list ();

						if (sym == rbrace)
						{
							readSymbol ();
							gen (opr, 0, 0, 0); /* return to the location where current function is called */
						}
						else /* the lack of '}' */
						{
							error (4);
						}
					}
					else /* the lack of '{' */
					{
						error (5);
					}
				}
				else /* the lack of ')' */
				{
					error (14);
				}
			}
			else /* the lack of '(' */
			{
				error (16);
			}
		}
		else /* the lack of identifier */
		{
			error (6);
		}
	}
	else /* the lack of 'void' */
	{
		error (55);
	}
}

int FunctionList ()
{
	int functionNum = 0;
	while (sym == voidsym)
	{
		Function ();
		functionNum++;
	}
	return functionNum;
}