/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse OSGScanParseSkel_parse
#define yylex   OSGScanParseSkel_lex
#define yyerror OSGScanParseSkel_error
#define yylval  OSGScanParseSkel_lval
#define yychar  OSGScanParseSkel_char
#define yydebug OSGScanParseSkel_debug
#define yynerrs OSGScanParseSkel_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UTF8BOM = 258,
     DEF = 259,
     USE = 260,
     ROUTE = 261,
     PERIOD = 262,
     TO = 263,
     OPENBRACE = 264,
     CLOSEBRACE = 265,
     ID = 266,
     PROTO = 267,
     OPENBRACKET = 268,
     CLOSEBRACKET = 269,
     EXTERNPROTO = 270,
     IS = 271,
     EXPORT = 272,
     IMPORT = 273,
     PROFILE = 274,
     COMPONENT = 275,
     OSG_META = 276,
     AS = 277,
     EVENTIN = 278,
     EVENTOUT = 279,
     EXPOSEDFIELD = 280,
     FIELD = 281,
     SCRIPT = 282,
     SFN_NULL = 283,
     TOK_SFBOOL = 284,
     TOK_SFCOLOR = 285,
     TOK_SFCOLORRGBA = 286,
     TOK_SFDOUBLE = 287,
     TOK_SFFLOAT = 288,
     TOK_SFIMAGE = 289,
     TOK_SFINT32 = 290,
     TOK_SFMATRIX3D = 291,
     TOK_SFMATRIX3F = 292,
     TOK_SFMATRIX4D = 293,
     TOK_SFMATRIX4F = 294,
     TOK_SFNODE = 295,
     TOK_SFROTATION = 296,
     TOK_SFSTRING = 297,
     TOK_SFTIME = 298,
     TOK_SFVEC2D = 299,
     TOK_SFVEC2F = 300,
     TOK_SFVEC3D = 301,
     TOK_SFVEC3F = 302,
     TOK_SFVEC4D = 303,
     TOK_SFVEC4F = 304,
     TOK_MFBOOL = 305,
     TOK_MFCOLOR = 306,
     TOK_MFCOLORRGBA = 307,
     TOK_MFDOUBLE = 308,
     TOK_MFFLOAT = 309,
     TOK_MFIMAGE = 310,
     TOK_MFINT32 = 311,
     TOK_MFMATRIX3D = 312,
     TOK_MFMATRIX3F = 313,
     TOK_MFMATRIX4D = 314,
     TOK_MFMATRIX4F = 315,
     TOK_MFNODE = 316,
     TOK_MFROTATION = 317,
     TOK_MFSTRING = 318,
     TOK_MFTIME = 319,
     TOK_MFVEC2D = 320,
     TOK_MFVEC2F = 321,
     TOK_MFVEC3D = 322,
     TOK_MFVEC3F = 323,
     TOK_MFVEC4D = 324,
     TOK_MFVEC4F = 325,
     Tok_MFBool = 326,
     Tok_MFColor = 327,
     Tok_MFColorRGBA = 328,
     Tok_MFDouble = 329,
     Tok_MFFloat = 330,
     Tok_MFImage = 331,
     Tok_MFInt32 = 332,
     Tok_MFMatrix3d = 333,
     Tok_MFMatrix3f = 334,
     Tok_MFMatrix4d = 335,
     Tok_MFMatrix4f = 336,
     Tok_MFNode = 337,
     Tok_MFRotation = 338,
     Tok_MFString = 339,
     Tok_MFTime = 340,
     Tok_MFVec2d = 341,
     Tok_MFVec2f = 342,
     Tok_MFVec3d = 343,
     Tok_MFVec3f = 344,
     Tok_MFVec4d = 345,
     Tok_MFVec4f = 346,
     Tok_SFBool = 347,
     Tok_SFColor = 348,
     Tok_SFColorRGBA = 349,
     Tok_SFDouble = 350,
     Tok_SFFloat = 351,
     Tok_SFImage = 352,
     Tok_SFInt32 = 353,
     Tok_SFMatrix3d = 354,
     Tok_SFMatrix3f = 355,
     Tok_SFMatrix4d = 356,
     Tok_SFMatrix4f = 357,
     Tok_SFNode = 358,
     Tok_SFRotation = 359,
     Tok_SFString = 360,
     Tok_SFTime = 361,
     Tok_SFVec2d = 362,
     Tok_SFVec2f = 363,
     Tok_SFVec3d = 364,
     Tok_SFVec3f = 365,
     Tok_SFVec4d = 366,
     Tok_SFVec4f = 367,
     TOK_MFCOLOR4I = 368,
     TOK_MFPNT2F = 369,
     TOK_MFPNT3F = 370,
     TOK_MFPNT4F = 371,
     TOK_MFPLANE = 372,
     TOK_SFCOLOR4I = 373,
     TOK_SFPNT2F = 374,
     TOK_SFPNT3F = 375,
     TOK_SFPNT4F = 376,
     TOK_SFPLANE = 377,
     TOK_SFVOLUME = 378,
     Tok_MFColor4i = 379,
     Tok_MFPnt2f = 380,
     Tok_MFPnt3f = 381,
     Tok_MFPnt4f = 382,
     Tok_MFPlane = 383,
     Tok_SFColor4i = 384,
     Tok_SFPnt2f = 385,
     Tok_SFPnt3f = 386,
     Tok_SFPnt4f = 387,
     Tok_SFPlane = 388,
     Tok_SFVolume = 389
   };
#endif
#define UTF8BOM 258
#define DEF 259
#define USE 260
#define ROUTE 261
#define PERIOD 262
#define TO 263
#define OPENBRACE 264
#define CLOSEBRACE 265
#define ID 266
#define PROTO 267
#define OPENBRACKET 268
#define CLOSEBRACKET 269
#define EXTERNPROTO 270
#define IS 271
#define EXPORT 272
#define IMPORT 273
#define PROFILE 274
#define COMPONENT 275
#define OSG_META 276
#define AS 277
#define EVENTIN 278
#define EVENTOUT 279
#define EXPOSEDFIELD 280
#define FIELD 281
#define SCRIPT 282
#define SFN_NULL 283
#define TOK_SFBOOL 284
#define TOK_SFCOLOR 285
#define TOK_SFCOLORRGBA 286
#define TOK_SFDOUBLE 287
#define TOK_SFFLOAT 288
#define TOK_SFIMAGE 289
#define TOK_SFINT32 290
#define TOK_SFMATRIX3D 291
#define TOK_SFMATRIX3F 292
#define TOK_SFMATRIX4D 293
#define TOK_SFMATRIX4F 294
#define TOK_SFNODE 295
#define TOK_SFROTATION 296
#define TOK_SFSTRING 297
#define TOK_SFTIME 298
#define TOK_SFVEC2D 299
#define TOK_SFVEC2F 300
#define TOK_SFVEC3D 301
#define TOK_SFVEC3F 302
#define TOK_SFVEC4D 303
#define TOK_SFVEC4F 304
#define TOK_MFBOOL 305
#define TOK_MFCOLOR 306
#define TOK_MFCOLORRGBA 307
#define TOK_MFDOUBLE 308
#define TOK_MFFLOAT 309
#define TOK_MFIMAGE 310
#define TOK_MFINT32 311
#define TOK_MFMATRIX3D 312
#define TOK_MFMATRIX3F 313
#define TOK_MFMATRIX4D 314
#define TOK_MFMATRIX4F 315
#define TOK_MFNODE 316
#define TOK_MFROTATION 317
#define TOK_MFSTRING 318
#define TOK_MFTIME 319
#define TOK_MFVEC2D 320
#define TOK_MFVEC2F 321
#define TOK_MFVEC3D 322
#define TOK_MFVEC3F 323
#define TOK_MFVEC4D 324
#define TOK_MFVEC4F 325
#define Tok_MFBool 326
#define Tok_MFColor 327
#define Tok_MFColorRGBA 328
#define Tok_MFDouble 329
#define Tok_MFFloat 330
#define Tok_MFImage 331
#define Tok_MFInt32 332
#define Tok_MFMatrix3d 333
#define Tok_MFMatrix3f 334
#define Tok_MFMatrix4d 335
#define Tok_MFMatrix4f 336
#define Tok_MFNode 337
#define Tok_MFRotation 338
#define Tok_MFString 339
#define Tok_MFTime 340
#define Tok_MFVec2d 341
#define Tok_MFVec2f 342
#define Tok_MFVec3d 343
#define Tok_MFVec3f 344
#define Tok_MFVec4d 345
#define Tok_MFVec4f 346
#define Tok_SFBool 347
#define Tok_SFColor 348
#define Tok_SFColorRGBA 349
#define Tok_SFDouble 350
#define Tok_SFFloat 351
#define Tok_SFImage 352
#define Tok_SFInt32 353
#define Tok_SFMatrix3d 354
#define Tok_SFMatrix3f 355
#define Tok_SFMatrix4d 356
#define Tok_SFMatrix4f 357
#define Tok_SFNode 358
#define Tok_SFRotation 359
#define Tok_SFString 360
#define Tok_SFTime 361
#define Tok_SFVec2d 362
#define Tok_SFVec2f 363
#define Tok_SFVec3d 364
#define Tok_SFVec3f 365
#define Tok_SFVec4d 366
#define Tok_SFVec4f 367
#define TOK_MFCOLOR4I 368
#define TOK_MFPNT2F 369
#define TOK_MFPNT3F 370
#define TOK_MFPNT4F 371
#define TOK_MFPLANE 372
#define TOK_SFCOLOR4I 373
#define TOK_SFPNT2F 374
#define TOK_SFPNT3F 375
#define TOK_SFPNT4F 376
#define TOK_SFPLANE 377
#define TOK_SFVOLUME 378
#define Tok_MFColor4i 379
#define Tok_MFPnt2f 380
#define Tok_MFPnt3f 381
#define Tok_MFPnt4f 382
#define Tok_MFPlane 383
#define Tok_SFColor4i 384
#define Tok_SFPnt2f 385
#define Tok_SFPnt3f 386
#define Tok_SFPnt4f 387
#define Tok_SFPlane 388
#define Tok_SFVolume 389




/* Copy the first part of user declarations.  */
#line 38 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define YYLTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_TRIVIAL 1

#define OSGScanParseSkel_error SKEL->handleError

#ifdef WIN32
#include <malloc.h>
#define YYSIZE_T size_t
#endif
#include <OSGScanParseSkelParser.hpp>
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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 411 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   554

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  89
/* YYNRULES -- Number of rules. */
#define YYNRULES  243
/* YYNRULES -- Number of states. */
#define YYNSTATES  329

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   389

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    14,    16,    19,    21,
      24,    26,    29,    32,    34,    37,    39,    40,    45,    47,
      49,    52,    54,    56,    58,    60,    62,    64,    66,    67,
      72,    75,    77,    78,    83,    85,    87,    89,    90,    93,
      95,    97,    99,   108,   110,   112,   116,   118,   120,   123,
     125,   126,   131,   132,   137,   138,   139,   146,   148,   149,
     150,   157,   158,   159,   168,   170,   172,   175,   177,   178,
     183,   184,   189,   190,   195,   196,   201,   202,   203,   204,
     216,   217,   222,   223,   224,   232,   235,   237,   239,   240,
     241,   247,   248,   254,   256,   258,   260,   263,   265,   266,
     271,   272,   277,   280,   281,   282,   287,   290,   292,   293,
     298,   301,   303,   305,   308,   311,   314,   315,   319,   321,
     323,   326,   328,   330,   332,   334,   336,   338,   340,   342,
     344,   346,   348,   350,   352,   354,   356,   358,   360,   362,
     364,   366,   368,   370,   372,   374,   376,   378,   380,   382,
     384,   386,   388,   390,   392,   394,   396,   398,   400,   402,
     404,   406,   408,   410,   412,   414,   416,   418,   420,   422,
     424,   426,   428,   430,   432,   434,   436,   438,   440,   442,
     444,   446,   448,   450,   452,   454,   456,   458,   460,   462,
     464,   466,   468,   470,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   499,   501,   503,
     505,   507,   509,   511,   513,   516,   518,   520,   522,   524,
     526,   528,   530,   532,   534,   536,   538,   540,   542,   544,
     546,   548,   550,   552,   554,   556,   558,   561,   563,   566,
     570,   572,   574,   577
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     136,     0,    -1,     3,   137,    -1,   137,    -1,    -1,    19,
      11,   138,   139,    -1,   139,    -1,   140,   142,    -1,   142,
      -1,   140,   141,    -1,   141,    -1,    20,    11,    -1,   143,
     146,    -1,   146,    -1,   143,   144,    -1,   144,    -1,    -1,
      21,    11,   145,    11,    -1,   147,    -1,   191,    -1,   147,
     148,    -1,   148,    -1,   149,    -1,   153,    -1,   180,    -1,
     186,    -1,   184,    -1,   192,    -1,    -1,     4,   212,   150,
     192,    -1,     5,   212,    -1,   192,    -1,    -1,     4,   212,
     152,   192,    -1,   157,    -1,   170,    -1,   155,    -1,    -1,
     155,   153,    -1,   153,    -1,   213,    -1,    27,    -1,    12,
     156,    13,   160,    14,     9,   158,    10,    -1,   159,    -1,
     191,    -1,   154,   151,   146,    -1,   161,    -1,   191,    -1,
     161,   167,    -1,   167,    -1,    -1,    23,   218,   163,   216,
      -1,    -1,    24,   218,   164,   217,    -1,    -1,    -1,    26,
     218,   165,   214,   166,   219,    -1,   162,    -1,    -1,    -1,
      25,   218,   168,   214,   169,   219,    -1,    -1,    -1,    15,
     213,   171,    13,   173,    14,   172,   190,    -1,   174,    -1,
     191,    -1,   174,   175,    -1,   175,    -1,    -1,    23,   218,
     176,   216,    -1,    -1,    24,   218,   177,   217,    -1,    -1,
      26,   218,   178,   214,    -1,    -1,    25,   218,   179,   214,
      -1,    -1,    -1,    -1,     6,   212,   181,     7,   217,   182,
       8,   212,   183,     7,   216,    -1,    -1,    17,    11,   185,
     189,    -1,    -1,    -1,    18,    11,   187,     7,    11,   188,
     189,    -1,    22,    11,    -1,   191,    -1,   219,    -1,    -1,
      -1,   213,   193,     9,   195,    10,    -1,    -1,    27,   194,
       9,   195,    10,    -1,    28,    -1,   196,    -1,   191,    -1,
     196,   207,    -1,   207,    -1,    -1,    23,   218,   198,   216,
      -1,    -1,    24,   218,   199,   217,    -1,    16,   215,    -1,
      -1,    -1,    26,   218,   202,   214,    -1,    16,   214,    -1,
     219,    -1,    -1,    25,   218,   205,   214,    -1,    16,   214,
      -1,   219,    -1,   208,    -1,   197,   200,    -1,   201,   203,
      -1,   204,   206,    -1,    -1,   214,   209,   210,    -1,   180,
      -1,   153,    -1,    16,   211,    -1,   219,    -1,    11,    -1,
      11,    -1,    11,    -1,    11,    -1,    11,    -1,    11,    -1,
      11,    -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,    82,    -1,    83,    -1,    84,    -1,
      85,    -1,    86,    -1,    87,    -1,    88,    -1,    89,    -1,
      90,    -1,    91,    -1,    92,    -1,    93,    -1,    94,    -1,
      95,    -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,
     100,    -1,   101,    -1,   102,    -1,   103,    -1,   104,    -1,
     105,    -1,   106,    -1,   107,    -1,   108,    -1,   109,    -1,
     110,    -1,   111,    -1,   112,    -1,   124,    -1,   125,    -1,
     126,    -1,   127,    -1,   128,    -1,   129,    -1,   130,    -1,
     131,    -1,   132,    -1,   133,    -1,   134,    -1,    29,    -1,
      30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,
      40,   220,    -1,    41,    -1,    42,    -1,    43,    -1,    44,
      -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,   221,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,   113,    -1,   114,    -1,   115,    -1,
     116,    -1,   117,    -1,   118,    -1,   119,    -1,   120,    -1,
     121,    -1,   122,    -1,   123,    -1,   149,    -1,    16,   211,
      -1,   149,    -1,    16,   211,    -1,    13,   222,    14,    -1,
     223,    -1,   191,    -1,   223,   149,    -1,   149,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   236,   236,   237,   242,   240,   249,   253,   254,   257,
     258,   261,   271,   272,   275,   276,   280,   279,   292,   293,
     296,   297,   300,   301,   302,   303,   304,   307,   309,   308,
     311,   316,   318,   317,   322,   323,   327,   328,   331,   332,
     335,   337,   341,   352,   353,   356,   359,   360,   363,   364,
     369,   368,   382,   381,   395,   397,   394,   410,   412,   414,
     411,   427,   432,   426,   445,   446,   450,   451,   455,   454,
     464,   463,   473,   472,   482,   481,   493,   495,   497,   492,
     512,   510,   529,   534,   527,   550,   554,   557,   560,   563,
     563,   573,   573,   582,   596,   597,   600,   601,   605,   604,
     615,   614,   626,   635,   644,   643,   659,   668,   677,   676,
     693,   703,   720,   721,   723,   725,   731,   730,   752,   753,
     758,   764,   770,   773,   776,   779,   782,   785,   788,   790,
     791,   792,   793,   794,   795,   796,   797,   798,   799,   800,
     801,   802,   803,   804,   805,   806,   807,   808,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     821,   822,   823,   824,   825,   826,   827,   828,   829,   830,
     831,   832,   833,   834,   835,   836,   837,   838,   839,   840,
     841,   842,   846,   847,   848,   849,   850,   851,   852,   853,
     854,   855,   856,   857,   858,   859,   860,   861,   862,   863,
     864,   865,   866,   867,   868,   869,   870,   871,   872,   873,
     874,   875,   876,   877,   878,   879,   880,   881,   882,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     894,   895,   896,   897,   898,   902,   903,   912,   913,   920,
     923,   924,   927,   928
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "UTF8BOM", "DEF", "USE", "ROUTE",
  "PERIOD", "TO", "OPENBRACE", "CLOSEBRACE", "ID", "PROTO", "OPENBRACKET",
  "CLOSEBRACKET", "EXTERNPROTO", "IS", "EXPORT", "IMPORT", "PROFILE",
  "COMPONENT", "OSG_META", "AS", "EVENTIN", "EVENTOUT", "EXPOSEDFIELD",
  "FIELD", "SCRIPT", "SFN_NULL", "TOK_SFBOOL", "TOK_SFCOLOR",
  "TOK_SFCOLORRGBA", "TOK_SFDOUBLE", "TOK_SFFLOAT", "TOK_SFIMAGE",
  "TOK_SFINT32", "TOK_SFMATRIX3D", "TOK_SFMATRIX3F", "TOK_SFMATRIX4D",
  "TOK_SFMATRIX4F", "TOK_SFNODE", "TOK_SFROTATION", "TOK_SFSTRING",
  "TOK_SFTIME", "TOK_SFVEC2D", "TOK_SFVEC2F", "TOK_SFVEC3D", "TOK_SFVEC3F",
  "TOK_SFVEC4D", "TOK_SFVEC4F", "TOK_MFBOOL", "TOK_MFCOLOR",
  "TOK_MFCOLORRGBA", "TOK_MFDOUBLE", "TOK_MFFLOAT", "TOK_MFIMAGE",
  "TOK_MFINT32", "TOK_MFMATRIX3D", "TOK_MFMATRIX3F", "TOK_MFMATRIX4D",
  "TOK_MFMATRIX4F", "TOK_MFNODE", "TOK_MFROTATION", "TOK_MFSTRING",
  "TOK_MFTIME", "TOK_MFVEC2D", "TOK_MFVEC2F", "TOK_MFVEC3D", "TOK_MFVEC3F",
  "TOK_MFVEC4D", "TOK_MFVEC4F", "Tok_MFBool", "Tok_MFColor",
  "Tok_MFColorRGBA", "Tok_MFDouble", "Tok_MFFloat", "Tok_MFImage",
  "Tok_MFInt32", "Tok_MFMatrix3d", "Tok_MFMatrix3f", "Tok_MFMatrix4d",
  "Tok_MFMatrix4f", "Tok_MFNode", "Tok_MFRotation", "Tok_MFString",
  "Tok_MFTime", "Tok_MFVec2d", "Tok_MFVec2f", "Tok_MFVec3d", "Tok_MFVec3f",
  "Tok_MFVec4d", "Tok_MFVec4f", "Tok_SFBool", "Tok_SFColor",
  "Tok_SFColorRGBA", "Tok_SFDouble", "Tok_SFFloat", "Tok_SFImage",
  "Tok_SFInt32", "Tok_SFMatrix3d", "Tok_SFMatrix3f", "Tok_SFMatrix4d",
  "Tok_SFMatrix4f", "Tok_SFNode", "Tok_SFRotation", "Tok_SFString",
  "Tok_SFTime", "Tok_SFVec2d", "Tok_SFVec2f", "Tok_SFVec3d", "Tok_SFVec3f",
  "Tok_SFVec4d", "Tok_SFVec4f", "TOK_MFCOLOR4I", "TOK_MFPNT2F",
  "TOK_MFPNT3F", "TOK_MFPNT4F", "TOK_MFPLANE", "TOK_SFCOLOR4I",
  "TOK_SFPNT2F", "TOK_SFPNT3F", "TOK_SFPNT4F", "TOK_SFPLANE",
  "TOK_SFVOLUME", "Tok_MFColor4i", "Tok_MFPnt2f", "Tok_MFPnt3f",
  "Tok_MFPnt4f", "Tok_MFPlane", "Tok_SFColor4i", "Tok_SFPnt2f",
  "Tok_SFPnt3f", "Tok_SFPnt4f", "Tok_SFPlane", "Tok_SFVolume", "$accept",
  "vrmlScene", "profileStatement", "@1", "componentStatements",
  "componentStatementsRec", "componentStatement", "metaStatements",
  "metaStatementsRec", "metaStatement", "@2", "statementsORempty",
  "statements", "statement", "nodeStatement", "@3", "rootNodeStatement",
  "@4", "protoStatement", "protoStatementsORempty", "protoStatements",
  "protoId", "proto", "protoBodyORempty", "protoBody",
  "interfaceDeclarationsORempty", "interfaceDeclarations",
  "restrictedInterfaceDeclaration", "@5", "@6", "@7", "@8",
  "interfaceDeclaration", "@9", "@10", "externproto", "@11", "@12",
  "externInterfaceDeclarationsORempty", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "@13", "@14", "@15", "@16",
  "routeStatement", "@17", "@18", "@19", "exportStatement", "@20",
  "importStatement", "@21", "@22", "importExportEnd", "URLList", "empty",
  "node", "@23", "@24", "scriptBodyORempty", "scriptBody",
  "resInterfaceDeclarationScriptEvent", "@25", "@26",
  "resInterfaceDeclarationScriptEventEnd",
  "resInterfaceDeclarationScriptField", "@27",
  "resInterafceDeclarationScriptFieldEnd",
  "resInterfaceDeclarationScriptExpField", "@28",
  "resInterafceDeclarationScriptExpFieldEnd", "scriptBodyElement",
  "nodeBodyElement", "@29", "fieldEnd", "generalId", "nodeNameId",
  "nodeTypeId", "fieldId", "eventId", "eventInId", "eventOutId",
  "fieldType", "fieldValue", "sfnodeValue", "mfnodeValue",
  "nodeStatementsORempty", "nodeStatements", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   135,   136,   136,   138,   137,   137,   139,   139,   140,
     140,   141,   142,   142,   143,   143,   145,   144,   146,   146,
     147,   147,   148,   148,   148,   148,   148,   149,   150,   149,
     149,   151,   152,   151,   153,   153,   154,   154,   155,   155,
     156,   156,   157,   158,   158,   159,   160,   160,   161,   161,
     163,   162,   164,   162,   165,   166,   162,   167,   168,   169,
     167,   171,   172,   170,   173,   173,   174,   174,   176,   175,
     177,   175,   178,   175,   179,   175,   181,   182,   183,   180,
     185,   184,   187,   188,   186,   189,   189,   190,   191,   193,
     192,   194,   192,   192,   195,   195,   196,   196,   198,   197,
     199,   197,   200,   200,   202,   201,   203,   203,   205,   204,
     206,   206,   207,   207,   207,   207,   209,   208,   208,   208,
     210,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   220,   220,   221,   221,   221,
     222,   222,   223,   223
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     1,     0,     4,     1,     2,     1,     2,
       1,     2,     2,     1,     2,     1,     0,     4,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       2,     1,     0,     4,     1,     1,     1,     0,     2,     1,
       1,     1,     8,     1,     1,     3,     1,     1,     2,     1,
       0,     4,     0,     4,     0,     0,     6,     1,     0,     0,
       6,     0,     0,     8,     1,     1,     2,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     0,     0,    11,
       0,     4,     0,     0,     7,     2,     1,     1,     0,     0,
       5,     0,     5,     1,     1,     1,     2,     1,     0,     4,
       0,     4,     2,     0,     0,     4,     2,     1,     0,     4,
       2,     1,     1,     2,     2,     2,     0,     3,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     3,
       1,     1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      88,    88,     0,     0,     0,   124,     0,     0,     0,     0,
       0,     0,     0,    91,    93,     0,     3,     6,    88,    10,
       8,    88,    15,    13,    18,    21,    22,    23,    34,    35,
      24,    26,    25,    19,    27,    89,     2,   123,    28,    30,
      76,    41,     0,    40,    61,    80,    82,     4,    11,    16,
       0,     1,     9,     7,    14,    12,    20,     0,     0,     0,
      88,     0,    88,     0,    88,     0,    88,    88,    29,     0,
       0,     0,     0,     0,     0,    46,    57,    49,    47,    88,
       0,    81,    86,     0,     5,    17,   125,     0,     0,     0,
       0,   119,   118,    95,     0,    94,   103,     0,     0,    97,
     112,   116,     0,   128,    77,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,    50,    52,
      58,    54,     0,    48,     0,     0,     0,     0,     0,    64,
      67,    65,    85,    83,    98,   100,   108,   104,    92,    96,
       0,   113,     0,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,     0,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,     0,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   114,   107,     0,   115,
     111,     0,    90,     0,     0,     0,     0,     0,    37,    68,
      70,    74,    72,    62,    66,    88,     0,     0,     0,     0,
     126,   102,   106,     0,   235,   193,    88,     0,   237,   214,
     110,     0,   117,   121,     0,   127,    51,    53,    59,    55,
      39,     0,    36,     0,    43,    44,     0,     0,     0,     0,
       0,    84,    99,   101,   109,   105,   122,   236,   243,   241,
       0,   240,   238,   120,    78,     0,     0,     0,    88,    31,
      38,    42,    69,    71,    75,    73,    63,    87,   239,   242,
       0,    60,    56,    32,    45,     0,     0,    79,    33
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,    15,    16,    64,    17,    18,    19,    20,    21,    22,
      65,    23,    24,    25,    26,    58,   308,   326,    27,   281,
     282,    42,    28,   283,   284,    74,    75,    76,   244,   245,
     247,   306,    77,   246,   305,    29,    61,   290,   168,   169,
     170,   286,   287,   289,   288,    30,    59,   243,   320,    31,
      62,    32,    63,   255,    81,   316,    33,    34,    57,    50,
      94,    95,    96,   256,   257,   181,    97,   259,   236,    98,
     258,   239,    99,   100,   241,   272,   297,    38,    35,   101,
     261,   276,   104,   158,   237,   265,   269,   300,   301
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -251
static const short int yypact[] =
{
     136,   154,     0,     0,     0,  -251,    67,     1,    14,    15,
      20,    66,    88,  -251,  -251,   102,  -251,  -251,   270,  -251,
    -251,   414,  -251,  -251,   520,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,    90,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
      10,  -251,  -251,  -251,  -251,  -251,  -251,    95,     2,   103,
      72,   100,   110,   126,   270,   123,   528,   528,  -251,   125,
     389,   389,   389,   389,   124,    72,  -251,  -251,  -251,    92,
     132,  -251,  -251,   133,  -251,  -251,  -251,   389,   389,   389,
     389,  -251,  -251,  -251,   127,   528,   129,     6,   199,  -251,
    -251,  -251,   139,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,   143,  -251,   389,   389,   389,   389,   147,    92,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
     151,  -251,   156,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,   417,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,   189,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,   156,  -251,
    -251,   294,  -251,   160,   159,   125,   156,   156,     8,  -251,
    -251,  -251,  -251,  -251,  -251,   110,   159,   125,   156,   156,
    -251,  -251,  -251,   165,  -251,  -251,   273,   165,  -251,  -251,
    -251,   165,  -251,  -251,     0,  -251,  -251,  -251,  -251,  -251,
    -251,     5,    70,   167,  -251,  -251,   159,   125,   156,   156,
     336,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
     164,   273,  -251,  -251,  -251,   336,   336,     0,   520,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
     172,  -251,  -251,  -251,  -251,   159,     2,  -251,  -251
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -251,  -251,   179,  -251,   128,  -251,   170,   171,  -251,   169,
    -251,   -19,  -251,   173,  -187,  -251,  -251,  -251,   -61,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,   116,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
      29,  -251,  -251,  -251,  -251,    17,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,   -56,  -251,   -52,   -54,  -251,  -251,
     134,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,   109,  -251,  -251,  -251,  -250,    -3,    80,  -158,
    -251,  -175,  -152,    19,   -95,  -251,  -251,  -251,  -251
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -89
static const short int yytable[] =
{
      39,    40,    55,   240,    68,    91,    91,   264,    78,   307,
      82,    37,     5,     5,    93,    93,     5,   302,   -88,    66,
       6,   303,   182,     7,   262,    45,    46,   171,   268,    13,
      14,    47,    13,    14,    91,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,    48,     5,   298,
     270,   292,     6,    92,    92,     7,    43,    44,   278,   279,
     159,   160,   161,   277,    41,    70,    71,    72,    73,    49,
     294,   295,    51,    60,    67,   293,   174,   175,   176,   177,
      69,   312,    92,    79,   319,   164,   165,   166,   167,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     314,   315,    80,    83,    85,   313,   103,   178,   162,     1,
       2,     3,     4,   172,   173,   180,   273,     5,     6,   242,
     327,     7,   248,     8,     9,    10,    11,    12,     2,     3,
       4,   253,   260,    13,    14,     5,     6,    86,   274,     7,
     275,     8,     9,    10,    11,    12,   296,   311,   318,   325,
      36,    13,    14,   249,   250,   251,   252,   280,    52,    53,
      54,   163,    84,     2,     3,   317,   285,    56,   254,   291,
       5,   102,   266,    82,   179,   267,     0,     0,     0,     0,
     321,   322,     0,     0,   299,   238,    13,    14,     0,     0,
       0,   310,     0,     0,     0,     0,     0,   309,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
       0,   304,   328,     0,     2,     3,     4,     2,     3,     0,
       0,     5,     6,     0,     5,     7,     0,     8,     9,   324,
      11,    12,     0,     0,     0,     0,     0,    13,    14,     0,
      13,    14,     0,     0,   323,     0,     0,     0,     0,     0,
     271,     0,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,     2,     3,
       4,     2,     3,     0,     0,     5,     6,     0,     5,     7,
       0,     8,     9,   263,     0,    12,     0,     0,     0,     0,
       0,    13,    14,     0,    13,    14,     0,     0,     0,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,     2,     3,     4,     0,     0,     0,
       0,     5,     6,     0,     4,     7,     0,     8,     9,    86,
       6,     0,     0,     7,     0,     0,     0,    13,    14,     0,
       0,    87,    88,    89,    90
};

static const short int yycheck[] =
{
       3,     4,    21,    98,    58,    66,    67,   194,    60,     4,
      62,    11,    11,    11,    66,    67,    11,   267,    10,     9,
      12,   271,    16,    15,   182,    11,    11,    79,   215,    27,
      28,    11,    27,    28,    95,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    11,    11,   266,
     238,   256,    12,    66,    67,    15,     6,     7,   246,   247,
      71,    72,    73,   245,    27,    23,    24,    25,    26,    11,
     258,   259,     0,    13,     9,   257,    87,    88,    89,    90,
       7,   286,    95,    13,   301,    23,    24,    25,    26,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     288,   289,    22,     7,    11,   287,    11,    10,    14,     3,
       4,     5,     6,    11,    11,    16,   241,    11,    12,    10,
     325,    15,     9,    17,    18,    19,    20,    21,     4,     5,
       6,    14,    11,    27,    28,    11,    12,    11,     8,    15,
      11,    17,    18,    19,    20,    21,    11,    10,    14,     7,
       1,    27,    28,   164,   165,   166,   167,   248,    18,    18,
      21,    75,    64,     4,     5,   290,   248,    24,   169,   255,
      11,    67,    13,   255,    95,    16,    -1,    -1,    -1,    -1,
     305,   306,    -1,    -1,   266,    16,    27,    28,    -1,    -1,
      -1,   282,    -1,    -1,    -1,    -1,    -1,   281,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,   274,   326,    -1,     4,     5,     6,     4,     5,    -1,
      -1,    11,    12,    -1,    11,    15,    -1,    17,    18,   308,
      20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,
      27,    28,    -1,    -1,   307,    -1,    -1,    -1,    -1,    -1,
      16,    -1,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,     4,     5,
       6,     4,     5,    -1,    -1,    11,    12,    -1,    11,    15,
      -1,    17,    18,    16,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    27,    28,    -1,    27,    28,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     4,     5,     6,    -1,    -1,    -1,
      -1,    11,    12,    -1,     6,    15,    -1,    17,    18,    11,
      12,    -1,    -1,    15,    -1,    -1,    -1,    27,    28,    -1,
      -1,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,     6,    11,    12,    15,    17,    18,
      19,    20,    21,    27,    28,   136,   137,   139,   140,   141,
     142,   143,   144,   146,   147,   148,   149,   153,   157,   170,
     180,   184,   186,   191,   192,   213,   137,    11,   212,   212,
     212,    27,   156,   213,   213,    11,    11,    11,    11,    11,
     194,     0,   141,   142,   144,   146,   148,   193,   150,   181,
      13,   171,   185,   187,   138,   145,     9,     9,   192,     7,
      23,    24,    25,    26,   160,   161,   162,   167,   191,    13,
      22,   189,   191,     7,   139,    11,    11,    23,    24,    25,
      26,   153,   180,   191,   195,   196,   197,   201,   204,   207,
     208,   214,   195,    11,   217,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   218,   218,
     218,   218,    14,   167,    23,    24,    25,    26,   173,   174,
     175,   191,    11,    11,   218,   218,   218,   218,    10,   207,
      16,   200,    16,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   203,   219,    16,   206,
     219,   209,    10,   182,   163,   164,   168,   165,     9,   218,
     218,   218,   218,    14,   175,   188,   198,   199,   205,   202,
      11,   215,   214,    16,   149,   220,    13,    16,   149,   221,
     214,    16,   210,   219,     8,    11,   216,   217,   214,   214,
     153,   154,   155,   158,   159,   191,   176,   177,   179,   178,
     172,   189,   216,   217,   214,   214,    11,   211,   149,   191,
     222,   223,   211,   211,   212,   169,   166,     4,   151,   192,
     153,    10,   216,   217,   214,   214,   190,   219,    14,   149,
     183,   219,   219,   212,   146,     7,   152,   216,   192
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  yyvsp[0] = yylval;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 242 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                       if(SKEL != NULL)
                       {
                           SKEL->profileElement(SKELTEXT);
                       }
                   ;}
    break;

  case 11:
#line 263 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                         if(SKEL != NULL)
                         {
                             SKEL->componentElement(SKELTEXT);
                         }
                     ;}
    break;

  case 16:
#line 280 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 17:
#line 282 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                    if(SKEL != NULL)
                    {
                        SKEL->metaElement(szName1, SKELTEXT);
                    }
                    freeName(szName1);
                ;}
    break;

  case 28:
#line 309 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 30:
#line 312 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); ;}
    break;

  case 32:
#line 318 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 40:
#line 335 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 41:
#line 337 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 42:
#line 348 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL) 
			SKEL->endProto(); ;}
    break;

  case 50:
#line 369 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 51:
#line 371 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                              {
                                               SKEL->beginEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); ;}
    break;

  case 52:
#line 382 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 53:
#line 384 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                              {
                                               SKEL->beginEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); ;}
    break;

  case 54:
#line 395 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 55:
#line 397 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->expectType(nextType); 
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                              freeName(szName1); ;}
    break;

  case 56:
#line 404 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = 0; 
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             ;}
    break;

  case 58:
#line 412 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                              SKELTEXT); ;}
    break;

  case 59:
#line 414 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->expectType(nextType);  
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 60:
#line 421 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = 0; 
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); ;}
    break;

  case 61:
#line 427 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL) 
                             SKEL->beginExternProto(SKELTEXT); ;}
    break;

  case 62:
#line 432 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProtoInterface(); 

                 SKEL->expectType(TOK_MFSTRING); 
              ;}
    break;

  case 63:
#line 439 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProto(); 
              ;}
    break;

  case 68:
#line 455 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 69:
#line 457 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 70:
#line 464 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 71:
#line 466 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                          freeName(szName1); ;}
    break;

  case 72:
#line 473 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 73:
#line 475 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 74:
#line 482 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 75:
#line 484 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 76:
#line 493 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 77:
#line 495 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName2, SKELTEXT); ;}
    break;

  case 78:
#line 497 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName3, SKELTEXT); ;}
    break;

  case 79:
#line 499 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                SKEL->addRoute(szName1, 
                                               szName2,
                                               szName3,
                                               SKELTEXT);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            ;}
    break;

  case 80:
#line 512 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                      setName(szName1, SKELTEXT);
                  ;}
    break;

  case 81:
#line 516 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                      if(SKEL != NULL)
                      {
                          SKEL->exportElement(szName1, szName2);
                      }

                      freeName(szName1);
                      freeName(szName2);
                  ;}
    break;

  case 82:
#line 529 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                      setName(szName1, SKELTEXT);
                  ;}
    break;

  case 83:
#line 534 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                      setName(szName3, SKELTEXT);
                  ;}
    break;

  case 84:
#line 538 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                      if(SKEL != NULL)
                      {
                          SKEL->importElement(szName1, szName3, szName2);
                      }
                    
                      freeName(szName1);
                      freeName(szName2);
                      freeName(szName3);
                  ;}
    break;

  case 85:
#line 551 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                        setName(szName2, SKELTEXT);
                  ;}
    break;

  case 89:
#line 563 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;}
    break;

  case 90:
#line 571 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 91:
#line 573 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;}
    break;

  case 92:
#line 580 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 93:
#line 582 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                    SKEL->nullNode(); ;}
    break;

  case 98:
#line 605 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 99:
#line 607 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                 freeName(szName1); ;}
    break;

  case 100:
#line 615 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 101:
#line 617 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                  freeName(szName1); ;}
    break;

  case 102:
#line 627 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl(); 
                                          }
                                        ;}
    break;

  case 103:
#line 635 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl(); 
                                            }
                                        ;}
    break;

  case 104:
#line 644 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                         SKELTEXT);
                                               ;}
    break;

  case 105:
#line 647 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->expectType(nextType); 
                                              
                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 
                                              
                                                 freeName(szName1);
                                               ;}
    break;

  case 106:
#line 659 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   ;}
    break;

  case 107:
#line 668 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   ;}
    break;

  case 108:
#line 677 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { setName(szName1, 
                                                            SKELTEXT);
                                                  ;}
    break;

  case 109:
#line 680 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->expectType(nextType);
                                                
                                                    if(SKEL != NULL)
                                                        SKEL->
                                                         beginExposedFieldDecl(
                                                           szName1,
                                                           nextType,
                                                           SKELTEXT); 
                                              
                                                    freeName(szName1);
                                                  ;}
    break;

  case 110:
#line 693 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = 0; 

                                                        if(SKEL != NULL)
                                                        {
                                                         SKEL->is(SKELTEXT);

                                                         SKEL->
                                                         endExposedFieldDecl();
                                                        }
                                                      ;}
    break;

  case 111:
#line 703 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = 0; 
   
                                                        if(SKEL != NULL)
                                                         SKEL->
                                                         endExposedFieldDecl();
                                                      ;}
    break;

  case 116:
#line 731 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
                   ;}
    break;

  case 120:
#line 758 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        ;}
    break;

  case 121:
#line 764 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL != NULL)
                            SKEL->endField();
                        ;}
    break;

  case 129:
#line 790 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFBOOL;      ;}
    break;

  case 130:
#line 791 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFCOLOR;     ;}
    break;

  case 131:
#line 792 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFCOLORRGBA; ;}
    break;

  case 132:
#line 793 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFDOUBLE;    ;}
    break;

  case 133:
#line 794 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFFLOAT;     ;}
    break;

  case 134:
#line 795 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFIMAGE;     ;}
    break;

  case 135:
#line 796 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFINT32;     ;}
    break;

  case 136:
#line 797 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFMATRIX3D;  ;}
    break;

  case 137:
#line 798 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFMATRIX3F;  ;}
    break;

  case 138:
#line 799 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFMATRIX4D;  ;}
    break;

  case 139:
#line 800 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFMATRIX4F;  ;}
    break;

  case 140:
#line 801 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFNODE;      ;}
    break;

  case 141:
#line 802 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFROTATION;  ;}
    break;

  case 142:
#line 803 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFSTRING;    ;}
    break;

  case 143:
#line 804 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFTIME;      ;}
    break;

  case 144:
#line 805 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFVEC2D;     ;}
    break;

  case 145:
#line 806 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFVEC2F;     ;}
    break;

  case 146:
#line 807 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFVEC3D;     ;}
    break;

  case 147:
#line 808 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFVEC3F;     ;}
    break;

  case 148:
#line 809 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFVEC4D;     ;}
    break;

  case 149:
#line 810 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFVEC4F;     ;}
    break;

  case 150:
#line 811 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFBOOL;      ;}
    break;

  case 151:
#line 812 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFCOLOR;     ;}
    break;

  case 152:
#line 813 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFCOLORRGBA; ;}
    break;

  case 153:
#line 814 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFDOUBLE;    ;}
    break;

  case 154:
#line 815 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFFLOAT;     ;}
    break;

  case 155:
#line 816 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFIMAGE;     ;}
    break;

  case 156:
#line 817 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFINT32;     ;}
    break;

  case 157:
#line 818 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFMATRIX3D;  ;}
    break;

  case 158:
#line 819 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFMATRIX3F;  ;}
    break;

  case 159:
#line 820 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFMATRIX4D;  ;}
    break;

  case 160:
#line 821 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFMATRIX4F;  ;}
    break;

  case 161:
#line 822 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFNODE;      ;}
    break;

  case 162:
#line 823 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFROTATION;  ;}
    break;

  case 163:
#line 824 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFSTRING;    ;}
    break;

  case 164:
#line 825 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFTIME;      ;}
    break;

  case 165:
#line 826 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVEC2D;     ;}
    break;

  case 166:
#line 827 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVEC2F;     ;}
    break;

  case 167:
#line 828 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVEC3D;     ;}
    break;

  case 168:
#line 829 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVEC3F;     ;}
    break;

  case 169:
#line 830 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVEC4D;     ;}
    break;

  case 170:
#line 831 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVEC4F;     ;}
    break;

  case 171:
#line 832 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFCOLOR4I;   ;}
    break;

  case 172:
#line 833 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFPNT2F;     ;}
    break;

  case 173:
#line 834 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFPNT3F;     ;}
    break;

  case 174:
#line 835 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFPNT4F;     ;}
    break;

  case 175:
#line 836 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_MFPLANE;     ;}
    break;

  case 176:
#line 837 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFCOLOR4I;   ;}
    break;

  case 177:
#line 838 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFPNT2F;     ;}
    break;

  case 178:
#line 839 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFPNT3F;     ;}
    break;

  case 179:
#line 840 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFPNT4F;     ;}
    break;

  case 180:
#line 841 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFPLANE;     ;}
    break;

  case 181:
#line 842 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { nextType = TOK_SFVOLUME;    ;}
    break;

  case 236:
#line 904 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;

  case 238:
#line 914 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 2595 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 932 "Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


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

