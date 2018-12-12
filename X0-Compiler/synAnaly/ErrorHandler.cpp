#include "../global.h"

/* error handler */
void ErrorHandler (int error_code)
{
	char space[81];
	memset (space, 32, sizeof(space));

	/* mark the position of error */
	if (posCh - 2 >= 0)
	{
		space[posCh - 2] = '\0';
	}
	else
	{
		space[0] = '\0';
	}

	printf ("%s^", space);

	switch (error_code)
	{
		case 1:
			printf ("too many character in one line of input file !\n");
			break;
		case 2:
			printf ("the name of the identifier is too long !\n");
			break;
		case 3:
			printf ("the number is too large !\n");
			break;
		case 4:
			printf ("the lack of '}' !\n");
			break;
		case 5:
			printf ("the lack of '{' !\n");
			break;
		case 6:
			printf ("the lack of identifier !\n");
			break;
		case 7:
			printf ("the lack of number can be assigned !\n");
			break;
		case 8:
			printf ("the lack of integer !\n");
			break;
		case 9:
			printf ("the lack of ']' !\n");
			break;
		case 10:
			printf ("the lack of ';' !\n");
			break;
		case 11:
			printf ("the lack of '=' !\n");
			break;
		case 14:
			printf ("the lack of ')' !\n");
			break;
		case 15:
			printf ("syntax error of 'factor' !\n");
			break;
		case 16:
			printf ("the lack of '(' !\n");
			break;
		case 17:
			printf ("the lack of 'if' !\n");
			break;
		case 18:
			printf ("the lack of 'read' !\n");
			break;
		case 19:
			printf ("illegal data type !\n");
			break;
		case 20:
			printf ("the lack of 'while' !\n");
			break;
		case 21:
			printf ("the lack of 'write' !\n");
			break;
		case 22:
			printf ("the lack of 'main' !\n");
			break;
		case 23:
			printf ("the identifier hasn't been declared !\n");
			break;
		case 24:
			printf ("identifier isn't {const} variable !\n");
			break;
		case 25:
			printf ("identifier isn't array !\n");
			break;
		case 26:
			printf ("the program is too long !\n");
			break;
		case 27:
			printf ("illegal operand of 'opr' instruction !\n");
			break;
		case 28:
			printf ("illegal function code !\n");
			break;
		case 30:
			printf ("the lack of 'for' !\n");
			break;
		case 31:
			printf ("constant can't be modified !\n");
			break;
		case 32:
			printf ("'read' function can't read Increasing or decreasing variable !\n");
			break;
		case 33:
			printf ("the lack of 'break' !\n");
			break;
		case 34:
			printf ("the lack of 'exit' !\n");
			break;
		case 35:
			printf ("the lack of 'continue' !\n");
			break;
		case 36:
			printf ("the lack of 'switch' !\n");
			break;
		case 37:
			printf ("the lack of ':' !\n");
			break;
		case 38:
			printf ("the lack of 'do' !\n");
			break;
		case 39:
			printf ("the operand of mod operation must be integer !\n");
			break;
		case 40:
			printf ("the parameter of exit function must be integer !\n");
			break;
		case 41:
			printf ("the operand of && must be integer !\n");
			break;
		case 42:
			printf ("the operand of || must be integer !\n");
			break;
		case 43:
			printf ("the operand of ! must be integer !\n");
			break;
		case 44:
			printf ("the operand of xor must be integer !\n");
			break;
		case 45:
			printf ("the operand of odd must be integer !\n");
			break;
		case 46:
			printf ("the subscript of array must be integer !\n");
			break;
		case 47:
			printf ("illegal number !\n");
			break;
		case 48:
			printf ("error type of symbol-table object !\n");
			break;
		case 49:
			printf ("Increasing or decreasing variable must be INT or CHAR !\n");
			break;
		case 50:
			printf ("array subscript is out of bound !\n");
			break;
		case 51:
			printf ("the lack of 'const' !\n");
			break;
		case 52:
			printf ("constant can't be read !\n");
			break;
		case 53:
			printf ("top element isn't integer, 'tad' instruction can't work !\n");
			break;
		case 54:
			printf ("illegal return type of function !\n");
			break;
		case 55:
			printf ("the function hasn't been declared !\n");
			break;
		default:
			printf ("illegal ErrorHandler code !\n");
	}
	exit (0);
}