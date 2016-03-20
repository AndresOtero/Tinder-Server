/*
 * EndPoint.h
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#ifndef SRC_DISPATCHER_ENDPOINT_H_
#define SRC_DISPATCHER_ENDPOINT_H_

class EndPoint {
private:
	EndPoint * next;
public:
	EndPoint();
	void setNext(EndPoint *);
	virtual ~EndPoint();
};

#endif /* SRC_DISPATCHER_ENDPOINT_H_ */
