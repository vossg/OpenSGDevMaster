
    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetIlmImf} STATIC 
                ${OSG_OEXR_IMF_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetIlmImf})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetIlmImf} PROPERTIES
                          DEBUG_POSTFIX "D")

    INCLUDE_DIRECTORIES(${OSGOpenExrSrcDir}/IlmBase/Half 
                        ${OSGOpenExrSrcDir}/IlmBase/Iex 
                        ${OSGOpenExrSrcDir}/IlmBase/Imath 
                        ${OSGOpenExrSrcDir}/IlmBase/IlmThread 
                        ${OSGOpenExrSrcDir}/OpenExr/IlmImf 
                        ${OSG_ZLIB_INCLUDE_DIR})

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIlmImf}
                CONFIGURATIONS Release
                RUNTIME DESTINATION lib COMPONENT release_libraries
                LIBRARY DESTINATION lib COMPONENT release_libraries
                ARCHIVE DESTINATION lib COMPONENT release_libraries)

    INSTALL(TARGETS ${${PROJECT_NAME}StaticTargetIlmImf}
                CONFIGURATIONS Debug
                RUNTIME DESTINATION lib COMPONENT debug_libraries
                LIBRARY DESTINATION lib COMPONENT debug_libraries
                ARCHIVE DESTINATION lib COMPONENT debug_libraries)
