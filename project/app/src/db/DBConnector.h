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
	std::string openedDB;
	DBConnector(std::string dbName);
	virtual ~DBConnector();
	bool isOk();

private:
	rocksdb::DB* db;
	rocksdb::Status status;
};

#endif /* SRC_DBCONNECTOR_H_ */
