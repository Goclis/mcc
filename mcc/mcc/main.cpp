#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "MccAssembler.h"
#include "MccRobot.h"
using namespace std;

extern int yyparse();
extern FILE *yyin;


int main(int args, char** argv)
{
	MccRobot &robot = theMccRobot();
	string output_filename;
	string input_filename;

#ifdef DEBUG_MODE
	// Test selection.
	int select_input;
	cout << "Input 1 or 2 to select input file, 1 select 'test', 2 select 'correct'\n"
		"Your select: ";
	cin >> select_input;
	if (1 == select_input) {
		output_filename = input_filename = "test";
	} else if (2 == select_input) {
		output_filename = input_filename = "correct";
	} else {
		cout << "Wrong selection.\n";
		exit(0);
	}
#endif

	// Deal with main arguments.
	// args[1]: input file name.
	if (args > 1) {
		input_filename = string(argv[1]);
		output_filename = input_filename;
		int pos = input_filename.find('.');
		if (pos != -1) {
			output_filename = input_filename.substr(0, pos);
		}
	} else if (input_filename.empty()) {
		cout << "No input file.\n";
		exit(0);
	}

	// Open input file as yyin, the input of flex.
	yyin = fopen(input_filename.c_str(), "r");
	if (nullptr == yyin) {
		cout << "Open file failed.\n";
		exit(1);
	}

	// Parse.
	if (0 != yyparse()) {
		cout << "Parse error.\n";
		exit(1);
	}
	
	// After parsing, do more thing.
	if (robot.check_semantic_error()) {
		robot.generate_code();

		// Deal with conflict between input filename and output filename.
		if (input_filename == output_filename) {
			output_filename += ".out";
		}
		
		// Output generated code.
		ofstream out_stream(output_filename);
		out_stream << robot.get_global_var_code_buffer() << robot.get_code_buffer();

		// Generate machine code by using assembler.
		MccAssembler mcca(robot.get_codes());
		mcca.scan();
		mcca.output_coes();
	} else {
		cout << "Found error.\n";
	}

	return 0;
}