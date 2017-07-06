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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline 
UInt32 MultiLightChunk::numLights() const
{
    return static_cast<UInt32>(_mfPosition.size());
}

inline
const Pnt3f& MultiLightChunk::getPosition(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfPosition.size());
    return Inherited::getPosition(idx);
}

inline
const Vec3f& MultiLightChunk::getDirection(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfDirection.size());
    return Inherited::getDirection(idx);
}

inline
const Color3f& MultiLightChunk::getColor(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfColor.size());
    return Inherited::getColor(idx);
}

inline
Real32 MultiLightChunk::getIntensity(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfIntensity.size());
    return Inherited::getIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getAmbientIntensity(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfAmbientIntensity.size());
    return Inherited::getAmbientIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getDiffuseIntensity(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfDiffuseIntensity.size());
    return Inherited::getDiffuseIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getSpecularIntensity(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSpecularIntensity.size());
    return Inherited::getSpecularIntensity(idx);
}

inline
const Vec3f& MultiLightChunk::getAttenuation(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfAttenuation.size());
    return Inherited::getAttenuation(idx);
}

inline
Real32 MultiLightChunk::getRange(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    return Inherited::getRangeCutOff(idx);
}

inline
Real32 MultiLightChunk::getSpotlightAngle(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSpotlightAngle.size());
    return Inherited::getSpotlightAngle(idx);
}

inline
Real32 MultiLightChunk::getSpotExponent(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSpotExponent.size());
    return Inherited::getSpotExponent(idx);
}

inline
Real32 MultiLightChunk::getInnerSuperEllipsesWidth(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesWidth.size());
    return Inherited::getInnerSuperEllipsesWidth(idx);
}

inline
Real32 MultiLightChunk::getInnerSuperEllipsesHeight(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesHeight.size());
    return Inherited::getInnerSuperEllipsesHeight(idx);
}

inline
Real32 MultiLightChunk::getOuterSuperEllipsesWidth(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesWidth.size());
    return Inherited::getOuterSuperEllipsesWidth(idx);
}

inline
Real32 MultiLightChunk::getOuterSuperEllipsesHeight(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesHeight.size());
    return Inherited::getOuterSuperEllipsesHeight(idx);
}

inline
Real32 MultiLightChunk::getSuperEllipsesRoundness(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSuperEllipsesRoundness.size());
    return Inherited::getSuperEllipsesRoundness(idx);
}

inline
Real32 MultiLightChunk::getSuperEllipsesTwist(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfSuperEllipsesTwist.size());
    return Inherited::getSuperEllipsesTwist(idx);
}

inline
Real32 MultiLightChunk::getRangeCutOn(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeCutOn.size());
    return Inherited::getRangeCutOn(idx);
}

inline
Real32 MultiLightChunk::getRangeCutOff(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    return Inherited::getRangeCutOff(idx);
}

inline
Real32 MultiLightChunk::getRangeNearZone(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeNearZone.size());
    return Inherited::getRangeNearZone(idx);
}

inline
Real32 MultiLightChunk::getRangeFarZone(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfRangeFarZone.size());
    return Inherited::getRangeFarZone(idx);
}

inline
UInt8 MultiLightChunk::getType(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfType.size());
    return Inherited::getType(idx);
}

inline
bool MultiLightChunk::getEnabled(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfEnabled.size());
    return Inherited::getEnabled(idx);
}

inline
Node* MultiLightChunk::getBeacon(const UInt32 idx) const
{
    OSG_ASSERT(idx < _mfBeacon.size());
    return Inherited::getBeacon(idx);
}

inline
void MultiLightChunk::setPosition(const UInt32 idx, const Pnt3f& position)
{
    OSG_ASSERT(idx < _mfPosition.size());
    editPosition(idx) = position;
}

inline
void MultiLightChunk::setDirection(const UInt32 idx, const Vec3f& direction)
{
    OSG_ASSERT(idx < _mfDirection.size());
    editDirection(idx) = direction;
}

inline
void MultiLightChunk::setColor(const UInt32 idx, const Color3f& color)
{
    OSG_ASSERT(idx < _mfColor.size());
    editColor(idx) = color;
}

inline
void MultiLightChunk::setIntensity(const UInt32 idx, Real32 intensity)
{
    OSG_ASSERT(idx < _mfIntensity.size());
    editIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setAmbientIntensity(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfAmbientIntensity.size());
    editAmbientIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setDiffuseIntensity(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfDiffuseIntensity.size());
    editDiffuseIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setSpecularIntensity(const UInt32 idx, const Vec3f& intensity)
{
    OSG_ASSERT(idx < _mfSpecularIntensity.size());
    editSpecularIntensity(idx) = intensity;
}

inline
void MultiLightChunk::setAttenuation(const UInt32 idx, const Vec3f& attenuation)
{
    OSG_ASSERT(idx < _mfAttenuation.size());
    editAttenuation(idx) = attenuation;
}

inline
void MultiLightChunk::setRange(const UInt32 idx, Real32 range)
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    editRangeCutOff(idx) = range;
}

inline
void MultiLightChunk::setSpotlightAngle(const UInt32 idx, Real32 angle)
{
    OSG_ASSERT(idx < _mfSpotlightAngle.size());
    editSpotlightAngle(idx) = angle;
}

inline
void MultiLightChunk::setSpotExponent(const UInt32 idx, Real32 exponent)
{
    OSG_ASSERT(idx < _mfSpotExponent.size());
    editSpotExponent(idx) = exponent;
}

inline
void MultiLightChunk::setInnerSuperEllipsesWidth(const UInt32 idx, Real32 width)
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesWidth.size());
    editInnerSuperEllipsesWidth(idx) = width;
}

inline
void MultiLightChunk::setInnerSuperEllipsesHeight(const UInt32 idx, Real32 height)
{
    OSG_ASSERT(idx < _mfInnerSuperEllipsesHeight.size());
    editInnerSuperEllipsesHeight(idx) = height;
}

inline
void MultiLightChunk::setOuterSuperEllipsesWidth(const UInt32 idx, Real32 width)
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesWidth.size());
    editOuterSuperEllipsesWidth(idx) = width;
}

inline
void MultiLightChunk::setOuterSuperEllipsesHeight(const UInt32 idx, Real32 height)
{
    OSG_ASSERT(idx < _mfOuterSuperEllipsesHeight.size());
    editOuterSuperEllipsesHeight(idx) = height;
}

inline
void MultiLightChunk::setSuperEllipsesRoundness(const UInt32 idx, Real32 roundness)
{
    OSG_ASSERT(idx < _mfSuperEllipsesRoundness.size());
    editSuperEllipsesRoundness(idx) = roundness;
}

inline
void MultiLightChunk::setSuperEllipsesTwist(const UInt32 idx, Real32 twist)
{
    OSG_ASSERT(idx < _mfSuperEllipsesTwist.size());
    editSuperEllipsesTwist(idx) = twist;
}

inline
void MultiLightChunk::setRangeCutOn(const UInt32 idx, Real32 cutOn)
{
    OSG_ASSERT(idx < _mfRangeCutOn.size());
    editRangeCutOn(idx) = cutOn;
}

inline
void MultiLightChunk::setRangeCutOff(const UInt32 idx, Real32 cutOff)
{
    OSG_ASSERT(idx < _mfRangeCutOff.size());
    editRangeCutOff(idx) = cutOff;
}

inline
void MultiLightChunk::setRangeNearZone(const UInt32 idx, Real32 nearZone)
{
    OSG_ASSERT(idx < _mfRangeNearZone.size());
    editRangeNearZone(idx) = nearZone;
}

inline
void MultiLightChunk::setRangeFarZone(const UInt32 idx, Real32 farZone)
{
    OSG_ASSERT(idx < _mfRangeFarZone.size());
    editRangeFarZone(idx) = farZone;
}

inline
void MultiLightChunk::setType(const UInt32 idx, MultiLight::Type eType)
{
    OSG_ASSERT(idx < _mfType.size());
    editType(idx) = eType;
}

inline
void MultiLightChunk::setEnabled(const UInt32 idx, bool flag)
{
    OSG_ASSERT(idx < _mfEnabled.size());
    editEnabled(idx) = flag;
}

inline
void MultiLightChunk::setBeacon(const UInt32 idx, Node* const beacon)
{
    OSG_ASSERT(idx < _mfBeacon.size());

    editMField(BeaconFieldMask, _mfBeacon);
    _mfBeacon.replace(idx, beacon);
}

inline
void MultiLightChunk::changedBeacon()
{
    editMField(BeaconFieldMask, _mfBeacon);
}

inline
bool MultiLightChunk::check_invariant() const
{
    std::size_t sz = _mfPosition.size();

    if (getHasSeparateIntensities()
      && (
        sz != _mfAmbientIntensity.size() ||
        sz != _mfDiffuseIntensity.size() ||
        sz != _mfSpecularIntensity.size()))
        return false;

    if (getHasColor() && sz != _mfColor.size())
        return false;

    if (getHasIntensity() && sz != _mfIntensity.size())
        return false;

    if (getHasAttenuation() && sz != _mfAttenuation.size())
        return false;

    if (getHasRangeCutOn() && sz != _mfRangeCutOn.size())
        return false;

    if (getHasRangeCutOff() && sz != _mfRangeCutOff.size())
        return false;

    if (getHasRangeNearZone() && sz != _mfRangeNearZone.size())
        return false;

    if (getHasRangeFarZone() && sz != _mfRangeFarZone.size())
        return false;

    if (getHasSpotExponent() && sz != _mfSpotExponent.size())
        return false;

    if (getHasCinemaLight()
      && (
        sz != _mfInnerSuperEllipsesWidth.size() ||
        sz != _mfInnerSuperEllipsesHeight.size() ||
        sz != _mfOuterSuperEllipsesWidth.size() ||
        sz != _mfOuterSuperEllipsesHeight.size() ||
        sz != _mfSuperEllipsesRoundness.size() ||
        sz != _mfSuperEllipsesTwist.size()))
        return false;

    return sz == _mfDirection.size() 
        && sz == _mfSpotlightAngle.size() 
        && sz == _mfType.size() 
        && sz == _mfEnabled.size() 
        && sz == _mfBeacon.size();
}

OSG_END_NAMESPACE
