
    ADD_LIBRARY(${${PROJECT_NAME}StaticTargetIlmImf} STATIC 
                ${OSG_OEXR_IMF_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}StaticTargetIlmImf})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTargetIlmImf} PROPERTIES
#                          COMPILE_DEFINITIONS "ZLIB_DLL"
                          DEBUG_POSTFIX "D")

    INCLUDE_DIRECTORIES(${OSGIlmBaseSrcDir}/Half 
                        ${OSGIlmBaseSrcDir}/Iex 
                        ${OSGIlmBaseSrcDir}/Imath 
                        ${OSGIlmBaseSrcDir}/IlmThread 
                        ${OSGOpenExrSrcDir}/IlmImf 
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
