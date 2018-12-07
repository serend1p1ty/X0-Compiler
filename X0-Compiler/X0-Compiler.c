#include "global.h"

/* 
 * function: check whether the syntax is correct, and generate intermidiate code
 */
void compile ()
{
	/* we are not sure where the program should jump to, so backfill it later */
	GenerateINTCode (jmp, 0, 0, 0);
	ReadSymbol ();
	FunctionList ();
	code[0].operand1 = iterCode; /* backfill */
	if (sym == mainsym)
	{
		tableNum++;		/* Create a new symbol table */
		iterFctInfo++;  /* Create a new FunctionInfo */
		strcpy (fctInfo[iterFctInfo].name, id);
		fctInfo[iterFctInfo].startINTCode = iterCode;
		fctInfo[iterFctInfo].posSymTables = tableNum;
		fctInfo[iterFctInfo].parameterNum = 0;

		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();
			if (sym == rparen)
			{
				ReadSymbol ();
				if (sym == lbrace)
				{
					ReadSymbol ();

					/* offset of local variable relative to the base address of current activity record */
					int offset = 3;

					/* offset is increasing when analysing ConstDeclarationList */
					ConstDeclarationList (&offset);

					/* offset is increasing when analysing VarDeclarationList */
					VarDeclarationList (&offset);

					/* initialize a space in the stack for current activity record */
					GenerateINTCode (ini, offset, iterFctInfo, 0);

					StatementList ();

					if (sym == rbrace)
					{
						GenerateINTCode (opr, 0, 0, 0); /* return to the location where current function is called */

						printf ("\n***************\n");
						printf ("Compile successfully!\n");
						printf ("***************\n");
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
	else /* the lack of 'main' */
	{
		ErrorHandler (23);
	}
}

int main ()
{
	//printf ("input x0 file name£º");
	//scanf ("%s", fileName);

	strcpy (fileName, "../../testSamples/testFunction.txt");

	if ((inputFile = fopen (fileName, "r")) == NULL) /* can't open this file */
	{
		printf ("can't open this file !\n");
		return 1;
	}

	char temp = fgetc (inputFile);
	if (feof(inputFile)) /* input file is empty */
	{
		printf ("input file is empty !\n");
		fclose (inputFile);
		return 1;
	}
	rewind (inputFile);

	compile ();

	FILE* fout = fopen ("../../testSamples/output.txt", "w");
	for (int i = 0; i < iterCode; i++)
	{
		fprintf (fout, "[%d] %s %d %d %.2f\n", i, fctCodeString[code[i].fct], code[i].operand1, 
											code[i].operand2, code[i].operand3);
	}
	fclose (fout);

	Interpret ();

	return 0;
}