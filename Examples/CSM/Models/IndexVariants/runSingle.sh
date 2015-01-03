
export _OSG_IV_DATA_ROOT_=../OpenSG/Examples/CSM/Models/IndexVariants/Single
export _OSG_TWG_DIR_=./bin


#./bin/testWindowGLUT ${_OSG_IV_DATA_ROOT_}/plane_dl_nvbo_att_nvao.osg

testFiles=("plane_dl_nvbo_att_nvao.osg"    \
           "plane_dl_nvbo_att_vao.osg"     \
           "plane_dl_nvbo_natt_nvao.osg"   \
           "plane_dl_nvbo_natt_vao.osg"    \
\
           "plane_dl_vbo_att_nvao.osg"     \
           "plane_dl_vbo_att_vao.osg"      \
           "plane_dl_vbo_natt_nvao.osg"    \
           "plane_dl_vbo_natt_vao.osg"     \
\
           "plane_ndl_nvbo_att_nvao.osg"   \
           "plane_ndl_nvbo_att_vao.osg"    \
           "plane_ndl_nvbo_natt_nvao.osg"  \
           "plane_ndl_nvbo_natt_vao.osg"   \
\
           "plane_ndl_vbo_att_nvao.osg"    \
           "plane_ndl_vbo_att_vao.osg"     \
           "plane_ndl_vbo_natt_nvao.osg"   \
           "plane_ndl_vbo_natt_vao.osg")

testResults=("no pos, vap fallback" \
             "no pos, no fallback" \
             "no pos, vap fallback" \
             "no pos, no fallback" \
\
             "ok" \
             "ok" \
             "ok" \
             "ok" \
\
             "ok, vap" \
             "no pos, no fallback" \
             "ok, vap" \
             "no pos, no fallback" \
\
             "ok, vap" \
             "ok" \
             "ok, vap" \
             "ok")

for testIndex in ${!testFiles[*]}
#for testFile in "${testFiles[@]}"
do
   :
   echo "---------------------------------"
   echo "running ${testFiles[$testIndex]}"
   echo "expected : ${testResults[$testIndex]}"
   ${_OSG_TWG_DIR_}/testWindowGLUT ${_OSG_IV_DATA_ROOT_}/${testFiles[$testIndex]}
   echo "expected : ${testResults[$testIndex]}"
   echo "##################################"
done
