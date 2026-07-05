#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Locker.h"
#include "model/Parcel.h"
#include "model/Client.h"
#include "model/parcels/Standard.h"

struct TestSuiteLockerFixture{
    ClientPtr client1;
    ClientPtr client2;
    LockerPtr locker1;
    LockerPtr locker2;
    ParcelPtr parcel1;

    TestSuiteLockerFixture() {
        client1 = std::make_shared<Client>(1, "Filip", "Olczyk", "olczykfilip@gmail.com");
        client2 = std::make_shared<Client>(2, "Jan", "Opala","low.cortisol@gmail.com");
        locker1 = std::make_shared<Locker>(1, "Lodz", 10);
        locker2 = std::make_shared<Locker>(2, "Radom", 1);
        parcel1 = std::make_shared<Standard>(1, ParcelStatus::registered, client2, client1, locker2, locker1, 20);
    }
    ~TestSuiteLockerFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteLocker, TestSuiteLockerFixture)
    BOOST_AUTO_TEST_CASE(BasicLockerTest) {
    BOOST_TEST(locker2->getId() == 2);
    BOOST_TEST(locker2->getLocation() == "Radom");
    BOOST_TEST(locker2->getLockerCount() == 1);
    BOOST_TEST(locker2->isFull()==false);
    BOOST_TEST(locker2->getCurrentParcels().size()==0);
    }
BOOST_AUTO_TEST_CASE(AddingParcel) {
    locker2->addParcel(parcel1);
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
    BOOST_TEST(locker2->isFull()==true);
}
BOOST_AUTO_TEST_CASE(AddNullptr) {
    BOOST_REQUIRE_THROW(locker2->addParcel(nullptr), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(LockerOverflow) {
    ParcelPtr parcel2 = std::make_shared<Standard>(2, ParcelStatus::registered, client2, client1, locker2, locker1, 25);
    locker2->addParcel(parcel1);
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
    BOOST_TEST(locker2->isFull()==true);
    BOOST_REQUIRE_THROW(locker2->addParcel(parcel2), std::length_error);
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
}
BOOST_AUTO_TEST_CASE(RemovingParcel) {
    locker2->addParcel(parcel1);
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
    BOOST_TEST(locker2->isFull()==true);
    locker2->removeParcel(parcel1);
    BOOST_TEST(locker2->getCurrentParcels().size()==0);
    BOOST_TEST(locker2->isFull()==false);
}


BOOST_AUTO_TEST_SUITE_END()
