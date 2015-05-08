add_definitions(-fpermissive)
add_definitions(-fPIC)
add_library(customJavaTest MODULE
    externalInterface.cpp
    )
target_link_libraries(customJavaTest
    ${CMAKE_SOURCE_DIR}/src/javaStrategy/libcustomHft.so
)

