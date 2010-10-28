CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(OSGGdalSrcDir)

  PROJECT(OSGGdal)

  SET(${PROJECT_NAME}SharedTarget osggdal)

  SET(OSG_GDAL_PORT_SRCS ${OSGGdalSrcDir}/port/cpl_conv.cpp
                         ${OSGGdalSrcDir}/port/cpl_csv.cpp
                         ${OSGGdalSrcDir}/port/cpl_error.cpp
                         ${OSGGdalSrcDir}/port/cpl_findfile.cpp
                         ${OSGGdalSrcDir}/port/cpl_getexecpath.cpp
                         ${OSGGdalSrcDir}/port/cpl_http.cpp
                         ${OSGGdalSrcDir}/port/cpl_list.cpp
                         ${OSGGdalSrcDir}/port/cpl_minixml.cpp
                         ${OSGGdalSrcDir}/port/cpl_multiproc.cpp
                         ${OSGGdalSrcDir}/port/cpl_odbc.cpp
                         ${OSGGdalSrcDir}/port/cpl_path.cpp
                         ${OSGGdalSrcDir}/port/cpl_string.cpp
                         ${OSGGdalSrcDir}/port/cpl_strtod.cpp
                         ${OSGGdalSrcDir}/port/cpl_vsi_mem.cpp
                         ${OSGGdalSrcDir}/port/cpl_vsil.cpp
                         ${OSGGdalSrcDir}/port/cpl_vsil_win32.cpp
                         ${OSGGdalSrcDir}/port/cpl_vsisimple.cpp
                         ${OSGGdalSrcDir}/port/cplgetsymbol.cpp
                         ${OSGGdalSrcDir}/port/cplstring.cpp
                         ${OSGGdalSrcDir}/port/xmlreformat.cpp)

  SET(OSG_GDAL_PORT_HDR ${CMAKE_BINARY_DIR}/gdal/cpl_config.h
                        ${OSGGdalSrcDir}/port/cpl_conv.h
                        ${OSGGdalSrcDir}/port/cpl_csv.h
                        ${OSGGdalSrcDir}/port/cpl_error.h
                        ${OSGGdalSrcDir}/port/cpl_list.h
                        ${OSGGdalSrcDir}/port/cpl_minixml.h
                        ${OSGGdalSrcDir}/port/cpl_multiproc.h
                        ${OSGGdalSrcDir}/port/cpl_odbc.h
                        ${OSGGdalSrcDir}/port/cpl_port.h
                        ${OSGGdalSrcDir}/port/cpl_string.h
                        ${OSGGdalSrcDir}/port/cpl_vsi.h)

  EXECUTE_PROCESS(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                     "${OSGGdalSrcDir}/port/cpl_config.h.vc"
                     "${CMAKE_BINARY_DIR}/gdal/cpl_config.h")


  SET(OSG_GDAL_ALG_SRCS ${OSGGdalSrcDir}/alg/contour.cpp
                        ${OSGGdalSrcDir}/alg/gdal_crs.c
                        ${OSGGdalSrcDir}/alg/gdal_rpc.cpp
                        ${OSGGdalSrcDir}/alg/gdal_tps.cpp
                        ${OSGGdalSrcDir}/alg/gdalchecksum.cpp
                        ${OSGGdalSrcDir}/alg/gdaldither.cpp
                        ${OSGGdalSrcDir}/alg/gdalgeoloc.cpp
                        ${OSGGdalSrcDir}/alg/gdalmediancut.cpp
                        ${OSGGdalSrcDir}/alg/gdalrasterize.cpp
                        ${OSGGdalSrcDir}/alg/gdalsimplewarp.cpp
                        ${OSGGdalSrcDir}/alg/gdaltransformer.cpp
                        ${OSGGdalSrcDir}/alg/gdalwarper.cpp
                        ${OSGGdalSrcDir}/alg/gdalwarpkernel.cpp
                        ${OSGGdalSrcDir}/alg/gdalwarpoperation.cpp
                        ${OSGGdalSrcDir}/alg/llrasterize.cpp
                        ${OSGGdalSrcDir}/alg/thinplatespline.cpp)

  SET(OSG_GDAL_ALG_HDR ${OSGGdalSrcDir}/alg/gdal_alg.h
                       ${OSGGdalSrcDir}/alg/gdalwarper.h
                       ${OSGGdalSrcDir}/alg/gvgcpfit.h)


  SET(OSG_GDAL_OGR_SRCS ${OSGGdalSrcDir}/ogr/gml2ogrgeometry.cpp
                        ${OSGGdalSrcDir}/ogr/ogr2gmlgeometry.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_api.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_fromepsg.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_opt.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_dict.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_esri.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_pci.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_proj4.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_usgs.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_validate.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srs_xml.cpp
                        ${OSGGdalSrcDir}/ogr/ogr_srsnode.cpp
                        ${OSGGdalSrcDir}/ogr/ograssemblepolygon.cpp
                        ${OSGGdalSrcDir}/ogr/ogrct.cpp
                        ${OSGGdalSrcDir}/ogr/ogrcurve.cpp    
                        ${OSGGdalSrcDir}/ogr/ogrfeature.cpp
                        ${OSGGdalSrcDir}/ogr/ogrfeaturedefn.cpp
                        ${OSGGdalSrcDir}/ogr/ogrfeaturequery.cpp
                        ${OSGGdalSrcDir}/ogr/ogrfeaturestyle.cpp
                        ${OSGGdalSrcDir}/ogr/ogrfielddefn.cpp
                        ${OSGGdalSrcDir}/ogr/ogrgeometry.cpp
                        ${OSGGdalSrcDir}/ogr/ogrgeometrycollection.cpp
                        ${OSGGdalSrcDir}/ogr/ogrgeometryfactory.cpp
                        ${OSGGdalSrcDir}/ogr/ogrlinearring.cpp
                        ${OSGGdalSrcDir}/ogr/ogrlinestring.cpp
                        ${OSGGdalSrcDir}/ogr/ogrmultilinestring.cpp
                        ${OSGGdalSrcDir}/ogr/ogrmultipoint.cpp
                        ${OSGGdalSrcDir}/ogr/ogrmultipolygon.cpp
                        ${OSGGdalSrcDir}/ogr/ogrpoint.cpp
                        ${OSGGdalSrcDir}/ogr/ogrpolygon.cpp
                        ${OSGGdalSrcDir}/ogr/ogrspatialreference.cpp
                        ${OSGGdalSrcDir}/ogr/ogrutils.cpp
                        ${OSGGdalSrcDir}/ogr/swq.c)

  SET(OSG_GDAL_OGR_HDR ${OSGGdalSrcDir}/ogr/ogr_api.h
                       ${OSGGdalSrcDir}/ogr/ogr_core.h
                       ${OSGGdalSrcDir}/ogr/ogr_feature.h
                       ${OSGGdalSrcDir}/ogr/ogr_featurestyle.h
                       ${OSGGdalSrcDir}/ogr/ogr_geometry.h
                       ${OSGGdalSrcDir}/ogr/ogr_p.h
                       ${OSGGdalSrcDir}/ogr/ogr_spatialref.h
                       ${OSGGdalSrcDir}/ogr/ogr_srs_api.h
#                       ${OSGGdalSrcDir}/ogr/oledb_sup.h
#                       ${OSGGdalSrcDir}/ogr/oledbgis.h
                       ${OSGGdalSrcDir}/ogr/swq.h)

  SET(OSG_GDAL_GCORE_SRCS ${OSGGdalSrcDir}/gcore/gdal_misc.cpp
                          ${OSGGdalSrcDir}/gcore/gdal_rat.cpp
                          ${OSGGdalSrcDir}/gcore/gdalallvalidmaskband.cpp
                          ${OSGGdalSrcDir}/gcore/gdalcolortable.cpp
                          ${OSGGdalSrcDir}/gcore/gdaldataset.cpp
                          ${OSGGdalSrcDir}/gcore/gdaldefaultoverviews.cpp
                          ${OSGGdalSrcDir}/gcore/gdaldriver.cpp
                          ${OSGGdalSrcDir}/gcore/gdaldrivermanager.cpp
                          ${OSGGdalSrcDir}/gcore/gdalmajorobject.cpp
                          ${OSGGdalSrcDir}/gcore/gdalmultidomainmetadata.cpp
                          ${OSGGdalSrcDir}/gcore/gdalnodatamaskband.cpp
                          ${OSGGdalSrcDir}/gcore/gdalopeninfo.cpp
                          ${OSGGdalSrcDir}/gcore/gdalpamdataset.cpp
                          ${OSGGdalSrcDir}/gcore/gdalpamproxydb.cpp
                          ${OSGGdalSrcDir}/gcore/gdalpamrasterband.cpp
                          ${OSGGdalSrcDir}/gcore/gdalrasterband.cpp
                          ${OSGGdalSrcDir}/gcore/gdalrasterblock.cpp
                          ${OSGGdalSrcDir}/gcore/overview.cpp
                          ${OSGGdalSrcDir}/gcore/rasterio.cpp)

  SET(OSG_GDAL_GCORE_HDR ${OSGGdalSrcDir}/gcore/gdal.h
                         ${OSGGdalSrcDir}/gcore/gdal_frmts.h
                         ${OSGGdalSrcDir}/gcore/gdal_priv.h
                         ${OSGGdalSrcDir}/gcore/gdal_version.h
                         ${OSGGdalSrcDir}/gcore/gdal_rat.h)

  SET(OSG_GDAL_OGR_FRMTS_SRCS ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_bin.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_binwr.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_e00gen.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_e00parse.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_e00read.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_e00write.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_mbyte.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_misc.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_rawbin.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravcbindatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravcbindriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravcbinlayer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravcdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravce00datasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravce00layer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogravclayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/csv/ogrcsvdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/csv/ogrcsvdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/csv/ogrcsvlayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnfloat.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnhelp.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnopen.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnread.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnstroke.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnwrite.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/ogrdgndatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/ogrdgndriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/ogrdgnlayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogr_attrind.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogr_gensql.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogr_miattrind.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogrdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogrlayer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogrregisterall.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogrsfdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogrsfdriverregistrar.cpp

                              ## Check off
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlfeature.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlfeatureclass.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlhandler.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlpropertydefn.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlreader.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlreadstate.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/ogrgmldatasource.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/ogrgmldriver.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/ogrgmllayer.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/parsexsd.cpp
#                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/trstring.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mem/ogrmemdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mem/ogrmemdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mem/ogrmemlayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_bounds.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_coordsys.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_datfile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_feature.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_feature_mif.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_geometry.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_idfile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_imapinfofile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_indfile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_mapcoordblock.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_mapfile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_mapheaderblock.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_mapindexblock.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_mapobjectblock.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_maptoolblock.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_middatafile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_miffile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_ogr_datasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_ogr_driver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_rawbinblock.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_spatialref.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_tabfile.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_tabseamless.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_tabview.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_tooldef.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_utils.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntf_codelist.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntf_estlayers.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntf_generic.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntf_raster.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntffilereader.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntfrecord.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntfstroke.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ogrntfdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ogrntfdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ogrntffeatureclasslayer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ogrntflayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/rec/ll_recio.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/rec/ogrrecdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/rec/ogrrecdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/rec/ogrreclayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/ddfrecordindex.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/ogrs57datasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/ogrs57driver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/ogrs57layer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57classregistrar.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57featuredefns.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57filecollector.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57reader.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57writer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/sdts/ogrsdtsdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/sdts/ogrsdtsdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/sdts/ogrsdtslayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/dbfopen.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/ogrshapedatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/ogrshapedriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/ogrshapelayer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/shape2ogr.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/shp_vsi.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/shpopen.c
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/shptree.c

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/ogrtigerdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/ogrtigerdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/ogrtigerlayer.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigeraltname.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerarealandmarks.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigercompletechain.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerentitynames.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerfeatureids.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerfilebase.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigeridhistory.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerkeyfeatures.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerlandmarks.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigeroverunder.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerpip.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerpoint.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerpolychainlink.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerpolygon.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerpolygoncorrections.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerpolygoneconomic.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerspatialmetadata.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigertlidrange.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerzerocellid.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerzipcodes.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/tigerzipplus4.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/vrt/ogrvrtdatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/vrt/ogrvrtdriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/vrt/ogrvrtlayer.cpp

                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/kml.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/kmlnode.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/kmlvector.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/ogr2kmlgeometry.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/ogrkmldatasource.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/ogrkmldriver.cpp
                              ${OSGGdalSrcDir}/ogr/ogrsf_frmts/kml/ogrkmllayer.cpp)


  SET(OSG_GDAL_OGR_FRMTS_HDR ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/avc_mbyte.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/dbfopen.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc/ogr_avc.h

#                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgn_pge.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnlib.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/dgnlibp.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/dgn/ogr_dgn.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/generic/ogr_gensql.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlreader.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/gmlreaderp.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/gml/ogr_gml.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mem/ogr_mem.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/ogrshape.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/shape/shapefil.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_geometry.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_ogr_driver.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_priv.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/mitab/mitab_utils.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/rec/ogr_rec.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/vrt/ogr_vrt.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/ogr_s57.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57.h
                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/s57/s57tables.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/tiger/ogr_tiger.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/sdts/ogr_sdts.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/ntf/ntf.h

                             ${OSGGdalSrcDir}/ogr/ogrsf_frmts/csv/ogr_csv.h)


  SET(OSG_GDAL_FRMTS_SRCS ${OSGGdalSrcDir}/frmts/gdalallregister.cpp

                          ${OSGGdalSrcDir}/frmts/aaigrid/aaigriddataset.cpp
                          ${OSGGdalSrcDir}/frmts/aigrid/aigccitt.c
                          ${OSGGdalSrcDir}/frmts/aigrid/aigdataset.cpp
                          ${OSGGdalSrcDir}/frmts/aigrid/aigopen.c
                          ${OSGGdalSrcDir}/frmts/aigrid/gridlib.c

                          ${OSGGdalSrcDir}/frmts/bmp/bmpdataset.cpp

                          ${OSGGdalSrcDir}/frmts/ceos/ceosdataset.cpp
                          ${OSGGdalSrcDir}/frmts/ceos/ceosopen.c

                          ${OSGGdalSrcDir}/frmts/ceos2/ceos.c
                          ${OSGGdalSrcDir}/frmts/ceos2/ceosrecipe.c
                          ${OSGGdalSrcDir}/frmts/ceos2/ceossar.c
                          ${OSGGdalSrcDir}/frmts/ceos2/link.c
                          ${OSGGdalSrcDir}/frmts/ceos2/sar_ceosdataset.cpp

                          ${OSGGdalSrcDir}/frmts/dted/dted_api.c
                          ${OSGGdalSrcDir}/frmts/dted/dted_create.c
                          ${OSGGdalSrcDir}/frmts/dted/dted_ptstream.c
                          ${OSGGdalSrcDir}/frmts/dted/dteddataset.cpp

                          ${OSGGdalSrcDir}/frmts/elas/elasdataset.cpp

                          ${OSGGdalSrcDir}/frmts/envisat/envisatdataset.cpp
                          ${OSGGdalSrcDir}/frmts/envisat/EnvisatFile.c

                          ${OSGGdalSrcDir}/frmts/fit/fit.cpp
                          ${OSGGdalSrcDir}/frmts/fit/fitdataset.cpp

                          ${OSGGdalSrcDir}/frmts/gif/gifdataset.cpp
                          ${OSGGdalSrcDir}/frmts/gif/libungif/dgif_lib.c
                          ${OSGGdalSrcDir}/frmts/gif/libungif/egif_lib.c
                          ${OSGGdalSrcDir}/frmts/gif/libungif/gif_err.c
                          ${OSGGdalSrcDir}/frmts/gif/libungif/gifalloc.c

                          ${OSGGdalSrcDir}/frmts/gtiff/geotiff.cpp
                          ${OSGGdalSrcDir}/frmts/gtiff/gt_overview.cpp
                          ${OSGGdalSrcDir}/frmts/gtiff/gt_wkt_srs.cpp
                          ${OSGGdalSrcDir}/frmts/gtiff/tif_float.c
                          ${OSGGdalSrcDir}/frmts/gtiff/tif_memio.c
                          ${OSGGdalSrcDir}/frmts/gtiff/tif_overview.c
                          ${OSGGdalSrcDir}/frmts/gtiff/tif_ovrcache.c
                          ${OSGGdalSrcDir}/frmts/gtiff/tifvsi.cpp
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_extra.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_free.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_get.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_names.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_new.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_normalize.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_print.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_set.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_tiffp.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_write.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geotiff_proj4.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/xtiff.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_aux.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_close.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_codec.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_color.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_compress.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_dir.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_dirinfo.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_dirread.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_dirwrite.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_dumpmode.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_error.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_extension.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_fax3.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_fax3sm.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_flush.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_getimage.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_jpeg.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_luv.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_lzw.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_next.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_open.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_packbits.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_pixarlog.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_predict.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_print.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_read.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_strip.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_swab.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_thunder.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_tile.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_version.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_vsi.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_warning.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_write.c
                          ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_zip.c

                          ${OSGGdalSrcDir}/frmts/gxf/gxf_ogcwkt.c
                          ${OSGGdalSrcDir}/frmts/gxf/gxfdataset.cpp
                          ${OSGGdalSrcDir}/frmts/gxf/gxfopen.c

                          ${OSGGdalSrcDir}/frmts/hfa/hfa_overviews.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfaband.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfacompress.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfadataset.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfadictionary.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfaentry.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfafield.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfaopen.cpp
                          ${OSGGdalSrcDir}/frmts/hfa/hfatype.cpp

                          ${OSGGdalSrcDir}/frmts/iso8211/ddffield.cpp
                          ${OSGGdalSrcDir}/frmts/iso8211/ddffielddefn.cpp
                          ${OSGGdalSrcDir}/frmts/iso8211/ddfmodule.cpp
                          ${OSGGdalSrcDir}/frmts/iso8211/ddfrecord.cpp
                          ${OSGGdalSrcDir}/frmts/iso8211/ddfsubfielddefn.cpp
                          ${OSGGdalSrcDir}/frmts/iso8211/ddfutils.cpp

                          ${OSGGdalSrcDir}/frmts/jdem/jdemdataset.cpp

                          ${OSGGdalSrcDir}/frmts/jpeg/jpgdataset.cpp
                          ${OSGGdalSrcDir}/frmts/jpeg/vsidataio.cpp

                          ${OSGGdalSrcDir}/frmts/l1b/l1bdataset.cpp

                          ${OSGGdalSrcDir}/frmts/mem/memdataset.cpp

                          ${OSGGdalSrcDir}/frmts/nitf/mgrs.c
                          ${OSGGdalSrcDir}/frmts/nitf/nitfaridpcm.cpp
                          ${OSGGdalSrcDir}/frmts/nitf/nitfbilevel.cpp
                          ${OSGGdalSrcDir}/frmts/nitf/nitfdataset.cpp
                          ${OSGGdalSrcDir}/frmts/nitf/nitffile.c
                          ${OSGGdalSrcDir}/frmts/nitf/nitfimage.c
                          ${OSGGdalSrcDir}/frmts/nitf/rpftocdataset.cpp
                          ${OSGGdalSrcDir}/frmts/nitf/rpftocfile.cpp

                          ${OSGGdalSrcDir}/frmts/pcidsk/pcidskdataset.cpp
                          ${OSGGdalSrcDir}/frmts/pcidsk/pcidsktiledrasterband.cpp

                          ${OSGGdalSrcDir}/frmts/png/pngdataset.cpp

                          ${OSGGdalSrcDir}/frmts/raw/atlsci_spheroid.cpp
                          ${OSGGdalSrcDir}/frmts/raw/btdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/cpgdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/dipxdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/doq1dataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/doq2dataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/ehdrdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/envidataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/fastdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/fujibasdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/genbindataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/gscdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/hkvdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/idadataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/landataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/mffdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/ndfdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/pauxdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/pnmdataset.cpp
                          ${OSGGdalSrcDir}/frmts/raw/rawdataset.cpp

                          ${OSGGdalSrcDir}/frmts/sdts/sdtsattrreader.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtscatd.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtsdataset.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtsindexedreader.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtsiref.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtslib.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtslinereader.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtspointreader.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtspolygonreader.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtsrasterreader.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtstransfer.cpp
                          ${OSGGdalSrcDir}/frmts/sdts/sdtsxref.cpp

                          ${OSGGdalSrcDir}/frmts/usgsdem/usgsdem_create.cpp
                          ${OSGGdalSrcDir}/frmts/usgsdem/usgsdemdataset.cpp

                          ${OSGGdalSrcDir}/frmts/vrt/vrtdataset.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtderivedrasterband.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtdriver.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtfilters.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtrasterband.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtrawrasterband.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtsourcedrasterband.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtsources.cpp
                          ${OSGGdalSrcDir}/frmts/vrt/vrtwarped.cpp

                          ${OSGGdalSrcDir}/frmts/xpm/xpmdataset.cpp

#                          ${OSGGdalSrcDir}/frmts/zlib/adler32.c
#                          ${OSGGdalSrcDir}/frmts/zlib/compress.c
#                          ${OSGGdalSrcDir}/frmts/zlib/crc32.c
#                          ${OSGGdalSrcDir}/frmts/zlib/deflate.c
#                          ${OSGGdalSrcDir}/frmts/zlib/gzio.c
#                          ${OSGGdalSrcDir}/frmts/zlib/infblock.c
#                          ${OSGGdalSrcDir}/frmts/zlib/infcodes.c
#                          ${OSGGdalSrcDir}/frmts/zlib/inffast.c
#                          ${OSGGdalSrcDir}/frmts/zlib/inflate.c
#                          ${OSGGdalSrcDir}/frmts/zlib/inftrees.c
#                          ${OSGGdalSrcDir}/frmts/zlib/infutil.c
#                          ${OSGGdalSrcDir}/frmts/zlib/trees.c
#                          ${OSGGdalSrcDir}/frmts/zlib/uncompr.c
#                          ${OSGGdalSrcDir}/frmts/zlib/zutil.c
                          )

  SET(OSG_GDAL_FRMTS_HDR ${OSGGdalSrcDir}/frmts/iso8211/iso8211.h
                         ${OSGGdalSrcDir}/frmts/sdts/sdts_al.h
                         ${OSGGdalSrcDir}/frmts/gtiff/tif_memio.h
                         ${OSGGdalSrcDir}/frmts/gtiff/tif_ovrcache.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/cpl_serv.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_datum.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_ellipse.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_gcs.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_pcs.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_pm.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_proj.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_units.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/epsg_vertcs.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_config.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_ctrans.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_keyp.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_normalize.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geo_tiffp.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geokeys.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geokeys.inc
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geonames.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geotiff.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geotiffio.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/geovalues.h
                         ${OSGGdalSrcDir}/frmts/gtiff/libgeotiff/xtiffio.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/port.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/t4.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_dir.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_fax3.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tif_predict.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tiff.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tiffcomp.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tiffconf.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tiffio.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tiffiop.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/tiffvers.h
#                         ${OSGGdalSrcDir}/frmts/gtiff/libtiff/uvcode.h

                         ${OSGGdalSrcDir}/frmts/ceos/ceosopen.h

                         ${OSGGdalSrcDir}/frmts/aigrid/aigrid.h

                         ${OSGGdalSrcDir}/frmts/dted/dted_api.h

                         ${OSGGdalSrcDir}/frmts/hfa/hfa.h
                         ${OSGGdalSrcDir}/frmts/hfa/hfa_p.h

                         ${OSGGdalSrcDir}/frmts/raw/atlsci_spheroid.h
                         ${OSGGdalSrcDir}/frmts/raw/rawdataset.h

                         ${OSGGdalSrcDir}/frmts/gxf/gxfopen.h

                         ${OSGGdalSrcDir}/frmts/ceos2/ceos.h

#                         ${OSGGdalSrcDir}/frmts/png/libpng/png.h
#                         ${OSGGdalSrcDir}/frmts/png/libpng/pngconf.h

#                         ${OSGGdalSrcDir}/frmts/zlib/deflate.h
#                         ${OSGGdalSrcDir}/frmts/zlib/infblock.h
#                         ${OSGGdalSrcDir}/frmts/zlib/infcodes.h
#                         ${OSGGdalSrcDir}/frmts/zlib/inffast.h
#                         ${OSGGdalSrcDir}/frmts/zlib/inffixed.h
#                         ${OSGGdalSrcDir}/frmts/zlib/inftrees.h
#                         ${OSGGdalSrcDir}/frmts/zlib/infutil.h
#                         ${OSGGdalSrcDir}/frmts/zlib/trees.h
#                         ${OSGGdalSrcDir}/frmts/zlib/zconf.h
#                         ${OSGGdalSrcDir}/frmts/zlib/zlib.h
#                         ${OSGGdalSrcDir}/frmts/zlib/zutil.h

                         ${OSGGdalSrcDir}/frmts/mem/memdataset.h

                         ${OSGGdalSrcDir}/frmts/gif/libungif/gif_lib.h
                         ${OSGGdalSrcDir}/frmts/gif/libungif/gif_lib_private.h
                         
                         ${OSGGdalSrcDir}/frmts/envisat/EnvisatFile.h

                         ${OSGGdalSrcDir}/frmts/fit/fit.h
                         ${OSGGdalSrcDir}/frmts/fit/gstEndian.h
                         ${OSGGdalSrcDir}/frmts/fit/gstTypes.h

                         ${OSGGdalSrcDir}/frmts/vrt/vrtdataset.h

                         ${OSGGdalSrcDir}/frmts/nitf/mgrs.h
                         ${OSGGdalSrcDir}/frmts/nitf/nitflib.h)


  SET(OSG_GDAL_SRCS ${OSG_GDAL_PORT_SRCS}
                    ${OSG_GDAL_ALG_SRCS}
                    ${OSG_GDAL_OGR_SRCS}
                    ${OSG_GDAL_GCORE_SRCS}
                    ${OSG_GDAL_OGR_FRMTS_SRCS}
                    ${OSG_GDAL_FRMTS_SRCS})

  SET(OSG_GDAL_HDR ${OSG_GDAL_PORT_HDR}
                   ${OSG_GDAL_ALG_HDR}
                   ${OSG_GDAL_OGR_HDR}
                   ${OSG_GDAL_GCORE_HDR}
                   ${OSG_GDAL_OGR_FRMTS_HDR}
                   ${OSG_GDAL_FRMTS_HDR})

  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/gcore)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/alg)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/port)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/ogr)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/ogr/ogrsf_frmts)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/iso8211)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/sdts)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/mem)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/raw)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/vrt)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/gtiff/libtiff)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/gtiff/libgeotiff)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/gif/libungif)
  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/ogr/ogrsf_frmts/avc)
#  INCLUDE_DIRECTORIES(${OSGGdalSrcDir}/frmts/sdts)
  INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/gdal)
  INCLUDE_DIRECTORIES(${OSG_EXPAT_INCLUDE_DIR})
  INCLUDE_DIRECTORIES(${OSG_PNG_INCLUDE_DIR})
  INCLUDE_DIRECTORIES(${OSG_ZLIB_INCLUDE_DIR})
  INCLUDE_DIRECTORIES(${OSG_JPEG_INCLUDE_DIR})

  SET(OSGGDAL_DEF HAVE_XERCES=0;FRMT_ceos;FRMT_aigrid;FRMT_elas;FRMT_hfa;FRMT_gtiff;FRMT_sdts;FRMT_raw;FRMT_gxf;FRMT_ceos2;FRMT_png;FRMT_dted;FRMT_mem;FRMT_jdem;FRMT_gif;FRMT_envisat;FRMT_aaigrid;FRMT_usgsdem;FRMT_l1b;FRMT_fit;FRMT_vrt;FRMT_xpm;FRMT_bmp;FRMT_nitf;FRMT_pcidsk;FRMT_jpeg;ZIP_SUPPORT;SHAPE_ENABLED;TAB_ENABLED;NTF_ENABLED;SDTS_ENABLED;TIGER_ENABLED;S57_ENABLED;DGN_ENABLED;VRT_ENABLED;AVCBIN_ENABLED;REC_ENABLED;MEM_ENABLED;CSV_ENABLED;KML_ENABLED;USE_CPL;_VC80_UPGRADE=0x0710;_MBCS;)

  IF(BUILD_SHARED_LIBS)
    ADD_LIBRARY(${${PROJECT_NAME}SharedTarget} SHARED ${OSG_GDAL_SRCS})

    ADD_DEPENDENCIES(ALL_STANDARD_BUILD ${${PROJECT_NAME}SharedTarget})

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          DEBUG_POSTFIX "D")

    SET(OSGGDAL_DEF_SHARED ${OSGGDAL_DEF};_USRDLL;GDAL_EXPORTS;SHAPELIB_DLLEXPORT;_WINDLL)

    SET_TARGET_PROPERTIES(${${PROJECT_NAME}SharedTarget} PROPERTIES
                          COMPILE_DEFINITIONS "${OSGGDAL_DEF_SHARED}")

    TARGET_LINK_LIBRARIES(${${PROJECT_NAME}SharedTarget} odbc32.lib 
                                                         odbccp32.lib
                                                         ${OSG_EXPAT_SHARED_LIBRARY}
                                                         ${OSG_JPEG_STATIC_LIBRARY}
                                                         ${OSG_PNG_STATIC_LIBRARY}
                                                         ${OSG_ZLIB_STATIC_LIBRARY})

    INSTALL(TARGETS ${${PROJECT_NAME}SharedTarget}
                CONFIGURATIONS Release Debug
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)
  ENDIF(BUILD_SHARED_LIBS)

  INSTALL(FILES ${OSG_GDAL_HDR}
          DESTINATION include/gdal
          PERMISSIONS OWNER_WRITE OWNER_READ
                      GROUP_READ
                      WORLD_READ)

#  SET(OSG_GLUT_INCLUDE_DIR ${OSGFreeGlutSrcDir}/include CACHE PATH "")
#  SET(OSG_GLUT_STATIC_LIBRARY ${${PROJECT_NAME}StaticTarget} CACHE STRING "")
#  SET(OSG_GLUT_SHARED_LIBRARY ${${PROJECT_NAME}SharedTarget} CACHE STRING "")

ELSE(OSGGdalSrcDir)
  SET(OSGGdalSrcDir "" CACHE PATH "")
ENDIF(OSGGdalSrcDir)

#/Od /I "..\..\frmts\mem" /I "..\..\frmts\gif\libungif" /I "..\..\frmts\raw" /I
#"." /I "..\..\frmts\gtiff\libtiff" /I "..\..\frmts\gtiff\libgeotiff" /I
#" /I "..\..\frmts\sdts" /I "..\..\frmts\iso8211" /I
#"..\..\frmts\vrt" /I "..\..\port" /I "..\..\ogr" /I "..\..\ogr\ogrsf_frmts" /I
#"..\..\ogr\ogrsf_frmts\avc" /I "..\..\alg" /I
#"E:\user\gerrit\Projects\OpenSG\svn\OpenSG.Support.install\include" 


#/D "WIN32" /D "_DEBUG" /D "_WINDOWS" 





#/D"_CRT_SECURE_NO_DEPRECATE" 

#/Gm /EHsc /RTC1 /MDd /Fo"Debug_DLL\\" /Fd"Debug_DLL\vc90.pdb" /W3 /c /Wp64 /Zi
#/TP /wd4251 /errorReport:prompt 

#/OUT:"Debug_DLL/gdal14d-vc8.dll" /INCREMENTAL /NOLOGO /LIBPATH:"E:\user\gerrit\Projects\OpenSG\svn\OpenSG.Support.install\lib" /DLL /MANIFEST /MANIFESTFILE:"Debug_DLL\gdal14d-vc8.dll.intermediate.manifest" /MANIFESTUAC:"level='asInvoker' uiAccess='false'"  /NODEFAULTLIB:"msvcrt.lib" /INCLUDE:"_GDALGCPTransform" /INCLUDE:"_OGRRegisterAll" /INCLUDE:"_OGRFeatureStylePuller" /INCLUDE:"_OSRValidate" /INCLUDE:"_OPTGetProjectionMethods" /INCLUDE:"_OGR_G_GetPointCount" /DEBUG /PDB:"Debug_DLL/gdal13d.pdb" /SUBSYSTEM:CONSOLE /DYNAMICBASE:NO /IMPLIB:"Debug_DLL/gdal_id-vc8.lib" /MACHINE:X86 /ERRORREPORT:PROMPT  libosgpngD.lib libosgjpgD.lib libosgzlibD.lib osgexpatD.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib  
