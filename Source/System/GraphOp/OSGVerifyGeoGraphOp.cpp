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

#include "OSGTypedGeoIntegralProperty.h"

#include "OSGVerifyGeoGraphOp.h"
#include "OSGGraphOpFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VerifyGeoGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
A base class used to traverse geometries.

*/

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpFactory::the()->registerOp(new VerifyGeoGraphOp);
    return true;
}
static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

VerifyGeoGraphOp::VerifyGeoGraphOp(const char* name, bool repair): 
    SingleTypeGraphOpGeo(name), _repair(repair)
{
}

VerifyGeoGraphOp::~VerifyGeoGraphOp(void)
{
}

GraphOp *VerifyGeoGraphOp::create()
{
    VerifyGeoGraphOp *inst = new VerifyGeoGraphOp();
    return inst;
}

void VerifyGeoGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("repair",  _repair);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("VerifyGeoGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string VerifyGeoGraphOp::usage(void)
{
    return 
    "Verify: Test validity of Geometries\n"
    "  Run some validity tests on Geometries, makes sure indices are\n"
    "  in the valid range etc.\n"
    "Params: name (type, default)\n"
    "  repair (bool, true): try to repair consistency errors\n";
}

void VerifyGeoGraphOp::setRepair(bool repair)
{
    _repair = repair;
}

bool VerifyGeoGraphOp::travNodeEnter(NodePtr node)
{
    if (!node->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
    {
        FWARNING(("VerifyGeoOp: travNodeEnter got a non-Geometry Node\n"));
        return false;
    }

    bool _verified = true;

    GeometryPtr geo = dynamic_cast<GeometryPtr>(node->getCore());

    if(geo->getTypes() != NullFC && geo->getTypes()->size() == 0)
    {
        if (_repair)
        {
            //geo->setTypes(NullFC);
        }
        else
        {
            //_verified = false;
        }
    }        

    if(geo->getLengths() != NullFC && geo->getLengths()->size() == 0)
    {
        if (_repair)
        {
            //geo->setLengths(NullFC);
        }
        else
        {
            //_verified = false;
        }
    }

    if(geo->getPositions() != NullFC && geo->getPositions()->size() == 0)
    {
        if (_repair)
            geo->setPositions(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getNormals() != NullFC && geo->getNormals()->size() == 0)
    {
        if (_repair)
            geo->setNormals(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getColors() != NullFC && geo->getColors()->size() == 0)
    {
        if (_repair)
            geo->setColors(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getSecondaryColors() != NullFC && geo->getSecondaryColors()->size() == 0)
    {
        if (_repair)
            geo->setSecondaryColors(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getTexCoords() != NullFC && geo->getTexCoords()->size() == 0)
    {
        if (_repair)
            geo->setTexCoords(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getTexCoords1() != NullFC && geo->getTexCoords1()->size() == 0)
    {
        if (_repair)
            geo->setTexCoords1(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getTexCoords2() != NullFC && geo->getTexCoords2()->size() == 0)
    {
        if (_repair)
            geo->setTexCoords2(NullFC);
        else
        {
            _verified = false;
        }
    }

    if(geo->getTexCoords3() != NullFC && geo->getTexCoords3()->size() == 0)
    {
        if (_repair)
            geo->setTexCoords3(NullFC);
        else
        {
            _verified = false;
        }
    }

    bool consistent=true;
    int i, mind;

    // PORTME
#if 0
    GeoIndicesPtr ind = geo->getIndices();
    UInt16 nmap = geo->getIndexMapping().size();

    if (nmap==0) return Action::Continue;

    UInt32* sizes = new UInt32[nmap];
    for (i=0; i<nmap; i++) sizes[i]=UInt32(-1);

    if ( ( mind = geo->calcMappingIndex( Geometry::MapPosition ) ) >= 0 )
    {
        if (geo->getPositions()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getPositions()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapPosition );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getPositions = NullFC\n"));
            }
        }
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapNormal ) ) >= 0 )
    {
        if (geo->getNormals()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getNormals()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapNormal );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getNormals = NullFC\n"));
            }                
        }
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapColor ) ) >= 0 )
    {
        if (geo->getColors()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getColors()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapColor );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getColors = NullFC\n"));
            }                
        }                
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapSecondaryColor ) ) >= 0 )
    {
        if (geo->getSecondaryColors()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getSecondaryColors()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapSecondaryColor );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getSecondaryColors = NullFC\n"));
            }                
        }
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapTexCoords ) ) >= 0 )
    {
        if (geo->getTexCoords()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getTexCoords()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapTexCoords );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getTexCoords = NullFC\n"));
            }                
        }
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapTexCoords1 ) ) >= 0 )
    {
        if (geo->getTexCoords1()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getTexCoords1()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapTexCoords1 );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getTexCoords1 = NullFC\n"));
            }                
        }
                
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapTexCoords2 ) ) >= 0 )
    {
        if (geo->getTexCoords2()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getTexCoords2()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapTexCoords2 );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getTexCoords2 = NullFC\n"));
            }                
        }
                
    }

    if ( ( mind = geo->calcMappingIndex( Geometry::MapTexCoords3 ) ) >= 0 )
    {
        if (geo->getTexCoords3()!=NullFC)
            sizes[ mind ] = osgMin ( sizes[ mind ], geo->getTexCoords3()->size() );
        else
        {
            if (_repair)
            {
                UInt16 &im = geo->getIndexMapping(mind);
                im &=~( Geometry::MapTexCoords3 );                
            }
            else
            {
                _verified = false;
                FDEBUG(("calcMappingIndex>=0, getTexCoords3 = NullFC\n"));
            }                
        }                
    }

    for (UInt32 j=0; j<ind->size(); j++)
        if (ind->getValue(j)>=sizes[j % nmap])
        {
            if (_repair)
            {
                ind->setValue(0,j);
            }
            else
            {
                consistent = false; break;
            }
        }

#endif

    _verified = (_verified && (_repair | consistent) );

    if (_verified)
        return Action::Continue;
    else
        return Action::Quit;
}

bool VerifyGeoGraphOp::travNodeLeave(NodePtr)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/
