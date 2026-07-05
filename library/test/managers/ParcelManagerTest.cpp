#include "managers/ParcelManager.h"
#include "model/Parcel.h"
#include "model/parcels/Insured.h"
#include "model/parcels/Express.h"
#include "model/parcels/Standard.h"
#include <boost/test/unit_test.hpp>
#include "model/Locker.h"

#include "model/Client.h"

struct TestSuiteParcelManagerFixture {
    ParcelManager parcelManager;
    ClientPtr client0;
    ClientPtr client1;
    LockerPtr locker0;
    LockerPtr locker1;
    TestSuiteParcelManagerFixture() {
        client0 = std::make_shared<Client>(0, "Filip", "Olczyk", "high@cortisol.com");
        client1 = std::make_shared<Client>(1,"Jan", "Opala","low@cortisol.com");
        locker0 = std::make_shared<Locker>(0, "Lodz", 2);
        locker1 = std::make_shared<Locker>(1, "Radom", 2);
        parcelManager.registerParcel<Standard>(0,client0,client1,locker0,locker1,100);
        parcelManager.registerParcel<Express>(1,client0,client1,locker0,locker1,200, ExpressParcelDeadline::nextDay);
        parcelManager.registerParcel<Insured>(2,client1,client0,locker1,locker0,500, true, true, 2137.67);
    }
    ~TestSuiteParcelManagerFixture() = default;
};
BOOST_FIXTURE_TEST_SUITE(ParcelManagerTest, TestSuiteParcelManagerFixture)
BOOST_AUTO_TEST_CASE(RegisterParcelManagerTest) {
    BOOST_TEST(parcelManager.registerParcel<Standard>(5,client0,client1,locker0,locker1,100)==true);
    BOOST_TEST(parcelManager.registerParcel<Express>(6,client0,client1,locker0,locker1,200,ExpressParcelDeadline::weekendDelivery)==true);
    BOOST_TEST(parcelManager.registerParcel<Insured>(7,client0,client1,locker0,locker1,500,true,true,2137.67)==true);
}
BOOST_AUTO_TEST_CASE(BasicParcelManagerTest) {
    BOOST_TEST(parcelManager.getRecipientsParcels(client1).size()==2);
    BOOST_TEST(parcelManager.getRecipientsParcels(client0).size()==1);
    BOOST_TEST(parcelManager.getDestinationsParcels(locker0).size()==1);
    BOOST_TEST(parcelManager.getDestinationsParcels(locker1).size()==2);
}
BOOST_AUTO_TEST_CASE(ParcelStatusChangeTest) {
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="registered");
    BOOST_TEST(parcelManager.getParcel(1)->getStatusString()=="registered");
    BOOST_TEST(parcelManager.getParcel(2)->getStatusString()=="registered");
    BOOST_TEST(parcelManager.getParcel(0)->getOrigin()->getCurrentParcels().size()==0);
    BOOST_TEST(parcelManager.getParcel(0)->getDestination()->getCurrentParcels().size()==0);
    parcelManager.dispatchParcel(parcelManager.getParcel(2));
    BOOST_TEST(parcelManager.getParcel(2)->getStatusString()=="dispatched");
    BOOST_TEST(parcelManager.getParcel(2)->getOrigin()->getCurrentParcels().size()==1);
    BOOST_TEST(parcelManager.getParcel(0)->getDestination()->getCurrentParcels().size()==1);
    parcelManager.dispatchParcel(parcelManager.getParcel(0));
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="dispatched");
    BOOST_TEST(parcelManager.getParcel(0)->getOrigin()->getCurrentParcels().size()==1);
    BOOST_TEST(parcelManager.getParcel(1)->getStatusString()=="registered");
    parcelManager.dispatchParcel(parcelManager.getParcel(1));
    BOOST_TEST(parcelManager.getParcel(1)->getOrigin()->getCurrentParcels().size()==2);
    parcelManager.courierCollectParcel(parcelManager.getParcel(0));
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="enRoute");
    BOOST_TEST(parcelManager.getParcel(1)->getStatusString()=="dispatched");
    BOOST_TEST(parcelManager.getParcel(1)->getOrigin()->getCurrentParcels().size()==1);
    parcelManager.deliverParcel(parcelManager.getParcel(0));
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="deliveredToLocker");
    BOOST_TEST(parcelManager.getParcel(1)->getStatusString()=="dispatched");
    BOOST_TEST(parcelManager.getParcel(1)->getOrigin()->getCurrentParcels().size()==1);
    BOOST_TEST(parcelManager.getParcel(2)->getOrigin()->getCurrentParcels().size()==2);
    BOOST_TEST(parcelManager.getParcel(0)->getDestination()->getCurrentParcels().size()==2);
    parcelManager.collectParcel(parcelManager.getParcel(0));
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="collected");
    BOOST_TEST(parcelManager.getParcel(1)->getStatusString()=="dispatched");
    BOOST_TEST(parcelManager.getParcel(0)->getOrigin()->getCurrentParcels().size()==1);
    BOOST_TEST(parcelManager.getParcel(0)->getDestination()->getCurrentParcels().size()==1);
}
BOOST_AUTO_TEST_CASE(FailedToDispatch) {
    parcelManager.dispatchParcel(parcelManager.getParcel(0));
    parcelManager.dispatchParcel(parcelManager.getParcel(1));
    BOOST_TEST(parcelManager.getParcel(0)->getOrigin()->getCurrentParcels().size()==2);
    parcelManager.registerParcel<Standard>(3,client0,client1,locker0,locker1,100);
    BOOST_TEST(parcelManager.getParcel(3)->getStatusString()=="registered");
    BOOST_REQUIRE_THROW(parcelManager.dispatchParcel(parcelManager.getParcel(3)), std::length_error);
    BOOST_TEST(parcelManager.getParcel(3)->getStatusString()=="registered");
    BOOST_TEST(parcelManager.getParcel(3)->getOrigin()->getCurrentParcels().size()==2);
}
BOOST_AUTO_TEST_CASE(FailedToDeliver) {
    parcelManager.dispatchParcel(parcelManager.getParcel(0));
    parcelManager.dispatchParcel(parcelManager.getParcel(1));
    parcelManager.dispatchParcel(parcelManager.getParcel(2));
    BOOST_TEST(parcelManager.getParcel(0)->getOrigin()->getCurrentParcels().size()==2);
    BOOST_TEST(parcelManager.getParcel(2)->getStatusString()=="dispatched");
    parcelManager.courierCollectParcel(parcelManager.getParcel(2));
    BOOST_TEST(parcelManager.getParcel(2)->getStatusString()=="enRoute");
    BOOST_REQUIRE_THROW(parcelManager.deliverParcel(parcelManager.getParcel(2)), std::length_error);
    BOOST_TEST(parcelManager.getParcel(2)->getStatusString()=="enRoute");
    BOOST_TEST(parcelManager.getParcel(0)->getOrigin()->getCurrentParcels().size()==2);
}
BOOST_AUTO_TEST_CASE(FailedToChangeStatus) {
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="registered");
    parcelManager.deliverParcel(parcelManager.getParcel(0));
    BOOST_TEST(parcelManager.getParcel(0)->getStatusString()=="registered");
}

BOOST_AUTO_TEST_CASE(FailedToRegisterParcel) {
    BOOST_TEST(parcelManager.registerParcel<Express>(1,client1,client0,locker1,locker0,400, ExpressParcelDeadline::nextDay)==false);
}
BOOST_AUTO_TEST_SUITE_END()