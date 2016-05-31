//
// Created by matias on 4/24/16.
//

#ifndef TINDER_SERVER_MATCHSERVICES_H
#define TINDER_SERVER_MATCHSERVICES_H

#include <User.h>
#include <ProfileServices.h>
#include "MatchDAO.h"
#include "Candidate.h"


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
	MatchServices(MatchDAO* matchDAO, ProfileServices* profile);
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
	 * Returns a list with the candidaes for the user. The list will have cantidad number of candidates or ,if less are
	 * remaining, the remaining amount. If no more candidates are available, NoMoreCandidatesException is Thrown. Users
	 * in the list must be deleted by the caller.
	 * @param user user to get the candidates for.
	 * @param cantidad quantity of candidates to get.
	 * @param distance maximum distance in kms for the candidates.
	 */
	list<User*> getCandidatesForUser(User* user, int cantidad,int distance);

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
	ProfileServices* profileServices;
	int dailyLimit;

	bool findInList(list<User*> likes, User* tofind);
	bool hasRemainingCandidates(User* user);
	list<User*> getUsersFromIDs(list<string> &ids);
	list<User*> getUserListFromCandidates(std::vector<Candidate*> candidatos, int distance);
	void getCandidatesScores(std::list<Candidate*> &lista, User* user);
	int getCommonInterests(User* userA, User* userB);
	double deg2rad(double deg);
	double rad2deg(double rad);
	void getCandidatesDistance(list<Candidate*> candidates, User* user);
	int getRemainingAmountOfCandidates(User* user);
	std::vector<Candidate *> filtrarLista(std::list<Candidate*> toFilter);

	/**
	 * Returns the distance between two points on the Earth.
	 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
	 * @param lat1d Latitude of the first point in degrees
	 * @param lon1d Longitude of the first point in degrees
	 * @param lat2d Latitude of the second point in degrees
	 * @param lon2d Longitude of the second point in degrees
	 * @return The distance between the two points in kilometers
	 */
	double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
};


#endif //TINDER_SERVER_MATCHSERVICES_H
