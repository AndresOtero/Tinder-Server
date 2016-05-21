//
// Created by matias on 5/20/16.
//

#include <fstream>
#include "OptionsReader.h"
#include "CorruptOptionsException.h"
#include "../json/json/json.h"


const std::string OptionsReader::DefaultLogLevel = "DEBUG";
const std::string OptionsReader::DefaultSharedServer =  "http://tinder-shared.herokuapp.com";
const std::string OptionsReader::DefaultLocalDB = "/tmp";

Options *OptionsReader::readOptionsFromFile(std::string file) {
	std::ifstream stream(file);
	std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	Json::Reader reader;
	Json::Value jsonContent;
	if(!reader.parse(content, jsonContent)) throw new CorruptOptionsException("Error parseando el archivo.");
	string LogLevel = jsonContent.get("Log_Level", DefaultLogLevel).asString();
	string SharedServer = jsonContent.get("Shared_URL", DefaultSharedServer).asString();
	string LocalDB = jsonContent.get("Local_DB", DefaultLocalDB).asString();
	return new Options(LogLevel, SharedServer, LocalDB);
}


Options *OptionsReader::loadDefaultOptions() {
	return new Options(DefaultLogLevel, DefaultSharedServer, DefaultLocalDB);
}

