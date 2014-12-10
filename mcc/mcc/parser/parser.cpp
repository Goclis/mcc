/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include <stdio.h>
#include <string>
#include "../MccRobot.h"
#include "../MccPublicType.h"
#include "../MccExpression.h"
#include "../MccIdentifier.h"
#include "../MccIntLiteral.h"
#include "../MccUnaryOperatorExpression.h"
#include "../MccFuncParameter.h"
#include "../MccFuncParameterList.h"
#include "../MccArrayAccessExpression.h"
#include "../MccDeclaration.h"
#include "../MccDeclarationList.h"
#include "../MccFunctionDeclaration.h"
#include "../MccVariableDeclaration.h"
#include "../MccStatement.h"
#include "../MccStatementList.h"
#include "../MccBlockStatement.h"
#include "../MccWhileStatement.h"
#include "../MccIfStatement.h"
#include "../MccAssignStatement.h"
#include "../MccExpressionList.h"
#include "../MccMethodCallExpression.h"
#include "../MccBinaryOperatorExpression.h"
#include "../MccReturnStatement.h"
#include "../MccContinueStatement.h"
#include "../MccBreakStatement.h"
using std::string;

extern int yylex();
extern int yylineno;
extern char *yytext;
void yyerror(const char *s)
{
	printf("ERROR: %s at line %d around '%s'\n", s, yylineno, yytext);
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 206 "parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 219 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   553

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  158

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,     2,    45,    31,    27,     2,
      39,    40,    29,    24,    43,    25,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      23,    44,    22,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,    26,    42,    33,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    34,    35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    13,    15,    19,
      26,    36,    43,    45,    47,    49,    51,    55,    57,    60,
      66,    68,    73,    76,    77,    81,    88,    91,    92,    94,
      96,    98,   100,   102,   104,   106,   108,   112,   118,   124,
     132,   135,   139,   142,   145,   150,   158,   164,   167,   171,
     175,   179,   183,   187,   191,   195,   199,   203,   207,   211,
     215,   219,   222,   225,   228,   231,   235,   237,   242,   247,
     249,   253,   257,   260,   264,   268,   272,   274,   275,   279,
     281,   283
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    -1,    -1,    48,    49,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,     3,    36,    -1,    52,
       3,    37,    71,    38,    36,    -1,    52,     3,    39,    53,
      40,    41,    56,    58,    42,    -1,    52,     3,    39,    53,
      40,    36,    -1,     6,    -1,     7,    -1,    54,    -1,     6,
      -1,    54,    43,    55,    -1,    55,    -1,     7,     3,    -1,
       7,     3,    37,    71,    38,    -1,     7,    -1,     7,    37,
      71,    38,    -1,    56,    57,    -1,    -1,    52,     3,    36,
      -1,    52,     3,    37,    71,    38,    36,    -1,    58,    59,
      -1,    -1,    66,    -1,    67,    -1,    60,    -1,    62,    -1,
      61,    -1,    63,    -1,    64,    -1,    65,    -1,    41,    58,
      42,    -1,     8,    39,    68,    40,    59,    -1,     9,    39,
      68,    40,    59,    -1,     9,    39,    68,    40,    59,    10,
      59,    -1,    11,    36,    -1,    11,    68,    36,    -1,    13,
      36,    -1,    12,    36,    -1,     3,    44,    68,    36,    -1,
       3,    37,    68,    38,    44,    68,    36,    -1,    45,    68,
      44,    68,    36,    -1,    68,    36,    -1,    68,    14,    68,
      -1,    68,    18,    68,    -1,    68,    19,    68,    -1,    68,
      16,    68,    -1,    68,    23,    68,    -1,    68,    17,    68,
      -1,    68,    22,    68,    -1,    68,    15,    68,    -1,    68,
      24,    68,    -1,    68,    25,    68,    -1,    68,    29,    68,
      -1,    68,    30,    68,    -1,    68,    31,    68,    -1,    32,
      68,    -1,    45,    68,    -1,    25,    68,    -1,    24,    68,
      -1,    39,    68,    40,    -1,     3,    -1,     3,    37,    68,
      38,    -1,     3,    39,    69,    40,    -1,    71,    -1,    68,
      27,    68,    -1,    68,    28,    68,    -1,    33,    68,    -1,
      68,    20,    68,    -1,    68,    21,    68,    -1,    68,    26,
      68,    -1,    70,    -1,    -1,    70,    43,    68,    -1,    68,
      -1,     4,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   133,   139,   144,   150,   153,   159,   166,
     176,   195,   209,   212,   218,   221,   227,   232,   238,   245,
     252,   256,   263,   268,   274,   281,   291,   296,   302,   305,
     308,   311,   314,   317,   320,   323,   329,   340,   347,   351,
     358,   362,   369,   376,   383,   389,   395,   402,   408,   412,
     416,   420,   424,   428,   432,   436,   440,   444,   448,   452,
     456,   460,   464,   468,   472,   476,   479,   484,   492,   503,
     506,   510,   514,   518,   522,   526,   533,   536,   542,   547,
     555,   559
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "DECNUM", "HEXNUM", "VOID",
  "INT", "WHILE", "IF", "ELSE", "RETURN", "BREAK", "CONTINUE", "OR", "AND",
  "LE", "GE", "EQ", "NE", "LSHIFT", "RSHIFT", "'>'", "'<'", "'+'", "'-'",
  "'|'", "'&'", "'^'", "'*'", "'/'", "'%'", "'!'", "'~'", "UNARY",
  "LOWER_THAN_ELSE", "';'", "'['", "']'", "'('", "')'", "'{'", "'}'",
  "','", "'='", "'$'", "$accept", "program", "decl_list", "decl",
  "var_decl", "fun_decl", "type_spec", "params", "param_list", "param",
  "local_decls", "local_decl", "stmt_list", "stmt", "block_stmt",
  "while_stmt", "if_stmt", "return_stmt", "continue_stmt", "break_stmt",
  "assign_stmt", "expr_stmt", "expr", "args", "arg_list", "int_literal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    62,    60,    43,    45,   124,    38,    94,    42,
      47,    37,    33,   126,   277,   278,    59,    91,    93,    40,
      41,   123,   125,    44,    61,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    61,    62,    62,
      63,    63,    64,    65,    66,    66,    66,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    70,    70,
      71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     3,     6,
       9,     6,     1,     1,     1,     1,     3,     1,     2,     5,
       1,     4,     2,     0,     3,     6,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     5,     5,     7,
       2,     3,     2,     2,     4,     7,     5,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     3,     1,     4,     4,     1,
       3,     3,     2,     3,     3,     3,     1,     0,     3,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    12,    13,     0,     2,     5,     6,     7,     0,     1,
       4,     0,     8,     0,     0,    80,    81,     0,    15,    20,
       0,    14,    17,     0,    18,     0,     0,     0,     9,     0,
       0,    11,    23,    16,     0,    21,    27,    19,     0,    22,
       0,     0,    66,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    10,     0,    26,    30,    32,    31,
      33,    34,    35,    28,    29,     0,    69,    24,     0,     0,
      77,     0,     0,     0,    66,    40,     0,     0,    43,    42,
      64,    63,    61,    72,     0,     0,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    47,     0,     0,    79,     0,
      76,     0,     0,     0,     0,    62,    41,    65,    36,     0,
      48,    55,    51,    53,    49,    50,    73,    74,    54,    52,
      56,    57,    75,    70,    71,    58,    59,    60,     0,    67,
      68,     0,    44,     0,     0,     0,     0,    25,     0,    78,
      37,    38,    67,    46,     0,     0,    45,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    20,    21,    22,
      36,    39,    40,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   109,   110,    66
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -136
static const yytype_int16 yypact[] =
{
       8,  -136,  -136,    40,     8,  -136,  -136,  -136,    -1,  -136,
    -136,     2,  -136,    14,    54,  -136,  -136,    28,  -136,    -2,
      27,    25,  -136,    34,    36,    14,   -25,    64,  -136,    14,
      37,  -136,  -136,  -136,    41,  -136,     8,  -136,    77,  -136,
      73,    26,    -7,    48,    49,   106,    47,    53,   149,   149,
     149,   149,   149,  -136,  -136,   149,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,   322,  -136,  -136,    14,   149,
     149,   149,   149,   149,    -3,  -136,   149,   345,  -136,  -136,
    -136,  -136,  -136,  -136,   191,   116,    46,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,  -136,    55,   272,   437,    51,
      52,   368,   218,   245,   149,  -136,  -136,  -136,  -136,   149,
     454,   470,   498,   498,   486,   486,    44,    44,   498,   498,
     510,   510,   522,    -8,    -8,    44,    44,    44,    56,    50,
    -136,   149,  -136,   159,   159,   297,   391,  -136,   149,   437,
    -136,    89,  -136,  -136,   414,   159,  -136,  -136
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -136,  -136,  -136,    96,  -136,  -136,    65,  -136,  -136,    75,
    -136,  -136,    60,  -135,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,   -45,  -136,  -136,     4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      77,    24,    11,    80,    81,    82,    83,    84,   150,   151,
      86,    31,    93,    94,     1,     2,    32,    17,    15,    16,
     157,   102,   103,   104,   107,   108,   111,   112,   113,    30,
      69,   115,    70,    34,   114,    25,    70,    71,    12,    13,
       9,    14,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
      18,    19,    67,    68,    93,    94,    23,    26,    27,   145,
      28,    19,   106,    29,   146,    35,    42,    15,    16,    37,
      41,    43,    44,    78,    45,    46,    47,    72,    73,    79,
     119,   140,   147,   138,   148,   141,   149,    48,    49,   155,
      10,    38,    33,   154,     0,    50,    51,     0,     0,    74,
      15,    16,    52,    85,    53,    54,     0,     0,    55,    42,
      15,    16,     0,     0,    43,    44,     0,    45,    46,    47,
      48,    49,     0,     0,     0,     0,     0,     0,    50,    51,
      48,    49,    75,     0,     0,    52,     0,     0,    50,    51,
       0,    76,    74,    15,    16,    52,     0,    53,   118,     0,
       0,    55,    42,    15,    16,     0,     0,    43,    44,     0,
      45,    46,    47,    48,    49,     0,     0,     0,     0,     0,
       0,    50,    51,    48,    49,     0,     0,     0,    52,     0,
       0,    50,    51,     0,    76,     0,     0,     0,    52,     0,
      53,     0,     0,     0,    55,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,     0,     0,
       0,   117,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,   143,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,   144,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,     0,     0,
     139,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,     0,
       0,     0,     0,     0,     0,   152,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,   105,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,     0,
       0,   116,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
       0,     0,     0,     0,   142,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,   153,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,     0,     0,
     156,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    89,    90,     0,     0,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    93,    94,
       0,     0,    97,    98,    99,   100,   101,   102,   103,   104,
      93,    94,     0,     0,     0,     0,    99,   100,   101,   102,
     103,   104,    93,    94,     0,     0,     0,     0,     0,   100,
     101,   102,   103,   104
};

static const yytype_int16 yycheck[] =
{
      45,     3,     3,    48,    49,    50,    51,    52,   143,   144,
      55,    36,    20,    21,     6,     7,    41,    13,     4,     5,
     155,    29,    30,    31,    69,    70,    71,    72,    73,    25,
      37,    76,    39,    29,    37,    37,    39,    44,    36,    37,
       0,    39,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
       6,     7,    36,    37,    20,    21,    38,    40,    43,   114,
      36,     7,    68,    37,   119,    38,     3,     4,     5,    38,
       3,     8,     9,    36,    11,    12,    13,    39,    39,    36,
      44,    40,    36,    38,    44,    43,   141,    24,    25,    10,
       4,    36,    27,   148,    -1,    32,    33,    -1,    -1,     3,
       4,     5,    39,    53,    41,    42,    -1,    -1,    45,     3,
       4,     5,    -1,    -1,     8,     9,    -1,    11,    12,    13,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      24,    25,    36,    -1,    -1,    39,    -1,    -1,    32,    33,
      -1,    45,     3,     4,     5,    39,    -1,    41,    42,    -1,
      -1,    45,     3,     4,     5,    -1,    -1,     8,     9,    -1,
      11,    12,    13,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    24,    25,    -1,    -1,    -1,    39,    -1,
      -1,    32,    33,    -1,    45,    -1,    -1,    -1,    39,    -1,
      41,    -1,    -1,    -1,    45,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    36,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    36,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    36,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    36,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      36,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    16,    17,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    20,    21,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      20,    21,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    31,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    47,    48,    49,    50,    51,    52,     0,
      49,     3,    36,    37,    39,     4,     5,    71,     6,     7,
      53,    54,    55,    38,     3,    37,    40,    43,    36,    37,
      71,    36,    41,    55,    71,    38,    56,    38,    52,    57,
      58,     3,     3,     8,     9,    11,    12,    13,    24,    25,
      32,    33,    39,    41,    42,    45,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    71,    36,    37,    37,
      39,    44,    39,    39,     3,    36,    45,    68,    36,    36,
      68,    68,    68,    68,    68,    58,    68,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    36,    71,    68,    68,    69,
      70,    68,    68,    68,    37,    68,    36,    40,    42,    44,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    38,    38,
      40,    43,    36,    40,    40,    68,    68,    36,    44,    68,
      59,    59,    38,    36,    68,    10,    36,    59
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 127 "parser.y"
    {
		theMccRobot().initialize((yyvsp[(1) - (1)].pDeclList));
		if ((yyvsp[(1) - (1)].pDeclList) != nullptr) {
			delete (yyvsp[(1) - (1)].pDeclList);
		}
	;}
    break;

  case 3:
#line 133 "parser.y"
    {
		theMccRobot().initialize(nullptr);
	;}
    break;

  case 4:
#line 139 "parser.y"
    {
		(yyval.pDeclList) = (yyvsp[(1) - (2)].pDeclList);
		(yyvsp[(1) - (2)].pDeclList) = nullptr;
		((yyval.pDeclList))->push_back((yyvsp[(2) - (2)].pDecl));
	;}
    break;

  case 5:
#line 144 "parser.y"
    {
		(yyval.pDeclList) = new MccDeclarationList((yyvsp[(1) - (1)].pDecl));
	;}
    break;

  case 6:
#line 150 "parser.y"
    {
		(yyval.pDecl) = (yyvsp[(1) - (1)].pVarDecl);
	;}
    break;

  case 7:
#line 153 "parser.y"
    {
		(yyval.pDecl) = (yyvsp[(1) - (1)].pFuncDecl);
	;}
    break;

  case 8:
#line 159 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (3)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (3)].pStr);
		(yyval.pVarDecl) = new MccVariableDeclaration((yyvsp[(1) - (3)].eType), ident);
		((yyval.pVarDecl))->set_lineno(yylineno);
	;}
    break;

  case 9:
#line 166 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (6)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (6)].pStr);
		(yyval.pVarDecl) = new MccVariableDeclaration((yyvsp[(1) - (6)].eType), ident, ((yyvsp[(4) - (6)].pInt))->get_value());
		((yyval.pVarDecl))->set_lineno(yylineno);
	;}
    break;

  case 10:
#line 176 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (9)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (9)].pStr);
		(yyval.pFuncDecl) = new MccFunctionDeclaration((yyvsp[(1) - (9)].eType), ident, (yyvsp[(4) - (9)].pFuncParamList), (yyvsp[(7) - (9)].pDeclList), (yyvsp[(8) - (9)].pStmtList));
		((yyval.pFuncDecl))->set_lineno(yylineno);
		if ((yyvsp[(4) - (9)].pFuncParamList) != nullptr) {
			delete (yyvsp[(4) - (9)].pFuncParamList);
		}

		if ((yyvsp[(7) - (9)].pDeclList) != nullptr) {
			delete (yyvsp[(7) - (9)].pDeclList);
		}

		if ((yyvsp[(8) - (9)].pStmtList) != nullptr) {
			delete (yyvsp[(8) - (9)].pStmtList);
		}
		
	;}
    break;

  case 11:
#line 195 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (6)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (6)].pStr);
		(yyval.pFuncDecl) = new MccFunctionDeclaration((yyvsp[(1) - (6)].eType), ident, (yyvsp[(4) - (6)].pFuncParamList));
		((yyval.pFuncDecl))->set_lineno(yylineno);

		if ((yyvsp[(4) - (6)].pFuncParamList) != nullptr) {
			delete (yyvsp[(4) - (6)].pFuncParamList);
		}
	;}
    break;

  case 12:
#line 209 "parser.y"
    {
		(yyval.eType) = VOID_TYPE_SPEC;
	;}
    break;

  case 13:
#line 212 "parser.y"
    {
		(yyval.eType) = INT_TYPE_SPEC;	
	;}
    break;

  case 14:
#line 218 "parser.y"
    {
		(yyval.pFuncParamList) = (yyvsp[(1) - (1)].pFuncParamList);
	;}
    break;

  case 15:
#line 221 "parser.y"
    {
		(yyval.pFuncParamList) = nullptr;
	;}
    break;

  case 16:
#line 227 "parser.y"
    {
		(yyval.pFuncParamList) = (yyvsp[(1) - (3)].pFuncParamList);
		(yyvsp[(1) - (3)].pFuncParamList) = nullptr;
		((yyval.pFuncParamList))->push_back((yyvsp[(3) - (3)].pFuncParam));
	;}
    break;

  case 17:
#line 232 "parser.y"
    {
		(yyval.pFuncParamList) = new MccFuncParameterList((yyvsp[(1) - (1)].pFuncParam));
	;}
    break;

  case 18:
#line 238 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (2)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (2)].pStr);
		(yyval.pFuncParam) = new MccFuncParameter(INT_TYPE_SPEC, ident);
		((yyval.pFuncParam))->set_lineno(yylineno);
	;}
    break;

  case 19:
#line 245 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (5)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (5)].pStr);
		(yyval.pFuncParam) = new MccFuncParameter(INT_TYPE_SPEC, ident, ((yyvsp[(4) - (5)].pInt))->get_value());
		((yyval.pFuncParam))->set_lineno(yylineno);
	;}
    break;

  case 20:
#line 252 "parser.y"
    {
		(yyval.pFuncParam) = new MccFuncParameter(INT_TYPE_SPEC, nullptr);
		((yyval.pFuncParam))->set_lineno(yylineno);
	;}
    break;

  case 21:
#line 256 "parser.y"
    {
		(yyval.pFuncParam) = new MccFuncParameter(INT_TYPE_SPEC, nullptr, ((yyvsp[(3) - (4)].pInt))->get_value());
		((yyval.pFuncParam))->set_lineno(yylineno);
	;}
    break;

  case 22:
#line 263 "parser.y"
    {
		(yyval.pDeclList) = (yyvsp[(1) - (2)].pDeclList);
		(yyvsp[(1) - (2)].pDeclList) = nullptr;
		((yyval.pDeclList))->push_back((yyvsp[(2) - (2)].pVarDecl));
	;}
    break;

  case 23:
#line 268 "parser.y"
    {
		(yyval.pDeclList) = new MccDeclarationList(nullptr);
	;}
    break;

  case 24:
#line 274 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (3)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (3)].pStr);
		(yyval.pVarDecl) = new MccVariableDeclaration((yyvsp[(1) - (3)].eType), ident);
		((yyval.pVarDecl))->set_lineno(yylineno);
	;}
    break;

  case 25:
#line 281 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(2) - (6)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(2) - (6)].pStr);
		(yyval.pVarDecl) = new MccVariableDeclaration((yyvsp[(1) - (6)].eType), ident, ((yyvsp[(4) - (6)].pInt))->get_value());
		((yyval.pVarDecl))->set_lineno(yylineno);
	;}
    break;

  case 26:
#line 291 "parser.y"
    {
		(yyval.pStmtList) = (yyvsp[(1) - (2)].pStmtList);
		(yyvsp[(1) - (2)].pStmtList) = nullptr;
		((yyval.pStmtList))->push_back((yyvsp[(2) - (2)].pStmt));
	;}
    break;

  case 27:
#line 296 "parser.y"
    {
		(yyval.pStmtList) = new MccStatementList(nullptr);
	;}
    break;

  case 28:
#line 302 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pAssignStmt);
	;}
    break;

  case 29:
#line 305 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pExpr);
	;}
    break;

  case 30:
#line 308 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pBlockStmt);
	;}
    break;

  case 31:
#line 311 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pIfStmt);
	;}
    break;

  case 32:
#line 314 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pWhileStmt);
	;}
    break;

  case 33:
#line 317 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pReturnStmt);
	;}
    break;

  case 34:
#line 320 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pContinueStmt);
	;}
    break;

  case 35:
#line 323 "parser.y"
    {
		(yyval.pStmt) = (yyvsp[(1) - (1)].pBreakStmt);
	;}
    break;

  case 36:
#line 329 "parser.y"
    {
		(yyval.pBlockStmt) = new MccBlockStatement((yyvsp[(2) - (3)].pStmtList));
		((yyval.pBlockStmt))->set_lineno(yylineno);

		if ((yyvsp[(2) - (3)].pStmtList) != nullptr) {
			delete (yyvsp[(2) - (3)].pStmtList);
		}
	;}
    break;

  case 37:
#line 340 "parser.y"
    {
		(yyval.pWhileStmt) = new MccWhileStatement((yyvsp[(3) - (5)].pExpr), (yyvsp[(5) - (5)].pStmt));
		((yyval.pWhileStmt))->set_lineno(yylineno);
	;}
    break;

  case 38:
#line 347 "parser.y"
    {
		(yyval.pIfStmt) = new MccIfStatement((yyvsp[(3) - (5)].pExpr), (yyvsp[(5) - (5)].pStmt));
		((yyval.pIfStmt))->set_lineno(yylineno);
	;}
    break;

  case 39:
#line 351 "parser.y"
    {
		(yyval.pIfStmt) = new MccIfStatement((yyvsp[(3) - (7)].pExpr), (yyvsp[(5) - (7)].pStmt), (yyvsp[(7) - (7)].pStmt));
		((yyval.pIfStmt))->set_lineno(yylineno);
	;}
    break;

  case 40:
#line 358 "parser.y"
    {
		(yyval.pReturnStmt) = new MccReturnStatement(nullptr);
		((yyval.pReturnStmt))->set_lineno(yylineno);
	;}
    break;

  case 41:
#line 362 "parser.y"
    {
		(yyval.pReturnStmt) = new MccReturnStatement((yyvsp[(2) - (3)].pExpr));
		((yyval.pReturnStmt))->set_lineno(yylineno);
	;}
    break;

  case 42:
#line 369 "parser.y"
    {
		(yyval.pContinueStmt) = new MccContinueStatement();
		((yyval.pContinueStmt))->set_lineno(yylineno);
	;}
    break;

  case 43:
#line 376 "parser.y"
    {
		(yyval.pBreakStmt) = new MccBreakStatement();
		((yyval.pBreakStmt))->set_lineno(yylineno);
	;}
    break;

  case 44:
#line 383 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(1) - (4)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(1) - (4)].pStr);
		(yyval.pAssignStmt) = new MccAssignStatement(ident, (yyvsp[(3) - (4)].pExpr));
	;}
    break;

  case 45:
#line 389 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(1) - (7)].pStr));
		ident->set_lineno(yylineno);
		delete (yyvsp[(1) - (7)].pStr);
		(yyval.pAssignStmt) = new MccAssignStatement(new MccArrayAccessExpression(ident, (yyvsp[(3) - (7)].pExpr)), (yyvsp[(6) - (7)].pExpr));
	;}
    break;

  case 46:
#line 395 "parser.y"
    {
		(yyval.pAssignStmt) = new MccAssignStatement(new MccUnaryOperatorExpression(PORT_UNARY, (yyvsp[(2) - (5)].pExpr)), (yyvsp[(4) - (5)].pExpr), true);
		((yyval.pAssignStmt))->set_lineno(yylineno);
	;}
    break;

  case 47:
#line 402 "parser.y"
    {
		(yyval.pExpr) = (yyvsp[(1) - (2)].pExpr);
	;}
    break;

  case 48:
#line 408 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(OR_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 49:
#line 412 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(EQ_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 50:
#line 416 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(NE_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 51:
#line 420 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(LE_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 52:
#line 424 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(LT_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 53:
#line 428 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(GE_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 54:
#line 432 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(GT_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 55:
#line 436 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(AND_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 56:
#line 440 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(PLUS_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 57:
#line 444 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(MINUS_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 58:
#line 448 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(MULT_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 59:
#line 452 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(DIV_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 60:
#line 456 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(MD_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 61:
#line 460 "parser.y"
    {
		(yyval.pExpr) = new MccUnaryOperatorExpression(NOT_UNARY, (yyvsp[(2) - (2)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 62:
#line 464 "parser.y"
    {
		(yyval.pExpr) = new MccUnaryOperatorExpression(PORT_UNARY, (yyvsp[(2) - (2)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 63:
#line 468 "parser.y"
    {
		(yyval.pExpr) = new MccUnaryOperatorExpression(NEGATIVE_UNARY, (yyvsp[(2) - (2)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 64:
#line 472 "parser.y"
    {
		(yyval.pExpr) = new MccUnaryOperatorExpression(POSITIVE_UNARY, (yyvsp[(2) - (2)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 65:
#line 476 "parser.y"
    {
		(yyval.pExpr) = (yyvsp[(2) - (3)].pExpr);
	;}
    break;

  case 66:
#line 479 "parser.y"
    {
		(yyval.pExpr) = new MccIdentifier((yyvsp[(1) - (1)].pStr));
		((yyval.pExpr))->set_lineno(yylineno);
		delete (yyvsp[(1) - (1)].pStr);
	;}
    break;

  case 67:
#line 484 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(1) - (4)].pStr));
		delete (yyvsp[(1) - (4)].pStr);
		ident->set_lineno(yylineno);
		(yyval.pExpr) = new MccArrayAccessExpression(ident, (yyvsp[(3) - (4)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
		delete (yyvsp[(1) - (4)].pStr);
	;}
    break;

  case 68:
#line 492 "parser.y"
    {
		MccIdentifier *ident = new MccIdentifier((yyvsp[(1) - (4)].pStr));
		delete (yyvsp[(1) - (4)].pStr);
		ident->set_lineno(yylineno);
		(yyval.pExpr) = new MccMethodCallExpression(ident, (yyvsp[(3) - (4)].pExprList));
		((yyval.pExpr))->set_lineno(yylineno);

		if ((yyvsp[(3) - (4)].pExprList) != nullptr) {
			delete (yyvsp[(3) - (4)].pExprList);
		}
	;}
    break;

  case 69:
#line 503 "parser.y"
    {
		(yyval.pExpr) = (yyvsp[(1) - (1)].pInt);
	;}
    break;

  case 70:
#line 506 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(BIT_AND_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 71:
#line 510 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(EXCLUSIVE_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 72:
#line 514 "parser.y"
    {
		(yyval.pExpr) = new MccUnaryOperatorExpression(NEG_UNARY, (yyvsp[(2) - (2)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 73:
#line 518 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(LSHIFT_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 74:
#line 522 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(RSHIFT_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 75:
#line 526 "parser.y"
    {
		(yyval.pExpr) = new MccBinaryOperatorExpression(BIT_OR_BINARY, (yyvsp[(1) - (3)].pExpr), (yyvsp[(3) - (3)].pExpr));
		((yyval.pExpr))->set_lineno(yylineno);
	;}
    break;

  case 76:
#line 533 "parser.y"
    {
		(yyval.pExprList) = (yyvsp[(1) - (1)].pExprList);
	;}
    break;

  case 77:
#line 536 "parser.y"
    {
		(yyval.pExprList) = nullptr;
	;}
    break;

  case 78:
#line 542 "parser.y"
    {
		(yyval.pExprList) = (yyvsp[(1) - (3)].pExprList);
		(yyvsp[(1) - (3)].pExprList) = nullptr;
		((yyval.pExprList))->push_back((yyvsp[(3) - (3)].pExpr));
	;}
    break;

  case 79:
#line 547 "parser.y"
    {
		(yyval.pExprList) = new MccExpressionList((yyvsp[(1) - (1)].pExpr));
	;}
    break;

  case 80:
#line 555 "parser.y"
    {
		(yyval.pInt) = new MccIntLiteral((yyvsp[(1) - (1)].iVal));
		((yyval.pInt))->set_lineno(yylineno);
	;}
    break;

  case 81:
#line 559 "parser.y"
    {
		(yyval.pInt) = new MccIntLiteral((yyvsp[(1) - (1)].iVal));
		((yyval.pInt))->set_lineno(yylineno);
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2314 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 565 "parser.y"




