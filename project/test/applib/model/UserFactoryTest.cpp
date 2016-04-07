#include "UserFactoryTest.h"
#include "model/UserFactory.h"
#include <string>
#include <iostream>

UserFactoryTest::UserFactoryTest() {};

UserFactoryTest::~UserFactoryTest() {};

void UserFactoryTest::SetUp() {};

void UserFactoryTest::TearDown() {};

TEST_F(UserFactoryTest, AssembleOneUserFromJson) {
	//Simula la llamada de getUserByID donde hay que agregar la respuesta a un array.
	UserFactory factory(NULL);
	Json::Value array;
	Json::Value root;
	Json::Value content;
	Json::Value location;
	location["longitude"] = 1.0;
	location["latitude"] = 2.0;
	content["id"] = 10;
	content["name"] = "prueba";
	content["alias"] = "alias";
	content["photo_profile"] = "photo";
	content["email"] = "aasd@gmail.com";
	content["location"] = location;
	root["user"] = content;
	array.append(root);
	list<User*> lista = factory.assembleUsersFromJson(array);
	ASSERT_TRUE(lista.front()->getId() == "10");
	ASSERT_TRUE(lista.front()->getName() == "prueba");
	ASSERT_TRUE(lista.front()->getAlias() == "alias");
	ASSERT_TRUE(lista.front()->getEmail() == "aasd@gmail.com");
	ASSERT_TRUE(lista.front()->getPhotoURL() == "photo");
	ASSERT_TRUE(lista.front()->getLatitude() == 2.0);
	ASSERT_TRUE(lista.front()->getLongitude() == 1.0);
}


TEST_F(UserFactoryTest, AssembleMultipleUsersFromJson) {
	//Simula la llamada de getUserByID donde hay que agregar la respuesta a un array.
	UserFactory factory(NULL);
	Json::Value users;
	Json::Value array;
	Json::Value root;
	Json::Value content;
	Json::Value location;
	location["longitude"] = 1.0;
	location["latitude"] = 2.0;
	content["id"] = 10;
	content["name"] = "prueba";
	content["alias"] = "alias";
	content["photo_profile"] = "photo";
	content["email"] = "aasd@gmail.com";
	content["location"] = location;
	root["user"] = content;
	array.append(root);
	users["users"] = array;
	Json::Value pasar = users.get("users", "ERROR");
	list<User*> lista = factory.assembleUsersFromJson(pasar);
	ASSERT_TRUE(lista.size() == 1);
}