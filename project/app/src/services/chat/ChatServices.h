//
// Created by matias on 4/18/16.
//

#ifndef TINDER_SERVER_CHATSERVICES_H
#define TINDER_SERVER_CHATSERVICES_H


#include <MatchDAO.h>
#include <Message.h>
#include "ChatDAO.h"

/**
 * @class ChatServices
 * Class that provides the methods to solve all the possible requests regarding messages between users.
 */
class ChatServices {
public:
	/**
	 * Default Ccnstructor
	 * @param chatDao DataAccessObject to use for messages.
	 * @param matchDao DataAccessObject to use to check matches.
	 */
	ChatServices(ChatDAO* chatDao, MatchDAO* matchDao);
	virtual ~ChatServices();

	/**
	 * Method to send messages between users. Returns true if the message was sent correctly and false if not. If
	 * the users do not like each other the message can not be sent and false will be returned.
	 *
	 * @param msg message to be sent.
	 */
	void sendMessageFromTo(Message *msg);

	/**
	 * Returns a json with all the messages between both users. If no messages are found, an empty json is returned.
	 * @param A one of the users of the conversation.
	 * @param B second user of the conversation.
	 */
	list<Message*>* getConversationBetweenUsers(User* A, User* B);

private:
	ChatDAO* chat;
	MatchDAO* match;
	bool static compareMessages( Message* msg1,  Message* msg2);
};


#endif //TINDER_SERVER_CHATSERVICES_H
