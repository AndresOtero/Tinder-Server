//
// Created by matias on 4/16/16.
//

#include <DBConnector.h>
#include <MatchDAO.h>
#include "MatchDAOTest.h"

MatchDAOTest::MatchDAOTest() { }

MatchDAOTest::~MatchDAOTest() { }

void MatchDAOTest::SetUp() { }

void MatchDAOTest::TearDown() { }

TEST_F(MatchDAOTest, noMatchTestAndAddTwice) {
	DBConnector connector("/tmp/testsMatch");
	connector.deleteKey("matias:1");
	MatchDAO match(&connector);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA(1, "caca", "matias", "", "M", 18,"", intereses, location);
	User userB(2, "caca", "maria", "", "F", 18,"", intereses, location);
	int likes = match.getNumberOfLikes(&userA);
	ASSERT_TRUE(likes == 0);
	int matches = match.getNumberOfMatches(&userA);
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike(&userA, &userB));
	likes = match.getNumberOfLikes(&userA);
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches(&userA);
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike(&userA, &userB));
	likes = match.getNumberOfLikes(&userA);
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches(&userA);
	ASSERT_TRUE(matches == 0);
	connector.deleteKey("matias:1");
}

TEST_F(MatchDAOTest, MatchTest) {
	DBConnector connector("/tmp/testsMatch");
	connector.deleteKey("matias:1");
	connector.deleteKey("maria:2");
	MatchDAO match(&connector);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA(1, "caca", "matias", "", "M", 18,"", intereses, location);
	User userB(2, "caca", "maria", "", "F", 18,"", intereses, location);
	int likes = match.getNumberOfLikes(&userA);
	ASSERT_TRUE(likes == 0);
	int matches = match.getNumberOfMatches(&userA);
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike(&userA, &userB));
	likes = match.getNumberOfLikes(&userA);
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches(&userA);
	ASSERT_TRUE(matches == 0);
	ASSERT_FALSE(match.checkForMatch(&userA, &userB));
	ASSERT_TRUE(match.saveLike(&userB, &userA));
	likes = match.getNumberOfLikes(&userB);
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches(&userB);
	ASSERT_TRUE(matches == 1);
	matches = match.getNumberOfMatches(&userA);
	ASSERT_TRUE(matches == 1);
	ASSERT_TRUE(match.checkForMatch(&userA, &userB));
	ASSERT_TRUE(match.checkForMatch(&userB, &userA));
	connector.deleteKey("matias:1");
	connector.deleteKey("maria:2");

}