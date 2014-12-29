#pragma once

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;
using std::pair;


/**
 * MiniC��������Ӧ�������
 *
 * @ע��
 *	1. ��Ϊ������Ϊmcc�ĺ�ˣ����������
 *	2. ��ʽ�ϵ�Ҫ����ܻ�ȽϿ��̡�
 */
class MccAssembler
{
public:
	MccAssembler();
	~MccAssembler();
	
	// һϵ�г�ʼ��������������ʼ�������õ���ֵ
	// ��ʼ���Ĵ�����ӳ���
	void init_registers();

	// ��ʼ��func��
	void init_func_codes();


	// ɨ����룬����ת��
	void scan();

	// һϵ�еĴ�����
	// ����label
	void deal_label(const string &code);

	// ����ָ��
	void deal_instruction(const string &code);


	// һϵ�е����ɷ���
	/**
	 * @brief ����R���͵�ָ��Ļ����롣
	 *
	 * @param name ָ������֣���add��
	 *
	 * @param operands ָ��ʹ�õĲ�������ȫ���������һ��
	 *
	 * @return ���ɵĻ����롣
	 */
	string generate_r_instruction(
		const string &name, 
		const string &operands) const;

	// ��������
	/**
	* @brief ��','���и������
	*
	* @param str ���и���ַ���
	*
	* @param operands �и����Ĳ�����
	*/
	void split_operands(
		const string &str, 
		vector<string> &operands) const;

	// ����ָ���Ӧ��func����
	string get_func_code(const string &name) const;

	// ���ҼĴ�����Ӧ�Ĵ���
	string get_register_code(const string &reg) const;

	// ��ӡ������־
	void log_warning(const string &info) const;
	
private:
	// Ҫ����ת���Ĵ���
	vector<string> m_codes;

	// Ŀ�����
	vector<string> m_machine_codes;

	// �Ĵ���ӳ�����ͨ�����Ƶ������Ӧ�����ֵ�ӳ�䣬��$zero->0
	typedef pair<string, unsigned int> RegisterPair;
	map<string, unsigned int> m_registers;

	// func���ӳ���
	typedef pair<string, string> FuncCodePair;
	map<string, string> m_func_codes;
};

