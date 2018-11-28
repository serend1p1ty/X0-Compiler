#include "../global.h"

/*
 * read语句语法分析程序
 */
void readStat ()
{
	if (sym == readsym)
	{
		getSym ();
		
		/*
		* 通过传地址的方式知道：变量在活动记录中的偏移、该变量是否是数组、该变量是否自增/减
		* (IncOrDec：1后自增、2后自减、3前自增、4前自减、5无增减)
		*/
		int offset;
		int isArray;
		int IncOrDec;
		variable (&offset, &isArray, &IncOrDec);

		/* read不能读取自增/减变量 */
		if (IncOrDec != 5)
		{
			error (33);
		}

		gen (opr, 0, 14); /* 用scanf读取一个数字 */
		
		/* 根据是单变量还是数组选择不同的存储指令 */
		if (isArray)
		{
			gen (stf, 0, offset);
		}
		else
		{
			gen (sto, 0, offset);
		}

		if (sym == semic)
		{
			getSym ();
		}
		else /* 缺少; */
		{
			error (10);
		}
	}
	else /* 缺少read */
	{
		error (18);
	}
}