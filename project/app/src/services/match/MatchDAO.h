//
// Created by matias on 4/15/16.
//

#ifndef TINDER_SERVER_MATCHDAO_H
#define TINDER_SERVER_MATCHDAO_H

#include <DBConnector.h>
#include <json/json.h>
#include <User.h>

using namespace std;
/**
 * @class MatchDAO
 * Data access object that provides functionality to save and retrieve matches.
 */
class MatchDAO {

public:
	/**
	 * Default constructor.
	 *
	 * @param connector DBConnector to the db that contains the matches.
	 */
	MatchDAO(DBConnector* connector);
	virtual ~MatchDAO();

	/**
	 * Saves the match in the db. Returns true if the like was stored successfully.
	 * @param user is the user that just liked another one.
	 * @param liked is user that first user liked.
	 */
	bool saveLike(User* user, User* liked);

	/**
	 * Returns the number of likes that a user has received.
	 * @param user user to get the number of likes he did.
	 */
	int getNumberOfLikes(User* user);

	/**
	 * Returns the number of users the number of matches a user has.
	 * @param user to get the number of matches he has.
	 */
	int getNumberOfMatches(User* user);

	/**
	 * Returns a Json::Value with all the users that have matched the requested user.
	 * @param user is the user to retrieve the  matches he has.
	 */
	Json::Value getMatches(User* user);

	/**
	 * Checks if the username A liked username B before.
	 * @param userA is the user we want to know if he has liked B or not.
	 * @param userB is the user we want to know if was liked before.
	 */
	bool checkForLike(User* userA, User* userB);

	/**
	 * Checks if the username A and B have matched.
	 * @param userA one of the users to know if they match
	 * @param userB the other user
	 */
	bool checkForMatch(User* userA, User* userB);

private:
	DBConnector* connector;

	void addMatch(User* a, User* b);
};


#endif //TINDER_SERVER_MATCHDAO_H
