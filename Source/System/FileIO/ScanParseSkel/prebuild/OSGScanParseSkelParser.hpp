/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP_INCLUDED
# define YY_OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int OSGScanParseSkel_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_HEADER = 258,
    TOK_PROFILE = 259,
    TOK_COMPONENT = 260,
    TOK_META = 261,
    TOK_PROTO = 262,
    TOK_EXTERNPROTO = 263,
    TOK_IS = 264,
    TOK_DEF = 265,
    TOK_USE = 266,
    TOK_ROUTE = 267,
    TOK_TO = 268,
    TOK_IMPORT = 269,
    TOK_EXPORT = 270,
    TOK_AS = 271,
    TOK_eventIn = 272,
    TOK_eventOut = 273,
    TOK_exposedField = 274,
    TOK_field = 275,
    TOK_MFBool = 276,
    TOK_MFColor = 277,
    TOK_MFColorRGBA = 278,
    TOK_MFDouble = 279,
    TOK_MFFloat = 280,
    TOK_MFImage = 281,
    TOK_MFInt32 = 282,
    TOK_MFMatrix3d = 283,
    TOK_MFMatrix3f = 284,
    TOK_MFMatrix4d = 285,
    TOK_MFMatrix4f = 286,
    TOK_MFNode = 287,
    TOK_MFRotation = 288,
    TOK_MFString = 289,
    TOK_MFTime = 290,
    TOK_MFVec2d = 291,
    TOK_MFVec2f = 292,
    TOK_MFVec3d = 293,
    TOK_MFVec3f = 294,
    TOK_MFVec4d = 295,
    TOK_MFVec4f = 296,
    TOK_SFBool = 297,
    TOK_SFColor = 298,
    TOK_SFColorRGBA = 299,
    TOK_SFDouble = 300,
    TOK_SFFloat = 301,
    TOK_SFImage = 302,
    TOK_SFInt32 = 303,
    TOK_SFMatrix3d = 304,
    TOK_SFMatrix3f = 305,
    TOK_SFMatrix4d = 306,
    TOK_SFMatrix4f = 307,
    TOK_SFNode = 308,
    TOK_SFRotation = 309,
    TOK_SFString = 310,
    TOK_SFTime = 311,
    TOK_SFVec2d = 312,
    TOK_SFVec2f = 313,
    TOK_SFVec3d = 314,
    TOK_SFVec3f = 315,
    TOK_SFVec4d = 316,
    TOK_SFVec4f = 317,
    TOK_MFColor4i = 318,
    TOK_MFPnt2f = 319,
    TOK_MFPnt3f = 320,
    TOK_MFPnt4f = 321,
    TOK_MFPlane = 322,
    TOK_SFColor4i = 323,
    TOK_SFPnt2f = 324,
    TOK_SFPnt3f = 325,
    TOK_SFPnt4f = 326,
    TOK_SFPlane = 327,
    TOK_SFVolume = 328,
    TOK_SFVec2i = 329,
    TOK_SFVec3i = 330,
    TOK_MFVec2i = 331,
    TOK_hex = 332,
    TOK_int32 = 333,
    TOK_double = 334,
    TOK_string = 335,
    TOK_bool = 336,
    TOK_NULL = 337,
    TOK_Id = 338,
    TOK_ImageFinished = 339,
    TOK_Error = 340,
    TOK_ClusterLocal = 341,
    TOK_ThreadLocal = 342
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 41 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy" /* yacc.c:1909  */

    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;

#line 150 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int OSGScanParseSkel_parse (void *pSkel);

#endif /* !YY_OSGSCANPARSESKEL_HOME_GERRIT_PROJECTS_OPENSG_SVN_OPENSG_BUILD_BUILD_OSGSYSTEM_OSGSCANPARSESKELPARSER_HPP_INCLUDED  */
