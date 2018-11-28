#include "../global.h"

/*
 * declaration_list语法分析程序
 */
void declarationList (int* ptr_offset)
{	
	/* 如果sym属于first(declarationStat)，就执行declarationStat分析程序 */
	while (sym == charsym || sym == intsym)
	{
		declarationStat (ptr_offset);
	}
}