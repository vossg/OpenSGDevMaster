CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGLibXml2SrcDir AND OSGZLibSrcDir AND OSGLibIconvSrcDir)

  PROJECT(OSGLibXml2)

  SET(${PROJECT_NAME}SharedTarget osgxml2)
  SET(${PROJECT_NAME}StaticTarget libosgxml2)

  SET(OSG_LIBXML2_SRCS ${OSGLibXml2SrcDir}/c14n.c
                       ${OSGLibXml2SrcDir}/catalog.c
                       ${OSGLibXml2SrcDir}/chvalid.c
                       ${OSGLibXml2SrcDir}/debugXML.c
                       ${OSGLibXml2SrcDir}/dict.c
                       ${OSGLibXml2SrcDir}/DOCBparser.c
                       ${OSGLibXml2SrcDir}/encoding.c
                       ${OSGLibXml2SrcDir}/entities.c
                       ${OSGLibXml2SrcDir}/error.c
                       ${OSGLibXml2SrcDir}/globals.c
                       ${OSGLibXml2SrcDir}/hash.c
                       ${OSGLibXml2SrcDir}/HTMLparser.c
                       ${OSGLibXml2SrcDir}/HTMLtree.c
                       ${OSGLibXml2SrcDir}/legacy.c
                       ${OSGLibXml2SrcDir}/list.c
                       ${OSGLibXml2SrcDir}/nanoftp.c
                       ${OSGLibXml2SrcDir}/nanohttp.c
                       ${OSGLibXml2SrcDir}/parser.c
                       ${OSGLibXml2SrcDir}/parserInternals.c
                       ${OSGLibXml2SrcDir}/pattern.c
                       ${OSGLibXml2SrcDir}/relaxng.c
                       ${OSGLibXml2SrcDir}/SAX2.c
                       ${OSGLibXml2SrcDir}/SAX.c
                       ${OSGLibXml2SrcDir}/schematron.c
                       ${OSGLibXml2SrcDir}/threads.c
                       ${OSGLibXml2SrcDir}/tree.c
                       ${OSGLibXml2SrcDir}/uri.c
                       ${OSGLibXml2SrcDir}/valid.c
                       ${OSGLibXml2SrcDir}/xinclude.c
                       ${OSGLibXml2SrcDir}/xlink.c
                       ${OSGLibXml2SrcDir}/xmlIO.c
                       ${OSGLibXml2SrcDir}/xmlmemory.c
                       ${OSGLibXml2SrcDir}/xmlreader.c
                       ${OSGLibXml2SrcDir}/xmlregexp.c
                       ${OSGLibXml2SrcDir}/xmlmodule.c
                       ${OSGLibXml2SrcDir}/xmlsave.c
                       ${OSGLibXml2SrcDir}/xmlschemas.c
                       ${OSGLibXml2SrcDir}/xmlschemastypes.c
                       ${OSGLibXml2SrcDir}/xmlunicode.c
                       ${OSGLibXml2SrcDir}/xmlwriter.c
                       ${OSGLibXml2SrcDir}/xpath.c
                       ${OSGLibXml2SrcDir}/xpointer.c
                       ${OSGLibXml2SrcDir}/xmlstring.c)

  SET(OSG_LIBXML2_HDR ${OSGLibXml2SrcDir})

  SET(OSGLIBXML2_DEF HAVE_ZLIB_H)

  INCLUDE_DIRECTORIES(${OSGLibXml2SrcDir}/include)
  INCLUDE_DIRECTORIES(${OSGLibIconvSrcDir}/source/include)
  INCLUDE_DIRECTORIES(${OSGZLibSrcDir})

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_LIBXML2_SRCS})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET(OSGLIBXML2_DEF_SHARED ${OSGLIBXML2_DEF};ZLIB_DLL)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGLIBXML2_DEF_SHARED}")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} osgzlib)
    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} osgiconv)

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

  ENDIF(BUILD_SHARED_LIBS)

  IF(BUILD_STATIC_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}StaticTarget} STATIC ${OSG_LIBXML2_SRCS})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}StaticTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGLIBXML2_DEF};LIBXML_STATIC")


    INSTALL(TARGETS ${${PROJECT_NAME}StaticTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_STATIC_LIBS)

#  INSTALL(FILES ${OSG_TIFFLIB_HDR}
#          DESTINATION include
#          PERMISSIONS OWNER_WRITE OWNER_READ
#                      GROUP_READ
#                      WORLD_READ)

ELSE(OSGLibXml2SrcDir AND OSGZLibSrcDir AND OSGLibIconvSrcDir)
  SET(OSGLibXml2SrcDir "" CACHE PATH "")
ENDIF(OSGLibXml2SrcDir AND OSGZLibSrcDir AND OSGLibIconvSrcDir)
