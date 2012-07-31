
    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetIlmThread} STATIC 
                ${OSG_OEXR_ITR_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetIlmThread})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetIlmThread} PROPERTIES
                          DEBUG_POSTFIX "D")

    INCLUDE_DIRECTORIES(${OSGOpenExrSrcDir}/IlmBase/Iex)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIlmThread}
                CONFIGURATIONS Release 
                RUNTIME DESTINATION lib COMPONENT release_libraries
                LIBRARY DESTINATION lib COMPONENT release_libraries
                ARCHIVE DESTINATION lib COMPONENT release_libraries)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIlmThread}
                CONFIGURATIONS Debug
                RUNTIME DESTINATION lib COMPONENT debug_libraries
                LIBRARY DESTINATION lib COMPONENT debug_libraries
                ARCHIVE DESTINATION lib COMPONENT debug_libraries)
