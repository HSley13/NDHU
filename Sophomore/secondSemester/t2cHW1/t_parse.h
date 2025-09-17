/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     lWRITE = 258,
     lREAD = 259,
     lIF = 260,
     lASSIGN = 261,
     lRETURN = 262,
     lBEGIN = 263,
     lEND = 264,
     lLE = 265,
     lGE = 266,
     lLT = 267,
     lGT = 268,
     lNEQ = 269,
     lEQU = 270,
     lMINUS = 271,
     lADD = 272,
     lDIVIDE = 273,
     lTIMES = 274,
     lLP = 275,
     lRP = 276,
     lINT = 277,
     lREAL = 278,
     lSTRING = 279,
     lELSE = 280,
     lMAIN = 281,
     lSEMI = 282,
     lCOMMA = 283,
     lID = 284,
     lINUM = 285,
     lRNUM = 286,
     lQSTR = 287
   };
#endif
/* Tokens.  */
#define lWRITE 258
#define lREAD 259
#define lIF 260
#define lASSIGN 261
#define lRETURN 262
#define lBEGIN 263
#define lEND 264
#define lLE 265
#define lGE 266
#define lLT 267
#define lGT 268
#define lNEQ 269
#define lEQU 270
#define lMINUS 271
#define lADD 272
#define lDIVIDE 273
#define lTIMES 274
#define lLP 275
#define lRP 276
#define lINT 277
#define lREAL 278
#define lSTRING 279
#define lELSE 280
#define lMAIN 281
#define lSEMI 282
#define lCOMMA 283
#define lID 284
#define lINUM 285
#define lRNUM 286
#define lQSTR 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

