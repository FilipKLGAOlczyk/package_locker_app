#include <boost/test/unit_test.hpp>
#include <typedefs.h>
#include <repositories/ParcelRepo.h>
#include "model/Parcel.h"
#include "model/parcels/Standard.h"
#include "repositories/ClientRepo.h"
#include "model/Locker.h"
#include "model/Client.h"

struct TestSuiteParcelRepoFixture {
    ParcelRepo parcelRepo;
    ParcelPtr parcel0;
    ParcelPtr parcel1;
    ParcelPtr parcel2;
    ClientRepo clientRepo;
    LockerPtr locker0;
    LockerPtr locker1;
    ClientPtr client0;
    ClientPtr client1;
    TestSuiteParcelRepoFixture() {
        locker0 = std::make_shared<Locker>(0, "Lodz", 10);
        locker1 = std::make_shared<Locker>(1, "Radom", 1);
        client0 = std::make_shared<Client>(0, "Filip", "Olczyk", "high@cortisol.com");
        client1 = std::make_shared<Client>(1, "Jan", "Opala","low@cortisol.com");
        clientRepo.add(client0);
        clientRepo.add(client1);
        parcel0 = std::make_shared<Standard>(0, ParcelStatus::registered, client0, client1, locker0, locker1, 100);
        parcel1 = std::make_shared<Standard>(1, ParcelStatus::registered, client0, client1, locker0, locker1, 100);
        parcel2 = std::make_shared<Standard>(2, ParcelStatus::registered, client1, client0, locker1, locker0, 100);
    }
    ~TestSuiteParcelRepoFixture() = default;
};
BOOST_FIXTURE_TEST_SUITE(ParcelRepoTest, TestSuiteParcelRepoFixture)
BOOST_AUTO_TEST_CASE(BasicParcelRepoTest) {
    BOOST_TEST(parcelRepo.size()==0);
    parcelRepo.add(parcel0);
    BOOST_TEST(parcelRepo.size()==1);
    BOOST_TEST(parcelRepo.findBy([](const ParcelPtr &parcel){return parcel->getId()==0;})==parcel0);
    parcelRepo.add(parcel1);
    BOOST_TEST(parcelRepo.size()==2);
    BOOST_TEST(parcelRepo.findBy([](const ParcelPtr &parcel){return parcel->getId()==1;})==parcel1);
    parcelRepo.add(parcel2);
    BOOST_TEST(parcelRepo.size()==3);
    BOOST_TEST(parcelRepo.findBy([](const ParcelPtr &parcel){return parcel->getId()==2;})==parcel2);
}
BOOST_AUTO_TEST_CASE(ParcelRepoExceptions) {
    BOOST_REQUIRE_THROW(parcelRepo.add(nullptr), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()