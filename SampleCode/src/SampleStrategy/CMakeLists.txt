add_library(SampleStrategy MODULE
  externalInterface.cpp
  ../common/orderWrapper.cpp
  sample.cpp
  )
include_directories(../common)
