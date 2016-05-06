//
// Created by jonathan on 27/04/16.
//

#ifndef TINDER_SERVER_CHATRESOURCE_H
#define TINDER_SERVER_CHATRESOURCE_H

#include "dispatcher/RestResource.h"
#include "dispatcher/WebContext.h"
#include "dispatcher/ApiDispatcher.h"
class ChatResource: public RestResource {
private:
    ChatServices & service;
public:
    ChatResource(ChatServices &service);
    virtual ~ChatResource();
    void setup(ApiDispatcher & dispatcher);
    void getConversation(WebContext & wc);
    void sendMessage(WebContext & wc);

};


#endif //TINDER_SERVER_CHATRESOURCE_H
