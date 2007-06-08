/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class HDRStageData!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldBundleType &HDRStageDataBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 HDRStageDataBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 HDRStageDataBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the HDRStageData::_sfToneMappingMaterial field.
inline
ChunkMaterialPtrConst HDRStageDataBase::getToneMappingMaterial(void) const
{
    return _sfToneMappingMaterial.getValue();
}

//! Set the value of the HDRStageData::_sfToneMappingMaterial field.
inline
void HDRStageDataBase::setToneMappingMaterial(ChunkMaterialPtrConstArg value)
{
    editSField(ToneMappingMaterialFieldMask);

    setRefd(_sfToneMappingMaterial.getValue(), value);

}

//! Get the value of the HDRStageData::_sfBlurRenderTarget field.
inline
FrameBufferObjectPtrConst HDRStageDataBase::getBlurRenderTarget(void) const
{
    return _sfBlurRenderTarget.getValue();
}

//! Set the value of the HDRStageData::_sfBlurRenderTarget field.
inline
void HDRStageDataBase::setBlurRenderTarget(FrameBufferObjectPtrConstArg value)
{
    editSField(BlurRenderTargetFieldMask);

    setRefd(_sfBlurRenderTarget.getValue(), value);

}

//! Get the value of the HDRStageData::_sfBlurMaterial field.
inline
ChunkMaterialPtrConst HDRStageDataBase::getBlurMaterial(void) const
{
    return _sfBlurMaterial.getValue();
}

//! Set the value of the HDRStageData::_sfBlurMaterial field.
inline
void HDRStageDataBase::setBlurMaterial(ChunkMaterialPtrConstArg value)
{
    editSField(BlurMaterialFieldMask);

    setRefd(_sfBlurMaterial.getValue(), value);

}

//! Get the value of the HDRStageData::_sfHBlurShader field.
inline
SHLChunkPtrConst HDRStageDataBase::getHBlurShader(void) const
{
    return _sfHBlurShader.getValue();
}

//! Set the value of the HDRStageData::_sfHBlurShader field.
inline
void HDRStageDataBase::setHBlurShader(SHLChunkPtrConstArg value)
{
    editSField(HBlurShaderFieldMask);

    setRefd(_sfHBlurShader.getValue(), value);

}

//! Get the value of the HDRStageData::_sfVBlurShader field.
inline
SHLChunkPtrConst HDRStageDataBase::getVBlurShader(void) const
{
    return _sfVBlurShader.getValue();
}

//! Set the value of the HDRStageData::_sfVBlurShader field.
inline
void HDRStageDataBase::setVBlurShader(SHLChunkPtrConstArg value)
{
    editSField(VBlurShaderFieldMask);

    setRefd(_sfVBlurShader.getValue(), value);

}
//! Get the value of the HDRStageData::_sfWidth field.

inline
UInt32 &HDRStageDataBase::editWidth(void)
{
    editSField(WidthFieldMask);

    return _sfWidth.getValue();
}

//! Get the value of the HDRStageData::_sfWidth field.
inline
const UInt32 &HDRStageDataBase::getWidth(void) const
{
    return _sfWidth.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
UInt32              &HDRStageDataBase::getWidth          (void)
{
    return this->editWidth          ();
}
#endif

//! Set the value of the HDRStageData::_sfWidth field.
inline
void HDRStageDataBase::setWidth(const UInt32 &value)
{
    editSField(WidthFieldMask);

    _sfWidth.setValue(value);
}
//! Get the value of the HDRStageData::_sfHeight field.

inline
UInt32 &HDRStageDataBase::editHeight(void)
{
    editSField(HeightFieldMask);

    return _sfHeight.getValue();
}

//! Get the value of the HDRStageData::_sfHeight field.
inline
const UInt32 &HDRStageDataBase::getHeight(void) const
{
    return _sfHeight.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
UInt32              &HDRStageDataBase::getHeight         (void)
{
    return this->editHeight         ();
}
#endif

//! Set the value of the HDRStageData::_sfHeight field.
inline
void HDRStageDataBase::setHeight(const UInt32 &value)
{
    editSField(HeightFieldMask);

    _sfHeight.setValue(value);
}

//! Get the value of the HDRStageData::_sfShrinkRenderTarget field.
inline
FrameBufferObjectPtrConst HDRStageDataBase::getShrinkRenderTarget(void) const
{
    return _sfShrinkRenderTarget.getValue();
}

//! Set the value of the HDRStageData::_sfShrinkRenderTarget field.
inline
void HDRStageDataBase::setShrinkRenderTarget(FrameBufferObjectPtrConstArg value)
{
    editSField(ShrinkRenderTargetFieldMask);

    setRefd(_sfShrinkRenderTarget.getValue(), value);

}

//! Get the value of the HDRStageData::_sfShrinkMaterial field.
inline
ChunkMaterialPtrConst HDRStageDataBase::getShrinkMaterial(void) const
{
    return _sfShrinkMaterial.getValue();
}

//! Set the value of the HDRStageData::_sfShrinkMaterial field.
inline
void HDRStageDataBase::setShrinkMaterial(ChunkMaterialPtrConstArg value)
{
    editSField(ShrinkMaterialFieldMask);

    setRefd(_sfShrinkMaterial.getValue(), value);

}

//! create a new instance of the class
inline
HDRStageDataP HDRStageDataBase::create(void)
{
    HDRStageDataP fc;

    if(getClassType().getPrototype() != NULL)
    {
        fc = dynamic_cast<HDRStageData::ObjPtr>(
            getClassType().getPrototype()-> shallowCopy());
    }

    return fc;
}



inline
Char8 *HDRStageDataBase::getClassname(void)
{
    return "HDRStageData";
}

typedef BundlePointerBuilder<
    HDRStageData>::ObjPtr          HDRStageDataP;

typedef BundlePointerBuilder<
    HDRStageData>::ObjPtrConst     HDRStageDataPConst;

typedef BundlePointerBuilder<
    HDRStageData>::ObjConstPtr     HDRStageDataConstP;

typedef BundlePointerBuilder<
    HDRStageData>::ObjPtrArg       HDRStageDataPArg;

typedef BundlePointerBuilder<
    HDRStageData>::ObjConstPtrArg  HDRStageDataConstPArg;

typedef BundlePointerBuilder<
    HDRStageData>::ObjPtrConstArg  HDRStageDataPConstArg;

OSG_END_NAMESPACE

