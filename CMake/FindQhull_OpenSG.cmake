# - Find Qhull
# Find the native Qhull includes and library
# This module defines
#  QHULL_INCLUDE_DIR, where to find libqhullcpp/Qhull.h.
#  QHULL_LIBRARIES, the libraries needed to use Qhull.
#  QHULL_FOUND, If false, do not try to use Qhull.
# also defined, but not for general use are

find_path(QHULL_INCLUDE_DIR libqhullcpp/Qhull.h)

set(QHULL_LIBRARIES "")
set(QHULL_LIBRARIES_FOUND FALSE)
set(QHULL_LIBRARY_NAMES "")
set(QHULL_LINK_DIRS "")

set(_qhull_configurations release debug releasenoopt debugopt)
set(_qhull_libs_to_process qhullcpp qhullstatic_r)
set(_qhull_libs_found TRUE)

foreach(_qhull_config ${_qhull_configurations})                         # release debug releasenoopt debugopt
    string(TOUPPER ${_qhull_config} _qhull_config_uc)                   # RELEASE, ..., DEBUGOPT

    if(${_qhull_config_uc} STREQUAL "RELEASE")
        set(_qhull_lib_suffix "")
    endif()
    if(${_qhull_config_uc} STREQUAL "DEBUG")
        set(_qhull_lib_suffix "D")
    endif()
    if(${_qhull_config_uc} STREQUAL "RELEASENOOPT")
        set(_qhull_lib_suffix "RN")
    endif()
    if(${_qhull_config_uc} STREQUAL "DEBUGOPT")
        set(_qhull_lib_suffix "DO")
    endif()

    foreach(_qhull_lib ${_qhull_libs_to_process})                       # qhullcpp qhullstatic_r
        string(TOUPPER ${_qhull_lib} _qhull_lib_uc)                     # QHULLCPP, QHULLSTATIC_R

        set(QHULL_${_qhull_lib_uc}_NAMES_${_qhull_config_uc} ${_qhull_lib}${_qhull_lib_suffix})                                    # set(QHULL_QHULLCPP_NAMES_DEBUGOPT qhullcppDO)
        find_library(QHULL_${_qhull_lib_uc}_LIBRARY_${_qhull_config_uc} NAMES ${QHULL_${_qhull_lib_uc}_NAMES_${_qhull_config_uc}}) # find_library(QHULL_QHULLCPP_LIBRARY_DEBUGOPT NAMES ${QHULL_QHULLCPP_NAMES_DEBUGOPT})

        set(_qhull_found_this_lib TRUE)
        if(NOT QHULL_${_qhull_lib_uc}_LIBRARY_${_qhull_config_uc})      # if(NOT QHULL_QHULLCPP_LIBRARY_DEBUGOPT)
            set(_qhull_found_this_lib FALSE)
        endif()

        if(_qhull_found_this_lib)
            list(APPEND QHULL_LIBRARY_NAMES ${_qhull_lib_uc})                                                         # list(APPEND QHULL_LIBRARY_NAMES QHULLCPP)
            list(APPEND _qhull_all_found_${_qhull_config}_libs ${QHULL_${_qhull_lib_uc}_LIBRARY_${_qhull_config_uc}}) # list(APPEND _qhull_all_found_debugopt_libs ${QHULL_QHULLCPP_LIBRARY_DEBUGOPT})
            mark_as_advanced(QHULL_${_qhull_lib_uc}_LIBRARY_${_qhull_config_uc})                                      # mark_as_advanced(QHULL_QHULLCPP_LIBRARY_DEBUGOPT)
            get_filename_component(_qhull_dir ${QHULL_${_qhull_lib_uc}_LIBRARY_${_qhull_config_uc}} PATH)             # get_filename_component(_qhull_dir ${QHULL_QHULLCPP_LIBRARY_DEBUGOPT} PATH)
            list(APPEND QHULL_LINK_DIRS ${_qhull_dir})
        endif()
    endforeach()
endforeach()

if(_qhull_libs_found)
    set(QHULL_FOUND TRUE)

    list(REMOVE_DUPLICATES QHULL_LIBRARY_NAMES)
    list(REMOVE_DUPLICATES QHULL_LINK_DIRS)

    foreach(_qhull_name ${QHULL_LIBRARY_NAMES})       # QHULLCPP QHULLSTATIC_R
        set(QHULL_${_qhull_name}_FOUND TRUE)                                    # set(QHULL_QHULLCPP_FOUND TRUE)
        set(QHULL_${_qhull_name}_LIBRARY QHULL_${_qhull_name}_LIBRARY_TARGET)   # set(QHULL_QHULLCPP_LIBRARY QHULL_QHULLCPP_LIBRARY_TARGET)
        mark_as_advanced(QHULL_${_qhull_name}_LIBRARY)                          # mark_as_advanced(QHULL_QHULLCPP_LIBRARY)

        set(_qhull_lib_name ${QHULL_${_qhull_name}_LIBRARY})                    # set(_qhull_lib_name ${QHULL_QHULLCPP_LIBRARY})
        set(_qhull_lib_name_uc ${_qhull_name})                                  # set(_qhull_lib_name_uc QHULLCPP)

        add_library(${_qhull_lib_name} UNKNOWN IMPORTED)                        # add_library(${QHULL_QHULLCPP_LIBRARY} UNKNOWN IMPORTED)

        if(QHULL_${_qhull_lib_name_uc}_LIBRARY_RELEASE)                         # if(QHULL_QHULLCPP_LIBRARY_RELEASE)
            set(_qhull_imp_release IMPORTED_LOCATION_RELEASE ${QHULL_${_qhull_lib_name_uc}_LIBRARY_RELEASE})                    # set(_qhull_imp_release IMPORTED_LOCATION_RELEASE ${QHULL_QHULLCPP_LIBRARY_RELEASE})
        endif()

        if(QHULL_${_qhull_lib_name_uc}_LIBRARY_RELEASENOOPT)                    # if(QHULL_QHULLCPP_LIBRARY_RELEASENOOPT)
            set(_qhull_imp_releasenoopt IMPORTED_LOCATION_RELEASENOOPT ${QHULL_${_qhull_lib_name_uc}_LIBRARY_RELEASENOOPT})     # set(_qhull_imp_releasenoopt IMPORTED_LOCATION_RELEASENOOPT ${QHULL_QHULLCPP_LIBRARY_RELEASENOOPT})
        endif()

        if(QHULL_${_qhull_lib_name_uc}_LIBRARY_DEBUG)                           # if(QHULL_QHULLCPP_LIBRARY_DEBUG)
            set(_qhull_imp_debug IMPORTED_LOCATION_DEBUG ${QHULL_${_qhull_lib_name_uc}_LIBRARY_DEBUG})                          # set(_qhull_imp_debug IMPORTED_LOCATION_DEBUG ${QHULL_QHULLCPP_LIBRARY_DEBUG})
        endif()

        if(QHULL_${_qhull_lib_name_uc}_LIBRARY_DEBUGOPT)                        # if(QHULL_QHULLCPP_LIBRARY_DEBUGOPT)
            set(_qhull_imp_debugopt IMPORTED_LOCATION_DEBUGOPT ${QHULL_${_qhull_lib_name_uc}_LIBRARY_DEBUGOPT})                 # set(_qhull_imp_debugopt IMPORTED_LOCATION_DEBUGOPT ${QHULL_QHULLCPP_LIBRARY_DEBUGOPT})
        endif()

        if(_qhull_imp_release OR _qhull_imp_releasenoopt OR _qhull_imp_debug OR _qhull_imp_debugopt)
            set_target_properties(
                ${_qhull_lib_name} PROPERTIES                                   # ${QHULL_QHULLCPP_LIBRARY} PROPERTIES
                    ${_qhull_imp_release}                                       # IMPORTED_LOCATION_RELEASE ${QHULL_QHULLCPP_LIBRARY_RELEASE}
                    ${_qhull_imp_releasenoopt}                                  # IMPORTED_LOCATION_RELEASENOOPT ${QHULL_QHULLCPP_LIBRARY_RELEASENOOPT}
                    ${_qhull_imp_debug}                                         # IMPORTED_LOCATION_DEBUG ${QHULL_QHULLCPP_LIBRARY_DEBUG}
                    ${_qhull_imp_debugopt}                                      # IMPORTED_LOCATION_DEBUGOPT ${QHULL_QHULLCPP_LIBRARY_DEBUGOPT}
            )

            list(APPEND QHULL_LIBRARIES ${QHULL_${_qhull_name}_LIBRARY})        # list(APPEND QHULL_LIBRARIES ${QHULL_QHULLCPP_LIBRARY})
        endif()
    endforeach()

    include(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(QHULL DEFAULT_MSG QHULL_LIBRARIES QHULL_INCLUDE_DIR)
    set(QHULL_LIBRARIES_FOUND TRUE)
    mark_as_advanced(QHULL_LIBRARIES_FOUND QHULL_INCLUDE_DIR)
endif()
