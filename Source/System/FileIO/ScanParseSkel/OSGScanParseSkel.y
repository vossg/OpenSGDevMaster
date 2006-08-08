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
%{

#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define YYLTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_TRIVIAL 1

#define OSGScanParseSkel_error SKEL->handleError

#ifdef WIN32
#include <malloc.h>
#define YYSIZE_T size_t
#endif
#include <OSGScanParseSkel.tab.h>
#include <OSGConfig.h>

#include <OSGBaseFunctions.h>
#include <OSGScanParseSkel.h>
#include <OSGLog.h>
#include <stack>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

int nextType;

char *szName1    = NULL;
char *szName2    = NULL;
char *szName3    = NULL;

void setName (char *&szName, const char *szVal);
void freeName(char *&szName);

#define SKEL ((ScanParseSkel *) pSkel)
#define SKELTEXT (SKEL->getText())

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif

%}

%token UTF8BOM

%token DEF
%token USE
%token ROUTE
%token PERIOD
%token TO
%token OPENBRACE
%token CLOSEBRACE
%token ID
%token PROTO
%token OPENBRACKET
%token CLOSEBRACKET
%token EXTERNPROTO
%token IS
%token EXPORT
%token IMPORT
%token PROFILE
%token COMPONENT
%token OSG_META
%token AS

%token EVENTIN
%token EVENTOUT
%token EXPOSEDFIELD
%token FIELD

%token SCRIPT

%token SFN_NULL

%token TOK_SFBOOL
%token TOK_SFCOLOR
%token TOK_SFCOLORRGBA
%token TOK_SFDOUBLE
%token TOK_SFFLOAT
%token TOK_SFIMAGE
%token TOK_SFINT32
%token TOK_SFMATRIX3D
%token TOK_SFMATRIX3F
%token TOK_SFMATRIX4D
%token TOK_SFMATRIX4F
%token TOK_SFNODE
%token TOK_SFROTATION
%token TOK_SFSTRING
%token TOK_SFTIME
%token TOK_SFVEC2D
%token TOK_SFVEC2F
%token TOK_SFVEC3D
%token TOK_SFVEC3F
%token TOK_SFVEC4D
%token TOK_SFVEC4F
%token TOK_MFBOOL
%token TOK_MFCOLOR
%token TOK_MFCOLORRGBA
%token TOK_MFDOUBLE
%token TOK_MFFLOAT
%token TOK_MFIMAGE
%token TOK_MFINT32
%token TOK_MFMATRIX3D
%token TOK_MFMATRIX3F
%token TOK_MFMATRIX4D
%token TOK_MFMATRIX4F
%token TOK_MFNODE 
%token TOK_MFROTATION
%token TOK_MFSTRING
%token TOK_MFTIME
%token TOK_MFVEC2D
%token TOK_MFVEC2F
%token TOK_MFVEC3D
%token TOK_MFVEC3F
%token TOK_MFVEC4D
%token TOK_MFVEC4F

%token Tok_MFBool
%token Tok_MFColor
%token Tok_MFColorRGBA
%token Tok_MFDouble
%token Tok_MFFloat
%token Tok_MFImage
%token Tok_MFInt32
%token Tok_MFMatrix3d
%token Tok_MFMatrix3f
%token Tok_MFMatrix4d
%token Tok_MFMatrix4f
%token Tok_MFNode
%token Tok_MFRotation
%token Tok_MFString
%token Tok_MFTime
%token Tok_MFVec2d
%token Tok_MFVec2f
%token Tok_MFVec3d
%token Tok_MFVec3f
%token Tok_MFVec4d
%token Tok_MFVec4f
%token Tok_SFBool
%token Tok_SFColor
%token Tok_SFColorRGBA
%token Tok_SFDouble
%token Tok_SFFloat
%token Tok_SFImage
%token Tok_SFInt32
%token Tok_SFMatrix3d
%token Tok_SFMatrix3f
%token Tok_SFMatrix4d
%token Tok_SFMatrix4f
%token Tok_SFNode
%token Tok_SFRotation
%token Tok_SFString
%token Tok_SFTime
%token Tok_SFVec2d
%token Tok_SFVec2f
%token Tok_SFVec3d
%token Tok_SFVec3f
%token Tok_SFVec4d
%token Tok_SFVec4f


%token TOK_MFCOLOR4I
%token TOK_MFPNT2F
%token TOK_MFPNT3F
%token TOK_MFPNT4F
%token TOK_MFPLANE

%token TOK_SFCOLOR4I
%token TOK_SFPNT2F
%token TOK_SFPNT3F
%token TOK_SFPNT4F
%token TOK_SFPLANE
%token TOK_SFVOLUME



%token Tok_MFColor4i
%token Tok_MFPnt2f
%token Tok_MFPnt3f
%token Tok_MFPnt4f
%token Tok_MFPlane

%token Tok_SFColor4i
%token Tok_SFPnt2f
%token Tok_SFPnt3f
%token Tok_SFPnt4f
%token Tok_SFPlane
%token Tok_SFVolume

%pure_parser

%%

vrmlScene : UTF8BOM profileStatement
          | profileStatement
;

profileStatement : PROFILE 
                   ID
                   {
                       if(SKEL != NULL)
                       {
                           SKEL->profileElement(SKELTEXT);
                       }
                   }
                   componentStatements
                 | componentStatements
;


componentStatements : componentStatementsRec metaStatements
                    |                        metaStatements
;

componentStatementsRec : componentStatementsRec componentStatement
                       |                        componentStatement
;

componentStatement : COMPONENT
                     ID
                     {
                         if(SKEL != NULL)
                         {
                             SKEL->componentElement(SKELTEXT);
                         }
                     }
;

metaStatements : metaStatementsRec statementsORempty
               |                   statementsORempty
;

metaStatementsRec : metaStatementsRec metaStatement
               |                      metaStatement
;

metaStatement : OSG_META
                ID { setName(szName1, SKELTEXT); }
                ID
                {
                    if(SKEL != NULL)
                    {
                        SKEL->metaElement(szName1, SKELTEXT);
                    }
                    freeName(szName1);
                }        
;


statementsORempty : statements
                  | empty 
;

statements : statements statement 
           |            statement  
;

statement : nodeStatement 
          | protoStatement 
          | routeStatement 
          | importStatement
          | exportStatement
;

nodeStatement : node 
              | DEF 
                nodeNameId  { setName(szName1, SKELTEXT); }
                node 
              | USE 
                nodeNameId  { if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); }
;

rootNodeStatement : node 
                  | DEF 
                    nodeNameId { setName(szName1, SKELTEXT); }
                    node 
;

protoStatement : proto 
               | externproto 
;


protoStatementsORempty : protoStatements
                       |
;

protoStatements : protoStatements protoStatement
                |                 protoStatement
;

protoId : nodeTypeId { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); }
        | SCRIPT     { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); }
;

proto : PROTO 
        protoId 
        OPENBRACKET 
        interfaceDeclarationsORempty 
        CLOSEBRACKET 
        OPENBRACE 
        protoBodyORempty
        CLOSEBRACE { if(SKEL != NULL) 
			SKEL->endProto(); }
;

protoBodyORempty : protoBody
                 | empty
;

protoBody : protoStatementsORempty rootNodeStatement statementsORempty
;

interfaceDeclarationsORempty : interfaceDeclarations
                             | empty
;

interfaceDeclarations : interfaceDeclarations interfaceDeclaration 
                      |                       interfaceDeclaration
;


restrictedInterfaceDeclaration : EVENTIN  
                                 fieldType  { setName(szName1, 
                                                      SKELTEXT);}
                                 eventInId  { if(SKEL != NULL)
                                              {
                                               SKEL->beginEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); }
                               | EVENTOUT 
                                 fieldType  { setName(szName1, 
                                                      SKELTEXT);}
                                 eventOutId { if(SKEL != NULL)
                                              {
                                               SKEL->beginEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); }
                               | FIELD    
                                 fieldType  { setName(szName1, 
                                                      SKELTEXT);}
                                 fieldId    { SKEL->expectType(nextType); 
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                              freeName(szName1); } 
                                 fieldValue { nextType = 0; 
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             }
;

interfaceDeclaration : restrictedInterfaceDeclaration
                     | EXPOSEDFIELD 
                       fieldType    { setName(szName1, 
                                              SKELTEXT); }
                       fieldId      { SKEL->expectType(nextType);  
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT); 
                                       freeName(szName1); }
                       fieldValue   { nextType = 0; 
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); }
;

externproto : EXTERNPROTO 
              nodeTypeId { if(SKEL != NULL) 
                             SKEL->beginExternProto(SKELTEXT); }
              OPENBRACKET 
              externInterfaceDeclarationsORempty
              CLOSEBRACKET 
              {
                 if(SKEL != NULL) 
                     SKEL->endExternProtoInterface(); 

                 SKEL->expectType(TOK_MFSTRING); 
              }
              URLList 
              {
                 if(SKEL != NULL) 
                     SKEL->endExternProto(); 
              }
;

externInterfaceDeclarationsORempty : externInterfaceDeclarations
                                   | empty
;

externInterfaceDeclarations : 
        externInterfaceDeclarations externInterfaceDeclaration
    |                               externInterfaceDeclaration
;

externInterfaceDeclaration : EVENTIN      
                             fieldType { setName(szName1, 
                                                 SKELTEXT); }
                             eventInId { if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); }
                           | EVENTOUT     
                             fieldType { setName(szName1, 
                                                 SKELTEXT); }
                             eventOutId { if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                          freeName(szName1); }
                           | FIELD        
                             fieldType { setName(szName1, 
                                                 SKELTEXT); }
                             fieldId   { if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); } 
                           | EXPOSEDFIELD 
                             fieldType { setName(szName1, 
                                                 SKELTEXT); }
                             fieldId { if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT); 
                                       freeName(szName1); }
;

routeStatement : ROUTE 
                 nodeNameId { setName(szName1, SKELTEXT); }
                 PERIOD     
                 eventOutId { setName(szName2, SKELTEXT); }
                 TO 
                 nodeNameId { setName(szName3, SKELTEXT); }
                 PERIOD 
                 eventInId  { if(SKEL != NULL)
                                SKEL->addRoute(szName1, 
                                               szName2,
                                               szName3,
                                               SKELTEXT);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            }
;

exportStatement : EXPORT 
                  ID 
                  {
                      setName(szName1, SKELTEXT);
                  }
                  importExportEnd
                  {
                      if(SKEL != NULL)
                      {
                          SKEL->exportElement(szName1, szName2);
                      }

                      freeName(szName1);
                      freeName(szName2);
                  }
;

importStatement : IMPORT 
                  ID 
                  {
                      setName(szName1, SKELTEXT);
                  }
                  PERIOD
                  ID
                  {
                      setName(szName3, SKELTEXT);
                  }
                  importExportEnd
                  {
                      if(SKEL != NULL)
                      {
                          SKEL->importElement(szName1, szName3, szName2);
                      }
                    
                      freeName(szName1);
                      freeName(szName2);
                      freeName(szName3);
                  }
;

importExportEnd : AS ID 
                  {
                        setName(szName2, SKELTEXT);
                  }
                | empty
;

URLList : fieldValue
;

empty :
;

node : nodeTypeId { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  }
       OPENBRACE 
//       nodeBodyORempty   
       scriptBodyORempty
       CLOSEBRACE { if(SKEL != NULL)
                     SKEL->endNode(); }
     | SCRIPT     { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  }
       OPENBRACE
       scriptBodyORempty 
       CLOSEBRACE { if(SKEL != NULL)
                     SKEL->endNode(); }
    | SFN_NULL { if(SKEL != NULL)
                    SKEL->nullNode(); }
;

/*
nodeBodyORempty : nodeBody
                | empty
;

nodeBody : nodeBody nodeBodyElement 
         |          nodeBodyElement
;
*/

scriptBodyORempty : scriptBody
                  | empty
;

scriptBody : scriptBody scriptBodyElement 
           |            scriptBodyElement
;

resInterfaceDeclarationScriptEvent : EVENTIN  
                                     fieldType  { setName(szName1, 
                                                          SKELTEXT); } 
                                     eventInId  { if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                 freeName(szName1); }
                                   | EVENTOUT 
                                     fieldType  { setName(szName1, 
                                                          SKELTEXT); }
                                     eventOutId { if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                  freeName(szName1); }
;

resInterfaceDeclarationScriptEventEnd : IS eventId 
                                        { 
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl(); 
                                          }
                                        }
                                      |
                                        { 
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl(); 
                                            }
                                        }
;

resInterfaceDeclarationScriptField : FIELD     
                                     fieldType { setName(szName1, 
                                                         SKELTEXT);
                                               }
                                     fieldId   { SKEL->expectType(nextType); 
                                              
                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 
                                              
                                                 freeName(szName1);
                                               }
;

resInterafceDeclarationScriptFieldEnd : IS fieldId { nextType = 0; 

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   } 
                                      | fieldValue { nextType = 0; 

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   }
;

resInterfaceDeclarationScriptExpField : EXPOSEDFIELD     
                                        fieldType { setName(szName1, 
                                                            SKELTEXT);
                                                  }
                                        fieldId   { SKEL->expectType(nextType);
                                                
                                                    if(SKEL != NULL)
                                                        SKEL->
                                                         beginExposedFieldDecl(
                                                           szName1,
                                                           nextType,
                                                           SKELTEXT); 
                                              
                                                    freeName(szName1);
                                                  }
;

resInterafceDeclarationScriptExpFieldEnd : IS fieldId { nextType = 0; 

                                                        if(SKEL != NULL)
                                                        {
                                                         SKEL->is(SKELTEXT);

                                                         SKEL->
                                                         endExposedFieldDecl();
                                                        }
                                                      } 
                                         | fieldValue { nextType = 0; 
   
                                                        if(SKEL != NULL)
                                                         SKEL->
                                                         endExposedFieldDecl();
                                                      }
;

/*
scriptBodyElement : nodeBodyElement 
                  | restrictedInterfaceDeclaration 
                  | EVENTIN  fieldType eventInId  IS eventInId 
                  | EVENTOUT fieldType eventOutId IS eventOutId 
                  | FIELD    fieldType fieldId    IS fieldId 
;
*/

scriptBodyElement : nodeBodyElement 
                  | resInterfaceDeclarationScriptEvent 
                    resInterfaceDeclarationScriptEventEnd
                  | resInterfaceDeclarationScriptField 
                    resInterafceDeclarationScriptFieldEnd
                  | resInterfaceDeclarationScriptExpField 
                    resInterafceDeclarationScriptExpFieldEnd
;


nodeBodyElement : fieldId 
                  { if(SKEL != NULL)
                    {
                     Int32 iFieldTypeId;

                     iFieldTypeId = SKEL->getFieldType(SKELTEXT);

                     if(SKEL->getMapFieldTypes() == true)
                     {
                      iFieldTypeId = SKEL->mapExtIntFieldType(    
                                        SKELTEXT,
                                        iFieldTypeId);
                     }
    
                     SKEL->expectType(iFieldTypeId); 

                     SKEL->beginField(SKELTEXT, 
                                        iFieldTypeId);
                                        
                    } 
                   }
                  fieldEnd
                | routeStatement 
                | protoStatement 
;

//                | generalId IS generalId 

fieldEnd : IS generalId { if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        } 
         | fieldValue   { if(SKEL != NULL)
                            SKEL->endField();
                        }
;


generalId  : ID
;

nodeNameId : ID 
;

nodeTypeId : ID
;

fieldId    : ID 
;

eventId    : ID 
;

eventInId  : ID 
;

eventOutId : ID ;

fieldType : Tok_MFBool      { nextType = TOK_MFBOOL;      }
          | Tok_MFColor     { nextType = TOK_MFCOLOR;     }
          | Tok_MFColorRGBA { nextType = TOK_MFCOLORRGBA; }
          | Tok_MFDouble    { nextType = TOK_MFDOUBLE;    }
          | Tok_MFFloat     { nextType = TOK_MFFLOAT;     }
          | Tok_MFImage     { nextType = TOK_MFIMAGE;     }
          | Tok_MFInt32     { nextType = TOK_MFINT32;     }
          | Tok_MFMatrix3d  { nextType = TOK_MFMATRIX3D;  }
          | Tok_MFMatrix3f  { nextType = TOK_MFMATRIX3F;  }
          | Tok_MFMatrix4d  { nextType = TOK_MFMATRIX4D;  }
          | Tok_MFMatrix4f  { nextType = TOK_MFMATRIX4F;  }
          | Tok_MFNode      { nextType = TOK_MFNODE;      }
          | Tok_MFRotation  { nextType = TOK_MFROTATION;  }
          | Tok_MFString    { nextType = TOK_MFSTRING;    }
          | Tok_MFTime      { nextType = TOK_MFTIME;      }
          | Tok_MFVec2d     { nextType = TOK_MFVEC2D;     }
          | Tok_MFVec2f     { nextType = TOK_MFVEC2F;     }
          | Tok_MFVec3d     { nextType = TOK_MFVEC3D;     }
          | Tok_MFVec3f     { nextType = TOK_MFVEC3F;     }
          | Tok_MFVec4d     { nextType = TOK_MFVEC4D;     }
          | Tok_MFVec4f     { nextType = TOK_MFVEC4F;     }
          | Tok_SFBool      { nextType = TOK_SFBOOL;      }
          | Tok_SFColor     { nextType = TOK_SFCOLOR;     }
          | Tok_SFColorRGBA { nextType = TOK_SFCOLORRGBA; }
          | Tok_SFDouble    { nextType = TOK_SFDOUBLE;    }
          | Tok_SFFloat     { nextType = TOK_SFFLOAT;     }
          | Tok_SFImage     { nextType = TOK_SFIMAGE;     }
          | Tok_SFInt32     { nextType = TOK_SFINT32;     }
          | Tok_SFMatrix3d  { nextType = TOK_SFMATRIX3D;  }
          | Tok_SFMatrix3f  { nextType = TOK_SFMATRIX3F;  }
          | Tok_SFMatrix4d  { nextType = TOK_SFMATRIX4D;  }
          | Tok_SFMatrix4f  { nextType = TOK_SFMATRIX4F;  }
          | Tok_SFNode      { nextType = TOK_SFNODE;      }
          | Tok_SFRotation  { nextType = TOK_SFROTATION;  }
          | Tok_SFString    { nextType = TOK_SFSTRING;    }
          | Tok_SFTime      { nextType = TOK_SFTIME;      }
          | Tok_SFVec2d     { nextType = TOK_SFVEC2D;     }
          | Tok_SFVec2f     { nextType = TOK_SFVEC2F;     }
          | Tok_SFVec3d     { nextType = TOK_SFVEC3D;     }
          | Tok_SFVec3f     { nextType = TOK_SFVEC3F;     }
          | Tok_SFVec4d     { nextType = TOK_SFVEC4D;     }
          | Tok_SFVec4f     { nextType = TOK_SFVEC4F;     }
          | Tok_MFColor4i   { nextType = TOK_MFCOLOR4I;   }
          | Tok_MFPnt2f     { nextType = TOK_MFPNT2F;     }
          | Tok_MFPnt3f     { nextType = TOK_MFPNT3F;     }
          | Tok_MFPnt4f     { nextType = TOK_MFPNT4F;     }
          | Tok_MFPlane     { nextType = TOK_MFPLANE;     }
          | Tok_SFColor4i   { nextType = TOK_SFCOLOR4I;   }
          | Tok_SFPnt2f     { nextType = TOK_SFPNT2F;     }
          | Tok_SFPnt3f     { nextType = TOK_SFPNT3F;     }
          | Tok_SFPnt4f     { nextType = TOK_SFPNT4F;     }
          | Tok_SFPlane     { nextType = TOK_SFPLANE;     }
          | Tok_SFVolume    { nextType = TOK_SFVOLUME;    }
;


fieldValue : TOK_SFBOOL
           | TOK_SFCOLOR
           | TOK_SFCOLORRGBA
           | TOK_SFDOUBLE
           | TOK_SFFLOAT
           | TOK_SFIMAGE
           | TOK_SFINT32
           | TOK_SFMATRIX3D
           | TOK_SFMATRIX3F
           | TOK_SFMATRIX4D
           | TOK_SFMATRIX4F
           | TOK_SFNODE     sfnodeValue
           | TOK_SFROTATION
           | TOK_SFSTRING
           | TOK_SFTIME
           | TOK_SFVEC2D
           | TOK_SFVEC2F
           | TOK_SFVEC3D
           | TOK_SFVEC3F
           | TOK_SFVEC4D
           | TOK_SFVEC4F
           | TOK_MFBOOL
           | TOK_MFCOLOR
           | TOK_MFCOLORRGBA
           | TOK_MFDOUBLE
           | TOK_MFFLOAT
           | TOK_MFIMAGE
           | TOK_MFINT32
           | TOK_MFMATRIX3D
           | TOK_MFMATRIX3F
           | TOK_MFMATRIX4D
           | TOK_MFMATRIX4F
           | TOK_MFNODE     mfnodeValue
           | TOK_MFROTATION
           | TOK_MFSTRING
           | TOK_MFTIME
           | TOK_MFVEC2D
           | TOK_MFVEC2F
           | TOK_MFVEC3D
           | TOK_MFVEC3F
           | TOK_MFVEC4D
           | TOK_MFVEC4F
           | TOK_MFCOLOR4I
           | TOK_MFPNT2F
           | TOK_MFPNT3F
           | TOK_MFPNT4F
           | TOK_MFPLANE
           | TOK_SFCOLOR4I
           | TOK_SFPNT2F
           | TOK_SFPNT3F
           | TOK_SFPNT4F
           | TOK_SFPLANE
           | TOK_SFVOLUME
;


sfnodeValue : nodeStatement 
            | IS generalId
              {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              }
;

mfnodeValue : nodeStatement   
            | IS generalId          
              {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              }
            | OPENBRACKET nodeStatementsORempty CLOSEBRACKET
;

nodeStatementsORempty : nodeStatements
                      | empty
;

nodeStatements : nodeStatements nodeStatement 
               |                nodeStatement  
;


%%

void setName (char *&szName, const char *szVal)
{
    stringDup(szVal, szName);
}

void freeName(char *&szName)
{
    delete [] szName;
    
    szName = NULL;
}


int OSGScanParseSkel_lex(YYSTYPE *, void *pSkel)
{
    return SKEL->lex();
}
