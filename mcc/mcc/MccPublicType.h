/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#ifndef MCC_PUBLIC_TYPE_H
#define MCC_PUBLIC_TYPE_H

#include <string>
#include <map>
using std::string;
using std::map;

enum TYPE_SPEC {
	VOID_TYPE_SPEC,
	INT_TYPE_SPEC
};

enum BINARY_OPERATOR {
	OR_BINARY, // ||
	EQ_BINARY, // ==
	NE_BINARY, // !=
	LE_BINARY, // <=
	LT_BINARY, // <
	GE_BINARY, // >=
	GT_BINARY, // >
	AND_BINARY, // &&
	PLUS_BINARY, // +
	MINUS_BINARY, // -
	MULT_BINARY, // *
	DIV_BINARY, // /
	MD_BINARY, // %
	BIT_AND_BINARY, // &
	EXCLUSIVE_BINARY, // ^
	LSHIFT_BINARY, // <<
	RSHIFT_BINARY, // >>
	BIT_OR_BINARY, // |
};

enum UNARY_OPERATOR {
	NOT_UNARY, // !
	PORT_UNARY, // $
	NEGATIVE_UNARY, // -
	POSITIVE_UNARY, // +
	NEG_UNARY // ~
};

enum IdentifierType {
	NOMARL_VAR,
	PARAMETER_VAR,
	ARRAY_VAR,
	FUNC
};

class IdentifierInfo
{
public:
	int position;
	IdentifierType id_type;
	void *scope;
};

typedef map<string, IdentifierInfo*> IdentifierMap;

#endif // MCC_PUBILC_TYPE_H