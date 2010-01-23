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

OSG_BEGIN_NAMESPACE

inline const DAE *
ColladaGlobal::getDAE(void) const
{
    return _dae;
}

inline DAE *
ColladaGlobal::editDAE(void)
{
    return _dae;
}

inline domCOLLADA *
ColladaGlobal::getDocRoot(void) const
{
    return _docRoot;
}

inline const std::string &
ColladaGlobal::getDocPath(void) const
{
    return _docPath;
}

inline void
ColladaGlobal::setDocPath(const std::string &docPath)
{
    _docPath = docPath;
}

inline ColladaOptions *
ColladaGlobal::getOptions(void) const
{
    return _options;
}

inline void
ColladaGlobal::setOptions(ColladaOptions *options)
{
    _options = options;
}

inline Node *
ColladaGlobal::getRoot(void) const
{
    return _rootN;
}

inline void
ColladaGlobal::setRoot(Node *rootN)
{
    if(_rootN != NULL)
    {
        SWARNING << "ColladaGlobal::setRoot: Root already set. Overwriting."
                 << std::endl;
    }

    _rootN = rootN;
}

inline GlobalsAttachment *
ColladaGlobal::getGlobalsAtt(void) const
{
    return _globalsAtt;
}

inline void
ColladaGlobal::addLoaderState(
    const std::string &name, ColladaLoaderState *state)
{
    _loaderState[name] = state;
}

inline void
ColladaGlobal::subLoaderState(const std::string &name)
{
    LoaderStateMapIt sIt = _loaderState.find(name);

    if(sIt != _loaderState.end())
        _loaderState.erase(sIt);
}

inline ColladaLoaderState *
ColladaGlobal::getLoaderState(const std::string &name) const
{
    ColladaLoaderState    *retVal = NULL;
    LoaderStateMapConstIt  sIt    = _loaderState.find(name);

    if(sIt != _loaderState.end())
        retVal = sIt->second;

    return retVal;
}

template <class StateTypeT>
inline StateTypeT *
ColladaGlobal::getLoaderStateAs(const std::string &name) const
{
    return dynamic_cast<StateTypeT *>(getLoaderState(name));
}

inline const ColladaGlobal::InstanceQueue &
ColladaGlobal::getInstQueue(void) const
{
    return _instQueue;
}

inline ColladaGlobal::InstanceQueue &
ColladaGlobal::editInstQueue(void)
{
    return _instQueue;
}

inline const ColladaGlobal::ElementStore &
ColladaGlobal::getElemStore(void) const
{
    return _elemStore;
}

inline ColladaGlobal::ElementStore &
ColladaGlobal::editElemStore(void)
{
    return _elemStore;
}

OSG_END_NAMESPACE
