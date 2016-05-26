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