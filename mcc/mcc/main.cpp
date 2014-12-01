#include <stdio.h>
#include <cstdio>
#include "MccRobot.h"
extern int yyparse();
extern FILE *yyin;

int main()
{
	yyin = fopen("test", "r");
	yyparse();

	theMccRobot().generate_code();
	return 0;
}