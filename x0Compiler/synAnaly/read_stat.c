#include "../global.h"

/*
 * read语句语法分析程序
 */
void read_stat ()
{
	if (sym == readsym)
	{
		getSym ();
		
		int offset;
		int isArray;
		var (&offset, &isArray); /* 通过传地址的方式知道：变量在活动记录中的偏移、该变量是否是数组 */

		gen (opr, 0, 14); /* 用scanf读取一个数字 */
		
		/* 根据是单变量还是数组选择不同的store方式 */
		if (isArray)
		{
			gen (stof, 0, offset);
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