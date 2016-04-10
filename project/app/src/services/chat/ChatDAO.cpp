#include "ChatDAO.h"
#include "json/json/json.h"
#include <time.h>

ChatDAO::ChatDAO(DBConnector* connector) {
	this->connector = connector;
}

ChatDAO::~ChatDAO() {}

bool ChatDAO::saveMsgFromTo(string msg, string from, string to) {
	string key(from + "-" + to);
	Json::Value nuevoMsg;
	struct tm * timeinfo;
	time_t rawtime;
	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	string timeStamp(asctime(timeinfo));
	nuevoMsg["time"] = timeStamp;
	nuevoMsg["msg"] = msg;
	string previous;
	bool resultado = this->connector->getValueForKey(key, previous);
	string toSave;
	Json::FastWriter writer;
	//Si no habia mensajes entre los dos
	if (!resultado) toSave = writer.write(nuevoMsg);
	else {
		toSave = previous + "," + writer.write(nuevoMsg);
	}
	return connector->putValueInKey(key, toSave);  
}

bool ChatDAO::getMsgBetween(string from, string to, string &msgs) {
	string key(from + "-" + to);
	return this->connector->getValueForKey(key, msgs);
}
