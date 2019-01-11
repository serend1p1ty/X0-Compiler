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
		strcpy (fctInfo[fctNum - 1].name, id);
		fctInfo[fctNum - 1].startINTCode = codeNum;
		fctInfo[fctNum - 1].paraNum = 0;
		fctInfo[fctNum - 1].tableSize = 0;
		fctInfo[fctNum - 1].retType = retVoid;

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
	/*printf ("Input file path: ");
	scanf ("%s", fileName);*/
	strcpy (fileName, "../../X0-Compiler-GUI/data/input.txt");

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

	Interpret ();

	/*FILE* fout = fopen ("./data/code.bin", "wb");
	fwrite (code, sizeof (code[0]), codeNum, fout);
	fclose (fout);

	fout = fopen ("./data/fctInfo.bin", "wb");
	fwrite (fctInfo, sizeof (fctInfo[0]), fctNum, fout);
	fclose (fout);*/

	return 0;
}