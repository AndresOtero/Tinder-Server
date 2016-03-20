/*
 * EndPoint.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include <dispatcher/EndPoint.h>

EndPoint::EndPoint() {
	// TODO Auto-generated constructor stub

}

void EndPoint::setNext(EndPoint* next) {
 if(this->next == 0) {
	 this->next = next;
 } else {
	 this->next->setNext(next);
 }
}

EndPoint::~EndPoint() {
	if(this->next != 0) {
		delete this->next;
	}
}

