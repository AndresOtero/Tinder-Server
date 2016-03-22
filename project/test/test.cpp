#define BOOST_TEST_MODULE SqrTests
#include <boost/test/unit_test.hpp>
#include "dispatcher/EndPoint.h"
#include <string>
#include <iostream>
using namespace std;

BOOST_AUTO_TEST_CASE(FailTest)
{
	EndPoint ep("asdasd");
	string uri = "asdasd";
	ep.handle(uri);
	cout << "prueba" << endl;
    BOOST_CHECK_EQUAL(5, 2);
}

