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

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
FrameTaskMixin<ParentT>::FrameTaskMixin(void) :
    Inherited()
{
}

template <class ParentT> inline
FrameTaskMixin<ParentT>::FrameTaskMixin(const FrameTaskMixin &source) :

    Inherited(source)
{
}

template <class ParentT> inline
FrameTaskMixin<ParentT>::~FrameTaskMixin(void)
{
}

template <class ParentT> inline
void FrameTaskMixin<ParentT>::dump(      UInt32    uiIndent,
                                   const BitVector bvFlags ) const
{
}

template <class ParentT> inline
void FrameTaskMixin<ParentT>::onCreate (const FrameTaskMixin *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running || FrameHandler::the() == NULL)
        return;

    FrameHandler::the()->addTask(this);
}

template <class ParentT> inline
void FrameTaskMixin<ParentT>::onDestroy(UInt32 uiContainerId)
{
    // Don't add the prototype instances to the list
    if(GlobalSystemState < Shutdown && FrameHandler::the() != NULL)
    {
        FrameHandler::the()->removeTask(this);
    }

    Inherited::onDestroy(uiContainerId);
}


/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

