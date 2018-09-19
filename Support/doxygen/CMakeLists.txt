CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FUNCTION(PROCESS_FILES SUBDIR FILES)
  FOREACH(_DX_FILE ${${FILES}})
    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OSGDoxygenSrcDir}/${SUBDIR}/${_DX_FILE}"
              "${CMAKE_BINARY_DIR}/External/doxygen/${SUBDIR}/")
  ENDFOREACH()
ENDFUNCTION()

IF(OSGDoxygenSrcDir)

  MESSAGE(STATUS "adding doxygen from : ${OSGDoxygenSrcDir}")

  PROJECT(OSGDoxygen)

  SET(OSG_DOXYGEN_DIRS "${CMAKE_BINARY_DIR}/External/doxygen"
                       "${CMAKE_BINARY_DIR}/External/doxygen/build"
                       "${CMAKE_BINARY_DIR}/External/doxygen/install")

  FOREACH(_DX_DIR ${OSG_DOXYGEN_DIRS})
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${_DX_DIR}")
  ENDFOREACH()

 
#  EXECUTE_PROCESS(
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${OSGDoxygenSrcDir}/packages"
#            "${CMAKE_BINARY_DIR}/External/doxygen/packages")

#  EXECUTE_PROCESS(
#    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${OSGDoxygenSrcDir}/tmake"
#            "${CMAKE_BINARY_DIR}/External/doxygen/tmake")


  MESSAGE(STATUS "configure doxygen : ${OSGDoxygenSrcDir} with ${CMAKE_COMMAND}")

  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/External/doxygen/install ${OSGDoxygenSrcDir}
                    OUTPUT_VARIABLE _CONFIGURE_DOXYGEN
                    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/External/doxygen/build")

  MESSAGE(STATUS "${_CONFIGURE_DOXYGEN} configure doxygen : done")

  ADD_CUSTOM_TARGET(doxygen ALL
                    COMMAND make install
                    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/External/doxygen/build")

  INSTALL(FILES "${CMAKE_BINARY_DIR}/External/doxygen/install/bin/doxygen"
          DESTINATION bin/${OSG_LIBDIR_BUILD_TYPE_SUFFIX} 
          COMPONENT development_tools
          PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
                      GROUP_READ GROUP_EXECUTE
                      WORLD_READ WORLD_EXECUTE)


ELSE(OSGDoxygenSrcDir)

  MESSAGE(STATUS "ignored doxygen")

  SET(OSGDoxygenSrcDir "" CACHE PATH "")

ENDIF(OSGDoxygenSrcDir)
