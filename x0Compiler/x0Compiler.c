#include "global.h"

int main ()
{
	//printf ("请输入x0文件名：");
	//scanf ("%s", fileName);		/* 输入文件名 */

	strcpy (fileName, "./testSamples/1.txt");

	if ((fin = fopen (fileName, "r")) == NULL)
	{
		printf ("文件无法打开!\n");
		return 1;
	}

	if (feof(fin))    /* 文件为空 */
	{
		printf ("输入文件为空!\n");
		fclose (fin);
		return 1;
	}
	rewind (fin);
	return 0;
}