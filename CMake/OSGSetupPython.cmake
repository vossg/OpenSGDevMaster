OSG_SET_CACHE(OSG_PYTHON_MODULE_BASE_DIR "" PATH "")

MACRO(SETUP_PYTHON_BUILD)

# optional pass for test programs
  IF(OSGBUILD_PYTHON_BINDINGS)
    LIST(APPEND OSG_CMAKE_PASSES "OSGPYTHON")
    SET(OSG_PASSDIR_OSGPYTHON "Python")

    IF(EXISTS ${PYOSG_PYPLUSPLUS_DIR})
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_DIR "True")
    ELSE()
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_DIR "False")
    ENDIF()

    IF(EXISTS ${PYOSG_PYPLUSPLUS_GOODIES_DIR})
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_GOODIES_DIR "True")
    ELSE()
      SET(OSG_HAS_PYOSG_PYPLUSPLUS_GOODIES_DIR "False")
    ENDIF()

    SET(OSG_CAN_REGEN_PYTHON_BINDINGS FALSE)

    IF(GCCXML                       AND
       PYOSG_DIR                    AND
       PYOSG_PYPLUSPLUS_DIR         AND 
       PYOSG_PYPLUSPLUS_GOODIES_DIR)

     IF(EXISTS ${GCCXML}                       AND
        EXISTS ${PYOSG_DIR}                    AND
        EXISTS ${PYOSG_PYPLUSPLUS_DIR}         AND 
        EXISTS ${PYOSG_PYPLUSPLUS_GOODIES_DIR})

        SET(OSG_CAN_REGEN_PYTHON_BINDINGS TRUE)

      ENDIF()
    ENDIF()

    IF(${CMAKE_PROJECT_NAME} STREQUAL "OpenSG")
      SET(OSG_PYTHON_SUPPORT_DIR "${CMAKE_SOURCE_DIR}/Bindings/Python")
    ELSE()
      SET(OSG_PYTHON_SUPPORT_DIR "${OpenSG_DIR}/share/OpenSG/python")
    ENDIF()

    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "${OSG_PYTHON_SUPPORT_DIR}/genLibOrder.py"
                "${CMAKE_BINARY_DIR}/Python/Helper/genLibOrder.py")

    FILE(WRITE  "${CMAKE_BINARY_DIR}/Python/Helper/libOrder.py" "# Lib order information\n\n\nlibInfo = {}\n\n")
    FILE(APPEND "${CMAKE_BINARY_DIR}/Python/Helper/libOrder.py" "fullLibInfo = {}\n\n")

    IF(EXISTS ${PYOSG_DIR})

      MESSAGE(STATUS "")
      MESSAGE(STATUS "preparing python")
      MESSAGE(STATUS "")

      FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/Python/Helper")

      #########################
      # osggen.py
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osggen.py")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_BINARY_DIR}/Python/Helper/processed/osggen.py.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_BINARY_DIR}/Python/Helper/osggen.py")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/osggen.py.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Python/Helper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      #########################
      # splitGenHelper.py
      #########################

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${OSG_PYTHON_SUPPORT_DIR}/splitGenHelper.py"
                  "${CMAKE_BINARY_DIR}/Python/Helper/splitGenHelper.py")
     
      #########################
      # settings.py
      #########################

      SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/settings.py")
      SET(_OSG_FILE_OUT_PROC "${CMAKE_BINARY_DIR}/Python/Helper/processed/settings.py.proc")
      SET(_OSG_FILE_OUT      "${CMAKE_BINARY_DIR}/Python/Helper/settings.py")
      SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/settings.py.patch")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy
                  "${_OSG_FILE_IN}"
                  "${_OSG_FILE_OUT_PROC}")

      EXECUTE_PROCESS(COMMAND "patch" 
                      INPUT_FILE "${_OSG_PATCH_FILE}"
                      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Python/Helper/processed")

      EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${_OSG_FILE_OUT_PROC}"
                  "${_OSG_FILE_OUT}")


      IF(CMAKE_PROJECT_NAME STREQUAL "OpenSG")

        #########################
        # PreBoostPython.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/PreBoostPython.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed/PreBoostPython.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/PreBoostPython.h")

        FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

        STRING(REPLACE "<OpenSG/"
                       "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

        FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # OsgPtrHelpers.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/OsgPtrHelpers.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed/OsgPtrHelpers.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/OsgPtrHelpers.h")
 
        FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

        STRING(REPLACE "<OpenSG/"
                       "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

        FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # pypp_OSGBase_aliases.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/aliases.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed/pypp_aliases.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/pypp_aliases.h")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/pypp_aliases.h.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # ColorWrapper.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/ColorWrapper.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/ColorWrapper.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/ColorWrapper.h")

        FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

        STRING(REPLACE "<OpenSG/"
                       "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

        FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # VecStorageWrappers.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/VecStorageWrappers.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/VecStorageWrappers.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/VecStorageWrappers.h")

        FILE(READ ${_OSG_FILE_IN} _OSG_FILE_IN_DATA)

        STRING(REPLACE "<OpenSG/"
                       "<" _OSG_FILE_IN_DATA_P1 "${_OSG_FILE_IN_DATA}")

        FILE(WRITE ${_OSG_FILE_OUT_PROC} "${_OSG_FILE_IN_DATA_P1}")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # BaseWrappers.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/BaseWrappers.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/BaseWrappers.h")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Patches/wrappers.h.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # BaseWrappers.cpp
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.cpp")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed/BaseWrappers.cpp.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/BaseWrappers.cpp")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Patches/wrappers.cpp.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/Base/Bindings/Python/Wrapper/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")



        #########################
        # SystemWrappers.h
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.h")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed/SystemWrappers.h.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/SystemWrappers.h")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Patches/wrappers.h.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # SystemWrappers.cpp
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/Wrappers.cpp")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed/SystemWrappers.cpp.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/SystemWrappers.cpp")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Patches/wrappers.cpp.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/System/Bindings/Python/Wrapper/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # helpers.py
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/lib/helpers.py")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed/helpers.py.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/helpers.py.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")



        #########################
        # cored_node.py
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/lib/cored_node.py")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed/cored_node.py.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/cored_node.py.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")


        #########################
        # fcd_reflector.py
        #########################

        SET(_OSG_FILE_IN       "${PYOSG_DIR}/src/osg_module/lib/fcd_reflector.py")
        SET(_OSG_FILE_OUT_PROC "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed/fcd_reflector.py.proc")
        SET(_OSG_FILE_OUT      "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py")
        SET(_OSG_PATCH_FILE    "${CMAKE_SOURCE_DIR}/Bindings/Python/Patches/fcd_reflector.py.patch")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy
                    "${_OSG_FILE_IN}"
                    "${_OSG_FILE_OUT_PROC}")

        EXECUTE_PROCESS(COMMAND "patch" 
                        INPUT_FILE "${_OSG_PATCH_FILE}"
                        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/processed")

        EXECUTE_PROCESS(
          COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                    "${_OSG_FILE_OUT_PROC}"
                    "${_OSG_FILE_OUT}")

      ENDIF()

      MESSAGE(STATUS "")
      MESSAGE(STATUS "done python")
      MESSAGE(STATUS "")

    ENDIF(EXISTS ${PYOSG_DIR})

    SET(_OSG_SRC_PYPATH_HELPERS ${OSG_PYTHON_SUPPORT_DIR}/helpers)
    SET(_OSG_SRC_PYPATH_OSG     ${CMAKE_BINARY_DIR}/Python/lib/osg2/helpers)

    SET(_OSG_DST_PYPATH_HELPERS ${CMAKE_BINARY_DIR}/Python/lib/osg2/helpers)
    SET(_OSG_DST_PYPATH_OSG     ${CMAKE_BINARY_DIR}/Python/lib/osg2/osg)

    FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Python/lib/osg2)
    FILE(MAKE_DIRECTORY ${_OSG_DST_PYPATH_HELPERS})
    FILE(MAKE_DIRECTORY ${_OSG_DST_PYPATH_OSG})

    OSG_SYMLINK_CHECKED(${OSG_PYTHON_SUPPORT_DIR}/osg2/__init__.py
                        ${CMAKE_BINARY_DIR}/Python/lib/osg2/__init__.py)

    OSG_SYMLINK_CHECKED(${_OSG_SRC_PYPATH_HELPERS}/cored_node.py
                        ${_OSG_DST_PYPATH_HELPERS}/cored_node.py)
    OSG_SYMLINK_CHECKED(${_OSG_SRC_PYPATH_HELPERS}/fcd_reflector.py
                        ${_OSG_DST_PYPATH_HELPERS}/fcd_reflector.py)
    OSG_SYMLINK_CHECKED(${_OSG_SRC_PYPATH_HELPERS}/helpers.py
                        ${_OSG_DST_PYPATH_HELPERS}/helpers.py)
    OSG_SYMLINK_CHECKED(${_OSG_SRC_PYPATH_HELPERS}/__init__.py
                        ${_OSG_DST_PYPATH_HELPERS}/__init__.py)

    IF(${CMAKE_PROJECT_NAME} STREQUAL "OpenSG")
      SET(OSG_PYTHON_COMMON_INCDIR "${CMAKE_SOURCE_DIR}/Bindings/Python/Common" CACHE PATH "" FORCE)
    ELSE()
      SET(OSG_PYTHON_COMMON_INCDIR "${OpenSG_DIR}/include/OpenSG/Bindings/Python/Common" CACHE PATH "" FORCE)
    ENDIF()

    ADD_CUSTOM_TARGET(OSGPy)

    IF(OSG_CAN_REGEN_PYTHON_BINDINGS)
      ADD_CUSTOM_TARGET(OSGPyGen)
    ENDIF()
#    ADD_CUSTOM_TARGET(OSGPyBuild)

  ENDIF(OSGBUILD_PYTHON_BINDINGS)
ENDMACRO()


MACRO(INSTALL_PYTHON_ELEMENTS)

  # Neverthless install bindings common headers
  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/PreBoostPython.h"
                "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/OsgPtrHelpers.h"
                "${CMAKE_SOURCE_DIR}/Bindings/Python/Common/pypp_aliases.h"
          DESTINATION include/OpenSG/Bindings/Python/Common)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/CMake/OSGSetupPython.cmake"
          DESTINATION share/OpenSG/cmake)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/genLibOrder.py"
          DESTINATION share/OpenSG/python/)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/splitGenHelper.py"
          DESTINATION share/OpenSG/python/)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/osgGenBindings.py.in"
          DESTINATION share/OpenSG/python/)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/__init__.py.in"
          DESTINATION share/OpenSG/python/)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/osg2/__init__.py"
          DESTINATION share/OpenSG/python/osg2)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/cored_node.py"
          DESTINATION share/OpenSG/python/helpers)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/fcd_reflector.py"
          DESTINATION share/OpenSG/python/helpers)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/helpers.py"
          DESTINATION share/OpenSG/python/helpers)

  INSTALL(FILES "${CMAKE_SOURCE_DIR}/Bindings/Python/helpers/__init__.py"
          DESTINATION share/OpenSG/python/helpers)

ENDMACRO()