//
// Created by matias on 4/24/16.
//

#include <ctime>
#include <iomanip>
#include "MatchServices.h"
#include "NoMoreCandidatesException.h"

using namespace std;

MatchServices::MatchServices(MatchDAO *matchDAO, ProfileServices *profile) {
	this->matchDao = matchDAO;
	this->profileServices = profile;
}

MatchServices::~MatchServices() { }

void MatchServices::likeAUser(User *userA, User *userB) {
	if (this->matchDao->checkForLike(userA, userB)) return;
	this->matchDao->saveLike(userA, userB);
	if (this->matchDao->checkForLike(userB, userA)) this->matchDao->addMatch(userA, userB);
}


int MatchServices::getNumberOfLikes(User *user) {
	return this->matchDao->getNumberOfLikes(user);
}

int MatchServices::getNumberOfMatches(User *user) {
	return this->matchDao->getNumberOfMatches(user);
}


list<User *> MatchServices::getMatchesForUser(User *user) {
	list<string> listaIDs = this->matchDao->getMatches(user);
	return this->getUsersFromIDs(listaIDs);
}


list<User *> MatchServices::getLikesForUser(User *user) {
	list<string> listaIDs = this->matchDao->getLikes(user);
	return this->getUsersFromIDs(listaIDs);
}

list<User *> MatchServices::getCandidatesForUser(User *user) {
	if (!this->hasRemainingCandidates(user)) throw NoMoreCandidatesException("Already requested candidates today.");
	auto lista = this->profileServices->getAllUsers();
	set<User*> remaining;
	for (auto itr= lista.begin(); itr != lista.end(); ++itr) {
		if(*itr != user) remaining.insert(*itr);
		else delete *itr;
	}
	auto alreadyLiked = this->getLikesForUser(user);
	for (auto otheritr = alreadyLiked.begin(); otheritr != alreadyLiked.end(); ++otheritr){
		std::set<User*>::iterator found = remaining.find(*otheritr);
		if (found != remaining.end()) {
			User* todelete = *found;
			remaining.erase(found);
			delete todelete;
		}
		delete *otheritr;
	}
	std::list<User*> candidates = this->assembleListFromSet(remaining);
	return candidates;
}

list<User*> MatchServices::assembleListFromSet(set<User*> toConvert) {
	std::list<User*> lista;
	for (auto itr=toConvert.begin(); itr!=toConvert.end(); ++itr) {
		lista.push_back(*itr);
	}
	return lista;
}

bool MatchServices::hasRemainingCandidates(User* user) {
	tm* lastDateStruct = this->matchDao->getLastRequestTime(user);
	time_t currentDay = time(NULL);
	struct tm* timeStruct = localtime(&currentDay);
	bool igualDia = timeStruct->tm_mday == lastDateStruct->tm_mday;
	bool igualAnio = timeStruct->tm_year == lastDateStruct->tm_year;
	bool igualMes = timeStruct->tm_mon == lastDateStruct->tm_mon;
	free(lastDateStruct);
	return  !(igualDia && igualAnio && igualMes);
}

list<User*> MatchServices::getUsersFromIDs(list<string> &ids) {
	std::list<User*> listaUsers;
	for (auto itr = ids.begin(); itr != ids.end(); ++itr) {
		listaUsers.push_back(this->profileServices->getUserByID(*itr));
	}
	return listaUsers;
}



