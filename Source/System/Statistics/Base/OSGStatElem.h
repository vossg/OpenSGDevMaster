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


#ifndef _OSGSTATELEM_H_
#define _OSGSTATELEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"

#include <string>

OSG_BEGIN_NAMESPACE

class StatElemDescBase;

/*! \brief Single Statistics element, see \ref PageSystemStatistics for 
    details.
*/

class OSG_SYSTEM_DLLMAPPING StatElem
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Instance                                 */
    /*! \{                                                                 */

    bool              isOn   (void   ) const;
    void              setOn  (bool on);

    StatElemDescBase *getDesc(void   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                */
    /*! \{                                                                 */

    virtual void   putToString   (      std::string &str, 
                                  const char        *format = NULL) const = 0;
                                                
    virtual bool   getFromCString(const Char8      *&inVal        )       = 0;

    virtual Real64 getValue      (void                            ) const = 0; 

    virtual void   reset         (void                            )       = 0; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                */
    /*! \{                                                                 */

    virtual ~StatElem(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

     bool operator <  (const StatElem &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Creation                                   */
    /*! \{                                                                 */

    virtual StatElem *clone(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    virtual StatElem &operator += (const StatElem &other) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    StatElem (StatElemDescBase *desc);

    /*==========================  PRIVATE  ================================*/

  private:

    bool              _on;
    StatElemDescBase *_desc;

    // prohibit default functions (move to 'public' if you need one)

    StatElem            (const StatElem &source);
    StatElem& operator =(const StatElem &source);
};

typedef StatElem *StatElemP;

OSG_END_NAMESPACE

#include "OSGStatElem.inl"

#endif /* _OSGSTATELEM_H_ */
