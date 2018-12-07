#include "../global.h"

/*
 * statement syntactical analyzer
 */
void statement ()
{
	if (sym == ifsym) /* if statement */
	{
		if_stat ();
	}
	else if (sym == whilesym) /* while statement */
	{
		while_stat ();
	}
	else if (sym == readsym) /* read statement */
	{
		read_stat ();
	}
	else if (sym == writesym) /* write statement */
	{
		write_stat ();
	}
	else if (sym == lbrace)	/* compound statement */
	{
		compound_stat ();
	}
	else if (sym == semic || sym == doublenum
		|| sym == lparen || sym == intnum || sym == minus
		|| sym == incsym || sym == decsym || sym == oddsym
		|| sym == notsym || sym == truesym || sym == falsesym)	/* expression statement */
	{
		expression_stat ();
	}
	else if (sym == ident)
	{
		int pos = find_position_v1 (id, tableNum);
		if (pos == -1)
		{
			FunctionStat ();
		}
		else
		{
			expression_stat ();
		}
	}
	else if (sym == forsym) /* for statement */
	{
		for_stat ();
	}
	else if (sym == brksym) /* break statement */
	{
		break_stat ();
	}
	else if (sym == exitsym) /* exit statement */
	{
		exit_stat ();
	}
	else if (sym == ctnsym) /* continue statement */
	{
		continue_stat ();
	}
	else if (sym == swtcsym) /* switch statement */
	{
		switch_stat ();
	}
	else if (sym == dosym) /* do-while statement */
	{
		dowhile_stat ();
	}
	else if (sym == reptsym) /* repeat-until statement */
	{
		repeat_stat ();
	}
	else /* sym isn't belong to first(statement) */
	{
		error (19);
	}
}