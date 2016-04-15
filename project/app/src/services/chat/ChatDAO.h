/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_CHATDAO_H_
#define SRC_CHATDAO_H_

#include <string>
#include "../../db/DBConnector.h"

using namespace std;

/**
 * @class ChatDAO
 *
 * Data Access Object to the chat database. Provides functionality to obtain messages from the chat.
 */
class ChatDAO {
public:
	/**
	 * Default constructor
	 *
	 * @param connector that has the messages db opened.
	 */
	ChatDAO(DBConnector* connector);
	virtual ~ChatDAO();

	/**
	 * Saves the message received. It does not do any validation of the sender and receiver.
	 *
	 * @param msg to store.
	 * @param from username of the sender of the message.
	 * @param to username of the receiver of the message.
	 */
	bool saveMsgFromTo(string msg, string from, string to);

	/**
	 * Saves in the param msgs all the messages from one username to the other. Returns true or false
	 * if the query to the db was successful.
	 *
	 * @param from username that is the sender of the messages to get.
	 * @param to username that is the receiver of the messages to get.
	 * @param msgs string were all the messages retrieved are saved.
	 */
	bool getMsgBetween(string from, string to, string& msgs);

private:
	DBConnector* connector;
};


#endif /* SRC_CHATDAO_H_ */