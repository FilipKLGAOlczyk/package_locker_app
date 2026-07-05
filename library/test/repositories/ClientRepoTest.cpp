#include <boost/test/unit_test.hpp>
#include <typedefs.h>
#include <repositories/ClientRepo.h>

#include "model/Client.h"


struct TestSuiteClientRepoFixture {
    ClientRepo clientRepo;
    ClientPtr client0;
    ClientPtr client1;
    ClientPtr client2;
    TestSuiteClientRepoFixture() {
        client0 = std::make_shared<Client>(0,"Filip", "Olczyk", "cos@tam.com");
        client1 = std::make_shared<Client>(1, "Jano", "Deweloper", "low@cortisol.pl");
        client2 = std::make_shared<Client>(2, "Nie", "Wiem", "tak@nie.com");
    }
    ~TestSuiteClientRepoFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(ClientRepoFixture, TestSuiteClientRepoFixture)
BOOST_AUTO_TEST_CASE(BasicClientRepoTest) {
    clientRepo.add(client0);
    BOOST_TEST(clientRepo.size()==1);
    BOOST_TEST(clientRepo.findBy([](const ClientPtr &client){return client->getId()==0;})==client0);
    clientRepo.add(client1);
    BOOST_TEST(clientRepo.size()==2);
    BOOST_TEST(clientRepo.findBy([](const ClientPtr &client){return client->getId()==1;})==client1);
    clientRepo.remove(client1);
    BOOST_TEST(clientRepo.size()==1);
    BOOST_TEST(clientRepo.findBy([](const ClientPtr &client){return client->getId()==1;})==nullptr);
    clientRepo.add(client2);
    BOOST_TEST(clientRepo.size()==2);
    BOOST_TEST(clientRepo.findBy([](const ClientPtr &client){return client->getId()==2;})==client2);
    BOOST_TEST(clientRepo.report()==client0->getInfo() + "\n" + client2->getInfo() + "\n");
}
BOOST_AUTO_TEST_CASE(ClientRepoException) {
    BOOST_REQUIRE_THROW(clientRepo.add(nullptr), std::invalid_argument);
    BOOST_REQUIRE_THROW(clientRepo.remove(nullptr), std::invalid_argument);
}


BOOST_AUTO_TEST_SUITE_END()