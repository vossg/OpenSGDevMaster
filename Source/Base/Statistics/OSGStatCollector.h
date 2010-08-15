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


#ifndef _OSGSTATCOLLECTOR_H_
#define _OSGSTATCOLLECTOR_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGSField.h"

#include "OSGStatElemDesc.h"
#include "OSGMemoryObject.h"

OSG_BEGIN_NAMESPACE

class StatElem;
class StatElemDescBase;

/*! \brief Manager for Stat elements, see \guide{Statistics} for details.
    \ingroup GrpBaseStatistics
    \ingroup GrpLibOSGBase
*/

class OSG_BASE_DLLMAPPING StatCollector : public MemoryObject
{

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MemoryObject  Inherited;
    typedef StatCollector Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(StatCollector);

    /*---------------------------------------------------------------------*/
    /*! \name                     Instance                                 */
    /*! \{                                                                 */

    UInt32 getNumOfElems(void        ) const;
    void   refitElemNum (void        );
    void   clearElems   (void        );
    bool   isValidID    (Int32 elemId) const;
    void   reset        (StatElemDescBase::ResetMode mode =
                                StatElemDescBase::RESET_DRAW);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    StatElem *getElem(Int32             elemId       ) const;

    StatElem *getElem(Int32             elemId,
                      bool              create = true);

    StatElem *getElem(StatElemDescBase &desc,
                      bool              create = true);

    template <class T>
    T        *getElem(StatElemDesc<T>  &desc,
                      bool              create = true);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    void putToString   (      std::string  &outVal) const;
    bool getFromCString(const Char8       *&inVal );
    bool getValue      (      std::string  &name,
                              Real64       &val   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    StatCollector(void);
    StatCollector(const StatCollector &source);

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StatCollector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    const StatCollector &operator =(const StatCollector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Create                                    */
    /*! \{                                                                 */

    static StatCollector *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

    bool operator == (const StatCollector &rhs  ) const;
    bool operator <  (const StatCollector &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    StatCollector  operator +  (const StatCollector &other);
    StatCollector &operator += (const StatCollector &other);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    typedef std::vector<StatElem*>        StatElemStore;
    typedef StatElemStore::iterator       StatElemStoreIt;
    typedef StatElemStore::const_iterator StatElemStoreConstIt;

    StatElemStore _elemVec;
};

typedef StatCollector *       StatCollectorP;
typedef StatCollector * const StatCollectorPConst;
typedef StatCollector * const StatCollectorPConstArg;

OSG_GEN_MEMOBJPTR(StatCollector);


#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \brief Single Statistics element, see \ref PageSystemStatistics for 
           details.
    \ingroup GrpBaseStatistics
    \ingroup GrpBaseFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<StatCollectorP> :
    public FieldTraitsTemplateBase<StatCollectorP>
{
    static  DataType                    _type;
    typedef FieldTraits<StatCollectorP>  Self;

    enum                  { Convertible = Self::ToStringConvertible  |
                                          Self::FromStringConvertible };

    static OSG_BASE_DLLMAPPING
    DataType &getType      (void);

    static const Char8    *getSName     (void) { return "SFStatCollectorP"; }
    static const Char8    *getMName     (void) { return "MFStatCollectorP"; }

    static StatCollectorP  getDefault   (void) { return new StatCollector(); }

    static bool            getFromCString(      StatCollectorP  &outVal,
                                          const Char8          *&inVal)
    {
        if(outVal != NULL)
            return outVal->getFromCString(inVal);
        else
            return true;
    }

    static void            putToString   (const StatCollectorP &inVal,
                                                std::string    &outVal)
    {
        if(inVal != NULL)
            inVal->putToString(outVal);
    }


    static UInt32 getBinSize(const StatCollectorP &)
    {
        return 0;
    }

    static void copyToBin(      BinaryDataHandler & OSG_CHECK_ARG(pMem),
                          const StatCollectorP    & OSG_CHECK_ARG(oObject))
    {
    }

    static void copyToBin(      BinaryDataHandler & OSG_CHECK_ARG(pMem),
                          const StatCollectorP    * OSG_CHECK_ARG(pObjectStore),
                                UInt32              OSG_CHECK_ARG(uiNumObjects))
    {
    }

    static void copyFromBin(BinaryDataHandler & OSG_CHECK_ARG(pMem),
                            StatCollectorP    & OSG_CHECK_ARG(oObject))
    {
    }

    static void copyFromBin(BinaryDataHandler & OSG_CHECK_ARG(pMem),
                            StatCollectorP    * OSG_CHECK_ARG(pObjectStore),
                            UInt32              OSG_CHECK_ARG(uiNumObjects))
    {
    }
};

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldSingle 
 */
typedef SField<StatCollectorP> SFStatCollectorP;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle 
    \ingroup GrpBaseStatistics
    \ingroup GrpLibOSGBase
 */
struct SFStatCollectorP : public SField<StatCollectorP> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#include "OSGStatCollector.inl"

#endif /* _OSGSTATCOLLECTOR_H_ */
