
FIND_PATH(COLLADA_DAE_INCLUDE_DIR dae.h
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/local/include/colladadom
    /usr/include/
    /usr/include/colladadom
    /sw/include 
    /opt/local/include
    /opt/include
)

FIND_PATH(COLLADA_DOM_INCLUDE_DIR /dom
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/local/include/colladadom
    /usr/include/
    /usr/include/colladadom
    /sw/include 
    /opt/local/include
    /opt/include
)


FIND_LIBRARY(COLLADA_LIBRARY 
    NAMES collada_dom collada14dom libcollada14dom21
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/lib
)

FIND_LIBRARY(COLLADA_LIBRARY_DEBUG 
    NAMES collada_dom-d collada14dom-d libcollada14dom21-d
    PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib64
    /usr/local/lib
    /usr/lib64
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/lib
)

SET(COLLADA_FOUND "NO")

IF(COLLADA_LIBRARY)
    IF(COLLADA_DAE_INCLUDE_DIR AND COLLADA_DOM_INCLUDE_DIR)
        SET(COLLADA_FOUND "YES")
    ENDIF(COLLADA_DAE_INCLUDE_DIR AND COLLADA_DOM_INCLUDE_DIR)
ENDIF(COLLADA_LIBRARY)
