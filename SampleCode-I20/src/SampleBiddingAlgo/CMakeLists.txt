add_library(  SampleBiddingAlgo MODULE       
       externalInterface.cpp
       ../common/orderWrapper.cpp
       ../common/common.cpp
       sampleAlgo.cpp
)
include_directories(../common)
