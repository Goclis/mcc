%{
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
%}


%union {
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

%token <pStr> IDENT 						/* Identifier */
%token <iVal> DECNUM 						/* decimal number*/
%token <iVal> HEXNUM
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

%type <eType> type_spec
%type <pExpr> expr expr_stmt
%type <pInt> int_literal
%type <pFuncParam> param
%type <pFuncParamList> param_list params
%type <pDecl> decl
%type <pDeclList> decl_list local_decls
%type <pVarDecl> var_decl local_decl
%type <pFuncDecl> fun_decl
%type <pStmt> stmt
%type <pStmtList> stmt_list
%type <pBlockStmt> block_stmt
%type <pWhileStmt> while_stmt
%type <pIfStmt> if_stmt
%type <pAssignStmt> assign_stmt
%type <pReturnStmt> return_stmt
%type <pContinueStmt> continue_stmt
%type <pBreakStmt> break_stmt
%type <pExprList> arg_list args


%start program

%%

program
	: decl_list {
		theMccRobot().initialize($1);
		if ($1 != nullptr) {
			delete $1;
		}
	}
	| {
		theMccRobot().initialize(nullptr);
	}
	;

decl_list
	: decl_list decl {
		$$ = $1;
		$1 = nullptr;
		($$)->push_back($2);
	}
	| decl {
		$$ = new MccDeclarationList($1);
	}
	;

decl
	: var_decl {
		$$ = $1;
	}
	| fun_decl {
		$$ = $1;
	}
	;

var_decl
	: type_spec IDENT ';' {
		$$ = new MccVariableDeclaration($1, new MccIdentifier($2));
		delete $2;
	}
	| type_spec IDENT '[' int_literal ']' ';' {
		$$ = new MccVariableDeclaration($1, new MccIdentifier($2), ($4)->get_value());
		delete $2;
	}
	;

fun_decl
	: type_spec IDENT '(' params ')' '{' local_decls stmt_list '}' {
		$$ = new MccFunctionDeclaration($1, new MccIdentifier($2), $4, $7, $8);
		delete $2;
		if ($4 != nullptr) {
			delete $4;
		}

		if ($7 != nullptr) {
			delete $7;
		}

		if ($8 != nullptr) {
			delete $8;
		}
		
	}
	| type_spec IDENT '(' params ')' ';' {
		$$ = new MccFunctionDeclaration($1, new MccIdentifier($2), $4);
		delete $2;

		if ($4 != nullptr) {
			delete $4;
		}
	}
	;

type_spec
	: VOID {
		$$ = VOID_TYPE_SPEC;
	}
	| INT {
		$$ = INT_TYPE_SPEC;	
	}
	;

params
	: param_list {
		$$ = $1;
	}
	| VOID {
		$$ = nullptr;
	}
	;

param_list
	: param_list ',' param {
		$$ = $1;
		$1 = nullptr;
		($$)->push_back($3);
	}
	| param {
		$$ = new MccFuncParameterList($1);
	}
	;

param
	: INT IDENT {
		$$ = new MccFuncParameter(INT_TYPE_SPEC, new MccIdentifier($2));
		delete $2;
	}
	| INT IDENT '[' int_literal ']' {
		$$ = new MccFuncParameter(INT_TYPE_SPEC, new MccIdentifier($2), ($4)->get_value());
		delete $2;
	}
	| INT {
		$$ = new MccFuncParameter(INT_TYPE_SPEC, nullptr);
	}
	| INT '[' int_literal ']' {
		$$ = new MccFuncParameter(INT_TYPE_SPEC, nullptr, ($3)->get_value());
	}
	;

local_decls
	: local_decls local_decl {
		$$ = $1;
		$1 = nullptr;
		($$)->push_back($2);
	}
	| {
		$$ = new MccDeclarationList(nullptr);
	}
	;

local_decl
	: type_spec IDENT ';' {
		$$ = new MccVariableDeclaration($1, new MccIdentifier($2));
		delete $2;
	}
	| type_spec IDENT '[' int_literal ']' ';' {
		$$ = new MccVariableDeclaration($1, new MccIdentifier($2), ($4)->get_value());
		delete $2;
	}
	;

stmt_list
	: stmt_list stmt {
		$$ = $1;
		$1 = nullptr;
		($$)->push_back($2);
	}
	| {
		$$ = new MccStatementList(nullptr);
	}
	;

stmt
	: assign_stmt {
		$$ = $1;
	}
	| expr_stmt {
		$$ = $1;
	}
	| block_stmt {
		$$ = $1;
	}
	| if_stmt {
		$$ = $1;
	}
	| while_stmt {
		$$ = $1;
	}
	| return_stmt {
		$$ = $1;
	}
	| continue_stmt {
		$$ = $1;
	}
	| break_stmt {
		$$ = $1;
	}
	;

block_stmt
	: '{' stmt_list '}' {
		$$ = new MccBlockStatement($2);

		if ($2 != nullptr) {
			delete $2;
		}
	}
	;

while_stmt
	: WHILE '(' expr ')' stmt {
		$$ = new MccWhileStatement($3, $5);
	}
	;

if_stmt
	: IF '(' expr ')' stmt %prec LOWER_THAN_ELSE {
		$$ = new MccIfStatement($3, $5);
	}
	| IF '(' expr ')' stmt ELSE stmt {
		$$ = new MccIfStatement($3, $5, $7);
	}
	;

return_stmt
	: RETURN ';' {
		$$ = new MccReturnStatement(nullptr);
	}
	| RETURN expr ';' {
		$$ = new MccReturnStatement($2);
	}
	;

continue_stmt
	: CONTINUE ';' {
		$$ = new MccContinueStatement();
	}
	;

break_stmt
	: BREAK ';' {
		$$ = new MccBreakStatement();
	}
	;

assign_stmt
	: IDENT '=' expr ';' {
		$$ = new MccAssignStatement(new MccIdentifier($1), $3);
		delete $1;
	}
	| IDENT '[' expr ']' '=' expr ';' {
		$$ = new MccAssignStatement(new MccArrayAccessExpression(new MccIdentifier($1), $3), $6);
		delete $1;
	}
	| '$' expr '=' expr ';' {
		$$ = new MccAssignStatement(new MccUnaryOperatorExpression(PORT_UNARY, $2), $4, true);
	}
	;

expr_stmt
	: expr ';' {
		$$ = $1;
	}
	;

expr
	: expr OR expr {
		$$ = new MccBinaryOperatorExpression(OR_BINARY, $1, $3);
	}
	| expr EQ expr {
		$$ = new MccBinaryOperatorExpression(EQ_BINARY, $1, $3);
	}
	| expr NE expr {
		$$ = new MccBinaryOperatorExpression(NE_BINARY, $1, $3);
	}
	| expr LE expr {
		$$ = new MccBinaryOperatorExpression(LE_BINARY, $1, $3);
	}
	| expr '<' expr {
		$$ = new MccBinaryOperatorExpression(LT_BINARY, $1, $3);
	}
	| expr GE expr {
		$$ = new MccBinaryOperatorExpression(GE_BINARY, $1, $3);
	}
	| expr '>' expr {
		$$ = new MccBinaryOperatorExpression(GT_BINARY, $1, $3);
	}
	| expr AND expr {
		$$ = new MccBinaryOperatorExpression(AND_BINARY, $1, $3);
	}
	| expr '+' expr {
		$$ = new MccBinaryOperatorExpression(PLUS_BINARY, $1, $3);
	}
	| expr '-' expr {
		$$ = new MccBinaryOperatorExpression(MINUS_BINARY, $1, $3);
	}
	| expr '*' expr {
		$$ = new MccBinaryOperatorExpression(MULT_BINARY, $1, $3);
	}
	| expr '/' expr {
		$$ = new MccBinaryOperatorExpression(DIV_BINARY, $1, $3);
	}
	| expr '%' expr {
		$$ = new MccBinaryOperatorExpression(MD_BINARY, $1, $3);
	}
	| '!' expr %prec UNARY {
		$$ = new MccUnaryOperatorExpression(NOT_UNARY, $2);
	}
	| '$' expr %prec UNARY {
		$$ = new MccUnaryOperatorExpression(PORT_UNARY, $2);
	}
	| '-' expr %prec UNARY {
		$$ = new MccUnaryOperatorExpression(NEGATIVE_UNARY, $2);
	}
	| '+' expr %prec UNARY {
		$$ = new MccUnaryOperatorExpression(POSITIVE_UNARY, $2);
	}
	| '(' expr ')' {
		$$ = $2;
	}
	| IDENT {
		$$ = new MccIdentifier($1);
		delete $1;
	}
	| IDENT '[' expr ']' {
		$$ = new MccArrayAccessExpression(new MccIdentifier($1), $3);
		delete $1;
	}
	| IDENT '(' args ')' {
		$$ = new MccMethodCallExpression(new MccIdentifier($1), $3);
		delete $1;

		if ($3 != nullptr) {
			delete $3;
		}
	}
	| int_literal {
		$$ = $1;
	}
	| expr '&' expr {
		$$ = new MccBinaryOperatorExpression(BIT_AND_BINARY, $1, $3);
	}
	| expr '^' expr {
		$$ = new MccBinaryOperatorExpression(EXCLUSIVE_BINARY, $1, $3);
	}
	| '~' expr {
		$$ = new MccUnaryOperatorExpression(NEG_UNARY, $2);
	}
	| expr LSHIFT expr {
		$$ = new MccBinaryOperatorExpression(LSHIFT_BINARY, $1, $3);
	}
	| expr RSHIFT expr {
		$$ = new MccBinaryOperatorExpression(RSHIFT_BINARY, $1, $3);
	}
	| expr '|' expr {
		$$ = new MccBinaryOperatorExpression(BIT_OR_BINARY, $1, $3);
	}
	;

args
	: arg_list {
		$$ = $1;
	}
	| {
		$$ = nullptr;
	}
	;

arg_list
	: arg_list ',' expr {
		$$ = $1;
		$1 = nullptr;
		($$)->push_back($3);
	}
	| expr {
		$$ = new MccExpressionList($1);
	}
	;


int_literal
	: DECNUM {
		$$ = new MccIntLiteral($1);
	}
	| HEXNUM {
		$$ = new MccIntLiteral($1);
	}
	;

%%


