/*
 * PathVariableExtractor.h
 *
 *  Created on: 20 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_DISPATCHER_PATHVARIABLEEXTRACTOR_H_
#define SRC_DISPATCHER_PATHVARIABLEEXTRACTOR_H_
#include <string>
#include <map>
using namespace std;


class PathVariableExtractor {
private:
	map<string, string> params;
public:
	PathVariableExtractor(string format, string path);
	virtual ~PathVariableExtractor();
	string get(string param);
};

#endif /* SRC_DISPATCHER_PATHVARIABLEEXTRACTOR_H_ */
