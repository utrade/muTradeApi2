#cmake -DCMAKE_BUILD_TYPE="Debug" ..
#cmake -DCMAKE_BUILD_TYPE="Release" ..
#LDFLAGS="-Wl,--as-needed"

cmake_minimum_required(VERSION 2.6)

project(muTrade)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#configure_file (
# "${muTrade_SOURCE_DIR}/config.h.in"
# "${muTrade_SOURCE_DIR}/config.h"
#)


set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED     OFF)
set(Boost_USE_STATIC_RUNTIME    ON)

unset(Boost_INCLUDE_DIR CACHE)
unset(Boost_LIBRARY_DIRS CACHE)

  #filesystem

find_package(Boost 1.51 REQUIRED COMPONENTS
  system
  regex
  serialization
  thread
  program_options
)

include_directories(${Boost_INCLUDE_DIRS})

#find_package(TBB REQUIRED)
#include_directories(${TBB_INCLUDE_DIRS})

#include_directories( /code/shared/jivjot/tbb42_20140122oss/include )

#find_package(QUICKFIX REQUIRED)
#include_directories(${QUICKFIX_INCLUDE_DIRS})

#find_package(QUICKFAST REQUIRED)
#include_directories(${QUICKFAST_INCLUDE_DIRS})

#find_package(ZMQ REQUIRED)
#include_directories(${ZMQ_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -Wall -fpermissive -fPIC  ")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fpermissive -pg")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x -Wall -O2 -fpermissive -fPIC ")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fpermissive -pg")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x -Wall -O2")
#set(CMAKE_EXE_LINKER_FLAGS "--no-as-needed")
include_directories(

  ${muTrade_SOURCE_DIR}/includes
  ${muTrade_SOURCE_DIR}/includes/sgLib
  ${muTrade_SOURCE_DIR}/includes/volumeProfile

  #${muTrade_SOURCE_DIR}/sgLibHelpers
  #${muTrade_SOURCE_DIR}/api2/helpers
  #${muTrade_SOURCE_DIR}/shared
  #${muTrade_SOURCE_DIR}/cm
  #${muTrade_SOURCE_DIR}/sg
  #${muTrade_SOURCE_DIR}/ed
  #${muTrade_SOURCE_DIR}/ed/common
  #${muTrade_SOURCE_DIR}/ed/cfh
#  ${muTrade_SOURCE_DIR}/test
#  ${muTrade_SOURCE_DIR}/tbt
#${muTrade_SOURCE_DIR}/multicastTbt
#  ${muTrade_SOURCE_DIR}/ed/orderLogReader
)

#include_directories(/home/hss/google-breakpad/src)

SET(EXECUTABLE_OUTPUT_PATH ${muTrade_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${muTrade_SOURCE_DIR}/bin)

#add_subdirectory( optionBidding )
add_subdirectory( src )
#add_subdirectory( ivcalc )
#add_subdirectory( sg )
#add_subdirectory( ed )
#add_subdirectory( test )
#add_subdirectory( tbt )
#add_subdirectory( multicastTbt )
#add_subdirectory( dispatcher )
#add_subdirectory( api2)

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

# Redhat/CentOS
#   /usr/lib64/liblzo2.so.2.0.0
# Debian/Ububntu
#   /usr/lib/x86_64-linux-gnu/liblzo2.so.2.0.0

install(FILES
  /usr/local/lib/libboost_thread.so.1.42.0
  /usr/local/lib/libboost_program_options.so.1.42.0
  /usr/local/lib/libboost_system.so.1.42.0
  /usr/local/lib/libquickfix.so.14.0.0
  /usr/local/lib/libquickfix.so.14
  /usr/lib64/liblzo2.so.2.0.0
#  /usr/lib/x86_64-linux-gnu/liblzo2.so.2.0.0
  DESTINATION lib
)

install(FILES
  ${muTrade_SOURCE_DIR}/bin/utrade.conf
  ${muTrade_SOURCE_DIR}/bin/FIX42_NSE.xml
  ${muTrade_SOURCE_DIR}/bin/FIX42.xml
  ${muTrade_SOURCE_DIR}/bin/FIXT11.xml
  ${muTrade_SOURCE_DIR}/bin/hft-settings
  ${muTrade_SOURCE_DIR}/scripts/displayHftLog.sh
  ${muTrade_SOURCE_DIR}/scripts/genConfirmationsCSV.sh
  ${muTrade_SOURCE_DIR}/scripts/intradayRestartServer.sh
  ${muTrade_SOURCE_DIR}/scripts/latestStrategyLog.sh
  ${muTrade_SOURCE_DIR}/scripts/latestHftLog.sh
  ${muTrade_SOURCE_DIR}/scripts/runHftIntraday.sh
  ${muTrade_SOURCE_DIR}/scripts/stopServer.sh
  ${muTrade_SOURCE_DIR}/scripts/genConfirmations
  ${muTrade_SOURCE_DIR}/scripts/HOWTO
  ${muTrade_SOURCE_DIR}/scripts/isServerRunning.sh
  ${muTrade_SOURCE_DIR}/scripts/restartServer.sh
  ${muTrade_SOURCE_DIR}/scripts/runHft.sh
  DESTINATION .
)
  
install(FILES
  ${muTrade_SOURCE_DIR}/bin/config/cacert.pem
  ${muTrade_SOURCE_DIR}/bin/config/clients.csv
  ${muTrade_SOURCE_DIR}/bin/config/risk.csv
  ${muTrade_SOURCE_DIR}/bin/config/globalrisk.csv
  ${muTrade_SOURCE_DIR}/bin/config/scrip_master_data.txt
  DESTINATION config
)
  
install(FILES
  ${muTrade_SOURCE_DIR}/bin/config/tbt/client/cmClientSymbols.txt
  ${muTrade_SOURCE_DIR}/bin/config/tbt/client/foClientSymbols.txt
  DESTINATION config/tbt/client
)

install(FILES
  ${muTrade_SOURCE_DIR}/bin/config/params/params.conf
  DESTINATION config/params
)

include(CPack)
