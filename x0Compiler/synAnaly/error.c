#include "../global.h"

void error (int error_code)
{
	char space[81];
	memset (space, 32, sizeof(space));

	/* 出错时当前终结符已经读完, ch为当前终结符的下一个字符, posCh指着当前终结符的下下一个字符 */
	space[posCh - 2] = '\0';

	printf ("%s^", space); /* 标记错误位置 */

	switch (error_code)
	{
		case 1:
			printf ("输入文件一行的字符太多\n");
			break;
		case 2:
			printf ("标识符长度太长\n");
			break;
		case 3:
			printf ("数字位数太多\n");
			break;
		case 4:
			printf ("缺少}\n");
			break;
		case 5:
			printf ("缺少{\n");
			break;
		case 6:
			printf ("缺少标识符\n");
			break;
		case 7:
			printf ("缺少;或[\n");
			break;
		case 8:
			printf ("缺少数字\n");
			break;
		case 9:
			printf ("缺少]\n");
			break;
		case 10:
			printf ("缺少;\n");
			break;
		case 11:
			printf ("缺少=\n");
			break;
		case 12:
			printf ("缺少#或标识符或(或数字或-或++或--或odd或!或true或false\n");
			break;
		case 13:
			printf ("缺少#或标识符或(或数字或-或++或--或odd或!或;或true或false\n");
			break;
		case 14:
			printf ("缺少)\n");
			break;
		case 15:
			printf ("缺少(或标识符或数字或!或++或--或true或false\n");
			break;
		case 16:
			printf ("缺少(\n");
			break;
		case 17:
			printf ("缺少if\n");
			break;
		case 18:
			printf ("缺少read\n");
			break;
		case 19:
			printf ("缺少if或while或read或write或{或for或#或标识符或(或数字或-或++或--或odd或!或;或true或false\n");
			break;
		case 20:
			printf ("缺少char或int或bool\n");
			break;
		case 21:
			printf ("缺少while\n");
			break;
		case 22:
			printf ("缺少write\n");
			break;
		case 23:
			printf ("缺少main\n");
			break;
		case 24:
			printf ("标识符未声明\n");
			break;
		case 25:
			printf ("标识符不是int或char变量\n");
			break;
		case 26:
			printf ("标识符不是int或char数组\n");
			break;
		case 27:
			printf ("程序太长!\n");
			break;
		case 28:
			printf ("不合法的opr操作数!\n");
			break;
		case 29:
			printf ("不合法的指令码!\n");
			break;
		case 30:
			printf ("不合法的运算符!\n");
			break;
		case 31:
			printf ("缺少for\n");
			break;
		case 32:
			printf ("赋值语句左边不能是自增或者自减变量\n");
			break;
		case 33:
			printf ("read不能读取自增/减变量\n");
			break;
		case 34:
			printf ("缺少break\n");
			break;
		case 35:
			printf ("缺少break\n");
			break;
		case 36:
			printf ("缺少continue\n");
			break;
		case 37:
			printf ("缺少switch\n");
			break;
		case 38:
			printf ("缺少:\n");
			break;
		case 39:
			printf ("缺少do\n");
			break;
		default:
			printf ("不存在的错误码!\n");
	}
	printf ("\ntip: ^所指即出错位置\n");
	exit (0);
}