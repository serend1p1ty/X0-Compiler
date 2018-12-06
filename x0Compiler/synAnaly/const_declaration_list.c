#include "../global.h"

/*
 * constDeclarationList syntactical analyzer
 */
void constDeclarationList (int* ptr_offset)
{
	/* execute constDeclarationStat syntactical analyzer if sym belong to first(constDeclarationStat) */
	while (sym == cstsym)
	{
		constDeclarationStat (ptr_offset);
	}
}