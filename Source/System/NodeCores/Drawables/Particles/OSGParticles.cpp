/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGGLEXT.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGMaterial.h"
//#include "OSGGeoPropPtrs.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"

#include "OSGParticles.h"
#include "OSGDrawableStatsAttachment.h"

#include <algorithm>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGParticlesBase.cpp file.
// To modify it, please change the .fcd file (OSGParticles.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           File variables                                *
\***************************************************************************/

static UInt32 _extMultitexture           = Window::invalidExtensionID;

static UInt32 _funcglMultiTexCoord3fvARB = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Particles::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            Particles::getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionEnterHandler));

        RenderAction::registerLeaveDefault(
            Particles::getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionLeaveHandler));

        _extMultitexture            =
            Window::registerExtension("GL_ARB_multitexture");

        _funcglMultiTexCoord3fvARB =
            Window::registerFunction(
                OSG_DLSYM_UNDERSCORE"glMultiTexCoord3fvARB", _extMultitexture);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

Particles::Particles(void) :
    Inherited()
{
}

Particles::Particles(const Particles &source) :
    Inherited(source)
{
}

Particles::~Particles(void)
{
}

/*------------------------------- Sync -----------------------------------*/

void Particles::changed(ConstFieldMaskArg whichField,
                        UInt32            origin,
                        BitVector         details)
{
    if(whichField & PositionsFieldMask)
    {
        for(UInt32 i = 0; i < _mfParents.size(); i++)
        {
            _mfParents[i]->invalidateVolume();
        }

        editBsp().destroy();
    }

    Inherited::changed(whichField, origin, details);
}

/*------------------------------ Output ----------------------------------*/

void Particles::dump(      UInt32    ,
                     const BitVector ) const
{
    SLOG << "Dump Particles NI" << std::endl;
}


void Particles::adjustVolume( Volume & volume )
{
    GeoVectorProperty *pos = getPositions();

    if ( pos == NULL )
        return;                 // Node has no particles, no volume

    volume.setValid();
    volume.setEmpty();

    const MFVec3f *sizes = getMFSizes();

    if(sizes->size() == pos->size())
    {
        Vec3f p;
        Real32 s;

        for(UInt32 i = 0; i < pos->size(); i++)
        {
            pos->getValue(p, i);
            // make the size bigger to accomodate rotations
            s=(*sizes)[i][0]*Sqrt2;

            p[0]+=s/2;
            p[1]+=s/2;
            p[2]+=s/2;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]-=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
            p[2]-=s;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]+=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
        }

    }
    else if(sizes->size() == 1)
    {
        Vec3f p;
        Real32 s,s2;
        // make the size bigger to accomodate rotations
        s=(*sizes)[0][0]*Sqrt2;
        s2=s/2;

        for(UInt32 i = 0; i < pos->size(); i++)
        {
            pos->getValue(p, i);

            p[0]+=s2;
            p[1]+=s2;
            p[2]+=s2;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]-=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
            p[2]-=s;
            volume.extendBy(p);
            p[0]-=s;
            volume.extendBy(p);
            p[1]+=s;
            volume.extendBy(p);
            p[0]+=s;
            volume.extendBy(p);
        }

    }
    else
    {
        Vec3f p;

        for(UInt32 i = 0; i < pos->getSize(); i++)
        {
            pos->getValue(p, i);

            volume.extendBy(p);
        }
    }
}

void Particles::fill(DrawableStatsAttachment *pStat)
{
    if(pStat == NULL)
    {
        FINFO(("Particles::fill(DrawableStatsAttachment *): "
                "No attachment given.\n"));
        return;
    }

    const GeoVectorProperty *positions = getPositions();
    const MFInt32           *indices   = getMFIndices();

    if(positions == NULL)
    {
        FINFO(("Particles::fill(DrawableStatsAttachment *): "
               "No positions.\n"));
        return;
    }

    UInt32 verts     = 0;
    UInt32 points    = 0;
    UInt32 lines     = 0;
    UInt32 triangles = 0;

    if(indices->size() > 0)
    {
        verts += indices->size();
    }
    else
    {
        verts += positions->size();
    }

    switch(getMode())
    {
    case Points:
    {
        points += verts;
        break;
    }

    case Lines:
    {
        lines += verts;
        break;
    }

    case ViewDirQuads:
    case ViewerQuads:
    case Rectangles:
    case ShaderQuads:
    {
        triangles += verts * 2;
        break;
    }

    case Arrows:
    case ViewerArrows:
    {
        triangles += verts * 5;
        break;
    }

    case ShaderStrips:
    {
        triangles += verts - 2;
        break;
    }

    default:
    {
        FWARNING(("Particles::fill(DrawableStatsAttachment *): "
                  "Invalid sfMode value.\n"));
        break;
    }
    }

    pStat->setVertices (verts    );
    pStat->setPoints   (points   );
    pStat->setLines    (lines    );
    pStat->setTriangles(triangles);
}

/*---------------------------- pumps -----------------------------------*/

/*! \name Drawing Pumps                                                 */
/*! \{                                                                  */

/*! The pumps use a trait system to create specialized code for important
    cases. The general idea is to keep decision out of the inner loops
    and make special versions for the most common data types. Not for
    everything, as that creates big time code bloat.
*/

/*! Base class for the particle rendering traits. Does nothing, just needed to
    have a common base class.
*/

/*! \ingroup GrpDrawablesParticlesHelpers
 */

class ParticleTraits
{
};

/*! Color trait base, keep the static data needed for color handling 
    \ingroup GrpDrawablesParticlesHelpers
 */

struct ColTraitBase : public ParticleTraits
{
    typedef void (OSG_APIENTRY *pumpFunc)( GLubyte * data );
    static const int formatBase;
    enum { numFormats = GL_DOUBLE - GL_BYTE + 1 };

    static const char *formatNames[];

    static pumpFunc ColorFuncs[numFormats][4];
};

/*! The smallest enum for data types, used as a base for the formatNames map.
*/
const int ColTraitBase::formatBase = GL_BYTE;

/*! A map from the OpenGL data type to the corresponding name
*/
const char *ColTraitBase::formatNames[] =
{   "GL_BYTE", "GL_UNSIGNED_BYTE", "GL_SHORT", "GL_UNSIGNED_SHORT",
    "GL_INT", "GL_UNSIGNED_INT", "GL_FLOAT", "GL_2_BYTES",
    "GL_3_BYTES", "GL_4_BYTES", "GL_DOUBLE"
};

/*! The pump functions for colors, indexed by data type and dimensionality
*/
ColTraitBase::pumpFunc
ColTraitBase::ColorFuncs[ColTraitBase::numFormats][4] = {
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3bv),
      reinterpret_cast<pumpFunc>(glColor4bv) },   // GL_BYTE
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3ubv),
      reinterpret_cast<pumpFunc>(glColor4ubv) },  // GL_UNSIGNED_BYTE
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3sv),
      reinterpret_cast<pumpFunc>(glColor4sv) },   // GL_SHORT
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3usv),
      reinterpret_cast<pumpFunc>(glColor4usv) },  // GL_UNSIGNED_SHORT
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3iv),
      reinterpret_cast<pumpFunc>(glColor4iv) },   // GL_INT
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3uiv),
      reinterpret_cast<pumpFunc>(glColor4uiv) },  // GL_UNSIGNED_INT
    { NULL,
      NULL,
      reinterpret_cast<pumpFunc>(glColor3fv),
      reinterpret_cast<pumpFunc>(glColor4fv) },   // GL_FLOAT
    { NULL, NULL, NULL, NULL },                   // GL_2_BYTES
    { NULL, NULL, NULL, NULL },                   // GL_3_BYTES
    { NULL, NULL, NULL, NULL },                   // GL_4_BYTES
    { NULL, NULL,
      reinterpret_cast<pumpFunc>(glColor3dv),
      reinterpret_cast<pumpFunc>(glColor4dv) },   // GL_DOUBLE
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */

struct ColTraitNone : public ColTraitBase
{
    typedef UInt8 dataType; // no data needed, but can't instantiate void

    static inline void init(Particles *, DrawEnv *, dataType &)
    {
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */

struct ColTraitSingle : public ColTraitBase
{
    typedef UInt8 dataType; // no data needed, but can't instantiate void

    static inline void init(Particles *part, DrawEnv *, dataType &)
    {
        GeoVectorProperty *col = part->getColors();

        if(col != NULL)
        {
            pumpFunc col_func;

            col_func = ColorFuncs[ col->getFormat() - formatBase ]
                                 [ col->getDimension() - 1 ];

            if(col_func == NULL)
            {
                SWARNING << "Particles " << part << "have illegal "
                         << "colors: " << col->getDimension()
                         << "D " << formatNames[col->getFormat() - formatBase]
                         << "!" << std::endl;
                return;
            }
            else
            {
                col_func(const_cast<GLubyte*>(col->getData()));
            }
        }
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */

struct ColTraitParticle : public ColTraitBase
{
    /*! \nohierarchy
     */
    typedef struct
    {
        const UInt8    *data;
              UInt32    stride;
              pumpFunc  func;
    }
    dataType;

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        GeoVectorProperty *col = part->getColors();

        data.data = col->getData();
        if((data.stride = col->getStride()) == 0)
            data.stride = col->getFormatSize() * col->getDimension();

        data.func = ColorFuncs[ col->getFormat() - formatBase ]
                              [ col->getDimension() - 1 ];

        if(data.func == NULL)
        {
            SWARNING << "Particles " << part << "have illegal "
                     << "colors: " << col->getDimension()
                     << "D " << formatNames[ col->getFormat() - formatBase ]
                     << "!" << std::endl;
            return;
        }
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        data.func(const_cast<GLubyte *>(data.data + particle * data.stride));

        return false;
    }

    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */

struct ColTraitGeneric : public ColTraitBase
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const UInt8    *data;
              UInt32    stride;
              pumpFunc  func;
              bool      perParticle;
    };

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        GeoVectorProperty *col = part->getColors();

        data.perParticle = false;

        if(col != NULL)
        {
            data.data = col->getData();
            if((data.stride = col->getStride()) == 0)
                data.stride = col->getFormatSize() * col->getDimension();

            data.func = ColorFuncs[ col->getFormat() - formatBase ]
                                  [ col->getDimension() - 1 ];

            if(data.func == NULL)
            {
                SWARNING << "Particles " << part << "have illegal "
                         << "colors: " << col->getDimension()
                         << "D " << formatNames[ col->getFormat() - formatBase ]
                         << "!" << std::endl;
                return;
            }

            if(col->getSize() == 1)
            {
                data.func(const_cast<GLubyte *>(col->getData()));
            }
            else if(col->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
        }
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        if(data.perParticle == true)
        {
            data.func(
                const_cast<GLubyte *>(data.data + particle * data.stride));
        }
        return false;
    }

    static inline void vertex(dataType &, UInt32, UInt32)
    {
    }
};

/*! Position Particle Traits 
    \ingroup GrpDrawablesParticlesHelpers
 */

struct PosTraitNone : public ParticleTraits
{
    /*! \nohierarchy
     */
    typedef struct
    {
    }
    dataType;

    static inline void init(Particles *, DrawEnv *, dataType &data,
        GeoVectorProperty *pos)
    {
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        return false;
    }

    static inline Pnt3f &position(dataType &data)
    {
        static Pnt3f null(0,0,0);
        return null;
    }

    static inline void vertex(dataType &data, UInt32 , Vec4f &dir,
                              Real32 s)
    {
    }

    static inline void vertex(dataType &data)
    {
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct PosTraitGeneric : public ParticleTraits
{
    /*! \nohierarchy
     */
    typedef struct
    {
        GeoVectorProperty *pos;
        Pnt3f              p;
    }
    dataType;

    static inline void init(Particles *, DrawEnv *, dataType &data,
        GeoVectorProperty *pos)
    {
        data.pos = pos;
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        data.pos->getValue(data.p, particle);

        return false;
    }

    static inline Pnt3f &position(dataType &data)
    {
        return data.p;
    }

    static inline void vertex(dataType &data, UInt32 , Vec4f &dir,
                              Real32 s)
    {
        glVertex3f( data.p[0] + dir[0] * s,
                    data.p[1] + dir[1] * s,
                    data.p[2] + dir[2] * s);
    }

    static inline void vertex(dataType &data)
    {
        glVertex3fv(static_cast<GLfloat *>(data.p.getValues()));
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct PosTrait3f : public ParticleTraits
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const MFPnt3f *pos;
        const Pnt3f   *p;
    };

    static inline void init(Particles         *,
                            DrawEnv           *,
                            dataType          &data,
                            GeoVectorProperty *pos)
    {
        GeoPnt3fProperty *pos3f = dynamic_cast<GeoPnt3fProperty *>(pos);

        data.pos  = pos3f->getFieldPtr();
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        data.p = & (*(data.pos))[particle];
        return false;
    }

    static inline const Pnt3f &position(dataType &data)
    {
        return *data.p;
    }

    static inline void vertex(dataType &data, UInt32 , Vec4f &dir, Real32 s)
    {
        glVertex3f( (*data.p)[0] + dir[0] * s,
                    (*data.p)[1] + dir[1] * s,
                    (*data.p)[2] + dir[2] * s);
    }

    static inline void vertex(dataType &data)
    {
        glVertex3fv(static_cast<const GLfloat *>((*data.p).getValues()));
    }
};

/*! Particle Size Traits 
    \ingroup GrpDrawablesParticlesHelpers
 */
struct SizeTraitGeneric : public ParticleTraits
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const MFVec3f *sizes;
              Vec3f    s;
              bool     perParticle;
    };

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.sizes = part->getMFSizes();

        if(data.sizes != NULL)
        {
            if(data.sizes->size() == 1)
            {
                data.s = (*(data.sizes))[0];
                data.perParticle = false;
            }
            else if(data.sizes->size() == part->getPositions()->size())
            {
                data.perParticle = true;
            }
            else
            {
                data.s.setValues(1,1,1);
                data.perParticle = false;
            }
        }
        else
        {
            data.s.setValues(1,1,1);
            data.perParticle = false;
        }
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline const Vec3f &size(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
                return (*(data.sizes))[particle];
        return data.s;
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct SizeTraitSingle : public ParticleTraits
{
    /*! \nohierarchy
     */
    typedef struct
    {
        Vec3f    s;
    }
    dataType;

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.s = (*part->getMFSizes())[0];
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline Vec3f &size(dataType &data, UInt32)
    {
        return data.s;
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct SizeTraitParticle : public ParticleTraits
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const MFVec3f *sizes;
              Vec3f    s;
    };

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.sizes = part->getMFSizes();
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline const Vec3f &size(dataType &data, UInt32 particle)
    {
        return (*(data.sizes))[particle];
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct SizeTraitNone : public ParticleTraits
{
    typedef UInt8 dataType;

    static inline void init(Particles *, DrawEnv *, dataType &)
    {
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline Vec3f &size(dataType &, UInt32 )
    {
        static Vec3f s(1,1,1);
        return s;
    }
};

/*! Particle Texture Traits 
   \ingroup GrpDrawablesParticlesHelpers
 */
struct TexTraitGeneric : public ParticleTraits
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const MFReal32 *texzs;
              Real32    z;
              bool      perParticle;
    };

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.texzs = part->getMFTextureZs();

        data.perParticle = false;

        if(data.texzs != NULL)
        {
            if(data.texzs->size() == 1)
            {
                data.z = (*(data.texzs))[0];
            }
            else if(data.texzs->size() == part->getPositions()->size())
            {
                data.perParticle = true;
                data.z = 0;
            }
            else
            {
                data.z = 0;
            }
        }
        else
        {
            data.z = 0;
        }
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
        {
            data.z = (*(data.texzs))[particle];
        }
        return false;
    }

    static inline void vertex(dataType &data)
    {
        glTexCoord1f(data.z);
    }

    static inline void vertex(dataType &data, UInt32 , Real32 u,
                                Real32 v)
    {
        glTexCoord3f(u, v, data.z);
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct TexTraitParticle : public ParticleTraits
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const MFReal32 *texzs;
              Real32    z;
    };

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.texzs = part->getMFTextureZs();
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        data.z = (*(data.texzs))[particle];
        return false;
    }

    static inline void vertex(dataType &data)
    {
        glTexCoord1f(data.z);
    }

    static inline void vertex(dataType &data, UInt32 , Real32 u,
                                Real32 v)
    {
        glTexCoord3f(u, v, data.z);
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct TexTraitSingle : public ParticleTraits
{
    /*! \nohierarchy
     */
    typedef struct
    {
        Real32    z;
    }
    dataType;

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.z = (*(part->getMFTextureZs()))[0];
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void vertex(dataType &data)
    {
        glTexCoord1f(data.z);
    }

    static inline void vertex(dataType &data, UInt32 , Real32 u,
                                Real32 v)
    {
        glTexCoord3f(u, v, data.z);
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct TexTraitNone : public ParticleTraits
{
    typedef UInt8 dataType;

    static inline void init(Particles *, DrawEnv *, dataType &)
    {
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void vertex(dataType &, UInt32 )
    {
        glTexCoord1f(0);
    }

    static inline void vertex(dataType &, UInt32, Real32 u, Real32 v)
    {
        glTexCoord2f(u, v);
    }
};


/*! Normal Particle Traits 
    \ingroup GrpDrawablesParticlesHelpers
 */
struct NormalTraitGeneric : public ParticleTraits
{
    /*! \nohierarchy
     */
    typedef struct
    {
        GeoVectorProperty *norms;
        Vec3f              n;
        bool               perParticle;
    }
    dataType;

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        data.norms = part->getNormals();

        data.perParticle = false;

        if(data.norms != NULL)
        {
            if(data.norms->size() == 1)
            {
                data.norms->getValue(data.n, 0);
            }
            else if(data.norms->getSize() == part->getPositions()->getSize())
            {
                data.perParticle = true;
            }
            else
            {
                data.n.setValues(0,1,0);
            }
        }
        else
        {
            data.n.setValues(0,1,0);
        }
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
            data.norms->getValue(data.n, particle);

        return false;
    }

    static inline Vec3f &normal(dataType &data)
    {
        return data.n;
    }

    static inline void normal(dataType &data, UInt32 )
    {
        glNormal3fv(static_cast<GLfloat *>(data.n.getValues()));
    }
};

/*! \ingroup GrpDrawablesParticlesHelpers
 */
struct NormalTraitGeneric3f : public ParticleTraits
{
    /*! \nohierarchy
     */
    struct dataType
    {
        const MFVec3f *norms;
        const Vec3f   *n;
              bool     perParticle;
              Vec3f    const_n;
    };

    static inline void init(Particles *part, DrawEnv *, dataType &data)
    {
        GeoVec3fProperty *norms3f =
            dynamic_cast<GeoVec3fProperty *>(part->getNormals());

        data.norms = norms3f->getFieldPtr();

        data.perParticle = false;

        if(norms3f != NULL)
        {
            if(norms3f->getSize() == 1)
            {
                data.n = &(*(data.norms))[0];
            }
            else if(data.norms->size() == part->getPositions()->size())
            {
                data.perParticle = true;
            }
            else
            {
                data.const_n.setValues(0,1,0);
                data.n = &data.const_n;
            }
        }
        else
        {
            data.const_n.setValues(0,1,0);
            data.n = &data.const_n;
        }
    }

    static inline bool particle(dataType &data, UInt32 particle)
    {
        if(data.perParticle)
            data.n = &(*(data.norms))[particle];

        return false;
    }

    static inline const Vec3f &normal(dataType &data)
    {
        return *data.n;
    }

    static inline void normal(dataType &data, UInt32 )
    {
        glNormal3fv(static_cast<const GLfloat *>(data.n->getValues()));
    }
};

/*! ParticlesDrawer base classes, define the common interface(s) 
    \ingroup GrpDrawablesParticlesHelpers
 */
struct ParticlesDrawer
{
    virtual void draw(Particles *part,
                      DrawEnv   *pEnv,
                      UInt32 length) = 0;

    virtual void drawIndexed(      Particles *part,
                                   DrawEnv   *pEnv,
                             const Int32     *index,
                                   UInt32     length) = 0;

    virtual ~ParticlesDrawer()
    {
    }
};

/*! View-Dir aligned, indexed quad rendering 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawViewDirQuads : public ParticlesDrawer
{
    virtual void drawIndexed(      Particles *part,
                                   DrawEnv   *pEnv,
                             const Int32     *index,
                                   UInt32     length)
    {
        // get ModelView matrix to define the direction vectors
        Matrix camera  = pEnv->getCameraToWorld();
        Matrix toworld = pEnv->getObjectToWorld();


/*
        DrawActionBase *action = pEnv->getOldAction();

        RenderAction *ra = dynamic_cast<RenderAction *>(action);

        if(ra != NULL)
        {
            toworld = ra->top_matrix();
        }
        else
        {
            action->getActNode()->getToWorld(toworld);
        }
 */

        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();
        toworld.transpose();
        camera.multLeft(toworld);

        // Direction vectors
        Vec4f  d1, d2, d3, d4;

        d1 = -1.0f * camera[0] + -1.0f * camera[1];
        d2 =  1.0f * camera[0] + -1.0f * camera[1];
        d3 =  1.0f * camera[0] +  1.0f * camera[1];
        d4 = -1.0f * camera[0] +  1.0f * camera[1];

        // some variables for faster access
        GeoVectorProperty *pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        glBegin(GL_QUADS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.f;

            if(s == 0)
                continue;

            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d1, s);

            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d2, s);

            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d3, s);

            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d4, s);
        }

        glEnd();
    }

    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        // get ModelView matrix to define the direction vectors

        Matrix camera  = pEnv->getCameraToWorld();
        Matrix toworld = pEnv->getObjectToWorld();

/*
        DrawActionBase *action = pEnv->getOldAction();

        RenderAction *ra = dynamic_cast<RenderAction *>(action);

        if(ra != NULL)
        {
            toworld = ra->top_matrix();
        }
        else
        {
            action->getActNode()->getToWorld(toworld);
        }
 */

        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();
        toworld.transpose();
        camera.multLeft(toworld);

        // Direction vectors
        Vec4f  d1, d2, d3, d4;

        d1 = -1.0f * camera[0] + -1.0f * camera[1];
        d2 =  1.0f * camera[0] + -1.0f * camera[1];
        d3 =  1.0f * camera[0] +  1.0f * camera[1];
        d4 = -1.0f * camera[0] +  1.0f * camera[1];

        // some variables for faster access

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        glBegin(GL_QUADS);

        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.f;

            if(s == 0)
                continue;

            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d1, s);

            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d2, s);

            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d3, s);

            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d4, s);
        }

        glEnd();
    }
};


/*! Viewer aligned, indexed quad rendering 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawViewerQuads : public ParticlesDrawer
{
    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        // get ModelView matrix to define the direction vectors
//        Matrix camera,toworld;

        Matrix camera  = pEnv->getCameraToWorld();
        Matrix toworld = pEnv->getObjectToWorld();

/*
        DrawActionBase *action = pEnv->getOldAction();

        RenderAction *ra = dynamic_cast<RenderAction *>(action);

        if(ra != NULL)
        {
            toworld = ra->top_matrix();
        }
        else
        {
            action->getActNode()->getToWorld(toworld);
        }
 */

        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();
        toworld.invert();
        camera.multLeft(toworld);

        // Viewer position & up
        Pnt3f  vpos(camera[3]);
        Vec3f  vup (camera[1]);
        vup.normalize();
        Vec3f  vdir,vnorm;

        // direction vector
        Vec4f d;

        // some variables for faster access
        GeoVectorProperty *pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        glBegin(GL_QUADS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.f;

            if(s == 0)
                continue;

            // calc viewer-relative coord system

            Pnt3f p = pos->getValue<Pnt3f>(i);
            vdir = vpos - p;
            vdir.normalize();
            vnorm = vup.cross(vdir);

            d.setValues( -vnorm[0] - vup[0],
                         -vnorm[1] - vup[1],
                         -vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d, s);

            d.setValues(  vnorm[0] - vup[0],
                          vnorm[1] - vup[1],
                          vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d, s);

            d.setValues(  vnorm[0] + vup[0],
                          vnorm[1] + vup[1],
                          vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d, s);

            d.setValues( -vnorm[0] + vup[0],
                         -vnorm[1] + vup[1],
                         -vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d, s);
        }

        glEnd();
    }

    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        // get ModelView matrix to define the direction vectors

        Matrix camera  = pEnv->getCameraToWorld();
        Matrix toworld = pEnv->getObjectToWorld();

/*
        DrawActionBase *action = pEnv->getOldAction();

        RenderAction *ra = dynamic_cast<RenderAction *>(action);

        if(ra != NULL)
        {
            toworld = ra->top_matrix();
        }
        else
        {
            action->getActNode()->getToWorld(toworld);
        }
 */

        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();
        toworld.invert();
        camera.multLeft(toworld);

        // Viewer position & up
        Pnt3f  vpos(camera[3]);
        Vec3f  vup (camera[1]);
        vup.normalize();
        Vec3f  vdir,vnorm;

        // direction vector
        Vec4f d;

        // some variables for faster access
        GeoVectorProperty *pos = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        glBegin(GL_QUADS);

        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            Real32 s = sizeTrait::size(sizeData, i)[0] / 2.f;

            if(s == 0)
                continue;

            // calc viewer-relative coord system

            Pnt3f p = pos->getValue<Pnt3f>(i);
            vdir = vpos - p;
            vdir.normalize();
            vnorm = vup.cross(vdir);

            d.setValues( -vnorm[0] - vup[0],
                         -vnorm[1] - vup[1],
                         -vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 0);
            texTrait::vertex(texData, 0, 0, 0);
            posTrait::vertex(posData, 0, d, s);

            d.setValues(  vnorm[0] - vup[0],
                          vnorm[1] - vup[1],
                          vnorm[2] - vup[2],
                         1 );
            colTrait::vertex(colData, i, 1);
            texTrait::vertex(texData, 1, 1, 0);
            posTrait::vertex(posData, 1, d, s);

            d.setValues(  vnorm[0] + vup[0],
                          vnorm[1] + vup[1],
                          vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 2);
            texTrait::vertex(texData, 2, 1, 1);
            posTrait::vertex(posData, 2, d, s);

            d.setValues( -vnorm[0] + vup[0],
                         -vnorm[1] + vup[1],
                         -vnorm[2] + vup[2],
                         1 );
            colTrait::vertex(colData, i, 3);
            texTrait::vertex(texData, 3, 0, 1);
            posTrait::vertex(posData, 3, d, s);
        }

        glEnd();
    }
};



/*! Single color lines between secPos and pos 
    \ingroup GrpDrawablesParticlesHelpers
 */


template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawLines : public ParticlesDrawer
{
    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        // some variables for faster access

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename posTrait::dataType secPosData;
        posTrait::init(part, pEnv, secPosData, part->getSecPositions());

        Real32 s = sizeTrait::size(sizeData, 0)[0];

        glPushAttrib(GL_LINE_BIT);
        glLineWidth(s);

        glBegin(GL_LINES);

        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(posTrait::particle(secPosData, i))
                continue;

            posTrait::vertex(posData);
            posTrait::vertex(secPosData);
        }

        glEnd();

        glPopAttrib();
    }

    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        // some variables for faster access
        GeoVectorProperty *pos  = part->getPositions();

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename posTrait::dataType secPosData;
        posTrait::init(part, pEnv, secPosData, part->getSecPositions());

        Real32 s = sizeTrait::size(sizeData, 0)[0];

        glPushAttrib(GL_LINE_BIT);
        glLineWidth(s);

        glBegin(GL_LINES);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle (texData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(posTrait::particle(secPosData, i))
                continue;

            posTrait::vertex(posData);
            posTrait::vertex(secPosData);
        }

        glEnd();

        glPopAttrib();
    }
};

/*! Points at pos 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class colTrait, class texTrait, class sizeTrait>
struct drawPoints : public ParticlesDrawer
{
    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        // some variables for faster access
        // init traits
        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        sizeTrait::particle(sizeData, 0);
        Real32 s = sizeTrait::size(sizeData, 0)[0];

        glPushAttrib(GL_POINT_BIT);
        glPointSize(s);

        glBegin(GL_POINTS);

        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle(colData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(texTrait::particle(texData, i))
                continue;

            texTrait::vertex(texData);
            posTrait::vertex(posData);
        }

        glEnd();

        glPopAttrib();
    }

    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        // some variables for faster access
        GeoVectorProperty *pos  = part->getPositions();

        // init traits
        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        sizeTrait::particle(sizeData, 0);
        Real32 s = sizeTrait::size(sizeData, 0)[0];

        glPushAttrib(GL_POINT_BIT);
        glPointSize(s);

        glBegin(GL_POINTS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(colTrait::particle(colData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            posTrait::vertex(posData);
        }

        glEnd();

        glPopAttrib();
    }
};

/*! Geometry traits for drawing objects 
    \ingroup GrpDrawablesParticlesHelpers
 */
struct GeoTraitArrow : public ParticleTraits
{
    typedef UInt8 dataType;

    static inline void init(Particles *, DrawEnv *, dataType &)
    {
    }

    static inline void exit(Particles *, DrawEnv *, dataType &)
    {
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void draw(      dataType &,
                            const Pnt3f    &p,
                            const Pnt3f    &,
                                  Vec3f    &dx,
                                  Vec3f    &dy,
                                  Vec3f    &dz,
                            const Vec3f    &s)
    {
        dz*=s[2];
        dx*=s[0];

        glNormal3fv(static_cast<GLfloat *>(dy.getValues()));

        glBegin(GL_TRIANGLE_FAN);

        glVertex3fv(static_cast<const GLfloat *>(p.getValues()));

        glVertex3f(p[0] + dz[0] * .5f + dx[0]      ,
                   p[1] + dz[1] * .5f + dx[1]      ,
                   p[2] + dz[2] * .5f + dx[2]      );

        glVertex3f(p[0] + dz[0] * .5f + dx[0] * .5f ,
                   p[1] + dz[1] * .5f + dx[1] * .5f ,
                   p[2] + dz[2] * .5f + dx[2] * .5f );

        glVertex3f(p[0] + dz[0]       + dx[0] * .5f ,
                   p[1] + dz[1]       + dx[1] * .5f ,
                   p[2] + dz[2]       + dx[2] * .5f );

        glVertex3f(p[0] + dz[0]       - dx[0] * .5f ,
                   p[1] + dz[1]       - dx[1] * .5f ,
                   p[2] + dz[2]       - dx[2] * .5f );

        glVertex3f(p[0] + dz[0] * .5f - dx[0] * .5f ,
                   p[1] + dz[1] * .5f - dx[1] * .5f ,
                   p[2] + dz[2] * .5f - dx[2] * .5f );

        glVertex3f(p[0] + dz[0] * .5f - dx[0]      ,
                   p[1] + dz[1] * .5f - dx[1]      ,
                   p[2] + dz[2] * .5f - dx[2]      );

        glEnd();
    }
};


/*! Geometry traits for drawing rectangles 
    \ingroup GrpDrawablesParticlesHelpers
 */

struct GeoTraitRectangle : public ParticleTraits
{
    typedef UInt8 dataType;

    static inline void init(Particles *, DrawEnv *, dataType &)
    {
        glBegin(GL_QUADS);
    }

    static inline void exit(Particles *, DrawEnv *, dataType &)
    {
        glEnd();
    }

    static inline bool particle(dataType &, UInt32)
    {
        return false;
    }

    static inline void draw(      dataType &,
                            const Pnt3f    &p,
                            const Pnt3f    &sp,
                                  Vec3f    &dx,
                                  Vec3f    &dy,
                                  Vec3f    &,
                            const Vec3f    &s)
    {
        dx *= s[0] * .5f;

        glNormal3fv(static_cast<GLfloat *>(dy.getValues()));

        glVertex3f( p[0] - dx[0],
                    p[1] - dx[1],
                    p[2] - dx[2]);

        glVertex3f( p[0] + dx[0],
                    p[1] + dx[1],
                    p[2] + dx[2]);

        glVertex3f(sp[0] + dx[0],
                   sp[1] + dx[1],
                   sp[2] + dx[2]);

        glVertex3f(sp[0] - dx[0],
                   sp[1] - dx[1],
                   sp[2] - dx[2]);
    }
};



/*! Objects using the pos/secpos/normal coordinate system for rendering 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class colTrait, class sizeTrait, class normalTrait,
          class geoTrait>
struct drawObjects : public ParticlesDrawer
{
    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        // some variables for faster access

        // init traits
        typename geoTrait::dataType geoData;
        geoTrait::init(part, pEnv, geoData);

        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, pEnv, normalData);

        typename posTrait::dataType posData, secPosData;
        posTrait::init(part, pEnv, posData   , part->getPositions());
        posTrait::init(part, pEnv, secPosData, part->getSecPositions());

        for(UInt32 i = 0; i < length; ++i)
        {
            if(geoTrait::particle (geoData,  i))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle (posData,  i))
                continue;

            if(posTrait::particle (secPosData,  i))
                continue;

            // calc the coordinate system

            Pnt3f &p  = posTrait   ::position(posData   );
            Pnt3f &sp = posTrait   ::position(secPosData);
            Vec3f &n  = normalTrait::normal  (normalData);

            Vec3f dz(sp - p);
            dz.normalize();

            Vec3f dx(n.cross(dz));
            if(dx.isZero())
            {
                dx=Vec3f(1,0,0).cross(dz);
                if(dx.isZero())
                {
                    dx=Vec3f(0,1,0).cross(dz);
                    if(dx.isZero())
                    {
                        dx=Vec3f(0,0,1).cross(dz);
                    }
                    else
                    {
                        dx.setValues(0,0,0);
                    }
                }
            }
            dx.normalize();

            Vec3f dy(dx.cross(dz));

            // now draw the geometry;
            geoTrait::draw(geoData, p, sp, dx, dy, dz,
                           sizeTrait::size(sizeData, i));
        }

        geoTrait::exit(part, pEnv, geoData);
    }

    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        // some variables for faster access
        GeoVectorProperty *pos = part->getPositions();

        // init traits
        typename geoTrait::dataType geoData;
        geoTrait::init(part, pEnv, geoData);

        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, pEnv, normalData);

        typename posTrait::dataType posData, secPosData;
        posTrait::init(part, pEnv, posData   , part->getPositions());
        posTrait::init(part, pEnv, secPosData, part->getSecPositions());

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(geoTrait::particle (geoData,  i))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle (posData,  i))
                continue;

            if(posTrait::particle (secPosData,  i))
                continue;

            // calc the coordinate system

            Pnt3f &p  = posTrait   ::position(posData   );
            Pnt3f &sp = posTrait   ::position(secPosData);
            Vec3f &n  = normalTrait::normal  (normalData);

            Vec3f dz(sp - p);
            dz.normalize();

            Vec3f dx(n.cross(dz));
            if(dx.isZero())
            {
                dx=Vec3f(1,0,0).cross(dz);
                if(dx.isZero())
                {
                    dx=Vec3f(0,1,0).cross(dz);
                    if(dx.isZero())
                    {
                        dx=Vec3f(0,0,1).cross(dz);
                    }
                    else
                    {
                        dx.setValues(0,0,0);
                    }
                }
            }
            dx.normalize();

            Vec3f dy(dx.cross(dz));

            // now draw the geometry;
            geoTrait::draw(geoData, p, sp, dx, dy, dz,
                           sizeTrait::size(sizeData, i));
        }

        geoTrait::exit(part, pEnv, geoData);
    }
};


/*! Objects using the pos/secpos and viewer-directed coordinate system for
    rendering 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class colTrait, class sizeTrait,
          class geoTrait>
struct drawViewerObjects : public ParticlesDrawer
{
    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        Matrix camera  = pEnv->getCameraToWorld();
        Matrix toworld = pEnv->getObjectToWorld();

//        DrawActionBase *action = pEnv->getOldAction();
        // get ModelView matrix to define the direction vectors
//        Matrix camera,toworld;
//        action->getCamera()->getBeacon()->getToWorld(camera);
//        action->getActNode()->getToWorld(toworld);
        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();
        toworld.invert();
        camera.multLeft(toworld);

        // Viewer position & up
        Pnt3f  vpos(camera[3]);

        // some variables for faster access

        // init traits
        typename geoTrait::dataType geoData;
        geoTrait::init(part, pEnv, geoData);

        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData, secPosData;
        posTrait::init(part, pEnv, posData   , part->getPositions());
        posTrait::init(part, pEnv, secPosData, part->getSecPositions());

        for(UInt32 i = 0; i < length; ++i)
        {
            if(geoTrait::particle (geoData,  i))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle (posData,  i))
                continue;

            if(posTrait::particle (secPosData,  i))
                continue;

            // calc the coordinate system

            Pnt3f &p  = posTrait::position(posData   );
            Pnt3f &sp = posTrait::position(secPosData);
            Vec3f  n  = vpos - p;

            Vec3f dz(sp - p);
            dz.normalize();

            Vec3f dx(n.cross(dz));
            if(dx.isZero())
            {
                dx=Vec3f(1,0,0).cross(dz);
                if(dx.isZero())
                {
                    dx=Vec3f(0,1,0).cross(dz);
                    if(dx.isZero())
                    {
                        dx=Vec3f(0,0,1).cross(dz);
                    }
                    else
                    {
                        dx.setValues(0,0,0);
                    }
                }
            }
            dx.normalize();

            Vec3f dy(dx.cross(dz));

            // now draw the geometry;
            geoTrait::draw(geoData, p, sp, dx, dy, dz,
                           sizeTrait::size(sizeData, i));
        }

        geoTrait::exit(part, pEnv, geoData);
   }

    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        Matrix camera  = pEnv->getCameraToWorld();
        Matrix toworld = pEnv->getObjectToWorld();

//        DrawActionBase *action = pEnv->getOldAction();
        // get ModelView matrix to define the direction vectors
//        Matrix camera,toworld;
//        action->getCamera()->getBeacon()->getToWorld(camera);
//        action->getActNode()->getToWorld(toworld);
        // normalize them, we don't want to neutralize scales in toworld
        toworld[0].normalize();
        toworld[1].normalize();
        toworld[2].normalize();
        toworld.invert();
        camera.multLeft(toworld);

        // Viewer position & up
        Pnt3f  vpos(camera[3]);

        // some variables for faster access
        GeoVectorProperty *pos = part->getPositions();

        // init traits
        typename geoTrait::dataType geoData;
        geoTrait::init(part, pEnv, geoData);

        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename posTrait::dataType posData, secPosData;
        posTrait::init(part, pEnv, posData   , part->getPositions());
        posTrait::init(part, pEnv, secPosData, part->getSecPositions());

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(geoTrait::particle (geoData,  i))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(posTrait::particle (posData,  i))
                continue;

            if(posTrait::particle (secPosData,  i))
                continue;

            // calc the coordinate system

            Pnt3f &p  = posTrait   ::position(posData   );
            Pnt3f &sp = posTrait   ::position(secPosData);
            Vec3f  n  = vpos - p;

            Vec3f dz(sp - p);
            dz.normalize();

            Vec3f dx(n.cross(dz));
            if(dx.isZero())
            {
                dx=Vec3f(1,0,0).cross(dz);
                if(dx.isZero())
                {
                    dx=Vec3f(0,1,0).cross(dz);
                    if(dx.isZero())
                    {
                        dx=Vec3f(0,0,1).cross(dz);
                    }
                    else
                    {
                        dx.setValues(0,0,0);
                    }
                }
            }
            dx.normalize();

            Vec3f dy(dx.cross(dz));

            // now draw the geometry;
            geoTrait::draw(geoData, p, sp, dx, dy, dz,
                           sizeTrait::size(sizeData, i));
        }

        geoTrait::exit(part, pEnv, geoData);
    }
};


/*! Static coordinates quad, pass all parameters to shader 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class secPosTrait, class colTrait, class texTrait,
          class sizeTrait, class normalTrait>
struct drawShaderQuads : public ParticlesDrawer
{
    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        Window *win = pEnv->getWindow();

        void (OSG_APIENTRY*_glMultiTexCoord3fvARB)(GLenum which,
                                                   GLubyte * data)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLenum which,
                                                   GLubyte * data)>(
                win->getFunction(_funcglMultiTexCoord3fvARB));

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, pEnv, normalData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename secPosTrait::dataType secPosData;
        secPosTrait::init(part, pEnv, secPosData, part->getSecPositions());

        GeoVectorProperty *pos = part->getPositions();

        glBegin(GL_QUADS);

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle(texData, i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(secPosTrait::particle(secPosData, i))
                continue;


            Vec3f s = sizeTrait::size(sizeData, i);

            if(s[0] == 0)
                continue;

            normalTrait::normal(normalData, 0);

            _glMultiTexCoord3fvARB(
                GL_TEXTURE1_ARB,
                reinterpret_cast<GLubyte *>(
                    posTrait::position(posData).getValues()));

            _glMultiTexCoord3fvARB(
                GL_TEXTURE2_ARB,
                reinterpret_cast<GLubyte *>(
                    secPosTrait::position(secPosData).getValues()));

            _glMultiTexCoord3fvARB(GL_TEXTURE3_ARB,
                                   reinterpret_cast<GLubyte *>(s.getValues()));

            texTrait::vertex(texData, 0, 0, 0);
            glVertex2f      (-.5f, -.5f);
            texTrait::vertex(texData, 0, 1, 0);
            glVertex2f      ( .5f, -.5f);
            texTrait::vertex(texData, 0, 1, 1);
            glVertex2f      ( .5f,  .5f);
            texTrait::vertex(texData, 0, 0, 1);
            glVertex2f      (-.5f,  .5f);
        }

        glEnd();
    }

    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        Window *win = pEnv->getWindow();

        void (OSG_APIENTRY*_glMultiTexCoord3fvARB)(GLenum which,
                                                   GLubyte * data)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLenum which,
                                                   GLubyte * data)>(
                win->getFunction(_funcglMultiTexCoord3fvARB));

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, pEnv, normalData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename secPosTrait::dataType secPosData;
        secPosTrait::init(part, pEnv, secPosData, part->getSecPositions());

        glBegin(GL_QUADS);

        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle(texData, i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(secPosTrait::particle(secPosData, i))
                continue;


            Vec3f s = sizeTrait::size(sizeData, i);

            if(s[0] == 0)
                continue;

            normalTrait::normal(normalData, 0);

            _glMultiTexCoord3fvARB(
                GL_TEXTURE1_ARB,
                reinterpret_cast<GLubyte *>(
                    posTrait::position(posData).getValues()));

            _glMultiTexCoord3fvARB(
                GL_TEXTURE2_ARB,
                reinterpret_cast<GLubyte *>(
                    secPosTrait::position(secPosData).getValues()));

            _glMultiTexCoord3fvARB(GL_TEXTURE3_ARB,
                                   reinterpret_cast<GLubyte *>(s.getValues()));

            texTrait::vertex(texData, 0, 0, 0);
            glVertex2f      (-.5f, -.5f);
            texTrait::vertex(texData, 0, 1, 0);
            glVertex2f      ( .5f, -.5f);
            texTrait::vertex(texData, 0, 1, 1);
            glVertex2f      ( .5f,  .5f);
            texTrait::vertex(texData, 0, 0, 1);
            glVertex2f      (-.5f,  .5f);
        }

        glEnd();
    }
};


/*! Static coordinates strips with y coordinates between -.5 and .5, split
    into size[2] parts, pass all parameters to shader 
    \ingroup GrpDrawablesParticlesHelpers
 */
template <class posTrait, class secPosTrait, class colTrait, class texTrait,
          class sizeTrait, class normalTrait>
struct drawShaderStrips : public ParticlesDrawer
{
    virtual void drawIndexed(Particles *part, DrawEnv *pEnv,
                             const Int32 *index, UInt32 length)
    {
        Window *win = pEnv->getWindow();

        void (OSG_APIENTRY*_glMultiTexCoord3fvARB)(GLenum which,
                                                   GLubyte * data)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLenum which,
                                                   GLubyte * data)>(
                win->getFunction(_funcglMultiTexCoord3fvARB));

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, pEnv, normalData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename secPosTrait::dataType secPosData;
        secPosTrait::init(part, pEnv, secPosData, part->getSecPositions());

        GeoVectorProperty *pos = part->getPositions();

        Int32 i;

        for(UInt32 ii = 0; ii < length; ++ii)
        {
            i = index[ii];

            if(i < 0 || i > Int32(pos->getSize()))
                continue;

            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle(texData, i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(secPosTrait::particle(secPosData, i))
                continue;


            Vec3f s = sizeTrait::size(sizeData, i);

            if(s[0] == 0)
                continue;

            normalTrait::normal(normalData, 0);

            _glMultiTexCoord3fvARB(
                GL_TEXTURE1_ARB,
                reinterpret_cast<GLubyte *>(
                    posTrait::position(posData).getValues()));

            _glMultiTexCoord3fvARB(
                GL_TEXTURE2_ARB,
                reinterpret_cast<GLubyte *>(
                    secPosTrait::position(secPosData).getValues()));

            _glMultiTexCoord3fvARB(GL_TEXTURE3_ARB,
                                   reinterpret_cast<GLubyte *>(s.getValues()));

            glBegin(GL_QUAD_STRIP);

            UInt32 n = static_cast<UInt32>(s[2]);
            Real32 step = 1.f / (n-1);
            Real32 v = 0.f;
            for(UInt32 y = 0; y < n; ++y, v += step)
            {
                texTrait::vertex(texData, 0, 0, v);
                glVertex2f  (-.5f, v-.5f);
                texTrait::vertex(texData, 0, 1, v);
                glVertex2f  ( .5f, v-.5f);
            }

            glEnd();
        }

    }

    virtual void draw(Particles *part, DrawEnv *pEnv, UInt32 length)
    {
        Window *win = pEnv->getWindow();

        void (OSG_APIENTRY*_glMultiTexCoord3fvARB) (GLenum which,
                                                    GLubyte * data)=
            reinterpret_cast<void (OSG_APIENTRY*) (GLenum which,
                                                   GLubyte * data)>(
                win->getFunction(_funcglMultiTexCoord3fvARB));

        // init traits
        typename colTrait::dataType colData;
        colTrait::init(part, pEnv, colData);

        typename texTrait::dataType texData;
        texTrait::init(part, pEnv, texData);

        typename sizeTrait::dataType sizeData;
        sizeTrait::init(part, pEnv, sizeData);

        typename normalTrait::dataType normalData;
        normalTrait::init(part, pEnv, normalData);

        typename posTrait::dataType posData;
        posTrait::init(part, pEnv, posData, part->getPositions());

        typename secPosTrait::dataType secPosData;
        secPosTrait::init(part, pEnv, secPosData, part->getSecPositions());

        for(UInt32 i = 0; i < length; ++i)
        {
            if(colTrait::particle (colData,  i))
                continue;

            if(texTrait::particle(texData, i))
                continue;

            if(sizeTrait::particle(sizeData, i))
                continue;

            if(normalTrait::particle(normalData, i))
                continue;

            if(posTrait::particle(posData, i))
                continue;

            if(secPosTrait::particle(secPosData, i))
                continue;


            Vec3f s = sizeTrait::size(sizeData, i);

            if(s[0] == 0)
                continue;

            normalTrait::normal(normalData, 0);

            _glMultiTexCoord3fvARB(
                GL_TEXTURE1_ARB,
                reinterpret_cast<GLubyte *>(
                    posTrait::position(posData).getValues()));

            _glMultiTexCoord3fvARB(
                GL_TEXTURE2_ARB,
                reinterpret_cast<GLubyte *>(
                    secPosTrait::position(secPosData).getValues()));

            _glMultiTexCoord3fvARB(GL_TEXTURE3_ARB,
                                   reinterpret_cast<GLubyte *>(s.getValues()));

            glBegin(GL_QUAD_STRIP);

            UInt32 n = static_cast<UInt32>(s[2]);
            Real32 step = 1.f / (n-1);
            Real32 v = 0.f;
            for(UInt32 y = 0; y < n; ++y, v += step)
            {
                texTrait::vertex(texData, 0, 0, v);
                glVertex2f  (-.5f, v-.5f);
                texTrait::vertex(texData, 0, 1, v);
                glVertex2f  ( .5f, v-.5f);
            }

            glEnd();
        }
    }
};

/*! \} */


/* Sorting functions */

/*! \ingroup GrpDrawablesParticlesHelpers
    \nohierarchy
 */

struct sorter
{
    sorter() {}

    sorter(Real32 value, Int32 index)
    {
        _value=value;
        _index=index;
    }

    bool operator<(const sorter &a) const
    {
        if(_value < a._value)
            return true;

        return false;
    }

    bool operator<=(const sorter &a) const
    {
        if(_value <= a._value)
            return true;

        return false;
    }

    bool operator>(const sorter &a) const
    {
        return ! (a < *this);
    }

    bool operator>=(const sorter &a) const
    {
        return ! (a <= *this);
    }

    Real32 _value;
    Int32  _index;
};

Int32 *Particles::calcIndex(DrawEnv *pEnv,
                            UInt32  &len,
                            Int32   *index)
{
    // some variables for faster access
          GeoVectorProperty *pos     = getPositions();
    const MFInt32           *indices = getMFIndices();

    // get ModelView matrix to define the direction vectors
//    Matrix camera,toworld;

    Matrix camera  = pEnv->getCameraToWorld();
    Matrix toworld = pEnv->getObjectToWorld();

/*
    RenderAction *ra = dynamic_cast<RenderAction *>(pEnv->getOldAction());

    if(ra != NULL)
    {
        toworld = ra->top_matrix();
    }
 */

    toworld.invert();
    camera.multLeft(toworld);

    Pnt3f refpoint(camera[3].getValues());

    if(getMode() == ViewDirQuads)
        camera.invert();

    Pnt3f p,q;
    UInt32 size;

    if(indices->size() > 0)
    {
        if(getNumParticles() == -1)
        {
            size = indices->size();
        }
        else
        {
            size = getNumParticles();
        }
    }
    else
    {
        if(getNumParticles() == -1)
        {
            size = pos->size();
        }
        else
        {
            size = getNumParticles();
        }
    }

    std::vector<sorter> sorterList(size);

    len = 0;
    UInt32 i;

    if(getMode() == ViewDirQuads)
    {
        if(indices->size() > 0)
        {
            for(i = 0; i < size; i++)
            {
                if((*(indices))[i] < 0 ||
                   (*(indices))[i] > Int32(pos->size()))
                    continue;

                sorterList[len]._index = (*(indices))[i];

                pos->getValue(p,i);
                camera.mult(p, p);
                sorterList[len]._value = p[2];

                len++;
            }
        }
        else
        {
            for(i = 0; i < size; i++)
            {
                sorterList[len]._index = i;

                pos->getValue(p,i);
                camera.mult(p, p);
                sorterList[len]._value = p[2];

                len++;
            }
        }
    }
    else
    {
        if(indices->size() > 0)
        {
            for(i = 0; i < size; i++)
            {
                if((*(indices))[i] < 0 ||
                   (*(indices))[i] > Int32(pos->size()))
                    continue;

                sorterList[len]._index = (*(indices))[i];

                pos->getValue(p,i);
                sorterList[len]._value = - refpoint.dist2(p);

                len++;
            }
        }
        else
        {
            for(i = 0; i < size; i++)
            {
                sorterList[len]._index = i;

                pos->getValue(p,i);
                sorterList[len]._value = - refpoint.dist2(p);

                len++;
            }
        }
    }

    std::sort(sorterList.begin(), sorterList.begin() + len);

    if(index == NULL)
        index=new Int32[len];

    if(getDrawOrder() == FrontToBack)
    {
        for(i = 0; i<len; i++)
        {
            index[i] = sorterList[len - 1 - i]._index;
        }
    }
    else
    {
        for(i = 0; i<len; i++)
        {
            index[i] = sorterList[i]._index;
        }
    }

    return index;
}


/*! Low-level Draw method that pumps OpenGL commands.
 */
void Particles::drawPrimitives(DrawEnv *pEnv)
{
    // some variables for faster access
          GeoVectorProperty *pos  = getPositions();
          GeoVectorProperty *col  = getColors();
          GeoVectorProperty *norm = getNormals();
    const MFVec3f           *size = getMFSizes();

    if((size   ->size() > 1 && size   ->size() != pos->getSize())  ||
       (col  != NULL && col->getSize()  != 1 &&
                        col->getSize()  != pos->getSize())       ||
       (norm != NULL && norm->getSize() != 1 &&
                        norm->getSize() != pos->getSize())
      )
    {
        FWARNING(("Particles::draw: inconsistent attributes "
                    "(p:%d s:%d c:%d)!\n",
                    pos->getSize(), size->size(),
                  (col != NULL)? int(col->getSize()) : -1));
        return;
    }

    ParticlesDrawer *drawer = findDrawer();

    if(drawer == NULL)
    {
        FWARNING(("Particles 0x%p: couldn't find drawer!\n", this));
        return;
    }

    const Int32 *index = NULL;
    UInt32 length = 0;
    bool freeIndex = false;

    if(_sfDrawOrder.getValue() != Particles::Any)
    {
        if(getDynamic())
        {
            index = calcIndex(pEnv,length);
        }
        else
        {
            if(!getBsp().created())
            {
                editBsp().build(this);
            }

//            Matrix modelview,toworld;

            Matrix modelview = pEnv->getCameraToWorld();
            Matrix toworld   = pEnv->getObjectToWorld();

/*
            RenderAction *ra = dynamic_cast<RenderAction *>(
                pEnv->getOldAction());

            if(ra != NULL)
            {
                toworld = ra->top_matrix();
            }
            else
            {
                pEnv->getOldAction()->getActNode()->getToWorld(toworld);
            }
 */
//            action->getCamera()->getBeacon()->getToWorld(modelview);
//            action->getActNode()->getToWorld(toworld);

            toworld.invert();
            modelview.mult(toworld);

            Pnt3f ref(modelview[3][0],modelview[3][1],
                      modelview[3][2]);
            Vec3f refvec(  modelview[2][0],modelview[2][1],
                      modelview[2][2]);

            index = getBsp().traverse(ref,length);
        }
        freeIndex = true;
    }
    else if (getMFIndices()->size() > 0)
    {
        index  = &(getMFIndices()->getValues()[0]);
        if(getNumParticles() == -1)
        {
            length = getMFIndices()->size();
        }
        else
        {
            length = getNumParticles();
        }
    }

    if(index != NULL)
    {
        if(length > 0)
            drawer->drawIndexed(this,pEnv,index,length);
    }
    else
    {
        if(getNumParticles() == -1)
        {
            drawer->draw(this,pEnv,pos->getSize());
        }
        else if(getNumParticles() > 0)
        {
            drawer->draw(this,pEnv,getNumParticles());
        }
    }

    if(freeIndex)
        delete [] index;

    return;
}

/*! find the drawer object for the actual configuration of parameters */

ParticlesDrawer *Particles::findDrawer(void)
{
    if(getPositions() == NULL)
        return NULL;

    UInt8 mode;
    enum { part = 0, sing, none } size,normal,color,tex,secpos;

    mode = getMode();

    // find the parameters' use

    size =   (getMFSizes()->size()      == getPositions()->getSize()) ? part :
             (getMFSizes()->size()      == 1                        ) ? sing :
                                                                        none;
    normal = (getNormals() != NULL &&
              getNormals()->getSize()   == getPositions()->getSize()) ? part :
             (getNormals() != NULL &&
              getNormals()->getSize()   == 1                        ) ? sing :
                                                                        none;
    secpos = (getSecPositions() != NULL &&
              getSecPositions()->getSize()== getPositions()->getSize())?part :
             (getSecPositions() != NULL &&
              getSecPositions()->getSize()== 1                        )?sing :
                                                                        none;
    color =  (getColors() != NULL &&
              getColors()->getSize()    == getPositions()->getSize()) ? part :
             (getColors() != NULL &&
              getColors()->getSize()    == 1                        ) ? sing :
                                                                        none;
    tex =    (getMFTextureZs()->size()  == getPositions()->getSize()) ? part :
             (getMFTextureZs()->size()  == 1                        ) ? sing :
                                                                        none;

    // check if the used types are common cases

/*
    bool normalIs3f = (getNormals()   != NULL &&
                       getNormals()->getFormat()      == GL_FLOAT);

    bool colorIs3f  = (getColors()    != NULL &&
                       getColors()->getFormat()       == GL_FLOAT &&
                       getColors()->getDimension()    == 3);
 */

    bool posIs3f    = (getPositions() != NULL &&
                       getPositions()->getFormat()    == GL_FLOAT &&
                       getPositions()->getDimension() == 3);

    // now find the drawer

    // main difference: mode, as only a subset of the attributes is used
    // in the different modes

    // this is where to add fast pathes...
    // don't go overboard, as every path adds code, and code bloat is
    // easily obtained here.

    switch(mode)
    {
    case Points:
    {
        static ParticlesDrawer *fallback =
                    new drawPoints<PosTraitGeneric,ColTraitGeneric,
                                   TexTraitGeneric,SizeTraitGeneric>;

        return fallback;
    }

    case Lines:
    {
        if(secpos == none)
        {
            FWARNING(("Particles::findDrawer: Need secondary positions for "
                      "type Lines!\n"));
            return NULL;
        }

        static ParticlesDrawer *fallback =
                    new drawLines<PosTraitGeneric,ColTraitGeneric,
                                  TexTraitGeneric,SizeTraitGeneric>;

        return fallback;
    }

    case ViewDirQuads:
    {
        static ParticlesDrawer *fallback =
                    new drawViewDirQuads<PosTraitGeneric,ColTraitGeneric,
                                         TexTraitGeneric,SizeTraitGeneric>;

        if(posIs3f && tex == none && size != none)
        {
            static ParticlesDrawer *pumps[] = {
              new drawViewDirQuads<PosTrait3f,ColTraitParticle,
                                   TexTraitNone,SizeTraitParticle>,
              new drawViewDirQuads<PosTrait3f,ColTraitSingle,
                                   TexTraitNone,SizeTraitParticle>,
              new drawViewDirQuads<PosTrait3f,ColTraitNone,
                                   TexTraitNone,SizeTraitParticle>,

              new drawViewDirQuads<PosTrait3f,ColTraitParticle,
                                   TexTraitNone,SizeTraitSingle>,
              new drawViewDirQuads<PosTrait3f,ColTraitSingle,
                                   TexTraitNone,SizeTraitSingle>,
              new drawViewDirQuads<PosTrait3f,ColTraitNone,
                                   TexTraitNone,SizeTraitSingle>,
              };

              return pumps[size * 3 + color];
        }

        return fallback;
    }

    case ViewerQuads:
    {
        static ParticlesDrawer *fallback =
                    new drawViewerQuads<PosTraitGeneric,ColTraitGeneric,
                                         TexTraitGeneric,SizeTraitGeneric>;

        if(posIs3f && tex == none && size != none)
        {
            static ParticlesDrawer *pumps[] = {
              new drawViewerQuads<PosTrait3f,ColTraitParticle,
                                  TexTraitNone,SizeTraitParticle>,
              new drawViewerQuads<PosTrait3f,ColTraitSingle,
                                  TexTraitNone,SizeTraitParticle>,
              new drawViewerQuads<PosTrait3f,ColTraitNone,
                                  TexTraitNone,SizeTraitParticle>,

              new drawViewerQuads<PosTrait3f,ColTraitParticle,
                                  TexTraitNone,SizeTraitSingle>,
              new drawViewerQuads<PosTrait3f,ColTraitSingle,
                                  TexTraitNone,SizeTraitSingle>,
              new drawViewerQuads<PosTrait3f,ColTraitNone,
                                  TexTraitNone,SizeTraitSingle>,
              };

              return pumps[size * 3 + color];
        }

        return fallback;
    }

    case Arrows:
    {
        if(secpos == none)
        {
            FWARNING(("Particles::findDrawer: Need secondary positions for "
                      "type Arrows!\n"));
            return NULL;
        }

        if(normal == none)
        {
            FWARNING(("Particles::findDrawer: Need normals for "
                      "type Arrows!\n"));
            return NULL;
        }

        static ParticlesDrawer *fallback =
                    new drawObjects<PosTraitGeneric,ColTraitGeneric,
                                    SizeTraitGeneric,NormalTraitGeneric,
                                    GeoTraitArrow>;

        return fallback;
    }

    case ViewerArrows:
    {
        if(secpos == none)
        {
            FWARNING(("Particles::findDrawer: Need secondary positions for "
                      "type ViewerArrows!\n"));
            return NULL;
        }

        if(normal == none)
        {
            FWARNING(("Particles::findDrawer: Need normals for "
                      "type ViewerArrows!\n"));
            return NULL;
        }

        static ParticlesDrawer *fallback =
                    new drawViewerObjects<PosTraitGeneric,ColTraitGeneric,
                                          SizeTraitGeneric,GeoTraitArrow>;

        return fallback;
    }

    case Rectangles:
    {
        if(secpos == none)
        {
            FWARNING(("Particles::findDrawer: Need secondary positions for "
                      "type Rectangles!\n"));
            return NULL;
        }

        if(normal == none)
        {
            FWARNING(("Particles::findDrawer: Need normals for "
                      "type Rectangles!\n"));
            return NULL;
        }

        static ParticlesDrawer *fallback =
                    new drawObjects<PosTraitGeneric,ColTraitGeneric,
                                    SizeTraitGeneric,NormalTraitGeneric,
                                    GeoTraitRectangle>;

        return fallback;
    }

    case ShaderQuads:
    {
        static ParticlesDrawer *fallback =
                    new drawShaderQuads<PosTraitGeneric,PosTraitGeneric,
                                        ColTraitGeneric, TexTraitGeneric,
                                        SizeTraitGeneric,NormalTraitGeneric>,
                               *nosecfallback =
                    new drawShaderQuads<PosTraitGeneric,PosTraitNone,
                                        ColTraitGeneric, TexTraitGeneric,
                                        SizeTraitGeneric,NormalTraitGeneric>;

        if(secpos == none)
        {
            return nosecfallback;
        }
        else
        {
            return fallback;
        }
    }

    case ShaderStrips:
    {
        static ParticlesDrawer *fallback =
                    new drawShaderStrips<PosTraitGeneric,PosTraitGeneric,
                                         ColTraitGeneric, TexTraitGeneric,
                                         SizeTraitGeneric,NormalTraitGeneric>,
                               *nosecfallback =
                    new drawShaderStrips<PosTraitGeneric,PosTraitNone,
                                         ColTraitGeneric, TexTraitGeneric,
                                         SizeTraitGeneric,NormalTraitGeneric>;

        if(secpos == none)
        {
            return nosecfallback;
        }
        else
        {
            return fallback;
        }
    }

    };


    if (normal) return NULL; // make picky compilers happy
    return NULL;
}

OSG_END_NAMESPACE
