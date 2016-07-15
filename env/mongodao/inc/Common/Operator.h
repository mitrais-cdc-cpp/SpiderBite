#ifndef INC_OPERATOR_H_
#define INC_OPERATOR_H_


namespace DB {
namespace Common {

enum class Operator{
	EQUALS,
	NOT_EQUALS,
	GREATER_THAN,
	GREATER_THAN_EQUALS,
	LESS_THAN,
	LESS_THAN_EQUALS,
	IN,
	NOT_IN
};

}}


#endif /* INC_OPERATOR_H_ */
