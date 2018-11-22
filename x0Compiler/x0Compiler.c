#include "global.h"

/* 
 * 编译器主程序
 */
void compile ()
{
	getSym ();
	if (sym == mainsym)
	{
		getSym ();
		if (sym == lbrace)
		{
			getSym ();
			declaration_list ();
			statement_list ();
			if (sym == rbrace)
			{
				printf ("\n***************\n");
				printf ("语法正确!\n");
				printf ("***************\n");
			}
			else /* 缺少} */
			{
				error (4);
			}
		}
		else /* 缺少{ */
		{
			error (5);
		}
	}
	else /* 缺少main */
	{
		error (23);
	}
}

int main ()
{
	//printf ("请输入x0文件名：");
	//scanf ("%s", fileName);

	strcpy (fileName, "./testSamples/test_synAnaly.txt");

	if ((fin = fopen (fileName, "r")) == NULL) /* 文件无法打开 */
	{
		printf ("文件无法打开!\n");
		return 1;
	}

	if (feof(fin))	/* 文件为空 */
	{
		printf ("输入文件为空!\n");
		fclose (fin);
		return 1;
	}
	rewind (fin);

	compile ();	/* 编译 */

	return 0;
}