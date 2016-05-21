//
// Created by matias on 5/19/16.
//

#include "CorruptOptionsException.h"

CorruptOptionsException::CorruptOptionsException(const string msg) : runtime_error(msg){ }

CorruptOptionsException::~CorruptOptionsException() { }