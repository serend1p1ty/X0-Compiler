#include "../global.h"

/*
 * type语法分析程序
 */
void type ()
{
	if (sym != charsym && sym != intsym && sym != bolsym) /* 缺少char或int或bool */
	{
		error (20);
	}
	getSym ();
}