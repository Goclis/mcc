#pragma once

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;
using std::pair;


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

	// 一系列的处理方法
	// 处理label
	void deal_label(const string &code);

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
		const string &operands_str) const;

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

	// 打印警告日志
	void log_warning(const string &info) const;
	
private:
	// 要进行转换的代码
	vector<string> m_codes;

	// 目标代码
	vector<string> m_machine_codes;

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
	
};

