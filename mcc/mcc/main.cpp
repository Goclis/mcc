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
	string input_path;

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
		string argv1 = string(argv[1]);
		// Split argv1 into input_path and input_filename.
		// Check windows path.
		int pos = argv1.find_last_of('\\');
		if (string::npos == pos) {
			// Check unix path.
			pos = argv1.find_last_of('/');
		}
		if (string::npos != pos) {
			input_filename = argv1.substr(pos + 1);
			input_path = argv1.substr(0, pos + 1);
		} else {
			input_filename = argv1;
		}
		output_filename = input_filename;
		pos = input_filename.find('.');
		if (string::npos != pos) {
			output_filename = input_filename.substr(0, pos);
		}
	} else if (input_filename.empty()) {
		cout << "No input file.\n";
		exit(0);
	}

	// Open input file as yyin, the input of flex.
	yyin = fopen((input_path + input_filename).c_str(), "r");
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
		out_stream.close();

		// Generate machine code by using assembler.
		bool use_bios = true;
		if (args > 2) {
			if (0 == strcmp("--no-bios", argv[2])) {
				use_bios = false;
			}
		}
		MccAssembler mcca(robot.get_codes(), use_bios);
		mcca.scan();
		mcca.output_coes();

		cout << "Code Generation Finished.\n";
	} else {
		cout << "Found error.\n";
	}

	return 0;
}