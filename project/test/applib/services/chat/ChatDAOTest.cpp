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
	bool resultado = dao.saveMsgFromTo(&msg);
	ASSERT_TRUE(resultado);

	std::string retrieved;
	std::list<Message*>* lista = new list<Message*>();
	bool resultado2 = dao.getMsgBetween(&userA, &userB, lista);
	ASSERT_TRUE(resultado2);
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
	string mensaje1("cacota enorme");
	Message msg(mensaje1, &userA, &userB);
	bool resultado = dao.saveMsgFromTo(&msg);
	ASSERT_TRUE(resultado);
	string mensaje2 = "chau gato";
	Message msg2(mensaje2, &userA, &userB);
	resultado = dao.saveMsgFromTo(&msg2);
	ASSERT_TRUE(resultado);

	std::list<Message*> lista;
	bool resultado2 = dao.getMsgBetween(&userA, &userB, &lista);
	ASSERT_TRUE(resultado2);

	int contador = 0;
	for( std::list<Message*>::iterator itr = lista.begin() ; itr != lista.end() ; itr++ ) {
		contador++;
		delete (*itr); //Voy limpiando los mensajes que cree.
	}
	ASSERT_EQ(2, contador);

}