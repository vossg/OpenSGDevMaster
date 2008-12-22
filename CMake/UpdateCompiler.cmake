
MESSAGE(STATUS "Update Compiler Settings")

IF(CMAKE_COMPILER_IS_GNUCC)

    IF(LINUX)
        IF(OSG_ENABLE_SSE2)

            MESSAGE(STATUS "Apply sse2 settings")

            string(REGEX MATCH "-msse2 -mfpmath=sse" 
                               SSE2_CXX_RES ${CMAKE_CXX_FLAGS})

            string(REGEX MATCH "-msse2 -mfpmath=sse" 
                               SSE2_C_RES ${CMAKE_C_FLAGS})

            IF(NOT SSE2_CXX_RES)
                SET(TMP_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 -mfpmath=sse")


                SET(CMAKE_CXX_FLAGS ${TMP_CXX_FLAGS} 
                                    CACHE STRING "OpenSG defaults" FORCE )
            ENDIF(NOT SSE2_CXX_RES)

            IF(NOT SSE2_C_RES)
                SET(TMP_C_FLAGS "${CMAKE_C_FLAGS} -msse2 -mfpmath=sse")


                SET(CMAKE_C_FLAGS ${TMP_C_FLAGS} 
                                  CACHE STRING "OpenSG defaults" FORCE )
            ENDIF(NOT SSE2_C_RES)
            

        ELSE(OSG_ENABLE_SSE2)

            MESSAGE(STATUS "Remove sse2 settings")

            STRING(REPLACE " -msse2 -mfpmath=sse" "" 
                   TMP_CXX_FLAGS ${CMAKE_CXX_FLAGS})

            STRING(REPLACE " -msse2 -mfpmath=sse" "" 
                   TMP_C_FLAGS ${CMAKE_C_FLAGS})

            SET(CMAKE_CXX_FLAGS ${TMP_CXX_FLAGS} 
                                CACHE STRING "OpenSG defaults" FORCE )
            SET(CMAKE_C_FLAGS   ${TMP_C_FLAGS} 
                                CACHE STRING "OpenSG defaults" FORCE )
            

        ENDIF(OSG_ENABLE_SSE2)
    ENDIF(LINUX)

ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(MSVC)

    IF(CMAKE_BUILD_TYPE STREQUAL "DebugRT")

        MESSAGE(STATUS "Apply DebugRT settings")

        STRING(REPLACE " msvcprt.lib msvcrt.lib" "" 
               TMP_CXX_STANDARD_LIBRARIES ${CMAKE_CXX_STANDARD_LIBRARIES})

        STRING(REPLACE " msvcrt.lib" "" 
               TMP_C_STANDARD_LIBRARIES ${CMAKE_C_STANDARD_LIBRARIES})

        STRING(REGEX MATCH "msvcprtd.lib msvcrtd.lib" 
                           MSVC_CXX_RES ${TMP_CXX_STANDARD_LIBRARIES})

        STRING(REGEX MATCH " msvcrtd.lib" 
                           MSVC_C_RES ${TMP_C_STANDARD_LIBRARIES})

        IF(NOT MSVC_CXX_RES)
            SET(TMP_CXX_STANDARD_LIBRARIES "${TMP_CXX_STANDARD_LIBRARIES} msvcprtd.lib msvcrtd.lib")


            SET(CMAKE_CXX_STANDARD_LIBRARIES ${TMP_CXX_STANDARD_LIBRARIES} 
                                             CACHE STRING "OpenSG defaults" FORCE )
        ENDIF(NOT MSVC_CXX_RES)

        IF(NOT MSVC_C_RES)
            SET(TMP_C_STANDARD_LIBRARIES "${TMP_C_STANDARD_LIBRARIES} msvcrtd.lib")

            SET(CMAKE_C_STANDARD_LIBRARIES ${TMP_C_STANDARD_LIBRARIES} 
                                           CACHE STRING "OpenSG defaults" FORCE )
        ENDIF(NOT MSVC_C_RES)

    ELSE(CMAKE_BUILD_TYPE STREQUAL "DebugRT")

        MESSAGE(STATUS "Apply Debug/Release settings")

        STRING(REPLACE " msvcprtd.lib msvcrtd.lib" "" 
               TMP_CXX_STANDARD_LIBRARIES ${CMAKE_CXX_STANDARD_LIBRARIES})

        STRING(REPLACE " msvcrtd.lib" "" 
               TMP_C_STANDARD_LIBRARIES ${CMAKE_C_STANDARD_LIBRARIES})

        STRING(REGEX MATCH "msvcprt.lib msvcrt.lib" 
                           MSVC_CXX_RES ${TMP_CXX_STANDARD_LIBRARIES})

        STRING(REGEX MATCH "msvcrt.lib" 
                           MSVC_C_RES ${TMP_C_STANDARD_LIBRARIES})

        IF(NOT MSVC_CXX_RES)
            SET(TMP_CXX_STANDARD_LIBRARIES "${TMP_CXX_STANDARD_LIBRARIES} msvcprt.lib msvcrt.lib")


            SET(CMAKE_CXX_STANDARD_LIBRARIES ${TMP_CXX_STANDARD_LIBRARIES} 
                                             CACHE STRING "OpenSG defaults" FORCE )
        ENDIF(NOT MSVC_CXX_RES)

        IF(NOT MSVC_C_RES)
            SET(TMP_C_STANDARD_LIBRARIES "${TMP_C_STANDARD_LIBRARIES} msvcrt.lib")

            SET(CMAKE_C_STANDARD_LIBRARIES ${TMP_C_STANDARD_LIBRARIES} 
                                           CACHE STRING "OpenSG defaults" FORCE )
        ENDIF(NOT MSVC_C_RES)

    ENDIF(CMAKE_BUILD_TYPE STREQUAL "DebugRT")

ENDIF(MSVC)