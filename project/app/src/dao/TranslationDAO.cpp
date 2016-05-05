//
// Created by jonathan on 01/05/16.
//

#include "TranslationDAO.h"
#include "TranslationException.h"

TranslationDAO::TranslationDAO(DBConnector &connector) : connector(connector) { }

void TranslationDAO::save(string id, int externalId) {
    connector.putValueInKey(id, to_string(externalId));
}

int TranslationDAO::get(string id) {
    string val = connector.getValueForKey(id);
    if (val.size() > 0) {
        return stoi(val);
    }
    throw TranslationException("Translation not found");
}

bool TranslationDAO::exist(string id) {
    string val =  connector.getValueForKey(id);
    return val.size() > 0;
}

void TranslationDAO::remove(string id) {
    connector.deleteKey(id);
}







