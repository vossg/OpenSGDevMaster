
    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetIlmThread} STATIC 
                ${OSG_OEXR_ITR_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetIlmThread})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetIlmThread} PROPERTIES
                          DEBUG_POSTFIX "D")

    INCLUDE_DIRECTORIES(${OSGOpenExrSrcDir}/IlmBase/Iex)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIlmThread}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
