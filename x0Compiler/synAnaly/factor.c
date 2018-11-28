#include "../global.h"

/*
 * factor语法分析程序
 */
void factor ()
{
	int flag = 0; /* flag = 1代表出现过逻辑非 */
	if (sym == notsym)
	{
		flag = 1;
		getSym ();
	}

	if (sym == lparen)
	{
		getSym ();
		expression ();
		if (sym == rparen)
		{
			getSym ();
		}
		else /* 缺少) */
		{
			error (14);
		}
	}
	else if (sym == ident || sym == incsym || sym == decsym) /* sym属于first(variable) */
	{
		/*
		* 通过传地址的方式知道：变量在活动记录中的偏移、该变量是否是数组、该变量是否自增/减
		* (IncOrDec：1后自增、2后自减、3前自增、4前自减、5无增减)
		*/
		int offset;
		int isArray;
		int IncOrDec;
		variable (&offset, &isArray, &IncOrDec);

		/* 加载变量 */
		if (isArray)
		{
			switch (IncOrDec)
			{
				case 1:
					gen (adf, 0, offset);
					gen (lof, 0, offset);
					gen (tad, 0, -1);
					break;
				case 2:
					gen (mif, 0, offset);
					gen (lof, 0, offset);
					gen (tad, 0, 1);
					break;
				case 3:
					gen (adf, 0, offset);
					gen (lof, 0, offset);
					break;
				case 4:
					gen (mif, 0, offset);
					gen (lof, 0, offset);
					break;
				case 5:
					gen (lof, 0, offset);
					break;
			}
		}
		else
		{
			switch (IncOrDec)
			{
				case 1:
					gen (add, 0, offset);
					gen (lod, 0, offset);
					gen (tad, 0, -1);
					break;
				case 2:
					gen (mis, 0, offset);
					gen (lod, 0, offset);
					gen (tad, 0, 1);
					break;
				case 3:
					gen (add, 0, offset);
					gen (lod, 0, offset);
					break;
				case 4:
					gen (mis, 0, offset);
					gen (lod, 0, offset);
					break;
				case 5:
					gen (lod, 0, offset);
					break;
			}
		}
	}
	else if (sym == number)
	{
		gen (lit, 0, num);
		getSym ();
	}
	else /* 缺少(或标识符或数字或!或++或-- */
	{
		error (15);
	}

	/* 如果出现过逻辑非 */
	if (flag)
	{
		gen (opr, 0, 18);
	}
}