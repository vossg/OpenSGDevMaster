
  INCLUDE_DIRECTORIES(${OSGColladaSrcDir}/dom/include/1.4)

  IF(NOT WIN32 AND NOT EXISTS ${OSGColladaSrcDir}/dom/include/1.4/dom/domAsset.h AND EXISTS ${OSGColladaSrcDir}/dom/include/1.4/dom/domasset.h)
    EXECUTE_PROCESS(
      COMMAND           "${CMAKE_COMMAND}" -E rename domasset.h domAsset.h
      WORKING_DIRECTORY "${OSGColladaSrcDir}/dom/include/1.4/dom")
  ENDIF()

  SET(OSGCOLLADA_DEF ${OSGCOLLADA_DEF};COLLADA_DOM_SUPPORT141)

  IF(BUILD_SHARED_LIBS)

    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget_14} SHARED 
                                                  ${OSG_COLLADA14_SRCS}
                                                  ${OSG_COLLADADAE_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget_14})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget_14} PROPERTIES
                            DEFINE_SYMBOL DOM_EXPORT
                            DEBUG_POSTFIX "D")
    ENDIF(WIN32)


    SET(OSGCOLLADA_DEF_SHARED ${OSGCOLLADA_DEF};DOM_DYNAMIC)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget_14} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGCOLLADA_DEF_SHARED};COLLADA14")

    IF(WIN32)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} osgxml2)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} osgpcrecpp)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} ${OSG_BOOST_LIBS})
    ELSEIF(UNIX AND APPLE)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} ${OSG_BOOST_LIBS})
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} ${LIBXML2_LIBRARIES})
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} pcrecpp)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} z)
    ELSE()
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} ${LIBXML2_LIBRARIES})
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} pcrecpp)
    ENDIF(WIN32)

    IF(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget_14}
                  CONFIGURATIONS Release
                  RUNTIME DESTINATION bin COMPONENT release_runtimes
                  LIBRARY DESTINATION lib COMPONENT release_libraries
                  ARCHIVE DESTINATION lib COMPONENT release_libraries)

      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget_14}
                  CONFIGURATIONS Debug
                  RUNTIME DESTINATION bin COMPONENT debug_runtimes
                  LIBRARY DESTINATION lib COMPONENT debug_libraries
                  ARCHIVE DESTINATION lib COMPONENT debug_libraries)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget_14}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT libraries)
    ENDIF(WIN32)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)

    ## 1.4 

    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget_14} STATIC ${OSG_COLLADA14_SRCS}
                                                         ${OSG_COLLADADAE_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTarget_14})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget_14} PROPERTIES
                            DEBUG_POSTFIX "D")

      SET(OSGCOLLADA_DEF_STATIC ${OSGCOLLADA_DEF};PCRE_STATIC)
    ENDIF(WIN32)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget_14} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGCOLLADA_DEF_STATIC};COLLADA14")

    IF(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget_14}
                  CONFIGURATIONS Release
                  RUNTIME DESTINATION lib COMPONENT debug_libraries
                  LIBRARY DESTINATION lib COMPONENT debug_libraries
                  ARCHIVE DESTINATION lib COMPONENT debug_libraries)

      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget_14}
                  CONFIGURATIONS Debug
                  RUNTIME DESTINATION lib COMPONENT debug_libraries
                  LIBRARY DESTINATION lib COMPONENT debug_libraries
                  ARCHIVE DESTINATION lib COMPONENT debug_libraries)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget_14}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT static_libraries
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT static_libraries
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX} COMPONENT static_libraries)
    ENDIF(WIN32)

  ENDIF(BUILD_STATIC_LIBS)
