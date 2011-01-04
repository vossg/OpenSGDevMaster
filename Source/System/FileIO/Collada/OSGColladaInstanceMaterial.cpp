/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaInstanceMaterial.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaInstanceEffect.h"

#include <dom/domInstance_material.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceMaterial::_regHelper(
    &ColladaInstanceMaterial::create, "instance_material");

ColladaElementTransitPtr
ColladaInstanceMaterial::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceMaterial(elem, global));
}

void
ColladaInstanceMaterial::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceMaterial::read\n"));

    domInstance_materialRef instMat =
        getDOMElementAs<domInstance_material>();
    ColladaMaterialRefPtr   colMat  = getTargetElem();

    if(colMat == NULL)
    {
        colMat = dynamic_pointer_cast<ColladaMaterial>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colMat->read();
    }

    if(instMat->getSymbol() != NULL)
    {
        _symbol = instMat->getSymbol();
    }
    else
    {
        SFATAL << "ColladaInstanceMaterial::read: No symbol."
               << std::endl;
    }

    _target = instMat->getTarget().str();

    const domInstance_material::domBind_Array &binds   =
        instMat->getBind_array();

    _bindStore.resize(binds.getCount());

    for(UInt32 i = 0; i < binds.getCount(); ++i)
    {
        std::string target   = binds[i]->getTarget();
        std::string semantic;

        if(binds[i]->getSemantic() != NULL)
        {
            semantic = binds[i]->getSemantic();
        }

        OSG_COLLADA_LOG(("ColladaInstanceMaterial::read: "
                         "<bind> semantic [%s] target [%s]\n",
                         semantic.c_str(), target.c_str()));

        _bindStore[i].semantic = semantic;
        _bindStore[i].target   = target;
    }

    const domInstance_material::domBind_vertex_input_Array &bindVerts =
        instMat->getBind_vertex_input_array();

    _bindVertexStore.resize(bindVerts.getCount());

    for(UInt32 i = 0; i < bindVerts.getCount(); ++i)
    {
        std::string semantic   = bindVerts[i]->getSemantic      ();
        std::string inSemantic = bindVerts[i]->getInput_semantic();
        UInt32      inSet      = bindVerts[i]->getInput_set     ();

        OSG_COLLADA_LOG(("ColladaInstanceMaterial::read "
                         "<bind_vertex_input> semantic [%s] "
                         "inSemantic [%s] inSet [%d]\n",
                         semantic.c_str(), inSemantic.c_str(), inSet));

        _bindVertexStore[i].semantic   = semantic;
        _bindVertexStore[i].inSemantic = inSemantic;
        _bindVertexStore[i].inSet      = inSet;
    }
}

Material *
ColladaInstanceMaterial::process(ColladaElement *parent)
{
    ColladaMaterialRefPtr colMat = getTargetElem();

    return colMat->createInstance(this);
}

ColladaMaterial *
ColladaInstanceMaterial::getTargetElem(void) const
{
    ColladaMaterial *retVal     = NULL;
    domMaterialRef   targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaMaterial>(targetElem);
    }

    return retVal;
}

domMaterial *
ColladaInstanceMaterial::getTargetDOMElem(void) const
{
    domMaterialRef          retVal  = NULL;
    domInstance_materialRef instMat = getDOMElementAs<domInstance_material>();

    if(instMat->getTarget().getElement() != NULL)
    {
        retVal = daeSafeCast<domMaterial>(instMat->getTarget().getElement());
    }

    return retVal;
}

const std::string &
ColladaInstanceMaterial::getSymbol(void) const
{
    return _symbol;
}

const std::string &
ColladaInstanceMaterial::getTarget(void) const
{
    return _target;
}

const ColladaInstanceMaterial::BindStore &
ColladaInstanceMaterial::getBindStore(void) const
{
    return _bindStore;
}

const ColladaInstanceMaterial::BindInfo *
ColladaInstanceMaterial::findBindInfo(const std::string &semantic) const
{
    const BindInfo *retVal = NULL;

    for(UInt32 i = 0; i < _bindStore.size(); ++i)
    {
        if(_bindStore[i].semantic == semantic)
        {
            retVal = &_bindStore[i];
            break;
        }
    }

    return retVal;
}

const ColladaInstanceMaterial::BindVertexStore &
ColladaInstanceMaterial::getBindVertexStore(void) const
{
    return _bindVertexStore;
}

const ColladaInstanceMaterial::BindVertexInfo *
ColladaInstanceMaterial::findBindVertexInfo(
    const std::string &inSemantic, UInt32 inSet) const
{
    const BindVertexInfo *retVal = NULL;

    for(UInt32 i = 0; i < _bindVertexStore.size(); ++i)
    {
        if(_bindVertexStore[i].inSemantic == inSemantic &&
           _bindVertexStore[i].inSet      == inSet        )
        {
            retVal = &_bindVertexStore[i];
            break;
        }
    }

    return retVal;
}

ColladaInstanceEffect *
ColladaInstanceMaterial::getInstanceEffect(void) const
{
    domMaterialRef         material   = getTargetDOMElem            ();
    domInstance_effectRef  instEffect = material->getInstance_effect();

    return getUserDataAs<ColladaInstanceEffect>(instEffect);
}

ColladaInstanceMaterial::ColladaInstanceMaterial(
    daeElement *elem, ColladaGlobal *global)

    : Inherited       (elem, global)
    , _symbol         ()
    , _target         ()
    , _bindStore      ()
    , _bindVertexStore()
{
}

ColladaInstanceMaterial::~ColladaInstanceMaterial(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
