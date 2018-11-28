#include "../global.h"

/*
 * 从输入文件中读取一个字符
 */
void getCh ()
{
	if (posCh == chNum)	/* 判断缓冲区中是否有字符，若无字符，则读入下一行字符(包括换行符)到缓冲区中 */
	{
		/* 初始化计数器 */
		chNum = 0;
		posCh = 0;

		/* 此处要注意feof的操作 */
		char temp = fgetc(fin);
		while (!feof (fin))
		{
			if (chNum >= MAX_SIZE_LINE)	/* 输入文件一行的字符太多 */
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
 * 词法分析程序：一次读取一个终结符
 */
void getSym ()
{
	int i, j, k;

	while (ch == ' ' || ch == '\n' || ch == 9)	/* 过滤空格、换行和制表符 */
	{
		getCh ();
	}

	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))	/* 当前的单词是标识符或是保留字 */
	{
		char temp[MAX_SIZE_IDENT + 1];	/* temp保存着读取的标识符/保留字的名字 */
		k = 0;
		do 
		{
			if (k < MAX_SIZE_IDENT)
			{
				temp[k++] = ch;
			}
			else /* 标识符长度太长 */
			{
				error (2);
			}
			getCh ();
		} while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'));
		temp[k] = 0;

		strcpy (id, temp);	/* 将标识符/保留字的名字拷贝到id里面 */
		
		/* 搜索当前单词是否为保留字，使用二分法查找 */
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

		if (i - 1 > j)	/* 当前的单词是保留字 */
		{
			sym = wsym[k];
		}
		else  /* 当前的单词是标识符 */
		{
			sym = ident;
		}
	}
	else
	{
		if (ch >= '0' && ch <= '9')	/* 当前的单词是数字 */
		{
			k = 0;
			num = 0;
			sym = number;

			/* 获取数字的值 */
			do 
			{
				num = 10 * num + ch - '0';
				k++;
				if (k > MAX_SIZE_NUMBER)	/* 数字位数太多 */
				{
					error (3);
				}
				getCh ();
			} while (ch >= '0' && ch <= '9');
		}
		else
		{
			if (ch == '=')		/* 检测=或==符号 */
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
				if (ch == '<')	/* 检测小于或小于等于符号 */
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
					if (ch == '>')	/* 检测大于或大于等于符号 */
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
						if (ch == '&')	/* 检测逻辑与符号 */
						{
							getCh ();
							if (ch == '&')
							{
								sym = andsym;
								getCh ();
							}
							else
							{
								sym = nul; /* 不能识别的符号 */
							}
						}
						else
						{
							if (ch == '|')	/* 检测逻辑或符号 */
							{
								getCh ();
								if (ch == '|')
								{
									sym = orsym;
									getCh ();
								}
								else
								{
									sym = nul; /* 不能识别的符号 */
								}
							}
							else
							{
								if (ch == '+')	/* 检测自增符号 */
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
									if (ch == '-')	/* 检测自减符号 */
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
										if (ch == '!')	/* 检测不等于或逻辑非符号 */
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
											sym = ssym[ch];	/* 当符号不满足上述条件时，全部按照单字符符号处理 */
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