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
	 * Saves the match in the db.
	 * @param user is the user that just liked another one.
	 * @param liked is user that first user liked.
	 */
	void saveLike(User *user, User *liked);

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
	 * Returns a list of strings with the ids of all the users that have matched the requested user.
	 * @param user is the user to retrieve the  matches he has.
	 */
	list<string> getMatches(User* user);

	/**
	 * Returns a list of strings with the id of all the users that the requested user has liked.
	 * @param user is the user to retrieve the  matches he has.
	 */
	list<string> getLikes(User* user);

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

	/**
	 * Adds a match between the two users. It does not check if they like each other or not.
	 *
	 * @param a first user.
	 * @param b second user.
	 */
	void addMatch(User* a, User* b);

	/**
	 * Returns the date date when the user last requested for candidates. The tm* has to be freed by the caller.
	 *
	 * @param user user to get the last day for.
	 */
	tm* getLastRequestTime(User *user);

	/**
	 * Returns the number of times that the user was liked.
	 * @param user the user to check how many likes he got.
	 */
	int getNumLiked(User* user);

	/**
	 * Updates the last time of the last request from the user to today.
	 *
	 * @param user user to update the last request time.
	 */
	void updateLastMatchRequest(User* user);
private:
	DBConnector* connector;
	void initializeUserEntry(User* user);
	Json::Value getUserEntry(User* user);
};


#endif //TINDER_SERVER_MATCHDAO_H
