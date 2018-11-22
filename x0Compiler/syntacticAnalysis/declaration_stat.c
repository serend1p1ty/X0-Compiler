#include "../global.h"

/*
 * declaration_stat语法分析程序
 */
void declaration_stat ()
{
	/* 
	 * 保存现在的符号类型, 1: char, 0: int 
	 */
	int isChar = (sym == charsym);

	type ();

	if (sym == ident)
	{
		getSym ();
		if (sym == semic)
		{
			/* 声明的是char变量 */	
			if (isChar)
			{
				enum objectKind temp = charVar;
				enter (temp);
			}
			else /* 声明的是int变量 */
			{
				enum objectKind temp = intVar;
				enter (temp);
			}

			getSym ();
		}
		else if (sym == lbracket)
		{
			getSym ();
			if (sym == number)
			{
				getSym ();
				if (sym == rbracket)
				{
					getSym ();
					if (sym == semic)
					{
						/* 声明的是char数组 */
						if (isChar)
						{
							enum objectKind temp = charArray;
							enter (temp);
						}
						else /* 声明的是int数组 */
						{
							enum objectKind temp = intArray;
							enter (temp);
						}
						
						getSym ();
					}
					else /* 缺少; */
					{
						error (10);
					}
				}
				else /* 缺少] */
				{
					error (9);
				}
			}
			else /* 缺少数字 */
			{
				error (8);
			}
		}
		else /* 缺少;或[ */
		{
			error (7);
		}
	}
	else /* 缺少标识符 */
	{
		error (6);
	}
}