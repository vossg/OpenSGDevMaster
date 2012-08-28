/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

template <class ParentT, class ContainerT> inline
void FileContextHandlerMixin<ParentT, ContainerT>::initMethod(
    typename Inherited::InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == Inherited::TypeObject::SystemPost)
    {
#ifdef WIN32
        typedef OSGSceneFileType::PostLoadingDispatcher<
                  ContainerT> PLDOSGSceneItem;

        OSGSceneFileType::the().registerEndNodeCallback(
            ContainerT::getClassType(),
            boost::bind(&PLDOSGSceneItem::dispatch,
                        PLDOSGSceneItem(), _1, _2)); 
#else
        OSGSceneFileType::the().registerEndNodeCallback(
            ContainerT::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &ContainerT::postOSGLoading));
#endif
    }
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class ParentT, class ContainerT> inline
void FileContextHandlerMixin<ParentT, ContainerT>::postOSGLoading(
    FileContextAttachment * const pContext)
{
    if(pContext != NULL)
    {
#if 0
        fprintf(stderr, "file context: %p : %s\n",
                pContext,
                pContext->getResolvedName().c_str());
#endif

        this->addAttachment(pContext);
    }
    else
    {
        fprintf(stderr, "file context: NULL\n");
    }
}

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT, class ContainerT> inline
FileContextHandlerMixin<ParentT, ContainerT>::FileContextHandlerMixin(void) :
    Inherited()
{
}

template <class ParentT, class ContainerT> inline
FileContextHandlerMixin<ParentT, ContainerT>::FileContextHandlerMixin(
    const FileContextHandlerMixin &source) :

    Inherited(source)
{
}

template <class ParentT, class ContainerT> inline
FileContextHandlerMixin<ParentT, ContainerT>::~FileContextHandlerMixin(void)
{
}


/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

