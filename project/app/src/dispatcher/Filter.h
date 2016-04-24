//
// Created by jonathan on 23/04/16.
//

#ifndef TINDER_SERVER_FILTER_H
#define TINDER_SERVER_FILTER_H
#include "WebContext.h"
#include "functional"

class Filter {
private:
    Filter * next;
protected:
    virtual bool doFilter(WebContext & context)  {
        return true;
    };
public:
    Filter () {
        next = 0;
    };
    void setNext(Filter & next) {
        this->next = &next;
    };
    virtual ~Filter(){};
    void filter(WebContext & context, function<void(WebContext&)> handler) {
        if(doFilter(context)) {
            if(next) {
                next->filter(context, handler);
            } else {
                handler(context);
            }
        }
    };
};


#endif //TINDER_SERVER_FILTER_H
