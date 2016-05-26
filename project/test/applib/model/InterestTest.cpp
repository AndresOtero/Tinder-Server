//
// Created by matias on 5/26/16.
//

#include <Interest.h>
#include "InterestTest.h"


InterestTest::InterestTest() { }

InterestTest::~InterestTest() { }


void InterestTest::SetUp() {
	Test::SetUp();
}

void InterestTest::TearDown() {
	Test::TearDown();
}


TEST_F(InterestTest, setAndRetrieveInformation) {
	Interest interes("categoria", "valor");
	ASSERT_EQ(interes.getCategory(), "categoria");
	ASSERT_EQ(interes.getValue(), "valor");
}

TEST_F(InterestTest, comparisonTest) {
	Interest interes1("A", "A");
	Interest interes2("B", "B");
	Interest interes3("A", "B");
	ASSERT_FALSE(interes1 == interes2);
	ASSERT_FALSE(interes1 == interes3);
	ASSERT_TRUE(interes1 == interes1);
}