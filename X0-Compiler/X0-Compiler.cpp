#include "global.h"

/* 
 * function: check whether the syntax is correct, and generate intermediate code
 */
void compile ()
{
	/* we are not sure where the program should jump to, so backfill it later */
	GenINTCode (jmp, 0, 0);
	ReadSymbol ();
	FunctionList ();
	code[0].opr1 = codeNum; /* backfill */

	if (sym == mainsym)
	{
		fctNum++;
		strcpy (fctInfo[fctNum].name, id);
		fctInfo[fctNum].startINTCode = codeNum;
		fctInfo[fctNum].paraNum = 0;
		fctInfo[fctNum].retType = retVoid;

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
					GenINTCode (ini, fctNum - 1, 0);

					StatementList ();

					if (sym == rbrace)
					{
						/* return to the location where current function is called */
						GenINTCode (opr, 0, fctNum - 1);
						printf ("\nCompile successfully!\n");
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
		ErrorHandler (22);
	}
}

int main ()
{

	strcpy (fileName, "../../testSamples/test19.txt");

	if ((fin = fopen (fileName, "r")) == NULL) /* can't open this file */
	{
		printf ("can't open this file !\n");
		return 1;
	}

	char temp = fgetc (fin);
	if (feof(fin)) /* input file is empty */
	{
		printf ("input file is empty !\n");
		fclose (fin);
		return 1;
	}
	rewind (fin);

	compile ();

	FILE* fout = fopen ("../../testSamples/INT-Code.txt", "w");
	for (int i = 0; i < codeNum; i++)
	{
		fprintf (fout, "[%d] %s %d %.2f\n", i, fctCodeString[code[i].fct], code[i].opr1, code[i].opr2);
	}
	fclose (fout);

	Interpret ();

	return 0;
}