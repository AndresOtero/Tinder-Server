#include "RestResource.h"


Json::Value RestResource::readJson(WebContext &wc) {
    Json::Reader reader;
    Json::Value parsed;
    bool success = reader.parse(wc.getRequest().getContent(), parsed);
    if(success) {
        return parsed;
    }
    throw "Error reading json";

}

void RestResource::writeJson(WebContext &wc, Json::Value &value) {
    Json::FastWriter writer;
    string content = writer.write(value);
    wc.getResponse().setContent(content);
}
