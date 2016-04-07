/*
 * PathVariableExtractor.cpp
 *
 *  Created on: 20 de mar. de 2016
 *      Author: jonathan
 */

#include "PathVariableExtractor.h"
#include <boost/regex.hpp>
#include <iostream>
#include "PathVariableException.h"
#include "NoSuchMethodHandlerException.h"
#include "log/Logger.h"
using namespace std;


PathVariableExtractor::PathVariableExtractor(string format, string path) {
	list<string> names = buildParamNames(format);
	buildParams(format, path, names);

}

PathVariableExtractor::~PathVariableExtractor() {}

list<string> PathVariableExtractor::buildParamNames(string input) {
	list<string> names;
    try {
        boost::regex exp( "#([^\\/]+)#" ) ;
        boost::match_results<std::string::const_iterator> what;
        std::string::const_iterator start = input.begin() ;
        while ( boost::regex_search(start, input.cend(), what, exp) ){
        	names.push_back(what[1]);
        	start = what[0].second ;
        }
        return names;
    }
    catch ( boost::bad_expression & ex )
    {
        throw PathVariableException(ex.what());
    }
}

void PathVariableExtractor::buildParams(string format, string path,
		list<string> names) {
	using namespace boost;
	regex exp ("#[^\\/]+#");
	const string replace = "([^\\/]+)";
	string gralExpression = "^" + regex_replace(format, exp ,replace) + "$" ;
    try {
        boost::regex exp( gralExpression ) ;
        boost::match_results<std::string::const_iterator> what;
        std::string::const_iterator start = path.begin() ;
        bool match= boost::regex_search(start, path.cend(), what, exp);
        if (!match) {
        	throw PathVariableException(path + " doesn't match with " + format);
        }
		int i = 0;
		for (std::list<string>::iterator it=names.begin(); it != names.end(); ++it) {
			string name = *it;
			this->params.insert(std::make_pair(name, what[++i]));
		}
    }
    catch ( boost::bad_expression & ex )
    {
    	 throw PathVariableException(ex.what());
    }

}

string PathVariableExtractor::get(string param) {
	if(params.count(param) > 0) {
		return params[param];
	} else {
		return "";
	}



}
