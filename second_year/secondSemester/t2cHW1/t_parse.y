nclude <stdio.h>
    #include <stdlib.h>
        #include "t2c.h"
            #include "t_parse.h"
            %}

%token lWRITE lREAD lIF lASSIGN
%token lRETURN lBEGIN lEND
%left  lEQU lNEQ lGT lLT lGE lLE
%left  lADD lMINUS
%left  lTIMES lDIVIDE
%token lLP lRP
%token lINT lREAL lSTRING
%token lELSE
%token lMAIN
%token lSEMI lCOMMA
%token lID lINUM lRNUM lQSTR

%expect 1

%%

prog
    : mthdcls
            { printf("Program -| MethodDecls\nParsed OK!\n"); }
                |
                        { printf("**** Parsing failed!\n"); }
                            ;

mthdcls
    : mthdcl mthdcls
            { printf("MethodDecls -| MethodDecl MethodDecls\n"); }
                | mthdcl
                        { printf("MethodDecls -| MethodDecl\n"); }
                            ;

type
    : lINT
            { printf("Type -| INT\n"); }
                | lREAL
                        { printf("Type -| REAL\n"); }
                            ;

mthdcl
    : type lMAIN lID lLP formals lRP block
            { printf("MethodDecl -| Type MAIN ID LP Formals RP Block\n"); }
                | type lID lLP formals lRP block
                        { printf("MethodDecl -| Type ID LP Formals RP Block\n"); }
                            ;

formals
    : formal oformal
            { printf("Formals -| Formal OtherFormals\n"); }
                |
                        { printf("Formals -| \n"); }
                            ;

formal
    : type lID
            { printf("Formal -| Type ID\n"); }
                ;

oformal
    : lCOMMA formal oformal
            { printf("OtherFormals -| COMMA Formal OtherFormals\n"); }
                |
                        { printf("OtherFormals -| \n"); }
                            ;

block
    : lBEGIN stmt_list lEND
            { printf("Block -| BEGIN StatementList END\n"); }
                ;

stmt_list
    : stmt stmt_list
            { printf("StatementList -| Statement StatementList\n"); }
                | stmt
                        { printf("StatementList -| Statement\n"); }
                            ;

stmt
    : block
            { printf("Statement -| Block\n"); }
                | localvar
                        { printf("Statement -| LocalVarDecl\n"); }
                            | assign
                                    { printf("Statement -| AssignStmt\n"); }
                                        | ret
                                                { printf("Statement -| ReturnStmt\n"); }
                                                    | ifstmt
                                                            { printf("Statement -| IfStmt\n"); }
                                                                | writestmt
                                                                        { printf("Statement -| WriteStmt\n"); }
                                                                            | readstmt
                                                                                    { printf("Statement -| ReadStmt\n"); }
                                                                                        ;

localvar
    : type lID lSEMI
            { printf("LocalVarDecl -| Type ID SEMI\n"); }
                | type assign
                        { printf("LocalVarDecl -| Type AssignStmt\n"); }
                            ;

assign
    : lID lASSIGN expr lSEMI
            { printf("AssignStmt -| ID := Expression SEMI\n"); }
                ;

ret
    : lRETURN expr lSEMI
            { printf("ReturnStmt -| RETURN Expression SEMI\n"); }
                ;

ifstmt
    : lIF lLP boolexpr lRP stmt lELSE stmt
            { printf("IfStmt -| IF ( BoolExpr ) Statement ELSE Statement\n"); }
                | lIF lLP boolexpr lRP stmt
                        { printf("IfStmt -| IF ( BoolExpr ) Statement\n"); }
                            ;

writestmt
    : lWRITE lLP expr lCOMMA lQSTR lRP lSEMI
            { printf("WriteStmt -| WRITE ( Expression , QString ) ;\n"); }
                ;

readstmt
    : lREAD lLP lID lCOMMA lQSTR lRP lSEMI
            { printf("ReadStmt -| READ ( ID , QString ) ;\n"); }
                ;

expr
    : expr lADD term
            { printf("Expression -| Expression + Term\n"); }
                | expr lMINUS term
                        { printf("Expression -| Expression - Term\n"); }
                            | term
                                    { printf("Expression -| Term\n"); }
                                        ;

term
    : term lTIMES factor
            { printf("Term -| Term * Factor\n"); }
                | term lDIVIDE factor
                        { printf("Term -| Term / Factor\n"); }
                            | factor
                                    { printf("Term -| Factor\n"); }
                                        ;

factor
    : lINUM
            { printf("Factor -| INUM\n"); }
                | lRNUM
                        { printf("Factor -| RNUM\n"); }
                            | lID
                                    { printf("Factor -| ID\n"); }
                                        | lLP expr lRP
                                                { printf("Factor -| ( Expression )\n"); }
                                                    | lID lLP actuals lRP
                                                            { printf("Factor -| ID ( ActualParams )\n"); }
                                                                ;

boolexpr
    : expr lEQU expr
            { printf("BoolExpr -| Expression == Expression\n"); }
                | expr lNEQ expr
                        { printf("BoolExpr -| Expression != Expression\n"); }
                            | expr lGT expr
                                    { printf("BoolExpr -| Expression | Expression\n"); }
                                        | expr lGE expr
                                                { printf("BoolExpr -| Expression >= Expression\n"); }
                                                    | expr lLT expr
                                                            { printf("BoolExpr -| Expression < Expression\n"); }
                                                                | expr lLE expr
                                                                        { printf("BoolExpr -| Expression <= Expression\n"); }
                                                                            ;

actuals
    : expr moreactuals
            { printf("ActualParams -| Expression OtherParams\n"); }
                |
                        { printf("ActualParams -| \n"); }
                            ;

moreactuals
    : lCOMMA expr moreactuals
            { printf("OtherParams -| , Expression OtherParams\n"); }
                |
                        { printf("OtherParams -| \n"); }
                            ;

%%

int yyerror(char *s)
{
    printf("%s\n", s);
        return 1;
        }
}
