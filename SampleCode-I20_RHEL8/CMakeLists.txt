#cmake -DCMAKE_BUILD_TYPE="Debug" ..
#cmake -DCMAKE_BUILD_TYPE="Release" ..
#LDFLAGS="-Wl,--as-needed"

cmake_minimum_required(VERSION 2.6)

project(muTrade)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

CMAKE_POLICY(SET CMP0054 NEW)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -Wall -fpermissive -fPIC  ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -Wall -O2 -fpermissive -fPIC ")

set(Boost_INCLUDE_PATH /usr/local/include/boost-1.66.0/include/)

include_directories(
  ${muTrade_SOURCE_DIR}/includes
  ${Boost_INCLUDE_PATH}
)

SET(EXECUTABLE_OUTPUT_PATH ${muTrade_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${muTrade_SOURCE_DIR}/bin)

add_subdirectory( src )

set(CPACK_COMPONENTS_ALL applications)
set(CPACK_GENERATOR "STGZ")
set(CPACK_PACKAGE_CONTACT "info@utradesolutions.com")
set(CPACK_PACKAGE_DESCRIPTION "muTrade")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "muTrade")
SET(CPACK_PACKAGE_FILE_NAME "muTrade-1.0.0-Linux")
set(CPACK_PACKAGE_VENDOR "uTrade Solutions Pvt Ltd")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")


include(CPack)
