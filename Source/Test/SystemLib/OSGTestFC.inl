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

OSG_FIELD_CONTAINER_INL_DEF(TestFC)

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void TestFC::execSync(      TestFC            *pFrom,
                            ConstFieldMaskArg  whichField,
                            ConstFieldMaskArg  syncMode  ,
                      const UInt32             uiSyncInfo,
                            UInt32             uiCopyOffset)
{
    Inherited::execSync(pFrom, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (Field1FieldMask & whichField))
    {
        _mfField1.syncWith(pFrom->_mfField1, 
                           syncMode, 
                           uiSyncInfo, 
                           uiCopyOffset);
    }

    if(FieldBits::NoField != (Field2FieldMask & whichField))
    {
        _sfField2.syncWith(pFrom->_sfField2);
    }

    if(FieldBits::NoField != (Field3FieldMask & whichField))
    {
        _mfField3.syncWith(pFrom->_mfField3, 
                           syncMode, 
                           uiSyncInfo, 
                           uiCopyOffset);
    }
}
#endif
#ifdef OSG_MT_CPTR_ASPECT
inline
void TestFC::execSync (      TestFC            *pFrom,
                             ConstFieldMaskArg  whichField,
                             AspectOffsetStore &oOffsets,
                             ConstFieldMaskArg  syncMode  ,
                       const UInt32             uiSyncInfo)
{
    if(FieldBits::NoField != (Field1FieldMask & whichField))
    {
        _mfField1.syncWith(pFrom->_mfField1, 
                           syncMode, 
                           uiSyncInfo, 
                           oOffsets);
    }

    if(FieldBits::NoField != (Field2FieldMask & whichField))
    {
        _sfField2.syncWith(pFrom->_sfField2);
    }
}
#endif

#if 0
inline
void TestFC::execBeginEdit(ConstFieldMaskArg whichField, 
                           UInt32            uiAspect,
                           UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    fprintf(stderr, "TestFC::beginEdit %p 0x%016llx %u\n", 
            this, whichField, uiContainerSize);

    if(FieldBits::NoField != (Field1FieldMask & whichField))
    {
        _mfField1.beginEdit(uiAspect, uiContainerSize);
    }

    if(FieldBits::NoField != (Field3FieldMask & whichField))
    {
        _mfField3.beginEdit(uiAspect, uiContainerSize);
    }
}
#endif

inline
Char8 *TestFC::getClassname(void)
{
    return "TestFC";
}

OSG_END_NAMESPACE
