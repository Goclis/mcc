%{

#include "parser.hpp"

static int myatoi(char *s, int d);

%}

digit 				[0-9]
letter 				[a-zA-Z]
id 					{letter}({letter}|{digit})*
num 				({digit})|([1-9]{digit}*)
hex 				0(x|X)({letter}|{digit})+


%option noyywrap

%%

[ \t]			;
[\n]			{ ++yylineno; }
"//"[^\n]*		;


"int" 					return INT;
"void" 					return VOID;
"while" 				return WHILE;
"if" 					return IF;
"else" 					return ELSE;
"break" 				return BREAK;
"continue" 				return CONTINUE;
"return" 				return RETURN;

{id} 					{yylval.id_name = yytext; return IDENT;}
{num}					{yylval.int_val = atoi(yytext); return DECNUM;}
{hex}					{yylval.int_val = myatoi(yytext, 16); return HEXNUM;}

","						return ',';
";"						return ';';
"="						return '=';
"["						return '[';
"]"						return ']';
"("						return '(';
")"						return ')';
"{"						return '{';
"}"						return '}';
"<<"					return LSHIFT;
">>"					return RSHIFT;
"||"					return OR;
"&&"					return AND;
"!"						return '!';
"<="					return LE;
">="					return GE;
"<"						return '<';
">"						return '>';
"=="					return EQ;
"!="					return NE;
"+"						return '+';
"-"						return '-';
"*"						return '*';
"/"						return '/';
"%"						return '%';
"$"						return '$';
"&"						return '&';
"^"						return '^';
"|"						return '|';
"~"						return '~';

%%

static int myatoi(char *s, int d)
{
	int r = 0;
	int negative = 0;

	if (*s == '-') {
		negative = 1;
		++s;
	}

	if (d == 16 && *s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X')) {
		s += 2;
	}

	for (; *s; ++s) {
		if (*s <= '9' && *s >= '0') {
			r = (r * d) + (*s - '0');
		} else if (d > 10 && *s <= 'f' && *s >= 'a') {
			r = (r * d) + (*s - 'a' + 10);
		} else if (d > 10 && *s <= 'F' && *s >= 'A') {
			r = (r * d) + (*s - 'A' + 10);
		} else {
			break;
		}
	}

	if (negative) {
		r *= -1;
	}

	return r;
}