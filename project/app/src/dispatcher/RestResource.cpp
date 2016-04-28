#include "RestResource.h"



void RestResource::readJson(WebContext &wc, Json::Value & value) {
    Json::Reader reader;
    bool success = reader.parse(wc.getRequest().getContent(), value);
    if(!success) {
        throw "Error reading json";
    }

}

void RestResource::writeJson(WebContext &wc, Json::Value &value) {
    Json::FastWriter writer;
    string content = writer.write(value);
    wc.getResponse().setContent(content);
}
