//
// Created by matias on 5/4/16.
//

#include <boost/filesystem.hpp>
#include "MatchServicesTest.h"


ProfileServicesTest::ProfileServicesTest() { }

ProfileServicesTest::~ProfileServicesTest() { }

void ProfileServicesTest::SetUp() {
	boost::filesystem::remove_all(DB_FILE);
	this->connector = new DBConnector(DB_FILE);
	this->dao = new MatchDAO(connector);
	this->service = new MatchServices(this->dao, NULL);
}

void ProfileServicesTest::TearDown() {
	delete this->connector;
	delete this->dao;
	delete this->service;
	boost::filesystem::remove_all(DB_FILE);
}

TEST_F(MatchServicesTest, noMatchTestAndAddTwice) {

	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "foo",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "foo", 2 , "", "F", 18,"", intereses, location);
	int likes = service->getNumberOfLikes(&userA);
	ASSERT_EQ(0, likes );
	int matches = service->getNumberOfMatches(&userA);
	ASSERT_EQ(0,matches);
	this->service->likeAUser(&userA, &userB);
	likes = service->getNumberOfLikes(&userA);
	ASSERT_EQ(1, likes);
	matches = service->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	this->service->likeAUser(&userA, &userB);
	likes = service->getNumberOfLikes(&userA);
	ASSERT_EQ(1, likes);
	matches = service->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
}

TEST_F(MatchServicesTest, MatchTest) {
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "foo",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "foo", 2 , "", "F", 18,"", intereses, location);
	int likes = service->getNumberOfLikes(&userA);
	ASSERT_EQ(0, likes);
	int matches = service->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	service->likeAUser(&userA, &userB);
	likes = service->getNumberOfLikes(&userA);
	ASSERT_EQ(1, likes);
	matches = service->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	service->likeAUser(&userB, &userA);
	likes = service->getNumberOfLikes(&userB);
	ASSERT_EQ(1, likes);
	matches = service->getNumberOfMatches(&userB);
	ASSERT_EQ(1, matches);
	matches = service->getNumberOfMatches(&userA);
	ASSERT_EQ(1, matches);
	ASSERT_TRUE(dao->checkForMatch(&userA, &userB));

}

