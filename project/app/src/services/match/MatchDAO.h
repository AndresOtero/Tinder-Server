//
// Created by matias on 4/15/16.
//

#ifndef TINDER_SERVER_MATCHDAO_H
#define TINDER_SERVER_MATCHDAO_H

#include <DBConnector.h>
#include <json/json.h>

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
	 * @param username is the name of the user that liked the other.
	 * @param userid is the id of the user that liked the other.
	 * @param match is the name of the user that was liked by username.
	 * @param matchid is the id of the user that was liked by the username.
	 */
	bool saveLike(string username, string userid, string match, string matchid);

	/**
	 * Returns the number of likes that a user has received.
	 * @param username is the name of the user to retrieve the number of likes he has received.
	 * @param id is the id of the user you want to get the number of likes.
	 */
	int getNumberOfLikes(string username, string id);

	/**
	 * Returns the number of users the number of matches a user has.
	 * @param username is the name of the user to retrieve the number of matches he has.
	 * @param id is the id of the user you want to get.
	 */
	int getNumberOfMatches(string username, string id);

	/**
	 * Returns a Json::Value with all the users that have matched the requested user.
	 * @param username is the name of the user to retrieve the  matches he has.
	 * @param id is the id of the user you want to get.
	 */
	Json::Value getMatches(string username, string id);

	/**
	 * Checks if the username A liked username B before.
	 * @param usernameA username of userA
	 * @param idA id of the username A
	 * @param usernameB username of the second user.
	 * @param idB id of the second username.
	 */
	bool checkForLike(string usernameA, string idA, string usernameB, string idB);

	/**
	 * Checks if the username A and B have matched.
	 * @param usernameA username of userA
	 * @param idA id of the username A
	 * @param usernameB username of the second user.
	 * @param idB id of the second username.
	 */
	bool checkForMatch(string usernameA, string idA, string usernameB, string idB);

private:
	DBConnector* connector;
	string assembleKey(string username, string id);

	void addMatch(string usernameA, string idA, string usernameB, string idB);
};


#endif //TINDER_SERVER_MATCHDAO_H
