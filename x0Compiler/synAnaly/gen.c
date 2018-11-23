#include "../global.h"

/*
* 生成中间代码
*
* fct: 函数码
* lev_dif: 引用层与声明层的层次差
* offset: 如果是lod指令，offset为相对于活动记录开始位置的偏移, 如果是cal指令，offset为被调用函数在中间代码中的开始位置
*/
void gen (enum fctCode fct, int lev_dif, int offset)
{
	if (iterCode >= MAX_SIZE_CODE) /* 生成的虚拟机代码程序过长 */
	{
		error (27);
	}

	code[iterCode].fct = fct;
	code[iterCode].lev_dif = lev_dif;
	code[iterCode++].offset = offset;
}