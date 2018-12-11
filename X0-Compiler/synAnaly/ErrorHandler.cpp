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

	FILE* fout = fopen ("../../ShareFolder/Output.txt", "w");
	fprintf (fout, "%s^", space);

	switch (error_code)
	{
		case 1:
			fprintf (fout, "too many character in one line of input file !\n");
			break;
		case 2:
			fprintf (fout, "the name of the identifier is too long !\n");
			break;
		case 3:
			fprintf (fout, "the number is too large !\n");
			break;
		case 4:
			fprintf (fout, "the lack of '}' !\n");
			break;
		case 5:
			fprintf (fout, "the lack of '{' !\n");
			break;
		case 6:
			fprintf (fout, "the lack of identifier !\n");
			break;
		case 7:
			fprintf (fout, "the lack of number can be assigned !\n");
			break;
		case 8:
			fprintf (fout, "the lack of integer !\n");
			break;
		case 9:
			fprintf (fout, "the lack of ']' !\n");
			break;
		case 10:
			fprintf (fout, "the lack of ';' !\n");
			break;
		case 11:
			fprintf (fout, "the lack of '=' !\n");
			break;
		case 14:
			fprintf (fout, "the lack of ')' !\n");
			break;
		case 15:
			fprintf (fout, "syntax error of 'factor' !\n");
			break;
		case 16:
			fprintf (fout, "the lack of '(' !\n");
			break;
		case 17:
			fprintf (fout, "the lack of 'if' !\n");
			break;
		case 18:
			fprintf (fout, "the lack of 'read' !\n");
			break;
		case 19:
			fprintf (fout, "illegal data type !\n");
			break;
		case 20:
			fprintf (fout, "the lack of 'while' !\n");
			break;
		case 21:
			fprintf (fout, "the lack of 'write' !\n");
			break;
		case 22:
			fprintf (fout, "the lack of 'main' !\n");
			break;
		case 23:
			fprintf (fout, "the identifier hasn't been declared !\n");
			break;
		case 24:
			fprintf (fout, "identifier isn't {const} variable !\n");
			break;
		case 25:
			fprintf (fout, "identifier isn't array !\n");
			break;
		case 26:
			fprintf (fout, "the program is too long !\n");
			break;
		case 27:
			fprintf (fout, "illegal operand of 'opr' instruction !\n");
			break;
		case 28:
			fprintf (fout, "illegal function code !\n");
			break;
		case 30:
			fprintf (fout, "the lack of 'for' !\n");
			break;
		case 31:
			fprintf (fout, "constant can't be modified !\n");
			break;
		case 32:
			fprintf (fout, "'read' function can't read Increasing or decreasing variable !\n");
			break;
		case 33:
			fprintf (fout, "the lack of 'break' !\n");
			break;
		case 34:
			fprintf (fout, "the lack of 'exit' !\n");
			break;
		case 35:
			fprintf (fout, "the lack of 'continue' !\n");
			break;
		case 36:
			fprintf (fout, "the lack of 'switch' !\n");
			break;
		case 37:
			fprintf (fout, "the lack of ':' !\n");
			break;
		case 38:
			fprintf (fout, "the lack of 'do' !\n");
			break;
		case 39:
			fprintf (fout, "the operand of mod operation must be integer !\n");
			break;
		case 40:
			fprintf (fout, "the parameter of exit function must be integer !\n");
			break;
		case 41:
			fprintf (fout, "the operand of && must be integer !\n");
			break;
		case 42:
			fprintf (fout, "the operand of || must be integer !\n");
			break;
		case 43:
			fprintf (fout, "the operand of ! must be integer !\n");
			break;
		case 44:
			fprintf (fout, "the operand of xor must be integer !\n");
			break;
		case 45:
			fprintf (fout, "the operand of odd must be integer !\n");
			break;
		case 46:
			fprintf (fout, "the subscript of array must be integer !\n");
			break;
		case 47:
			fprintf (fout, "illegal number !\n");
			break;
		case 48:
			fprintf (fout, "error type of symbol-table object !\n");
			break;
		case 49:
			fprintf (fout, "Increasing or decreasing variable must be INT or CHAR !\n");
			break;
		case 50:
			fprintf (fout, "array subscript is out of bound !\n");
			break;
		case 51:
			fprintf (fout, "the lack of 'const' !\n");
			break;
		case 52:
			fprintf (fout, "constant can't be read !\n");
			break;
		case 53:
			fprintf (fout, "top element isn't integer, 'tad' instruction can't work !\n");
			break;
		case 54:
			fprintf (fout, "illegal return type of function !\n");
			break;
		case 55:
			fprintf (fout, "the function hasn't been declared !\n");
			break;
		default:
			fprintf (fout, "illegal ErrorHandler code !\n");
	}
	fprintf (fout, "\ntip: '^' point to the position where error occurs.\n");
	fclose (fout);
	exit (0);
}