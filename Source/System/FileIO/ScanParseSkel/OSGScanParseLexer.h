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

#ifndef _OSGSCANPARSELEXER_H_
#define _OSGSCANPARSELEXER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif

// We have to prevent double inclusion of the scanner header file
#ifndef TOK_HEADER
#include "OSGScanParseSkelParser.hpp"
#endif



#ifndef yyFlexLexer
#ifdef OSG_USE_OSG2_NAMESPACE
# define yyFlexLexer OSG2ScanParseSkel_FlexLexer
#else
# define yyFlexLexer OSGScanParseSkel_FlexLexer
#endif
#ifdef OSG_PREBUILD_SCANPARSE
#include "OSGScanParseSkelScanner_FlexLexer.h"
#else
#include "FlexLexer.h"
#endif
#undef yyFlexLexer
#endif

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic pop
#endif

#include "OSGBaseTypes.h"

// OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

#ifdef OSG_USE_OSG2_NAMESPACE
# define OSGScanParseLexer          OSG2ScanParseLexer
# define OSGScanParseSkel_FlexLexer OSG2ScanParseSkel_FlexLexer
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFileIOScanParse
    \ingroup GrpLibOSGSystem
 */

class OSGScanParseLexer : public OSGScanParseSkel_FlexLexer
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGScanParseSkel_FlexLexer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    //! prohibit default function (move to 'public' if needed)
    OSGScanParseLexer(const OSGScanParseLexer &source);
    //! prohibit default function (move to 'public' if needed)
    void operator =(const OSGScanParseLexer &source);

    virtual int yylex();

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    YYSTYPE *lvalp;

    std::string tmpStr;
    OSG::Int32  expectToken;
    OSG::Int32  imageIntsExpected;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGScanParseLexer(std::istream           *arg_yyin  = 0,
                      std::ostream           *arg_yyout = 0);

    virtual ~OSGScanParseLexer(void);

    /*------------------------- your_category -------------------------------*/

    inline int yylex(YYSTYPE *plval)
    {
        this->lvalp = plval;
        return yylex();
    }

    /*------------------------- your_operators ------------------------------*/

    inline void expectType(OSG::Int32 iType)
    { expectToken = iType; }

    inline void expectImageInts(OSG::Int32 iImageIntsExpected)
    { this->imageIntsExpected = iImageIntsExpected; }

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};

//OSG_END_NAMESPACE

#endif /* _OSGSCANPARSESKELLEXER_H_ */
