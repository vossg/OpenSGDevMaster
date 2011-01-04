/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000-2002 by the OpenSG Forum               *
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


#ifndef _OSGIMAGEGENERICATT_H_
#define _OSGIMAGEGENERICATT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include <vector>
#include <string>

#include "OSGFieldContainer.h"
#include "OSGAttachment.h"
#include "OSGDynamicAttachmentMixin.h"
#include "OSGFieldContainerFieldTraits.h"

#include "OSGPointerSField.h"
#include "OSGPointerMField.h"

OSG_BEGIN_NAMESPACE

class FieldDescriptionBase;

/*! \ingroup GrpSystemImageHelper
    \nohierarchy 
 */

struct ImageGenericAttDesc
{
    typedef Attachment  Parent;
    typedef Attachment *ParentPtr;

    static const Char8 *getTypeName      (void) { return "ImageGenericAtt"; }
    static const Char8 *getParentTypeName(void) 
    {
        return "Attachment";      
    }
    static const Char8 *getGroupName     (void) { return "ImageGenAtt";     }

    static InitContainerF         getInitMethod(void) { return NULL; }

    static FieldDescriptionBase **getDesc      (void) { return NULL; }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemImageHelper
 */
typedef DynFieldAttachment<ImageGenericAttDesc>  ImageGenericAtt;
#else
/*! \ingroup GrpSystemImageHelper
 */
class ImageGenericAtt : public DynFieldAttachment<ImageGenericAttDesc> {};
#endif

/*! \ingroup GrpSystemImageHelper
 */

typedef RefCountPtr<ImageGenericAtt, 
                    UnrecordedRefCountPolicy>    ImageGenericAttUnrecPtr;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_IMAGEGENERICATT
#if defined(OSG_WIN32_CL) && _MSC_VER > 1300
OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment, 
                            ImageGenericAttDesc,
                            )
#else
OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment, 
                            ImageGenericAttDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */



/*! \ingroup GrpSystemImageFieldTraits
    \ingroup GrpLibOSGSystem
 */

template <>
struct FieldTraits<ImageGenericAtt *, 0> : 
    public FieldTraitsFCPtrBase<ImageGenericAtt *>
{
    static  DataType                        _type;
    typedef FieldTraits<ImageGenericAtt *>   Self;

    enum                            { Convertible = Self::NotConvertible };

    static       DataType &getType (void) { return _type;                      }

    template<typename RefCountPolicy> inline
    static const Char8    *getSName(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName(void);
};

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecImageGenericAttPtr"; 
}

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecImageGenericAttPtr"; 
}

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakImageGenericAttPtr"; 
}

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdImageGenericAttPtr"; 
}



template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecImageGenericAttPtr"; 
}

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecImageGenericAttPtr"; 
}

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakImageGenericAttPtr"; 
}

template<> inline
const Char8 *FieldTraits<
    ImageGenericAtt *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdImageGenericAttPtr"; 
}



#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup  GrpSystemImageFieldSFields */
typedef PointerSField<ImageGenericAtt *, 
                      RecordedRefCountPolicy  > SFRecImageGenericAtPtr;
/*! \ingroup  GrpSystemImageFieldSFields */
typedef PointerSField<ImageGenericAtt *, 
                      UnrecordedRefCountPolicy> SFUnrecImageGenericAtPtr;
/*! \ingroup  GrpSystemImageFieldSFields */
typedef PointerSField<ImageGenericAtt *, 
                      WeakRefCountPolicy      > SFWeakImageGenericAtPtr;
/*! \ingroup  GrpSystemImageFieldSFields */
typedef PointerSField<ImageGenericAtt *, 
                      NoRefCountPolicy        > SFUncountedImageGenericAtPtr;



/*! \ingroup  GrpSystemImageFieldMFields */
typedef PointerMField<ImageGenericAtt *, 
                      RecordedRefCountPolicy  > MFRecImageGenericAttPtr;
/*! \ingroup  GrpSystemImageFieldMFields */
typedef PointerMField<ImageGenericAtt *, 
                      UnrecordedRefCountPolicy> MFUnrecImageGenericAttPtr;
/*! \ingroup  GrpSystemImageFieldMFields */
typedef PointerMField<ImageGenericAtt *, 
                      WeakRefCountPolicy      > MFWeakImageGenericAttPtr;
/*! \ingroup  GrpSystemImageFieldMFields */
typedef PointerMField<ImageGenericAtt *, 
                      NoRefCountPolicy        > MFUncountedImageGenericAttPtr;
#else
/*! \ingroup  GrpSystemImageFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecImageGenericAtPtr :
    public PointerSField<ImageGenericAtt *, 
                         RecordedRefCountPolicy  > {};
/*! \ingroup  GrpSystemImageFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecImageGenericAtPtr : 
    public PointerSField<ImageGenericAtt *, 
                         UnrecordedRefCountPolicy> {};
/*! \ingroup  GrpSystemImageFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakImageGenericAtPtr : 
    public PointerSField<ImageGenericAtt *, 
                         WeakRefCountPolicy      > {};
/*! \ingroup  GrpSystemImageFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedImageGenericAtPtr :
    public PointerSField<ImageGenericAtt *, 
                         NoRefCountPolicy        > {};



/*! \ingroup  GrpSystemImageFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecImageGenericAttPtr : 
    public PointerMField<ImageGenericAtt *, 
                         RecordedRefCountPolicy  > {};
/*! \ingroup  GrpSystemImageFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecImageGenericAttPtr : 
    public PointerMField<ImageGenericAtt *, 
                         UnrecordedRefCountPolicy> {};
/*! \ingroup  GrpSystemImageFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakImageGenericAttPtr :
    public PointerMField<ImageGenericAtt *, 
                         WeakRefCountPolicy      > {};
/*! \ingroup  GrpSystemImageFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedImageGenericAttPtr : 
    public PointerMField<ImageGenericAtt *, 
                         NoRefCountPolicy        > {};
#endif


OSG_END_NAMESPACE

#endif /* _OSGIMAGEGENERICATT_H_ */


