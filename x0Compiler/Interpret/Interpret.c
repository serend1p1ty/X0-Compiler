#include "../global.h"

/*
 * input: data type of plus/subtract/multiply/divide operation's operand
 * output: data type of result
 * tip: dataType = 1 denotes INT, 2 denotes DOUBLE, 3 denotes CHAR, 4 denotes BOOL
 */
int calculateType (int dataType1, int dataType2)
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
	else /* in addition to above, result is INT (tip: result of plus/subtract/multiply/divide operation can't be BOOL) */
	{
		return 1;
	}
}

/*
 * input: s  data stack, i/j  two positions
 * function: store the j-th element in the i-th position 
 */
void store (struct stackObject* s, int i, int j)
{
	/* the types of s[i] and s[j] need to be discussed separately */
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

/* interpret and execute intermidiate code */
void Interpret ()
{
	int p = 0; /* pointer of next instruction */
	int b = 1; /* the base address of current activity record */
	int t = 0; /* pointer of stack top */
	struct instruction i; /* current instruction */
	struct stackObject s[MAX_SIZE_STACK]; /* data stack */
	int intTmp;   /* temporary int variable used in the next part */
	char charTmp; /* temporary char variable used in the next part */

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
		i = code[p];  /* read current instruction */
		p = p + 1;

		switch (i.fct)
		{
			case lit:	/* place the constant on top of the stack */
				t = t + 1;
				if (i.operand1 == 1)
				{
					s[t].dataType = 1;
					s[t].intData = i.operand2;
				}
				else
				{
					s[t].dataType = 2;
					s[t].dblData = i.operand3;
				}
				break;
			case opr:	/* mathematical¡¢logical¡¢read/write operation */
				switch (i.operand1)
				{
					case 0: /* return to the location where current function is called */
						t = b - 1;
						p = s[t + 3].intData;
						b = s[t + 2].intData;
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
						s[t].dataType = calculateType (s[t].dataType, s[t + 1].dataType);
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
						s[t].dataType = calculateType (s[t].dataType, s[t + 1].dataType);
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
						s[t].dataType = calculateType (s[t].dataType, s[t + 1].dataType);
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
						s[t].dataType = calculateType (s[t].dataType, s[t + 1].dataType);
						break;
					case 6: /* mod operation */
						t = t - 1;
						/* the operand of mod operation must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							error (40);
						}
						s[t].dataType = 1;
						s[t].intData = s[t].intData % s[t + 1].intData;
						break;
					case 7: /* exit function */
						t = t - 1;
						/* the parameter of exit function must be integer */
						if (s[t + 1].dataType == 2)
						{
							error (41);
						}
						exit (s[t + 1].intData);
						break;
					case 8: /* "==" operation(version 1: delete the top and second-top elements) */
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
						s[t].dataType = i.operand2;
						if (i.operand2 == 1 || i.operand2 == 4) /* read int/bool */
						{
							scanf ("%d", &(s[t].intData));
						}
						else if (i.operand2 == 3)
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
							error (42);
						}
						s[t].intData = s[t].intData && s[t + 1].intData;
						s[t].dataType = 4;
						break;
					case 17: /* "||" operation */
						t = t - 1;
						/* the operand of || must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							error (43);
						}
						s[t].intData = s[t].intData || s[t + 1].intData;
						s[t].dataType = 4;
						break;
					case 18: /* "!" operation */
						/* the operand of ! must be integer */
						if (s[t].dataType == 2)
						{
							error (44);
						}
						s[t].intData = !s[t].intData;
						s[t].dataType = 4;
						break;
					case 19: /* "XOR" operation */
						t = t - 1;
						/* the operand of xor must be integer */
						if (s[t].dataType == 2 || s[t + 1].dataType == 2)
						{
							error (45);
						}
						s[t].intData = s[t].intData ^ s[t + 1].intData;
						s[t].dataType = 4;
						break;
					case 20: /* "ODD" operation */
						/* the operand of ODD must be integer */
						if (s[t].dataType == 2)
						{
							error (46);
						}
						s[t].intData = s[t].intData % 2;
						s[t].dataType = 4;
						break;
					case 21: /* "==" operation(version 2: delete the top element) */
						s[t].intData = (s[t - 1].dataType != 2 ? s[t - 1].intData : s[t - 1].dblData)
							== (s[t].dataType != 2 ? s[t].intData : s[t].dblData);
						s[t].dataType = 4;
						break;
					default: /* illegal operand of 'opr' instruction */
						error (28);
				}
				break;
			case lod: /* set a variable on top of stack */
				t = t + 1;
				s[t] = s[1 + i.operand1];
				break;
			case lod2: /* set a 1-dimension array element on top of stack */
				/* the subscript of array must be integer */
				if (s[t].dataType == 2)
				{
					error (47);
				}
				s[t] = s[1 + i.operand1 + s[t].intData];
				break;
			case lod3: /* set a 2-dimension array element on top of stack */
				/* the subscript of array must be integer */
				if (s[t].dataType == 2)
				{
					error (47);
				}
				s[t - 1] = s[1 + i.operand1 + s[t - 1].intData * i.operand2 + s[t].intData];
				t = t - 1;
				break;
			case sto: /* store the top element in a variable */
				store (s, 1 + i.operand1, t);
				t = t - 1;
				break;
			case sto2: /* store the top element in a 1-dimension array element */ 
				/* the subscript of array must be integer */
				if (s[t - 1].dataType == 2)
				{
					error (47);
				}
				store (s, 1 + i.operand1 + s[t - 1].intData, t);
				t = t - 2;
				break;
			case sto3: /* store the top element in a 2-dimension array element */
				/* the subscript of array must be integer */
				if (s[t - 1].dataType == 2)
				{
					error (47);
				}
				store (s, 1 + i.operand1 + s[t - 2].intData * i.operand2 + s[t - 1].intData, t);
				t = t - 3;
				break;
			case add: /* add one to the value of a variable */
				s[1 + i.operand1].intData += i.operand2;
				break;
			case add2: /* add one to the value of a 1-dimension array element */
				/* the subscript of array must be integer */
				if (s[t].dataType == 2)
				{
					error (47);
				}
				s[1 + i.operand1 + s[t].intData].intData += i.operand2;
				break;
			case add3: /* add one to the value of a 2-dimension array element */
				/* the subscript of array must be integer */
				if (s[t].dataType == 2)
				{
					error (47);
				}
				double temp = i.operand3 > 0 ? 0.5 : -0.5;
				s[1 + i.operand1 + s[t - 1].intData * i.operand2 + s[t].intData].intData += (int)(i.operand3 + temp);
				break;
			case tad: /* add i.operand1 to the value of top element */
				s[t].intData += i.operand1;
				break;
			case cal: /* call function */
				break;
			case ini: /* initialize a space in the stack for current activity record */
				intTmp = 4;
				/* initialize the type of local variables */
				for (int i = 0; i < iterTable; i++)
				{
					struct tableObject to = table[i];
					double temp = to.value > 0 ? 0.5 : -0.5;

					for (int j = 1; j <= to.size1 * to.size2; j++)
					{
						switch (to.kind)
						{
							case intVar:
								s[intTmp++].dataType = 1;
								break;
							case intArray:
								s[intTmp++].dataType = 1;
								break;
							case constIntVar:
								s[intTmp].dataType = 1;
								s[intTmp++].intData = (int)(to.value + temp);
								break;
							case doubleVar:
								s[intTmp++].dataType = 2;
								break;
							case doubleArray:
								s[intTmp++].dataType = 2;
								break;
							case constDoubleVar:
								s[intTmp].dataType = 2;
								s[intTmp++].dblData = to.value;
								break;
							case charVar:
								s[intTmp++].dataType = 3;
								break;
							case charArray:
								s[intTmp++].dataType = 3;
								break;
							case constCharVar:
								s[intTmp].dataType = 3;
								s[intTmp++].intData = (int)(to.value + temp);
								break;
							case boolVar:
								s[intTmp++].dataType = 4;
								break;
							case boolArray:
								s[intTmp++].dataType = 4;
								break;
							case constBoolVar:
								s[intTmp].dataType = 4;
								s[intTmp++].intData = (int)(to.value + temp);
								break;
							default: /* error type of symbol-table object */
								error (49);
						}
					}
				}
				t = t + i.operand1;
				break;
			case jmp: /* unconditionaly jump */
				p = i.operand1;
				break;
			case jpc: /* conditionaly jump */
				if (s[t].intData == 0)
				{
					p = i.operand1;
				}
				t = t - 1;
				break;
			default: /* illegal function code */
				error (29);
		}
	} while (p != 0);
}