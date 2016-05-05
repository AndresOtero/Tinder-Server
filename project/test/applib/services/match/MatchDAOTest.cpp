//
// Created by matias on 4/16/16.
//

#include <DBConnector.h>
#include <MatchDAO.h>
#include "MatchDAOTest.h"
#include "boost/filesystem.hpp"
MatchDAOTest::MatchDAOTest() { }

MatchDAOTest::~MatchDAOTest() { }

void MatchDAOTest::SetUp() {
	boost::filesystem::remove_all(DB_FILE);
	this->connector = new DBConnector(DB_FILE);
	this->dao = new MatchDAO(connector);
}

void MatchDAOTest::TearDown() {
	delete this->connector;
	delete this->dao;
	boost::filesystem::remove_all(DB_FILE);
}

TEST_F(MatchDAOTest, noMatchTestAndAddTwice) {

	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "foo",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "foo", 2 , "", "F", 18,"", intereses, location);
	int likes = dao->getNumberOfLikes(&userA);
	ASSERT_EQ(0, likes );
	int matches = dao->getNumberOfMatches(&userA);
	ASSERT_EQ(0,matches);
	dao->saveLike(&userA, &userB);
	likes = dao->getNumberOfLikes(&userA);
	ASSERT_EQ(1, likes);
	matches = dao->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	dao->saveLike(&userA, &userB);
	likes = dao->getNumberOfLikes(&userA);
	ASSERT_EQ(2, likes);
	matches = dao->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
}

TEST_F(MatchDAOTest, MatchTest) {
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "foo",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "foo", 2 , "", "F", 18,"", intereses, location);
	int likes = dao->getNumberOfLikes(&userA);
	ASSERT_EQ(0, likes);
	int matches = dao->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	dao->saveLike(&userA, &userB);
	likes = dao->getNumberOfLikes(&userA);
	ASSERT_EQ(1, likes);
	matches = dao->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	ASSERT_FALSE(dao->checkForMatch(&userA, &userB));
	dao->saveLike(&userB, &userA);
	likes = dao->getNumberOfLikes(&userB);
	ASSERT_EQ(1, likes);
	matches = dao->getNumberOfMatches(&userB);
	ASSERT_EQ(0, matches);
	matches = dao->getNumberOfMatches(&userA);
	ASSERT_EQ(0, matches);
	ASSERT_FALSE(dao->checkForMatch(&userA, &userB));

}