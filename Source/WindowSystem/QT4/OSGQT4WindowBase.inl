/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class QT4Window!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &QT4WindowBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 QT4WindowBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 QT4WindowBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the QT4Window::_sfGlWidget field.

inline
OSGQGLWidgetP &QT4WindowBase::editGlWidget(void)
{
    editSField(GlWidgetFieldMask);

    return _sfGlWidget.getValue();
}

//! Get the value of the QT4Window::_sfGlWidget field.
inline
const OSGQGLWidgetP &QT4WindowBase::getGlWidget(void) const
{
    return _sfGlWidget.getValue();
}

//! Set the value of the QT4Window::_sfGlWidget field.
inline
void QT4WindowBase::setGlWidget(const OSGQGLWidgetP &value)
{
    editSField(GlWidgetFieldMask);

    _sfGlWidget.setValue(value);
}
//! Get the value of the QT4Window::_sfPrivateOSGContext field.

inline
bool &QT4WindowBase::editPrivateOSGContext(void)
{
    editSField(PrivateOSGContextFieldMask);

    return _sfPrivateOSGContext.getValue();
}

//! Get the value of the QT4Window::_sfPrivateOSGContext field.
inline
      bool  QT4WindowBase::getPrivateOSGContext(void) const
{
    return _sfPrivateOSGContext.getValue();
}

//! Set the value of the QT4Window::_sfPrivateOSGContext field.
inline
void QT4WindowBase::setPrivateOSGContext(const bool value)
{
    editSField(PrivateOSGContextFieldMask);

    _sfPrivateOSGContext.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void QT4WindowBase::execSync (      QT4WindowBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (GlWidgetFieldMask & whichField))
        _sfGlWidget.syncWith(pFrom->_sfGlWidget);

    if(FieldBits::NoField != (PrivateOSGContextFieldMask & whichField))
        _sfPrivateOSGContext.syncWith(pFrom->_sfPrivateOSGContext);
}
#endif


inline
const Char8 *QT4WindowBase::getClassname(void)
{
    return "QT4Window";
}
OSG_GEN_CONTAINERPTR(QT4Window);

OSG_END_NAMESPACE

