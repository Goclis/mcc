%{
#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char *yytext;
void yyerror(const char *s)
{
	printf("ERROR: %s at line %d around '%s'\n", s, yylineno, yytext);
}
%}

%token IDENT 						/* Identifier */
%token DECNUM 						/* decimal number*/
%token HEXNUM

%token VOID
%token INT
%token WHILE
%token IF
%token ELSE
%token RETURN
%token BREAK
%token CONTINUE
%token OR
%token AND
%token LE
%token GE
%token EQ
%token NE
%token LSHIFT
%token RSHIFT

%left OR 
%left AND
%left EQ NE
%left LE GE '>' '<'
%left '+' '-'
%left '|'
%left '&' '^'
%left '*' '/' '%'
%right LSHIFT RSHIFT
%right '!'
%right '~'
%nonassoc UNARY
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%nonassoc ID_CALL
%nonassoc '[' '('


%union {
	char *id_name;
	int int_val;
}

%start program

%%

/* 这个文件用于解释文法 */

/* 1 */
program
	: decl_list /* 程序最外层Block由一系列的声明组成 */
	| /* 支持空程序 */
	;

/* 左递归声明列表 */
decl_list
	: decl_list decl
	| decl
	;

/* 单个声明 */
decl
	: var_decl /* 变量声明 */
	| fun_decl /* 函数声明 */
	;

/* 变量声明，只支持int类型，需要做语义检查 */
var_decl
	: type_spec IDENT ';' /* 普通变量声明 */
	| type_spec IDENT '[' int_literal ']' ';' /* 数组变量声明 */
	;

/* 方法声明，返回值为int或void */
fun_decl
	: type_spec IDENT '(' params ')' compound_stmt /* 方法定义，这里需要语义检查形参是否有参数名 */
	| type_spec IDENT '(' params ')' ';' /* 方法声明 */
	;

/* 类型 */
type_spec
	: VOID /* void */
	| INT /* int */
	;

/* 方法声明参数，VOID表示无参数 */
params
	: param_list
	| VOID
	;

/* 方法声明参数列表，左递归实现 */
param_list
	: param_list ',' param
	| param
	;

/* 方法声明参数列表中每个参数的形式，参数类型只能为int */
param
	: INT IDENT  /* int i */
	| INT IDENT '[' int_literal ']' /* int i[10] */
	| INT /* int，无需形参名 */
	| INT '[' int_literal ']' /* int [10]，无需形参名 */
	;

/* 复杂语句块，这里指方法实现的语句块 */
compound_stmt
	: '{' local_decls stmt_list '}' /* 由局部声明列表和语句列表组成 */
	;

/* 局部声明的列表，左递归实现 */
local_decls
	: local_decls local_decl
	|
	;

/* 局部声明，只能为变量声明，同样只支持int类型，需要做语义错误检查 */
local_decl
	: type_spec IDENT ';'
	| type_spec IDENT '[' int_literal ']' ';'
	;

/* 语句列表，左递归实现，可以为空 */
stmt_list
	: stmt_list stmt
	|
	;

/* 单条语句 */
stmt
	: assign_stmt
	| expr_stmt
	| block_stmt
	| if_stmt
	| while_stmt
	| return_stmt
	| continue_stmt
	| break_stmt
	| ';'
	;

/* 块语句，为了与compound_stmt区分，针对if、else、while等语句的块以及普通的块 */
block_stmt
	: '{' stmt_list '}' {printf("Block\n");}
	;

/* while语句 */
while_stmt
	: WHILE '(' expr ')' stmt
	;

/* if语句 */
if_stmt
	: IF '(' expr ')' stmt %prec LOWER_THAN_ELSE
	| IF '(' expr ')' stmt ELSE stmt
	;

/* return语句，需要语义检查返回情况于方法的返回值是否匹配 */
return_stmt
	: RETURN ';'
	| RETURN expr ';'
	;

/* continue语句，需要语义检查外层是否有while */
continue_stmt
	: CONTINUE ';'
	;

/* break语句，需要语义检查外层是否有while */
break_stmt
	: BREAK ';'
	;

/* 赋值语句 */
assign_stmt
	: IDENT '=' expr ';' /* 普通变量赋值 */
	| IDENT '[' expr ']' '=' expr ';' /* 数组变量赋值 */
	| '$' expr '=' expr ';' /* 端口赋值操作 */
	;

/* 表达式语句，单纯的表达式也可以认为是语句 */
expr_stmt
	: expr ';'
	;

/* 表达式 */
expr
	: expr OR expr
	| expr EQ expr	
	| expr NE expr
	| expr LE expr
	| expr '<' expr 		
	| expr GE expr
	| expr '>' expr
	| expr AND expr
	| expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| expr '%' expr
	| '!' expr %prec UNARY	
	| '$' expr %prec UNARY
	| '-' expr %prec UNARY
	| '+' expr %prec UNARY
	| '(' expr ')'
	| IDENT
	| IDENT '[' expr ']'
	| IDENT '(' args ')'
	| int_literal
	| expr '&' expr
	| expr '^' expr
	| '~' expr
	| expr LSHIFT expr
	| expr RSHIFT expr
	| expr '|' expr
	;

/* 实参列表，左递归实现 */
arg_list
	: arg_list ',' expr
	| expr
	;

/* 实参列表，提供支持空参数 */
args
	: arg_list
	|
	;

/* 整数常量 */
int_literal
	: DECNUM	/* decimal number */
	| HEXNUM
	;

%%


