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

struct RecordedRefCountPolicy
{
    static void addRef(const FieldContainerPtr objectP)
    {
        if(objectP != NullFC)
        {
            objectP->addReferenceX();

//            Thread::getCurrentChangeList()->addAddRefd(objectP->getId());
        }
    }
    static void subRef(const FieldContainerPtr objectP)
    {
        if(objectP != NullFC)
            objectP->subReferenceX();
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
        pOut = pIn;
        pIn  = NULL;

        if(pOut != NULL)
        {
            Thread::getCurrentChangeList()->addAddRefd(pOut->getId());
        }
    } 
};

struct MTRecordedRefCountPolicy : public RecordedRefCountPolicy
{
    template <class T>
    static T *validate   (T *pObject)
    {
        return convertToCurrentAspect(pObject);
    }

    template <class T>
    static T &dereference(T *pObject)
    {
        return *(validate(pObject));
    }
};

struct UnrecordedRefCountPolicy
{
    static void addRef(const FieldContainerPtr objectP)
    {
        if(objectP != NULL)
            objectP->addReferenceUnrecordedX();
    }
    static void subRef(const FieldContainerPtr objectP)
    {
        if(objectP != NULL)
            objectP->subReferenceUnrecordedX();
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
        pOut = pIn;
        pIn  = NULL;
    } 
};

struct NoRefCountPolicy
{
    static void addRef(const FieldContainerPtr)
    {
    }
    static void subRef(const FieldContainerPtr)
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

struct WeakRefCountPolicy
{
    static void addRef(const FieldContainerPtr objectP)
    {
        if(objectP != NULL)
            objectP->addWeakReference();
    }
    static void subRef(const FieldContainerPtr objectP)
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

#endif /* _OSGFIELDCONTAINERFIELDTRAITS_H_ */
