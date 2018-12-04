#include "global.h"

/* 
 * function: check whether the syntax is correct, and generate intermidiate code
 */
void compile ()
{
	gen (jmp, 1, 0, 0);
	getSym ();

	if (sym == mainsym)
	{
		getSym ();

		if (sym == lbrace)
		{
			getSym ();
			int offset = 3;	/* offset of local variable relative to the base address of current activity record */
			declarationList (&offset); /* offset is increasing when analysing declarationList */
			gen (ini, offset, 0, 0); /* initialize a space in the stack for current activity record */
			statementList ();

			if (sym == rbrace)
			{
				gen (opr, 0, 0, 0); /* return to the location where current function is called */

				printf ("\n***************\n");
				printf ("Compile successfully!\n");
				printf ("***************\n");
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
	else /* the lack of 'main' */
	{
		error (23);
	}
}

int main ()
{
	//printf ("input x0 file name£º");
	//scanf ("%s", fileName);

	strcpy (fileName, "../../testSamples/input.txt");

	if ((fin = fopen (fileName, "r")) == NULL) /* can't open this file */
	{
		printf ("can't open this file !\n");
		return 1;
	}

	if (feof(fin))	/* input file is empty */
	{
		printf ("input file is empty !\n");
		fclose (fin);
		return 1;
	}

	compile ();	/* check whether the syntax is correct, and generate intermidiate code */

	FILE* fout = fopen ("../../testSamples/output.txt", "w");
	for (int i = 0; i < iterCode; i++)
	{
		fprintf (fout, "[%d] %s %d %d %.2f\n", i, fctCode_string[code[i].fct], code[i].operand1, 
											code[i].operand2, code[i].operand3);
	}
	fclose (fout);

	Interpret (); /* interpret and execute intermidiate code */

	return 0;
}