#include "global.h"
#include "stackobj.h"

/* 
 * convert to integer from floating number 
 */
int ConvertToInt (double num)
{
	double temp = num > 0 ? 0.5 : -0.5;
	return (int)(num + temp);
}

/* 
 * interpreting and executing intermidiate code
 */
void Interpret ()
{
	int p = 0;						/* pointer of next instruction */
	int b = 1;						/* the base address of current activity record */
	int t = 0;						/* pointer of stack top */
	Instruction inst;				/* current instruction */
	StackObject s[MAX_SIZE_STACK];	/* data stack */

	int intTmp;						/* temporary int variable */
	int d;							/* the dimension of the array */
	int offset;						/* offset relative to the head of array */
	int pos;						/* position of the variable in symbol table */
	int retType;					/* type of function's return value */
	int paraNum;				    /* the number of function's parameters */
	int fctIndex;                   /* index of the function in fctInfo */

	printf ("output of x0 program£º\n");

	/* set static-link, dynamic-link, return-address of main program to 0 */
	s[1].dataType = Int;
	s[1].intData = 0;
	s[2].dataType = Int;
	s[2].intData = 0;
	s[3].dataType = Int;
	s[3].intData = 0;

	do 
	{
		inst = code[p];  /* read current instruction */
		p = p + 1;

		switch (inst.fct)
		{
			case lit:	/* load the constant to top of the stack */
				t = t + 1;
				if (!inst.opr2)
				{
					s[t].dataType = Int;
					s[t].intData = inst.opr1;
				}
				else
				{
					s[t].dataType = Double;
					s[t].dblData = inst.opr2;
				}
				break;
			case opr:	/* mathematical¡¢logical¡¢read/write operation */
				switch (inst.opr1)
				{
					case 0: /* return to the location where current function is called */
						fctIndex = ConvertToInt (inst.opr2);
						paraNum = fctInfo[fctIndex].paraNum;
						retType = fctInfo[fctIndex].retType;
						intTmp = t;
						t = b - 1;
						p = s[t + 3].intData;
						b = s[t + 2].intData;
						t = t - paraNum;
						if (retType != retVoid)
						{
							s[++t] = s[intTmp];
						}
						break;
					case 1: /* arithmetical inversion */
						s[t] = -s[t];
						break;
					case 2: /* plus operation */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3: /* subtract operation */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4: /* multiply operation */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5: /* divide operation */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6: /* mod operation */
						t = t - 1;
						s[t] = s[t] % s[t + 1];
						break;
					case 7: /* exit function */
						t = t - 1;
						/* the parameter of exit function must be integer */
						if (s[t + 1].dataType == Double)
						{
							ErrorHandler (40);
						}
						exit (s[t + 1].intData);
						break;
					case 8: /* "==" operation(version 1: remove the top and second-top elements) */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9: /* "!=" operation */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10: /* "<" operation */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11: /* ">=" operation */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12: /* ">" operation */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* "<=" operation */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14: /* input */
						s[++t].dataType = (DataType)ConvertToInt(inst.opr2);
						if (s[t].dataType == Int || s[t].dataType == Bool)
						{
							scanf ("%d", &(s[t].intData));
						}
						else if (s[t].dataType == Char)
						{
							s[t].intData = getchar();
						}
						else
						{
							scanf ("%lf", &(s[t].dblData));
						}
						break;
					case 15: /* output */
						if (s[t].dataType == Int || s[t].dataType == Bool)
						{
							printf ("%d\n", s[t].intData);
						}
						else if (s[t].dataType == Double)
						{
							printf ("%f\n", s[t].dblData);
						}
						else if (s[t].dataType == Char)
						{
							printf ("%c\n", s[t].intData);
						}
						t = t - 1;
						break;
					case 16: /* "&&" operation */
						t = t - 1;
						s[t] = s[t] && s[t + 1];
						break;
					case 17: /* "||" operation */
						t = t - 1;
						s[t] = s[t] || s[t + 1];
						break;
					case 18: /* "!" operation */
						s[t] = !s[t];
						break;
					case 19: /* "xor" operation */
						t = t - 1;
						s[t] = s[t] ^ s[t + 1];
						break;
					case 20: /* "odd" operation */
						/* the operand of odd must be integer */
						if (s[t].dataType == Double)
						{
							ErrorHandler (45);
						}
						s[t].intData = s[t].intData % 2;
						s[t].dataType = Bool;
						break;
					case 21: /* "==" operation(version 2: remove the top element) */
						s[t] = (s[t - 1] == s[t]);
						break;
					default: /* illegal operand of 'opr' instruction */
						ErrorHandler (27);
				}
				break;
			case lod: /* load a variable to the top of stack */
				fctIndex = ConvertToInt (inst.opr2);
				pos = FindPosition (inst.opr1, fctIndex);
				d = fctInfo[fctIndex].symTable[pos].d;
				offset = 0;
				for (int i = 0; i < d; i++)
				{
					/* the subscript of array must be integer */
					if (s[t + 1 - d + i].dataType == 2)
					{
						ErrorHandler (46);
					}
					offset = offset * fctInfo[fctIndex].symTable[pos].size[i] + s[t + 1 - d + i].intData;
				}
				s[t + 1 - d] = s[b + inst.opr1 + offset];
				t = t + 1 - d;
				break;
			case sto: /* store the top element in the specific variable */
				fctIndex = ConvertToInt (inst.opr2);
				pos = FindPosition (inst.opr1, fctIndex);
				d = fctInfo[fctIndex].symTable[pos].d;
				offset = 0;
				for (int i = 0; i < d; i++)
				{
					/* the subscript of array must be integer */
					if (s[t - d + i].dataType == 2)
					{
						ErrorHandler (46);
					}
					offset = offset * fctInfo[fctIndex].symTable[pos].size[i] + s[t - d + i].intData;
				}
				s[b + inst.opr1 + offset].assign(s[t]);
				s[t - d] = s[t]; /* remove the subscript of the array, but reserve the top element */
				t = t - d;
				break;
			case add: /* add one to the value of a variable */
				fctIndex = ConvertToInt (inst.opr2);
				pos = FindPosition (inst.opr1, fctIndex);
				d = fctInfo[fctIndex].symTable[pos].d;
				offset = 0;
				for (int i = 0; i < d; i++)
				{
					/* the subscript of array must be integer */
					if (s[t + 1 - d + i].dataType == 2)
					{
						ErrorHandler (46);
					}
					offset = offset * fctInfo[fctIndex].symTable[pos].size[i] + s[t + 1 - d + i].intData;
				}
				s[b + inst.opr1 + offset].intData += 1;
				break;
			case sub: /* subtract one from the value of a variable */
				fctIndex = ConvertToInt (inst.opr2);
				pos = FindPosition (inst.opr1, fctIndex);
				d = fctInfo[fctIndex].symTable[pos].d;
				offset = 0;
				for (int i = 0; i < d; i++)
				{
					/* the subscript of array must be integer */
					if (s[t + 1 - d + i].dataType == 2)
					{
						ErrorHandler (46);
					}
					offset = offset * fctInfo[fctIndex].symTable[pos].size[i] + s[t + 1 - d + i].intData;
				}
				s[b + inst.opr1 + offset].intData -= 1;
				break;
			case tad: /* add inst.opr1 to the value of top element */
				/* top element isn't integer, 'tad' instruction can't work */
				if (s[t].dataType == 2)
				{
					ErrorHandler (53);
				}
				s[t].intData += inst.opr1;
				break;
			case cal: /* call function */
				s[t + 1].dataType = Int;
				s[t + 1].intData = 0;
				s[t + 2].dataType = Int;
				s[t + 2].intData = b;
				s[t + 3].dataType = Int;
				s[t + 3].intData = p;
				b = t + 1;
				p = inst.opr1;
				break;
			case ini: /* initialize a space in the stack for current activity record */
				t = b + 2;
				paraNum = fctInfo[inst.opr1].paraNum;
				/* initialize the type of local variables */
				for (int i = 0; i < fctInfo[inst.opr1].tableSize; i++)
				{
					struct tableObject to = fctInfo[inst.opr1].symTable[i];
					int totalSize = 1;
					for (int j = 0; j < to.d; j++)
					{
						totalSize *= to.size[j];
					}
					for (int j = 1; j <= totalSize; j++)
					{
						switch (to.kind)
						{
							case intVar:
							case intArray:
								s[++t].dataType = Int;
								break;
							case constIntVar:
								s[++t].dataType = Int;
								s[t].intData = ConvertToInt(to.value);
								break;
							case doubleVar:
							case doubleArray:
								s[++t].dataType = Double;
								break;
							case constDoubleVar:
								s[++t].dataType = Double;
								s[t].dblData = to.value;
								break;
							case charVar:
							case charArray:
								s[++t].dataType = Char;
								break;
							case constCharVar:
								s[++t].dataType = Char;
								s[t].intData = ConvertToInt (to.value);
								break;
							case boolVar:
							case boolArray:
								s[++t].dataType = Bool;
								break;
							case constBoolVar:
								s[++t].dataType = Bool;
								s[t].intData = ConvertToInt (to.value);
								break;
							default: /* error type of symbol-table object */
								ErrorHandler (48);
						}
					}
				}
				/* load the parameters of the function */
				for (int j = 0; j < paraNum; j++)
				{
					s[b + 3 + j].assign(s[b - paraNum + j]);
				}
				break;
			case jmp: /* unconditionaly jump */
				p = inst.opr1;
				break;
			case jpc: /* conditionaly jump */
				if (!s[t].intData)
				{
					p = inst.opr1;
				}
				t = t - 1;
				break;
			default: /* illegal function code */
				ErrorHandler (28);
		}
	} while (p != 0);
}