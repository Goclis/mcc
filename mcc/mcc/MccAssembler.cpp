#include "MccAssembler.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;


MccAssembler::MccAssembler()
{
	init_registers();
	init_func_codes();
	init_op_codes();

	// Test
	m_codes.push_back("add $v0, $v0, $v1");
	m_codes.push_back("bne $v0, $v0, main");
	m_codes.push_back("srlv $v1, $zero, $zero");
	m_codes.push_back("j main");
	m_codes.push_back("srlv $v1, $zero, $zero");
	m_codes.push_back("main:");
	m_codes.push_back("add $v0, $v0, $v1");
	m_codes.push_back("beq $v0, $v0, main");
	m_codes.push_back("srlv $v1, $zero, $zero");
	m_codes.push_back("jal main");
	m_codes.push_back("srlv $v1, $zero, $zero");
}


MccAssembler::MccAssembler(const vector<string> &codes)
	: m_codes(codes.begin(), codes.end())
{
	init_registers();
	init_func_codes();
	init_op_codes();
	init_bios_codes();
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
	m_func_codes.insert(FuncCodePair("addu", "100001"));
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


void MccAssembler::init_op_codes()
{
	m_op_codes.insert(OpCodePair("addiu", "001001"));
	m_op_codes.insert(OpCodePair("ori", "001101"));
	m_op_codes.insert(OpCodePair("lui", "001111"));
	m_op_codes.insert(OpCodePair("lw", "100011"));
	m_op_codes.insert(OpCodePair("sw", "101011"));
	m_op_codes.insert(OpCodePair("beq", "000100"));
	m_op_codes.insert(OpCodePair("bne", "000101"));
}


void MccAssembler::init_bios_codes()
{
	// BIOS
	vector<string> bios_codes;
	
	// ����ͳһ�Ĵ������
	m_codes.insert(m_codes.begin(), bios_codes.begin(), bios_codes.end());
}


void MccAssembler::scan()
{
	// �������룬���з��ദ��
	string current_line;
	for (size_t i = 0, size = m_codes.size(); i < size; ++i) {
		current_line = m_codes[i];

		if (current_line.find(':') != string::npos) {
			// �����з�����':'��Ϊlabel
			deal_label(current_line.substr(0, current_line.length() - 1));
		} else {
			// ������ָ�����
			deal_instruction(current_line);
		}
	}

	// ����Ĭ�ϵ��жϴ������
	m_interrupt_address["default"] = m_machine_codes.size();
	m_machine_codes.push_back("01000010000000000000000000011000");
}


void MccAssembler::output_coes()
{
	string rom_filename = "rom.coe";
	string ram_filename = "ram.coe";

	// ram.coe
	ofstream ram(ram_filename);
	ram <<
		"MEMORY_INITIALIZATION_RADIX=2;\n"
		"MEMORY_INITIALIZATION_VECTOR=\n";
	// ���ݼ�¼���ж������ж�������
	string interrupts[] = {
		"interrupt0",
		"interrupt1",
		"interrupt2",
		"interrupt3"
	};
	int itrs = 0;
	for (; itrs < 3; ++itrs) {
		ram << get_interrupt_address(interrupts[itrs]) << ",\n";
	}
	ram << get_interrupt_address(interrupts[itrs]) << ";\n";
	ram.close();

	// rom.coe
	ofstream rom(rom_filename);
	rom <<
		"MEMORY_INITIALIZATION_RADIX=2;\n"
		"MEMORY_INITIALIZATION_VECTOR=\n";
	size_t i = 0;
	size_t size = m_machine_codes.size();
	if (0 != size) {
		--size;
	}

	for (; i < size; ++i) {
		rom << m_machine_codes[i] << ",\n";
	}
	rom << m_machine_codes[i] << ";\n";
	rom.close();
}


void MccAssembler::deal_label(const string &label)
{
	// ��¼label�Ĵ�����
	unsigned int line_num = m_machine_codes.size();
	m_labels[label] = line_num;

	// �����label���жϴ�������label����Ҫ��¼����
	if ("interrupt0" == label || "interrupt1" == label
		|| "interrupt2" == label || "interrupt3" == label) {
		m_interrupt_address[label] = line_num;
	}

	// �����Ƿ������ڴ�label���µ�ָ���ȱ������
	vector<LackInfo*> &lacks = get_lack_infos(label);
	LackInfo *info;
	for (size_t i = 0, len = lacks.size(); i < len; ++i) {
		info = lacks[i];
		if (info->concern_offset) {
			// ����offset��bne��beq
			int offset = calculate_offset(info->code_line, line_num);
			m_machine_codes[info->code_line] += convert_scale(
				offset,
				16);
		} else {
			// ��ַ��j��jal
			m_machine_codes[info->code_line] += convert_scale(
				line_num,
				26);
		}

		// �ͷŵ�LackInfo
		delete info;
	}
	lacks.clear();
}


void MccAssembler::deal_instruction(const string &code)
{
	stringstream sstm(code);
	string instruction;
	sstm >> instruction;

	// ֻ�������õ���ָ��
	if ("add" == instruction || "addu" == instruction || "sub" == instruction
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
		|| "bne" == instruction) {
		// I����
		m_machine_codes.push_back(generate_i_instruction(
			instruction,
			code.substr(instruction.length() + 1)));
	} else if ("j" == instruction || "jal" == instruction) {
		// J���ͣ�Ŀǰ��������������
		m_machine_codes.push_back(generate_j_instruction(
			instruction,
			code.substr(instruction.length() + 1)));
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
	if (3 == operands_num) {
		// ��������������˳��Ϊrd, rs, rt
		rd = get_register_code(operands[0]);
		rs = get_register_code(operands[1]);
		rt = get_register_code(operands[2]);
	} else if (2 == operands_num) {
		// ��������������˳��Ϊrs, rt��rdΪ000000
		rd = "00000";
		rs = get_register_code(operands[0]);
		rt = get_register_code(operands[1]);
	} else if (1 == operands_num) {
		// һ������������rd����������Ϊ000000
		rd = get_register_code(operands[0]);
		rs = rt = "00000";
	}

	// shamt�����ڿ����õ���Rָ���Ϊ00000
	shamt = "00000";

	// func
	func = get_func_code(name);

	return op + rs + rt + rd + shamt + func;
}


string MccAssembler::generate_i_instruction(
	const string &name,
	const string &operands_str)
{
	string op, rs, rt, immediate;

	// op
	op = get_op_code(name);

	// rs, rt
	vector<string> operands;
	string immediate_or_offset;
	split_operands(operands_str, operands);
	// ����ָ��Ĳ�ͬ������ͬ�Ĵ���
	if ("addiu" == name || "ori" == name) {
		rt = get_register_code(operands[0]);
		rs = get_register_code(operands[1]);
		immediate_or_offset = operands[2];
	} else if ("lui" == name) {
		rs = "00000";
		rt = get_register_code(operands[0]);
		immediate_or_offset = operands[1];
	} else if ("lw" == name || "sw" == name) {
		rt = get_register_code(operands[0]);
		string &to_seperate = operands[1];

		// ��Ҫ�ӵڶ����������з������������op1����rs��op2��
		string op1, op2;
		bool add_to_op1 = true;
		char current_char;
		for (int i = 0, len = to_seperate.length(); i < len; ++i) {
			current_char = to_seperate[i];
			if ('(' == current_char) {
				add_to_op1 = false;
				continue;
			} else if (')' == current_char) {
				add_to_op1 = true;
				continue;
			}

			if (add_to_op1) {
				op1 += current_char;
			} else {
				op2 += current_char;
			}
		}

		rs = get_register_code(op2);
		immediate_or_offset = op1;
	} else if ("beq" == name || "bne" == name) {
		rt = get_register_code(operands[0]);
		rs = get_register_code(operands[1]);
		string &label = operands[2];

		//@todo δ��������Ҫ���Ӵ���bne��beqʹ�õ���ֱ�ӵ����ֶ���label�����

		// ���Ҹ�label�Ƿ���ȷ��λ�ã�δȷ������Ҫ��¼����������������
		unsigned int this_code_line = m_machine_codes.size();
		map<string, unsigned int>::const_iterator iter
			= m_labels.find(label);
		if (iter != m_labels.end()) {
			// ��label�ѳ��֣�����offset
			unsigned int label_line = iter->second;
			int offset = calculate_offset(this_code_line, label_line);

			// ��offsetת��Ϊ16λ�����ƣ�����immediate
			immediate = convert_scale(
				offset,
				16);
		} else {
			// labelδȷ�������ȱʧ��Ϣ
			LackInfo *lack_info = new LackInfo;
			lack_info->code_line = this_code_line;
			lack_info->concern_offset = true;

			vector<LackInfo*> &lack_infos = get_lack_infos(label);
			lack_infos.push_back(lack_info);
		}
	}

	// immediate
	if (0 != immediate_or_offset.length()) {
		// ת����16λ������
		// ������ܵ����������Ǳ��������ɵģ�ǿ��Ҫ����������ɵ���16����
		immediate = convert_scale(
			immediate_or_offset,
			16);
	}

	return op + rs + rt + immediate;
}


string MccAssembler::generate_j_instruction(
	const string &name,
	const string &label)
{
	string op, address;
	if ("j" == name) {
		op = "000010";
	} else if ("jal" == name) {
		op = "000011";
	}

	map<string, unsigned int>::const_iterator iter
		= m_labels.find(label);
	if (iter != m_labels.end()) {
		unsigned int code_line = iter->second;
		address = convert_scale((int)code_line, 26);
	} else {
		// labelδȷ�������ȱʧ��Ϣ
		LackInfo *lack_info = new LackInfo;
		lack_info->code_line = m_machine_codes.size();
		lack_info->concern_offset = false;

		vector<LackInfo*> &lack_infos = get_lack_infos(label);
		lack_infos.push_back(lack_info);
	}

	return op + address;
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
		return convert_scale(
			(int)iter->second,
			5);
	} else {
		log_warning("δ�ҵ���" + reg + "����Ӧ�ļĴ�������");
		return "000000";
	}
}


string MccAssembler::get_op_code(const string &op) const
{
	map<string, string>::const_iterator iter
		= m_op_codes.find(op);

	if (iter != m_op_codes.end()) {
		return iter->second;
	} else {
		log_warning("δ�ҵ���" + op + "����Ӧ��op����");
		return "000000";
	}
}


vector<LackInfo*>& MccAssembler::get_lack_infos(const string &label)
{
	map<string, vector<LackInfo*>>::iterator iter
		= m_lack_infos.find(label);
	if (iter != m_lack_infos.end()) {
		return iter->second;
	} else {
		vector<LackInfo*> new_vector;
		m_lack_infos[label] = new_vector;
		return m_lack_infos[label];
	}
}


string MccAssembler::get_interrupt_address(const string &int_name)
{
	map<string, unsigned int>::iterator iter
		= m_interrupt_address.find(int_name);
	if (iter != m_interrupt_address.end()) {
		return convert_scale((int)iter->second, 32);
	} else {
		return convert_scale(m_interrupt_address["default"], 32);
	}
}


string MccAssembler::convert_scale(
	int num,
	unsigned int digits) const
{
	char hex_chars[10] = { 0 };
	sprintf(hex_chars, "%X", num);

	string to_convert;
	for (int i = 0; i < 10; ++i) {
		if (hex_chars[i] != '\0') {
			to_convert += hex_chars[i];
		}
	}
	to_convert += "H";

	return convert_scale(to_convert, digits);
}


string MccAssembler::convert_scale(
	string num,
	unsigned int digits) const
{
	string ret;
	if (num.find('H') != string::npos) {
		// 16������������Լ��
		for (int i = 0, len = num.length() - 1; i < len; ++i) {
			ret += convert_hex_to_binary(num[i]);
		}
	} else {
		// ��16��������Ĭ��Ϊ10������
		// �����ֵ
		int value = 0;
		int base = 1;
		for (int i = num.length() - 1; i >= 0; --i) {
			value += (num[i] - '0') * base;
			base *= 10;
		}
		
		// ת���ɶ�����
		int digit;
		while (value > 0) {
			digit = value % 2;
			ret.insert(ret.begin(), digit + '0');
			value /= 2;
		}
	}

	int current_len = ret.length();
	if (current_len > digits) {
		ret = ret.substr(current_len - digits);
	} else if (current_len < digits) {
		for (int i = current_len; i < digits; ++i) {
			ret.insert(ret.begin(), '0');
		}
	}
	return ret;
}


string MccAssembler::convert_hex_to_binary(char c) const
{
	string ret;
	switch (c) {
	case '0':
		ret += "0000";
		break;
	case '1':
		ret += "0001";
		break;
	case '2':
		ret += "0010";
		break;
	case '3':
		ret += "0011";
		break;
	case '4':
		ret += "0100";
		break;
	case '5':
		ret += "0101";
		break;
	case '6':
		ret += "0110";
		break;
	case '7':
		ret += "0111";
		break;
	case '8':
		ret += "1000";
		break;
	case '9':
		ret += "1001";
		break;
	case 'A':
		ret += "1010";
		break;
	case 'B':
		ret += "1011";
		break;
	case 'C':
		ret += "1100";
		break;
	case 'D':
		ret += "1101";
		break;
	case 'E':
		ret += "1110";
		break;
	case 'F':
		ret += "1111";
		break;
	default:
		break;
	}

	return ret;
}


int MccAssembler::calculate_offset(int src, int trg) const
{
	int offset = trg - src;

	offset -= 2;

	return offset;
}


void MccAssembler::log_warning(const string &info) const
{
	cout << info << endl;
}

