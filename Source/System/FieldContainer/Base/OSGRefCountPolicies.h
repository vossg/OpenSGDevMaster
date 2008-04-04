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

struct RecordedRefCounts
{
    static void addRef(FieldContainerPtrConst objectP)
    {
        if(objectP != NullFC)
            objectP->addReferenceX();
    }
    static void subRef(FieldContainerPtrConst objectP)
    {
        if(objectP != NullFC)
            objectP->subReferenceX();
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        RecordedRefCounts::addRef(pSource);
        RecordedRefCounts::subRef(pTarget);
    
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
        pOut = pIn;
        pIn  = NULL;
    } 
};

struct UnrecordedRefCounts
{
    static void addRef(FieldContainerPtrConst objectP)
    {
        if(objectP != NULL)
            objectP->addReferenceUnrecordedX();
    }
    static void subRef(FieldContainerPtrConst objectP)
    {
        if(objectP != NULL)
            objectP->subReferenceUnrecordedX();
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        UnrecordedRefCounts::addRef(pSource);
        UnrecordedRefCounts::subRef(pTarget);
    
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
        pOut = pIn;
        pIn  = NULL;
    } 
};

struct NoRefCounts
{
    static void addRef(FieldContainerPtrConst)
    {
    }
    static void subRef(FieldContainerPtrConst)
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
    static void convertTransitPtr(T *&pOut, T *&pIn)
    {
        OSG_ASSERT(false);
    } 
};

struct WeakRefCounts
{
    static void addRef(FieldContainerPtrConst objectP)
    {
        if(objectP != NULL)
            objectP->addWeakReference();
    }
    static void subRef(FieldContainerPtrConst objectP)
    {
        if(objectP != NULL)
            objectP->subWeakReference();

    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        WeakRefCounts::addRef(pSource);
        WeakRefCounts::subRef(pTarget);
    
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

#endif /* _OSGFIELDCONTAINERFIELDTRAITS_H_ */
