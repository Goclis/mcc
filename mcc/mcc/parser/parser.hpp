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
     IDENT = 258,
     DECNUM = 259,
     HEXNUM = 260,
     VOID = 261,
     INT = 262,
     WHILE = 263,
     IF = 264,
     ELSE = 265,
     RETURN = 266,
     BREAK = 267,
     CONTINUE = 268,
     OR = 269,
     AND = 270,
     LE = 271,
     GE = 272,
     EQ = 273,
     NE = 274,
     LSHIFT = 275,
     RSHIFT = 276,
     UNARY = 277,
     LOWER_THAN_ELSE = 278
   };
#endif
/* Tokens.  */
#define IDENT 258
#define DECNUM 259
#define HEXNUM 260
#define VOID 261
#define INT 262
#define WHILE 263
#define IF 264
#define ELSE 265
#define RETURN 266
#define BREAK 267
#define CONTINUE 268
#define OR 269
#define AND 270
#define LE 271
#define GE 272
#define EQ 273
#define NE 274
#define LSHIFT 275
#define RSHIFT 276
#define UNARY 277
#define LOWER_THAN_ELSE 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "parser.y"
{
	int iVal;
	string* pStr;
	TYPE_SPEC eType;
	MccExpression* pExpr;
	MccExpressionList* pExprList;
	MccIdentifier* pIdent;
	MccIntLiteral* pInt;
	MccFuncParameter* pFuncParam;
	MccFuncParameterList* pFuncParamList;
	MccDeclaration* pDecl;
	MccDeclarationList* pDeclList;
	MccFunctionDeclaration* pFuncDecl;
	MccVariableDeclaration* pVarDecl;
	MccStatement* pStmt;
	MccStatementList* pStmtList;
	MccBlockStatement* pBlockStmt;
	MccWhileStatement* pWhileStmt;
	MccIfStatement* pIfStmt;
	MccAssignStatement* pAssignStmt;
	MccReturnStatement* pReturnStmt;
	MccContinueStatement* pContinueStmt;
	MccBreakStatement* pBreakStmt;
}
/* Line 1529 of yacc.c.  */
#line 120 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

