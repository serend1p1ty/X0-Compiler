#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 100        /* max length of file name */
#define MAX_SIZE_IDENT    20         /* max length of identifier */
#define MAX_SIZE_NUMBER   9          /* max digits of number */
#define MAX_SIZE_LINE     100		 /* max number of a line's character in input file */
#define MAX_SIZE_TABLE    100        /* max size of symbol table */
#define MAX_SIZE_CODE     1000       /* max number of intermidiate code */
#define MAX_SIZE_STACK    10000      /* max size of data stack */
#define MAX_SIZE_BREAK    1000       /* max number of 'break' statement */
#define MAX_SIZE_CONTINUE 1000       /* max number of 'continue' statement */
#define MAX_SIZE_BACKUP   100        /* max number of backups */
#define MAX_DIMENSION     10         /* max dimension of array */
#define MAX_NUM_FUNCTION  100        /* max number of functions */
#define FCTCODE_NUM       16         /* number of function code */
#define TERMINAL_SYM_NUM  56         /* number of terminal symbol */
#define RESERVE_WORD_NUM  26         /* number of reserved word */

/* terminal symbol */
enum symbol
{
	nul, ident, mainsym, charsym, intsym, ifsym,
	elsesym, whilesym, readsym, writesym, plus, minus,
	times, slash, lparen, rparen, lbracket, rbracket, 
	lbrace, rbrace, semic, eql, great, less,
	greateql, lesseql, eqleql, neql, intnum, dblsym,
	andsym, orsym, forsym, modsym, oddsym, xorsym,
	incsym, decsym, notsym, brksym, ctnsym, exitsym,
	swtcsym, cassym, colonsym, defausym, dosym, reptsym,
	untlsym, bolsym, truesym, falsesym, doublenum, cstsym,
	comma, voidsym
};

/* the kind of object stored in the symbol table */
enum objectKind
{
	intVar, constIntVar, intArray,
	doubleVar, constDoubleVar, doubleArray,
	charVar, constCharVar, charArray,
	boolVar, constBoolVar, boolArray
};

/* object stored in the symbol table */
struct tableObject
{
	char name[MAX_SIZE_IDENT + 1];	/* name of the identifier */
	enum objectKind kind;			/* kind of the identifier */
	int offset;						/* offset relative to current activity record */
	int size[MAX_DIMENSION];		/* size of each dimension */
	int dimension;					/* the dimension of array */
	double value;					/* only used by constant */
};

/* function code */
enum fctCode
{
	lit, opr, lod, sto, cal, ini, jmp, jpc, add, tad
};

/* intermidiate code */
struct instruction
{
	enum fctCode fct; /* function code */
	int operand1;
	int operand2;
	double operand3;
};

/* object stored in data stack */
struct stackObject
{
	int dataType; /* data-type, 1: int, 2: double, 3: char, 4: bool */
	int intData;
	double dblData;
};

struct functionInfo
{
	char name[MAX_SIZE_IDENT];
	int parameterNum;
	int startINTCode;
	int posSymTables;
};

/* backup object */
struct BackUp
{
	FILE* backupFin;                          /* backup the fin */
	enum symbol backupSym;                    /* backup the sym */
	char backupCh;                            /* backup the ch */
	int backupPosCh;                          /* backup the posCh */
	char backupLineCache[MAX_SIZE_LINE];      /* backup the lineCache */
	int backupChNum;                          /* backup the chNum */
	double backupDoubleNum;                   /* backup the doubleNum */
	int backupIntNum;                         /* backup the intNum */
	char backupId[MAX_SIZE_IDENT + 1];        /* backup the id */
	int backupIterCode;                       /* in addition to above, iterCode also need to be backuped */
};

extern char fileName[MAX_SIZE_FILENAME + 1];     /* file name */

/* 
 * variables used in lexical analysis
 */
extern struct BackUp backups[MAX_SIZE_BACKUP];   /* backups of lexical analysing's status */
extern int iterBackUp;                           /* iterator of backups */
extern FILE* fin;                                /* input file */
extern enum symbol sym;                          /* current terminal symbol read by readSymbol() */
extern char ch;                                  /* current character read by getCh() */
extern int posCh;								 /* counter using by getCh() */
extern char lineCache[MAX_SIZE_LINE];            /* line cache using by getCh() */
extern int chNum;								 /* counter using by line cache */
extern double doubleNum;                         /* current floating number */
extern int intNum;                               /* current number */
extern char id[MAX_SIZE_IDENT + 1];              /* current identifier */
extern char* reserveWord[RESERVE_WORD_NUM];      /* reserved word */
extern enum symbol ssym[256];                    /* symbol-value of single character */
extern enum symbol wsym[RESERVE_WORD_NUM];       /* symbol-value corresponding to reserved word */

/* 
 * variables used in syntactical analysis
 */
extern int continueList[MAX_SIZE_CONTINUE];      /* continue statement to be backfilled */
extern int iterCtnList;                          /* the iterator of continueList */
extern int breakList[MAX_SIZE_BREAK];            /* break statement to be backfilled */
extern int iterBreakList;                        /* the iterator of breakList */
extern char* fctCode_string[FCTCODE_NUM];        /* strings corresponding to function code */
extern struct instruction code[MAX_SIZE_CODE];   /* intermidiate code */
extern int iterCode;                             /* the iterator of code */
extern int expressionNum;                        /* store the value of 'expression' in 'expressionNum' 
												  * if 'expression' is a number */
extern struct tableObject functionTable[MAX_NUM_FUNCTION][MAX_SIZE_TABLE];  /* symbol tables */
extern int iterators[MAX_NUM_FUNCTION];          /* iterator of each symbol table */
extern int tableNum;        
extern struct functionInfo fctInfo[MAX_NUM_FUNCTION];
extern int iterFctInfo;

/* 
 * lexical analyzer 
 */
void readSymbol ();
void backup ();  /* backup the status of lexical analysing */
void recover (); /* recover the status of lexical analysing from backups */

/* 
 * syntactical analyzer
 * tip: if no error occurs, sym should be the first symbol when a syntactical analyzer starts, and
 * sym should be the following symbol at the end of analysing.
 */
void FunctionStat ();
int FunctionList ();
void var_declaration_list (int* ptr_offset);
void var_declaration_stat (int* ptr_offset);
void const_declaration_list (int* ptr_offset);
void const_declaration_stat (int* ptr_offset);
void statement_list ();
void statement ();
void type ();
void if_stat ();
void while_stat ();
void read_stat ();
void write_stat ();
void compound_stat ();
void expression_stat ();
void variable (enum objectKind* ptr_kind, int* ptr_offset, int* ptr_IncOrDec);
void simple_variable (enum objectKind* ptr_kind, int* ptr_offset);
void expression ();
void simple_value ();
void term ();
void factor ();
void additive_expr ();
void for_stat ();
void value_expr ();
void break_stat ();
void exit_stat ();
void continue_stat ();
void switch_stat ();
void dowhile_stat ();
void repeat_stat ();
void enter (enum objectKind k, int offset, int* size, int dimension, double value);	/* add a new entry to symbol table */
int find_position_v1 (char* identName, int pos);	/* search the position of an identifier in symbol table according to its name */
int find_position_v2 (int offset, int pos);	    /* search the position of an identifier in symbol table according to its offset */
int find_position_v3 (char* fctName);
void error (int error_code);					/* error handler */
void gen (enum fctCode fct, int operand1, int operand2, double operand3);	/* generate an intermidiate code */

/* 
 * interpret and execute intermidiate code 
 */
void Interpret();