CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FUNCTION(PROCESS_FILES SUBDIR FILES)
  FOREACH(_DX_FILE ${${FILES}})
    EXECUTE_PROCESS(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OSGDoxygenSrcDir}/${SUBDIR}/${_DX_FILE}"
              "${CMAKE_BINARY_DIR}/External/doxygen/${SUBDIR}/")
  ENDFOREACH()
ENDFUNCTION()

IF(OSGDoxygenSrcDir)

  PROJECT(OSGDoxygen)

  SET(OSG_DOXYGEN_SRC_PATCH classdef.cpp
                            classdef.h
                            doxygen.cpp
                            entry.cpp
                            entry.h
                            marshal.cpp
                            memberlist.cpp
                            scanner.l
                            util.cpp)

  SET(OSG_DOXYGEN_CONFIGURE_FILES configure
                                  Makefile.in
                                  PLATFORMS)

  SET(OSG_DOXYGEN_QTOOLS_FILES Makefile.in
                               qtools.pro.in
                               qarray.h
                               qasciidict.h
                               qbuffer.cpp
                               qbuffer.h
                               qcache.h
                               qcollection.cpp
                               qcollection.h
                               qconfig.h
                               qcstring.cpp
                               qcstring.h
                               qdatastream.cpp
                               qdatastream.h
                               qdatetime.cpp
                               qdatetime.h
                               qdict.h
                               qdir.cpp
                               qdir.h
                               qdir_unix.cpp
                               qdir_win32.cpp
                               qfeatures.h
                               qfile.cpp
                               qfiledefs_p.h
                               qfile.h
                               qfileinfo.cpp
                               qfileinfo.h
                               qfileinfo_unix.cpp
                               qfileinfo_win32.cpp
                               qfile_unix.cpp
                               qfile_win32.cpp
                               qgarray.cpp
                               qgarray.h
                               qgcache.cpp
                               qgcache.h
                               qgdict.cpp
                               qgdict.h
                               qgeneric.h
                               qglist.cpp
                               qglist.h
                               qglobal.cpp
                               qglobal.h
                               qgstring.cpp
                               qgstring.h
                               qgvector.cpp
                               qgvector.h
                               qintdict.doc
                               qintdict.h
                               qiodevice.cpp
                               qiodevice.h
                               qlist.h
                               qmap.cpp
                               qmap.h
                               qmodules.h
                               qmutex.cpp
                               qmutex.h
                               qmutex_p.h
                               qmutex_unix.cpp
                               qmutex_win32.cpp
                               qptrdict.h
                               qqueue.h
                               qregexp.cpp
                               qregexp.h
                               qshared.h
                               qsortedlist.h
                               qstack.h
                               qstring.cpp
                               qstring.h
                               qstringlist.cpp
                               qstringlist.h
                               qstrlist.doc
                               qstrlist.h
                               qstrvec.h
                               qtextcodec.cpp
                               qtextcodec.h
                               qtextstream.cpp
                               qtextstream.h
                               qthread.cpp
                               qthread.h
                               qthread_p.h
                               qthread_unix.cpp
                               qthread_win32.cpp
                               qtl.h
                               qutfcodec.cpp
                               qutfcodec.h
                               qvaluelist.h
                               qvaluestack.h
                               qvector.h
                               qwaitcondition.h
                               qwaitcondition_unix.cpp
                               qwaitcondition_win32.cpp
                               qxml.cpp
                               qxml.h
                               scstring.cpp
                               scstring.h
                               )

  SET(OSG_DOXYGEN_SRC_FILES Makefile.in
                            libdoxygen.pro.in
                            libdoxycfg.pro.in
                            doxygen.pro.in
                            doxytag.pro.in
                            libdoxygen.t
                            libdoxycfg.t
                            doxytag.t
                            config.l
                            config.xml
                            configgen.py
                            constexp.l
                            constexp.y
                            increasebuffer.pl
                            code.l
                            commentcnv.l
                            commentscan.l
                            declinfo.l
                            defargs.l
                            doctokenizer.l
                            fortrancode.l
                            fortranscanner.l
                            doxygen.css
                            search.php
                            search.css
                            search.js
                            layout_default.xml
                            pre.l
                            pycode.l
                            pyscanner.l
                            vhdlcode.l
                            vhdlscanner.l
                            index.xsd
                            compound.xsd
                            doxytag.l
                            navtree.js
                            navtree.css
                            jquery.js
                            jquery_ui.js
                            resize.js
                            sizzle.js

                            bufstr.h
                            classlist.h
                            cmdmapper.h
                            code.h
                            commentcnv.h
                            commentscan.h
                            compound_xsd.h
                            config.h
                            configoptions.h
                            constexp.h
                            cppvalue.h
                            dbusxmlscanner.h
                            debug.h
                            declinfo.h
                            defargs.h
                            defgen.h
                            define.h
                            definition.h
                            diagram.h
                            dirdef.h
                            docparser.h
                            docsets.h
                            doctokenizer.h
                            docvisitor.h
                            dot.h
                            doxygen_css.h
                            doxygen.h
                            eclipsehelp.h
                            example.h
                            filedef.h
                            filename.h
                            formula.h
                            fortrancode.h
                            fortranscanner.h
                            ftextstream.h
                            ftvhelp.h
                            gifenc.h
                            groupdef.h
                            htags.h
                            htmlattrib.h
                            htmldocvisitor.h
                            htmlgen.h
                            htmlhelp.h
                            image.h
                            index.h
                            indexlog.h
                            index_xsd.h
                            instdox.h
                            jquery_js.h
                            jquery_ui_js.h
                            lang_cfg.h
                            language.h
                            latexdocvisitor.h
                            latexgen.h
                            layout_default.h
                            layout.h
                            lockingptr.h
                            lodepng.h
                            logos.h
                            mandocvisitor.h
                            mangen.h
                            marshal.h
                            memberdef.h
                            membergroup.h
                            memberlist.h
                            membername.h
                            message.h
                            msc.h
                            namespacedef.h      
                            navtree_js.h
                            navtree_css.h            
                            objcache.h
                            outputgen.h
                            outputlist.h
                            pagedef.h
                            parserintf.h
                            perlmodgen.h
                            portable.h
                            pre.h
                            printdocvisitor.h
                            pycode.h
                            pyscanner.h
                            qhp.h
                            qhpxmlwriter.h
                            qtbc.h
                            reflist.h
                            resize_js.h
                            rtfdocvisitor.h
                            rtfgen.h
                            rtfstyle.h
                            scanner.h
                            search_css.h
                            searchindex.h
                            search_js.h
                            search_php.h
                            section.h
                            sizzle_js.h
                            sortdict.h
                            store.h
                            tagreader.h
                            textdocvisitor.h
                            translator_adapter.h
                            translator_ar.h
                            translator_br.h
                            translator_ca.h
                            translator_cn.h
                            translator_cz.h
                            translatordecoder.h
                            translator_de.h
                            translator_dk.h
                            translator_en.h
                            translator_eo.h
                            translator_es.h
                            translator_fa.h
                            translator_fi.h
                            translator_fr.h
                            translator_gr.h
                            translator.h
                            translator_hr.h
                            translator_hu.h
                            translator_id.h
                            translator_it.h
                            translator_je.h
                            translator_jp.h
                            translator_ke.h
                            translator_kr.h
                            translator_lt.h
                            translator_mk.h
                            translator_nl.h
                            translator_no.h
                            translator_pl.h
                            translator_pt.h
                            translator_ro.h
                            translator_ru.h
                            translator_sc.h
                            translator_si.h
                            translator_sk.h
                            translator_sr.h
                            translator_sv.h
                            translator_tr.h
                            translator_tw.h
                            translator_ua.h
                            translator_vi.h
                            translator_za.h
                            util.h
                            version.h
                            vhdlcode.h
                            vhdldocgen.h
                            vhdlscanner.h
                            xmldocvisitor.h
                            xmlgen.h

                            portable_c.c

                            classlist.cpp
                            cmdmapper.cpp
                            configoptions.cpp
                            cppvalue.cpp
                            dbusxmlscanner.cpp
                            debug.cpp
                            defgen.cpp
                            define.cpp
                            definition.cpp
                            diagram.cpp
                            dirdef.cpp
                            docparser.cpp
                            docsets.cpp
                            dot.cpp
                            eclipsehelp.cpp
                            filedef.cpp
                            filename.cpp
                            formula.cpp
                            ftextstream.cpp
                            ftvhelp.cpp
                            gifenc.cpp
                            groupdef.cpp
                            htags.cpp
                            htmldocvisitor.cpp
                            htmlgen.cpp
                            htmlhelp.cpp
                            image.cpp
                            index.cpp
                            indexlog.cpp
                            instdox.cpp
                            language.cpp
                            latexdocvisitor.cpp
                            latexgen.cpp
                            layout.cpp
                            lodepng.cpp
                            logos.cpp
                            main.cpp
                            mandocvisitor.cpp
                            mangen.cpp
                            memberdef.cpp
                            membergroup.cpp
                            membername.cpp
                            message.cpp
                            msc.cpp
                            namespacedef.cpp
                            objcache.cpp
                            outputgen.cpp
                            outputlist.cpp
                            pagedef.cpp
                            perlmodgen.cpp
                            portable.cpp
                            qhp.cpp
                            qhpxmlwriter.cpp
                            reflist.cpp
                            rtfdocvisitor.cpp
                            rtfgen.cpp
                            rtfstyle.cpp
                            searchindex.cpp
                            store.cpp
                            tagreader.cpp
                            textdocvisitor.cpp
                            translator.cpp
                            vhdldocgen.cpp
                            xmldocvisitor.cpp
                            xmlgen.cpp
                            )

  SET(OSG_DOXYGEN_EXAMPLES_FILES Makefile.in)

  SET(OSG_DOXYGEN_DOC_FILES Makefile.in)

  SET(OSG_DOXYGEN_DWIZARD_FILES Makefile.in
                                doxywizard.pro.in)
  SET(OSG_DOXYGEN_DAPP_FILES Makefile.in
                             doxyapp.pro.in)

  SET(OSG_DOXYGEN_DPARSE_SRC_FILES Makefile.in
                                   doxmlparser.pro.in)
  SET(OSG_DOXYGEN_DPARSE_TST_FILES Makefile.in
                                   xmlparse.pro.in)
  SET(OSG_DOXYGEN_DPARSE_EX_FILES Makefile.in
                                  metrics.pro.in)

  SET(OSG_DOXYGEN_MD5_FILES Makefile.in
                            libmd5.pro.in
                            md5.c
                            md5.h
                            md5_loc.h)


  SET(OSG_DOXYGEN_DIRS "${OSGDoxygenSrcDir}/src/patched/"
                       "${CMAKE_BINARY_DIR}/External/doxygen"
                       "${CMAKE_BINARY_DIR}/External/doxygen/src"
                       "${CMAKE_BINARY_DIR}/External/doxygen/examples"
                       "${CMAKE_BINARY_DIR}/External/doxygen/doc"
                       "${CMAKE_BINARY_DIR}/External/doxygen/addon/doxywizard"
                       "${CMAKE_BINARY_DIR}/External/doxygen/addon/doxyapp"
                       "${CMAKE_BINARY_DIR}/External/doxygen/addon/doxmlparser/src"
                       "${CMAKE_BINARY_DIR}/External/doxygen/addon/doxmlparser/test"
                       "${CMAKE_BINARY_DIR}/External/doxygen/addon/doxmlparser/examples/metrics"
                       "${CMAKE_BINARY_DIR}/External/doxygen/libmd5"
                       "${CMAKE_BINARY_DIR}/External/doxygen/qtools")

  SET(OSG_DOXYGEN_PATCHES ${CMAKE_CURRENT_SOURCE_DIR}/01_custom_commands.patch
                          ${CMAKE_CURRENT_SOURCE_DIR}/02_infinite_recursion_fix.patch)

  FOREACH(_DX_DIR ${OSG_DOXYGEN_DIRS})
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${_DX_DIR}")
  ENDFOREACH()

 

  FOREACH(_DX_PATCHED_SRC ${OSG_DOXYGEN_SRC_PATCH})
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy "${OSGDoxygenSrcDir}/src/${_DX_PATCHED_SRC}" "${OSGDoxygenSrcDir}/src/patched/")
  ENDFOREACH()

  FOREACH(_DX_PATCH ${OSG_DOXYGEN_PATCHES})
    EXECUTE_PROCESS(COMMAND "patch" "-p2" 
                    INPUT_FILE "${_DX_PATCH}"
                    WORKING_DIRECTORY "${OSGDoxygenSrcDir}/src/patched")
  ENDFOREACH()


  PROCESS_FILES(. OSG_DOXYGEN_CONFIGURE_FILES)
  PROCESS_FILES(qtools OSG_DOXYGEN_QTOOLS_FILES)
  PROCESS_FILES(src OSG_DOXYGEN_SRC_FILES)
  PROCESS_FILES(examples OSG_DOXYGEN_EXAMPLES_FILES)
  PROCESS_FILES(doc OSG_DOXYGEN_DOC_FILES)
  PROCESS_FILES(addon/doxywizard OSG_DOXYGEN_DWIZARD_FILES)
  PROCESS_FILES(addon/doxyapp OSG_DOXYGEN_DAPP_FILES)

  PROCESS_FILES(addon/doxmlparser/src OSG_DOXYGEN_DPARSE_SRC_FILES)
  PROCESS_FILES(addon/doxmlparser/test OSG_DOXYGEN_DPARSE_TST_FILES)
  PROCESS_FILES(addon/doxmlparser/examples/metrics OSG_DOXYGEN_DPARSE_EX_FILES)

  PROCESS_FILES(libmd5 OSG_DOXYGEN_MD5_FILES)


  FOREACH(_DX_PATCHED_SRC ${OSG_DOXYGEN_SRC_PATCH})
    EXECUTE_PROCESS(
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${OSGDoxygenSrcDir}/src/patched/${_DX_PATCHED_SRC}"
                                   "${CMAKE_BINARY_DIR}/External/doxygen/src/")
  ENDFOREACH()

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${OSGDoxygenSrcDir}/packages"
            "${CMAKE_BINARY_DIR}/External/doxygen/packages")

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${OSGDoxygenSrcDir}/tmake"
            "${CMAKE_BINARY_DIR}/External/doxygen/tmake")


  EXECUTE_PROCESS(COMMAND "./configure"
                    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/External/doxygen")


  ADD_CUSTOM_TARGET(doxygen ALL
                    COMMAND "make"
                    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/External/doxygen")

  INSTALL(FILES "${CMAKE_BINARY_DIR}/External/doxygen/bin/doxygen"
          DESTINATION bin
          PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
                      GROUP_READ GROUP_EXECUTE
                      WORLD_READ WORLD_EXECUTE)


ELSE(OSGDoxygenSrcDir)

  SET(OSGDoxygenSrcDir "" CACHE PATH "")

ENDIF(OSGDoxygenSrcDir)
