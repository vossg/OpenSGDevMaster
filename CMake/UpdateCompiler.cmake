
MESSAGE(STATUS "Update Compiler Settings")

IF(CMAKE_COMPILER_IS_GNUCC)

    IF(LINUX)
        IF(OSG_ENABLE_SSE2)

            MESSAGE(STATUS "Apply sse2 settings")

            IF(CMAKE_CXX_FLAGS)
                string(REGEX MATCH "-msse2 -mfpmath=sse" 
                                   SSE2_CXX_RES ${CMAKE_CXX_FLAGS})
            ENDIF(CMAKE_CXX_FLAGS)

            IF(CMAKE_C_FLAGS)
                string(REGEX MATCH "-msse2 -mfpmath=sse" 
                                   SSE2_C_RES ${CMAKE_C_FLAGS})
            ENDIF(CMAKE_C_FLAGS)

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

            IF(CMAKE_CXX_FLAGS)
                STRING(REPLACE " -msse2 -mfpmath=sse" "" 
                       TMP_CXX_FLAGS ${CMAKE_CXX_FLAGS})
            ENDIF(CMAKE_CXX_FLAGS)

            IF(CMAKE_C_FLAGS)
                STRING(REPLACE " -msse2 -mfpmath=sse" "" 
                       TMP_C_FLAGS ${CMAKE_C_FLAGS})
            ENDIF(CMAKE_C_FLAGS)

            SET(CMAKE_CXX_FLAGS ${TMP_CXX_FLAGS} 
                                CACHE STRING "OpenSG defaults" FORCE )
            SET(CMAKE_C_FLAGS   ${TMP_C_FLAGS} 
                                CACHE STRING "OpenSG defaults" FORCE )
            

        ENDIF(OSG_ENABLE_SSE2)
    ENDIF(LINUX)

ENDIF(CMAKE_COMPILER_IS_GNUCC)

