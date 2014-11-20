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


%union {
	char *id_name;
	int int_val;
}

%start program

%%

program
	: decl_list
	;

decl_list
	: decl_list decl
	| decl
	;

decl
	: var_decl
	| fun_decl
	;

var_decl
		/* normal variable*/
	: type_spec IDENT ';' 
		/* array variable */
	| type_spec IDENT '[' int_literal ']' ';'
	;

type_spec
	: VOID
	| INT
	;

fun_decl
	: type_spec IDENT '(' params ')' compound_stmt
	| type_spec IDENT '(' params ')' ';'
	;

params
	: param_list
	| VOID
	;

param_list
	: param_list ',' param
	| param
	;

param
	: type_spec IDENT
	| type_spec IDENT '[' int_literal ']'
	;

stmt_list
	: stmt_list stmt
	|
	;

stmt
	: expr_stmt
	| compound_stmt
	| if_stmt
	| while_stmt
	| return_stmt
	| continue_stmt
	| break_stmt
	;

continue_stmt
	: CONTINUE ';'
	;

break_stmt
	: BREAK ';'
	;

expr_stmt
	: IDENT '=' expr ';'
	| IDENT '[' expr ']' '=' expr ';'
	| ';'
	;

while_stmt
	: WHILE '(' expr ')' stmt
	;

compound_stmt
	: '{' local_decls stmt_list '}'
	;

local_decls
	: local_decls local_decl
	|
	;

local_decl
	: type_spec IDENT ';'
	| type_spec IDENT '[' int_literal ']' ';'
	;

if_stmt
	: IF '(' expr ')' stmt %prec LOWER_THAN_ELSE
	| IF '(' expr ')' stmt ELSE stmt
	;

return_stmt
	: RETURN ';'
	| RETURN expr ';'
	;

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

int_literal
	: DECNUM	/* decimal number */
	| HEXNUM
	;

arg_list
	: arg_list ',' expr
	| expr
	;

args
	: arg_list
	|
	;



%%


