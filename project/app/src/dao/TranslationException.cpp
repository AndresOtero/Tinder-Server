//
// Created by jonathan on 01/05/16.
//

#include "TranslationException.h"

TranslationException::TranslationException(string error): runtime_error(error) {

}

TranslationException::~TranslationException() {

}



