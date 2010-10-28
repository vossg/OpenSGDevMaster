
  INCLUDE_DIRECTORIES(${OSGColladaSrcDir}/dom/include/1.4)

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
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} libosgminizip)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} ${OSG_BOOST_LIBS})
    ELSE(WIN32)
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} ${LIBXML2_LIBRARIES})
      TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget_14} pcrecpp)
    ENDIF(WIN32)

    IF(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget_14}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION bin
                  LIBRARY DESTINATION lib
                  ARCHIVE DESTINATION lib)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget_14}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
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
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION bin
                  LIBRARY DESTINATION lib
                  ARCHIVE DESTINATION lib)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget_14}
                  CONFIGURATIONS Release Debug
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
    ENDIF(WIN32)

  ENDIF(BUILD_STATIC_LIBS)
