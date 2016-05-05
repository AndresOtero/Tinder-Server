//
// Created by matias on 4/24/16.
//

#ifndef TINDER_SERVER_MATCHSERVICES_H
#define TINDER_SERVER_MATCHSERVICES_H


#include <UserDAO.h>
#include "MatchDAO.h"

/**
 * @class MatchServices
 * Provides de required methods to resolve match related requests.
 */
class MatchServices {
public:
	/**
	 * Default Constructor.
	 * @param matchDao DAO to use to get the information from matches.
	 * @param userDAO DAO to use to get information from users.
	 */
	MatchServices(MatchDAO* matchDAO, UserDAO* userDAO);
	virtual ~MatchServices();

	/**
	 * Method to be called when a user likes other. If the had previously liked each other, the like is not added. If
	 * the other user has already liked him, a match is added.
	 * @param userA user that just liked other
	 * @param userB user that was liked by userA
	 */
	void likeAUser(User* userA, User* userB);

	/**
	 * Returns a list with all the matches that a user has. The caller has to delete the users.
	 */
	list<User*> getMatchesForUser(User* user);

	/**
	 * Returns a list with all the likes that a user has. The caller has to delete the users.
	 */
	list<User*> getLikesForUser(User* user);

	/**
	 * Returns a list of all the candidate the user has today. If he has already requested the list today,
	 * NoMoreCandidatesException is raised. The caller has to delete the users.
	 */
	list<User*> getCandidatesForUser(User* user);

	/**
	 * Returns the number of likes that the user has.
	 * @param user user to get the number of likes.
	 */
	int getNumberOfLikes(User* user);

	/**
	 * Returns the number of matches that the user has.
	 * @param user user to get the number of matches.
	 */
	int getNumberOfMatches(User* user);

private:
	MatchDAO* matchDao;
	UserDAO* userDao;
	bool hasRemainingCandidates(User* user);
};


#endif //TINDER_SERVER_MATCHSERVICES_H
