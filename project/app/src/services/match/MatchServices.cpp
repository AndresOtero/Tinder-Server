//
// Created by matias on 4/24/16.
//

#include <ctime>
#include <iomanip>
#include "MatchServices.h"
#include "NoMoreCandidatesException.h"
#include <cmath>
#include <algorithm>
#include <vector>

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

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

list<User *> MatchServices::getCandidatesForUser(User *user, int cantidad,int distance) {
	if (!this->hasRemainingCandidates(user)) throw NoMoreCandidatesException("Already requested all the candidates today.");
	int cantidadRestante = this->getRemainingAmountOfCandidates(user);
	int cantidadEfectiva = cantidad;
	if (cantidad > cantidadRestante) {
		cantidadEfectiva = cantidadRestante;
	}
	auto lista = this->profileServices->getAllUsers();
	auto alreadyLiked = this->getLikesForUser(user);
	std::list<Candidate*> candidates;
	for (auto itr= lista.begin(); itr != lista.end(); ++itr) {
		if((*itr)->getId() != user->getId() && !this->findInList(alreadyLiked, (*itr))) {
			candidates.push_back(new Candidate(*itr, distance));
		}
		else delete *itr;
	}
	this->getCandidatesDistance(candidates, user);
	this->getCandidatesScores(candidates, user);
	std::vector<Candidate*> listaFinal = this->filtrarLista(candidates);
	if (listaFinal.size() < cantidadEfectiva) cantidadEfectiva = listaFinal.size();
	this->matchDao->updateLastMatchRequest(user, cantidadEfectiva);
	random_shuffle(listaFinal.begin(), listaFinal.end());
	return this->getUserListFromCandidates(listaFinal, cantidadEfectiva);
}

std::vector<Candidate *> MatchServices::filtrarLista(std::list<Candidate*> toFilter) {
	std::vector<Candidate*> filtrada;
	for (auto it = toFilter.begin(); it != toFilter.end(); ++it) {
		if ((*it)->distanceToUser <= (*it)->distanceLimit && (*it)->score > 0) {
			filtrada.push_back((*it));
		}
		else delete (*it);
	}
	return filtrada;
}

void MatchServices::getCandidatesDistance(std::list < Candidate * > candidates, User * user) {
	for (auto itr = candidates.begin(); itr!=candidates.end(); ++itr) {
		(*itr)->distanceToUser = this->distanceEarth((*itr)->getUser()->getLatitude(),
		                                             (*itr)->getUser()->getLongitude(), user->getLatitude(),
		                                             user->getLongitude());
	}
}

void MatchServices::getCandidatesScores(std::list<Candidate*> &lista, User* user) {
	for (auto it = lista.begin(); it != lista.end() ; ++it) {
		(*it)->numLiked = this->matchDao->getNumLiked((*it)->getUser());
		(*it)->score = this->getCommonInterests((*it)->getUser(), user) * 3 - (*it)->numLiked;
	}
}

int MatchServices::getCommonInterests(User* userA, User* userB) {
	std::list<Interest> intereses = userA->getInterests();
	int contador = 0;
	for (auto it = intereses.begin(); it != intereses.end(); ++it) {
		if (userB->likesInterest(*it)) contador++;
	}
	return contador;
}

list<User*> MatchServices::getUserListFromCandidates(std::vector<Candidate*> candidatos, int cantidad) {
	std::list<User*> toReturn;
	int contador = 0;
	for (auto itr=candidatos.begin(); itr!=candidatos.end() && contador < cantidad; ++itr) {
		toReturn.push_back((*itr)->getUser());
		contador++;
		delete (*itr);
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
	return (this->getRemainingAmountOfCandidates(user) > 0);
}


int MatchServices::getRemainingAmountOfCandidates(User *user) {
	tm* lastDateStruct = this->matchDao->getLastRequestTime(user);
	time_t currentDay = time(NULL);
	struct tm* timeStruct = localtime(&currentDay);
	bool igualDia = timeStruct->tm_mday == lastDateStruct->tm_mday;
	bool igualAnio = timeStruct->tm_year == lastDateStruct->tm_year;
	bool igualMes = timeStruct->tm_mon == lastDateStruct->tm_mon;
	free(lastDateStruct);
	if (!(igualDia && igualAnio && igualMes)) {
		this->matchDao->resetRequests(user);
		return this->dailyLimit;
	}
	int pedidos = this->matchDao->getRequestedCandidates(user);
	return this->dailyLimit - pedidos;
}


list<User*> MatchServices::getUsersFromIDs(list<string> &ids) {
	std::list<User*> listaUsers;
	for (auto itr = ids.begin(); itr != ids.end(); ++itr) {
		listaUsers.push_back(this->profileServices->getUserByID(*itr));
	}
	return listaUsers;
}

double MatchServices::deg2rad(double deg) {
	return (deg * pi / 180);
}

double MatchServices::rad2deg(double rad) {
	return (rad * 180 / pi);
}

double MatchServices::distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r)/2);
	v = sin((lon2r - lon1r)/2);
	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}



