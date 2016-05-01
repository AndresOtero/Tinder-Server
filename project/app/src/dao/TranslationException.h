//
// Created by jonathan on 01/05/16.
//

#ifndef TINDER_SERVER_TRANSLATIONEXCEPTION_H
#define TINDER_SERVER_TRANSLATIONEXCEPTION_H
#include <stdexcept>
#include <string>
using namespace std;
using std::runtime_error;

class TranslationException: public runtime_error {
public :
    /**
 * Constructor with error
 * @param error message
 */
    TranslationException(string error);
    virtual ~TranslationException();
};


#endif //TINDER_SERVER_TRANSLATIONEXCEPTION_H
