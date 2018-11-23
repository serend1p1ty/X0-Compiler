#include "../global.h"

/*
 * declaration_list语法分析程序
 */
void declaration_list (int* ptr_offset)
{	
	/* 如果sym属于first(declaration_stat)，就执行declaration_stat分析程序 */
	while (sym == charsym || sym == intsym)
	{
		declaration_stat (ptr_offset);
	}
}