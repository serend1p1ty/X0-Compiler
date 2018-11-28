#include "global.h"

struct instruction code[MAX_SIZE_CODE];   // 中间代码
int iterCode = 0;                         // 中间代码的迭代器
struct tableObject table[MAX_SIZE_TABLE]; // 符号表
int iterTable = 0;                        // 符号表的迭代器
char fileName[MAX_SIZE_FILENAME + 1];     // 文件名
FILE* fin;                                // 输入文件
enum symbol sym;                          // getSym读取出的终结符
char ch = ' ';                            // getCh读取出的字符
int posCh;								  // getCh使用的计数器, 表示当前字符的位置
int chNum;								  // getCh使用的计数器, 表示当前行缓冲区有多少字符
char lineCache[MAX_SIZE_LINE];            // getCh使用的行缓冲区
int num;                                  // 当前数字
char id[MAX_SIZE_IDENT + 1];              // 当前标识符

// 保留字
char* reserveWord[RESERVE_WORD_NUM] = { "char", "else", "for",
										"if", "int", "main",
										"odd", "read", "while",
										"write", "xor" };
// 保留字对应的符号值
enum symbol wsym[RESERVE_WORD_NUM] = { charsym, elsesym, forsym,
									   ifsym, intsym, mainsym,
									   oddsym, readsym, whilesym,
									   writesym, xorsym };
// 单字符的符号值
enum symbol ssym[256] = { ['+'] = plus,['-'] = minus,['*'] = times,
						 ['/'] = slash,['('] = lparen,[')'] = rparen,
						 ['['] = lbracket,[']'] = rbracket,['{'] = lbrace,
						 ['}'] = rbrace,[';'] = semic,['#'] = hashsym,['%'] = modsym };
// 指令码对应的指令字符串
char* fctCode_string[FCTCODE_NUM] = {"lit", "opr", "lod", "sto", "cal", "ini", 
									 "jmp", "jpc", "stf", "lof", "add", "adf",
									 "mis", "mif", "tad"};