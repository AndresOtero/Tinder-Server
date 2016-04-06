#include "db/DBConnector.h"
#include "DBConnectorTest.h"
#include <string>

DBConnectorTest::DBConnectorTest() {}

DBConnectorTest::~DBConnectorTest() {};

void DBConnectorTest::SetUp() {

};

void DBConnectorTest::TearDown() {};

TEST_F(DBConnectorTest, AddKeyToDB) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	rocksdb::Iterator* it = connector.db->NewIterator(rocksdb::ReadOptions());
	int contadorInicial = 0;
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		contadorInicial++;
	}
	ASSERT_TRUE(it->status().ok()); // Check for any errors found during the scan
	delete it;
	bool resultado = connector.putValueInKey("testKey", "testValue");
	ASSERT_TRUE(resultado);
	it = connector.db->NewIterator(rocksdb::ReadOptions());
	int contadorFinal = 0;
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		contadorFinal++;
	}
	ASSERT_TRUE(it->status().ok()); // Check for any errors found during the scan
	delete it;
	ASSERT_TRUE(contadorFinal==contadorInicial+1);
}

TEST_F(DBConnectorTest, RetriveValueFromDB) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	std::string key;
	bool resultado = connector.getValueForKey("testKey", key);
	ASSERT_TRUE(resultado);
	ASSERT_TRUE(key=="testValue");
}

TEST_F(DBConnectorTest, DeleteValueFromDB) {
	DBConnector connector = DBConnector("/tmp/testdb/");
	rocksdb::Iterator* it = connector.db->NewIterator(rocksdb::ReadOptions());
	int contadorInicial = 0;
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		contadorInicial++;
	}
	ASSERT_TRUE(it->status().ok()); // Check for any errors found during the scan
	delete it;
	bool resultado = connector.deleteKey("testKey");
	ASSERT_TRUE(resultado);
	it = connector.db->NewIterator(rocksdb::ReadOptions());
	int contadorFinal = 0;
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		contadorFinal++;
	}
	ASSERT_TRUE(it->status().ok()); // Check for any errors found during the scan
	delete it;
	ASSERT_TRUE(contadorFinal==contadorInicial-1);
}