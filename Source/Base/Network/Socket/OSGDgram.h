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

#ifndef _DGRAM_H_
#define _DGRAM_H_
#ifdef __sgi
#pragma once
#endif

#include <list>
#include <vector>

#include "OSGBaseTypes.h"
#include "OSGTime.h"
#include "OSGBaseDef.h"
#include "OSGLock.h"

OSG_BEGIN_NAMESPACE

/* Package len */
#define OSG_DGRAM_LEN                   9216

/* num of Packages in read or write queue */
#define OSG_DGRAM_QUEUE_LEN             500

//#define TEST_LOST_DGRAM_RATE 0.1

/*! \ingroup GrpBaseNetwork
    \ingroup GrpBaseNetworkSockets
    \nohierarchy
*/

class OSG_BASE_DLLMAPPING Dgram
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name               constructor                            */
    /*! \{                                                                 */

    Dgram(void);
    ~Dgram(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               create, release                                */
    /*! \{                                                                 */

    static Dgram *create (void        );
    static void   release(Dgram *dgram);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               get                                            */
    /*! \{                                                                 */

          UInt32         getCapacity      (void) const;
          UInt16         getId            (void) const;
          bool           getResponseAck   (void) const;
          UInt32         getSize          (void) const;
          UChar8        *getData          (void);
    const UChar8        *getData          (void) const;

          UChar8        *getBuffer        (void);
          UInt32         getBufferSize    (void) const;
          UInt32         getBufferCapacity(void) const;

          bool           getEarlySend     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               set                                            */
    /*! \{                                                                 */

    void setSize         (UInt32 size    );
    void setResponseSize (void           );
    void setId           (UInt16 id      );
    void setResponseAck  (bool value     );

    void setBufferSize   (UInt32 size    );

    void setEarlySend    (bool value     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               compare                                        */
    /*! \{                                                                 */

           bool operator < (const Dgram  &other) const;
    static bool less(UInt16,UInt16);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               member                                         */
    /*! \{                                                                 */

    bool   _earlySend;
    UInt32 _size;

    /*! \nohierarchy 
     */
    struct 
    {
        UInt16 _id;
        UChar8 _data[OSG_DGRAM_LEN-2];
    } _buffer;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

};

// class pointer
typedef Dgram *DgramP;

OSG_END_NAMESPACE

// Application declarations
// to get ntons/ntohs
#ifdef WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

#include "OSGDgram.inl"

#endif /* _DGRAM_H_ */
