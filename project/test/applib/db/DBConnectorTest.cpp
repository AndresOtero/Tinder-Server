#include "db/DBConnector.h"
#include "DBConnectorTest.h"
#include <string>

DBConnectorTest::DBConnectorTest() {}

DBConnectorTest::~DBConnectorTest() {};

void DBConnectorTest::SetUp() {

};

void DBConnectorTest::TearDown() {};

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
	DBConnector connector = DBConnector("/tmp/testdb/");
	int contadorInicial = contarEntradas(&connector);
	bool resultado = connector.putValueInKey("testKey", "testValue");
	ASSERT_TRUE(resultado);

	int contadorFinal = contarEntradas(&connector);
	ASSERT_TRUE(contadorFinal==contadorInicial+1);
}

TEST_F(DBConnectorTest, AddKeyToDBMultipleTimes) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	bool resultado = connector.putValueInKey("twoTimesKey", "testValue");
	ASSERT_TRUE(resultado);
	int contadorMedio = contarEntradas(&connector);
	resultado = connector.putValueInKey("twoTimesKey", "updatedValue");
	int contadorFinal = contarEntradas(&connector);
	ASSERT_TRUE(contadorFinal==contadorMedio);
	ASSERT_TRUE(resultado);
	std::string valor;
	resultado = connector.getValueForKey("twoTimesKey", valor);
	ASSERT_TRUE(resultado);
	ASSERT_TRUE(valor == "updatedValue");
	resultado = connector.deleteKey("twoTimesKey");
	ASSERT_TRUE(resultado);
}

TEST_F(DBConnectorTest, RetriveValueFromDB) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	std::string key;
	bool resultado = connector.getValueForKey("testKey", key);
	ASSERT_TRUE(resultado);
	ASSERT_TRUE(key=="testValue");
}

TEST_F(DBConnectorTest, RetriveNonExistentValue) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	std::string key;
	bool resultado = connector.getValueForKey("nonExistent", key);
	ASSERT_FALSE(resultado);
}

TEST_F(DBConnectorTest, DeleteValueFromDB) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	int contadorInicial = contarEntradas(&connector);
	bool resultado = connector.deleteKey("testKey");
	ASSERT_TRUE(resultado);

	int contadorFinal = contarEntradas(&connector);
	ASSERT_TRUE(contadorFinal==contadorInicial-1);
}

TEST_F(DBConnectorTest, DeleteNonExistentValueFromDB) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	int contadorInicial = contarEntradas(&connector);
	bool resultado = connector.deleteKey("nonExistent");
	//OJO Borrar un valor que no existe devuelve true.
	ASSERT_TRUE(resultado);

	int contadorFinal = contarEntradas(&connector);
	ASSERT_TRUE(contadorFinal==contadorInicial);
}