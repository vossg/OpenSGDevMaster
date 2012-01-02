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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaMayaExtraHandler.h"
#include "OSGColladaLog.h"
#include "OSGColladaGeometry.h"
#include "OSGColladaTexture.h"

#ifdef OSG_WITH_COLLADA


OSG_BEGIN_NAMESPACE

ColladaExtraHandlerRegHelper ColladaMayaExtraHandler::_regHelper(
    &ColladaMayaExtraHandler::create);

ColladaExtraHandlerTransitPtr ColladaMayaExtraHandler::create(void)
{
    ColladaExtraHandlerTransitPtr returnValue(new ColladaMayaExtraHandler);

    return returnValue;
}

void ColladaMayaExtraHandler::readTextureExtraElements(
          ColladaTexture *texture,
    const domExtra       *extra  )
{
#if 0
    fprintf(stderr, "ColladaMayaExtraHandler::readTextureParams %p %p\n",
            texture,
            extra);
#endif

    const domTechnique_Array &extraTechniques = extra->getTechnique_array();

    for(UInt32 j = 0; j < extraTechniques.getCount(); ++j)
    {
        xsNMTOKEN extraProfile = extraTechniques[j]->getProfile();

#if 0
        fprintf(stderr, "Found extra profile %s\n",
                extraProfile);
#endif

        if(osgStringNCmp(extraProfile, "OpenCOLLADAMaya", 15) == 0)
        {
#if 0
            fprintf(stderr, "processing OpenCOLLADAMaya\n");
#endif

            const daeElementRefArray &profileElements = 
                extraTechniques[j]->getContents();

            Vec3f      t(0.f, 0.f, 0.f);
            Vec3f      s(1.f, 1.f, 1.f);
            Quaternion r(0.f, 0.f, 0.f, 1.f);

            bool       bMatrixModified = false;

            for(UInt32 k = 0; k < profileElements.getCount(); ++k)
            {
#if 0
                fprintf(stderr, "prElemName : %s | %s\n",
                        profileElements[k]->getElementName(),
                        profileElements[k]->getCharData().c_str());
#endif

                if(osgStringNCmp(profileElements[k]->getElementName(),
                                 "blend_mode",
                                 10                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "coverageU",
                                      9                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "coverageV",
                                      9                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "fast",
                                      4                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "mirrorU",
                                      7                                  ) == 0)
                {
                    UInt32 mirrorU = TypeTraits<UInt32>::getFromCString(
                            profileElements[k]->getCharData().c_str());

                    if(mirrorU == 1)
                    {
                        s[0] *= -1.f;
                    }

                    bMatrixModified = true;
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "mirrorV",
                                      7                                  ) == 0)
                {
                    UInt32 mirrorV = TypeTraits<UInt32>::getFromCString(
                            profileElements[k]->getCharData().c_str());

                    if(mirrorV == 1)
                    {
                        s[1] *= -1.f;
                    }

                    bMatrixModified = true;
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "noiseU",
                                      6                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "noiseV",
                                      6                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "offsetU",
                                      7                                  ) == 0)
                {
                    t[0] = TypeTraits<Real32>::getFromCString(
                               profileElements[k]->getCharData().c_str());

                    bMatrixModified = true;
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "offsetV",
                                      7                                  ) == 0)
                {
                    t[1] = TypeTraits<Real32>::getFromCString(
                               profileElements[k]->getCharData().c_str());

                    bMatrixModified = true;
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "repeatU",
                                      7                                  ) == 0)
                {
                    s[0] *= TypeTraits<Real32>::getFromCString(
                                profileElements[k]->getCharData().c_str());

                    bMatrixModified = true;
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "repeatV",
                                      7                                  ) == 0)
                {
                    s[1] *= TypeTraits<Real32>::getFromCString(
                                profileElements[k]->getCharData().c_str());

                    bMatrixModified = true;
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "rotateFrame",
                                      11                                 ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "rotateUV",
                                      8                                  ) == 0)
                {
                    r.setValueAsAxisDeg(
                        0.f, 1.f, 0.f,
                        TypeTraits<Real32>::getFromCString(
                            profileElements[k]->getCharData().c_str()));
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "stagger",
                                      7                                  ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "translateFrameU",
                                      15                                 ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "translateFrameV",
                                      15                                 ) == 0)
                {
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "wrapU",
                                      5                                  ) == 0)
                {
                    UInt32 wrapU = TypeTraits<UInt32>::getFromCString(
                            profileElements[k]->getCharData().c_str());

                    TextureObjChunk *pTex = texture->getTexture();

                    if(wrapU == 1)
                    {
                        pTex->setWrapS(GL_REPEAT);
                    }
                    else
                    {
                        pTex->setWrapS(GL_CLAMP_TO_BORDER);
                    }
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "wrapV",
                                      5                                  ) == 0)
                {
                    UInt32 wrapV = TypeTraits<UInt32>::getFromCString(
                            profileElements[k]->getCharData().c_str());

                    TextureObjChunk *pTex = texture->getTexture();

                    if(wrapV == 1)
                    {
                        pTex->setWrapT(GL_REPEAT);
                    }
                    else
                    {
                        pTex->setWrapT(GL_CLAMP_TO_BORDER);
                    }
                }
                else
                {
                    OSG_COLLADA_LOG(("ColladaMayaExtraHandler::readTexParam: "
                                     "unknown OpenColladaMaya parameter %s\n",
                                     profileElements[k]->getElementName()));
                }
            }

            if(bMatrixModified == true)
            {
                TextureTransformChunk *pTexTr = texture->editTexTransform();

                pTexTr->editMatrix().setTransform(t, r, s);
            }
        }
        else if(osgStringNCmp(extraProfile, "MAYA", 4) == 0)
        {
#if 0
            fprintf(stderr, "processing MAYA\n");
#endif

            const daeElementRefArray &profileElements = 
                extraTechniques[j]->getContents();

            for(UInt32 k = 0; k < profileElements.getCount(); ++k)
            {
#if 0
                fprintf(stderr, "prElemName : %s | %s\n",
                        profileElements[k]->getElementName(),
                        profileElements[k]->getCharData().c_str());
#endif

                if(osgStringNCmp(profileElements[k]->getElementName(),
                                 "wrapU",
                                 5                                  ) == 0)
                {
                    bool wrapU = TypeTraits<bool>::getFromCString(
                            profileElements[k]->getCharData().c_str());

                    TextureObjChunk *pTex = texture->getTexture();

                    if(wrapU == true)
                    {
                        pTex->setWrapS(GL_REPEAT);
                    }
                    else
                    {
                        pTex->setWrapS(GL_CLAMP_TO_BORDER);
                    }
                }
                else if(osgStringNCmp(profileElements[k]->getElementName(),
                                      "wrapV",
                                      5                                  ) == 0)
                {
                    bool wrapV = TypeTraits<bool>::getFromCString(
                            profileElements[k]->getCharData().c_str());

                    TextureObjChunk *pTex = texture->getTexture();

                    if(wrapV == true)
                    {
                        pTex->setWrapT(GL_REPEAT);
                    }
                    else
                    {
                        pTex->setWrapT(GL_CLAMP_TO_BORDER);
                    }
                }
                else
                {
                    OSG_COLLADA_LOG(("ColladaMayaExtraHandler::readTexParam:"
                                     "MAYA : unknown parameter %s\n",
                                     profileElements[k]->getElementName()));
                }
            }
        }
    }
}

void ColladaMayaExtraHandler::readTechniqueExtraElements(
          ColladaEffect *effect,
    const domExtra      *extra )
{
}

void ColladaMayaExtraHandler::readGeometryExtraElements(
          ColladaGeometry *geometry,
    const domExtra        *extra   )
{
#if 0
    fprintf(stderr, "ColladaMayaExtraHandler::readGeoExtraElems %p %p\n",
            geometry,
            extra);
#endif

    const domTechnique_Array &extraTechniques = extra->getTechnique_array();

    for(UInt32 j = 0; j < extraTechniques.getCount(); ++j)
    {
        xsNMTOKEN extraProfile = extraTechniques[j]->getProfile();

#if 0
        fprintf(stderr, "Found extra profile %s\n",
                extraProfile);
#endif

        if(osgStringNCmp(extraProfile, "OpenCOLLADAMaya", 15) == 0)
        {
#if 0
            fprintf(stderr, "processing\n");
#endif

            const daeElementRefArray &profileElements = 
                extraTechniques[j]->getContents();

            for(UInt32 k = 0; k < profileElements.getCount(); ++k)
            {
#if 0
                fprintf(stderr, "prElemName : %s | %s\n",
                        profileElements[k]->getElementName(),
                        profileElements[k]->getCharData().c_str());
#endif

                if(osgStringNCmp(profileElements[k]->getElementName(),
                                 "double_sided",
                                 12                                  ) == 0)
                {
                    bool doubleSided = 
                        TypeTraits<UInt32>::getFromCString(
                            profileElements[k]->getCharData().c_str()) != 0;

                    geometry->setDoubleSided(doubleSided);
                }
            }
        }
    }
}

ColladaMayaExtraHandler::ColladaMayaExtraHandler(void) :
    Inherited()
{
}

ColladaMayaExtraHandler::~ColladaMayaExtraHandler(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
