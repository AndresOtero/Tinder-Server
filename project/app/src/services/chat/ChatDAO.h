/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_CHATDAO_H_
#define SRC_CHATDAO_H_

#include <string>
#include "db/DBConnector.h"

using namespace std;

class ChatDAO {
public:
	ChatDAO(DBConnector* connector);
	virtual ~ChatDAO();
	bool saveMsgFromTo(string msg, string from, string to);
	bool getMsgBetween(string from, string to, string& msgs);

private:
	DBConnector* connector;
};


#endif /* SRC_CHATDAO_H_ */