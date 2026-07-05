//
// Created by Filip Olczyk on 30/05/2026.
//
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "model/Client.h"
#include "model/Parcel.h"
#include "model/Locker.h"
#include "model/parcels/Express.h"
#include "model/parcels/Insured.h"
#include "model/parcels/Standard.h"

struct TestSuiteParcelFixture{
    ClientPtr client1;
    ClientPtr client2;
    LockerPtr locker1;
    LockerPtr locker2;
    std::shared_ptr<Standard> standardParcel;
    std::shared_ptr<Standard> standardParcel2;
    TestSuiteParcelFixture() {
        client1 = std::make_shared<Client>(1, "Filip", "Olczyk", "olczykfilip@gmail.com");
        client2 = std::make_shared<Client>(2, "Jan", "Opala","low.cortisol@gmail.com");
        locker1 = std::make_shared<Locker>(1, "Lodz", 10);
        locker2 = std::make_shared<Locker>(2, "Radom", 1);
        standardParcel = std::make_shared<Standard>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20);
    }
    ~TestSuiteParcelFixture() = default;
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteParcel, TestSuiteParcelFixture)
BOOST_AUTO_TEST_CASE(BasicParcelTest) {
    BOOST_TEST(standardParcel->getId() == 1);
    BOOST_TEST(standardParcel->getStatusString() == "registered");
    BOOST_TEST(standardParcel->getSender()->getId() == 1);
    BOOST_TEST(standardParcel->getRecipient()->getId() == 2);
    BOOST_TEST(standardParcel->getOrigin()->getLocation() == "Lodz");
    BOOST_TEST(standardParcel->getDestination()->getLocation()=="Radom");
    BOOST_TEST(standardParcel->getBasePrice()==20);
}
BOOST_AUTO_TEST_CASE(ParcelDeliveryTest) {
    BOOST_TEST(standardParcel->getStatusString()=="registered");
    locker1->addParcel(standardParcel);
    standardParcel->setStatus(ParcelStatus::dispatched);
    BOOST_TEST(standardParcel->getStatusString()=="dispatched");
    locker1->removeParcel(standardParcel);
    standardParcel->setStatus(ParcelStatus::enRoute);
    locker2->addParcel(standardParcel);
    standardParcel->setStatus(ParcelStatus::deliveredToLocker);
    BOOST_TEST(standardParcel->getStatusString()=="deliveredToLocker");
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
    standardParcel2 = std::make_shared<Standard>(2, ParcelStatus::enRoute, client1, client2, locker1, locker2, 20);
    BOOST_REQUIRE_THROW(locker2->addParcel(standardParcel2), std::length_error);
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
    BOOST_TEST(standardParcel2->getStatusString()=="enRoute");

    standardParcel->setStatus(ParcelStatus::collected);
    BOOST_TEST(standardParcel->getStatusString()=="collected");
    locker2->removeParcel(standardParcel);
    BOOST_TEST(locker2->getCurrentParcels().size()==0);
    locker2->addParcel(standardParcel2);
    BOOST_TEST(locker2->getCurrentParcels().size()==1);
    standardParcel2->setStatus(ParcelStatus::deliveredToLocker);
    BOOST_TEST(standardParcel2->getStatusString()=="deliveredToLocker");
    locker2->removeParcel(standardParcel2);
}
BOOST_AUTO_TEST_CASE(StandardParcelTest) {
    BOOST_TEST(standardParcel->getBasePrice() == standardParcel->getActualPrice());
}
BOOST_AUTO_TEST_CASE(ExpressParcelTest) {
    auto expressParcel1 = std::make_shared<Express>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, ExpressParcelDeadline::weekendDelivery);
    BOOST_TEST(expressParcel1->getActualPrice() == 20*1.20);
    auto expressParcel2 = std::make_shared<Express>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, ExpressParcelDeadline::nextDay);
    BOOST_TEST(expressParcel2->getActualPrice() == 20*1.50);
    auto expressParcel3 = std::make_shared<Express>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, ExpressParcelDeadline::sameDay);
    BOOST_TEST(expressParcel3->getActualPrice() == 20*2.50);
}
BOOST_AUTO_TEST_CASE(InsuredParcelTest) {
    auto insuredParcel = std::make_shared<Insured>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, false, false, 1000);
    BOOST_TEST(insuredParcel->getActualPrice() == 20 + 1000*0.005);
    BOOST_TEST(insuredParcel->getDeclaredValue() == 1000);
    BOOST_TEST(insuredParcel->isFragile() == false);
    BOOST_TEST(insuredParcel->isDirectional() == false);

    auto insuredParcelFragile = std::make_shared<Insured>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, true, false, 1000);
    BOOST_TEST(insuredParcelFragile->getActualPrice() == 20 + 1000*0.015);
    BOOST_TEST(insuredParcelFragile->isFragile() == true);
    BOOST_TEST(insuredParcelFragile->isDirectional() == false);

    auto insuredParcelDirectional = std::make_shared<Insured>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, false, true, 1000);
    BOOST_TEST(insuredParcelDirectional->getActualPrice() == 20 + 1000*0.01);
    BOOST_TEST(insuredParcelDirectional->isFragile() == false);
    BOOST_TEST(insuredParcelDirectional->isDirectional() == true);

    auto insuredParcelBoth = std::make_shared<Insured>(1, ParcelStatus::registered, client1, client2, locker1, locker2, 20, true, true, 1000);
    BOOST_TEST(insuredParcelBoth->getActualPrice() == 20 + 1000*0.02);
    BOOST_TEST(insuredParcelBoth->isFragile() == true);
    BOOST_TEST(insuredParcelBoth->isDirectional() == true);
}

BOOST_AUTO_TEST_CASE(NegativeBasePrice) {
    BOOST_REQUIRE_THROW(auto parcel = std::make_shared<Standard>(1, ParcelStatus::registered, client1, client2, locker1, locker2, -10), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()