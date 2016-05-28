//
// Created by matias on 5/26/16.
//

#include <Candidate.h>
#include "CandidateTest.h"


CandidateTest::CandidateTest() {

}

CandidateTest::~CandidateTest() {

}

void CandidateTest::SetUp() {
	Test::SetUp();
}

void CandidateTest::TearDown() {
	Test::TearDown();
}

TEST_F(CandidateTest, SetAndRetrieveInformation) {
	Candidate candidate(NULL);
	ASSERT_EQ(candidate.score, 0);
	ASSERT_EQ(candidate.numLiked, 0);
	ASSERT_EQ(candidate.distanceToUser, 0);
	ASSERT_TRUE(candidate.getUser() == NULL);
}