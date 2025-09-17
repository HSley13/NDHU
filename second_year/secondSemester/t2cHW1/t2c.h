/*
#define L_MIN 0
#define lWRITE 1
#define lREAD 2
#define lIF 3
#define lELSE 4
#define lRETURN 5
#define lBEGIN 6
#define lEND 7
#define lMAIN 8
#define lSTRING 9
#define lINT 10
#define lREAL 11
#define lSEMI 12
#define lCOMMA 13
#define lLP 14
#define lRP 15
#define lADD 16
#define lMINUS 17
#define lTIMES 18
#define lDIVIDE 19
#define lASSIGN 20
#define lEQU 21
#define lNEQ 22
#define lID 23
#define lINUM 24
#define lRNUM 25
#define lQSTR 26
#define L_MAX 27
*/
#include <stdio.h>
extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern int yyerror(char *);

extern void print_lex(int);

extern char name[16];
extern int ival;
extern float rval;
extern char qstr[80];
