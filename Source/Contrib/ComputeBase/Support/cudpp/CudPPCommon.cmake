  SET(OSG_CUDPP_SRC_INPUT          cudpp.cpp
                                   cudpp_plan.cpp
                                   cudpp_plan_manager.cpp
                                   cudpp_maximal_launch.cpp)

  SET(OSG_CUDPP_APP_SRC_INPUT      compact_app.cu
                                   radixsort_app.cu
                                   rand_app.cu
                                   scan_app.cu
                                   segmented_scan_app.cu
                                   spmvmult_app.cu)

  SET(OSG_CUDPP_KERNEL_SRC_INPUT   spmvmult_kernel.cu
                                   compact_kernel.cu
                                   radixsort_kernel.cu
                                   rand_kernel.cu
                                   scan_kernel.cu
                                   vector_kernel.cu
                                   segmented_scan_kernel.cu)

  SET(OSG_CUDPP_CTA_SRC_INPUT      rand_cta.cu
                                   radixsort_cta.cu
                                   scan_cta.cu
                                   segmented_scan_cta.cu)

  SET(OSG_CUDPP_HDR_INPUT          cudpp.h)

  SET(OSG_CUDPP_INTERNAL_HDR_INPUT cudpp_plan_manager.h
                                   cudpp_scan.h
                                   cudpp_segscan.h
                                   cudpp_compact.h
                                   cudpp_spmvmult.h
                                   cudpp_radixsort.h
                                   cudpp_rand.h
                                   cudpp_globals.h
                                   cudpp_plan.h
                                   cudpp_maximal_launch.h
                                   cudpp_util.h
                                   sharedmem.h)

  SetupFiles(OSG_CUDPP_SRC_INPUT 
             OSG_CUDPP_SRCS 
             "${OSGNVidiaCudPPSrcDir}/cudpp/src"
             "${OSG_SUPP_CC_BBASE}/cudpp/src")

  SetupFiles(OSG_CUDPP_APP_SRC_INPUT 
             OSG_CUDPP_SRCS 
             "${OSGNVidiaCudPPSrcDir}/cudpp/src/app"
             "${OSG_SUPP_CC_BBASE}/cudpp/src/app")

  SetupFiles(OSG_CUDPP_KERNEL_SRC_INPUT 
             OSG_CUDPP_KERNEL_SRCS 
             "${OSGNVidiaCudPPSrcDir}/cudpp/src/kernel"
             "${OSG_SUPP_CC_BBASE}/cudpp/src/kernel")

  SetupFiles(OSG_CUDPP_CTA_SRC_INPUT 
             OSG_CUDPP_KERNEL_SRCS 
             "${OSGNVidiaCudPPSrcDir}/cudpp/src/cta"
             "${OSG_SUPP_CC_BBASE}/cudpp/src/cta")

  SetupFiles(OSG_CUDPP_INTERNAL_HDR_INPUT 
             OSG_CUDPP_INTERNAL_HDR 
             "${OSGNVidiaCudPPSrcDir}/cudpp/src"
             "${OSG_SUPP_CC_BBASE}/cudpp/src")

  SetupFiles(OSG_CUDPP_HDR_INPUT 
             OSG_CUDPP_HDR 
             "${OSGNVidiaCudPPSrcDir}/cudpp/include"
             "${OSG_SUPP_CC_BBASE}/cudpp/src/cudpp")

  INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/cudpp/src")
  INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/${OSG_SUPP_CC_BBASE}/cudpp/src/cudpp")
  INCLUDE_DIRECTORIES("${CUDA_TOOLKIT_INCLUDE}")
  INCLUDE_DIRECTORIES(${OSG_CUDA_UTIL_INCLUDEDIR})

  IF(UNIX)
    SET(OSGCUDPPLIB_DEF GL_GLEXT_PROTOTYPES=1)
  ENDIF(UNIX)

  IF(NOT WIN32)
    SET(_OSG_INSTALL_CONFIGS ${CMAKE_BUILD_TYPE})
  ELSE()
    SET(_OSG_INSTALL_CONFIGS Debug;Release)
  ENDIF()

  IF(BUILD_SHARED_LIBS)
    CUDA_ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_CUDPP_SRCS})

    ADD_DEPENDENCIES(ALL_CUDA_BUILD ${${PROJECT_NAME}SharedTarget})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                            DEBUG_POSTFIX "D")
    ENDIF(WIN32)

    SET(OSGCUDPPLIB_DEF_SHARED ${OSGCUDPPLIB_DEF};BUILD_DLL;${${PROJECT_NAME}_EXTRA_DEF})
                          
    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGCUDPPLIB_DEF_SHARED}")

    IF(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  CONFIGURATIONS ${_OSG_INSTALL_CONFIGS}
                  RUNTIME DESTINATION bin
                  LIBRARY DESTINATION lib
                  ARCHIVE DESTINATION lib)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
    ENDIF(WIN32)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    CUDA_ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_CUDPP_SRCS})

    ADD_DEPENDENCIES(ALL_CUDA_BUILD ${${PROJECT_NAME}StaticTarget})

    IF(WIN32)
      SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                            DEBUG_POSTFIX "D")
    ENDIF(WIN32)

    SET(OSGCUDPPLIB_DEF_STATIC ${OSGCUDPPLIB_DEF};CUDPP_STATIC_LIB;${${PROJECT_NAME}_EXTRA_DEF})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGCUDPPLIB_DEF_STATIC}")

    IF(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                  CONFIGURATIONS ${_OSG_INSTALL_CONFIGS}
                  RUNTIME DESTINATION bin
                  LIBRARY DESTINATION lib
                  ARCHIVE DESTINATION lib)
    ELSE(WIN32)
      INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                  RUNTIME DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  LIBRARY DESTINATION lib${OSG_LIBDIR_SUFFIX}
                  ARCHIVE DESTINATION lib${OSG_LIBDIR_SUFFIX})
    ENDIF(WIN32)

  ENDIF(BUILD_STATIC_LIBS)

  INSTALL(FILES ${OSG_CUDPP_HDR}
          DESTINATION include/cuda/cudpp
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)
