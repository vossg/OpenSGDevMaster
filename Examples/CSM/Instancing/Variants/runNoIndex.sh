
export _OSG_IV_EX_ROOT_=../OpenSG/Examples/CSM
export _OSG_IV_DATA_ROOT_=../OpenSG/Examples/CSM/Models/IndexVariants/NoIndex
export _OSG_TWG_DIR_=./bin

def="--global ${_OSG_IV_EX_ROOT_}/Common/default-setup.osg"
sys="--system ${_OSG_IV_EX_ROOT_}/Common/system-native.osg"

#--global ../OpenSG/Examples/CSM/Models/IndexVariants/NoIndex/plane_ndl_vbo_natt_vao.osg 

dat="--data ${_OSG_IV_EX_ROOT_}/Instancing/Variants/Simple/scene.osg"
ms="--global ${_OSG_IV_EX_ROOT_}/Common/simple_mouse.osg"

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
   echo "running ${testFiles[$testIndex]}"
   echo "expected : ${testResults[$testIndex]}"

   echo "def ${def}"
   echo "def ${sys}"
   echo "def ${dat}"
   echo "def ${ms}"

   echo "
   ${_OSG_TWG_DIR_}/appCSM ${def} ${sys} \
       --global ${_OSG_IV_DATA_ROOT_}/${testFiles[$testIndex]} \
       ${dat} ${ms}"

   ${_OSG_TWG_DIR_}/appCSM ${def} ${sys} \
       --global ${_OSG_IV_DATA_ROOT_}/${testFiles[$testIndex]} \
       ${dat} ${ms}

   echo "expected : ${testResults[$testIndex]}"
done
