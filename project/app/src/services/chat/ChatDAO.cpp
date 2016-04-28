#include <Message.h>
#include <Logger.h>
#include "ChatDAO.h"
#include "../../json/json/json.h"

ChatDAO::ChatDAO(DBConnector* connector) {
	this->connector = connector;
}

ChatDAO::~ChatDAO() {}

bool ChatDAO::saveMsgFromTo(Message* msg) {
	string key = this->assembleKey(msg->getSender(), msg->getReceiver());
	Json::Value nuevoMsg;
	string timeStamp(asctime(msg->getTime()));
	nuevoMsg["time"] = timeStamp;
	nuevoMsg["msg"] = msg->getContent();
	string previous;
	bool resultado = this->connector->getValueForKey(key, previous);
	Json::Value toSaveJson;
	//Si no habia mensajes entre los dos
	if (!resultado) {
		toSaveJson = Json::Value(Json::arrayValue);
	}
	else {
		Json::Reader reader;
		reader.parse(previous, toSaveJson);
	}
	toSaveJson.append(nuevoMsg);
	Json::FastWriter writer;
	string toSave = writer.write(toSaveJson);
	return connector->putValueInKey(key, toSave);  
}

bool ChatDAO::getMsgBetween(User* sender, User* receiver, list<Message*>* msgs) {
	string key = this->assembleKey(sender, receiver);
	string jsonString;
	bool result = this->connector->getValueForKey(key, jsonString);
	if (!result) return false;
	Json::Reader reader;
	Json::Value json;
	if(!reader.parse(jsonString, json)){
		LOG_ERROR << "DB Corrupted, error parsing." << jsonString << " .";
		return false;
	}
	Json::FastWriter writer;
	string prueba = writer.write(json);
	for (Json::ValueIterator itr = json.begin(); itr != json.end(); itr++) {
		struct tm savedTime;
		if(!strptime(itr->get("time", "error").asString().c_str(), "%a %b %e %H:%M:%S %Y", &savedTime))
			LOG_ERROR << "Error parsing time.";
		Message* nuevo = new Message(itr->get("msg", "error").asString(), &savedTime ,sender, receiver);
		msgs->push_front(nuevo);
	}
	return true;
}

string ChatDAO::assembleKey(User *A, User *B) {
	string idfrom = A->getId();
	string idto = B->getId();

	std::stringstream ss;
	ss << idfrom << "-" << idto;
	string key(ss.str());
	return key;
}
