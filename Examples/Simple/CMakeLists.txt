
if(OSG_BUILD_ACTIVE)
    INCLUDE(./CMakeLists.fromosg.txt)
else()
    INCLUDE(./CMakeLists.standalone.txt)
endif()