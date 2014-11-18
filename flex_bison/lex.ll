%{
		
%}

%option noyywrap

%%

[ \t]			;
[\n]			;
"//"[^\n]*		;

"int" 					return token::INT;
"void" 					return token::VOID;
"while" 				return token::WHILE;
"if" 					return token::IF;
"else" 					return token::ELSE;
"break" 				return token::BREAK;
"continue" 				return token::CONTINUE;
"return" 				return token::RETURN;
[a-zA-Z][a-zA-Z0-9]*	return token::IDENT;
[1-9][0-9]*				return token::DECNUM;

","						return token::COMMA;
";"						return token::SEMICOLON;
"="						return token::EQUAL;
"["						return token::LEFT_SQUARE_BRACKET;
"]"						return token::RIGHT_SQUARE_BRACKET;
"("						return token::LEFT_PARANTHESIS;
")"						return token::RIGHT_PARANTHESIS;
"{"						return token::LEFT_CURLY_BRACKET;
"}"						return token::RIGHT_CURLY_BRACKET;
"||"					return token::OR;
"&&"					return token::AND;
"!"						return token::NOT;
"<="					return token::LE;
">="					return token::GE;
"<"						return token::LT;
">"						return token::GT;
"=="					return token::EQ;
"!="					return token::NE;
"+"						return token::PLUS;
"-"						return token::MINUS;
"*"						return token::ASTERISK;
"/"						return token::SOLIDUS;
"%"						return token::PERCENT;
"$"						return token::DOLLAR;

%%

