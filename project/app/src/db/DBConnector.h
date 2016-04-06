/*
 * DBConnector.h
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#ifndef SRC_DBCONNECTOR_H_
#define SRC_DBCONNECTOR_H_

#include "rocksdb/db.h"
#include <string>

class DBConnector {
public:
	rocksdb::DB* db;
	std::string openedDB;
	DBConnector(std::string dbName);
	virtual ~DBConnector();
	bool isOk();
	bool deleteKey(std::string key);
	bool getValueForKey(std::string key, std::string& value);
	bool putValueInKey(std::string key, std::string value);

private:
	rocksdb::Status status;
};

#endif /* SRC_DBCONNECTOR_H_ */
