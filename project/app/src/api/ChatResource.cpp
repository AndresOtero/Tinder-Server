//
// Created by jonathan on 27/04/16.
//

#include <ChatServices.h>
#include <UserNotFoundException.h>
#include <ChatException.h>
#include "ChatResource.h"
#include "ApiConstants.h"

ChatResource::ChatResource(ChatServices &service, ProfileServices &profile): chatService(service),
                                                                             profileServices(profile)  {

}

ChatResource::~ChatResource() {

}

void ChatResource::setup(ApiDispatcher &dispatcher) {
    using placeholders::_1;
    dispatcher.registerEndPoint(RestRequest::GET, "/chat/#user#", (function<void (WebContext&)>)bind( &ChatResource::getConversation, this, _1 ));
    dispatcher.registerEndPoint(RestRequest::POST, "/chat", (function<void (WebContext&)>)bind( &ChatResource::sendMessage, this, _1 ));
}
void ChatResource::getConversation(WebContext &wc) {
    User *receiver;
    User *sender;
    try {
        receiver = profileServices.getUserByID(wc.getParam("user"));
    } catch (UserNotFoundException & e) {
        Json::Value result;
        this->writeJsonResponse(wc, result, API_STATUS_INVALID_RECIPIENT);
        return;
    }

    try {
        sender = profileServices.getUserByID(wc.getUserid());
    } catch (UserNotFoundException & e) {
        delete receiver;
        this->writeJsonResponse(wc, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
        return;
    }

    try {
        std::list<Message *> *lista = chatService.getConversationBetweenUsers(sender, receiver);
        Json::Value raiz;
        for (auto it = lista->begin(); it != lista->end(); ++it) {
            raiz.append((*it)->toJson());
            delete (*it);
        }
        delete lista;
        delete receiver;
        delete sender;
        this->writeJsonResponse(wc, raiz);
    } catch (runtime_error &e){
        delete sender;
        delete receiver;
        wc.getResponse().setStatus(STATUS_500_INTERNAL_SERVER_ERROR);
    }
}

void ChatResource::sendMessage(WebContext &wc) {
    Json::Value params;
    RestResource::readJson(wc, params);
    User * sender;
    User* receiver;
    string content;
    Message* message;
    try {
        sender = profileServices.getUserByID(wc.getUserid());
    } catch (UserNotFoundException & e) {
        this->writeJsonResponse(wc, API_STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED);
        return;
    }
    string receiverID = params["receiver"].asString();
    content = params["content"].asString();
    if (receiverID == "" || content == "") {
        wc.getResponse().setStatus(STATUS_400_BAD_REQUEST);
        return;
    }
    try {
        receiver = profileServices.getUserByID(receiverID);
    } catch (UserNotFoundException & e) {
        delete sender;
        this->writeJsonResponse(wc, API_STATUS_INVALID_RECIPIENT);
        return;
    }
    try {
        message = new Message(content, sender, receiver);
        chatService.sendMessageFromTo(message);
        this->writeJsonResponse(wc, API_STATUS_CODE_DONE);
        delete sender;
        delete receiver;
        delete message;
    } catch (ChatException & e) {
        delete sender;
        delete receiver;
        delete message;
        this->writeJsonResponse(wc, API_STATUS_INVALID_RECIPIENT);
    }

}









