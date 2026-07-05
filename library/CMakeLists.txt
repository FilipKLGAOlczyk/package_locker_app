cmake_minimum_required(VERSION 3.10)

project(Library)

if(APPLE)
    set(BOOST_ROOT "/opt/homebrew")
endif (APPLE)

set(SOURCE_FILES
        include/model/Client.h
        src/Client.cpp
        include/model/Locker.h
        src/Locker.cpp
        include/model/Parcel.h
        src/Parcel.cpp
        include/typedefs.h
        src/repositories/ClientRepo.cpp
        include/repositories/ClientRepo.h
        src/repositories/LockerRepo.cpp
        include/repositories/LockerRepo.h
        test/repositories/LockerRepoTest.cpp
        src/repositories/ParcelRepo.cpp
        include/repositories/ParcelRepo.h
        test/repositories/ParcelRepoTest.cpp
        include/model/parcels/Standard.h
        src/parcels/Standard.cpp
        include/model/parcels/Express.h
        src/parcels/Express.cpp
        include/model/parcels/Insured.h
        src/parcels/Insured.cpp
        src/managers/ClientManager.cpp
        include/managers/ClientManager.h
        src/managers/LockerManager.cpp
        include/managers/LockerManager.h
        src/managers/ParcelManager.cpp
        include/managers/ParcelManager.h
        include/Exceptions.h
        test/managers/ClientManagerTest.cpp
        test/managers/LockerManagerTest.cpp
        test/managers/ParcelManagerTest.cpp
)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

enable_testing()

find_package(Boost 1.80.0 CONFIG COMPONENTS unit_test_framework date_time REQUIRED)

find_package(nlohmann_json REQUIRED)
target_link_libraries(Library PUBLIC nlohmann_json::nlohmann_json)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/ClientTest.cpp
        test/ParcelTest.cpp
        test/LockerTest.cpp
        test/repositories/ClientRepoTest.cpp
        test/repositories/LockerRepoTest.cpp
        test/repositories/ParcelRepoTest.cpp
        test/managers/ClientManagerTest.cpp
        test/managers/LockerManagerTest.cpp
        test/managers/ParcelManagerTest.cpp
        include/model/parcels/Standard.h
        src/parcels/Standard.cpp
        include/model/parcels/Express.h
        src/parcels/Express.cpp
        include/model/parcels/Insured.h
        src/parcels/Insured.cpp
        include/Exceptions.h
)

add_executable (LibraryTester ${SOURCE_TEST_FILES})

target_link_libraries (LibraryTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(LibraryTest LibraryTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})