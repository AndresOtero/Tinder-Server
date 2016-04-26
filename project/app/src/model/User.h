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
#include <json/json.h>

using namespace std;


/**
 * @class User
 * Represents a user of the DB.
 *
 * @author MLuraschi
 *
 */
class User {
public:
	/**
	 * Constructor that sets the user in a valid state.
	 *
	 * @param id of the user to represent.
	 * @param name of the user to represent.
	 * @param alias of the user to represent.
	 * @param email of the user to represent.
	 * @param sex of the user to represent.
	 * @param age of the user to represent.
	 * @param photoURL of the user to represent.
	 * @param interests of the user to represent. Stored with the categories as keys an the values in the set.
	 * @param location of the user to represent.
	 *
	 */
	User(int id, string name, string alias, string email, string sex, int age, string photoURL,
		unordered_map<string, set<string>> interests , Location location);

	/**
 	* From Json Creation
 	*
	* @param value a user json representation
	*
	*/
	User (Json::Value & value);

	virtual ~User();

	/**
	 * Returns de id of the user.
	 */
	int getId();

	/**
	 * Returns the name of the user;
	 */
	string getName();

	/**
	 * Return the alias of the user.
	 */
	string getAlias();

	/**
	 * Returns the email of the user.
	 */
	string getEmail();

	/**
	 * Returns the url of the profile photo of the user
	 */
	string getPhotoURL();

	/**
	 * Returns last known latitude of the user
	 */
	double getLatitude();

	/**
	 * Returns las known longtude of the user.
	 */
	double getLongitude();

	/**
	 * Changes the name of the user.
	 *
	 * @param name new value to set.
	 */
	void setName(string name);

	/**
	 * Changes the alias of the user.
	 *
	 * @param alias new value to set.
	 */
	void setAlias(string alias);

	/**
	 * Changes the email of the user.
	 *
	 * @param email new value to set.
	 */
	void setEmail(string email);

	/**
	 * Changes the name of the user.
	 *
	 * @param name new value to set.
	 */
	void setPhotoURL(string url);

	/**
	 * Changes the latitude of the user.
	 *
	 * @param latitude new value to set.
	 */
	void setLatitude(double latitude);

	/**
	 * Changes the longitude of the user.
	 *
	 * @param longitude new value to set.
	 */
	void setLongitude(double longitude);

	/**
	 * Changes the id of the user. WARNING Use only when uploading a new user.
	 *
	 * @param id new value to set.
	 */
	void setId(int id);

	/**
	 * Returns the insterests of the user
	 */
	unordered_map<string, set<string>> getInterests();

	/**
	 * Changes the sex of the user.
	 *
	 * @param sex new value to set.
	 */
	void setSex(string sex);

	/**
	 * Changes the age of the user.
	 *
	 * @param age new value to set.
	 */
	void setAge(int age);

	/**
	 * Returns the age of the user
	 */
	int getAge();

	/**
	 * Returns the sex of the user.
	 */
	string getSex();

	/**
	 * Return json Representation;
	 */
	Json::Value toJson();


	/**
	 *
	 */
	static unordered_map<string, set<string>> populateInterests(Json::Value &root);
private:
	int age;
	string sex;
	int id;
	string name;
	string alias;
	string email;
	string photoURL;
	unordered_map<string, set<string>> interests;
	Location location;

};

#endif /* SRC_USER_H_ */
