#include <boost/test/unit_test.hpp>
#include "managers/LockerManager.h"
#include "model/Locker.h"

    LockerManager lockerManager;


BOOST_AUTO_TEST_CASE(RegisterLockerManagerTest) {
    BOOST_TEST(lockerManager.registerLocker(0, "Lodz", 10) == true);
    BOOST_TEST(lockerManager.registerLocker(1, "Wloszczowa", 5)==true);
}
BOOST_AUTO_TEST_CASE(BasicLockerManagerTest) {
    BOOST_TEST(lockerManager.getLocker(0)->getId()==0);
    BOOST_TEST(lockerManager.getLocker(1)->getId()==1);
}
BOOST_AUTO_TEST_CASE(FailedLockerRegister) {
    BOOST_TEST(lockerManager.registerLocker(0, "Warszawa", 120) == false);
}