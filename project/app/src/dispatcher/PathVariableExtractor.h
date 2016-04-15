#ifndef SRC_DISPATCHER_PATHVARIABLEEXTRACTOR_H_
#define SRC_DISPATCHER_PATHVARIABLEEXTRACTOR_H_
#include <string>
#include <map>
#include <list>
using namespace std;

/**
 * @class PathVariableExtractor
 * Extracts variables from a given path
 *
 * @author jtierno
 *
 */

class PathVariableExtractor {
private:
	/**
	 * Extracted parameters
	 */
	map<string, string> params;
	/**
	 * This method Extracts parameters names
	 */
	list<string> buildParamNames(string format);
	/**
	 * This method constructs map of parameters
	 */
	void buildParams(string format,string path, list<string> names);
public:

	/**
	 * Constructor with format and path to evaluate
	 * @param format that describes how to parse path
	 * @param path from where to read variables
	 */
	PathVariableExtractor(string format, string path);
	virtual ~PathVariableExtractor();

	/**
	 * Get a variable in path
	 * @return Returns the value of  the variable if exists, else returns an empty string
	 */
	string get(string param);
};

#endif /* SRC_DISPATCHER_PATHVARIABLEEXTRACTOR_H_ */
