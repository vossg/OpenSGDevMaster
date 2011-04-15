/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#include "OSGOgreSkeletonReader.h"
#include "OSGOgreLog.h"

#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimTargetAttachment.h"
#include "OSGConceptPropertyChecks.h"
#include "OSGNameAttachment.h"
#include "OSGQuaternion.h"
#include "OSGSkeleton.h"
#include "OSGSkeletonOgreJoint.h"
#include "OSGVector.h"


OSG_BEGIN_NAMESPACE

const std::string OgreSkeletonReader::_versionString        ("[Serializer_v1.10]");
const std::size_t OgreSkeletonReader::_boneLengthNoScale    (_chunkHeaderSize + 1 * sizeof(UInt16) + 7 * sizeof(Real32));
const std::size_t OgreSkeletonReader::_keyFrameLengthNoScale(_chunkHeaderSize + 8 * sizeof(Real32));

/* explicit */
OgreSkeletonReader::OgreSkeletonReader(      std::istream &is, 
                                       const OgreOptions  &options)
    : Inherited(is),
      _options (options),
      _skel    (),
      _globals ()
{
}

/* virtual */
OgreSkeletonReader::~OgreSkeletonReader(void)
{
}

void
OgreSkeletonReader::read(void)
{
    OSG_OGRE_LOG(("OgreSkeletonReader::read\n"));

    UInt16 headerId = readUInt16(_is);

    if(headerId == CHUNK_HEADER)
    {
        std::string version = readString(_is);

        if(version == _versionString)
        {
            readContent();
        }
        else
        {
            SWARNING << "OgreSkeletonReader::read: Unsupported version '"
                     << version << "'." << std::endl;
        }
    }
    else
    {
        SWARNING << "OgreMeshReader::read: Unrecognized file heeader."
                 << std::endl;
    }
}

Skeleton*
OgreSkeletonReader::getSkeleton(void)
{
    return _skel;
}

GlobalsAttachment*
OgreSkeletonReader::getGlobals(void)
{
    return _globals;
}

void
OgreSkeletonReader::readContent(void)
{
    OSG_OGRE_LOG(("OgreSkeletonReader::readContent\n"));

    JointNodeStore joints;

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_BONE:
            readBone(joints);
            break;

        case CHUNK_BONE_PARENT:
            readBoneParent(joints);
            break;

        case CHUNK_ANIMATION:
            readAnimation(joints);
            break;

        case CHUNK_ANIMATION_LINK:
            readAnimationLink();
            break;

        default:
            OSG_OGRE_LOG(("OgreSkeletonReader::readContent: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        }

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }

    calcInvBindMatrices(joints);

    // construct skeleton
    _skel = Skeleton::create();
 
    JointNodeStore::const_iterator jIt  = joints.begin();
    JointNodeStore::const_iterator jEnd = joints.end  ();

    for(; jIt != jEnd; ++jIt)
    {
        if((*jIt) != NULL && (*jIt)->getParent() == NULL)
        {
#ifndef OSG_OGRE_SILENT
            SkeletonOgreJoint* joint =
                dynamic_cast<SkeletonOgreJoint*>((*jIt)->getCore());
#endif

            OSG_OGRE_LOG(("OgreSkeletonReader::readContent: "
                          "adding root joint id '%u'\n", joint->getJointId()));

            _skel->editMFRoots()->push_back(*jIt);
        }
    }
}

void
OgreSkeletonReader::readBone(JointNodeStore &joints)
{
    std::string boneName = readString(_is);
    UInt16      boneId   = readUInt16(_is);
    Vec3f       translate;
    Quaternion  rotate;
    Vec3f       scale(1.f, 1.f, 1.f);

    translate[0] = readReal32(_is);
    translate[1] = readReal32(_is);
    translate[2] = readReal32(_is);

    rotate[0]    = readReal32(_is);
    rotate[1]    = readReal32(_is);
    rotate[2]    = readReal32(_is);
    rotate[3]    = readReal32(_is);
    rotate.normalize();

    if(_header.chunkSize > _boneLengthNoScale)
    {
        scale[0] = readReal32(_is);
        scale[1] = readReal32(_is);
        scale[2] = readReal32(_is);
    }

    Vec3f  axis;
    Real32 angle;
    rotate.getValueAsAxisDeg(axis, angle);

    OSG_OGRE_LOG(("OgreSkeletonReader::readBone: boneName '%s' "
                  "boneId '%u' translate '(%f %f %f)' rotate '(%f %f %f %f)' "
                  "scale '(%f %f %f)'\n",
                  boneName.c_str(), boneId, translate[0], translate[1], translate[2],
                  axis[0], axis[1], axis[2], angle, scale[0], scale[1], scale[2]));

    SkeletonOgreJointUnrecPtr joint  = SkeletonOgreJoint::create();
    NodeUnrecPtr              jointN = makeNodeFor(joint);
    joint->setJointId(boneId);
    joint->setTranslate(translate);
    joint->setScale    (scale);
    joint->setRotate   (rotate);

    setTargetId(joint,  boneName);
    setName    (jointN, boneName);

    if(boneId >= joints.size())
        joints.resize(boneId + 1, NULL);

    joints[boneId] = jointN;
}

void
OgreSkeletonReader::readBoneParent(JointNodeStore &joints)
{
    UInt16 boneId   = readUInt16(_is);
    UInt16 parentId = readUInt16(_is);

    OSG_OGRE_LOG(("OgreSkeletonReader::readBoneParent: "
                  "boneId '%u' parentId '%u'\n", boneId, parentId));

    joints[parentId]->addChild(joints[boneId]);
}

void
OgreSkeletonReader::readAnimation(JointNodeStore &joints)
{
    if(_options.getLoadAnimations() == true)
    {
        std::string animName = readString(_is);
        Real32      animLen  = readReal32(_is);

        osgSinkUnusedWarning(animLen);

        OSG_OGRE_LOG(("OgreSkeletonReader::readAnimation: "
                      "animName '%s' animLen '%f'\n", animName.c_str(), animLen));

        AnimTemplateUnrecPtr animTmpl = AnimKeyFrameTemplate::create();
        animTmpl->setName(animName);

        bool stop = false;

        while(_is)
        {
            readChunkHeader(_is);

            switch(_header.chunkId)
            {
            case CHUNK_ANIMATION_TRACK:
                readAnimationTrack(joints, animTmpl);
                break;

            default:
                stop = true;
                break;
            }

            if(stop == true)
            {
                skip(_is, -_chunkHeaderSize);
                break;
            }
        }

        if(_globals == NULL)
            _globals = GlobalsAttachment::create();

        _globals->editMFElements()->push_back(animTmpl);
    }
    else
    {
        skip(_is, _header.chunkSize - _chunkHeaderSize);
    }
}

void
OgreSkeletonReader::readAnimationTrack(JointNodeStore &joints,
                                       AnimTemplate   *animTmpl)
{
    UInt16 boneId = readUInt16(_is);

    std::string boneName;
    getTargetId(joints[boneId]->getCore(), boneName);

    // OSG_OGRE_LOG(("OgreSkeletonReader::readAnimationTrack: boneId '%u' boneName '%s'\n",
    //               boneId, boneName.c_str()));

    AnimVec3fDataSourceUnrecPtr      translateSrc = AnimVec3fDataSource     ::create();
    AnimVec3fDataSourceUnrecPtr      scaleSrc     = AnimVec3fDataSource     ::create();
    AnimQuaternionDataSourceUnrecPtr rotateSrc    = AnimQuaternionDataSource::create();

    translateSrc->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);
    scaleSrc    ->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);
    rotateSrc   ->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_ANIMATION_TRACK_KEYFRAME:
            readAnimationTrackKeyFrame(translateSrc, scaleSrc, rotateSrc);
            break;

        default:
            stop = true;
            break;
        }

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }

    if(translateSrc->getMFInValues()->empty() == false)
    {
        animTmpl->editMFSources  ()->push_back(translateSrc);
        animTmpl->editMFTargetIds()->push_back(boneName + ".offsetTranslate");
    }

    if(scaleSrc->getMFInValues()->empty() == false)
    {
        animTmpl->editMFSources  ()->push_back(scaleSrc);
        animTmpl->editMFTargetIds()->push_back(boneName + ".offsetScale");
    }

    if(rotateSrc->getMFInValues()->empty() == false)
    {
        animTmpl->editMFSources  ()->push_back(rotateSrc);
        animTmpl->editMFTargetIds()->push_back(boneName + ".offsetRotate");
    }
}

void
OgreSkeletonReader::readAnimationTrackKeyFrame(AnimVec3fDataSource      *translateSrc,
                                               AnimVec3fDataSource      *scaleSrc,
                                               AnimQuaternionDataSource *rotateSrc    )
{
    Real32      time = readReal32(_is);
    Vec3f       translate;
    Quaternion  rotate;
    Vec3f       scale(1.f, 1.f, 1.f);
    bool        hasScale = false;

    rotate[0]    = readReal32(_is);
    rotate[1]    = readReal32(_is);
    rotate[2]    = readReal32(_is);
    rotate[3]    = readReal32(_is);
    rotate.normalize();

    translate[0] = readReal32(_is);
    translate[1] = readReal32(_is);
    translate[2] = readReal32(_is);

    if(_header.chunkSize > _keyFrameLengthNoScale)
    {
        hasScale = true;

        scale[0] = readReal32(_is);
        scale[1] = readReal32(_is);
        scale[2] = readReal32(_is);
    }

    Vec3f  axis;
    Real32 angle;
    rotate.getValueAsAxisDeg(axis, angle);

    // OSG_OGRE_LOG(("OgreSkeletonReader::readAnimationTrackKeyFrame: "
    //               "time '%f' rotate '(%f %f %f %f)' translate '(%f %f %f)' "
    //               "scale '(%f %f %f)'\n",
    //               time, axis[0], axis[1], axis[2], angle,
    //               translate[0], translate[1], translate[2],
    //               scale[0], scale[1], scale[2]));

    translateSrc->editMFInValues()->push_back(time);
    translateSrc->editMFValues  ()->push_back(translate);

    if(hasScale == true)
    {
        scaleSrc    ->editMFInValues()->push_back(time);
        scaleSrc    ->editMFValues  ()->push_back(scale);
    }

    rotateSrc   ->editMFInValues()->push_back(time);
    rotateSrc   ->editMFValues  ()->push_back(rotate);
}

void
OgreSkeletonReader::readAnimationLink(void)
{
    std::string skelName = readString(_is);
    Real32      scale    = readReal32(_is);

    osgSinkUnusedWarning(skelName);
    osgSinkUnusedWarning(scale);

    OSG_OGRE_LOG(("OgreSkeletonReader::readAnimationLink "
                  "skelName '%s' scale '%f'\n", skelName.c_str(), scale));
}

void
OgreSkeletonReader::calcInvBindMatrices(JointNodeStore &joints)
{
    OSG_OGRE_LOG(("OgreSkeletonReader::calcInvBindMatrices\n"));

    JointNodeStore::iterator jIt  = joints.begin();
    JointNodeStore::iterator jEnd = joints.end  ();

    for(; jIt != jEnd; ++jIt)
    {
        if((*jIt) != NULL && (*jIt)->getParent() == NULL)
        {
            calcInvBindMatrix(*jIt, Vec3f(0.f, 0.f, 0.f),
                                    Vec3f(1.f, 1.f, 1.f),
                                    Quaternion::identity());
        }
    }
}

void
OgreSkeletonReader::calcInvBindMatrix(Node      *node,
                                      Vec3f      parentTranslate,
                                      Vec3f      parentScale,
                                      Quaternion parentRotate)
{
    SkeletonOgreJoint *joint = dynamic_cast<SkeletonOgreJoint *>(node->getCore());

    Quaternion rotate(parentRotate);
    Vec3f      scale (parentScale );
    Vec3f      translate;

    if(joint != NULL)
    {
        rotate.mult(joint->getRotate());

        scale[0] *= joint->getScale()[0];
        scale[1] *= joint->getScale()[1];
        scale[2] *= joint->getScale()[2];

        translate = joint->getTranslate();
        translate[0] *= parentScale[0];
        translate[1] *= parentScale[1];
        translate[2] *= parentScale[2];

        parentRotate.multVec(translate, translate);

        translate += parentTranslate;

        joint->setInvBindTranslate(-translate);
        joint->setInvBindScale    (Vec3f(1.f/scale[0], 1.f/scale[1], 1.f/scale[2]));
        joint->setInvBindRotate   (rotate.inverse());

        Vec3f  axis;
        Real32 angle;
        joint->getInvBindRotate().getValueAsAxisDeg(axis, angle);
    }

    Node::MFChildrenType::const_iterator cIt  = node->getMFChildren()->begin();
    Node::MFChildrenType::const_iterator cEnd = node->getMFChildren()->end  ();

    for(; cIt != cEnd; ++cIt)
    {
        calcInvBindMatrix(*cIt, translate, scale, rotate);
    }
}

OSG_END_NAMESPACE
