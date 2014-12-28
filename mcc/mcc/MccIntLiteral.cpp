#include "MccIntLiteral.h"
#include "MccRobot.h"
#include "Utility.h"


MccIntLiteral::MccIntLiteral(int value)
	: m_value(value)
{
	
}


MccIntLiteral::~MccIntLiteral(void)
{
}


int MccIntLiteral::get_value() const
{
	return this->m_value;
}


int MccIntLiteral::generate_code() const
{
	MccRobot &robot = theMccRobot();
	string &code_buffer = robot.get_code_buffer();
#ifdef DEBUG_MODE
	code_buffer += "MccIntLiteral generation.\n";
#endif
	if (m_value >= -32768 && m_value <= 32767) {
		// [-2^15, 2^15-1]
		code_buffer += Utility::string_concat_int(
			"addu $v0 $v0 ", m_value) + "\n";
		robot
			.add_code(Utility::string_concat_int("addu $v0, $zero, ", m_value));
	} else {
		// Calculate two parts.
		// Convert value to hexadecimal number.
		char hex_value[9] = {0};
		sprintf(hex_value, "%08X", m_value & 0xFFFFFFFF);
		string higher_bits;
		string lower_bits;
		higher_bits += hex_value[0];
		higher_bits += hex_value[1];
		higher_bits += hex_value[2];
		higher_bits += hex_value[3];
		lower_bits += hex_value[4];
		lower_bits += hex_value[5];
		lower_bits += hex_value[6];
		lower_bits += hex_value[7];

		code_buffer += 
			"ori $v0 $zero 0x" + lower_bits + "\n"
			"lui $v1 " + higher_bits + "\n"
			"addu $v0 $v0 $v1\n";

		robot
			.add_code("ori $v0, $zero, 0x" + lower_bits)
			.add_code("lui $v1, " + higher_bits)
			.add_code("addu $v0, $v0, $v1");
	}

	return 0;
}
