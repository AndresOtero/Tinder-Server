/*
 * User.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_CHATDAO_H_
#define SRC_CHATDAO_H_

#include <string>
#include <list>
#include "../../model/Message.h"
#include "../../model/User.h"
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
	 */
	void saveMsgFromTo(Message *msg);

	/**
	 * Saves in the param msgs all the messages from one username to the other. Returns true or false
	 * if the query to the db was successful.
	 *
	 * @param sender username that is the sender of the messages to get.
	 * @param receiver username that is the receiver of the messages to get.
	 * @param msgs list of all the messages in the db.
	 */
	void getMsgBetween(User* sender, User* receiver, list<Message*>* msgs);

private:
	DBConnector* connector;
	string assembleKey(User* A, User* B);
};


#endif /* SRC_CHATDAO_H_ */