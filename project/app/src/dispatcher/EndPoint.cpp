/*
 * EndPoint.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "EndPoint.h"
#include <regex>
#include <iostream>
using namespace std;


EndPoint::EndPoint(string u) {

		this->uri = u;
		this->next = 0;
		regex exp ("#[^\\/]+#");
		string const group =  "([^\\/]+)";
		this->expression = "^" + regex_replace(u, exp , group) + "$" ;

}

void EndPoint::setNext(EndPoint* next) {
 if(this->next == 0) {
	 this->next = next;
 } else {
	 this->next->setNext(next);
 }
}

void EndPoint::handle(string & uri) {
	regex exp (this->expression);
	if(regex_match(uri, exp)) {
		cout<<"match"<<endl;
	}

}

EndPoint::~EndPoint() {
	if(this->next != 0) {
		delete this->next;
	}
}

