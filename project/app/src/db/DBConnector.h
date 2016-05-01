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

/**
 * @class DBConnector
 * It provides the necessary methods to access RocksDB, save and retrieve information.
 */
class DBConnector {
public:
	rocksdb::DB* db;

	/**
	 * Name of the opened DB.
	 */
	std::string openedDB;

	/**
	 * Default constructor.
	 *
	 * @param dbName name of the db to be opened. If it is not found, it is created.
	 */
	DBConnector(std::string dbName);
	virtual ~DBConnector();

	/**
	 * Returns true if the db is opened and ready to be used. False if not.
	 */
	bool isOk();

	/**
	 * Deletes the key received from the DB. It returns true if the operation was successful, false if no.
	 *
	 * @param key to delete from the db.
	 */
	void deleteKey(std::string key);

	/**
	 * Retrieves the value stored in the given key. It returns true if the operation was successful, false if not.
	 *
	 * @param key to search for in the DB.
	 * @param value the value stored in the db is saved here.
	 */
	std::string getValueForKey(std::string key);

	/**
	 * Saves the given value in the given key. If the key already exists, it overwrites the value stored.
	 *
	 * @param key to store the value in.
	 * @param value to be stored in the given key.
	 */
	void putValueInKey(std::string key, std::string value);

	bool exist(std::string key);
private:
	rocksdb::Status status;
};

#endif /* SRC_DBCONNECTOR_H_ */
