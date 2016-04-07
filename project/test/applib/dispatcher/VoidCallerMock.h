/*
 * VoidCallerMock.h
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#ifndef TEST_APPLIB_DISPATCHER_VOIDCALLERMOCK_H_
#define TEST_APPLIB_DISPATCHER_VOIDCALLERMOCK_H_
#include <gmock/gmock.h>

class VoidCallerInterface {
public:
	VoidCallerInterface();
	virtual ~VoidCallerInterface();
	virtual void call() = 0;
};

class VoidCallerConcrete {
public:
	VoidCallerConcrete();
	virtual ~VoidCallerConcrete();
	MOCK_METHOD0(call, void());
};


#endif /* TEST_APPLIB_DISPATCHER_VOIDCALLERMOCK_H_ */
