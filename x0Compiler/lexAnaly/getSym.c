#include "../global.h"

/*
 * read a character from input file
 */
void getCh ()
{
	if (posCh == chNum)	/* cache is empty. read a new line into the cache. */
	{
		/* initialization */
		chNum = 0;
		posCh = 0;

		/* pay attention to the operation of 'feof' function */
		char temp = fgetc(fin);

		while (!feof (fin))
		{
			if (chNum >= MAX_SIZE_LINE)	/* too many character in one line of input file */
			{
				error (1);
			}

			printf ("%c", temp);
			lineCache[chNum++] = temp;

			if (temp == '\n')
			{
				break;
			}

			temp = fgetc (fin);
		}
	}
	if (posCh != chNum)
	{
		ch = lineCache[posCh++];
	}
}

/*
 * lexical analyzer£ºread a terminal symbol
 */
void getSym ()
{
	int i, j, k;

	while (ch == ' ' || ch == '\n' || ch == 9)	/* filter out ' ', '\n' and tab */
	{
		getCh ();
	}

	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))	/* identifier or reserved word */
	{
		char temp[MAX_SIZE_IDENT + 1];	/* 'temp' saves the name of identifier/reserved word */
		
		k = 0;		
		do 
		{
			if (k < MAX_SIZE_IDENT)
			{
				temp[k++] = ch;
			}
			else /* the identifier is too long */
			{
				error (2);
			}

			getCh ();
		} while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'));	
		temp[k] = 0;

		strcpy (id, temp);	/* store the name of identifier/reserved word in 'id' */
		
		/* check whether current word is a reserved word with binary-search */
		i = 0;
		j = RESERVE_WORD_NUM - 1;
		do
		{
			k = (i + j) / 2;

			if (strcmp (id, reserveWord[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp (id, reserveWord[k]) >= 0)
			{
				i = k + 1;
			}
		} while (i <= j);
		sym = (i - 1) > j ? wsym[k] : ident;
	}
	else
	{
		if (ch >= '0' && ch <= '9')	/* number */
		{
			k = 0;
			intNum = 0;
			int flagDecPoint = 0; /* 1: denotes decimal point has appeared */
			double decimal = 0;   /* decimal part of floatNumber */
			double weight = 0.1;  /* weight of decimal part */

			/* read number */
			do 
			{
				if (!flagDecPoint)
				{
					intNum = 10 * intNum + ch - '0';
					k++;

					if (k > MAX_SIZE_NUMBER) /* the number is too large */
					{
						error (3);
					}
				}
				else
				{
					decimal += weight * (ch - '0');
					weight *= 0.1;
				}

				getCh ();
				
				if (ch == '.' && !flagDecPoint)
				{
					getCh ();
					flagDecPoint = 1;
					
					if (ch < '0' || ch > '9') /* illegal number */
					{
						error (48);
					}
				}
			} while (ch >= '0' && ch <= '9');

			if (flagDecPoint) /* current sym is floatnumber */
			{
				doubleNum = intNum + decimal;
			}

			sym = flagDecPoint ? doublenum : intnum;
		}
		else
		{
			if (ch == '=') /* detect '=' or '==' */
			{
				getCh ();

				if (ch == '=')
				{
					sym = eqleql;
					getCh ();
				}
				else
				{
					sym = eql;
				}
			}
			else
			{
				if (ch == '<')	/* detect '<' or '<=' */
				{
					getCh ();

					if (ch == '=')
					{
						sym = lesseql;
						getCh ();
					}
					else
					{
						sym = less;
					}
				}
				else
				{
					if (ch == '>')	/* detect '>' or '>=' */
					{
						getCh ();

						if (ch == '=')
						{
							sym = greateql;
							getCh ();
						}
						else
						{
							sym = great;
						}
					}
					else
					{
						if (ch == '&')	/* detect '&&' */
						{
							getCh ();

							if (ch == '&')
							{
								sym = andsym;
								getCh ();
							}
							else
							{
								sym = nul; /* unrecognized symbol */
							}
						}
						else
						{
							if (ch == '|')	/* detect '||' */
							{
								getCh ();

								if (ch == '|')
								{
									sym = orsym;
									getCh ();
								}
								else
								{
									sym = nul; /* unrecognized symbol */
								}
							}
							else
							{
								if (ch == '+')	/* detect '++' */
								{
									getCh ();

									if (ch == '+')
									{
										sym = incsym;
										getCh ();
									}
									else
									{
										sym = plus;
									}
								}
								else
								{
									if (ch == '-')	/* detect '--' */
									{
										getCh ();

										if (ch == '-')
										{
											sym = decsym;
											getCh ();
										}
										else
										{
											sym = minus;
										}
									}
									else
									{
										if (ch == '!')	/* detect '!=' or '!' */
										{
											getCh ();

											if (ch == '=')
											{
												sym = neql;
												getCh ();
											}
											else
											{
												sym = notsym;
											}
										}
										else
										{
											sym = ssym[ch];	/* symbol will be handled as single character
															 * if it can't satisfy conditions above */
											getCh ();
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}