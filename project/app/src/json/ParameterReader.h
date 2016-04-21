/*
 * ParameterReader.h
 *
 *  Created on: 9 de abr. de 2016
 *      Author: jonathan
 */

#ifndef APP_SRC_JSON_PARAMETERREADER_H_
#define APP_SRC_JSON_PARAMETERREADER_H_
#include <string>
#include "json/json.h"
#include <functional>
using namespace std;


/**
 * @class ParameterReader
 *
 * Generic reader to access a json object
 * @return the Request
 */

template<class T>
class ParameterReader {
protected:
	Json::Value root;
	virtual T get(string key, bool required, function<T(Json::Value & value)> converter) {
		Json::Value value = root[key];
		Json::FastWriter as;
		if(value != Json::nullValue) {
			return converter(this->root);
		} else {
			if(required) {
				throw "Null value : " + key;
			}
			return T();
		}
	}

public:
	/**
	 * Constructor
	 * @param Json from where read.
	 */
	ParameterReader(Json::Value value){
		this->root = value;
		Json::FastWriter as;

	};
	virtual ~ParameterReader() {};

	/**
	 * Getter of value, validating if empty
	 * @return the value
	 * @throws an string with a description
	 */

	T get(string key, bool required) {
		return this->get(key, required, [key] (Json::Value & val) {return val[key];});
	}

};

/**
 * @class StringReader
 *
 * Reader for string value
 * @return the Request
 */
class StringReader: public ParameterReader<string> {
public:
	StringReader(Json::Value value) :	ParameterReader(value) {};
	virtual ~StringReader() {};
	string get(string key, bool required) {
		function<string (Json::Value & value)> converter = [key] (Json::Value & val) {
			return val[key].asString();
		};
		return ParameterReader::get(key, required, converter);
	}
};

/**
 * @class BoolReader
 *
 * Reader for boolean value
 * @return the Request
 */

class BoolReader: public ParameterReader<bool> {
public:
	BoolReader(Json::Value value) :	ParameterReader(value) {};
	virtual ~BoolReader() {};
	bool get(string key, bool required) {
		function<bool(Json::Value & value)> converter = [key] (Json::Value & val) {
			return val[key].asBool();
		};
		return ParameterReader<bool>::get(key, required, converter);
	}
};

/**
 * @class IntReader
 *
 * Reader for int value
 * @return the Request
 */

class IntReader: public ParameterReader<int> {
public:
	IntReader(Json::Value value) :	ParameterReader(value) {};
	virtual ~IntReader() {};
	int get(string key, bool required) {
		function<int (Json::Value & value)> converter = [key] (Json::Value & val) {
			return val[key].asInt();
		};
		return ParameterReader<int>::get(key, required, converter);
	}
};

#endif /* APP_SRC_JSON_PARAMETERREADER_H_ */
