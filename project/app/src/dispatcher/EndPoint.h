/*
 * EndPoint.h
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_DISPATCHER_ENDPOINT_H_
#define SRC_DISPATCHER_ENDPOINT_H_
#include <string>

#include "../mongoose/mongoose.h"

using namespace std;

class EndPoint {
private:
	EndPoint * next;
	string expression;
	string uri;
public:
	EndPoint(string u);
	void setNext(EndPoint *);
	void handle(string & uri);
	virtual ~EndPoint();
};

#endif /* SRC_DISPATCHER_ENDPOINT_H_ */
