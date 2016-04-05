/*
 * PathVariableExtractor.cpp
 *
 *  Created on: 20 de mar. de 2016
 *      Author: jonathan
 */

#include "PathVariableExtractor.h"
#include <regex>
using namespace std;


PathVariableExtractor::PathVariableExtractor(string format, string path) {
	regex exp ("#[^\\/]+#");
	const string replace = "([^\\/]+)";
	string expression = "^" + regex_replace(format, exp ,replace) + "$" ;




}

PathVariableExtractor::~PathVariableExtractor() {
	// TODO Auto-generated destructor stub
}

string PathVariableExtractor::get(string param) {
	if(params.count(param) > 0) {
		return params[param];
	} else {
		return "";
	}


}
