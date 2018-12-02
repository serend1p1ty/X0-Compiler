#include "../global.h"

/*
* input:
* fct: function code
* lev_dif: the level difference between reference-level and declare-level
* offset: if 'lod' instruction is generated, 'offset' is the offset relative to the base address of current activity record.
*         if 'cal' instruction is generated, 'offset' is the position where called function starts in the intermidiate code.
* function: generate an intermidiate code.
*/
void gen (enum fctCode fct, int lev_dif, double offset)
{
	if (iterCode >= MAX_SIZE_CODE) /* the program is too long */
	{
		error (27);
	}

	code[iterCode].fct = fct;
	code[iterCode].lev_dif = lev_dif;
	code[iterCode++].offset = offset;
}