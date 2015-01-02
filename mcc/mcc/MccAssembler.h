#pragma once

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;
using std::pair;


// 记录指令缺失信息的struct
struct LackInfo {
	bool concern_offset; // true - offset, false - address
	unsigned int code_line;
};


/**
* MiniC编译器对应汇编器。
*
* @注意
*	1. 因为仅仅作为mcc的后端，处理很弱。
*	2. 格式上的要求可能会比较苛刻。
*/
class MccAssembler
{
public:
	MccAssembler();
	MccAssembler(const vector<string> &codes);
	~MccAssembler();

	// 一系列初始化方法，仅仅初始化可能用到的值
	// 初始化寄存器的映射表
	void init_registers();

	// 初始化func码
	void init_func_codes();

	// 初始化op码
	void init_op_codes();

	// 扫描代码，进行转换
	void scan();

	// 输出到coe文件，默认为rom.coe和ram.coe
	void output_coes();

	// 一系列的处理方法
	// 处理label
	void deal_label(const string &label);

	// 处理指令
	void deal_instruction(const string &code);


	// 一系列的生成方法
	/**
	* @brief 生成R类型的指令的机器码。
	*
	* @param name 指令的名字，如add。
	*
	* @param operands 指令使用的操作数，全部组合在了一起。
	*
	* @return 生成的机器码。
	*/
	string generate_r_instruction(
		const string &name,
		const string &operands_str) const;

	/**
	* @breif 生成I类型的指令的机器码。
	*
	* @param name 指令的名字，如addiu。
	*
	* @param operands 指令使用的操作数，全部组合在了一起。
	*
	* @return 生成的机器码。
	*/
	string generate_i_instruction(
		const string &name,
		const string &operands_str);

	string generate_j_instruction(
		const string &name,
		const string &label);

	// 辅助方法
	/**
	* @brief 按','号切割操作数
	*
	* @param str 待切割的字符串
	*
	* @param operands 切割完后的操作数
	*/
	void split_operands(
		const string &str,
		vector<string> &operands) const;

	// 查找指令对应的func编码
	string get_func_code(const string &name) const;

	// 查找寄存器对应的编码
	string get_register_code(const string &reg) const;

	// 查找操作对应的编码
	string get_op_code(const string &op) const;

	// 查找某label对应的缺失信息
	vector<LackInfo*>& get_lack_infos(const string &label);

	// 获取中断处理程序的32位地址，如果不存在返回默认的中断处理程序的地址
	string get_interrupt_address(const string &int_name);
	

	/**
	* @brief 将十进制数转换为二进制字符串
	*
	* @param num 待转化的数字
	*
	* @param digits 位数
	*
	* @return 转换得到的字符串
	*/
	string convert_scale(
		int num,
		unsigned int digits) const;

	// 重载，数字用字符串表示，源进制信息包含在数字中，目前只处理16进制数
	string convert_scale(
		string num,
		unsigned int digits) const;

	// 将十六进制的字符转换为4位二进制字符串
	string convert_hex_to_binary(char c) const;

	// 计算offset
	int calculate_offset(int src, int trg) const;

	// 打印警告日志
	void log_warning(const string &info) const;

private:
	// 要进行转换的代码
	vector<string> m_codes;

	// 目标代码
	vector<string> m_machine_codes;

	// 中断处理程序的地址
	map<string, unsigned int> m_interrupt_address;

	// 寄存器映射表，由通俗名称到具体对应的数字的映射，如$zero->0
	typedef pair<string, unsigned int> RegisterPair;
	map<string, unsigned int> m_registers;

	// func码的映射表
	typedef pair<string, string> FuncCodePair;
	map<string, string> m_func_codes;

	// op码的映射表
	typedef pair<string, string> OpCodePair;
	map<string, string> m_op_codes;

	// label到地址的映射表
	typedef pair<string, unsigned int> LabelAddrPair;
	map<string, unsigned int> m_labels;

	// 缺失label的指令
	map<string, vector<LackInfo*>> m_lack_infos;
};

