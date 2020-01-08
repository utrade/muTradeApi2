add_library( FutFutCustom MODULE
	externalInterface.cpp
	futFutNew.cpp
	price.cpp
    futFutNewHedging.cpp
	../common/common.cpp
)
include_directories(../common)
