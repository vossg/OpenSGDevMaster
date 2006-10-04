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

%{

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 111 810)
#endif

#define YY_NEVER_INTERACTIVE 1

#include "OSGScanParseLexer.h"

//OSG_BEGIN_NAMESPACE

#ifdef __sgi
#pragma set woff 1174,1552,1110,1209
#endif

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 279 111 )
#endif

// This function removes leading and trailing quotes from strings
// as well as the escape sequences \\ and \"
static char *stripEscapes(char *s)
{
    char *src = s + 1, *dst = s;
    while (true)
    {
        char c = *src++;
        if ((c == '\\') && ((*src == '\\') || (*src == '"')))
            c = *src++;
        else if (c == '"')
            break;
        *dst++ = c;
    }
    *dst = '\0';
    return s;
}

%}

%option yyclass="OSGScanParseLexer"
%option noyywrap
%option yylineno

%s NODE
%s HEADER

hex         [+\-]?0[xX][0-9a-fA-F]+
int32       [+\-]?[0-9]+
double      [+\-]?((([0-9]+(\.)?)|([0-9]*\.[0-9]+))([eE][+\-]?[0-9]+)?)
string      \"([^\\"]|(\\(.|\n)))*\"
    /* Not VRML conformant */
IdFirstChar [^\x00-\x19 "#'+,\-.0-9[\\\]{}\x7f]
    /* Not VRML conformant */
IdRestChar  [^\x00-\x19 "#',.[\\\]{}\x7f]
Id          {IdFirstChar}{IdRestChar}*
comment     #.*
ws          [\r\n \t,]|{comment}
utf8bom     \xef\xbb\xbf

%%

%{
    if (expectToken != 0)
    {
        int tmp = expectToken;
        expectToken = 0;
        return tmp;
    }
%}

<INITIAL>{utf8bom} BEGIN(HEADER);
<INITIAL,HEADER>[\r\n \t]+ BEGIN(HEADER);
<INITIAL,HEADER>{comment} BEGIN(NODE); lvalp->stringVal = yytext; return TOK_HEADER;

PROFILE   BEGIN(NODE); return TOK_PROFILE;
COMPONENT BEGIN(NODE); return TOK_COMPONENT;
META      BEGIN(NODE); return TOK_META;

PROTO       BEGIN(NODE); return TOK_PROTO;
EXTERNPROTO BEGIN(NODE); return TOK_EXTERNPROTO;
IS          BEGIN(NODE); return TOK_IS;

DEF BEGIN(NODE); return TOK_DEF;
USE BEGIN(NODE); return TOK_USE;

ROUTE BEGIN(NODE); return TOK_ROUTE;
TO    BEGIN(NODE); return TOK_TO;

IMPORT BEGIN(NODE); return TOK_IMPORT;
EXPORT BEGIN(NODE); return TOK_EXPORT;
AS     BEGIN(NODE); return TOK_AS;

eventIn        BEGIN(NODE); return TOK_eventIn;
inputOnly      BEGIN(NODE); return TOK_eventIn;
eventOut       BEGIN(NODE); return TOK_eventOut;
outputOnly     BEGIN(NODE); return TOK_eventOut;
exposedField   BEGIN(NODE); return TOK_exposedField;
inputOutput    BEGIN(NODE); return TOK_exposedField;
field          BEGIN(NODE); return TOK_field;
initializeOnly BEGIN(NODE); return TOK_field;

MFBool      BEGIN(NODE); lvalp->intVal = TOK_MFBool; return TOK_MFBool;
MFColor     BEGIN(NODE); lvalp->intVal = TOK_MFColor; return TOK_MFColor;
MFColorRGBA BEGIN(NODE); lvalp->intVal = TOK_MFColorRGBA; return TOK_MFColorRGBA;
MFDouble    BEGIN(NODE); lvalp->intVal = TOK_MFDouble; return TOK_MFDouble;
MFFloat     BEGIN(NODE); lvalp->intVal = TOK_MFFloat; return TOK_MFFloat;
MFImage     BEGIN(NODE); lvalp->intVal = TOK_MFImage; return TOK_MFImage;
MFInt32     BEGIN(NODE); lvalp->intVal = TOK_MFInt32; return TOK_MFInt32;
MFMatrix3d  BEGIN(NODE); lvalp->intVal = TOK_MFMatrix3d; return TOK_MFMatrix3d;
MFMatrix3f  BEGIN(NODE); lvalp->intVal = TOK_MFMatrix3f; return TOK_MFMatrix3f;
MFMatrix4d  BEGIN(NODE); lvalp->intVal = TOK_MFMatrix4d; return TOK_MFMatrix4d;
MFMatrix4f  BEGIN(NODE); lvalp->intVal = TOK_MFMatrix4f; return TOK_MFMatrix4f;
MFNode      BEGIN(NODE); lvalp->intVal = TOK_MFNode; return TOK_MFNode;
MFRotation  BEGIN(NODE); lvalp->intVal = TOK_MFRotation; return TOK_MFRotation;
MFString    BEGIN(NODE); lvalp->intVal = TOK_MFString; return TOK_MFString;
MFTime      BEGIN(NODE); lvalp->intVal = TOK_MFTime; return TOK_MFTime;
MFVec2d     BEGIN(NODE); lvalp->intVal = TOK_MFVec2d; return TOK_MFVec2d;
MFVec2f     BEGIN(NODE); lvalp->intVal = TOK_MFVec2f; return TOK_MFVec2f;
MFVec3d     BEGIN(NODE); lvalp->intVal = TOK_MFVec3d; return TOK_MFVec3d;
MFVec3f     BEGIN(NODE); lvalp->intVal = TOK_MFVec3f; return TOK_MFVec3f;
MFVec4d     BEGIN(NODE); lvalp->intVal = TOK_MFVec4d; return TOK_MFVec4d;
MFVec4f     BEGIN(NODE); lvalp->intVal = TOK_MFVec4f; return TOK_MFVec4f;
SFBool      BEGIN(NODE); lvalp->intVal = TOK_SFBool; return TOK_SFBool;
SFColor     BEGIN(NODE); lvalp->intVal = TOK_SFColor; return TOK_SFColor;
SFColorRGBA BEGIN(NODE); lvalp->intVal = TOK_SFColorRGBA; return TOK_SFColorRGBA;
SFDouble    BEGIN(NODE); lvalp->intVal = TOK_SFDouble; return TOK_SFDouble;
SFFloat     BEGIN(NODE); lvalp->intVal = TOK_SFFloat; return TOK_SFFloat;
SFImage     BEGIN(NODE); lvalp->intVal = TOK_SFImage; return TOK_SFImage;
SFInt32     BEGIN(NODE); lvalp->intVal = TOK_SFInt32; return TOK_SFInt32;
SFMatrix3d  BEGIN(NODE); lvalp->intVal = TOK_SFMatrix3d; return TOK_SFMatrix3d;
SFMatrix3f  BEGIN(NODE); lvalp->intVal = TOK_SFMatrix3f; return TOK_SFMatrix3f;
SFMatrix4d  BEGIN(NODE); lvalp->intVal = TOK_SFMatrix4d; return TOK_SFMatrix4d;
SFMatrix4f  BEGIN(NODE); lvalp->intVal = TOK_SFMatrix4f; return TOK_SFMatrix4f;
SFNode      BEGIN(NODE); lvalp->intVal = TOK_SFNode; return TOK_SFNode;
SFRotation  BEGIN(NODE); lvalp->intVal = TOK_SFRotation; return TOK_SFRotation;
SFString    BEGIN(NODE); lvalp->intVal = TOK_SFString; return TOK_SFString;
SFTime      BEGIN(NODE); lvalp->intVal = TOK_SFTime; return TOK_SFTime;
SFVec2d     BEGIN(NODE); lvalp->intVal = TOK_SFVec2d; return TOK_SFVec2d;
SFVec2f     BEGIN(NODE); lvalp->intVal = TOK_SFVec2f; return TOK_SFVec2f;
SFVec3d     BEGIN(NODE); lvalp->intVal = TOK_SFVec3d; return TOK_SFVec3d;
SFVec3f     BEGIN(NODE); lvalp->intVal = TOK_SFVec3f; return TOK_SFVec3f;
SFVec4d     BEGIN(NODE); lvalp->intVal = TOK_SFVec4d; return TOK_SFVec4d;
SFVec4f     BEGIN(NODE); lvalp->intVal = TOK_SFVec4f; return TOK_SFVec4f;
    /* The following types are not VRML conformant */
MFColor4f   BEGIN(NODE); lvalp->intVal = TOK_MFColorRGBA; return TOK_MFColorRGBA;
MFColor4i   BEGIN(NODE); lvalp->intVal = TOK_MFColor4i; return TOK_MFColor4i;
MFColor3f   BEGIN(NODE); lvalp->intVal = TOK_MFColor; return TOK_MFColor;
MFMatrix    BEGIN(NODE); lvalp->intVal = TOK_MFMatrix4f; return TOK_MFMatrix4f;
MFPnt2f     BEGIN(NODE); lvalp->intVal = TOK_MFPnt2f; return TOK_MFPnt2f;
MFPnt3f     BEGIN(NODE); lvalp->intVal = TOK_MFPnt3f; return TOK_MFPnt3f;
MFPnt4f     BEGIN(NODE); lvalp->intVal = TOK_MFPnt4f; return TOK_MFPnt4f;
MFPlane     BEGIN(NODE); lvalp->intVal = TOK_MFPlane; return TOK_MFPlane;
SFColor4f   BEGIN(NODE); lvalp->intVal = TOK_SFColorRGBA; return TOK_SFColorRGBA;
SFColor4i   BEGIN(NODE); lvalp->intVal = TOK_SFColor4i; return TOK_SFColor4i;
SFColor3f   BEGIN(NODE); lvalp->intVal = TOK_SFColor; return TOK_SFColor;
SFMatrix    BEGIN(NODE); lvalp->intVal = TOK_SFMatrix4f; return TOK_SFMatrix4f;
SFPnt2f     BEGIN(NODE); lvalp->intVal = TOK_SFPnt2f; return TOK_SFPnt2f;
SFPnt3f     BEGIN(NODE); lvalp->intVal = TOK_SFPnt3f; return TOK_SFPnt3f;
SFPnt4f     BEGIN(NODE); lvalp->intVal = TOK_SFPnt4f; return TOK_SFPnt4f;
SFPlane     BEGIN(NODE); lvalp->intVal = TOK_SFPlane; return TOK_SFPlane;
SFVolume    BEGIN(NODE); lvalp->intVal = TOK_SFVolume; return TOK_SFVolume;

{hex}                {
                         BEGIN(NODE);
                         lvalp->intVal = strtoul(yytext, 0, 0);
                         if (imageIntsExpected > 0)
                             if ((--imageIntsExpected == 0) || (*yytext == '-')) /* Not VRML conformant */
                             {
                                 imageIntsExpected = 0;
                                 expectToken = TOK_ImageFinished;
                             }
                         return TOK_hex;
                     }
{int32}              {
                         BEGIN(NODE);
                         lvalp->intVal = strtoul(yytext, 0, 0);
                         if (imageIntsExpected > 0)
                             if ((--imageIntsExpected == 0) || (*yytext == '-')) /* Not VRML conformant */
                             {
                                 imageIntsExpected = 0;
                                 expectToken = TOK_ImageFinished;
                             }
                         return TOK_int32;
                     }
{double}             BEGIN(NODE); lvalp->doubleVal = strtod(yytext, 0); return TOK_double;
{string}             BEGIN(NODE); lvalp->stringVal = stripEscapes(yytext); return TOK_string;
    /* Not VRML conformant */
[Tt][Rr][Uu][Ee]     BEGIN(NODE); lvalp->boolVal = true; return TOK_bool;
    /* Not VRML conformant */
[Ff][Aa][Ll][Ss][Ee] BEGIN(NODE); lvalp->boolVal = false; return TOK_bool;
NULL                 BEGIN(NODE); return TOK_NULL;
{Id}                 BEGIN(NODE); lvalp->stringVal = yytext; return TOK_Id;

"{" BEGIN(NODE); return '{';
"}" BEGIN(NODE); return '}';
"[" BEGIN(NODE); return '[';
"]" BEGIN(NODE); return ']';
"." BEGIN(NODE); return '.';
    /*":" BEGIN(NODE); return ':';*/

<NODE>{ws}+

. return TOK_Error;

%%

//OSG_END_NAMESPACE

#ifdef OSG_WIN32_ICL
#pragma warning (default : 111 810)
#endif
