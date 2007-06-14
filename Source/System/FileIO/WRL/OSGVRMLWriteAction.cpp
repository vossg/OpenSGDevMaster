/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGLog.h"
#include "OSGFieldContainer.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGGroup.h"
#include "OSGGeometry.h"
#include "OSGTriangleIterator.h"
#include "OSGComponentTransform.h"
//#include "OSGGeoPropPtrs.h"
#include "OSGSimpleMaterial.h"
#include "OSGMaterialGroup.h"
#include "OSGAction.h"
#include "OSGVRMLWriteAction.h"
#include "OSGNameAttachment.h"
#include "OSGTextureObjChunk.h"
#include "OSGImage.h"
#include "OSGImageFileHandler.h"
#include "OSGSimpleGeometry.h"
#include "OSGSceneFileHandler.h"

#include "OSGGL.h"

#include "functional"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VRMLWriteAction
    \ingroup GrpSystemAction

The action class for writing VRML files.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

VRMLWriteAction::ActionInitializer::ActionInitializer(void)
{
    addPostFactoryInitFunction(&VRMLWriteAction::initializeAction);
    addPreFactoryExitFunction (&VRMLWriteAction::terminateAction );
}

VRMLWriteAction::ActionInitializer::~ActionInitializer(void)
{
}

VRMLWriteAction::FCInfo::FCInfo(void) :
    _iTimesUsed(0     ),
    _bOwnName   (false),
    _szName     (NULL ),
    _bWritten    (false)
{
}

VRMLWriteAction::FCInfo::FCInfo(const FCInfo &source) :
    _iTimesUsed(source._iTimesUsed),
    _bOwnName  (source._bOwnName  ),
    _szName    (NULL              ),
    _bWritten   (source._bWritten   )
{
    if(_bOwnName == true)
    {
        osgStringDup(source._szName, _szName);
    }
}

VRMLWriteAction::FCInfo::~FCInfo(void)
{
    if(_bOwnName == true)
        delete [] _szName;
}

Char8 VRMLWriteAction::FCInfo::mapChar(Char8 c)
{
    // These are taken from the VRML97 reference document
    static char badchars[] = {  
        0x22, 0x23, 0x27, 0x2c, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x7f
    };
    
    if (c <= 0x20) return '_';
    
    for(Int16 i = 0; i < sizeof(badchars); ++i)
        if(c == badchars[i])
            return '_';
    
    return c;
}

void VRMLWriteAction::FCInfo::convertName(Char8 *&szName)
{       
    if(szName == NULL)
        return;
    
    for(UInt32 i = 0; i < strlen(szName); i++)
    {
        szName[i] = mapChar(szName[i]);
    }
    
    // first char a number a plus or a minus? add an _
    if((szName[0] >= 0x30 && szName[0] <= 0x39) ||
        szName[0] == 0x2b || szName[0] == 0x2d)
    {
        Char8 *newstring = new char [strlen(szName) + 2];
        
        newstring[0] = '_';
        strcpy(newstring + 1, szName);
        delete[] szName;
        szName = newstring;
    }
}

void VRMLWriteAction::FCInfo::setName(const Char8 *szName)
{
    osgStringDup(szName, _szName);
    convertName(_szName);
    _bOwnName = true;
}

void VRMLWriteAction::FCInfo::buildName(const Char8  *szTypename,
                                              UInt32  uiContainerId)
{
    if(_szName != NULL)
        return;

    if(szTypename != NULL)
    {
        _szName = new Char8[strlen(szTypename) + 32];

        sprintf(_szName, "%s_%u", szTypename, uiContainerId);
    }
    else
    {
        _szName = new Char8[64];
        
        sprintf(_szName, "UType_%u", uiContainerId);
    }

    _bOwnName = true;
}

void VRMLWriteAction::FCInfo::incUse(void)
{
    _iTimesUsed++;
}

UInt32 VRMLWriteAction::FCInfo::getUse(void) const
{
    return _iTimesUsed;
}

const Char8 *VRMLWriteAction::FCInfo::getName(void) const
{
    return _szName;
}

bool VRMLWriteAction::FCInfo::getWritten(void) const
{
    return _bWritten;
}

void VRMLWriteAction::FCInfo::setWritten(void)
{
    _bWritten = true;
}

Int32 VRMLWriteAction::FCInfo::clear(void)
{
    _iTimesUsed = 0;

    if(_bOwnName == true)
    {
        delete [] _szName;
    }

    _bOwnName = false;
    _szName   = NULL;
    _bWritten  = false;

    return 0;
}

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLWriteAction::cvsid[] = "@(#)$Id$";

VRMLWriteAction * VRMLWriteAction::_prototype = NULL;

std::vector<Action::Functor> *VRMLWriteAction::_defaultEnterFunctors;
std::vector<Action::Functor> *VRMLWriteAction::_defaultLeaveFunctors;

VRMLWriteAction::ActionInitializer VRMLWriteAction::_actionInitializer;


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void VRMLWriteAction::registerEnterDefault(const FieldContainerType &type, 
                                           const Action::Functor    &func)
{
    if(_defaultEnterFunctors == NULL)
        _defaultEnterFunctors = new std::vector<Action::Functor>;

    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back(&Action::_defaultEnterFunction);
    }
    
    (*_defaultEnterFunctors)[type.getId()] = func;
}

void VRMLWriteAction::registerLeaveDefault(const FieldContainerType &type, 
                                           const Action::Functor    &func)
{
    if(_defaultLeaveFunctors == NULL)
        _defaultLeaveFunctors = new std::vector<Action::Functor>;

    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back(&Action::_defaultLeaveFunction);
    }
    
    (*_defaultLeaveFunctors)[type.getId()] = func;
}

void VRMLWriteAction::setPrototype(VRMLWriteAction *proto)
{
    _prototype = proto;
}

VRMLWriteAction *VRMLWriteAction::getPrototype( void )
{
    return _prototype;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

ActionBase::ResultE VRMLWriteAction::writeGroupEnter(NodeCorePtrConstArg , 
                                                     Action     *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    NodePtr pNode = pAction->getActNode();

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write Group Enter 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pNode);
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->updateProgress();

        NodeCorePtr pCore = pNode->getCore();

        FCInfo *pInfo     = pWriter->getInfo(pNode);
        FCInfo *pCoreInfo = pWriter->getInfo(pCore);

        if(pInfo == NULL || pCoreInfo == NULL)
        {
            FWARNING(("Info missing %p %p\n", pInfo, pCoreInfo));
            return Action::Quit;
        }

        if(pCoreInfo->getUse()    >  0 && 
           pCoreInfo->getWritten() == true)
        {
            pWriter->printIndent();
            fprintf(pFile, "Group # osg shared %s\n", pCoreInfo->getName());

//            pWriter->setCurrentUse(true);
        }
        else if((pCoreInfo->getName()    != NULL) &&
               (pCoreInfo->getName()[0] != '\0'))
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Group\n", pCoreInfo->getName());
            
            pCoreInfo->setWritten();
        }
        else if((pInfo->getName()    != NULL) &&
                (pInfo->getName()[0] != '\0'))
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Group\n", pInfo->getName());
            
            pInfo->setWritten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "Group\n");
        }
                    
        pWriter->printIndent();
        fprintf(pFile, "{\n");
        
        if(pNode->getNChildren() != 0)
        {
            pWriter->incIndent(4);
            
            pWriter->printIndent();
            fprintf(pFile, "children [\n");
            
            pWriter->incIndent(4);        
        }
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeGroupLeave(NodeCorePtrConstArg , 
                                                 Action              *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    NodePtr pNode = pAction->getActNode();

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write Group Leave 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        if(pWriter->isCurrentUse() == false)
        {
            if(pNode->getNChildren() != 0)
            {
                pWriter->decIndent(4);
                
                pWriter->printIndent();
                fprintf(pFile, "]\n");
                
                pWriter->decIndent(4);
            }

            pWriter->printIndent();
            fprintf(pFile, "}\n");
        }
        
        pWriter->setCurrentUse(false);
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeComponentTransformEnter(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);
    NodePtr pNode = pAction->getActNode();
    ComponentTransformPtr pTrans = 
        dynamic_cast<ComponentTransformPtr>(pNode->getCore());

    Real32 rQX;
    Real32 rQY;
    Real32 rQZ;
    Real32 rQW;

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write ComponentTransform Enter 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pNode);
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->updateProgress();

        FCInfo *pInfo = pWriter->getInfo(pNode);

        if(pInfo == NULL)
        {
            return Action::Quit;
        }

        if((pInfo->getName() != NULL   ) &&
           (pInfo->getWritten() == false) && 
           (pInfo->getName()[0] != '\0'))
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Transform\n", pInfo->getName());

            pInfo->setWritten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "Transform\n");
        }

        pWriter->printIndent();
        fprintf(pFile, "{\n");

        pWriter->incIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "center %f %f %f\n",
                pTrans->getCenter()[0],
                pTrans->getCenter()[1],
                pTrans->getCenter()[2]);

        pTrans->getRotation().getValueAsAxisRad(rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "rotation %f %f %f %f\n",
                rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "scale %f %f %f\n",
                pTrans->getScale()[0],
                pTrans->getScale()[1],
                pTrans->getScale()[2]);

        pTrans->getScaleOrientation().getValueAsAxisRad(rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "scaleOrientation %f %f %f %f\n",
                rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "translation %f %f %f\n", 
                pTrans->getTranslation()[0],
                pTrans->getTranslation()[1],
                pTrans->getTranslation()[2]);

        pWriter->printIndent();
        fprintf(pFile, "children [\n");

        pWriter->incIndent(4);
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeComponentTransformLeave(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write ComponentTransform Leave 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "]\n");

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "}\n");
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeTransformEnter(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);
    NodePtr pNode = pAction->getActNode();
    TransformPtr pTrans = dynamic_cast<TransformPtr>(pNode->getCore());

    Real32 rQX;
    Real32 rQY;
    Real32 rQZ;
    Real32 rQW;

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write Transform Enter 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pNode);
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->updateProgress();

        FCInfo *pInfo = pWriter->getInfo(pNode);

        if(pInfo == NULL)
        {
            return Action::Quit;
        }

        if((pInfo->getName() != NULL   ) &&
           (pInfo->getWritten() == false) && 
           (pInfo->getName()[0] != '\0'))
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Transform\n", pInfo->getName());

            pInfo->setWritten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "Transform\n");
        }

        pWriter->printIndent();
        fprintf(pFile, "{\n");

        pWriter->incIndent(4);

        // decompose matrix.
        Matrix m = pTrans->getSFMatrix()->getValue();
        Vec3f translation, scale, center;
        Quaternion rotation, scaleOrientation;
        m.getTransform(translation, rotation, scale, scaleOrientation);
        
        pWriter->printIndent();
        fprintf(pFile, "center %f %f %f\n",
                center[0],
                center[1],
                center[2]);

        rotation.getValueAsAxisRad(rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "rotation %f %f %f %f\n",
                rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "scale %f %f %f\n",
                scale[0],
                scale[1],
                scale[2]);

        scaleOrientation.getValueAsAxisRad(rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "scaleOrientation %f %f %f %f\n",
                rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "translation %f %f %f\n", 
                translation[0],
                translation[1],
                translation[2]);

        pWriter->printIndent();
        fprintf(pFile, "children [\n");

        pWriter->incIndent(4);
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeTransformLeave(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write Transform Leave 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "]\n");

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "}\n");
    }

    return Action::Continue;
}

void VRMLWriteAction::writePoints(GeometryPtr      pGeo, 
                                  FILE            *pFile,
                                  VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoVectorPropertyPtr pPos = pGeo->getPositions();

    if(pPos == NullFC)
        return;

    pWriter->printIndent();
    fprintf(pFile, "coord Coordinate\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "point [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pPos->getSize(); i++)
    {
        pWriter->printIndent();

        Pnt3f p;
        pPos->getValue(p,i);
        
        fprintf(pFile, "%f %f %f", p[0], p[1], p[2]);

        if(i == pPos->getSize() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ", \n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");

}

void VRMLWriteAction::writeNormals(GeometryPtr      pGeo, 
                                   FILE            *pFile,
                                   VRMLWriteAction *pWriter)
{
    if(0 != (pWriter->getOptions() & VRMLWriteAction::OSGNoNormals))
        return;

    if(pGeo == NullFC)
        return;

    GeoVectorPropertyPtr pNorm = pGeo->getNormals();

    if(pNorm == NullFC)
        return;

    pWriter->printIndent();
    fprintf(pFile, "normal Normal\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "vector [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pNorm->getSize(); i++)
    {
        pWriter->printIndent();

        Vec3f n;
        pNorm->getValue(n,i);
        
        fprintf(pFile, "%f %f %f", n[0], n[1], n[2]);

        if(i == pNorm->getSize() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ", \n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

void VRMLWriteAction::writeColors(GeometryPtr      pGeo, 
                                  FILE            *pFile,
                                  VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoVectorPropertyPtr pCol = pGeo->getColors();

    if(pCol == NullFC)
        return;

    pWriter->printIndent();
    fprintf(pFile, "color Color\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "color [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pCol->getSize(); i++)
    {
        pWriter->printIndent();

        Color3f c;
        pCol->getValue(c,i);
        
        fprintf(pFile, "%f %f %f", c[0], c[1], c[2]);

        if(i == pCol->getSize() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ", \n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

void VRMLWriteAction::writeTexCoords(GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoVectorPropertyPtr pTex = pGeo->getTexCoords();

    if(pTex == NullFC)
        return;

    pWriter->printIndent();
    fprintf(pFile, "texCoord TextureCoordinate\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "point [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pTex->getSize(); i++)
    {
        pWriter->printIndent();

        Vec2f t;
        pTex->getValue(t,i);
        
        fprintf(pFile, "%f %f", t[0], t[1]);
 
        if(i == pTex->getSize() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ", \n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

void VRMLWriteAction::writeIndex(GeometryPtr      pGeo, 
                                 FILE            *pFile,
                                 VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoIntegralPropertyPtr pIndex  = pGeo->getIndices();
    GeoIntegralPropertyPtr pTypes  = pGeo->getTypes  ();
    GeoIntegralPropertyPtr pLength = pGeo->getLengths();

    if((pIndex  == NullFC) ||
       (pTypes  == NullFC) ||
       (pLength == NullFC))
    {
        return;
    }

    if(pIndex->size() == 0 ||
       pTypes->size() == 0 ||
       pLength->size() == 0)
    {
        return;
    }

    pWriter->printIndent();
    fprintf(pFile, "coordIndex [\n");
    pWriter->incIndent(4);

    TriangleIterator it;

    for(it = pGeo->beginTriangles(); it != pGeo->endTriangles(); ++it)
    {
        pWriter->printIndent();

        for(UInt32 i = 0; i < 3; ++i)
        {
            fprintf(pFile, "%d, ", it.getPositionIndex(i));
        }
/*
        fprintf(pFile, "%d,%d,%d,", it.getPositionIndex(0), 
                                    it.getPositionIndex(1), 
                                    it.getPositionIndex(2));
        if(it.getPositionIndex(3) != -1)
            fprintf(pFile, "%d,", it.getPositionIndex(3));
            */
        
        fprintf(pFile, "-1,\n");
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");
    
    if(pGeo->getNormals()           != NullFC && 
       pGeo->getNormals()->getSize() > 0      &&
       0 == (pWriter->getOptions() & VRMLWriteAction::OSGNoNormals))
    {
        pWriter->printIndent();
        fprintf(pFile, "normalIndex [\n");
        pWriter->incIndent(4);

        TriangleIterator it;

        for(it = pGeo->beginTriangles(); it != pGeo->endTriangles(); ++it)
        {
            pWriter->printIndent();

            for(UInt32 i = 0; i < 3; ++i)
            {
                fprintf(pFile, "%d, ", it.getNormalIndex(i));
            }

/*
            fprintf(pFile, "%d,%d,%d,", it.getNormalIndex(0), 
                                        it.getNormalIndex(1), 
                                        it.getNormalIndex(2));
            if(it.getNormalIndex(3) != -1)
                fprintf(pFile, "%d,", it.getNormalIndex(3));
                */

            fprintf(pFile, "-1,\n");
        }

        pWriter->decIndent(4);
        pWriter->printIndent();
        fprintf(pFile, "]\n");
    }
    
    if(pGeo->getColors() != NullFC && pGeo->getColors()->getSize() > 0)
    {
        pWriter->printIndent();
        fprintf(pFile, "colorIndex [\n");
        pWriter->incIndent(4);

        TriangleIterator it;

        for(it = pGeo->beginTriangles(); it != pGeo->endTriangles(); ++it)
        {
            pWriter->printIndent();

            for(UInt32 i = 0; i < 3; ++i)
            {
                fprintf(pFile, " %d,", it.getColorIndex(i));
            }
/*
            fprintf(pFile, "%d,%d,%d,", it.getColorIndex(0), 
                                        it.getColorIndex(1), 
                                        it.getColorIndex(2));
            if(it.getColorIndex(3) != -1)
                fprintf(pFile, "%d,", it.getColorIndex(3));
                */

            fprintf(pFile, "-1,\n");
        }

        pWriter->decIndent(4);
        pWriter->printIndent();
        fprintf(pFile, "]\n");
    }
    
    if(pGeo->getTexCoords() != NullFC && pGeo->getTexCoords()->getSize() > 0)
    {
        pWriter->printIndent();
        fprintf(pFile, "texCoordIndex [\n");
        pWriter->incIndent(4);

        TriangleIterator it;

        for(it = pGeo->beginTriangles(); it != pGeo->endTriangles(); ++it)
        {
            pWriter->printIndent();

            for(UInt32 i = 0; i < 3; ++i)
            {
                fprintf(pFile, "%d,", it.getTexCoordsIndex(i));
            }
/*
            fprintf(pFile, "%d,%d,%d,", it.getTexCoordsIndex(0), 
                                        it.getTexCoordsIndex(1), 
                                        it.getTexCoordsIndex(2));
            if(it.getTexCoordsIndex(3) != -1)
                fprintf(pFile, "%d,", it.getTexCoordsIndex(3));
                */

            fprintf(pFile, "-1,\n");
        }

        pWriter->decIndent(4);
        pWriter->printIndent();
        fprintf(pFile, "]\n");
    }
}

void VRMLWriteAction::writeLineIndex(GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoIntegralPropertyPtr pTypes  = pGeo->getTypes();
    GeoIntegralPropertyPtr pLength = pGeo->getLengths();

    if((pTypes  == NullFC) ||
       (pLength == NullFC))
    {
        return;
    }

    if(pTypes->size() == 0 ||
       pLength->size() == 0)
    {
        return;
    }

    pWriter->printIndent();
    fprintf(pFile, "coordIndex [\n");
    pWriter->incIndent(4);

    PrimitiveIterator it;
    UInt32            i;

    for(it = pGeo->beginPrimitives(); it != pGeo->endPrimitives(); ++it)
    {
        if(it.getType() == GL_LINES)
        {
            for(i = 0; i < it.getLength(); i += 2)
            {
                pWriter->printIndent();

                fprintf(pFile, "%d, %d, -1,\n", 
                        it.getPositionIndex(i),
                        it.getPositionIndex(i + 1));
            }
        }
        else if(it.getType() == GL_LINE_STRIP)
        {
            pWriter->printIndent();

            for(i = 0; i < it.getLength(); ++i)
            {
                fprintf(pFile, "%d, ", it.getPositionIndex(i));
            }

            fprintf(pFile, "-1,\n");
        }
        else if(it.getType() == GL_LINE_LOOP)
        {
            pWriter->printIndent();

            for(i = 0; i < it.getLength(); ++i)
            {
                fprintf(pFile, "%d, ", it.getPositionIndex(i));
            }

            fprintf(pFile, "%d, -1, \n", it.getPositionIndex(i - 1));
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");


    if(pGeo->getColors() != NullFC && pGeo->getColors()->getSize() > 0)
    {
        pWriter->printIndent();
        fprintf(pFile, "colorIndex [\n");
        pWriter->incIndent(4);

        PrimitiveIterator it;
        UInt32            i;
        
        for(it = pGeo->beginPrimitives(); it != pGeo->endPrimitives(); ++it)
        {
            if(it.getType() == GL_LINES)
            {
                for(i = 0; i < it.getLength(); i += 2)
                {
                    pWriter->printIndent();

                    fprintf(pFile, "%d, %d, -1,\n", 
                            it.getColorIndex(i),
                            it.getColorIndex(i + 1));
                }
            }
            else if(it.getType() == GL_LINE_STRIP)
            {
                pWriter->printIndent();
                
                for(i = 0; i < it.getLength(); ++i)
                {
                    fprintf(pFile, "%d, ", it.getColorIndex(i));
                }
                
                fprintf(pFile, "-1,\n");
            }
            else if(it.getType() == GL_LINE_LOOP)
            {
                pWriter->printIndent();
                
                for(i = 0; i < it.getLength(); ++i)
                {
                    fprintf(pFile, "%d, ", it.getColorIndex(i));
                }
                
                fprintf(pFile, "%d, -1, \n", it.getColorIndex(i - 1));
            }
        }

        pWriter->decIndent(4);
        pWriter->printIndent();
        fprintf(pFile, "]\n");
    }
}

void VRMLWriteAction::writeMaterial(GeometryPtr      pGeo, 
                                    FILE            *pFile,
                                    VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    MaterialPtr pMat;
    
    pMat = pWriter->getMaterial();
    
    if(pMat == NullFC)
        pMat = pGeo->getMaterial();

    if(pMat == NullFC)
        pMat = OSG::getDefaultMaterial();

    if(pWriter->isWritten(pMat))
    {
        pWriter->printIndent();
        fprintf(pFile, "appearance USE App_%u\n", pWriter->getIndex(pMat));
        return;
    }

    pMat->rebuildState();
    StatePtr st = pMat->getState();
    
    StateChunkPtr sChunk =
        st->getChunk(MaterialChunk::getStaticClassId());
    
    if(sChunk == NullFC)
        return;
    
    MaterialChunkPtr mChunk = dynamic_cast<MaterialChunkPtr>(sChunk);
    
    if(mChunk == NullFC)
        return;

    pWriter->printIndent();
    fprintf(pFile, "appearance DEF App_%u Appearance\n", pWriter->setWritten(pMat));
    
    pWriter->printIndent();
    fprintf(pFile, "{\n");
    
    pWriter->incIndent(4);
    
    pWriter->printIndent();
    fprintf(pFile, "material Material\n");
    
    pWriter->printIndent();
    fprintf(pFile, "{\n");
    
    pWriter->incIndent(4);

    Real32 rAmbient = 0.f;

    if(osgAbs(mChunk->getDiffuse()[0]) > Eps)
    {
        rAmbient = mChunk->getAmbient()[0] / mChunk->getDiffuse()[0];
    }
    else if(osgAbs(mChunk->getDiffuse()[1]) > Eps)
    {
        rAmbient = mChunk->getAmbient()[1] / mChunk->getDiffuse()[1];
    }
    else if(osgAbs(mChunk->getDiffuse()[2]) > Eps)
    {
        rAmbient = mChunk->getAmbient()[2] / mChunk->getDiffuse()[2];
    }


    pWriter->printIndent();
    fprintf(pFile, "ambientIntensity %f\n", rAmbient);

    pWriter->printIndent();
    fprintf(pFile, "diffuseColor %f %f %f\n",
            mChunk->getDiffuse()[0],
            mChunk->getDiffuse()[1],
            mChunk->getDiffuse()[2]);

    pWriter->printIndent();
    if(!mChunk->getLit())
    {
        fprintf(pFile, "emissiveColor 1.0 1.0 1.0\n");
    }
    else
    {
        fprintf(pFile, "emissiveColor %f %f %f\n",
                mChunk->getEmission()[0],
                mChunk->getEmission()[1],
                mChunk->getEmission()[2]);
    }

    pWriter->printIndent();
    fprintf(pFile, "shininess %f\n",
            mChunk->getShininess() / 128.);

    pWriter->printIndent();
    fprintf(pFile, "specularColor %f %f %f\n",
            mChunk->getSpecular()[0],
            mChunk->getSpecular()[1],
            mChunk->getSpecular()[2]);

    pWriter->printIndent();
    fprintf(pFile, "transparency %f\n",
            1.f-mChunk->getDiffuse()[3]);
    
    pWriter->decIndent(4);
    
    pWriter->printIndent();
    fprintf(pFile, "}\n");

    sChunk = st->getChunk(TextureObjChunk::getStaticClassId());    

    TextureObjChunkPtr pTChunk = dynamic_cast<TextureObjChunkPtr>(sChunk);

    if(pTChunk != NullFC)
    {
        if(pWriter->isWritten(pTChunk))
        {
            pWriter->printIndent();
            fprintf(pFile, "texture USE Tex_%u\n", pWriter->getIndex(pTChunk));
        }
        else
        {
            ImagePtr pImage = pTChunk->getImage();

            if(pImage != NullFC)
            {
                if(pWriter->getOptions() & 
                                   VRMLWriteAction::OSGPixelTextures)
                {
                    pWriter->printIndent();
                    fprintf(pFile, "texture DEF Tex_%u PixelTexture\n",
                        pWriter->setWritten(pTChunk) );
    
                    pWriter->printIndent();
                    fprintf(pFile, "{\n");
    
                    pWriter->incIndent(4);
    
                    UInt32 pixelformat = pImage->getPixelFormat();
                    UInt32 pixelsize = 1;
                    if ( pixelformat == Image::OSG_RGB_PF)
                        pixelsize = 3;
                    else if ( pixelformat == Image::OSG_RGBA_PF)
                        pixelsize = 4;
                    else if ( pixelformat == Image::OSG_LA_PF )
                        pixelsize = 2;

                    pWriter->printIndent();
                    fprintf(pFile, "image %d %d %u    ",
                        pImage->getWidth(), pImage->getHeight(), pixelsize);
    
                    const UInt8 *data = pImage->getData();
                    for (Int32 x=0; x<pImage->getHeight(); ++x) 
                    {
                        for (Int32 y=0; y<pImage->getWidth(); ++y) 
                        {
                            UInt32 pos = (x * pImage->getWidth() + y) * pixelsize;
                            fprintf(pFile, "0x");
                            for (UInt32 i=0;i<pixelsize;i++) 
                            {
                                fprintf(pFile, "%02X", (pImage->getData())[pos+i] );
                            }
                            fprintf(pFile, " ");
                        }
                        fprintf(pFile, "\n");
                    }
    
                    if(pTChunk->getWrapS() != GL_REPEAT)
                    {
                        pWriter->printIndent();
                        fprintf(pFile, "repeatS FALSE\n");
                    }
    
                    if(pTChunk->getWrapT() != GL_REPEAT)
                    {
                        pWriter->printIndent();
                        fprintf(pFile, "repeatT FALSE\n");
                    }
    
                    pWriter->decIndent(4);
    
                    pWriter->printIndent();
                    fprintf(pFile, "}\n");
                } 
                else
                {
                    const std::string *pFilename = 
                        pImage->findAttachmentField("fileName");
                    std::string filename;
                    if(pFilename == NULL)
                        filename = pImage->getName();
                    else
                        filename = *pFilename;
    
                    if(!filename.empty())
                    {
                        
                        pWriter->printIndent();
                        fprintf(pFile, "texture DEF Tex_%u ImageTexture\n",
                                    pWriter->setWritten(pTChunk) );
    
                        pWriter->printIndent();
                        fprintf(pFile, "{\n");
    
                        pWriter->incIndent(4);
    
                        pWriter->printIndent();
                        fprintf(pFile, "url \"%s\"\n",
                                filename.c_str());
    
                        if(pTChunk->getWrapS() != GL_REPEAT)
                        {
                            pWriter->printIndent();
                            fprintf(pFile, "repeatS FALSE\n");
                        }
    
                        if(pTChunk->getWrapT() != GL_REPEAT)
                        {
                            pWriter->printIndent();
                            fprintf(pFile, "repeatT FALSE\n");
                        }
    
                        pWriter->decIndent(4);
    
                        pWriter->printIndent();
                        fprintf(pFile, "}\n");
                    }
                }
            }
        }
    }
/*
    sChunk = st->getChunk(TextureTransformChunk::getStaticClassId());    

    TextureTransformChunkPtr pTTChunk = dynamic_cast<TextureTransformChunkPtr>(sChunk);

    if(pTTChunk != NullFC)
    {
    }
 */

    pWriter->decIndent(4);
    
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

bool VRMLWriteAction::writeGeoCommon(NodePtr          pNode,
                                     GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter,
                                     const Char8     *setTypename)
{
    FCInfo *pInfo     = pWriter->getInfo(pNode);
    FCInfo *pCoreInfo = pWriter->getInfo(pGeo);

    if(pInfo == NULL || pCoreInfo == NULL || setTypename == NULL)
    {
        FWARNING(("Info missing %p %p\n", pInfo, pCoreInfo));
        return false;
    }

    if(pCoreInfo->getUse()    >  0 && 
       pCoreInfo->getWritten() == true)
    {
        pWriter->printIndent();
        fprintf(pFile, "geometry USE %s\n", pCoreInfo->getName());
        pWriter->setCurrentUse(true);
    }
    else
    {
        if((pCoreInfo->getName()    != NULL) &&
           (pCoreInfo->getName()[0] != '\0'))
        {
            pWriter->printIndent();
            fprintf(pFile, "geometry DEF %s %s\n", 
                    pCoreInfo->getName(), 
                    setTypename);
            
            pCoreInfo->setWritten();
        }
        else if((pInfo->getName()    != NULL) &&
                (pInfo->getName()[0] != '\0'))
        {
            pWriter->printIndent();
            fprintf(pFile, 
                    "geometry DEF %s %s\n", 
                    pInfo->getName(), 
                    setTypename);
            
            pInfo->setWritten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "geometry %s\n", setTypename);

        }

        pWriter->printIndent();
        fprintf(pFile, "{\n");
        
        pWriter->incIndent(4);
    }

    return true;
#if 0

//        pWriter->printIndent();
// !!!        fprintf(pFile, "colorPerVertex  %s\n", 
// !!!                pGeo->getColorPerVertex() ? "TRUE" : "FALSE");

//        pWriter->printIndent();
// !!!        fprintf(pFile, "normalPerVertex %s\n",
// !!!                pGeo->getNormalPerVertex() ? "TRUE" : "FALSE");
#endif
}

void VRMLWriteAction::writePointSet(NodePtr          pNode,
                                    GeometryPtr      pGeo, 
                                    FILE            *pFile,
                                    VRMLWriteAction *pWriter)
{
    FWARNING(("point set not supported\n"));

    if(writeGeoCommon(pNode, pGeo, pFile, pWriter, "PointSet") == true)
    {
        
        if(pWriter->isCurrentUse() == false)
        {
            pWriter->decIndent(4);
            
            pWriter->printIndent();
            fprintf(pFile, "}\n");
        }

        pWriter->setCurrentUse(false);
    }
}

void VRMLWriteAction::writeLineSet(NodePtr          pNode,
                                   GeometryPtr      pGeo, 
                                   FILE            *pFile,
                                   VRMLWriteAction *pWriter,
                                   bool             )
{
    if(writeGeoCommon(pNode, pGeo, pFile, pWriter, "IndexedLineSet") == true)
    {
        
        if(pWriter->isCurrentUse() == false)
        {
            writePoints   (pGeo, pFile, pWriter);
            writeColors   (pGeo, pFile, pWriter);
            
            writeLineIndex(pGeo, pFile, pWriter);
            
            pWriter->decIndent(4);
            
            pWriter->printIndent();
            fprintf(pFile, "}\n");

            writeMaterial(pGeo, pFile, pWriter);
        }

        pWriter->setCurrentUse(false);
    }
}

void VRMLWriteAction::writeFaceSet(NodePtr          pNode,
                                   GeometryPtr      pGeo, 
                                   FILE            *pFile,
                                   VRMLWriteAction *pWriter,
                                   bool             )
{
    if(writeGeoCommon(pNode, pGeo, pFile, pWriter, "IndexedFaceSet") == true)
    {
        if(pWriter->isCurrentUse() == false)
        {
            pWriter->printIndent();
            fprintf(pFile, "solid FALSE\n");

            writePoints   (pGeo, pFile, pWriter);
            writeNormals  (pGeo, pFile, pWriter);
            writeColors   (pGeo, pFile, pWriter);
            writeTexCoords(pGeo, pFile, pWriter);
            
            writeIndex    (pGeo, pFile, pWriter);
            
            pWriter->decIndent(4);
            
            pWriter->printIndent();
            fprintf(pFile, "}\n");

            writeMaterial(pGeo, pFile, pWriter);
        }

        pWriter->setCurrentUse(false);
    }
}


Action::ResultE VRMLWriteAction::writeGeoEnter(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    NodePtr pNode = pAction->getActNode();
    GeometryPtr pGeo = dynamic_cast<GeometryPtr>(pNode->getCore());

    if(pWriter == NULL || pGeo == NullFC)
    {
        return Action::Quit;
    }

    FDEBUG(("Write Geo Enter 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pNode);

        pWriter->addContainerUse(pGeo->getPositions());
        pWriter->addContainerUse(pGeo->getNormals  ());
        pWriter->addContainerUse(pGeo->getColors   ());
        pWriter->addContainerUse(pGeo->getTexCoords());
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->updateProgress();

        pWriter->printIndent();
        fprintf(pFile, "Shape\n");
        pWriter->printIndent();
        fprintf(pFile, "{\n");
        
        pWriter->incIndent(4);

        PrimitiveIterator pIt  = pGeo->beginPrimitives();
        PrimitiveIterator pEnd = pGeo->endPrimitives();

        UInt32 uiPointCount = 0;
        UInt32 uiLineCount  = 0;
        UInt32 uiFaceCount  = 0;

        while(pIt != pEnd)
        {
            if(pIt.getType() == GL_LINES      ||
               pIt.getType() == GL_LINE_STRIP ||
               pIt.getType() == GL_LINE_LOOP   )
            {
                ++uiLineCount;
            }
            else if(pIt.getType() == GL_POINTS)
            {
                ++uiPointCount;
            }
            else
            {
                ++uiFaceCount;
            }

            ++pIt;
        }

        FINFO(( "Geo Stat : %d %d %d\n", 
                uiPointCount, 
                uiLineCount,
                uiFaceCount));

        if(uiPointCount != 0)
        {
            if((uiLineCount != 0) || (uiFaceCount != 0))
            {
                FWARNING(("ERROR writer does not support mixed primitives"
                          "including points\n"));
            }
            else
            {
                writePointSet(pNode, pGeo, pFile, pWriter);
            }
        }
        
        if(uiLineCount != 0)
        {
            writeLineSet(pNode,
                         pGeo, 
                         pFile, 
                         pWriter, 
                         ((uiPointCount == 0) && (uiFaceCount == 0)));
        }
        
        if(uiFaceCount != 0)
        {
            writeFaceSet(pNode,
                         pGeo,
                         pFile,
                         pWriter,
                         ((uiPointCount == 0) && (uiLineCount == 0)));
        }
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeGeoLeave(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    FDEBUG(("Write Geo Leave 0x%04x\n", pWriter->getMode()));

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->decIndent(4);
        
        pWriter->printIndent();
        fprintf(pFile, "}\n");
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeMatGroupEnter(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    NodePtr pNode = pAction->getActNode();

    MaterialGroupPtr pMatGroup = 
        dynamic_cast<MaterialGroupPtr>(pNode->getCore());

    if(pWriter == NULL || pMatGroup == NullFC)
    {
        return Action::Quit;
    }

    FDEBUG(("Write MatGroup Enter 0x%04x\n", pWriter->getMode()));
    
    pWriter->setMaterial(pMatGroup->getMaterial());
    
    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeMatGroupLeave(NodeCorePtrConstArg , Action *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);
 

    if(pWriter == NULL)
    {
        return Action::Quit;
    }
    
    FDEBUG(("Write MatGroup Leave 0x%04x\n", pWriter->getMode()));
   
    pWriter->setMaterial(NullFC);
    
    return Action::Continue;
}


bool VRMLWriteAction::initializeAction(void)
{
    FINFO(( "Init VRMLWriter\n" ));

    VRMLWriteAction::registerEnterDefault( 
            Group::getClassType(), &VRMLWriteAction::writeGroupEnter);

    VRMLWriteAction::registerEnterDefault( 
            ComponentTransform::getClassType(),
            &VRMLWriteAction::writeComponentTransformEnter);
    
    VRMLWriteAction::registerEnterDefault( 
            Transform::getClassType(), &VRMLWriteAction::writeTransformEnter);
    
    VRMLWriteAction::registerEnterDefault( 
            Geometry::getClassType(), &VRMLWriteAction::writeGeoEnter);
    
    VRMLWriteAction::registerEnterDefault( 
            MaterialGroup::getClassType(), &VRMLWriteAction::writeMatGroupEnter);

    
    VRMLWriteAction::registerLeaveDefault( 
            Group::getClassType(), &VRMLWriteAction::writeGroupLeave);

    VRMLWriteAction::registerLeaveDefault( 
            ComponentTransform::getClassType(),
            &VRMLWriteAction::writeComponentTransformLeave);

    VRMLWriteAction::registerLeaveDefault( 
            Transform::getClassType(), &VRMLWriteAction::writeTransformLeave);
    
    VRMLWriteAction::registerLeaveDefault( 
            Geometry::getClassType(), &VRMLWriteAction::writeGeoLeave);
    
    VRMLWriteAction::registerLeaveDefault( 
            MaterialGroup::getClassType(), &VRMLWriteAction::writeMatGroupLeave);

    return true;
}

bool VRMLWriteAction::terminateAction(void)
{
    FINFO(( "Terminate VRMLWriter\n" ));

    delete _defaultEnterFunctors;
    delete _defaultLeaveFunctors;

    return true;
}


void VRMLWriteAction::incIndent(UInt32 uiDelta)
{
    if(0 == (_uiOptions & OSGNoIndent))
    {
        _uiIndent += uiDelta;
    }
}

void VRMLWriteAction::decIndent(UInt32 uiDelta)
{
    if(0 == (_uiOptions & OSGNoIndent))
    {
        _uiIndent -= uiDelta;
    }
}

void VRMLWriteAction::printIndent(void)
{
    if(_pFile != NULL)
    {
        for(UInt32 i = 0; i < _uiIndent/8; i++)
        {
            fprintf(_pFile, "\t");
        }
        for(UInt32 i = 0; i < _uiIndent%8; i++)
        {
            fprintf(_pFile, " ");
        }
    }
}

void VRMLWriteAction::setCurrentUse(bool bVal)
{
    _currentUse = bVal;
}

bool VRMLWriteAction::isCurrentUse(void)
{
    return _currentUse;
}

void VRMLWriteAction::addNodeUse(NodePtr &pNode)
{ 
    if(pNode == NullFC)
        return;

    NodeCorePtr pCore = pNode->getCore();

    if(_vFCInfos.find(getContainerId(pNode)) == _vFCInfos.end())
        _vFCInfos.insert(std::make_pair(getContainerId(pNode), new FCInfo));

    if(_vFCInfos.find(getContainerId(pCore)) == _vFCInfos.end())
        _vFCInfos.insert(std::make_pair(getContainerId(pCore), new FCInfo));

    FCInfo *pInfoNode = _vFCInfos[getContainerId(pNode)];
    FCInfo *pInfoCore = _vFCInfos[getContainerId(pCore)];

    NamePtr pNodename =
        dynamic_cast<NamePtr>(pNode->findAttachment(
            Name::getClassType().getGroupId()));

    NamePtr pCorename =
        dynamic_cast<NamePtr>(pCore->findAttachment(
            Name::getClassType().getGroupId()));

    pInfoNode->incUse();
    pInfoCore->incUse();

    if(pNodename != NullFC)
    {
        pInfoNode->setName(pNodename->getFieldPtr()->getValue().c_str());
    }

    if(pCorename != NullFC)
    {
        pInfoCore->setName(pCorename->getFieldPtr()->getValue().c_str());
    }

    if(pInfoCore->getUse() > 1)
    {
        if(pCorename != NullFC)
        {
            pInfoCore->buildName(pCore->getTypeName(), 
                                 getContainerId(pCore));
        }
    }

    ++_nodeCount;
}

void VRMLWriteAction::addContainerUse(FieldContainerPtr pContainer)
{
    if(pContainer == NullFC)
        return;

    if(_vFCInfos.find(getContainerId(pContainer)) == _vFCInfos.end())
        _vFCInfos.insert(std::make_pair(getContainerId(pContainer), new FCInfo));

    FCInfo *pInfo = _vFCInfos[getContainerId(pContainer)];

    pInfo->incUse();

    if(pInfo->getUse() > 1)
    {
        pInfo->buildName(pContainer->getTypeName(), 
                         getContainerId(pContainer));
    }
}

void VRMLWriteAction::clearInfos(void)
{
    for(FCInfosMap::iterator it = _vFCInfos.begin();it != _vFCInfos.end();++it)
        delete (*it).second;
    _vFCInfos.clear();
}

VRMLWriteAction::FCInfo *VRMLWriteAction::getInfo(
    FieldContainerPtr pContainer)
{
    if(pContainer == NullFC)
        return NULL;

    if(_vFCInfos.find(getContainerId(pContainer)) == _vFCInfos.end())
        return NULL;

    return _vFCInfos[getContainerId(pContainer)];
}

void VRMLWriteAction::updateProgress(void)
{
    if(_nodeCount > 0)
        SceneFileHandler::the()->updateWriteProgress((_currentNodeCount++ * 100) / _nodeCount);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLWriteAction::VRMLWriteAction(void) :
     Inherited       (            ),
    _material        (NullFC      ),
    _uiIndent        (0           ),
    _pFile           (NULL        ),
    _eTraversalMode  (OSGCollectFC),
    _currentUse      (false       ),
    _uiOptions       (OSGNoOptions),
    _vFCInfos        (            ),
    _writtenFCs      (            ),
    _nodeCount       (0           ),
    _currentNodeCount(0           )
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}


/** \brief Copy-Constructor
 */

VRMLWriteAction::VRMLWriteAction(const VRMLWriteAction &source) :
     Inherited       (source                  ),
    _material        (source._material        ),
    _uiIndent        (source._uiIndent        ),
    _pFile           (NULL                    ),
    _eTraversalMode  (source._eTraversalMode  ),
    _currentUse      (source._currentUse      ),
    _uiOptions       (source._uiOptions       ),
    _vFCInfos        (source._vFCInfos        ),
    _writtenFCs      (source._writtenFCs      ),
    _nodeCount       (source._nodeCount       ),
    _currentNodeCount(source._currentNodeCount)
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}

/** \brief create a new action
 */

VRMLWriteAction *VRMLWriteAction::create( void )
{
    VRMLWriteAction * act;
    
    if(_prototype)
        act = new VRMLWriteAction(*_prototype);
    else
        act = new VRMLWriteAction();
    
    return act;
}


/** \brief Destructor
 */

VRMLWriteAction::~VRMLWriteAction(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/
    
void VRMLWriteAction::setMaterial(MaterialPtr material)
{
    _material = material;
}

bool VRMLWriteAction::open(const Char8 *szFilename)
{
    if(szFilename != NULL)
    {
        _pFile = fopen(szFilename, "w");

        if(_pFile != NULL)
        {
            fprintf(_pFile, "#VRML V2.0 utf8 \n");
        }
    }

    return _pFile != NULL;
}

void VRMLWriteAction::close(void)
{
    if(_pFile != NULL)
    {
        fclose(_pFile);
    }
}

void VRMLWriteAction::addOptions(UInt32 uiOptions)
{
    _uiOptions |= uiOptions;
}

void VRMLWriteAction::subOptions(UInt32 uiOptions)
{
    _uiOptions &= ~uiOptions;
}

UInt32 VRMLWriteAction::getOptions(void)
{
    return _uiOptions;
}

Action::ResultE VRMLWriteAction::write(NodePtr node)
{
    Action::ResultE returnValue = Action::Continue;
    
    _eTraversalMode = OSGCollectFC;

    clearInfos();

    _writtenFCs.clear();
    
    setMaterial(NullFC);

    SceneFileHandler::the()->updateWriteProgress(0);
    _nodeCount = 0;
    _currentNodeCount = 0;

    returnValue = Inherited::apply(node);

    if(returnValue == Action::Continue)
    {
        _eTraversalMode = OSGWrite;
        returnValue = Inherited::apply(node);
    }

    SceneFileHandler::the()->updateReadProgress(100);

    clearInfos();

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*

DrawAction& DrawAction::operator = (const DrawAction &source)
{
    if (this == &source)
        return *this;

    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;

    // free mem alloced by members of 'this'

    // alloc new mem for members

    // copy 
}

*/

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

bool VRMLWriteAction::operator < (const VRMLWriteAction &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool VRMLWriteAction::operator == (
    const VRMLWriteAction &OSG_CHECK_ARG(other)) const
{
    return false;
}

/** \brief unequal
 */

bool VRMLWriteAction::operator != (const VRMLWriteAction &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


std::vector<VRMLWriteAction::Functor> *
    VRMLWriteAction::getDefaultEnterFunctors(void)
{
    return _defaultEnterFunctors;
}

std::vector<VRMLWriteAction::Functor> *
    VRMLWriteAction::getDefaultLeaveFunctors(void)
{
    return _defaultLeaveFunctors;
}

Action::ResultE VRMLWriteAction::apply(std::vector<NodePtr>::iterator begin, 
                                       std::vector<NodePtr>::iterator end)
{
    return Inherited::apply(begin, end);
}

Action::ResultE VRMLWriteAction::apply(NodePtr node)
{
    return Inherited::apply(node);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

