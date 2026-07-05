
#include <boost/test/unit_test.hpp>
#include "managers/ClientManager.h"
#include "model/Client.h"
#include <typedefs.h>


    ClientManager clientManager;



BOOST_AUTO_TEST_CASE(ClientManagerRegisterTest) {
    BOOST_TEST(clientManager.registerClient(1,"Filip", "Olczyk", "cos@tam.com")==true);
    BOOST_TEST(clientManager.registerClient(2, "Jano", "Deweloper", "low@cortisol.pl")==true);
    BOOST_TEST(clientManager.registerClient(3, "Nie", "Wiem", "tak@nie.com")==true);
}
BOOST_AUTO_TEST_CASE(ClientManagerGettersTest) {
    BOOST_TEST(clientManager.getClient("cos@tam.com")->getId()==1);
    BOOST_TEST(clientManager.getClient("low@cortisol.pl")->getId()==2);
    BOOST_TEST(clientManager.getClient("tak@nie.com")->getId()==3);
}

BOOST_AUTO_TEST_CASE(FailedClientRegistration) {
    //BOOST_CATCH(clientManager.registerClient(1,"Filip", "Olczyk", "cos@tam.com"));
    BOOST_TEST(clientManager.registerClient(1,"Filip", "Olczyk", "cos@tam.com")==false);
    BOOST_TEST(clientManager.registerClient(2, "Filip", "Drugi", "loaf@ofbread.com")==false);
}