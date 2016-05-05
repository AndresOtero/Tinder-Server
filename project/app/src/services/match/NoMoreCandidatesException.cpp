//
// Created by matias on 5/4/16.
//

#include "NoMoreCandidatesException.h"


NoMoreCandidatesException::NoMoreCandidatesException(const string msg) : runtime_error (msg) { }

NoMoreCandidatesException::~NoMoreCandidatesException() { }

