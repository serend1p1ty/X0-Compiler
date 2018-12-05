#include "../global.h"

/*
 * varDeclarationList syntactical analyzer
 */
void varDeclarationList (int* ptr_offset)
{	
	/* execute varDeclarationStat syntactical analyzer if sym belong to first(varDeclarationStat) */
	while (sym == charsym || sym == intsym || sym == bolsym || sym == dblsym)
	{
		varDeclarationStat (ptr_offset);
	}
}