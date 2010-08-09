/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGMANIPULATORMANAGER_H_
#define _OSGMANIPULATORMANAGER_H_

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGNodeFields.h"

#include "OSGManipulator.h"
#include "OSGMoveManipulator.h"
#include "OSGRotateManipulator.h"
#include "OSGScaleManipulator.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBGUI_DLLMAPPING ManipulatorManager
{
 public:
    enum    ManipulatorType { ROTATE, SCALE, TRANSLATE };

     ManipulatorManager();
    ~ManipulatorManager();

    Node*           createManipulator(const ManipulatorType  type);
    void            changeManipulator(const ManipulatorType  type);
    ManipulatorType getCurrentType   (                           ) const;
    bool            activate         (      Node            *n   );
    
    void            setTarget        (      Node     * const value);
    void            setViewport      (      Viewport * const value);
    bool            isActive         (      void                  );
    
    void            mouseMove         (const Int16  x,
                                       const Int16  y);
    void            mouseButtonPress  (const UInt16 button,
                                       const Int16  x,
                                       const Int16  y     );
    void            mouseButtonRelease(const UInt16 button,
                                       const Int16  x,
                                       const Int16  y     );
private:

    NodeRefPtr         _maniN;
    ManipulatorType    _currentType;
    NodeRefPtr         _target;
    ViewportRefPtr     _viewport;
};

OSG_END_NAMESPACE

#endif // _OSGMANIPULATORMANAGER_H_
