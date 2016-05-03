#include "services/chat/ChatDAO.h"
#include "ChatDAOTest.h"
#include "db/DBConnector.h"
#include "json/json/json.h"
#include <string>
#include <User.h>
#include <Message.h>
#include <stdio.h>
#include <boost/filesystem.hpp>
ChatDAOTest::ChatDAOTest() {}

ChatDAOTest::~ChatDAOTest() {};

void ChatDAOTest::SetUp() {
	this->connector = new DBConnector(DB_FILE);
};

void ChatDAOTest::TearDown() {
	delete this->connector;
	boost::filesystem::remove_all(DB_FILE);

};

TEST_F(ChatDAOTest, saveMSGToDBAndRetrieve) {

	ChatDAO dao(connector);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "hola",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "chau", 2 , "", "F", 18,"", intereses, location);
	string mensaje("muy enorme");
	Message msg(mensaje, &userA, &userB);
	dao.saveMsgFromTo(&msg);


	std::string retrieved;
	std::list<Message*>* lista = new list<Message*>();
	dao.getMsgBetween(&userA, &userB, lista);

	ASSERT_TRUE(lista->front()->getContent() == mensaje);

	Message* limpiar  = lista->front();
	delete limpiar;
	//Limpio la DB
}

TEST_F(ChatDAOTest, retrieveMultipleMsgs) {
	ChatDAO dao(connector);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "hola",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "chau", 2 , "", "F", 18,"", intereses, location);
	string mensaje1("foo enorme");
	Message msg(mensaje1, &userA, &userB);
	dao.saveMsgFromTo(&msg);
	string mensaje2 = "chau gato";
	Message msg2(mensaje2, &userA, &userB);
	dao.saveMsgFromTo(&msg2);

	std::list<Message*> lista;
	dao.getMsgBetween(&userA, &userB, &lista);

	int contador = 0;
	for( std::list<Message*>::iterator itr = lista.begin() ; itr != lista.end() ; itr++ ) {
		contador++;
		delete (*itr); //Voy limpiando los mensajes que cree.
	}
	ASSERT_EQ(2, contador);

}