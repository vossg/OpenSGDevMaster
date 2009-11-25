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

#ifndef _OSGREFCOUNTPOLICIES_H_
#define _OSGREFCOUNTPOLICIES_H_
#ifdef __sgi
#pragma once
#endif

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct RecordedRefCountPolicy
{
    static const bool NotCounting = false;

    static void addRef(FieldContainer * const objectP)
    {
        if(objectP != NULL)
            objectP->addReferenceRecorded();
    }
    static void subRef(FieldContainer * const objectP)
    {
        if(objectP != NULL)
            objectP->subReferenceRecorded();
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        RecordedRefCountPolicy::addRef(pSource);
        RecordedRefCountPolicy::subRef(pTarget);
    
        pTarget = pSource;
    }

    template<class T>
    static T *validate(T *pIn)
    {
        return pIn;
    }

    template<class T>
    static T &dereference(T *pIn)
    {
        return *pIn;
    }

    template<class T, class U>
    static void convertTransitPtr(T *&pOut, U *&pIn)
    {
        RecordedRefCountPolicy::subRef(pOut);

        pOut = pIn;
        pIn  = NULL;

        if(pOut != NULL)
        {
            Thread::getCurrentChangeList()->addAddRefd(pOut->getId());
        }
    } 
};

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct UnrecordedRefCountPolicy
{
    static const bool NotCounting = false;

    static void addRef(FieldContainer * const objectP)
    {
        if(objectP != NULL)
            objectP->addReferenceUnrecorded();
    }
    static void subRef(FieldContainer * const objectP)
    {
        if(objectP != NULL)
            objectP->subReferenceUnrecorded();
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        UnrecordedRefCountPolicy::addRef(pSource);
        UnrecordedRefCountPolicy::subRef(pTarget);
    
        pTarget = pSource;
    }

    template<class T>
    static T *validate(T *pIn)
    {
        return pIn;
    }

    template<class T>
    static T &dereference(T *pIn)
    {
        return *pIn;
    }

    template<class T, class U>
    static void convertTransitPtr(T *&pOut, U *&pIn)
    {
        UnrecordedRefCountPolicy::subRef(pOut);

        pOut = pIn;
        pIn  = NULL;
    } 
};

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct NoRefCountPolicy
{
    static const bool NotCounting = true;

    template<class ObjT>
    static void addRef(ObjT * const)
    {
    }

    template<class ObjT>
    static void subRef(ObjT * const)
    {
    }

    static void addRef(FieldContainer * const)
    {
    }
    static void subRef(FieldContainer * const)
    {
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        pTarget = pSource;
    }

    template<class T>
    static T *validate(T *pIn)
    {
        return pIn;
    }

    template<class T, class U>
    static void convertTransitPtr(T *&pOut, U *&pIn)
    {
        OSG_ASSERT(false);
    } 
};

/*! \ingroup GrpBaseFieldContainerBase
    \ingroup GrpBaseBaseRefCounting
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

struct WeakRefCountPolicy
{
    static const bool NotCounting = false;

    static void addRef(FieldContainer * const objectP)
    {
        if(objectP != NULL)
            objectP->addWeakReference();
    }
    static void subRef(FieldContainer * const objectP)
    {
        if(objectP != NULL)
            objectP->subWeakReference();

    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        WeakRefCountPolicy::addRef(pSource);
        WeakRefCountPolicy::subRef(pTarget);
    
        pTarget = pSource;
    }

    template<class T>
    static T *validate(T *pIn)
    {
        if(pIn == NULL) 
        {
            return NULL;
        }
        else
        {
            return (pIn->getRefCount() > 0) ? pIn : NULL;
        }
    }

    template<class T>
    static T &dereference(T *pIn)
    {
        T *returnValue;
        
        if(pIn == NULL)
        {
            returnValue = NULL;
        }
        else
        {
            returnValue = (pIn->getRefCount() > 0) ? pIn : NULL;
        }

        return *returnValue;
    }

    template<class T, class U>
    static void convertTransitPtr(T *&pOut, U *&pIn)
    {
        OSG_ASSERT(false);
    } 
};

OSG_END_NAMESPACE

#endif /* _OSGREFCOUNTPOLICIES_H_ */
