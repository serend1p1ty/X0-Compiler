#include "../global.h"

/*
 * type语法分析程序
 */
void type ()
{
	if (sym != charsym && sym != intsym) /* 缺少char或int */
	{
		error (20);
	}
	getSym ();
}