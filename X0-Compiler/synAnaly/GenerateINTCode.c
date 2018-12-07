#include "../global.h"

/*
 * function: generate an intermidiate code.
 */
void GenerateINTCode (FctCode fct, int operand1, int operand2, double operand3)
{
	if (iterCode >= MAX_SIZE_CODE) /* the program is too long */
	{
		ErrorHandler (27);
	}

	code[iterCode].fct = fct;
	code[iterCode].operand1 = operand1;
	code[iterCode].operand2 = operand2;
	code[iterCode++].operand3 = operand3;
}