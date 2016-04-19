#include "services/chat/ChatDAO.h"
#include "ChatDAOTest.h"
#include "db/DBConnector.h"
#include "json/json/json.h"
#include <string>

ChatDAOTest::ChatDAOTest() {}

ChatDAOTest::~ChatDAOTest() {};

void ChatDAOTest::SetUp() {

};

void ChatDAOTest::TearDown() {};

TEST_F(ChatDAOTest, saveMSGToDBAndRetrieve) {
	DBConnector connector = DBConnector("/tmp/testChatDB/");
	ChatDAO dao(&connector);
	string mensaje = "hola gato";
	bool resultado = dao.saveMsgFromTo(mensaje, "joni", "1", "matias", "2");
	ASSERT_TRUE(resultado);

	std::string retrieved;
	bool resultado2 = dao.getMsgBetween("joni", "1", "matias", "2", retrieved);
	ASSERT_TRUE(resultado2);

	Json::Reader reader;
	Json::Value value;
	bool resultado3 = reader.parse(retrieved, value);
	ASSERT_TRUE(resultado3);
	ASSERT_TRUE(value.get("msg", "ERROR").asString() == mensaje);

	//Limpio la DB
	connector.deleteKey("joni:1-matias:2");
}

TEST_F(ChatDAOTest, retrieveMultipleMsgs) {
	DBConnector connector = DBConnector("/tmp/testChatDB/");
	ChatDAO dao(&connector);
	string mensaje1 = "hola gato";
	bool resultado = dao.saveMsgFromTo(mensaje1, "joni","1", "matias","2");
	ASSERT_TRUE(resultado);
	string mensaje2 = "chau gato";
	resultado = dao.saveMsgFromTo(mensaje2, "joni","1", "matias","2");
	ASSERT_TRUE(resultado);

	std::string retrieved;
	bool resultado2 = dao.getMsgBetween("joni","1", "matias","2", retrieved);
	ASSERT_TRUE(resultado2);

	Json::Reader reader;
	Json::Value value;
	bool resultado3 = reader.parse(retrieved, value);
	ASSERT_TRUE(resultado3);

	int contador = 0;
	for( Json::ValueIterator itr = value.begin() ; itr != value.end() ; itr++ ) {
		contador++;
	}
	ASSERT_TRUE(contador == 2);

	//Limpio la DB
	connector.deleteKey("joni:1-matias:2");
}