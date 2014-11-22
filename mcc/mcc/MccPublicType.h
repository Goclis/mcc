/**
 * @author Goclis Yao
 * @email goclisyyh@gmail.com
 */

#ifndef MCC_PUBLIC_TYPE_H
#define MCC_PUBLIC_TYPE_H

enum TYPE_SPEC {
	VOID_TYPE_SPEC,
	INT_TYPE_SPEC
};

enum BINARY_OPERATOR {

};

enum UNARY_OPERATOR {
	NOT_UNARY, // !
	PORT_UNARY, // $
	NEGATIVE_UNARY, // -
	POSITIVE_UNARY, // +
	NEG_UNARY // ~
};

#endif // MCC_PUBILC_TYPE_H