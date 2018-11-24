#include "global.h"

/* 
 * 编译器主程序
 */
void compile ()
{
	gen (jmp, 0, 1);
	getSym ();

	if (sym == mainsym)
	{
		getSym ();

		if (sym == lbrace)
		{
			getSym ();

			int offset = 3;	/* 局部变量相对于活动记录开始位置的偏移 */
			declaration_list (&offset);

			gen (ini, 0, offset); /* 声明结束的时候就知道了需要预留多少空间 */

			statement_list ();

			if (sym == rbrace)
			{
				gen (opr, 0, 0); /* 返回调用过程 */

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

	compile ();	/* 检查语法是否正确，并编译成中间代码 */

	FILE* fout = fopen ("./testSamples/output.txt", "w");
	
	for (int i = 0; i < iterCode; i++)
	{
		fprintf (fout, "[%d] %s %d %d\n", i, fctCode_string[code[i].fct], code[i].lev_dif, code[i].offset);
	}

	fclose (fout);

	Interpret (); /* 解释执行生成的中间代码 */

	return 0;
}