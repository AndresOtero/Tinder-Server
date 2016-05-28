#include "db/DBConnector.h"
#include "DBConnectorTest.h"
#include <string>
#include <boost/filesystem.hpp>
#include <DBException.h>

DBConnectorTest::DBConnectorTest() {}

DBConnectorTest::~DBConnectorTest() {};

void DBConnectorTest::SetUp() {

	this->connector = new DBConnector(DB_AUTH);
};

void DBConnectorTest::TearDown() {
	delete this->connector;
	boost::filesystem::remove_all(DB_AUTH);
};

int contarEntradas(DBConnector* connector) {
	int contador = 0;
	rocksdb::Iterator* it = connector->db->NewIterator(rocksdb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		contador++;
	}
	delete it;
	return contador;
}

TEST_F(DBConnectorTest, AddKeyToDB) {

	connector->putValueInKey("testKey", "testValue");
	int contadorFinal = contarEntradas(connector);
	int expected = 1;
	ASSERT_EQ(expected, contadorFinal);
}

TEST_F(DBConnectorTest, AddKeyToDBMultipleTimes) {
	connector->putValueInKey("twoTimesKey", "testValue");
	connector->putValueInKey("twoTimesKey", "updatedValue");
	int contadorFinal = contarEntradas(connector);
	int expected = 1;
	ASSERT_EQ(expected, contadorFinal);


	std::string valor = connector->getValueForKey("twoTimesKey");

	ASSERT_EQ(valor, "updatedValue");
	connector->deleteKey("twoTimesKey");
	
}

TEST_F(DBConnectorTest, RetriveValueFromDB) {
	std::string key;
	connector->putValueInKey("testKey","val");
	std::string value = connector->getValueForKey("testKey");
	ASSERT_TRUE("val" == value);
}

TEST_F(DBConnectorTest, RetriveNonExistentValue) {
	std::string key;
	key = connector->getValueForKey("nonExistent");
	int size = key.size();

	ASSERT_EQ(0, size);
}

TEST_F(DBConnectorTest, DeleteValueFromDB) {
	connector->putValueInKey("testKey", "prueba");
	int contadorInicial = contarEntradas(connector);
	ASSERT_EQ(1, contadorInicial);
	connector->deleteKey("testKey");
	int contadorFinal = contarEntradas(connector);
	ASSERT_EQ(0, contadorFinal);
}

TEST_F(DBConnectorTest, DeleteNonExistentValueFromDB) {
	int contadorInicial = contarEntradas(connector);
	ASSERT_EQ(0, contadorInicial);
	connector->deleteKey("nonExistent");

	int contadorFinal = contarEntradas(connector);
	ASSERT_EQ(0, contadorFinal);
}


TEST_F(DBConnectorTest, IsOK) {
	ASSERT_TRUE(connector->isOk());
}


