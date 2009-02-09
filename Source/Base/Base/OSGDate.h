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

#ifndef _OSGDATE_H_
#define _OSGDATE_H_

#ifdef  __sgi
#pragma  once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseHelper
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING Date
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Date(void);
    Date(const Date &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Date(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    void   setSecond    (      UInt32  second   );
    UInt32 getSecond    (      void             );

    void   setMinute    (      UInt32  minute   );
    UInt32 getMinute    (      void             );

    void   setHour      (      UInt32  hour     );
    UInt32 getHour      (      void             );

    void   setDay       (      UInt32  day      );
    UInt32 getDay       (      void             );

    void   setYear      (      Int32   year     );
     Int32 getYear      (      void             );
    
    void   clear        (      void             );
    void   setSystemDate(      void             );

    void   set          (const Char8  *stringP  );

    bool   isLeapYear   (      void             );
    bool   valid        (      void             );

    void   set          (      UInt32 day, 
                               UInt32 month, 
                                Int32 year,
                               UInt32 hour   = 0, 
                               UInt32 minute = 0,
                               UInt32 second = 0);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    bool operator ==(const Date &other);
    bool operator !=(const Date &other);
    bool operator < (const Date &other);

    /*! \}                                                                 */
    /*===========================  PRIVATE  ===============================*/

  private:

    UInt32 _second;
    UInt32 _minute;
    UInt32 _hour;
    UInt32 _day;
    UInt32 _month;
    UInt32 _year;
             
    friend 
    std::ostream &operator <<(      std::ostream &os, 
                              const OSG::Date    &obj);
    friend 
    std::istream &operator >>(      std::istream &is, 
                                    OSG::Date    &obj);
};

std::ostream &operator <<(std::ostream &outStream, const OSG::Date &obj);
std::istream &operator >>(std::istream &inStream,        OSG::Date &obj);

OSG_END_NAMESPACE

#include "OSGDate.inl"

#endif // _OSGDATE_H_
