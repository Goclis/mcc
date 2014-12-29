#include "MccAssembler.h"
#include <sstream>
#include <iostream>
#include <cstdio>
using namespace std;


MccAssembler::MccAssembler()
{
	init_registers();
	init_func_codes();
	
	// Test
	m_codes.push_back("add $v0, $v0, $v1");
}


MccAssembler::~MccAssembler()
{
}


void MccAssembler::init_registers()
{
	// $zero -> 0
	m_registers.insert(RegisterPair("$zero", 0));

	// $v0 -> 2
	m_registers.insert(RegisterPair("$v0", 2));

	// $v1 -> 3
	m_registers.insert(RegisterPair("$v1", 3));

	// $t0 -> 8
	m_registers.insert(RegisterPair("$t0", 8));

	// $sp -> 29
	m_registers.insert(RegisterPair("$sp", 29));

	// $ra -> 31
	m_registers.insert(RegisterPair("$ra", 31));
}


void MccAssembler::init_func_codes()
{
	m_func_codes.insert(FuncCodePair("add", "100000"));
	m_func_codes.insert(FuncCodePair("sub", "100010"));
	m_func_codes.insert(FuncCodePair("subu", "100011"));
	m_func_codes.insert(FuncCodePair("and", "100100"));
	m_func_codes.insert(FuncCodePair("mult", "011000"));
	m_func_codes.insert(FuncCodePair("div", "011010"));
	m_func_codes.insert(FuncCodePair("mfhi", "010000"));
	m_func_codes.insert(FuncCodePair("mflo", "010010"));
	m_func_codes.insert(FuncCodePair("or", "100101"));
	m_func_codes.insert(FuncCodePair("xor", "100110"));
	m_func_codes.insert(FuncCodePair("nor", "100111"));
	m_func_codes.insert(FuncCodePair("slt", "101010"));
	m_func_codes.insert(FuncCodePair("sltu", "101011"));
	m_func_codes.insert(FuncCodePair("sllv", "000100"));
	m_func_codes.insert(FuncCodePair("srlv", "000110"));
	m_func_codes.insert(FuncCodePair("jr", "001000"));
}


void MccAssembler::scan()
{
	// �������룬���з��ദ��
	string current_line;
	for (size_t i = 0, size = m_codes.size(); i < size; ++i) {
		current_line = m_codes[i];

		if (current_line.find(':') != string::npos) {
			// �����з�����':'��Ϊlabel
			deal_label(current_line);
		} else {
			// ������ָ�����
			deal_instruction(current_line);
		}
	}
}


void MccAssembler::deal_label(const string &code)
{
	
}


void MccAssembler::deal_instruction(const string &code)
{
	stringstream sstm(code);
	string instruction;
	sstm >> instruction;

	// ֻ�������õ���ָ��
	if ("add" == instruction || "sub" == instruction
			|| "subu" == instruction || "and" == instruction
			|| "mult" == instruction || "div" == instruction
			|| "mfhi" == instruction || "mflo" == instruction
			|| "or" == instruction || "xor" == instruction
			|| "nor" == instruction || "slt" == instruction
			|| "sltu" == instruction || "sllv" == instruction
			|| "srlv" == instruction || "jr" == instruction) {
		// R����
		m_machine_codes.push_back(generate_r_instruction(
			instruction, 
			code.substr(instruction.length() + 1)));
	} else if ("addiu" == instruction || "ori" == instruction
			|| "lui" == instruction || "lw" == instruction
			|| "sw" == instruction || "beq" == instruction
			|| "bne" == instruction ) {
		// I����
	} else if ("j" == instruction || "jal" == instruction) {
		// J����
	}
}


string MccAssembler::generate_r_instruction(
	const string &name, 
	const string &operands_str) const
{
	string op, rs, rt, rd, shamt, func;

	op = "000000";

	// rs, rt, rd
	vector<string> operands;
	split_operands(operands_str, operands);
	size_t operands_num = operands.size();
	// ����ָ��Ĳ�ͬ���Բ���������ͬ�Ĵ���
	if (3 == operands_num) {
		// ��������������˳��Ϊrd, rs, rt
		rd = get_register_code(operands[0]);
		rs = get_register_code(operands[1]);
		rt = get_register_code(operands[2]);
	} else if (2 == operands_num) {
		// ��������������˳��Ϊrs, rt��rdΪ000000
		rd = "000000";
		rs = get_register_code(operands[0]);
		rt = get_register_code(operands[1]);
	} else if (1 == operands_num) {
		// һ������������rd����������Ϊ000000
		rd = get_register_code(operands[0]);
		rs = rt = "000000";
	}

	// shamt�����ڿ����õ���Rָ���Ϊ000000
	shamt = "000000";

	// func
	func = get_func_code(name);

	return op + rs + rt + rd + shamt + func;
}


void MccAssembler::split_operands(
	const string &str, 
	vector<string> &operands) const
{
	string token;
	char current_char;
	for (int i = 0, len = str.length(); i < len; ++i) {
		current_char = str[i];
		if (',' == current_char) {
			operands.push_back(token);
			token.clear();
		} else if (' ' == current_char) {
			// ����
		} else {
			token += current_char;
		}
	}
	if (0 != token.length()) {
		operands.push_back(token);
	}
}


string MccAssembler::get_func_code(const string &name) const
{
	map<string, string>::const_iterator iter 
		= m_func_codes.find(name);

	if (iter != m_func_codes.end()) {
		return iter->second;
	} else {
		log_warning("δ�ҵ���" + name + "����func_code");
		return "000000";
	}
}


string MccAssembler::get_register_code(const string &reg) const
{
	map<string, unsigned int>::const_iterator iter 
		= m_registers.find(reg);

	if (iter != m_registers.end()) {
		stringstream sstm;
		sstm << iter->second;
		string ret = sstm.str();
		int rest = 6 - ret.length();
		while (rest > 0) {
			ret.insert(ret.begin(), '0');
			--rest;
		}
		return ret;
	} else {
		log_warning("δ�ҵ���" + reg + "����Ӧ�ļĴ�������");
		return "000000";
	}
}


void MccAssembler::log_warning(const string &info) const
{
	cout << info << endl;
}

