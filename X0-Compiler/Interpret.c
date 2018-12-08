#include "global.h"

/*
 * input: data type of plus/subtract/multiply/divide operation's operand
 * output: data type of result
 * Tip: dataType = 1 means INT, 2 means DOUBLE, 3 means CHAR, 4 means BOOL
 */
int ResultType (int dataType1, int dataType2)
{	
	/* result is DOUBLE if either operand1 or operand2 is DOUBLE */
	if (dataType1 == 2 || dataType2 == 2)
	{
		return 2;
	}
	else if (dataType1 == 3 || dataType2 == 3) /* result is CHAR if either operand1 or operand2 is CHAR */
	{
		return 3;
	}
	/* In addition to above, result is INT.
	 * Tip: result of plus/subtract/multiply/divide operation can't be BOOL */
	else
	{
		return 1;
	}
}

/*
 * function: store the j-th element in the j-th position
 */
void store (struct stackObject* s, int i, int j)
{
	/* the types of s[j] and s[j] need to be discussed separately */
	if (s[i].dataType == 2)
	{
		if (s[j].dataType == 2)
		{
			s[i].dblData = s[j].dblData;
		}
		else
		{
			s[i].dblData = s[j].intData;
		}
	}
	else
	{
		if (s[j].dataType == 2)
		{
			s[i].intData = (int)s[j].dblData;
		}
		else
		{
			s[i].intData = s[j].intData;
		}
	}
}

/* 
 * convert to integer from floating number 
 */
int ConvertToInt (double num)
{
	double temp = num > 0 ? 0.5 : -0.5;
	return (int)(num + temp);
}

/* 
 * interpret and execute intermidiate code 
 */
void Interpret ()
{
	int p = 0;						/* pointer of next instruction */
	int b = 1;						/* the base address of current activity record */
	int t = 0;						/* pointer of stack top */
	Instruction inst;				/* current instruction */
	int intTmp;						/* temporary int variable */
	char charTmp;					/* temporary char variable */
	int dimension;					/* the dimension of array */
	int offset;						/* offset relative to the head of array */
	int pos;						/* position of the variable in symbol table */
	int retType;					/* type of function's return value */
	int tableIndex;					/* index of the function' symbol table in symTables */
	int parameterNum;				/* the number of function's parameters */
	StackObject s[MAX_SIZE_STACK];	/* data stack */

	printf ("output of x0 program£º\n");

	/* unused s[0] */
	s[0].dataType = 1;
	s[0].intData = 0;

	/* set static-link, dynamic-link, return-address of main program to 0 */
	s[1].dataType = 1;
	s[1].intData = 0;
	s[2].dataType = 1;
	s[2].intData = 0;
	s[3].dataType = 1;
	s[3].intData = 0;

	do 
	{
		inst = code[p];  /* read current instruction */
		p = p + 1;

		switch (inst.fct)
		{
			case lit:	/* load the constant to top of the stack */
				t = t + 1;
				if (inst.operand1 == 1)
				{
					s[t].dataType = 1;
					s[t].intData = inst.operand2;
				}
				else
				{
					s[t].dataType = 2;
					s[t].dblData = inst.operand3;
				}
				break;
			case opr:	/* mathematical¡¢logical¡¢read/write operation */
				switch (inst.operand1)
				{
					case 0: /* return to the location where current function is called */
						parameterNum = fctInfo[inst.operand2].parameterNum;
						retType = fctInfo[inst.operand2].retType;
						intTmp = t;
						t = b - 1;
						p = s[t + 3].intData;
						b = s[t + 2].intData;
						t = t - parameterNum;
						if (retType != Void)
						{
							t = t + 1;
							s[t] = s[intTmp];
						}
						break;
					case 1: /* arithmetical inversion */
						/* Determine the type of data before using it */
						if (s[t].dataType != 2)
						{
							s[t].intData = -s[t].intData;
						}
						else
						{
							s[t].dblData = -s[t].dblData;
						}
						break;
					case 2: /* plus operation */
						t = t - 1;
						if (s[t].dataType != 2 && s[t + 1].dataType != 2)
						{
							s[t].intData = s[t].intData + s[t + 1].intData;
						}
						else
						{
							s[t].dblData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
								+ (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						}
						s[t].dataType = ResultType (s[t].dataType, s[t + 1].dataType);
						break;
					case 3: /* subtract operation */
						t = t - 1;
						if (s[t].dataType != 2 && s[t + 1].dataType != 2)
						{
							s[t].intData = s[t].intData - s[t + 1].intData;
						}
						else
						{
							s[t].dblData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
								- (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						}
						s[t].dataType = ResultType (s[t].dataType, s[t + 1].dataType);
						break;
					case 4: /* multiply operation */
						t = t - 1;
						if (s[t].dataType != 2 && s[t + 1].dataType != 2)
						{
							s[t].intData = s[t].intData * s[t + 1].intData;
						}
						else
						{
							s[t].dblData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
								* (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						}
						s[t].dataType = ResultType (s[t].dataType, s[t + 1].dataType);
						break;
					case 5: /* divide operation */
						t = t - 1;
						if (s[t].dataType != 2 && s[t + 1].dataType != 2)
						{
							s[t].intData = s[t].intData / s[t + 1].intData;
						}
						else
						{
							s[t].dblData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
								/ (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						}
						s[t].dataType = ResultType (s[t].dataType, s[t + 1].dataType);
						break;
					case 6: /* mod operation */
						t = t - 1;
						/* the operand of mod operation must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							ErrorHandler (40);
						}
						s[t].dataType = 1;
						s[t].intData = s[t].intData % s[t + 1].intData;
						break;
					case 7: /* exit function */
						t = t - 1;
						/* the parameter of exit function must be integer */
						if (s[t + 1].dataType == 2)
						{
							ErrorHandler (41);
						}
						exit (s[t + 1].intData);
						break;
					case 8: /* "==" operation(version 1: remove the top and second-top elements) */
						t = t - 1;
						s[t].dataType = 4;
						s[t].intData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
							== (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						break;
					case 9: /* "!=" operation */
						t = t - 1;
						s[t].dataType = 4;
						s[t].intData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
							!= (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						break;
					case 10: /* "<" operation */
						t = t - 1;
						s[t].dataType = 4;
						s[t].intData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
							< (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						break;
					case 11: /* ">=" operation */
						t = t - 1;
						s[t].dataType = 4;
						s[t].intData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
							>= (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						break;
					case 12: /* ">" operation */
						t = t - 1;
						s[t].dataType = 4;
						s[t].intData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
							> (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						break;
					case 13: /* "<=" operation */
						t = t - 1;
						s[t].dataType = 4;
						s[t].intData = (s[t].dataType != 2 ? s[t].intData : s[t].dblData)
							<= (s[t + 1].dataType != 2 ? s[t + 1].intData : s[t + 1].dblData);
						break;
					case 14: /* read a integer and place it on top of the data stack */
						t = t + 1;
						s[t].dataType = inst.operand2;
						if (inst.operand2 == 1 || inst.operand2 == 4) /* read int/bool */
						{
							scanf ("%d", &(s[t].intData));
						}
						else if (inst.operand2 == 3)
						{
							scanf ("%c", &charTmp);
							getchar (); /* absorb '\n' produced by scanf function */
							s[t].intData = charTmp;
						}
						else /* read floating number */
						{
							scanf ("%lf", &(s[t].dblData));
						}
						break;
					case 15: /* output the element on top of the data stack */
						if (s[t].dataType == 1 || s[t].dataType == 4) /* output integer/bool */
						{
							printf ("%d\n", s[t].intData);
						}
						else if (s[t].dataType == 2) /* output floating number */
						{
							printf ("%f\n", s[t].dblData);
						}
						else if (s[t].dataType == 3) /* output character */
						{
							printf ("%c\n", s[t].intData);
						}
						t = t - 1;
						break;
					case 16: /* "&&" operation */
						t = t - 1;
						/* the operand of && must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							ErrorHandler (42);
						}
						s[t].intData = s[t].intData && s[t + 1].intData;
						s[t].dataType = 4;
						break;
					case 17: /* "||" operation */
						t = t - 1;
						/* the operand of || must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							ErrorHandler (43);
						}
						s[t].intData = s[t].intData || s[t + 1].intData;
						s[t].dataType = 4;
						break;
					case 18: /* "!" operation */
						/* the operand of ! must be integer */
						if (s[t].dataType == 2)
						{
							ErrorHandler (44);
						}
						s[t].intData = !s[t].intData;
						s[t].dataType = 4;
						break;
					case 19: /* "XOR" operation */
						t = t - 1;
						/* the operand of xor must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							ErrorHandler (45);
						}
						s[t].intData = s[t].intData ^ s[t + 1].intData;
						s[t].dataType = 4;
						break;
					case 20: /* "ODD" operation */
						/* the operand of ODD must be integer */
						if (s[t].dataType == 2)
						{
							ErrorHandler (46);
						}
						s[t].intData = s[t].intData % 2;
						s[t].dataType = 4;
						break;
					case 21: /* "==" operation(version 2: remove the top element) */
						s[t].intData = (s[t - 1].dataType != 2 ? s[t - 1].intData : s[t - 1].dblData)
							== (s[t].dataType != 2 ? s[t].intData : s[t].dblData);
						s[t].dataType = 4;
						break;
					default: /* illegal operand of 'opr' instruction */
						ErrorHandler (28);
				}
				break;
			case lod: /* load a variable to the top of stack */
				pos = FindPosition_V2 (inst.operand1, inst.operand2);
				dimension = symTables[inst.operand2][pos].dimension;
				offset = 0;
				for (int i = 0; i < dimension; i++)
				{
					/* the subscript of array must be integer */
					if (s[t + 1 - dimension + i].dataType == 2)
					{
						ErrorHandler (47);
					}
					offset = offset * symTables[inst.operand2][pos].sizeArray[i] + s[t + 1 - dimension + i].intData;
				}
				s[t + 1 - dimension] = s[b + inst.operand1 + offset];
				t = t + 1 - dimension;
				break;
			case sto: /* store the top element in the specific variable */
				pos = FindPosition_V2 (inst.operand1, inst.operand2);
				dimension = symTables[inst.operand2][pos].dimension;
				offset = 0;
				for (int i = 0; i < dimension; i++)
				{
					/* the subscript of array must be integer */
					if (s[t - dimension + i].dataType == 2)
					{
						ErrorHandler (47);
					}
					offset = offset * symTables[inst.operand2][pos].sizeArray[i] + s[t - dimension + i].intData;
				}
				store (s, b + inst.operand1 + offset, t);
				s[t - dimension] = s[t];
				t = t - dimension;
				break;
			case add: /* add inst.operand2 to the value of a variable */
				tableIndex = ConvertToInt (inst.operand3);
				pos = FindPosition_V2 (inst.operand1, tableIndex);
				dimension = symTables[tableIndex][pos].dimension;
				offset = 0;
				for (int i = 0; i < dimension; i++)
				{
					/* the subscript of array must be integer */
					if (s[t + 1 - dimension + i].dataType == 2)
					{
						ErrorHandler (47);
					}
					offset = offset * symTables[tableIndex][pos].sizeArray[i] + s[t + 1 - dimension + i].intData;
				}
				s[b + inst.operand1 + offset].intData += inst.operand2;
				break;
			case tad: /* add inst.operand1 to the value of top element */
				/* top element isn't integer, 'tad' instruction can't work */
				if (s[t].dataType == 2)
				{
					ErrorHandler (54);
				}
				s[t].intData += inst.operand1;
				break;
			case cal: /* call function */
				s[t + 1].dataType = 1;
				s[t + 1].intData = 0;
				s[t + 2].dataType = 1;
				s[t + 2].intData = b;
				s[t + 3].dataType = 1;
				s[t + 3].intData = p;
				b = t + 1;
				p = inst.operand1;
				break;
			case ini: /* initialize a space in the stack for current activity record */
				t = b + 2;
				parameterNum = fctInfo[inst.operand1].parameterNum;
				tableIndex = fctInfo[inst.operand1].posSymTables;
				/* initialize the type of local variables */
				for (int i = 0; i < iterators[tableIndex]; i++)
				{
					struct tableObject to = symTables[tableIndex][i];
					int totalSize = 1;
					for (int j = 0; j < to.dimension; j++)
					{
						totalSize *= to.sizeArray[j];
					}
					for (int j = 1; j <= totalSize; j++)
					{
						switch (to.kind)
						{
							case intVar:
								s[++t].dataType = 1;
								break;
							case intArray:
								s[++t].dataType = 1;
								break;
							case constIntVar:
								s[++t].dataType = 1;
								s[t].intData = ConvertToInt(to.value);
								break;
							case doubleVar:
								s[++t].dataType = 2;
								break;
							case doubleArray:
								s[++t].dataType = 2;
								break;
							case constDoubleVar:
								s[++t].dataType = 2;
								s[t].dblData = to.value;
								break;
							case charVar:
								s[++t].dataType = 3;
								break;
							case charArray:
								s[++t].dataType = 3;
								break;
							case constCharVar:
								s[++t].dataType = 3;
								s[t].intData = ConvertToInt (to.value);
								break;
							case boolVar:
								s[++t].dataType = 4;
								break;
							case boolArray:
								s[++t].dataType = 4;
								break;
							case constBoolVar:
								s[++t].dataType = 4;
								s[t].intData = ConvertToInt (to.value);
								break;
							default: /* ErrorHandler type of symbol-table object */
								ErrorHandler (49);
						}
					}
				}
				for (int j = 0; j < parameterNum; j++)
				{
					store (s, b + 3 + j, b - parameterNum + j);
				}
				break;
			case jmp: /* unconditionaly jump */
				p = inst.operand1;
				break;
			case jpc: /* conditionaly jump */
				if (s[t].intData == 0)
				{
					p = inst.operand1;
				}
				t = t - 1;
				break;
			default: /* illegal function code */
				ErrorHandler (29);
		}
	} while (p != 0);
}