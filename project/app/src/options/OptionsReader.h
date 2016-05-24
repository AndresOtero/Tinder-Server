//
// Created by matias on 5/20/16.
//

#ifndef TINDER_SERVER_OPTIONSREADER_H
#define TINDER_SERVER_OPTIONSREADER_H

#include <string>
#include "Options.h"

class OptionsReader {
public:
	static Options* readOptionsFromFile(std::string file);
	static Options* loadDefaultOptions();

private:
	static const std::string DefaultLogLevel;
	static const std::string DefaultSharedServer;
	static const std::string DefaultLocalDB;
};


#endif //TINDER_SERVER_OPTIONSREADER_H
