#include <boost/test/unit_test.hpp>
#include <typedefs.h>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <repositories/LockerRepo.h>
#include "model/Locker.h"


struct TestSuiteLockerRepoFixture {
    LockerRepo lockerRepo;
    LockerPtr locker0;
    LockerPtr locker1;
    LockerPtr locker2;
    TestSuiteLockerRepoFixture() {
        locker0 = std::make_shared<Locker>(0, "Lodz", 10);
        locker1 = std::make_shared<Locker>(1, "Radom", 1);
        locker2 = std::make_shared<Locker>(2, "Warszawa", 10);
    }
    ~TestSuiteLockerRepoFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(BasicLockerRepoTest, TestSuiteLockerRepoFixture)
BOOST_AUTO_TEST_CASE(LockerRepoFixture) {
    lockerRepo.add(locker0);
    BOOST_TEST(lockerRepo.size()==1);
    lockerRepo.add(locker1);
    BOOST_TEST(lockerRepo.size()==2);
    lockerRepo.remove(locker1);
    BOOST_TEST(lockerRepo.size()==1);
    lockerRepo.add(locker2);
    BOOST_TEST(lockerRepo.size()=2);
}
BOOST_AUTO_TEST_CASE(LockerFindByMethodTest) {
    lockerRepo.add(locker0);
    lockerRepo.add(locker1);
    lockerRepo.add(locker2);
    lockerRepo.remove(locker1);
    BOOST_TEST(lockerRepo.findBy([](const LockerPtr &locker){return locker->getId()==0;})==locker0);
    BOOST_TEST(lockerRepo.findBy([](const LockerPtr &locker){return locker->getId()==1;})==nullptr);
    BOOST_TEST(lockerRepo.findBy([](const LockerPtr &locker){return locker->getId()==2;})==locker2);
}
BOOST_AUTO_TEST_CASE(LockerRepoException) {
    BOOST_REQUIRE_THROW(lockerRepo.add(nullptr), std::invalid_argument);
    BOOST_REQUIRE_THROW(lockerRepo.remove(nullptr), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()