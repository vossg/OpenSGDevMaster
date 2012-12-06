
MACRO(SetupFiles fileList targetList sourceDir dstDir)

  SET(_OSGSUPP_DST_DIR ${CMAKE_BINARY_DIR}/${dstDir})

#MESSAGE(STATUS "
  FILE(MAKE_DIRECTORY ${_OSGSUPP_DST_DIR})
#")

  FOREACH(_src_file ${${fileList}})

    IF(NOT WIN32)
#MESSAGE(STATUS "
      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E create_symlink ${sourceDir}/${_src_file} ${_OSGSUPP_DST_DIR}/${_src_file} )
#")
    ELSE()
#MESSAGE(STATUS "
      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${sourceDir}/${_src_file}" "${_OSGSUPP_DST_DIR}/${_src_file}" )
#")
    ENDIF()

    LIST(APPEND ${targetList} ${_OSGSUPP_DST_DIR}/${_src_file})
    
  ENDFOREACH(_src_file ${fileList})

ENDMACRO(SetupFiles)

MACRO(ProcessFile fileList srcFile dstFile filter)

  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -DIN_FILE:FILE=${srcFile} 
                                   -DOUT_FILE:FILE=${dstFile}.proc
                                   -P ${filter})

  EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${dstFile}.proc" "${dstFile}")

  LIST(APPEND ${fileList} ${dstFile})

ENDMACRO(ProcessFile fileList srcFile dstFile filter)


MACRO(CopyOrLink srcFile dstFile)
  IF(NOT WIN32)
#MESSAGE(STATUS "
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E create_symlink "${srcFile}" "${dstFile}" )
#")
  ELSE()
#MESSAGE(STATUS "
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${srcFile}" "${dstFile}" )
#")
  ENDIF()
ENDMACRO(CopyOrLink srcFile dstFile)