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
		const string replace = "([^\\/]+)";
		this->expression = "^" + regex_replace(u, exp ,replace) + "$" ;
}

void EndPoint::setNext(EndPoint* next) {
 if(this->next == 0) {
	 this->next = next;
 } else {
	 this->next->setNext(next);
 }
}

/** \brief getAccounts - inputs accounts from the keyboard
 * \details This function reads input from the keyboard.
 * For every S or C entered, the function creates a new
 * Savings or Checking account object and adds it to the
 * account list. An X terminates the entry. Any other
 * input is assumed to be a deposit (numbers greater than
 * 0) or a withdrawal (numbers less than 0).
 *
 * \param accList list<AccountPtr>& the list of account
 *                objects created by getAccounts()
 * \return void
 */
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

