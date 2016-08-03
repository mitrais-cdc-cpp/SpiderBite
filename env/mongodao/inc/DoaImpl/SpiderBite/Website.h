/*
 * Website.h
 *
 *  Created on: Jul 4, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef INC_WEBSITE_H_
#define INC_WEBSITE_H_

#include <ctime>

using namespace std;

namespace DB
{

struct Website
{
	string 	protocolType;
	string 	url;
	string 	content;
	time_t 	createdDate;
	time_t 	lastUpdated;
};

} //namespace DB

#endif /* INC_WEBSITE_H_ */
