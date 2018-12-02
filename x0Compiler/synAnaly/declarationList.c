#include "../global.h"

/*
 * declaration_list syntactical analyzer
 */
void declarationList (int* ptr_offset)
{	
	/* execute declarationStat syntactical analyzer if sym belong to first(declarationStat) */
	while (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		declarationStat (ptr_offset);
	}
}