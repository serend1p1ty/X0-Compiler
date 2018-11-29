#include "../global.h"

/* 解释程序 */
void Interpret ()
{
	int p = 0; /* 指令指针 */
	int b = 1; /* 指令基址 */
	int t = 0; /* 栈顶指针 */
	struct instruction i;	/* 存放当前指令 */
	int s[MAX_SIZE_STACK];	/* 栈 */

	printf ("程序输出：\n");

	s[0] = 0; /* s[0]不用 */
	s[1] = 0; /* 主程序的SL, DL, RA均置为0 */
	s[2] = 0;
	s[3] = 0;

	do 
	{
		i = code[p];  /* 读当前指令 */
		p = p + 1;
		switch (i.fct)
		{
			case lit:	/* 将常量a的值取到栈顶 */
				t = t + 1;
				s[t] = i.offset;
				break;
			case opr:	/* 数学、逻辑、读入、输出运算 */
				switch (i.offset)
				{
					case 0:  /* 函数调用结束后返回 */
						t = b - 1;
						p = s[t + 3];
						b = s[t + 2];
						break;
					case 1: /* 栈顶元素取反 */
						s[t] = -s[t];
						break;
					case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3: /* 次栈顶项减去栈顶项 */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4: /* 次栈顶项乘以栈顶项 */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5: /* 次栈顶项除以栈顶项 */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6: /* 取模 */
						t = t - 1;
						s[t] = s[t] % s[t + 1];
						break;
					case 7: /* exit */
						t = t - 1;
						exit (s[t + 1]);
						break;
					case 8: /* 判断次栈顶项与栈顶项是否相等(删除次栈顶项和栈顶项) */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9: /* 判断次栈顶项与栈顶项是否不等 */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10: /* 判断次栈顶项是否小于栈顶项 */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11: /* 判断次栈顶项是否大于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12: /* 判断次栈顶项是否大于栈顶项 */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* 判断次栈顶项是否小于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14: /* 读入一个数字到栈顶 */
						t = t + 1;
						scanf ("%d", &(s[t]));
						break;
					case 15: /* 将栈顶元素输出 */
						printf ("%d\n", s[t]);
						t = t - 1;
						break;
					case 16: /* 逻辑与 */
						t = t - 1;
						s[t] = s[t] && s[t + 1];
						break;
					case 17: /* 逻辑或 */
						t = t - 1;
						s[t] = s[t] || s[t + 1];
						break;
					case 18: /* 逻辑非 */
						s[t] = !s[t];
						break;
					case 19: /* 异或 */
						t = t - 1;
						s[t] = s[t] ^ s[t + 1];
						break;
					case 20: /* 判断栈顶元素是否为奇数 */
						s[t] = s[t] % 2;
						break;
					case 21: /* 判断次栈顶项与栈顶项是否相等(删除栈顶项) */
						s[t] = (s[t] == s[t - 1]);
						break;
					default: /* 不合法的opr操作数 */
						error (28);
				}
				break;
			case lod:	/* 取相对于当前活动记录基地址偏移量为offset的变量值到栈顶 */
				t = t + 1;
				s[t] = s[1 + i.offset];
				break;
			case lof:	/* 取数组值到栈顶，数组基地址为当前活动记录基地址+offset，数组内部偏移量为s[t] */
				s[t] = s[1 + i.offset + s[t]];
				break;
			case sto:	/* 栈顶的值存到相对于当前活动记录基地址偏移量为offset的变量 */
				s[1 + i.offset] = s[t];
				t = t - 1;
				break;
			case stf:	/* 栈顶的值存到数组元素里，数组基地址为当前活动记录基地址+offset，数组内部偏移量为s[t - 1] */
				s[1 + i.offset + s[t - 1]] = s[t];
				t = t - 2;
				break;
			case add:	/* 将相对于当前活动记录基地址偏移量为offset的变量的值加上1 */
				s[1 + i.offset] += 1;
				break;
			case adf:	/* 将数组元素(数组基地址为当前活动记录基地址+offset，数组内部偏移量为s[t]的那个元素)的值加上1 */
				s[1 + i.offset + s[t]] += 1;
				break;
			case mis:	/* 将相对于当前活动记录基地址偏移量为offset的变量的值减去1 */
				s[1 + i.offset] -= 1;
				break;
			case mif:	/* 将数组元素(数组基地址为当前活动记录基地址+offset，数组内部偏移量为s[t]的那个元素)的值减去1 */
				s[1 + i.offset + s[t]] -= 1;
				break;
			case tad:	/* 栈顶元素加上offset */
				s[t] += i.offset;
				break;
			case cal:	/* 调用子过程 */
				break;
			case ini:	/* 在数据栈中为被调用的过程开辟offset个单元的数据区 */
				t = t + i.offset;
				break;
			case jmp:	/* 直接跳转 */
				p = i.offset;
				break;
			case jpc:	/* 条件跳转 */
				if (s[t] == 0)
				{
					p = i.offset;
				}
				t = t - 1;
				break;
			default:
				error (29);
		}
	} while (p != 0);
}