//
// Created by jonathan on 27/04/16.
//

#include <ChatServices.h>
#include "ChatResource.h"

ChatResource::ChatResource(ChatServices &service): service(service)  {

}

ChatResource::~ChatResource() {

}

void ChatResource::setup(ApiDispatcher &dispatcher) {
    using placeholders::_1;
    dispatcher.registerEndPoint(RestRequest::GET, "/chat/#user#", (function<void (WebContext&)>)bind( &ChatResource::getConversation, this, _1 ));
    dispatcher.registerEndPoint(RestRequest::POST, "/chat", (function<void (WebContext&)>)bind( &ChatResource::sendMessage, this, _1 ));
}

void ChatResource::getConversation(WebContext &wc) {
    string user = wc.getParam("user");
    wc.getUserid()
    //service.getConversationBetweenUsers(, user);

}

void ChatResource::sendMessage(WebContext &wc) {
    Json::Value params = RestResource::readJson(wc);
}









