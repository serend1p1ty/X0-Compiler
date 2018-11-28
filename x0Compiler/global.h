#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 100        // 文件名最大长度
#define MAX_SIZE_IDENT    20         // 标识符最大长度
#define MAX_SIZE_NUMBER   9          // 数字最大位数
#define MAX_SIZE_LINE     100		 // 输入文件一行最大的字符数
#define MAX_SIZE_TABLE    100        // 符号表的最大大小
#define MAX_SIZE_CODE     1000       // 中间代码的最大数目
#define MAX_SIZE_STACK    10000      // 数据栈最大长度
#define FCTCODE_NUM       15         // 指令码的数目
#define TERMINAL_SYM_NUM  39         // 终结符数目
#define RESERVE_WORD_NUM  11         // 保留字数目

// 终结符
enum symbol
{
	nul, ident, mainsym, charsym, intsym, ifsym,
	elsesym, whilesym, readsym, writesym, plus, minus,
	times, slash, lparen, rparen, lbracket, rbracket, 
	lbrace, rbrace, semic, eql, great, less,
	greateql, lesseql, eqleql, neql, number, hashsym,
	andsym, orsym, forsym, modsym, oddsym, xorsym,
	incsym, decsym, notsym
};

// 符号表存储的对象的种类
enum objectKind
{
	charVar, intVar, charArray, intArray
};

// 符号表存储的对象
struct tableObject
{
	char name[MAX_SIZE_IDENT + 1];
	enum objectKind kind;
	int offset;	/* 相对于当前活动记录开始地址的偏移 */
	int size;	/* 需要分配的空间大小 */
};

// 指令码
enum fctCode
{
	lit, opr, lod,
	sto, cal, ini,
	jmp, jpc, stf,
	lof, add, adf,
	mis, mif, tad
};

// 中间代码
struct instruction
{
	enum fctCode fct;	/* 指令码 */
	int lev_dif;		/* 引用层与声明层的层次差 */
	int offset;			/* 如果是lod指令，offset为相对于活动记录开始位置的偏移,
						   如果是cal指令，offset为被调用函数在中间代码中的开始位置 */
};

extern char* fctCode_string[FCTCODE_NUM];        // 指令码对应的指令字符串
extern struct instruction code[MAX_SIZE_CODE];   // 中间代码
extern int iterCode;                             // 中间代码的迭代器
extern struct tableObject table[MAX_SIZE_TABLE]; // 符号表
extern int iterTable;                            // 符号表的迭代器
extern char fileName[MAX_SIZE_FILENAME + 1];     // 文件名
extern FILE* fin;                                // 输入文件
extern enum symbol sym;                          // getSym读取出的终结符
extern char ch;                                  // getCh读取出的字符
extern int posCh;								 // getCh使用的计数器, 表示当前字符在行缓冲区中的位置
extern char lineCache[MAX_SIZE_LINE];            // getCh使用的行缓冲区
extern int chNum;								 // 行缓冲区使用的计数器, 表示当前行缓冲区有多少字符
extern int num;                                  // 当前数字
extern char id[MAX_SIZE_IDENT + 1];              // 当前标识符
extern char* reserveWord[RESERVE_WORD_NUM];      // 保留字
extern enum symbol wsym[RESERVE_WORD_NUM];       // 保留字对应的符号值
extern enum symbol ssym[256];                    // 单字符的符号值

/* 词法分析程序 */
void getSym ();

/* 
 * 语法分析程序
 * ps: 如果语法没问题，语法分析程序开始的时候sym应为当前模块的第一个符号，
 * 程序结束的时候sym应为当前模块结束后的下一个符号
 */
void declarationList (int* ptr_offset);
void declarationStat (int* ptr_offset);
void statementList ();
void statement ();
void type ();
void ifStat ();
void whileStat ();
void readStat ();
void writeStat ();
void compoundStat ();
void expressionStat ();
void variable (int* ptr_offset, int* ptr_isArray, int* ptr_IncOrDec);
void simpleVariable (int* ptr_offset, int* ptr_isArray);
void expression ();
void simpleValue ();
void term ();
void factor ();
void additiveExpr ();
void forStat ();
void valueExpr ();
void enter (enum objectKind k, int offset, int size);				/* 在符号表中加入一项 */
int findPosition (char* identName);									/* 在符号表中查找并返回identName的位置 */
void error (int error_code);										/* 错误分析子程序,编译出现问题时调用 */
void gen (enum fctCode fct, int lev_dif, int offset);               /* 生成中间代码 */

/* 解释程序 */
void Interpret();