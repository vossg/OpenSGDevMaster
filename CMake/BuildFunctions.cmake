

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

    SET_DIRECTORY_PROPERTIES(PROPERTIES CLEAN_NO_CUSTOM TRUE)

    SET(${PROJECT_NAME}_BUILD_FILE
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.cmake")
    SET(${PROJECT_NAME}_CONFIG_FILE
        "${CMAKE_BINARY_DIR}/bin/osg2-config.part2.tmp")

    # write header
    IF(${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        FILE(WRITE ${${PROJECT_NAME}_BUILD_FILE}
            "# ${PROJECT_NAME}.cmake -- auto generated\n\n")

        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_HDR)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_INL)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_INS)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_FCD)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_LL)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_YY)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "SET(${PROJECT_NAME}_MOC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_UNITTEST_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "SET(${PROJECT_NAME}_TEST_SRC)\n")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
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
    SET(${PROJECT_NAME}_DEP_CPP_DEF)
ENDMACRO(OSG_SELECT_PROJECT)

#############################################################################
# Extract separate libs and paths from a list of files.
#
# cmake stores libraries as full paths to the library file, this splits
# this form into a library (suitable for use on the linker command line) and
# the path where that library can be found.
FUNCTION(OSG_EXTRACT_LIB_AND_LIBDIR INLIBS OUTLIBS OUTLIBDIRS)

    FOREACH(INLIB ${INLIBS})
        GET_FILENAME_COMPONENT(INLIB_LIB    ${INLIB} NAME)
        GET_FILENAME_COMPONENT(INLIB_LIBDIR ${INLIB} PATH)

        STRING(REPLACE "${CMAKE_SHARED_LIBRARY_PREFIX}" "" INLIB_LIB ${INLIB_LIB})
        STRING(REPLACE "${CMAKE_SHARED_LIBRARY_SUFFIX}" "" INLIB_LIB ${INLIB_LIB})

        LIST(APPEND OLIBS ${INLIB_LIB})
        LIST(APPEND OLIBDIRS ${INLIB_LIBDIR})
    ENDFOREACH(INLIB)

    SET(${OUTLIBS} ${OLIBS} PARENT_SCOPE)
    SET(${OUTLIBDIRS} ${OLIBDIRS} PARENT_SCOPE)

ENDFUNCTION(OSG_EXTRACT_LIB_AND_LIBDIR)

FUNCTION(OSG_EXTRACT_LIBDIR INLIBDIRS OUTLIBDIRS)

    FOREACH(INLIBDIR ${INLIBDIRS})
        LIST(APPEND OLIBDIRS ${INLIBDIR})
    ENDFOREACH(INLIBDIR)

    SET(${OUTLIBDIRS} ${OLIBDIRS} PARENT_SCOPE)
ENDFUNCTION(OSG_EXTRACT_LIBDIR)

FUNCTION(OSG_EXTRACT_INCDIR ININCDIRS OUTINCDIRS)

    FOREACH(ININCDIR ${ININCDIRS})
        LIST(APPEND OINCDIRS ${ININCDIR})
    ENDFOREACH(ININCDIR)

    SET(${OUTINCDIRS} ${OINCDIRS} PARENT_SCOPE)
ENDFUNCTION(OSG_EXTRACT_INCDIR)

#############################################################################
# write the dependecy variables to the ${${PROJECT_NAME}_BUILD_FILE} file
# for use during the build and to
# ${${PROJECT_NAME}_CONFIG_FILE} for constructing osg2-config

FUNCTION(OSG_STORE_PROJECT_DEPENDENCIES)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    #########################################
    # store dependencies for the build

    # dependencies - OpenSG
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_OSG_LIB ${${PROJECT_NAME}_DEP_OSG_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_OSG_LIB ${${PROJECT_NAME}_DEP_TEST_OSG_LIB})\n\n")

    # dependencies - external
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_LIB ${${PROJECT_NAME}_DEP_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_LIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_INCDIR ${${PROJECT_NAME}_DEP_INCDIR})\n\n")

    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_LIB ${${PROJECT_NAME}_DEP_TEST_LIB})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_LIBDIR ${${PROJECT_NAME}_DEP_TEST_LIBDIR})\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_TEST_INCDIR ${${PROJECT_NAME}_DEP_TEST_INCDIR})\n\n")

    # dependencies - additional
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_ADD_INCDIR ${${PROJECT_NAME}_DEP_ADD_INCDIR})\n\n")
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
        "SET(${PROJECT_NAME}_DEP_CPP_DEF ${${PROJECT_NAME}_DEP_CPP_DEF})\n\n")

    #########################################################################
    # Store dependencies for osg2-config.
    # This is a bit lengthy as it writes a python dictionary

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "############################################################\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "## Dependecies for ${PROJECT_NAME}\n\n")

    # OpenSG libraries this lib depends on
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "\"${PROJECT_NAME}\" : {\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_osg_lib\"  :  [")

    FOREACH(DEPOSGLIB ${${PROJECT_NAME}_DEP_OSG_LIB})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${DEPOSGLIB}\", ")
    ENDFOREACH(DEPOSGLIB)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")

    # External libraries this lib depends on
    # we build lists of libs, libdirs and incdirs then write them
    FOREACH(DEPLIB ${${PROJECT_NAME}_DEP_LIB})
        OSG_EXTRACT_LIB_AND_LIBDIR("${${DEPLIB}}" LIBS LIBDIRS)

        LIST(APPEND DEPLIBS ${LIBS})
        LIST(APPEND DEPLIBDIRS ${LIBDIRS})
    ENDFOREACH(DEPLIB)

    FOREACH(DEPLIBDIR ${${PROJECT_NAME}_DEP_LIBDIR})
        OSG_EXTRACT_LIBDIR("${${DEPLIBDIR}}" LIBDIRS)

        LIST(APPEND DEPLIBDIRS ${LIBDIRS})
    ENDFOREACH(DEPLIBDIR)

    FOREACH(DEPINCDIR ${${PROJECT_NAME}_DEP_INCDIR})
        OSG_EXTRACT_INCDIR("${${DEPINCDIR}}" INCDIRS)

        LIST(APPEND DEPINCDIRS ${INCDIRS})
    ENDFOREACH(DEPINCDIR)

    IF(DEPLIBS)
        LIST(REMOVE_DUPLICATES DEPLIBS)
    ENDIF(DEPLIBS)

    IF(DEPLIBDIRS)
        LIST(REMOVE_DUPLICATES DEPLIBDIRS)
    ENDIF(DEPLIBDIRS)

    IF(DEPINCDIRS)
        LIST(REMOVE_DUPLICATES DEPINCDIRS)
    ENDIF(DEPINCDIRS)

    IF(DEPLIBS OR DEPLIBDIRS OR DEPINCDIRS)
        OSG_MSG("   DEPLIBS: ${DEPLIBS}")
        OSG_MSG("   DEPLIBDIRS: ${DEPLIBDIRS}")
        OSG_MSG("   DEPINCDIRS: ${DEPINCDIRS}")
    ENDIF(DEPLIBS OR DEPLIBDIRS OR DEPINCDIRS)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_lib\"  :  [")

    FOREACH(LIB ${DEPLIBS})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${LIB}\", ")
    ENDFOREACH(LIB)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")
    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_lib_dir\"  :  [")

    FOREACH(LIBDIR ${DEPLIBDIRS})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${LIBDIR}\", ")
    ENDFOREACH(LIBDIR)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "    \"dep_inc_dir\"  :  [")

    FOREACH(INCDIR ${DEPINCDIRS})
        FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
            " \"${INCDIR}\", ")
    ENDFOREACH(INCDIR)

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        " ],\n")

    FILE(APPEND ${${PROJECT_NAME}_CONFIG_FILE}
        "},\n")

ENDFUNCTION(OSG_STORE_PROJECT_DEPENDENCIES)

#############################################################################
# add directory DIRNAME to current project

FUNCTION(OSG_ADD_DIRECTORY DIRNAME)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGCOLLECT")

    OSG_MSG("Adding directory: ${DIRNAME}")

    IF(EXISTS "${CMAKE_SOURCE_DIR}/${DIRNAME}")
        FILE(GLOB LOCAL_SRC          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.cpp"
                                     "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.mm")
        FILE(GLOB LOCAL_HDR          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.h")
        FILE(GLOB LOCAL_INL          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.inl")
        FILE(GLOB LOCAL_INS          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.ins")
        FILE(GLOB LOCAL_FCD          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.fcd")
        FILE(GLOB LOCAL_LL           "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.ll")
        FILE(GLOB LOCAL_YY           "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*.yy")
        FILE(GLOB LOCAL_MOC          "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*_qt.h")
        FILE(GLOB LOCAL_UNITTEST_SRC "${CMAKE_SOURCE_DIR}/${DIRNAME}/OSG*Test.cpp")
        FILE(GLOB LOCAL_TEST_SRC     "${CMAKE_SOURCE_DIR}/${DIRNAME}/test*.cpp"
                                     "${CMAKE_SOURCE_DIR}/${DIRNAME}/test*.mm")
    ELSE()
        # Guess it's an absolute dir we got as the rel one is not there
        FILE(GLOB LOCAL_SRC          "${DIRNAME}/OSG*.cpp" "${DIRNAME}/OSG*.mm")
        FILE(GLOB LOCAL_HDR          "${DIRNAME}/OSG*.h")
        FILE(GLOB LOCAL_INL          "${DIRNAME}/OSG*.inl")
        FILE(GLOB LOCAL_INS          "${DIRNAME}/OSG*.ins")
        FILE(GLOB LOCAL_FCD          "${DIRNAME}/OSG*.fcd")
        FILE(GLOB LOCAL_LL           "${DIRNAME}/OSG*.ll")
        FILE(GLOB LOCAL_YY           "${DIRNAME}/OSG*.yy")
        FILE(GLOB LOCAL_MOC          "${DIRNAME}/OSG*_qt.h")
        FILE(GLOB LOCAL_UNITTEST_SRC "${DIRNAME}/OSG*Test.cpp")
        FILE(GLOB LOCAL_TEST_SRC     "${DIRNAME}/test*.cpp" "${DIRNAME}/test*.mm")
    ENDIF()

    # filter unittest sources out of library sources
    IF(LOCAL_UNITTEST_SRC)
        LIST(REMOVE_ITEM LOCAL_SRC ${LOCAL_UNITTEST_SRC})
    ENDIF(LOCAL_UNITTEST_SRC)

    # store file lists
    FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE} "# File lists for ${DIRNAME}\n\n")

    # library sources
    IF(LOCAL_SRC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_SRC \"${LOCAL_SRC}\")\n\n")
    ENDIF(LOCAL_SRC)

    IF(LOCAL_HDR)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_HDR \"${LOCAL_HDR}\")\n\n")
    ENDIF(LOCAL_HDR)

    IF(LOCAL_INL)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INL \"${LOCAL_INL}\")\n\n")
    ENDIF(LOCAL_INL)

    IF(LOCAL_INS)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INS \"${LOCAL_INS}\")\n\n")
    ENDIF(LOCAL_INS)

    IF(LOCAL_FCD)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_FCD \"${LOCAL_FCD}\")\n\n")
    ENDIF(LOCAL_FCD)

    IF(LOCAL_LL)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_LL \"${LOCAL_LL}\")\n\n")
    ENDIF(LOCAL_LL)

    IF(LOCAL_YY)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_YY \"${LOCAL_YY}\")\n\n")
    ENDIF(LOCAL_YY)

    IF(LOCAL_MOC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_MOC \"${LOCAL_MOC}\")\n\n")
    ENDIF(LOCAL_MOC)

    # unittests
    IF(LOCAL_UNITTEST_SRC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
            "LIST(APPEND ${PROJECT_NAME}_UNITTEST_SRC \"${LOCAL_UNITTEST_SRC}\")\n\n")
    ENDIF(LOCAL_UNITTEST_SRC)

    # tests
    IF(LOCAL_TEST_SRC)
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_TEST_SRC \"${LOCAL_TEST_SRC}\")\n\n")
    ENDIF(LOCAL_TEST_SRC)

    IF(EXISTS "${CMAKE_SOURCE_DIR}/${DIRNAME}")
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INC \"${CMAKE_SOURCE_DIR}/${DIRNAME}\")\n\n")
    ELSE()
        FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
             "LIST(APPEND ${PROJECT_NAME}_INC \"${DIRNAME}\")\n\n")
    ENDIF()
ENDFUNCTION(OSG_ADD_DIRECTORY)

#############################################################################
# perform default actions for pass OSGSETUP

FUNCTION(OSG_SETUP_LIBRARY_BUILD PROJ_DEFINE)

    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUP")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGSETUP")

    # read file lists
    INCLUDE(${${PROJECT_NAME}_BUILD_FILE})

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

            SET(FCDClassHdr "${FCDBase}.h")
            SET(FCDClassCpp "${FCDBase}.cpp")
            SET(FCDClassInl "${FCDBase}.inl")

            IF(NOT EXISTS ${FCDDir}/${FCDBaseCpp})
                SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${FCDDir}/${FCDBaseCpp})
                SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDBaseHdr})
                SET(${PROJECT_NAME}_INL ${${PROJECT_NAME}_INL} ${FCDDir}/${FCDBaseInl})
                SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDBaseFld})

                IF(NOT EXISTS ${FCDDir}/${FCDClassHdr})
                    SET(${PROJECT_NAME}_SRC ${${PROJECT_NAME}_SRC} ${FCDDir}/${FCDClassCpp})
                    SET(${PROJECT_NAME}_HDR ${${PROJECT_NAME}_HDR} ${FCDDir}/${FCDClassHdr})
                    SET(${PROJECT_NAME}_INL ${${PROJECT_NAME}_INL} ${FCDDir}/${FCDClassInl})

                    SET(FCD_TMP_OUT ${FCDDir}/${FCDClassCpp}
                                    ${FCDDir}/${FCDClassHdr}
                                    ${FCDDir}/${FCDClassInl})
                ENDIF(NOT EXISTS ${FCDDir}/${FCDClassHdr})
            ENDIF(NOT EXISTS ${FCDDir}/${FCDBaseCpp})

            SET(FCDCommand ${CMAKE_SOURCE_DIR}/Tools/fcd2code/fcd2code)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${FCDDir}/${FCDBaseHdr}
                       ${FCDDir}/${FCDBaseCpp}
                       ${FCDDir}/${FCDBaseInl}
                       ${FCDDir}/${FCDBaseFld}
                       ${FCD_TMP_OUT}
                COMMAND ${PYTHON_EXECUTABLE} ${FCDCommand} -c -b -d ${FCDFile} -p ${FCDDir} -r ${CMAKE_SOURCE_DIR}
                MAIN_DEPENDENCY ${FCDFile})

            SET(FCD_TMP_OUT )
        ENDFOREACH(FCDFile)

    ENDIF(OSG_ENABLE_FCD2CODE AND PYTHONINTERP_FOUND)

    ############
    # Qt4
    ############

    IF(${PROJECT_NAME} STREQUAL "OSGWindowQT4")
        # Here only the OSG_WITH_QT define is passes to qt moc.
        SET(moc_flags -DOSG_WITH_QT)

        SET(${PROJECT_NAME}_INC ${${PROJECT_NAME}_INC} ${CMAKE_CURRENT_BINARY_DIR})

        FOREACH(MOCFile ${${PROJECT_NAME}_MOC})
            GET_FILENAME_COMPONENT(MOCFile ${MOCFile} ABSOLUTE)
            QT4_MAKE_OUTPUT_FILE(${MOCFile} moc_ cpp MOCOutFile)

            ADD_CUSTOM_COMMAND(
                OUTPUT ${MOCOutFile}
                COMMAND ${QT_MOC_EXECUTABLE}
                ARGS ${moc_flags} ${moc_options} -o ${MOCOutFile} ${MOCFile}
                DEPENDS ${MOCFile})
            LIST(APPEND ${PROJECT_NAME}_SRC ${MOCOutFile})
        ENDFOREACH(MOCFile)
    ENDIF(${PROJECT_NAME} STREQUAL "OSGWindowQT4")
    
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

            LIST(APPEND ${PROJECT_NAME}_SRC ${YYSrc})
            LIST(APPEND ${PROJECT_NAME}_HDR ${YYHdr})

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

            FILE(APPEND ${${PROJECT_NAME}_BUILD_FILE}
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


    ADD_LIBRARY(${PROJECT_NAME} ${${PROJECT_NAME}_SRC}
                                ${${PROJECT_NAME}_HDR}
                                ${${PROJECT_NAME}_INL}
                                ${${PROJECT_NAME}_INS})

    INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INC})

    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
        DEFINE_SYMBOL ${PROJ_DEFINE}
        VERSION ${OSG_VERSION}
        SOVERSION ${OSG_VERSION}
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

    IF(${PROJECT_NAME}_DEP_CPP_DEF)
        OSG_MSG("  definitions = ${${PROJECT_NAME}_DEP_CPP_DEF}")
        SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
            COMPILE_DEFINITIONS "${${PROJECT_NAME}_DEP_CPP_DEF}")
    ENDIF(${PROJECT_NAME}_DEP_CPP_DEF)

    # install rules
    IF(WIN32)
        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS Release
                RUNTIME DESTINATION lib/opt
                LIBRARY DESTINATION lib/opt
                ARCHIVE DESTINATION lib/opt)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS Debug 
                RUNTIME DESTINATION lib/debug
                LIBRARY DESTINATION lib/debug
                ARCHIVE DESTINATION lib/debug)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS DebugRT
                RUNTIME DESTINATION lib/debugrt
                LIBRARY DESTINATION lib/debugrt
                ARCHIVE DESTINATION lib/debugrt)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS MinSizeRel
                RUNTIME DESTINATION lib/minsizerel
                LIBRARY DESTINATION lib/minsizerel
                ARCHIVE DESTINATION lib/minsizerel)

        INSTALL(TARGETS ${PROJECT_NAME}
                CONFIGURATIONS RelWithDebInfo
                RUNTIME DESTINATION lib/relwithdbg
                LIBRARY DESTINATION lib/relwithdbg
                ARCHIVE DESTINATION lib/relwithdbg)
    ELSE(WIN32)
        INSTALL(TARGETS ${PROJECT_NAME}
                RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
    ENDIF(WIN32)

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

    INCLUDE(${${PROJECT_NAME}_BUILD_FILE})
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

        FOREACH(LIB ${${PROJECT_NAME}_DEP_TEST_LIB})
            OSG_MSG("  library ${LIB} = ${${LIB}}")
            TARGET_LINK_LIBRARIES(${EXE} ${${LIB}})
        ENDFOREACH(LIB)

        TARGET_LINK_LIBRARIES(${EXE} ${PROJECT_NAME})
    ENDFOREACH(EXE_SRC)

ENDFUNCTION(OSG_SETUP_TEST_BUILD)

#############################################################################
# perform default actions for pass OSGDOXYDOC

FUNCTION(OSG_SETUP_DOXYDOC)
    IF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")
        RETURN()
    ENDIF(NOT ${OSG_CMAKE_PASS} STREQUAL "OSGDOXYDOC")

    INCLUDE(${${PROJECT_NAME}_BUILD_FILE})

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

##########################################################################
# write settings so different variants can be build with the same settings

MACRO(OSG_OPTION NAME DESC VALUE)
    LIST(APPEND OSG_OPTION_LIST ${NAME})
    OSG_MSG("adding option ${NAME} = ${VALUE}")

    OPTION(${NAME} "${DESC}" ${VALUE})
ENDMACRO(OSG_OPTION)

MACRO(OSG_SET_CACHE NAME VALUE TYPE DESC)
    LIST(APPEND OSG_OPTION_LIST ${NAME})

    SET(${NAME} ${VALUE} CACHE ${TYPE} "${DESC}")
ENDMACRO(OSG_SET_CACHE)

MACRO(OSG_SET NAME VALUE)
    LIST(APPEND OSG_OPTION_LIST ${NAME})

    SET(${NAME} ${VALUE})
ENDMACRO(OSG_SET)

MACRO(OSG_ADD_OPT NAME)
    LIST(APPEND OSG_OPTION_LIST ${NAME})
ENDMACRO(OSG_ADD_OPT)

MACRO(OSG_FIND_PACKAGE NAME)
    FIND_PACKAGE(${NAME})

    IF(${NAME}_FOUND)
        OSG_ADD_OPT(${NAME}_LIBRARIES)
        OSG_ADD_OPT(${NAME}_INCLUDE_DIR)        
    ENDIF(${NAME}_FOUND)

    OSG_ADD_OPT(${NAME}_FOUND)
ENDMACRO(OSG_FIND_PACKAGE)

MACRO(OSG_BOOST_DEP_SETUP)
    SET(Boost_USE_MULTITHREAD ON )
    SET(Boost_USE_STATIC_LIBS OFF)

    FIND_PACKAGE(Boost COMPONENTS filesystem)

    IF(Boost_FOUND)

        # Hide settings
        SET(Boost_FILESYSTEM_LIBRARY ${Boost_FILESYSTEM_LIBRARY} 
                                     CACHE INTERNAL "")
        SET(Boost_FILESYSTEM_LIBRARY_DEBUG ${Boost_FILESYSTEM_LIBRARY_DEBUG} 
                                           CACHE INTERNAL "")
        SET(Boost_FILESYSTEM_LIBRARY_RELEASE 
           ${Boost_FILESYSTEM_LIBRARY_RELEASE}  
           CACHE INTERNAL "")

        SET(Boost_INCLUDE_DIR ${Boost_INCLUDE_DIR}
                              CACHE INTERNAL "")

        SET(Boost_LIBRARY_DIRS ${Boost_LIBRARY_DIRS}
                               CACHE INTERNAL "")

        SET(Boost_USE_MULTITHREADED ${Boost_USE_MULTI_THREADED}
                                    CACHE INTERNAL "")


        INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR} )

        IF(UNIX)
            LINK_DIRECTORIES   (${Boost_LIBRARY_DIRS})
        ENDIF(UNIX)

        ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)

        IF(CMAKE_BUILD_TYPE STREQUAL "DebugRT")
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_DEBUG})
        ELSE()
            SET(OSG_BOOST_LIBS ${Boost_FILESYSTEM_LIBRARY_RELEASE})
        ENDIF()

        SET(OSG_BOOST_INCDIRS ${Boost_INCLUDE_DIR})



    ENDIF(Boost_FOUND)
ENDMACRO(OSG_BOOST_DEP_SETUP)

FUNCTION(OSG_WRITE_SETTINGS FILENAME)
    FILE(WRITE ${FILENAME}
            "# CMake.settings -- auto generated\n\n")

    FOREACH(OSG_OPT ${OSG_OPTION_LIST})
        FILE(APPEND ${FILENAME}
             "SET(${OSG_OPT} ${${OSG_OPT}} CACHE INTERNAL \"\")\n")
    ENDFOREACH(OSG_OPT ${OSG_OPTION_LIST})

ENDFUNCTION(OSG_WRITE_SETTINGS FILENAME)
