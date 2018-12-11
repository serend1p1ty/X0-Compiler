#include "../global.h"

/*
 * type syntactical analyzer
 */
DataType type ()
{
	switch (sym)
	{
		case intsym:
			ReadSymbol ();
			return Int;
		case dblsym:
			ReadSymbol ();
			return Double;
		case charsym:
			ReadSymbol ();
			return Char;
		case bolsym:
			ReadSymbol ();
			return Bool;
		default: /* illegal data type */
			ErrorHandler (19);
	}
	return Int;
}