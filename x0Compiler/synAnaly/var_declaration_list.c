#include "../global.h"

/*
 * var_declaration_list syntactical analyzer
 */
void var_declaration_list (int* ptr_offset)
{	
	/* execute var_declaration_stat syntactical analyzer if sym belong to first(var_declaration_stat) */
	while (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		var_declaration_stat (ptr_offset);
	}
}