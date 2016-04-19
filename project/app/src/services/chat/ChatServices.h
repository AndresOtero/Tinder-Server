//
// Created by matias on 4/18/16.
//

#ifndef TINDER_SERVER_CHATSERVICES_H
#define TINDER_SERVER_CHATSERVICES_H


#include <MatchDAO.h>
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
	 * @param from user sending the message
	 * @param to user that will receive the message
	 */
	bool sendMessageFromTo(string from, string to);

	/**
	 * Returns a json with all the messages between both users. If no messages are found, an empty json is returned.
	 * @param userA one of the users of the conversation.
	 * @param userB the other user of the conversation.
	 */
	Json::Value getConversationBetweenUsers(string userA, string userB);

private:
	ChatDAO* chat;
	MatchDAO* match;
};


#endif //TINDER_SERVER_CHATSERVICES_H
