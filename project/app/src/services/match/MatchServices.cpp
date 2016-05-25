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
	this->dailyLimit = 10;
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
	auto alreadyLiked = this->getLikesForUser(user);
	std::list<Candidate*> candidates;
	for (auto itr= lista.begin(); itr != lista.end(); ++itr) {
		if((*itr)->getId() != user->getId() && !this->findInList(alreadyLiked, (*itr))) {
			candidates.push_back(new Candidate(*itr));
		}
		else delete *itr;
	}
	this->getCandidatesScores(candidates, user);
	candidates.sort([] (const Candidate* first, const Candidate* second) {
		return ( first->score < second->score );
	});
	this->matchDao->updateLastMatchRequest(user);
	return this->getUserListFromCandidates(candidates);
}

void MatchServices::getCandidatesScores(std::list<Candidate*> &lista, User* user) {
	for (auto it = lista.begin(); it != lista.end() ; ++it) {
		(*it)->numLiked = this->matchDao->getNumLiked((*it)->getUser());
		(*it)->score = this->getCommonInterests((*it)->getUser(), user) * 3 - (*it)->numLiked;
	}
}

int MatchServices::getCommonInterests(User* userA, User* userB) {
	std::list<Interest*> intereses = userA->getInterests();
	int contador = 0;
	for (auto it = intereses.begin(); it != intereses.end(); ++it) {
		if (userB->likesInterest(*it)) contador++;
	}
	return contador;
}

list<User*> MatchServices::getUserListFromCandidates(std::list<Candidate*> candidatos) {
	std::list<User*> toReturn;
	int contador = 0;
	for (auto itr=candidatos.begin(); itr!=candidatos.end() && contador < this->dailyLimit; ++itr) {
		toReturn.push_back((*itr)->getUser());
		contador++;
	}
	return toReturn;
}

bool MatchServices::findInList(std::list<User*> likes, User* tofind) {
	for(auto itr = likes.begin(); itr != likes.end(); ++itr) {
		if ((*itr)->getId() == tofind->getId()) return true;
	}
	return false;
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



