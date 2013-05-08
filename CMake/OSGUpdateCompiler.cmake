
MESSAGE(STATUS "Update Compiler Settings")

IF(CMAKE_COMPILER_IS_GNUCC)

    IF(LINUX OR APPLE)

        IF(NOT APPLE)
          SET(OSG_GCC_FPMATHOPT "-mfpmath=sse")
        ELSE()
          SET(OSG_GCC_FPMATHOPT "")
        ENDIF(NOT APPLE)

        IF(OSG_ENABLE_SSE2)

            MESSAGE(STATUS "Apply sse2 settings")

            IF(CMAKE_CXX_FLAGS)
                STRING(REGEX MATCH "-msse2 ${OSG_GCC_FPMATHOPT}" 
                                   SSE2_CXX_RES ${CMAKE_CXX_FLAGS})
            ENDIF(CMAKE_CXX_FLAGS)

            IF(CMAKE_C_FLAGS)
                STRING(REGEX MATCH "-msse2 ${OSG_GCC_FPMATHOPT}" 
                                   SSE2_C_RES ${CMAKE_C_FLAGS})
            ENDIF(CMAKE_C_FLAGS)

            IF(NOT SSE2_CXX_RES)
                SET(TMP_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2 ${OSG_GCC_FPMATHOPT}")


                SET(CMAKE_CXX_FLAGS ${TMP_CXX_FLAGS} 
                                    CACHE STRING "OpenSG defaults" FORCE )
            ENDIF(NOT SSE2_CXX_RES)

            IF(NOT SSE2_C_RES)
                SET(TMP_C_FLAGS "${CMAKE_C_FLAGS} -msse2 ${OSG_GCC_FPMATHOPT}")


                SET(CMAKE_C_FLAGS ${TMP_C_FLAGS} 
                                  CACHE STRING "OpenSG defaults" FORCE )
            ENDIF(NOT SSE2_C_RES)
            

        ELSE(OSG_ENABLE_SSE2)

            MESSAGE(STATUS "Remove sse2 settings")

            IF(CMAKE_CXX_FLAGS)
                STRING(REPLACE " -msse2 ${OSG_GCC_FPMATHOPT}" "" 
                       TMP_CXX_FLAGS ${CMAKE_CXX_FLAGS})
            ENDIF(CMAKE_CXX_FLAGS)

            IF(CMAKE_C_FLAGS)
                STRING(REPLACE " -msse2 ${OSG_GCC_FPMATHOPT}" "" 
                       TMP_C_FLAGS ${CMAKE_C_FLAGS})
            ENDIF(CMAKE_C_FLAGS)

            SET(CMAKE_CXX_FLAGS ${TMP_CXX_FLAGS} 
                                CACHE STRING "OpenSG defaults" FORCE )
            SET(CMAKE_C_FLAGS   ${TMP_C_FLAGS} 
                                CACHE STRING "OpenSG defaults" FORCE )
            

        ENDIF(OSG_ENABLE_SSE2)
    ENDIF(LINUX OR APPLE)

    IF(CMAKE_CXX_FLAGS)
       STRING(REGEX MATCH "__STDC_FORMAT_MACROS" 
       STDFORMAT_CXX_RES ${CMAKE_CXX_FLAGS})
    ENDIF(CMAKE_CXX_FLAGS)

    IF(CMAKE_C_FLAGS)
        STRING(REGEX MATCH "__STDC_FORMAT_MACROS" 
               STDFORMAT_C_RES ${CMAKE_C_FLAGS})
    ENDIF(CMAKE_C_FLAGS)

    IF(NOT STDFORMAT_CXX_RES)
      SET(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -D__STDC_FORMAT_MACROS"
          CACHE STRING "OpenSG defaults" FORCE )
    ENDIF(NOT STDFORMAT_CXX_RES)

    IF(NOT STDFORMAT_C_RES)
      SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -D__STDC_FORMAT_MACROS"
          CACHE STRING "OpenSG defaults" FORCE )
    ENDIF(NOT STDFORMAT_C_RES)

    ###########
    # GV stuff
    ###########

    IF(CMAKE_BUILD_TYPE STREQUAL "DebugGV" OR CMAKE_BUILD_TYPE STREQUAL "ReleaseGV")
      SET(OSG_ADD_CXX_FLAGS " -Wall -Wextra -Wno-unused-parameter")
      SET(OSG_ADD_C_FLAGS " -Wall -Wextra -Wno-unused-parameter")

      IF(CMAKE_BUILD_TYPE STREQUAL "ReleaseGV")
      SET(OSG_ADD_CXX_FLAGS " ${OSG_ADD_CXX_FLAGS} -Wno-strict-aliasing")
      ENDIF(CMAKE_BUILD_TYPE STREQUAL "ReleaseGV")
    ELSE()
      SET(OSG_ADD_CXX_FLAGS )
      SET(OSG_ADD_C_FLAGS )
    ENDIF()

ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(MSVC)
  IF(OSG_DISABLE_MICROSOFT_SECURE_CXXX)
    ADD_DEFINITIONS("-D_CRT_SECURE_NO_DEPRECATE")
    ADD_DEFINITIONS("-D_CRT_SECURE_NO_WARNINGS")
    ADD_DEFINITIONS("-D_CRT_NONSTDC_NO_DEPRECATE")
    ADD_DEFINITIONS("-D_SECURE_SCL=0")
    ADD_DEFINITIONS("-D_SCL_SECURE_NO_WARNINGS")
    ADD_DEFINITIONS("-D_SCL_SECURE_NO_DEPRECATE")
  ELSE()
    IF(OSG_DISABLE_MICROSOFT_SECURE_CXXX_DEBUG)
    ENDIF()
    IF(OSG_DISABLE_MICROSOFT_SECURE_CXXX_RELEASE)
    ENDIF()
  ENDIF()

  IF(OSG_DISABLE_MS_ITERATOR_DEBUGGING)
    ADD_DEFINITIONS("-D_HAS_ITERATOR_DEBUGGING=0")
  ENDIF(OSG_DISABLE_MS_ITERATOR_DEBUGGING)
ENDIF(MSVC)
