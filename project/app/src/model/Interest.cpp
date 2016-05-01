//
// Created by matias on 4/30/16.
//

#include "Interest.h"

Interest::Interest(string category, string value) {
	this->category = category;
	this->value = value;
}

Interest::~Interest() { }

bool Interest::operator==(const Interest &other) {
	return (this->category == other.category && this->value == other.value);
}



