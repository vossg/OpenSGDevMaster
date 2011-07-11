/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include "OSGOFRecords.h"

#include "OSGSingletonHolder.ins"
#include "OSGGroup.h"
#include "OSGNode.h"

#include "OSGOFDatabase.h"
#include "OSGOpenFlightLog.h"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(OFRecordFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<OFRecordFactoryBase>;


//---------------------------------------------------------------------
// OFRecordFactoryBase
//---------------------------------------------------------------------

OFRecordFactoryBase::RegisterRecord::RegisterRecord(CreateRecord fCreate,
                                                    UInt16       sRecordOpCode)
{
    OFRecordFactory::the()->registerRecord(fCreate, sRecordOpCode);
}


OFRecordFactoryBase::OFRecordFactoryBase(void) :
    _mRegisteredRecords()
{
}

OFRecordFactoryBase::~OFRecordFactoryBase(void)
{
}

void OFRecordFactoryBase::registerRecord(CreateRecord fHelper,
                                         UInt16       sRecordOpCode)
{
    if(fHelper == NULL)
        return;

    NameRecordCreateMap::iterator mRecordIt =
        _mRegisteredRecords.find(sRecordOpCode);


    if(mRecordIt == _mRegisteredRecords.end())
    {
        _mRegisteredRecords[sRecordOpCode] = fHelper;

        PINFO << "Record registered for "
              << sRecordOpCode
              << std::endl;
    }
    else
    {
        PWARNING << "Record already registered for %s "
                 << sRecordOpCode
                 << std::endl;
    }
}

OFRecordTransitPtr OFRecordFactoryBase::createRecord(
    const OFRecordHeader &oHeader, OFDatabase &oDB)
{
    NameRecordCreateMap::iterator mRecordIt =
        _mRegisteredRecords.find(oHeader.sOpCode);

    OFRecordTransitPtr returnValue(NULL);

    if(mRecordIt != _mRegisteredRecords.end())
    {
        returnValue = (*mRecordIt).second(oHeader, oDB);
    }
    else
    {
        returnValue = new OFUnknownRecord(oHeader, oDB);
    }

    return returnValue;
}

//---------------------------------------------------------------------
// OFRecord
//---------------------------------------------------------------------

/*! \nohierarchy
 */
struct OFOpCodeDesc
{
          UInt16  sOpCode;
    const Char8  *szDesc;
};


OFOpCodeDesc aOpCodeDescs[] =
{
    {1,   "Header"                             },
    {2,   "Group"                              },
    {4,   "Object"                             },
    {5,   "Face"                               },
    {10,  "Push Level"                         },
    {11,  "Pop Level"                          },
    {14,  "Degree of Freedom"                  },
    {19,  "Push Subface"                       },
    {20,  "Pop Subface"                        },
    {21,  "Push Extension"                     },
    {22,  "Pop Extension"                      },
    {23,  "Continuation"                       },
    {31,  "Comment"                            },
    {32,  "Color Palette"                      },
    {33,  "Long ID"                            },
    {49,  "Matrix"                             },
    {50,  "Vector"                             },
    {52,  "Multitexture"                       },
    {53,  "UV List"                            },
    {55,  "Binary Separating Plane"            },
    {60,  "Replicate"                          },
    {61,  "Instance Reference"                 },
    {62,  "Instance Definition"                },
    {63,  "External Reference"                 },
    {64,  "Texture Palette"                    },
    {67,  "Vertex Palette"                     },
    {68,  "Vertex with Color"                  },
    {69,  "Vertex with Color and Normal"       },
    {70,  "Vertex with Color, Normal and UV"   },
    {71,  "Vertex with Color and UV"           },
    {72,  "Vertex List"                        },
    {73,  "Level of Detail"                    },
    {74,  "Bounding Box"                       },
    {76,  "Rotate About Edge"                  },
    {78,  "Translate"                          },
    {79,  "Scale"                              },
    {80,  "Rotate About Point"                 },
    {81,  "Rotate and/or Scale to Point"       },
    {82,  "Put"                                },
    {83,  "Eyepoint and Trackplane Palette"    },
    {84,  "Mesh"                               },
    {85,  "Local Vertex Pool"                  },
    {86,  "Mesh Primitive"                     },
    {87,  "Road Segment"                       },
    {88,  "Road Zone"                          },
    {89,  "Morph Vertex List"                  },
    {90,  "Linkage Palette"                    },
    {91,  "Sound"                              },
    {92,  "Road Path"                          },
    {93,  "Sound Palette"                      },
    {94,  "General Matrix"                     },
    {95,  "Text"                               },
    {96,  "Switch"                             },
    {97,  "Line Style Palette"                 },
    {98,  "Clip Region"                        },
    {100, "Extension"                          },
    {101, "Light Source"                       },
    {102, "Light Source Palette"               },
    {103, "Reserved"                           },
    {104, "Reserved"                           },
    {105, "Bounding Sphere"                    },
    {106, "Bounding Cylinder"                  },
    {107, "Bounding Convex Hull"               },
    {108, "Bounding Volume Center"             },
    {109, "Bounding Volume Orientation"        },
    {110, "Reserved"                           },
    {111, "Light Point"                        },
    {112, "Texture Mapping Palette"            },
    {113, "Material Palette"                   },
    {114, "Name Table"                         },
    {115, "Continuously Adaptive Terrain (CAT)"},
    {116, "CAT Data"                           },
    {117, "Reserved"                           },
    {118, "Reserved"                           },
    {119, "Bounding Histogram"                 },
    {120, "Reserved"                           },
    {121, "Reserved"                           },
    {122, "Push Attribute"                     },
    {123, "Pop Attribute"                      },
    {124, "Reserved"                           },
    {125, "Reserved"                           },
    {126, "Curve"                              },
    {127, "Road Construction"                  },
    {128, "Light Point Appearance Palette"     },
    {129, "Light Point Animation Palette"      },
    {130, "Indexed Light Point"                },
    {131, "Light Point System"                 },
    {132, "Indexed String"                     },
    {133, "Shader Palette"                     },
    {134, "Reserved"                           },
    {135, "Extended Material Header"           },
    {136, "Extended Material Ambient"          },
    {137, "Extended Material Diffuse"          },
    {138, "Extended Material Specular"         },
    {139, "Extended Material Emissive"         },
    {140, "Extended Material Alpha"            },
    {141, "Extended Material Light Map"        },
    {142, "Extended Material Normal Map"       },
    {143, "Extended Material Bump Map"         },
    {144, "Reserved"                           },
    {145, "Extended Material Shadow Map"       },
    {146, "Reserved"                           },
    {147, "Extended Material Reflection Map"   },

    {  0, "Reached last -> Unknown"            }
};

const Char8 *aCategoryNames[] =
{
    "Control",
    "Primary",
    "Ancillary",
    "Continuation",

    "Undefined"
};

#if 0
Obsolete

3  Level of Detail (single precision floating point, replaced by Opcode 73)
6  Vertex with ID (scaled integer coordinates, replaced by Opcodes 68-71)
7  Short Vertex w/o ID (scaled integer coordinates, replaced by Opcodes 68-71)
8  Vertex with Color (scaled integer coordinates, replaced by Opcodes 68-71)
9  Vertex with Color and Normal (scaled integer coordinates, replaced by Opcodes 68-71)
12 Translate (replaced by Opcode 78)
13 Degree of Freedom (scaled integer coordinates, replaced by Opcode 14)
16 Instance Reference (replaced by Opcode 61)
17 Instance Definition (replaced by Opcode 62)
40 Translate (replaced by Opcode 78)
41 Rotate about Point (replaced by Opcode 80)
42 Rotate about Edge (replaced by Opcode 76)
43 Scale (replaced by Opcode 79)
44 Translate (replaced by Opcode 78)
45 Scale nonuniform (replaced by Opcode 79)
46 Rotate about Point (replaced by Opcode 80)
47 Rotate and/or Scale to Point (replaced by Opcode 81)
48 Put (replaced by Opcode 82)
51 Bounding Box (replaced by Opcode 74)
65 Eyepoint Palette (only eyepoints, replaced by Opcode 83)
66 Material Palette (fixed size 64 entries, replaced by Opcode 80)
77 Scale (replaced by Opcode 79)

#endif


/* static */
const Char8 *OFRecord::getOpCodeString(UInt16 sOpCode)
{
    OFOpCodeDesc *pDesc = aOpCodeDescs;

    while(pDesc->sOpCode != 0)
    {
        if(pDesc->sOpCode == sOpCode)
        {
            break;
        }

        ++pDesc;
    }

    return pDesc->szDesc;
}

/* static */
const Char8 *OFRecord::getCategoryString(CategoryE cat)
{
    return aCategoryNames[cat];
}

const Char8 *OFRecord::getOpCodeString(void) const
{
    return getOpCodeString(getOpCode());
}

const Char8 *OFRecord::getCategoryString(void) const
{
    return getCategoryString(getCategory());
}

bool OFRecord::read(std::istream &is)
{
    if(_sLength > 4)
    {
        return readContinue(is, _sLength - 4);
    }
    else
    {
        return is.good();
    }
}

bool OFRecord::readContinue(std::istream &is, UInt16 uiLength)
{
    std::vector<char> tmpBuf;

    tmpBuf.resize(uiLength);

    is.read(&(tmpBuf.front()), uiLength);

    return is.good();
}

NodeTransitPtr OFRecord::convertToNode(void)
{
    NodeTransitPtr returnValue(NULL);

    return returnValue;
}

void OFRecord::dump(UInt32 uiIndent)
{
}

OFRecord::OFRecord(const OFRecordHeader &oHeader,
                         OFDatabase     &oDB     ) :
     Inherited(               ),
    _oDB      (oDB            ),
    _sLength  (oHeader.sLength)
{
}

OFRecord::~OFRecord(void)
{
}

//---------------------------------------------------------------------
// OFPrimaryRecord
//---------------------------------------------------------------------

/* static */
OFPrimaryRecord::CategoryE OFPrimaryRecord::getClassCategory(void)
{
    return Category;
}

/* virtual */
OFPrimaryRecord::CategoryE OFPrimaryRecord::getCategory(void) const
{
    return getClassCategory();
}

/* virtual */
bool OFPrimaryRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    OSG_OPENFLIGHT_LOG(("OFPrimaryRecord::addChild: this "
                        "[%u][%s][%s] - child [%u][%s][%s]\n",
                        getOpCode(),
                        getOpCodeString(),
                        getCategoryString(),
                        pChild->getOpCode(),
                        pChild->getOpCodeString(),
                        pChild->getCategoryString()));

    bool returnValue(false);

    if(pChild->getCategory() == RC_Primary)
    {
        OFPrimaryRecord *pPrimChild = dynamic_cast<OFPrimaryRecord *>(pChild);

        _primaryChildren.push_back(pPrimChild);

        returnValue = true;
    }
    else if(pChild->getCategory() == RC_Ancillary)
    {
        OFAncillaryRecord *pAncilChild =
            dynamic_cast<OFAncillaryRecord *>(pChild);

        _ancillaryChildren.push_back(pAncilChild);

        returnValue = true;
    }
    else
    {
        FFATAL(("OFPrimaryRecord::addChild: attempting to add child "
                "[%u][%s] with unsupported category [%s].\n",
                pChild->getOpCode(),
                pChild->getOpCodeString(),
                pChild->getCategoryString()));
    }

    return returnValue;
}

/* virtual */
void OFPrimaryRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "#PrimaryChildren " << _primaryChildren.size() << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _primaryChildren.size(); ++i)
    {
        _primaryChildren[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "#AncillaryChildren " << _ancillaryChildren.size() << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    uiIndent += 2;

    for(UInt32 i = 0; i < _ancillaryChildren.size(); ++i)
    {
        _ancillaryChildren[i]->dump(uiIndent);
    }

    uiIndent -= 2;

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;
    
}

OFPrimaryRecord::OFPrimaryRecord(const OFRecordHeader &oHeader,
                                       OFDatabase     &oDB     ) :
    Inherited         (oHeader, oDB),
    _primaryChildren  (),
    _ancillaryChildren()
{
}

/* virtual */
OFPrimaryRecord::~OFPrimaryRecord(void)
{
}

//---------------------------------------------------------------------
// OFAncillaryRecord
//---------------------------------------------------------------------

/* static */
OFAncillaryRecord::CategoryE OFAncillaryRecord::getClassCategory(void)
{
    return Category;
}

/* virtual */
OFAncillaryRecord::CategoryE OFAncillaryRecord::getCategory(void) const
{
    return getClassCategory();
}

/* virtual */
bool OFAncillaryRecord::addChild(OFRecord *pChild)
{
    FFATAL(("OFAncillaryRecord::addChild: called for [%u][%s] "
            "with child [%u][%s] - this should never happen.\n",
            getOpCode(), getOpCodeString(),
            (pChild != NULL ? pChild->getOpCode() : 0),
            (pChild != NULL ? pChild->getOpCodeString() : "NULL")));

    return false;
}

/* virtual */
NodeTransitPtr OFAncillaryRecord::convertToNode(void)
{
    FFATAL(("OFAncillaryRecord::convertToNode: called for [%u][%s] "
            "- this should never happen.\n",
            getOpCode(), getOpCodeString()));

    return NodeTransitPtr(NULL);
}

/* virtual */
NodeTransitPtr OFAncillaryRecord::convert(Node *pNode)
{
    FWARNING(("OFAncillaryRecord::convert: Not implemented for [%u][%s].\n",
              getOpCode(), getOpCodeString()));
}

OFAncillaryRecord::OFAncillaryRecord(const OFRecordHeader &oHeader,
                                           OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB)
{
}

/* virtual */
OFAncillaryRecord::~OFAncillaryRecord(void)
{
}

//---------------------------------------------------------------------
// OFControlRecord
//---------------------------------------------------------------------

/* static */
OFControlRecord::CategoryE OFControlRecord::getClassCategory(void)
{
    return Category;
}

/* virtual */
OFControlRecord::CategoryE OFControlRecord::getCategory(void) const
{
    return getClassCategory();
}

/* virtual */
bool OFControlRecord::addChild(OFRecord *pChild)
{
    FFATAL(("OFControlRecord::addChild: This should never be called\n"));

    return false;
}

OFControlRecord::OFControlRecord(const OFRecordHeader &oHeader,
                                       OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB)
{
}

/* virtual */
OFControlRecord::~OFControlRecord(void)
{
}

//---------------------------------------------------------------------
// OFUnknownRecord
//---------------------------------------------------------------------

OFUnknownRecord::OFUnknownRecord(const OFRecordHeader &oHeader,
                                       OFDatabase     &oDB     ) :
    Inherited(oHeader, oDB    ),
    _sOpCode  (oHeader.sOpCode),
    _vChildren(               )
{
}

OFUnknownRecord::~OFUnknownRecord(void)
{
}

bool OFUnknownRecord::read(std::istream &is)
{
    OSG_OPENFLIGHT_LOG(("OFUnknownRecord::read op [%u][%s] len [%u]\n",
                        _sOpCode, getOpCodeString(_sOpCode), _sLength));

    static std::vector<char> tmpBuf;

    if(_sLength > 4)
    {
        tmpBuf.resize(_sLength);

        is.read(&(tmpBuf.front()), _sLength - 4);
    }

    return is.good();
}

bool OFUnknownRecord::addChild(OFRecord *pChild)
{
    if(pChild == NULL)
        return false;

    OSG_OPENFLIGHT_LOG(("OFUnknownRecord::addChild: this [%u][%s][%s] "
                        "child [%u][%s][%s]\n",
                        getOpCode(),
                        getCategoryString(),
                        getOpCodeString(),
                        pChild->getOpCode(),
                        pChild->getCategoryString(),
                        pChild->getOpCodeString()   ));

    _vChildren.push_back(pChild);

    return true;
}

/* virtual */
UInt16 OFUnknownRecord::getOpCode(void) const
{
    return _sOpCode;
}

/* virtual */
OFUnknownRecord::CategoryE OFUnknownRecord::getCategory(void) const
{
    return RC_Undefined;
}

NodeTransitPtr OFUnknownRecord::convertToNode(void)
{
    NodeTransitPtr returnValue(NULL);

    if(_vChildren.empty() == false)
    {
        returnValue = makeCoredNode<Group>();

        for(UInt32 i = 0; i < _vChildren.size(); ++i)
            returnValue->addChild(_vChildren[i]->convertToNode());
    }

    return returnValue;
}

void OFUnknownRecord::dump(UInt32 uiIndent)
{
    indentLog(uiIndent, PLOG);
    PLOG << "OFUnknownRecord - " << _sOpCode
         << " - "                << getOpCodeString(_sOpCode)
         << std::endl;
}

OSG_END_NAMESPACE
