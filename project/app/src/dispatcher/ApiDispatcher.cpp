/*
 * ApiDispatcher.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "ApiDispatcher.h"



ApiDispatcher::ApiDispatcher() {


}

ApiDispatcher::~ApiDispatcher() {
}

void ApiDispatcher::registerEndPoint(methods method, string uri,
		function<void(WebContext&)> func) {
}

void ApiDispatcher::handle(RestRequest&, RestResponse&) {

}
