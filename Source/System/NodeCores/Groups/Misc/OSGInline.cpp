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

#include <cstdlib>
#include <cstdio>

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGInline.h"
#include "OSGSceneFileHandler.h"
#include "OSGOSGSceneFileType.h"
#include "OSGRenderAction.h"
#include "OSGGraphOpSeq.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGInlineBase.cpp file.
// To modify it, please change the .fcd file (OSGInline.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Inline::changed(ConstFieldMaskArg whichField, 
                     UInt32            origin,
                     BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Inline::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Inline NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Inline::Inline(void) :
    Inherited()
{
}

Inline::Inline(const Inline &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Inline::~Inline(void)
{
}


/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Inline::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        OSGSceneFileType::the().registerEndNodeCallback(
            Inline::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &Inline::postOSGLoading));

        RenderAction::registerEnterDefault(
            Inline::getClassType(),
            reinterpret_cast<Action::Callback>(&Inline::renderEnter));
    }
}
 
void Inline::postOSGLoading(void)
{
    UInt32 i = 0;

    for(; i < _mfUrl.size(); ++i)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _mfUrl[i].c_str());


        SceneFileHandler::the()->getPathHandler()->pushState();

        // could be a real url with a relative inline path.
        if(szFilenameResolved.empty() == true)
        {
            szFilenameResolved = _mfUrl[i];
        }

        SceneFileHandler::the()->getPathHandler()->setBaseFile(
            szFilenameResolved.c_str());

        std::string szFName = 
            SceneFileHandler::the()->getPathHandler()->extractFilename(
                _mfUrl[i].c_str());

        GraphOpSeqRefPtr pGraphOp = NULL;
        
        if(_sfGraphOp.getValue().compare("none") == 0)
        {
            // leave it NULL
        }
        else if(_sfGraphOp.getValue().compare("default") == 0)
        {
            pGraphOp = SceneFileHandler::the()->getDefaultGraphOp();
        }
        else
        {
            pGraphOp = GraphOpSeq::create(_sfGraphOp.getValue());
        }

        NodeUnrecPtr pFile = SceneFileHandler::the()->read(
            szFName.c_str(),
            pGraphOp,
            NULL,
            false);

        if(pFile == NULL)
        {
            pFile = SceneFileHandler::the()->read(
                szFilenameResolved.c_str(),
                pGraphOp,
                NULL,
                false);

            if(pFile == NULL)
            {
                pFile = SceneFileHandler::the()->read(
                    _mfUrl[i].c_str(),
                    pGraphOp,
                    NULL,
                    false);
            }
        }

        if(pFile != NULL)
        {
            pFile->addChangedFunctor(
                boost::bind(&Inline::rootChanged, this, _1, _2, _3),
                "");

            setRoot(pFile);

            SceneFileHandler::the()->getPathHandler()->popState();

            break;
        }
        else
        {
            SWARNING << "could not read " 
                     << _mfUrl[i] 
                     << std::endl;
        }

        SceneFileHandler::the()->getPathHandler()->popState();
    }

    if(i == _mfUrl.size() && _sfRoot.getValue() != NULL)
    {
        _sfRoot.getValue()->subChangedFunctor(
            boost::bind(&Inline::rootChanged, this, _1, _2, _3));

        setRoot(NULL);
    }
}

Action::ResultE Inline::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->useNodeList();
    
    if(a->isVisible(this->getRoot()))
        a->addNode(this->getRoot());

    return Action::Continue;
}

void Inline::adjustVolume(Volume &volume)
{
    if(getRoot() != NULL)
    {
        getRoot()->updateVolume();

        volume.extendBy(getRoot()->getVolume());
    }
}

void Inline::rootChanged(FieldContainer    *pFC,
                         ConstFieldMaskArg  whichField,
                         UInt32             origin    )
{
    if(0x0000 != (whichField & Node::VolumeFieldMask))
    {
        this->invalidateVolume();
    }
}

void Inline::resolveLinks(void)
{
    if(_sfRoot.getValue() != NULL)
    {
        _sfRoot.getValue()->subChangedFunctor(
            boost::bind(&Inline::rootChanged, this, _1, _2, _3));
    }

    Inherited::resolveLinks();
}
