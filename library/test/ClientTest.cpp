/// @file
/// @brief Unit tests for the Client class.

#include <boost/test/unit_test.hpp>

#include "typedefs.h"
#include "model/Client.h"

struct TestSuiteClientFixture {

    ClientPtr client1;
    ClientPtr client2;
    TestSuiteClientFixture() {

        client1 = std::make_shared<Client>(1, "Filip", "Olczyk", "olczykfilip@gmail.com");
        client2 = std::make_shared<Client>(2, "Jan", "Opala","low.cortisol@gmail.com");
    }

    ~TestSuiteClientFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)
BOOST_AUTO_TEST_CASE(BasicClientTest) {
    BOOST_TEST(client1->getId() == 1);
    BOOST_TEST(client1->getEmail()=="olczykfilip@gmail.com");
    BOOST_TEST(client1->getFirstName()=="Filip");
    BOOST_TEST(client1->getLastName()=="Olczyk");
    BOOST_TEST(client1->getId()!=client2->getId());
}


BOOST_AUTO_TEST_SUITE_END()