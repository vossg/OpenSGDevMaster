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

#ifndef _STATINTONCEELEM_H_
#define _STATINTONCEELEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStatElem.h"

#include "OSGTime.h"

#include "OSGDeprecatedCPP.h"


OSG_BEGIN_NAMESPACE

class StatElemDescBase;

/*! \brief Time Statistics element, see \ref PageSystemStatistics for details.
    \ingroup GrpBaseStatistics
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING StatIntOnceElem : public StatElem 
{

    /*==========================  PUBLIC  =================================*/

 public:

    typedef OSG_HASH_SET(UInt32) IdHash;
    
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */
 
    static StatElem *create(StatElemDescBase *desc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */

    virtual void  reset(void                );

            void  add  (UInt32 contributorId, 
                         Int64 v            );
            void  sub  (UInt32 contributorId, 
                         Int64 v            );

            void  inc  (UInt32 contributorId);
            void  dec  (UInt32 contributorId);

            Int64 get  (void                ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */
        
    virtual void   putToString   (      std::string & str, 
                                  const std::string &format = std::string()) const;
 
    virtual bool   getFromCString(const Char8       *&inVal        );

    virtual Real64 getValue      (      void                       ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    comparison                                */
    /*! \{                                                                 */

    bool operator < (const StatIntOnceElem &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Creation                                   */
    /*! \{                                                                 */

    virtual StatElem *clone(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    virtual StatElem &operator += (const StatElem &other);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

 protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    StatIntOnceElem(StatElemDescBase *desc);

    virtual ~StatIntOnceElem(void); 

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
 private:

    typedef StatElem Inherited;

    Int64   _value;
    
    IdHash  _ids;

    // prohibit default functions (move to 'public' if you need one)
    StatIntOnceElem            (const StatIntOnceElem &source);
    StatIntOnceElem& operator =(const StatIntOnceElem &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef StatIntOnceElem *StatIntOnceElemP;

OSG_END_NAMESPACE

#include "OSGStatIntOnceElem.inl"

#endif /* _STATINTONCEELEM_H_ */
