/*
 * Connector.h
 *
 *  Created on: Jul 1, 2016
 *      Author: Ari Suarkadipa
 */

#ifndef INC_CONNECTOR_H_
#define INC_CONNECTOR_H_

#include "../../PocoMongoIncludes.h"
#include "../../Common/Filter.h"
#include "Website.h"

using namespace Poco;
using namespace DB::Common;

namespace DB
{
/**
 * Class Connector is a DAO Layer using MongoDB
 */
class Connector
{
public:

	Connector() {};
	virtual ~Connector() {};
	/**
	 * Insert Website to MongoDB
	 *
	 * @param website a website data to insert
	 */
	void Insert(Website &website);

	/**
	 * Update MongoDB
	 *
	 * @param whereColumn a column
	 * @param whereValue a condition
	 * @param newValue a new value
	 */
	void Update(string whereColumn, string whereValue, string newValue);

	/**
	 * Delete record on MongoDB
	 *
	 * @param filters a filter
	 */
	void Delete(vector<DB::Common::Filter> &filters);

	/**
	 * Show all records from MongoDB
	 */
	void showAll();

	/**
	 * Get all record from MongoDB
	 *
	 * @param response a response
	 * @return template a template
	 */
	template<typename T>
	vector<T> GetAll(MongoDB::ResponseMessage &response);

	/**
	 * Check the record is Database
	 *
	 * @param content a content to search
	 */
	bool checkIsExist(string content);

	/**
	 * Create filter used for delete method
	 *
	 * @param selectedColumn
	 * 1 is content
	 * 2 is protocolType
	 *
	 * @param selectedOpr is selected operator
	 * 1. Equal
	 * 2. Not Equal
	 * 3. Greater
	 * 4. Greater Than Equals
	 * 5. Less Than
	 * 6. Less Than Equal
	 * 7. In
	 * 8. Not In
	 *
	 * @param value is a value criteria to delete
	 *
	 * @return Filter
	 */
	Filter createFilter(int selectedColumn, int selectedOpr, string value);

private:
	const string _host = "localhost";
	const int _port = 27017;
	const string _dbName = "SpiderBite";
	const string _collectionName = "Website";
};

} // namespace DB



#endif /* INC_CONNECTOR_H_ */
