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

#ifndef _STATTIMEELEM_H_
#define _STATTIMEELEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"

#include "OSGStatElem.h"

#include "OSGTime.h"

OSG_BEGIN_NAMESPACE

class StatElemDescBase;

/*! \brief Time Statistics element, see \ref PageSystemStatistics for details.
 */

class OSG_SYSTEM_DLLMAPPING StatTimeElem : public StatElem 
{

    /*==========================  PUBLIC  =================================*/

 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */
 
    static StatElem *create(StatElemDescBase *desc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */

    virtual void  reset  (void);
    
    const   Time &start  (void);
    const   Time &stop   (void);
    const   Time &getTime(void) const;
        
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */

    virtual void   putToString   (      std::string  &str, 
                                  const Char8        *format = NULL) const;
 
    virtual bool   getFromCString(const Char8       *&inVal        );

    virtual Real64 getValue      (      void                       ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    comparison                                */
    /*! \{                                                                 */

    bool operator < (const StatTimeElem &other) const;

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
  
    StatTimeElem(StatElemDescBase *desc);

    virtual ~StatTimeElem(void); 

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/

 private:

    typedef StatElem Inherited;

    Time _time;

    // prohibit default functions (move to 'public' if you need one)
    StatTimeElem            (const StatTimeElem &source);
    StatTimeElem& operator =(const StatTimeElem &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef StatTimeElem *StatTimeElemP;

OSG_END_NAMESPACE

#include "OSGStatTimeElem.inl"

#endif /* _STATTIMEELEM_H_ */
