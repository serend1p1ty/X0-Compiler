#include "global.h"

char fileName[MAX_SIZE_FILENAME + 1];     /* file name */

/* 
 * variables used in lexical analysis 
 */
BackUp backups[MAX_SIZE_BACKUP];		  /* backups of lexical analysing's status */
int iterBackUp = 0;                       /* iterator of backups */
FILE* inputFile;                          /* input file */
enum symbol sym;                          /* current terminal symbol read by ReadSymbol() */
char ch = ' ';                            /* current character read by ReadCh() */
int posCh;								  /* counter using by ReadCh() */
char lineCache[MAX_SIZE_LINE];            /* line cache using by ReadCh() */
int chNum;								  /* counter using by line cache */
double doubleNum;                         /* current floating number */
int intNum;                               /* current integer */
char id[MAX_SIZE_IDENT + 1];              /* current identifier */

/* reserved word */
char* reserveWord[RESERVE_WORD_NUM] = { "bool", "break", "case", "char", "const", "continue", 
									    "default", "do", "double", "else", "exit", "false", 
										"for", "if", "int", "main", "odd", "read", 
										"repeat", "switch", "true", "until", "void", "while", 
										"write", "xor" };

/* symbol-value corresponding to reserved word */
enum symbol wsym[RESERVE_WORD_NUM] = { bolsym, brksym, cassym, charsym, cstsym, ctnsym, 
									   defausym, dosym, dblsym, elsesym, exitsym, falsesym, 
									   forsym, ifsym, intsym, mainsym, oddsym, readsym, 
									   reptsym, swtcsym, truesym, untlsym, voidsym, whilesym, 
									   writesym, xorsym };

/* symbol-value of single character */
enum symbol ssym[256] = { ['+'] = plus, ['-'] = minus, ['*'] = times,
						  ['/'] = slash, ['('] = lparen, [')'] = rparen,
						  ['['] = lbracket, [']'] = rbracket, ['{'] = lbrace,
						  ['}'] = rbrace, [';'] = semic, ['%'] = modsym, 
						  [':'] = colonsym, [','] = comma };

/* 
 * variables used in syntactical analysis 
 */
int continueList[MAX_SIZE_CONTINUE];					  /* continue statement to be backfilled */
int iterCtnList = 0;									  /* the iterator of continueList */
int breakList[MAX_SIZE_BREAK];							  /* break statement to be backfilled */
int iterBreakList = 0;									  /* the iterator of breakList */
Instruction code[MAX_SIZE_CODE];						  /* intermediate code */
int iterCode = 0;										  /* position of next intermediate code */
TableObject symTables[MAX_NUM_FUNCTION][MAX_SIZE_TABLE];  /* symbol tables */
int iterators[MAX_NUM_FUNCTION] = { 0 };				  /* iterator of each symbol table */
int tableNum = -1;										  /* number of tables */
FunctionInfo fctInfo[MAX_NUM_FUNCTION];					  /* information of each function */
int iterFctInfo = -1;									  /* iterator of fctInfo */

/* strings corresponding to function code */
char* fctCodeString[FCTCODE_NUM] = { "lit", "opr", "lod", "sto", "cal", 
									 "ini", "jmp", "jpc", "add", "tad" };