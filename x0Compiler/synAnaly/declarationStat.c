#include "../global.h"

/*
 * declarationStat语法分析程序
 */
void declarationStat (int* ptr_offset)
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
				enter (charVar, *ptr_offset, 1);
				*ptr_offset = *ptr_offset + 1;
			}
			else /* 声明的是int变量 */
			{
				enter (intVar, *ptr_offset, 1);
				*ptr_offset = *ptr_offset + 1;
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
							enter (charArray, *ptr_offset, num);
							*ptr_offset = *ptr_offset + num;
						}
						else /* 声明的是int数组 */
						{
							enter (intArray, *ptr_offset, num);
							*ptr_offset = *ptr_offset + num;
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