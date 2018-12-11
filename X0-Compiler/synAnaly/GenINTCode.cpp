#include "../global.h"

/*
 * function: generate an intermidiate code.
 */
void GenINTCode (FctCode fct, int opr1, double opr2)
{
	if (codeNum >= MAX_NUM_CODE) /* the program is too long */
	{
		ErrorHandler (26);
	}

	code[codeNum].fct = fct;
	code[codeNum].opr1 = opr1;
	code[codeNum++].opr2 = opr2;
}