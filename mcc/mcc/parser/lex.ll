%{

#include "yacc.tab.hpp"

%}

%option noyywrap

%%

[ \t]			;
[\n]			;
"//"[^\n]*		;

"int" 					return INT;
"void" 					return VOID;
"while" 				return WHILE;
"if" 					return IF;
"else" 					return ELSE;
"break" 				return BREAK;
"continue" 				return CONTINUE;
"return" 				return RETURN;
[a-zA-Z][a-zA-Z0-9]*	return IDENT;
[1-9][0-9]*				return DECNUM;

","						return COMMA;
";"						return SEMICOLON;
"="						return EQUAL;
"["						return LEFT_SQUARE_BRACKET;
"]"						return RIGHT_SQUARE_BRACKET;
"("						return LEFT_PARANTHESIS;
")"						return RIGHT_PARANTHESIS;
"{"						return LEFT_CURLY_BRACKET;
"}"						return RIGHT_CURLY_BRACKET;
"||"					return OR;
"&&"					return AND;
"!"						return NOT;
"<="					return LE;
">="					return GE;
"<"						return LT;
">"						return GT;
"=="					return EQ;
"!="					return NE;
"+"						return PLUS;
"-"						return MINUS;
"*"						return ASTERISK;
"/"						return SOLIDUS;
"%"						return PERCENT;
"$"						return DOLLAR;

%%

