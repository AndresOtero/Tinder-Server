#include <Message.h>
#include <Logger.h>
#include <DBException.h>
#include "ChatDAO.h"
#include "../../json/json/json.h"

ChatDAO::ChatDAO(DBConnector* connector) {
	this->connector = connector;
}

ChatDAO::~ChatDAO() {}

void ChatDAO::saveMsgFromTo(Message *msg) {
	string key = this->assembleKey(msg->getSender(), msg->getReceiver());
	Json::Value nuevoMsg;
	string timeStamp(asctime(msg->getTime()));
	nuevoMsg["time"] = timeStamp;
	nuevoMsg["msg"] = msg->getContent();
	bool resultado = this->connector->exist(key);
	string previous = this->connector->getValueForKey(key);
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
	connector->putValueInKey(key, toSave);
}

void ChatDAO::getMsgBetween(User* sender, User* receiver, list<Message*>* msgs) {
	string key = this->assembleKey(sender, receiver);
	if(!this->connector->exist(key)) return;

	string jsonString = this->connector->getValueForKey(key);
	Json::Reader reader;
	Json::Value json;
	if(!reader.parse(jsonString, json)){
		LOG_ERROR << "DB Corrupted, error parsing." << jsonString << " .";
		throw DBException("DB corrupted");
	}
	//Json::FastWriter writer;
	//string prueba = writer.write(json);
	for (Json::ValueIterator itr = json.begin(); itr != json.end(); itr++) {
		struct tm savedTime;
		if(!strptime(itr->get("time", "error").asString().c_str(), "%a %b %e %H:%M:%S %Y", &savedTime))
			LOG_ERROR << "Error parsing time.";
		Message* nuevo = new Message(itr->get("msg", "error").asString(), &savedTime ,sender, receiver);
		msgs->push_front(nuevo);
	}
}

string ChatDAO::assembleKey(User *A, User *B) {
	string idfrom = A->getId();
	string idto = B->getId();

	std::stringstream ss;
	ss << idfrom << "-" << idto;
	string key(ss.str());
	return key;
}
