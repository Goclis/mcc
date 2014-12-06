#include <stdio.h>
#include <cstdio>
#include <fstream>
#include "MccRobot.h"
using namespace std;
extern int yyparse();
extern FILE *yyin;

int main(int args, char** argv)
{
	MccRobot &robot = theMccRobot();
	string output_filename = "test";
	string input_filename = "test";
	if (args > 1) {
		input_filename = string(argv[1]);
		int pos = input_filename.find('.');
		if (pos != -1) {
			output_filename = input_filename.substr(0, pos);
		}
	}

	yyin = fopen(input_filename.c_str(), "r");

	yyparse();

	robot.generate_code();
	
	if (input_filename == output_filename) {
		output_filename += ".out";
	}
	ofstream out_stream(output_filename);
	out_stream << robot.get_global_var_code_buffer() << robot.get_code_buffer();

	return 0;
}