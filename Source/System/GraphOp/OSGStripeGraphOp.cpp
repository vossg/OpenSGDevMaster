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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include "OSGStripeGraphOp.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGGeoFunctions.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StripeGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = StripeGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
    
} // namespace


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

StripeGraphOp::StripeGraphOp(const char* name) :
    Inherited(name),
    _force   (false),
    _stitch  (false)
{
}

StripeGraphOp::~StripeGraphOp(void)
{
}

StripeGraphOpTransitPtr
StripeGraphOp::create(void)
{
    return StripeGraphOpTransitPtr(new StripeGraphOp);
}

GraphOpTransitPtr StripeGraphOp::clone(void)
{
    return GraphOpTransitPtr(new StripeGraphOp);
}

void StripeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("force",  _force);
    ps("stitch",  _stitch);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("StripeGraphOp doesn't have parameters '%s'\n.",
                out.c_str()));
    }
}

std::string StripeGraphOp::usage(void)
{
    return 
    "Stripe: Stripe Geometries\n"
    "Params: name (type, default)\n"
    "  force  (bool, false): force striping even if already striped\n"
    "  stitch (bool, false): stitch strips using degenerate triangles\n";
}

bool StripeGraphOp::travNodeEnter(Node *node)
{
    Geometry *geo = dynamic_cast<Geometry *>(node->getCore());

    if(geo != NULL)
    {
        // Check if it's striped already
        if (!_force)
        {
            GeoIntegralProperty *t = geo->getTypes();
            
            if(t != NULL)
            {
                bool gotNonTriangles = false;
                bool gotTriStrips    = false;

                for(UInt32 i = 0; i < t->size(); ++i)
                {
                    switch(t->getValue(i))
                    {
                        case GL_TRIANGLE_STRIP:
                        case GL_TRIANGLE_FAN:
                            gotTriStrips = true;
                            break;

                        case GL_QUADS:
                        case GL_QUAD_STRIP:
                        case GL_POLYGON:
                            gotNonTriangles = true;
                            break;
                            
                        default:
                            break;
                    }

                    if(gotNonTriangles == true)
                        break;
                }

                if(gotNonTriangles == false &&
                   gotTriStrips    == true   )
                {
                    return true;
                }
            }
        }

        createSharedIndex(geo);
        createOptimizedPrimitives(geo, 1, true, true, 16, false, _stitch);
    }
    
    return true;
}

bool StripeGraphOp::travNodeLeave(Node *)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/
