#include "../global.h"

/*
 * readStat syntactical analyzer
 */
void readStat ()
{
	if (sym == readsym)
	{
		getSym ();
		
		int offset;    /* the offset relative to the base address of current activity record */
		int isArray;   /* 1: 'variable' is array element   0: 'variable' is just a variable */
		int IncOrDec;  /* 1: auto-adding after variable   2: auto-decreasing after variable
					    * 3: auto-adding before variable  4: auto-decreasing before variable
					    * 5: without auto-adding or auto-decreasing */
		int identType; /* 1: INT   2: DOUBLE   3: CHAR   4: BOOL */
		variable (&offset, &isArray, &IncOrDec, &identType);

		/* 'read' function can't read auto-adding or auto-decreasing variable */
		if (IncOrDec != 5)
		{
			error (33);
		}

		gen (opr, identType, 14); /* read a variable using scanf function */
		
		/* store the value of top element in variable */
		if (isArray)
		{
			gen (stf, 0, offset);
		}
		else
		{
			gen (sto, 0, offset);
		}

		if (sym == semic)
		{
			getSym ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else /* the lack of 'read' */
	{
		error (18);
	}
}