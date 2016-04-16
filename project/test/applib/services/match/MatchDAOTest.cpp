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
	int likes = match.getNumberOfLikes("matias", "1");
	ASSERT_TRUE(likes == 0);
	int matches = match.getNumberOfMatches("matias", "1");
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike("matias", "1", "maria", "2"));
	likes = match.getNumberOfLikes("matias", "1");
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches("matias", "1");
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike("matias", "1", "maria", "2"));
	likes = match.getNumberOfLikes("matias", "1");
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches("matias", "1");
	ASSERT_TRUE(matches == 0);
	connector.deleteKey("matias:1");
}

TEST_F(MatchDAOTest, MatchTest) {
	DBConnector connector("/tmp/testsMatch");
	connector.deleteKey("matias:1");
	connector.deleteKey("maria:2");
	MatchDAO match(&connector);
	int likes = match.getNumberOfLikes("matias", "1");
	ASSERT_TRUE(likes == 0);
	int matches = match.getNumberOfMatches("matias", "1");
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike("matias", "1", "maria", "2"));
	likes = match.getNumberOfLikes("matias", "1");
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches("matias", "1");
	ASSERT_TRUE(matches == 0);
	ASSERT_TRUE(match.saveLike("maria", "2", "matias", "1"));
	likes = match.getNumberOfLikes("maria", "2");
	ASSERT_TRUE(likes == 1);
	matches = match.getNumberOfMatches("maria", "2");
	ASSERT_TRUE(matches == 1);
	matches = match.getNumberOfMatches("matias", "1");
	ASSERT_TRUE(matches == 1);
	connector.deleteKey("matias:1");
	connector.deleteKey("maria:2");
}