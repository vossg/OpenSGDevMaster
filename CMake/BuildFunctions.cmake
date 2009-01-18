

#############################################################################
#print message depending on the setting of OSG_VERBOSE_BUILD_MESSAGES

FUNCTION(OSG_MSG MSG)
    IF(OSG_VERBOSE_BUILD_MESSAGES)
        MESSAGE(STATUS "${MSG}")
    ENDIF(OSG_VERBOSE_BUILD_MESSAGES)
ENDFUNCTION(OSG_MSG)

#############################################################################
# register project with build

MACRO(OSG_ADD_PROJECT)
    IF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        OPTION(OSGBUILD_${PROJECT_NAME} "Build the ${PROJECT_NAME} library" ON)
    ENDIF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
ENDMACRO(OSG_ADD_PROJECT)

#############################################################################
# select the current project as the one settings are added to

MACRO(OSG_SELECT_PROJECT)

    IF(OSGBUILD_${PROJECT_NAME})
        MESSAGE(STATUS "Processing ${PROJECT_NAME}")
    ELSE(OSGBUILD_${PROJECT_NAME})
        RETURN()
    ENDIF(OSGBUILD_${PROJECT_NAME})

    SET(${PROJECT_NAME}_CONFIG_FILE
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.cmake")

    IF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        FILE(WRITE ${${PROJECT_NAME}_CONFIG_FILE}
            "# ${PROJECT_NAME}.cmake -- auto generated\n\n")

        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_HDR)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_INL)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_INS)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_FCD)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_LL)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_YY)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_UNITTEST_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_TEST_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "SET(${PROJECT_NAME}_INC)\n\n")
    ENDIF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    # clear dependency variables
    SET(${PROJECT_NAME}_DEP_OSG_LIB)
    SET(${PROJECT_NAME}_DEP_TEST_OSG_LIB)

    SET(${PROJECT_NAME}_DEP_LIB)
    SET(${PROJECT_NAME}_DEP_LIBDIR)
    SET(${PROJECT_NAME}_DEP_INCDIR)

    SET(${PROJECT_NAME}_DEP_TEST_LIB)
    SET(${PROJECT_NAME}_DEP_TEST_LIBDIR)
    SET(${PROJECT_NAME}_DEP_TEST_INCDIR)

    SET(${PROJECT_NAME}_DEP_ADD_INCDIR)
ENDMACRO(OSG_SELECT_PROJECT)

#############################################################################
# write the dependecy variables to the ${${PROJECT_NAME}_CONFIG_FILE file

FUNCTION(OSG_STORE_PROJECT_DEPENDENCIES)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    # dependencies - OpenSG
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_OSG_LIB ${${PROJECT_NAME}_DEP_OSG_LIB})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_OSG_LIB ${${PROJECT_NAME}_DEP_TEST_OSG_LIB})\n\n")

    # dependencies - external
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_DEP_LIB})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_INCDIR ${${PROJECT_NAME}_DEP_INCDIR})\n\n")

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_LIB ${${PROJECT_NAME}_DEP_TEST_LIB})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_LIBDIR ${${PROJECT_NAME}_DEP_TEST_LIBDIR})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR})\n\n")

    # dependencies - additional
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "SET(${PROJECT_NAME}_DEP_ADD_INCDIR ${${PROJECT_NAME}_DEP_ADD_INCDIR})\n\n")

ENDFUNCTION(OSG_STORE_PROJECT_DEPENDENCIES)

#############################################################################
# add directory DIRNAME to current project

FUNCTION(OSG_ADD_DIRECTORY DIRNAME)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    OSG_MSG("Adding directory: ${DIRNAME}")

    FILE(GLOB LOCAL_SRC          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.cpp")
    FILE(GLOB LOCAL_HDR          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.h")
    FILE(GLOB LOCAL_INL          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.inl")
    FILE(GLOB LOCAL_INS          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.ins")
    FILE(GLOB LOCAL_FCD          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.fcd")
    FILE(GLOB LOCAL_LL           "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.ll")
    FILE(GLOB LOCAL_YY           "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.yy")
    FILE(GLOB LOCAL_UNITTEST_SRC "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*Test.cpp")
    FILE(GLOB LOCAL_TEST_SRC     "${CMAKE_SOURCE_DIR}/${DIRNAME}/test*.cpp")

    # filter unittest sources
    IF(LOCAL_UNITTEST_SRC)
        LIST(REMOVE_ITEM LOCAL_SRC ${LOCAL_UNITTEST_SRC})
    ENDIF(LOCAL_UNITTEST_SRC)

    # store file lists

    # library sources
    IF(LOCAL_SRC)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_SRC \"${LOCAL_SRC}\")\n\n")
    ENDIF(LOCAL_SRC)

    IF(LOCAL_HDR)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_HDR \"${LOCAL_HDR}\")\n\n")
    ENDIF(LOCAL_HDR)

    IF(LOCAL_INL)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INL \"${LOCAL_INL}\")\n\n")
    ENDIF(LOCAL_INL)

    IF(LOCAL_INS)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INS \"${LOCAL_INS}\")\n\n")
    ENDIF(LOCAL_INS)

    IF(LOCAL_FCD)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_FCD \"${LOCAL_FCD}\")\n\n")
    ENDIF(LOCAL_FCD)

    IF(LOCAL_LL)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_LL \"${LOCAL_LL}\")\n\n")
    ENDIF(LOCAL_LL)

    IF(LOCAL_YY)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_YY \"${LOCAL_YY}\")\n\n")
    ENDIF(LOCAL_YY)

    # unittests
    IF(LOCAL_UNITTEST_SRC)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            "LIST(APPEND ${PROJECT_NAME}_UNITTEST_SRC \"${LOCAL_UNITTEST_SRC}\")\n\n")
    ENDIF(LOCAL_UNITTEST_SRC)

    # tests
    IF(LOCAL_TEST_SRC)
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
             "LIST(APPEND ${PROJECT_NAME}_TEST_SRC \"${LOCAL_TEST_SRC}\")\n\n")
    ENDIF(LOCAL_TEST_SRC)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
         "LIST(APPEND ${PROJECT_NAME}_INC \"${CMAKE_SOURCE_DIR}/${DIRNAME}\")\n\n")

ENDFUNCTION(OSG_ADD_DIRECTORY)

#############################################################################
# perform default actions for pass OSGSETUP

FUNCTION(OSG_SETUP_LIBRARY_BUILD PROJ_DEFINE)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUP")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUP")

    # read file lists
    INCLUDE(${${PROJECT_NAME}_CONFIG_FILE})

    #####
    # FCD
    #####

    IF(OSG_ENABLE_FCD2CODE AND PYTHONINTERP_FOUND)

        FOREACH(FCDFile ${${PROJECT_NAME}_FCD})
            GET_FILENAME_COMPONENT(FCDBase ${FCDFile} NAME_WE)
            GET_FILENAME_COMPONENT(FCDDir  ${FCDFile} PATH)

            SET(FCDBaseHdr "${FCDBase}Base.h")
            SET(FCDBaseCpp "${FCDBase}Base.cpp")
            SET(FCDBaseInl "${FCDBase}Base.inl")
            SET(FCDBaseFld "${FCDBase}Fields.h")

            IF(NOT EXISTS ${FCDDir}/${FCDBaseCpp})
                SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${FCDDir}/${FCDBaseCpp})
                SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDBaseHds})
                SET(${PROJECT_NAME}_INL ${${PROJECT_NAME}_INL} ${FCDDir}/${FCDBaseInl})
                SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDBaseFld})
            ENDIF(NOT EXISTS ${FCDDir}/${FCDBaseCpp})

            SET(FCDCommand ${CMAKE_SOURCE_DIR}/Tools/fcd2code/fcd2code)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${FCDDir}/${FCDBaseHdr}
                        ${FCDDir}/${FCDBaseCpp}
                        ${FCDDir}/${FCDBaseInl}
                        ${FCDDir}/${FCDBaseFld}
                COMMAND ${PYTHON_EXECUTABLE} ${FCDCommand} -c -b -d ${FCDFile} -p ${FCDDir} -r ${CMAKE_SOURCE_DIR}
                MAIN_DEPENDENCY ${FCDFile})
        ENDFOREACH(FCDFile)

    ENDIF(OSG_ENABLE_FCD2CODE AND PYTHONINTERP_FOUND)

    ############
    # Flex/Bison
    ############

    IF(OSG_ENABLE_SCANPARSE_REGEN AND FLEX_EXE AND BISON_EXE)

        FOREACH(YYFile ${${PROJECT_NAME}_YY})

            GET_FILENAME_COMPONENT(YYBase ${YYFile} NAME_WE)

            STRING(REPLACE "Parser" "_" YYOpt ${YYBase})

            SET(YYSrc ${CMAKE_CURRENT_BINARY_DIR}/${YYBase}.cpp)
            SET(YYHdr ${CMAKE_CURRENT_BINARY_DIR}/${YYBase}.hpp)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${YYSrc} ${YYHdr}
                COMMAND ${BISON_EXE} -d -v -p${YYOpt} -b${YYOpt} -o ${YYSrc} ${YYFile}
                MAIN_DEPENDENCY ${YYFile})

            SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${YYSrc})
            SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${YYHdr})

        ENDFOREACH()

        FOREACH(LLFile ${${PROJECT_NAME}_LL})

            GET_FILENAME_COMPONENT(LLBase ${LLFile} NAME_WE)

            STRING(REPLACE "Scanner" "_" LLOpt ${LLBase})

            SET(LLSrc ${CMAKE_CURRENT_BINARY_DIR}/${LLBase}.cpp)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${LLSrc}
                COMMAND ${FLEX_EXE} -+ -P${LLOpt} -t ${LLFile} >  ${LLSrc}
                MAIN_DEPENDENCY ${LLFile})

            SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${LLSrc})

        ENDFOREACH()

        IF(${PROJECT_NAME}_YY OR ${PROJECT_NAME}_LL)
            SET(${PROJECT_NAME}_INC ${${PROJECT_NAME}_INC} ${CMAKE_CURRENT_BINARY_DIR})

            FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
                "LIST(APPEND ${PROJECT_NAME}_INC \"${CMAKE_CURRENT_BINARY_DIR}\")\n\n")

        ENDIF(${PROJECT_NAME}_YY OR ${PROJECT_NAME}_LL)

    ENDIF(OSG_ENABLE_SCANPARSE_REGEN AND FLEX_EXE AND BISON_EXE)

    ###############
    # build the lib
    ###############

    ## LINK_DIRS have to go first, before the ADD_LIB statement

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})
        OSG_MSG("  library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)


    ADD_LIBRARY(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

    INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INC})

    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
        DEFINE_SYMBOL ${PROJ_DEFINE}
        VERSION 2.0.0
        SOVERSION 2.0.0
        DEBUGRT_POSTFIX "_d")

    # dependencies - OpenSG
    FOREACH(OSGDEP ${${PROJECT_NAME}_DEP_OSG_LIB})
        IF(NOT EXISTS "${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
            MESSAGE(FATAL_ERROR "Dependency (${OSGDEP}) not found, "
                                "can not build ${PROJECT_NAME}\n")
            RETURN()
        ENDIF(NOT EXISTS "${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")

        INCLUDE("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGDEP}_INC})

        ADD_DEPENDENCIES(${PROJECT_NAME} ${OSGDEP})

        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OSGDEP})
    ENDFOREACH(OSGDEP)

    # dependencies - External
    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_INCDIR})
        OSG_MSG("  include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIB ${${PROJECT_NAME}_DEP_LIB})
        OSG_MSG("  library ${LIB} = ${${LIB}}")
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${${LIB}})
    ENDFOREACH(LIB)

    # install rules
    INSTALL(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
            LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
            ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})

    INSTALL(FILES ${${PROJECT_NAME}_HDR}
            DESTINATION include/OpenSG
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ)

    INSTALL(FILES ${${PROJECT_NAME}_INL}
            DESTINATION include/OpenSG
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ)

    INSTALL(FILES ${${PROJECT_NAME}_INS}
            DESTINATION include/OpenSG
            PERMISSIONS OWNER_WRITE OWNER_READ
                        GROUP_READ
                        WORLD_READ)

ENDFUNCTION(OSG_SETUP_LIBRARY_BUILD)

#############################################################################
# perform default actions for pass OSGSETUPTEST

FUNCTION(OSG_SETUP_TEST_BUILD)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUPTEST")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUPTEST")

    INCLUDE(${${PROJECT_NAME}_CONFIG_FILE})
    INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INC})

    FOREACH(OSGDEP ${${PROJECT_NAME}_DEP_OSG_LIB})
        IF(NOT EXISTS "${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
            MESSAGE(FATAL_ERROR "Dependency (${OSGDEP}) not found, "
                                "can not build tests for ${PROJECT_NAME}\n")
            RETURN()
        ENDIF(NOT EXISTS "${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")

        INCLUDE("${CMAKE_BINARY_DIR}/${OSGDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGDEP}_INC})
    ENDFOREACH(OSGDEP)

    # dependencies - External
    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_INCDIR})
        OSG_MSG("  include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})
        OSG_MSG("  library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    FOREACH(OSGTESTDEP ${${PROJECT_NAME}_DEP_TEST_OSG_LIB})
        IF(NOT EXISTS "${CMAKE_BINARY_DIR}/${OSGTESTDEP}.cmake")
            MESSAGE(STATUS "Test dependency (${OSGTESTDEP}) not found, "
                           "ignoring tests for ${PROJECT_NAME}\n")

            RETURN()
        ENDIF(NOT EXISTS "${CMAKE_BINARY_DIR}/${OSGTESTDEP}.cmake")

        INCLUDE("${CMAKE_BINARY_DIR}/${OSGTESTDEP}.cmake")
        INCLUDE_DIRECTORIES(${${OSGTESTDEP}_INC})
    ENDFOREACH(OSGTESTDEP)

    FOREACH(INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR})
        OSG_MSG("  test include dir ${INCDIR} = ${${INCDIR}}")
        INCLUDE_DIRECTORIES(${${INCDIR}})
    ENDFOREACH(INCDIR)

    FOREACH(LIBDIR ${${PROJECT_NAME}_DEP_TEST_LIBDIR})
        OSG_MSG("  test library dir ${LIBDIR} = ${${LIBDIR}}")
        LINK_DIRECTORIES(${${LIBDIR}})
    ENDFOREACH(LIBDIR)

    FOREACH(EXE_SRC ${${PROJECT_NAME}_TEST_SRC})
        GET_FILENAME_COMPONENT(EXE ${EXE_SRC} NAME_WE)

        ADD_EXECUTABLE(${EXE} ${EXE_SRC})

        FOREACH(OSGTESTDEP ${${PROJECT_NAME}_DEP_TEST_OSG_LIB})
            ADD_DEPENDENCIES(${EXE} ${OSGTESTDEP})
            TARGET_LINK_LIBRARIES(${EXE} ${OSGTESTDEP})
        ENDFOREACH(OSGTESTDEP)

        TARGET_LINK_LIBRARIES(${EXE} ${PROJECT_NAME})
    ENDFOREACH(EXE_SRC)

ENDFUNCTION(OSG_SETUP_TEST_BUILD)

#############################################################################
# perform default actions for pass OSGDOXYDOC

FUNCTION(OSG_SETUP_DOXYDOC)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")

    INCLUDE(${${PROJECT_NAME}_CONFIG_FILE})

    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
        "#############################################################################\n"
        )
    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
        "# doc input files for ${PROJECT_NAME}\n\n"
        )

    FOREACH(INCDIR ${${PROJECT_NAME}_INC})
        FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE}
            "INPUT += ${INCDIR}\n")
    ENDFOREACH(INCDIR)

    FILE(APPEND ${OSG_DOXY_CONFIGURATION_FILE} "\n")

ENDFUNCTION(OSG_SETUP_DOXYDOC)

#############################################################################
# perform default actions for build passes

FUNCTION(OSG_SETUP_PROJECT PROJ_DEFINE)
    IF(OSG_CMAKE_PASS STREQUAL "OSGSETUP")
        OSG_SETUP_LIBRARY_BUILD(${PROJ_DEFINE})

    ELSEIF(OSG_CMAKE_PASS STREQUAL "OSGSETUPTEST")
        OSG_SETUP_TEST_BUILD()

    ELSEIF(OSG_CMAKE_PASS STREQUAL "OSGDOXYDOC")
        OSG_SETUP_DOXYDOC()

    ENDIF(OSG_CMAKE_PASS STREQUAL "OSGSETUP")

ENDFUNCTION(OSG_SETUP_PROJECT)

#############################################################################
# setup import targets so the debugrt build type works correctly

FUNCTION(OSG_SETUP_IMPORT_LIB TARGET_NAME NEW_LIB)

    GET_FILENAME_COMPONENT(OSG_TMP_LIB_DIR ${${NEW_LIB}_RELEASE}
                           PATH)

    SET_TARGET_PROPERTIES(OSG_${NEW_LIB}_TARGET PROPERTIES
                          IMPORTED_IMPLIB ${${NEW_LIB}_RELEASE}
                          IMPORTED_LOCATION ${OSG_TMP_LIB_DIR}
                          IMPORTED_IMPLIB_DEBUGRT ${${NEW_LIB}_DEBUG}
                          IMPORTED_LOCATION_DEBUGRT ${OSG_TMP_LIB_DIR})

ENDFUNCTION(OSG_SETUP_IMPORT_LIB)

MACRO(OSG_ADD_LIB_TARGET TARGET_LIST NEW_LIB)

    ADD_LIBRARY(OSG_${NEW_LIB}_TARGET SHARED IMPORTED)

    OSG_SETUP_IMPORT_LIB(${TARGET_LIST} ${NEW_LIB})

    SET(${TARGET_LIST} ${${TARGET_LIST}} OSG_${NEW_LIB}_TARGET)

ENDMACRO(OSG_ADD_LIB_TARGET)


