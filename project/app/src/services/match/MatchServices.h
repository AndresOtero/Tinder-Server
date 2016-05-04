//
// Created by matias on 4/24/16.
//

#ifndef TINDER_SERVER_MATCHSERVICES_H
#define TINDER_SERVER_MATCHSERVICES_H


#include <UserDAO.h>
#include "MatchDAO.h"

class MatchServices {


private:
	MatchDAO* MatchDao;
	UserDAO* userDao;
};


#endif //TINDER_SERVER_MATCHSERVICES_H
