
export _OSG_IV_EX_ROOT_=../OpenSG/Examples/CSM
export _OSG_IV_DATA_ROOT_=../OpenSG/Examples/CSM/Models/IndexVariants/Multi
export _OSG_TWG_DIR_=./bin

def="--global ${_OSG_IV_EX_ROOT_}/Common/default-setup.osg"
sys="--system ${_OSG_IV_EX_ROOT_}/Common/system-native.osg"

dat="--data ${_OSG_IV_EX_ROOT_}/Instancing/Variants/Simple/scene.osg"
ms="--global ${_OSG_IV_EX_ROOT_}/Common/simple_mouse.osg"

#for testIndex in ${!testFiles[*]}
#for testFile in "${testFiles[@]}"
#do
#   :
   echo "running $1"
#   echo "expected : ${testResults[$testIndex]}"

   echo "def ${def}"
   echo "def ${sys}"
   echo "def ${dat}"
   echo "def ${ms}"

   echo "
   ${_OSG_TWG_DIR_}/appCSM ${def} ${sys} \
       --global ${_OSG_IV_DATA_ROOT_}/$1 \
       ${dat} ${ms}"

   ${_OSG_TWG_DIR_}/appCSM ${def} ${sys} \
       --global ${_OSG_IV_DATA_ROOT_}/$1 \
       ${dat} ${ms}

#   echo "expected : ${testResults[$testIndex]}"
#done
