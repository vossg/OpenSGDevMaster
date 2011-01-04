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

/* Author: Patrick Daehne */

%union {
    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;
}

%{

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define OSGScanParseSkel_error SKEL->handleError

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGMatrix.h"
#include "OSGScanParseLexer.h"
#include "OSGScanParseSkel.h"

#include <iostream>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

#define SKEL (static_cast<ScanParseSkel *>(pSkel))

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif

%}

%token <stringVal> TOK_HEADER

%token TOK_PROFILE
%token TOK_COMPONENT
%token TOK_META

%token TOK_PROTO
%token TOK_EXTERNPROTO
%token TOK_IS

%token TOK_DEF
%token TOK_USE

%token TOK_ROUTE
%token TOK_TO

%token TOK_IMPORT
%token TOK_EXPORT
%token TOK_AS

%token TOK_eventIn
%token TOK_eventOut
%token TOK_exposedField
%token TOK_field

%token <intVal> TOK_MFBool
%token <intVal> TOK_MFColor
%token <intVal> TOK_MFColorRGBA
%token <intVal> TOK_MFDouble
%token <intVal> TOK_MFFloat
%token <intVal> TOK_MFImage
%token <intVal> TOK_MFInt32
%token <intVal> TOK_MFMatrix3d
%token <intVal> TOK_MFMatrix3f
%token <intVal> TOK_MFMatrix4d
%token <intVal> TOK_MFMatrix4f
%token <intVal> TOK_MFNode
%token <intVal> TOK_MFRotation
%token <intVal> TOK_MFString
%token <intVal> TOK_MFTime
%token <intVal> TOK_MFVec2d
%token <intVal> TOK_MFVec2f
%token <intVal> TOK_MFVec3d
%token <intVal> TOK_MFVec3f
%token <intVal> TOK_MFVec4d
%token <intVal> TOK_MFVec4f
%token <intVal> TOK_SFBool
%token <intVal> TOK_SFColor
%token <intVal> TOK_SFColorRGBA
%token <intVal> TOK_SFDouble
%token <intVal> TOK_SFFloat
%token <intVal> TOK_SFImage
%token <intVal> TOK_SFInt32
%token <intVal> TOK_SFMatrix3d
%token <intVal> TOK_SFMatrix3f
%token <intVal> TOK_SFMatrix4d
%token <intVal> TOK_SFMatrix4f
%token <intVal> TOK_SFNode
%token <intVal> TOK_SFRotation
%token <intVal> TOK_SFString
%token <intVal> TOK_SFTime
%token <intVal> TOK_SFVec2d
%token <intVal> TOK_SFVec2f
%token <intVal> TOK_SFVec3d
%token <intVal> TOK_SFVec3f
%token <intVal> TOK_SFVec4d
%token <intVal> TOK_SFVec4f
/* The following types are not VRML conformant */
%token <intVal> TOK_MFColor4i
%token <intVal> TOK_MFPnt2f
%token <intVal> TOK_MFPnt3f
%token <intVal> TOK_MFPnt4f
%token <intVal> TOK_MFPlane
%token <intVal> TOK_SFColor4i
%token <intVal> TOK_SFPnt2f
%token <intVal> TOK_SFPnt3f
%token <intVal> TOK_SFPnt4f
%token <intVal> TOK_SFPlane
%token <intVal> TOK_SFVolume
%token <intVal> TOK_SFVec2i
%token <intVal> TOK_MFVec2i

%token <intVal> TOK_hex
%token <intVal> TOK_int32
%token <doubleVal> TOK_double
%token <stringVal> TOK_string
%token <boolVal> TOK_bool
%token TOK_NULL
%token <stringVal> TOK_Id

%token TOK_ImageFinished

%token TOK_Error

%type <stringVal> profileNameId
%type <stringVal> componentNameId
/*%type <intVal> componentSupportLevel*/
%type <stringVal> metakey
%type <stringVal> metavalue
%type <stringVal> asStatement
%type <stringVal> nodeNameId
%type <stringVal> nodeTypeId
%type <stringVal> fieldId
%type <stringVal> eventInId
%type <stringVal> eventOutId
%type <intVal> fieldType
%type <intVal> fieldValue
%type <intVal> fieldEnd
%type <intVal> fieldDeclarationEnd

%type <intVal> int32
%type <doubleVal> double
%type <floatVal> float

%pure_parser

%%

x3dScene:
    headerStatement
    profileStatement
    componentStatements
    metaStatements
    statements;

headerStatement:
    TOK_HEADER { if(SKEL->verifyHeader($1) == false) { YYABORT; } }
    | /* empty */{ if(SKEL->checkHeader() == true) { YYABORT; } }

profileStatement:
    TOK_PROFILE profileNameId { SKEL->profileElement($2); }
    | /* empty */;

profileNameId:
    TOK_Id;

componentStatements:
    componentStatements componentStatement
    | /* empty */;

componentStatement:
    /* Not VRML conformant */
    TOK_COMPONENT
    componentNameId
    { SKEL->componentElement($2); };

componentNameId:
    TOK_Id
    | TOK_string;
/*
componentSupportLevel:
    int32;
*/

metaStatements:
    metaStatements metaStatement
    | /* empty */;

metaStatement:
    TOK_META
    metakey
    { SKEL->_tmpString1 = $2; }
    metavalue
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), $4); };

metakey:
    TOK_string;

metavalue:
    TOK_string;

statements:
    statements statement
    | /* empty */;

statement:
    nodeStatement
    | protoStatement
    | routeStatement
    | importStatement
    | exportStatement;

nodeStatement:
    nodeTypeId { SKEL->beginNode($1, 0); }
    node
    | TOK_DEF
    nodeNameId { SKEL->_tmpString1 = $2; }
    nodeTypeId { SKEL->beginNode($4, SKEL->_tmpString1.c_str()); }
    node
    | TOK_USE
    nodeNameId { SKEL->use($2); };

protoStatement:
    proto
    | externproto;

protoStatements:
    protoStatements protoStatement
    | /* empty */;

proto:
    TOK_PROTO nodeTypeId { SKEL->beginProto($2); }
    '[' interfaceDeclarations ']' { SKEL->endProtoInterface(); }
    '{' statements '}' { SKEL->endProto(); }; /* Not VRML conformant */

interfaceDeclarations:
    interfaceDeclarations interfaceDeclaration
    | /* empty */;

interfaceDeclaration:
    TOK_eventIn
    fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    eventInId { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), $2, $4); SKEL->endEventDecl(); }
    | TOK_eventOut
      fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
      eventOutId { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), $2, $4); SKEL->endEventDecl(); }
    | TOK_field
      fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
      fieldId { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), $2, $4); SKEL->getLexer()->expectType($2); }
      fieldValue { SKEL->endFieldDecl(); }
    | TOK_exposedField
      fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
      fieldId { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), $2, $4); SKEL->getLexer()->expectType($2); }
      fieldValue { SKEL->endExposedFieldDecl(); };

externproto:
    TOK_EXTERNPROTO nodeTypeId { SKEL->beginExternProto($2); }
    '[' externInterfaceDeclarations ']' { SKEL->endExternProtoInterface(); }
    URLList { SKEL->endExternProto(); };

externInterfaceDeclarations:
    externInterfaceDeclarations externInterfaceDeclaration
    | /* empty */;

externInterfaceDeclaration:
    TOK_eventIn
    fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    eventInId { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), $2, $4); }
    | TOK_eventOut
      fieldType  { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
      eventOutId { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), $2, $4); }
    | TOK_field
      fieldType  { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
      fieldId { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), $2, $4); }
    | TOK_exposedField
      fieldType  { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
      fieldId { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), $2, $4); };

routeStatement:
    TOK_ROUTE
    nodeNameId { SKEL->_tmpString1 = $2; }
    '.'
    eventOutId { SKEL->_tmpString2 = $5; }
    TOK_TO
    nodeNameId { SKEL->_tmpString3 = $8; }
    '.'
    eventInId
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), $11); };

importStatement:
    TOK_IMPORT
    nodeNameId { SKEL->_tmpString1 = $2; }
    '.'
    nodeNameId { SKEL->_tmpString2 = $5; }
    asStatement
    {
        if ($7 != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), $7);
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    };

exportStatement:
    TOK_EXPORT
    nodeNameId { SKEL->_tmpString1 = $2; }
    asStatement
    {
        if ($4 != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), $4);
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    };

asStatement:
    TOK_AS
    nodeNameId { $$ = $2; }
    | /* empty */ { $$ = 0; };

URLList:
    mfstringValue;

node:
    '{' scriptBody '}' { SKEL->endNode(); }; /* Not VRML conformant */

scriptBody:
    scriptBody scriptBodyElement
    | /* empty */;

scriptBodyElement:
    nodeBodyElement
    | eventInDeclaration
    | eventOutDeclaration
    | fieldDeclaration
    | exposedFieldDeclaration
    | error;

eventInDeclaration:
    TOK_eventIn
    fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    eventInId { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), $2, $4); }
    eventDeclarationEnd { SKEL->endEventDecl(); };

eventOutDeclaration:
    TOK_eventOut
    fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    eventOutId { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), $2, $4); }
    eventDeclarationEnd { SKEL->endEventDecl(); };

eventDeclarationEnd:
    /* empty */
    | TOK_IS fieldId { SKEL->is($2); };

fieldDeclaration:
    TOK_field
    fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    fieldId { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), $2, $4); SKEL->getLexer()->expectType($2); }
    fieldDeclarationEnd { SKEL->endFieldDecl(); };

exposedFieldDeclaration:
    TOK_exposedField
    fieldType { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    fieldId { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), $2, $4); SKEL->getLexer()->expectType($2); }
    fieldDeclarationEnd { SKEL->endExposedFieldDecl(); };

fieldDeclarationEnd:
    fieldValue
    | fieldType TOK_IS fieldId { SKEL->is($3); };

nodeBodyElement:
    fieldId
    {
        Int32 iFieldTypeId = SKEL->getFieldType($1);
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType($1, iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField($1, iFieldTypeId);
    }
    fieldEnd { SKEL->endField(); }
    | routeStatement
    | protoStatement
    | importStatement
    | exportStatement;

fieldEnd:
    fieldValue
    | fieldType TOK_IS fieldId { SKEL->is($3); };

nodeNameId:
    TOK_Id;

nodeTypeId:
    TOK_Id;

fieldId:
    TOK_Id;

eventInId:
    TOK_Id;

eventOutId:
    TOK_Id;

fieldType:
    TOK_MFBool
    | TOK_MFColor
    | TOK_MFColorRGBA
    | TOK_MFDouble
    | TOK_MFFloat
    | TOK_MFImage
    | TOK_MFInt32
    | TOK_MFMatrix3d
    | TOK_MFMatrix3f
    | TOK_MFMatrix4d
    | TOK_MFMatrix4f
    | TOK_MFNode
    | TOK_MFRotation
    | TOK_MFString
    | TOK_MFTime
    | TOK_MFVec2d
    | TOK_MFVec2f
    | TOK_MFVec3d
    | TOK_MFVec3f
    | TOK_MFVec4d
    | TOK_MFVec4f
    | TOK_SFBool
    | TOK_SFColor
    | TOK_SFColorRGBA
    | TOK_SFDouble
    | TOK_SFFloat
    | TOK_SFImage
    | TOK_SFInt32
    | TOK_SFMatrix3d
    | TOK_SFMatrix3f
    | TOK_SFMatrix4d
    | TOK_SFMatrix4f
    | TOK_SFNode
    | TOK_SFRotation
    | TOK_SFString
    | TOK_SFTime
    | TOK_SFVec2d
    | TOK_SFVec2f
    | TOK_SFVec3d
    | TOK_SFVec3f
    | TOK_SFVec4d
    | TOK_SFVec4f
    /* The following types are not VRML conformant */
    | TOK_MFColor4i
    | TOK_MFPnt2f
    | TOK_MFPnt3f
    | TOK_MFPnt4f
    | TOK_MFPlane
    | TOK_SFColor4i
    | TOK_SFPnt2f
    | TOK_SFPnt3f
    | TOK_SFPnt4f
    | TOK_SFPlane
    | TOK_SFVolume;

fieldValue:
    TOK_MFBool mfboolValue
    | TOK_MFColor mfcolorValue
    | TOK_MFColorRGBA mfcolorRGBAValue
    | TOK_MFDouble mfdoubleValue
    | TOK_MFFloat mffloatValue
    | TOK_MFImage mfimageValue
    | TOK_MFInt32 mfint32Value
    | TOK_MFMatrix3d mfmatrix3dValue
    | TOK_MFMatrix3f mfmatrix3fValue
    | TOK_MFMatrix4d mfmatrix4dValue
    | TOK_MFMatrix4f mfmatrix4fValue
    | TOK_MFNode mfnodeValue
    | TOK_MFRotation mfrotationValue
    | TOK_MFString mfstringValue
    | TOK_MFTime mftimeValue
    | TOK_MFVec2d mfvec2dValue
    | TOK_MFVec2f mfvec2fValue
    | TOK_MFVec3d mfvec3dValue
    | TOK_MFVec3f mfvec3fValue
    | TOK_MFVec4d mfvec4dValue
    | TOK_MFVec4f mfvec4fValue
    | TOK_SFBool sfboolValue
    | TOK_SFColor sfcolorValue
    | TOK_SFColorRGBA sfcolorRGBAValue
    | TOK_SFDouble sfdoubleValue
    | TOK_SFFloat sffloatValue
    | TOK_SFImage sfimageValue
    | TOK_SFInt32 sfint32Value
    | TOK_SFMatrix3d sfmatrix3dValue
    | TOK_SFMatrix3f sfmatrix3fValue
    | TOK_SFMatrix4d sfmatrix4dValue
    | TOK_SFMatrix4f sfmatrix4fValue
    | TOK_SFNode sfnodeValue
    | TOK_SFRotation sfrotationValue
    | TOK_SFString sfstringValue
    | TOK_SFTime sftimeValue
    | TOK_SFVec2d sfvec2dValue
    | TOK_SFVec2f sfvec2fValue
    | TOK_SFVec3d sfvec3dValue
    | TOK_SFVec3f sfvec3fValue
    | TOK_SFVec4d sfvec4dValue
    | TOK_SFVec4f sfvec4fValue
    /* The following types are not VRML conformant */
    | TOK_MFColor4i mfcolor4iValue
    | TOK_MFPnt2f mfpnt2fValue
    | TOK_MFPnt3f mfpnt3fValue
    | TOK_MFPnt4f mfpnt4fValue
    | TOK_MFPlane mfplaneValue
    | TOK_SFColor4i sfcolor4iValue
    | TOK_SFPnt2f sfpnt2fValue
    | TOK_SFPnt3f sfpnt3fValue
    | TOK_SFPnt4f sfpnt4fValue
    | TOK_SFPlane sfplaneValue
    | TOK_SFVolume sfVolumeValue;
    | TOK_SFVec2i sfvec2iValue
    | TOK_MFVec2i mfvec2iValue

int32:
    TOK_hex { $$ = $1; }
    | TOK_int32 { $$ = $1; };

double:
    TOK_int32 { $$ = $1; }
    | TOK_double { $$ = $1; };

float:
    TOK_int32 { $$ = static_cast<float>($1); }
    | TOK_double { $$ = static_cast<float>($1); };

sfboolValue:
    TOK_bool
    {
        SKEL->addBoolValue($1);
    }
    | TOK_Id { SKEL->addFieldValue($1); }; /* Not VRML conformant */

sfcolorValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f($1, $3, $5));
    };

sfcolorRGBAValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f($1, $3, $5, $7));
    };

sfdoubleValue:
    double
    {
        SKEL->addDoubleValue($1);
    };

sffloatValue:
    float
    {
        SKEL->addFloatValue($1);
    };

sfimageValue:
    int32 { SKEL->beginValue(); }
    int32 { SKEL->appendValue(); }
    int32
    {
        SKEL->appendValue();
        SKEL->beginImage($1, $3, $5);
    }
    pixels TOK_ImageFinished
    {
        SKEL->endImage();
    };

pixels:
    pixels int32
    {
        SKEL->addImagePixel($2);
    }
    | /* empty */;

sfint32Value:
    int32
    {
        SKEL->addInt32Value($1);
    };

sfmatrix3dValue:
    double { SKEL->beginValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            $1,  $7, $13,
            $3,  $9, $15,
            $5, $11, $17);
    };

sfmatrix3fValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            $1,  $7, $13,
            $3,  $9, $15,
            $5, $11, $17);
    };

sfmatrix4dValue:
    double { SKEL->beginValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            $1,  $9, $17, $25,
            $3, $11, $19, $27,
            $5, $13, $21, $29,
            $7, $15, $23, $31));
    };

sfmatrix4fValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            $1,  $9, $17, $25,
            $3, $11, $19, $27,
            $5, $13, $21, $29,
            $7, $15, $23, $31));
    };

sfnodeValue:
    nodeStatement
    | TOK_NULL { SKEL->nullNode(); }

sfrotationValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f($1, $3, $5), $7);
    };

sfstringValue:
    TOK_string
    {
        SKEL->addStringValue($1);
    }
    | TOK_Id
    { /* Not VRML conformant */
        SKEL->addStringValue($1);
    }
    | TOK_hex
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    };

sftimeValue:
    double
    {
        SKEL->addTimeValue($1);
    };

sfvec2dValue:
    double { SKEL->beginValue(); }
    double
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d($1, $3));
    };

sfvec2fValue:
    float { SKEL->beginValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f($1, $3));
    };

sfvec3dValue:
    double { SKEL->beginValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d($1, $3, $5));
    };

sfvec3fValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f($1, $3, $5));
    };

sfvec4dValue:
    double { SKEL->beginValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    double { SKEL->appendValue(); }
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d($1, $3, $5, $7));
    };

sfvec4fValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f($1, $3, $5, $7));
    };

mfboolValue:
    sfboolValue
    | '[' sfboolValues ']';

sfboolValues:
    sfboolValues sfboolValue
    | /* empty */;

mfcolorValue:
    sfcolorValue
    | '[' sfcolorValues ']';

sfcolorValues:
    sfcolorValues sfcolorValue
    | /* empty */;

mfcolorRGBAValue:
    sfcolorRGBAValue
    | '[' sfcolorRGBAValues ']';

sfcolorRGBAValues:
    sfcolorRGBAValues sfcolorRGBAValue
    | /* empty */;

mfdoubleValue:
    sfdoubleValue
    | '[' sfdoubleValues ']';

sfdoubleValues:
    sfdoubleValues sfdoubleValue
    | /* empty */;

mffloatValue:
    sffloatValue
    | '[' sffloatValues ']';

sffloatValues:
    sffloatValues sffloatValue
    | /* empty */;

mfimageValue:
    sfimageValue
    | '[' sfimageValues ']';

sfimageValues:
    sfimageValues sfimageValue
    | /* empty */;

mfint32Value:
    sfint32Value
    | '[' sfint32Values ']';

sfint32Values:
    sfint32Values sfint32Value
    | /* empty */;

mfmatrix3dValue:
    sfmatrix3dValue
    | '[' sfmatrix3dValues ']';

sfmatrix3dValues:
    sfmatrix3dValues sfmatrix3dValue
    | /* empty */;

mfmatrix3fValue:
    sfmatrix3fValue
    | '[' sfmatrix3fValues ']';

sfmatrix3fValues:
    sfmatrix3fValues sfmatrix3fValue
    | /* empty */;

mfmatrix4dValue:
    sfmatrix4dValue
    | '[' sfmatrix4dValues ']';

sfmatrix4dValues:
    sfmatrix4dValues sfmatrix4dValue
    | /* empty */;

mfmatrix4fValue:
    sfmatrix4fValue
    | '[' sfmatrix4fValues ']';

sfmatrix4fValues:
    sfmatrix4fValues sfmatrix4fValue
    | /* empty */;

mfnodeValue:
    sfnodeValue
    | '[' sfnodeValues ']';

sfnodeValues:
    sfnodeValues sfnodeValue
    | /* empty */;

mfrotationValue:
    sfrotationValue
    | '[' sfrotationValues ']';

sfrotationValues:
    sfrotationValues sfrotationValue
    | /* empty */;

mfstringValue:
    sfstringValue
    | '[' sfstringValues ']';

sfstringValues:
    sfstringValues sfstringValue
    | /* empty */;

mftimeValue:
    sftimeValue
    | '[' sftimeValues ']';

sftimeValues:
    sftimeValues sftimeValue
    | /* empty */;

mfvec2dValue:
    sfvec2dValue
    | '[' sfvec2dValues ']';

sfvec2dValues:
    sfvec2dValues sfvec2dValue
    | /* empty */;

mfvec2fValue:
    sfvec2fValue
    | '[' sfvec2fValues ']';

sfvec2fValues:
    sfvec2fValues sfvec2fValue
    | /* empty */;

mfvec3dValue:
    sfvec3dValue
    | '[' sfvec3dValues ']';

sfvec3dValues:
    sfvec3dValues sfvec3dValue
    | /* empty */;

mfvec3fValue:
    sfvec3fValue
    | '[' sfvec3fValues ']';

sfvec3fValues:
    sfvec3fValues sfvec3fValue
    | /* empty */;

mfvec4dValue:
    sfvec4dValue
    | '[' sfvec4dValues ']';

sfvec4dValues:
    sfvec4dValues sfvec4dValue
    | /* empty */;

mfvec4fValue:
    sfvec4fValue
    | '[' sfvec4fValues ']';

sfvec4fValues:
    sfvec4fValues sfvec4fValue
    | /* empty */;

/* The following types are not VRML conformant */

sfcolor4iValue:
    int32 { SKEL->beginValue(); }
    int32 { SKEL->appendValue(); }
    int32 { SKEL->appendValue(); }
    int32
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>($1), static_cast<UInt8>($3),
                                       static_cast<UInt8>($5), static_cast<UInt8>($7)));
    };

sfpnt2fValue:
    float { SKEL->beginValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f($1, $3));
    };

sfpnt3fValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f($1, $3, $5));
    };

sfpnt4fValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f($1, $3, $5, $7));
    };

sfplaneValue:
    float { SKEL->beginValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f($1, $3, $5), $7));
    };

sfVolumeValue:
    int32 { SKEL->beginValue();  }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float { SKEL->appendValue(); }
    float
    {
        SKEL->appendValue();
        BoxVolume bv($3, $5, $7, $9, $11, $13);
        
        bv.setState($1);

        SKEL->addVolumeValue(bv);
    }

sfvec2iValue:
    int32 { SKEL->beginValue(); }
    int32
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i($1, $3));
    };

mfcolor4iValue:
    sfcolor4iValue
    | '[' sfcolor4iValues ']';

sfcolor4iValues:
    sfcolor4iValues sfcolor4iValue
    | /* empty */;

mfpnt2fValue:
    sfpnt2fValue
    | '[' sfpnt2fValues ']';

sfpnt2fValues:
    sfpnt2fValues sfpnt2fValue
    | /* empty */;

mfpnt3fValue:
    sfpnt3fValue
    | '[' sfpnt3fValues ']';

sfpnt3fValues:
    sfpnt3fValues sfpnt3fValue
    | /* empty */;

mfpnt4fValue:
    sfpnt4fValue
    | '[' sfpnt4fValues ']';

sfpnt4fValues:
    sfpnt4fValues sfpnt4fValue
    | /* empty */;

mfplaneValue:
    sfplaneValue
    | '[' sfplaneValues ']';

sfplaneValues:
    sfplaneValues sfplaneValue
    | /* empty */;

mfvec2iValue:
    sfvec2iValue
    | '[' sfvec2iValues ']';

sfvec2iValues:
    sfvec2iValues sfvec2iValue
    | /* empty */;

%%

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}
