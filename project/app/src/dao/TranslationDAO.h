//
// Created by jonathan on 01/05/16.
//

#ifndef TINDER_SERVER_TRANSLATIONDAO_H
#define TINDER_SERVER_TRANSLATIONDAO_H

#include "DBConnector.h"
#include "string"
using namespace std;

class TranslationDAO {
private:
public:
    TranslationDAO(DBConnector &connector);

private:
    DBConnector & connector;
public:
    void save(string id, int externalId);
    int get(string id);
    bool exist(string id);
};


#endif //TINDER_SERVER_TRANSLATIONDAO_H
