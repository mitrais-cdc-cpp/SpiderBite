/*
 * Filter.h
 *
 *  Created on: Jul 4, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include "Operator.h"

namespace DB {
namespace Common {

struct Filter
{
	std::string field;
	std::string value;
	Operator op;
};

}}

#endif /* INC_FILTER_H_ */
