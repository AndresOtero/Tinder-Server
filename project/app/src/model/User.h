/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_USER_H_
#define SRC_USER_H_

#include "Location.h"
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

class User {
public:
	User(string id, string name, string alias, string email, string photoURL, 
		unordered_map<string, set<string>> interests , Location location);

	virtual ~User();
	string getId();
	string getName();
	string getAlias();
	string getEmail();
	string getPhotoURL();
	double getLatitude();
	double getLongitude();
	void setName(string name);
	void setAlias(string alias);
	void setEmail(string email);
	void setPhotoURL(string url);
	void setLatitude(double latitude);
	void setLongitude(double longitude);
	void setId(string id);
	unordered_map<string, set<string>> getInterests();

private:
	string id;
	string name;
	string alias;
	string email;
	string photoURL;
	unordered_map<string, set<string>> interests;
	Location location;

};

#endif /* SRC_USER_H_ */
