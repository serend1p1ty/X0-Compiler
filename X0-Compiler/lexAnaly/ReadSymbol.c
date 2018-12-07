#include "../global.h"

/*
 * read a character from input file
 */
void ReadCh ()
{
	if (posCh == chNum)	/* cache is empty. read a new line into the cache. */
	{
		/* initialization */
		chNum = 0;
		posCh = 0;

		/* pay attention to the operation of 'feof' function */
		char temp = fgetc(inputFile);

		while (!feof (inputFile))
		{
			if (chNum >= MAX_SIZE_LINE)	/* too many character in one line of input file */
			{
				ErrorHandler (1);
			}

			printf ("%c", temp);
			lineCache[chNum++] = temp;

			if (temp == '\n')
			{
				break;
			}

			temp = fgetc (inputFile);
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
void ReadSymbol ()
{
	int i, j, k;

	while (ch == ' ' || ch == '\n' || ch == 9)	/* filter out ' ', '\n' and tab */
	{
		ReadCh ();
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
				ErrorHandler (2);
			}

			ReadCh ();
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
						ErrorHandler (3);
					}
				}
				else
				{
					decimal += weight * (ch - '0');
					weight *= 0.1;
				}

				ReadCh ();
				
				if (ch == '.' && !flagDecPoint)
				{
					ReadCh ();
					flagDecPoint = 1;
					
					if (ch < '0' || ch > '9') /* illegal number */
					{
						ErrorHandler (48);
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
				ReadCh ();

				if (ch == '=')
				{
					sym = eqleql;
					ReadCh ();
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
					ReadCh ();

					if (ch == '=')
					{
						sym = lesseql;
						ReadCh ();
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
						ReadCh ();

						if (ch == '=')
						{
							sym = greateql;
							ReadCh ();
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
							ReadCh ();

							if (ch == '&')
							{
								sym = andsym;
								ReadCh ();
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
								ReadCh ();

								if (ch == '|')
								{
									sym = orsym;
									ReadCh ();
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
									ReadCh ();

									if (ch == '+')
									{
										sym = incsym;
										ReadCh ();
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
										ReadCh ();

										if (ch == '-')
										{
											sym = decsym;
											ReadCh ();
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
											ReadCh ();

											if (ch == '=')
											{
												sym = neql;
												ReadCh ();
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
											ReadCh ();
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