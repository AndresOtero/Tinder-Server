#include <ApiConstants.h>
#include "RestResource.h"



void RestResource::readJson(WebContext &wc, Json::Value & value) {
    Json::Reader reader;
    bool success = reader.parse(wc.getRequest().getContent(), value);
    if(!success) {
        throw "Error reading json";
    }

}

void RestResource::writeJsonResponse(WebContext &wc, Json::Value &value, int apiStatus) {
    Json::Value response;
    response[API_RESPONSE_PARAM] = value;
    response[API_STATUS_CODE_PARAM] = apiStatus;
    Json::FastWriter writer;
    string content = writer.write(response);
    wc.getResponse().setContent(content);
}

void RestResource::writeJsonResponse(WebContext &wc, Json::Value &value) {
    writeJsonResponse(wc, value, API_STATUS_CODE_DONE);
}

void RestResource::writeJsonResponse(WebContext &wc) {
    Json::Value value = "";
    writeJsonResponse(wc, value);
}

void RestResource::writeJsonResponse(WebContext &wc, int apiStatus) {
    Json::Value val = "";
    writeJsonResponse(wc, val, apiStatus);
}






