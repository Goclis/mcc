#include <stdio.h>
#include <cstdio>
extern int yyparse();
extern FILE *yyin;

int main()
{
	yyin = fopen("test", "r");
	yyparse();
	return 0;
}