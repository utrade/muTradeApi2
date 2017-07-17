
add_definitions(-fpermissive)
add_definitions(-fPIC)
add_definitions(-fno-strict-aliasing)
add_definitions(-O2)
add_definitions(-D_FORTIFY_SOURCE=2)
add_definitions(-fwrapv)

add_library(customPythonTest MODULE
    externalInterface.cpp 
    )
target_link_libraries(customPythonTest
  ${CMAKE_SOURCE_DIR}/src/pythonStrategy/libpyContextDeps.so
  ${CMAKE_SOURCE_DIR}/src/pythonStrategy/libpyContextMgr.so
  )

