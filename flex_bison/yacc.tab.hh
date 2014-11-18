/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
     NEG_DECNUM = 260,
     COMMA = 261,
     SEMICOLON = 262,
     EQUAL = 263,
     LEFT_SQUARE_BRACKET = 264,
     RIGHT_SQUARE_BRACKET = 265,
     LEFT_PARANTHESIS = 266,
     RIGHT_PARANTHESIS = 267,
     LEFT_CURLY_BRACKET = 268,
     RIGHT_CURLY_BRACKET = 269,
     VOID = 270,
     INT = 271,
     WHILE = 272,
     IF = 273,
     ELSE = 274,
     RETURN = 275,
     BREAK = 276,
     CONTINUE = 277,
     OR = 278,
     AND = 279,
     NOT = 280,
     LE = 281,
     GE = 282,
     LT = 283,
     GT = 284,
     EQ = 285,
     NE = 286,
     PLUS = 287,
     MINUS = 288,
     ASTERISK = 289,
     SOLIDUS = 290,
     PERCENT = 291,
     DOLLAR = 292,
     LOWER_THAN_ELSE = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


