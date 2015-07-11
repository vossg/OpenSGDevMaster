/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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

inline ParSpaceTrimmerError::ParSpaceTrimmerError(void) : 
    errtype(0)
{
}

inline ParSpaceTrimmerError::ParSpaceTrimmerError(int t)
    : errtype(t)
{
}

inline ParSpaceTrimmerError::~ParSpaceTrimmerError(void)
{
}


inline bool SScanLineEventLess::operator() (
    const SScanLineEvent *ptEvent1, const SScanLineEvent *ptEvent2) const
{
    const SScanLineEdge *cui_e1 = ptEvent1->ptEdge;
    const SScanLineEdge *cui_e2 = ptEvent2->ptEdge;

//     std::cerr << cui_e1 << " " << cui_e2 << std::endl;
    if( ( cui_e1 == cui_e2 ) && ( ptEvent1->bStart == ptEvent2->bStart ) )
    {
//         the same event!
//         std::cerr << "same event!" << std::endl;
//         std::cerr << ptEvent1->ptEdge << " <-> " << ptEvent2->ptEdge << std::endl;
//         std::cerr << ptEvent1->bStart << " <-> " << ptEvent2->bStart << std::endl;
        return false;
    }

    /*
    if( osgAbs( ptEvent1->clPos[1] - ptEvent2->clPos[1] ) > 1e-15 )
    {
        return ptEvent1->clPos[1] < ptEvent2->clPos[1];
    }
    else
    {
        if( osgAbs( ptEvent1->clPos[0] - ptEvent2->clPos[0] ) > 1e-15 )
        {
            return ptEvent1->clPos[0] < ptEvent2->clPos[0];
        }
    }*/
    if(DCTPVecIsNotEqual(ptEvent1->clPos, ptEvent2->clPos) )
    {
//         return ( ptEvent1->clPos < ptEvent2->clPos );
        return ( DCTPVecIsLesser(ptEvent1->clPos, ptEvent2->clPos) );
    }

    if( ( ptEvent1->bStart ) && !( ptEvent2->bStart ) )
        return false;
    if(!( ptEvent1->bStart ) && ( ptEvent2->bStart ) )
        return true;

//     std::cerr << "start = " << ptEvent1->bStart << " " << ptEvent2->bStart;
//     std::cerr << " checking dirs..." << std::endl;

    Vec2d dir1, dir2;

    dir1 = ptEvent1->clOther - ptEvent1->clPos;
    dir2 = ptEvent2->clOther - ptEvent2->clPos;
    if(DCTPVecIsNotEqual(dir1, dir2) )
    {
        if(!ptEvent1->bStart)
        {
            dir1[1] = -dir1[1];
            dir2[1] = -dir2[1];
        }

        if(osgAbs(dir1[1]) < DCTP_EPS)
        {
            if(osgAbs(dir2[1]) < DCTP_EPS)
            {
                if(dir1[0] < 0.0)   // this can't be zero!
                {
                    if(dir2[0] > 0.0)
                        return true;                  // this can't be zero!
                }
                else
                {
                    if(dir2[0] < 0.0)
                        return false;                 // this can't be zero!
                }
//             return ( dir1[0] < dir2[0] );
            }
            else
            {
//             std::cerr << "( dir1[0] < 0.0 )" << dir1[0];
                return ( dir1[0] < 0.0 ); // this can't be zero!
            }
        }
        else if(osgAbs(dir2[1]) < DCTP_EPS)
        {
//         std::cerr << "( dir2[0] > 0.0 )" << dir2[0];
            return ( dir2[0] > 0.0 ); // this can't be zero!
        }
        else
        {
            const double r1 = dir1[0] / dir1[1];
            const double r2 = dir2[0] / dir2[1];

            if(osgAbs(r1 - r2) >= DCTP_EPS)
            {
                return ( r1 < r2 );
            }
        }
    }

//     this can only be false for both ways, if it is the same edge!
    return( cui_e1 < cui_e2 );
}



inline bool SPolySimVertexLess::operator() (
    const SPolySimVertex *ptVertex1, const SPolySimVertex *ptVertex2) const
{
    if(ptVertex2->dSimplifyError - ptVertex1->dSimplifyError > 1e-20)
        return true;
    if(ptVertex1->dSimplifyError - ptVertex2->dSimplifyError > 1e-20)
        return false;
    return ( ptVertex1->uiIndex < ptVertex2->uiIndex );
}


inline ParSpaceTrimmer::ParSpaceTrimmer(void) :
    mesh(NULL),
    tcs(NULL),         //trimming curves
    tcs3d(NULL),       // 3d trimming curves
    terr(0),        // trimming error (used for 3d loops only!)
    state(),
    start_face(NULL),  //the face in which the curve starts (if it starts OVER_FACE)
    ie(NULL),          //last intersected edge
    ip(0.0),          //intersection parameter on bezier curve
    vcel(),
    pvccrd(NULL),
    m_pvvclSewed(NULL),
#ifdef OSG_FORCE_NO_T_VERTICES
/* #ifndef OSG_CREATE_NORMAL_MAPS
        std::vector< std::vector< Vec3d > >		*m_pvvclNormals;
 #endif*/
 #ifdef OSG_KEEP_2D_POINTS
    m_uiPosCnt(0),
 #endif
#endif
    m_bDeleteVertexInfo(false),
    m_clMin(),
    m_clMax(),
#ifdef OSG_ADAPTIVE_QUAD_TREE
    m_pclQuadTree(NULL),
#endif
    m_pvbReversed(NULL),
    m_pvbUsed(NULL),

#ifdef OSG_USE_SIMPLIFIER
    m_pclNurbs(NULL)
#endif
{
//     std::cerr << "pst constr" << std::endl;
}

inline ParSpaceTrimmer::~ParSpaceTrimmer(void)
{
//     std::cerr << "pst destr" << std::endl;
    if(m_bDeleteVertexInfo)
        deleteVertexInfo();
}

OSG_END_NAMESPACE
