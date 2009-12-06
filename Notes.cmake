
# setup dependend build dir :

cmake -DOSG_BUILD_DEPENDEND:INTERNAL=true -DOSG_REFERENCE_DIR:INTERNAL=../OpenSG.build -DCMAKE_BUILD_TYPE:STRING=Release ../OpenSG

