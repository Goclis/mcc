%token IDENT 						/* Identifier */
%token DECNUM 						/* decimal number*/
%token NEG_DECNUM
%token COMMA						/* , */
%token SEMICOLON 					/* ; */
%token EQUAL						/* = */
%token LEFT_SQUARE_BRACKET 			/* [ */
%token RIGHT_SQUARE_BRACKET 		/* ] */
%token LEFT_PARANTHESIS				/* ( */
%token RIGHT_PARANTHESIS			/* ) */
%token LEFT_CURLY_BRACKET			/* { */
%token RIGHT_CURLY_BRACKET			/* } */
%token VOID							/* void */
%token INT 							/* int */
%token WHILE 						/* while */
%token IF 							/* if */
%token ELSE							/* else */
%token RETURN 						/* return */
%token BREAK 						/* break */
%token CONTINUE 					/* continue */
%token OR							/* || */
%token AND							/* && */
%token NOT							/* ! */
%token LE 							/* <= */
%token GE							/* >= */
%token LT 							/* < */
%token GT 							/* > */
%token EQ 							/* == */
%token NE 							/* != */
%token PLUS 						/* + */
%token MINUS 						/* - */
%token ASTERISK 					/* * */
%token SOLIDUS 						/* / */
%token PERCENT 						/* % */
%token DOLLAR 						/* $ */

%left OR AND
%left EQ NE
%left LE LT GE GT
%left PLUS MINUS
%left ASTERISK SOLIDUS PERCENT
%right NOT DOLLAR

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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
	: type_spec IDENT SEMICOLON 
		/* array variable */
	| type_spec IDENT LEFT_SQUARE_BRACKET int_literal RIGHT_SQUARE_BRACKET SEMICOLON
	;

type_spec
	: VOID
	| INT
	;

fun_decl
	: type_spec IDENT LEFT_PARANTHESIS params RIGHT_PARANTHESIS compound_stmt
	;

params
	: param_list
	| VOID
	;

param_list
	: param_list COMMA param
	| param
	;

param
	: type_spec IDENT
	| type_spec IDENT LEFT_SQUARE_BRACKET int_literal RIGHT_SQUARE_BRACKET
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
	: CONTINUE SEMICOLON
	;

break_stmt
	: BREAK SEMICOLON
	;

expr_stmt
	: IDENT EQUAL expr SEMICOLON
	| IDENT LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET EQUAL expr SEMICOLON
	| SEMICOLON
	;

while_stmt
	: WHILE LEFT_PARANTHESIS expr RIGHT_PARANTHESIS stmt
	;

compound_stmt
	: LEFT_CURLY_BRACKET local_decls stmt_list RIGHT_CURLY_BRACKET
	;

local_decls
	: local_decls local_decl
	|
	;

local_decl
	: type_spec IDENT SEMICOLON
	| type_spec IDENT LEFT_SQUARE_BRACKET int_literal RIGHT_SQUARE_BRACKET SEMICOLON
	;

if_stmt
	: IF LEFT_PARANTHESIS expr RIGHT_PARANTHESIS stmt %prec LOWER_THAN_ELSE
	| IF LEFT_PARANTHESIS expr RIGHT_PARANTHESIS stmt ELSE stmt
	;

return_stmt
	: RETURN SEMICOLON
	| RETURN expr SEMICOLON
	;

expr
	: expr OR expr 				/* || */
	| expr EQ expr 				/* == */
	| expr NE expr 				/* != */
	| expr LE expr 				/* <= */
	| expr LT expr 				/* < */
	| expr GE expr 				/* >= */
	| expr GT expr 				/* > */
	| expr AND expr 			/* && */
	| expr PLUS expr 			/* + */
	| expr MINUS expr 			/* - */
	| expr ASTERISK expr 		/* * */
	| expr SOLIDUS expr 		/* / */
	| expr PERCENT expr 		/* % */
	| NOT expr 					/* ! */
	| DOLLAR expr 				/* $ */
	| LEFT_PARANTHESIS expr RIGHT_PARANTHESIS
	| IDENT
	| IDENT LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET
	| IDENT LEFT_PARANTHESIS args RIGHT_PARANTHESIS
	| int_literal
	| NEG_DECNUM
	;

int_literal
	: DECNUM	/* decimal number */
	;

arg_list
	: arg_list COMMA expr
	| expr
	;

args
	: arg_list
	|
	;



%%


