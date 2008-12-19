
MESSAGE(STATUS "Applying Compiler Defaults")

SET(OSG_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DOSG_DEBUG")
SET(OSG_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} -DOSG_DEBUG")

SET(OSG_CXX_FLAGS ${CMAKE_CXX_FLAGS})
SET(OSG_C_FLAGS   ${CMAKE_C_FLAGS})

SET(OSG_EXE_LINKER_FLAGS    ${CMAKE_EXE_LINKER_FLAGS})
SET(OSG_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

IF(CMAKE_COMPILER_IS_GNUCC)

    IF(OSG_PLATFORM_64 AND LINUX)
        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -m64")
        SET(OSG_C_FLAGS   "${OSG_C_FLAGS} -m64")

        SET(OSG_EXE_LINKER_FLAGS    "${OSG_EXE_LINKER_FLAGS} -m64")
        SET(OSG_SHARED_LINKER_FLAGS "${OSG_SHARED_LINKER_FLAGS} -m64")

    ENDIF(OSG_PLATFORM_64 AND LINUX)

ENDIF(CMAKE_COMPILER_IS_GNUCC)






SET(CMAKE_CXX_FLAGS       ${OSG_CXX_FLAGS} 
                          CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS         ${OSG_C_FLAGS} 
                          CACHE STRING "OpenSG defaults" FORCE )

SET(CMAKE_CXX_FLAGS_DEBUG ${OSG_CXX_FLAGS_DEBUG} 
                          CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS_DEBUG   ${OSG_C_FLAGS_DEBUG} 
                          CACHE STRING "OpenSG defaults" FORCE )


SET(CMAKE_EXE_LINKER_FLAGS    ${OSG_EXE_LINKER_FLAGS} 
                              CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_SHARED_LINKER_FLAGS ${OSG_SHARED_LINKER_FLAGS} 
                              CACHE STRING "OpenSG defaults" FORCE )

   

###########
# GV stuff
###########

IF(CMAKE_COMPILER_IS_GNUCC)
    SET(OSG_CXX_FLAGS_GV " -Wreturn-type -Wold-style-cast -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE -Wwrite-strings -Werror")

    SET(OSG_C_FLAGS_GV " -Wreturn-type -Wold-style-cast -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE -Wwrite-strings -Werror")

    SET(OSG_SHARED_LINKER_FLAGS_GV " -Wl,--no-undefined")


##########
# Debug
##########

    SET(CMAKE_CXX_FLAGS_DEBUGGV 
        "${CMAKE_CXX_FLAGS_DEBUG}${OSG_CXX_FLAGS_GV}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_DEBUGGV 
        "${CMAKE_C_FLAGS_DEBUG}${OSG_C_FLAGS_GV}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)

    SET(CMAKE_EXE_LINKER_FLAGS_DEBUGGV
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" 
        CACHE STRING "Flags used for linking binaries during maintainer builds."
        FORCE)

    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUGGV
        "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" 
        CACHE STRING "Flags used for linking binaries during maintainer builds."
        FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUGGV
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}${OSG_SHARED_LINKER_FLAGS_GV}" 
        CACHE STRING
        "Flags used by the shared libraries linker during maintainer builds."
        FORCE)

    ##########
    # Release
    ##########

    SET(CMAKE_CXX_FLAGS_RELEASEGV 
        "${CMAKE_CXX_FLAGS_RELEASE}${OSG_CXX_FLAGS_GV}" 
        CACHE STRING "Flags used by the C++ compiler during gv builds."
        FORCE)

    SET(CMAKE_C_FLAGS_RELEASEGV 
        "${CMAKE_C_FLAGS_RELEASE}${OSG_C_FLAGS_GV}"
        CACHE STRING "Flags used by the C compiler during gv builds."
        FORCE)

    SET(CMAKE_EXE_LINKER_FLAGS_RELEASEGV
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" 
        CACHE STRING "Flags used for linking binaries during gv builds."
        FORCE)

    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASEGV
         "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}" 
        CACHE STRING "Flags used for linking binaries during gv builds."
        FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASEGV
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}${OSG_SHARED_LINKER_FLAGS_GV}" 
        CACHE STRING
        "Flags used by the shared libraries linker during gv builds."
        FORCE)

ENDIF(CMAKE_COMPILER_IS_GNUCC)
