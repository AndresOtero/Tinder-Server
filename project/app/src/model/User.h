/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_USER_H_
#define SRC_USER_H_

#include "Location.h"
#include "Interest.h"
#include <string>
#include <unordered_map>
#include <set>
#include <json/json.h>
#include <list>

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
     * @param externalId of the user to represent.
     * @param email of the user to represent.
     * @param sex of the user to represent.
     * @param age of the user to represent.
     * @param photoURL of the user to represent.
     * @param interests of the user to represent. Stored with the categories as keys an the values in the set.
     * @param location of the user to represent.
     *
     */
    User(string id, string name, int externalId, string email, string sex, int age, string photoURL,
         unordered_map<string, set<string>> interests, Location location);


    User();

/**
 	* From Json Creation
 	*
	* @param value a user json representation
	*
	*/
    User(Json::Value &value);

    virtual ~User();

    /**
     * Returns de id of the user.
     */
    string getId();

    /**
     * Returns the name of the user;
     */
    string getName();

    /**
    * Returns the alias of the user;
    */
    string getAlias();

    /**
     * Return the externalId of the user.
     */
    int getExternalId();

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
     * Changes the externalId of the user.
     *
     * @param externalId new value to set.
     */
    void setExternalId(int alias);

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
    void setId(string id);

    /**
    * Setter of alias
    *
    * @param alias new value to set.
    */
    void setAlias(string alias);

    /**
     * Returns a list with interests in it. It is responsability of the caller to delete the Interests in it.
     */
    list<Interest *> getInterests();

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
     *	Converts to external user json format.
     *	@return a external json representation
     *
     */
    void toExternalJson(Json::Value &userData);

    /**
     * Read a user from a json with external user format
     * @param value json values
     */
    static User *fromExternalJson(Json::Value &value);

    static unordered_map<string, set<string>> populateInterests(Json::Value &root);

private:
    int age;
    string sex;
    string id;
    string name;
    int externalId;
    string email;
    string alias;
    string photoURL;
    unordered_map<string, set<string>> interests;
    Location location;

    static void readCommonBody(const Json::Value &values, User &user);

    static Json::Value &bodyToJson(Json::Value &userData, User &user);
};

#endif /* SRC_USER_H_ */
