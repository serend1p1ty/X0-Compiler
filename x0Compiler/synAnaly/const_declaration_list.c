#include "../global.h"

/*
 * const_declaration_list syntactical analyzer
 */
void const_declaration_list (int* ptr_offset)
{
	/* execute const_declaration_stat syntactical analyzer if sym belong to first(const_declaration_stat) */
	while (sym == cstsym)
	{
		const_declaration_stat (ptr_offset);
	}
}