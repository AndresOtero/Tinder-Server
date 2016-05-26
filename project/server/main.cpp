/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include <User.h>
#include <ProfileServices.h>
#include <SecurityFilter.h>
#include <InterestResource.h>
#include <MatchServices.h>
#include <Options.h>
#include <OptionsReader.h>
#include <CorruptOptionsException.h>
#include <LocationResource.h>
#include <CandidateResource.h>
#include <WebServerException.h>
#include <MatchResource.h>
#include <LikeResource.h>
#include "webserver/WebServer.h"
#include "log/Logger.h"
#include "db/DBConnector.h"
#include "dispatcher/ApiDispatcher.h"
#include "api/UserResource.h"
#include "api/AuthResource.h"
#include "services/authentication/AuthenticationService.h"
#include <thread>
#include <chrono>
int main(int argc, char* argv[]) {
	Options* options;
	if (argc == 3 && string(argv[1]) == "-config"){
		try {
			LOG_INFO << "Archivo de opciones recibido: " + string(argv[2]) ;
			options = OptionsReader::readOptionsFromFile(string(argv[2]));
		} catch (CorruptOptionsException &e){
			LOG_WARNING << "Error cargando archivo de configuracion. Cargando valores por defecto.";
			options = OptionsReader::loadDefaultOptions();
		}
	}
	else {
		LOG_INFO << "No se recibio archivo de opciones. Cargando valores por defecto.";
		options = OptionsReader::loadDefaultOptions();
	}




	setLevelFilter(options->getLogLevel());

	LOG_DEBUG << "Nivel del loggeo seteado en DEBUG.";
	LOG_INFO << "Testing conection to shared server.";
	SharedConnector sharedConnector = SharedConnector(options->getSharedServerURL());
	if(!sharedConnector.testConnection()) LOG_WARNING<< "Error probando conexion con el shared server";
	else LOG_INFO << "CONNECTION [OK]";

	LOG_INFO << "Starting DB";
	DBConnector authenticationDB = DBConnector(options->getDbLocation() + "/authentication/");
	if(!authenticationDB.isOk()) {
		LOG_FATAL<< ("Error abriendo la DB de autenticación.");
		std::this_thread::sleep_for (std::chrono::seconds(1));
		return 0;
	}

	DBConnector translationDB = DBConnector(options->getDbLocation() + "/translation/");
	if(!authenticationDB.isOk())
	{
		LOG_FATAL << ("Error abriendo la DB de traducción.");
		std::this_thread::sleep_for (std::chrono::seconds(1));
		return 0;
	}

	DBConnector matchDB = DBConnector(options->getDbLocation() + "/match");
	if(!matchDB.isOk()) {
		LOG_FATAL << ("Error abriendo la DB de match.");
		std::this_thread::sleep_for (std::chrono::seconds(1));
		return 0;
	}

	LOG_INFO << "Starting WebServer";

	MatchDAO matchDAO(&matchDB);
	UserDAO userDAO(&sharedConnector);
	AuthenticationDAO authDAO (authenticationDB);
	TranslationDAO transDAO (translationDB);
	ProfileServices profileService(&userDAO, &transDAO);
	AuthenticationService authService(&authDAO, &profileService);
	MatchServices matchServices(&matchDAO,&profileService);
	//authService.saveNewUser("chelo3","prueba");


	SecurityFilter securityFilter(authService);
	securityFilter.excludeRegex(RestRequest::POST, "/auth");
	securityFilter.excludeRegex(RestRequest::PUT, "/auth");
	ApiDispatcher dispatcher(securityFilter);

	UserResource user(profileService);
	user.setup(dispatcher);

	AuthResource auth (&authService);
	auth.setup(dispatcher);

	InterestResource interestResource(profileService);
	interestResource.setup(dispatcher);

	LocationResource locationRes(profileService);
	locationRes.setup(dispatcher);

	CandidateResource candidateResource(matchServices, profileService);
	candidateResource.setup(dispatcher);
	MatchResource matchResource(matchServices, profileService);
	matchResource.setup(dispatcher);

	LikeResource likeResource(matchServices, profileService);
	likeResource.setup(dispatcher);


	try {
		WebServer ws(dispatcher);
		ws.start();
	} catch (WebServerException & e) {
		LOG_FATAL <<  "Error starting server : " << e.what();
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}

	return 0;

}
