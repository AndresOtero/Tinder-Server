/*
 * DBConnector.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#include "DBConnector.h"

DBConnector::DBConnector(std::string dbName) {
	rocksdb::Options options;
	options.create_if_missing = true;
	this->openedDB = dbName;
	this->status = rocksdb::DB::Open(options, this->openedDB , &this->db);
}

DBConnector::~DBConnector() {
	delete this->db;
}

bool DBConnector::isOk() {
	if (this->status.ok()) {
		return true;
	}
	return false;
}

