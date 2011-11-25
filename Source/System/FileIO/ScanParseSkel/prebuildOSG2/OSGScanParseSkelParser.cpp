/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         OSGScanParseSkel_parse
#define yylex           OSGScanParseSkel_lex
#define yyerror         OSGScanParseSkel_error
#define yylval          OSGScanParseSkel_lval
#define yychar          OSGScanParseSkel_char
#define yydebug         OSGScanParseSkel_debug
#define yynerrs         OSGScanParseSkel_nerrs


/* Copy the first part of user declarations.  */


/* Line 189 of yacc.c  */
#line 80 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     TOK_MFVec2i = 330,
     TOK_hex = 331,
     TOK_int32 = 332,
     TOK_double = 333,
     TOK_string = 334,
     TOK_bool = 335,
     TOK_NULL = 336,
     TOK_Id = 337,
     TOK_ImageFinished = 338,
     TOK_Error = 339,
     TOK_ClusterLocal = 340,
     TOK_ThreadLocal = 341
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 41 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"

    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;



/* Line 214 of yacc.c  */
#line 212 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 49 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


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

#ifdef OSG_USE_OSG2_NAMESPACE
#define OSGScanParseSkel_lex OSG2ScanParseSkel_lex
#endif

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

#define SKEL (static_cast<ScanParseSkel *>(pSkel))

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif



/* Line 264 of yacc.c  */
#line 264 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1016

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  263
/* YYNRULES -- Number of rules.  */
#define YYNRULES  470
/* YYNRULES -- Number of states.  */
#define YYNSTATES  766

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    91,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    88,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,     2,    90,     2,     2,     2,     2,
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
      85,    86
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    29,    32,    33,    34,    39,    41,    43,
      46,    47,    49,    51,    53,    55,    57,    58,    59,    65,
      66,    67,    68,    77,    80,    84,    85,    88,    89,    91,
      93,    95,    97,    98,    99,   110,   113,   114,   115,   120,
     121,   126,   127,   128,   135,   136,   137,   144,   145,   146,
     155,   158,   159,   160,   165,   166,   171,   172,   177,   178,
     183,   184,   185,   186,   198,   199,   200,   208,   209,   214,
     217,   218,   220,   224,   227,   228,   230,   232,   234,   236,
     238,   240,   241,   242,   249,   250,   251,   258,   259,   262,
     263,   264,   271,   272,   273,   280,   281,   282,   289,   291,
     295,   296,   300,   302,   304,   306,   308,   310,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   342,   344,   346,   348,   350,   352,   354,   356,
     358,   360,   362,   364,   366,   368,   370,   372,   374,   376,
     378,   380,   382,   384,   386,   388,   390,   392,   394,   396,
     398,   400,   402,   404,   406,   408,   410,   412,   414,   416,
     418,   420,   422,   424,   426,   428,   430,   433,   436,   439,
     442,   445,   448,   451,   454,   457,   460,   463,   466,   469,
     472,   475,   478,   481,   484,   487,   490,   493,   496,   499,
     502,   505,   508,   511,   514,   517,   520,   523,   526,   529,
     532,   535,   538,   541,   544,   547,   550,   553,   556,   559,
     562,   565,   568,   571,   574,   577,   580,   583,   586,   589,
     592,   595,   597,   599,   601,   603,   605,   607,   609,   611,
     612,   613,   619,   620,   621,   622,   630,   632,   634,   635,
     636,   637,   646,   649,   650,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   704,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   751,
     752,   753,   754,   755,   756,   757,   758,   759,   760,   761,
     762,   763,   764,   765,   766,   798,   800,   802,   803,   804,
     805,   813,   815,   817,   819,   821,   822,   826,   827,   831,
     832,   833,   834,   841,   842,   843,   844,   851,   852,   853,
     854,   855,   864,   865,   866,   867,   868,   877,   879,   883,
     886,   887,   889,   893,   896,   897,   899,   903,   906,   907,
     909,   913,   916,   917,   919,   923,   926,   927,   929,   933,
     936,   937,   939,   943,   946,   947,   949,   953,   956,   957,
     959,   963,   966,   967,   969,   973,   976,   977,   979,   983,
     986,   987,   989,   993,   996,   997,   999,  1003,  1006,  1007,
    1009,  1013,  1016,  1017,  1019,  1023,  1026,  1027,  1029,  1033,
    1036,  1037,  1039,  1043,  1046,  1047,  1049,  1053,  1056,  1057,
    1059,  1063,  1066,  1067,  1069,  1073,  1076,  1077,  1079,  1083,
    1086,  1087,  1088,  1089,  1090,  1098,  1099,  1103,  1104,  1105,
    1111,  1112,  1113,  1114,  1122,  1123,  1124,  1125,  1133,  1134,
    1135,  1136,  1137,  1138,  1139,  1153,  1154,  1158,  1160,  1164,
    1167,  1168,  1170,  1174,  1177,  1178,  1180,  1184,  1187,  1188,
    1190,  1194,  1197,  1198,  1200,  1204,  1207,  1208,  1210,  1214,
    1217
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    94,    95,    97,   100,   105,    -1,     3,
      -1,    -1,     4,    96,    -1,    -1,    82,    -1,    97,    98,
      -1,    -1,     5,    99,    -1,    82,    -1,    79,    -1,   100,
     101,    -1,    -1,    -1,     6,   103,   102,   104,    -1,    79,
      -1,    79,    -1,   105,   106,    -1,    -1,   107,    -1,   116,
      -1,   137,    -1,   141,    -1,   144,    -1,    -1,    -1,   171,
     108,   113,   109,   148,    -1,    -1,    -1,    -1,    10,   170,
     110,   171,   111,   113,   112,   148,    -1,    11,   170,    -1,
      87,   114,    88,    -1,    -1,   114,   115,    -1,    -1,    85,
      -1,    86,    -1,   117,    -1,   128,    -1,    -1,    -1,     7,
     171,   118,    87,   120,    88,   119,    89,   105,    90,    -1,
     120,   121,    -1,    -1,    -1,    17,   175,   122,   173,    -1,
      -1,    18,   175,   123,   174,    -1,    -1,    -1,    20,   175,
     124,   172,   125,   176,    -1,    -1,    -1,    19,   175,   126,
     172,   127,   176,    -1,    -1,    -1,     8,   171,   129,    87,
     131,    88,   130,   147,    -1,   131,   132,    -1,    -1,    -1,
      17,   175,   133,   173,    -1,    -1,    18,   175,   134,   174,
      -1,    -1,    20,   175,   135,   172,    -1,    -1,    19,   175,
     136,   172,    -1,    -1,    -1,    -1,    12,   170,   138,    91,
     174,   139,    13,   170,   140,    91,   173,    -1,    -1,    -1,
      14,   170,   142,    91,   170,   143,   146,    -1,    -1,    15,
     170,   145,   146,    -1,    16,   170,    -1,    -1,   301,    -1,
      89,   149,    90,    -1,   149,   150,    -1,    -1,   167,    -1,
     151,    -1,   154,    -1,   158,    -1,   163,    -1,     1,    -1,
      -1,    -1,    17,   175,   152,   173,   153,   157,    -1,    -1,
      -1,    18,   175,   155,   174,   156,   157,    -1,    -1,     9,
     172,    -1,    -1,    -1,    20,   175,   159,   172,   160,   166,
      -1,    -1,    -1,    20,    82,   161,   172,   162,   166,    -1,
      -1,    -1,    19,   175,   164,   172,   165,   166,    -1,   176,
      -1,   175,     9,   172,    -1,    -1,   172,   168,   169,    -1,
     137,    -1,   116,    -1,   141,    -1,   144,    -1,   176,    -1,
     175,     9,   172,    -1,    82,    -1,    82,    -1,    82,    -1,
      82,    -1,    82,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,
      49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,
      54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,
      59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,
      21,   275,    -1,    22,   277,    -1,    23,   279,    -1,    24,
     281,    -1,    25,   283,    -1,    26,   285,    -1,    27,   287,
      -1,    28,   289,    -1,    29,   291,    -1,    30,   293,    -1,
      31,   295,    -1,    32,   297,    -1,    33,   299,    -1,    34,
     301,    -1,    35,   303,    -1,    36,   305,    -1,    37,   307,
      -1,    38,   309,    -1,    39,   311,    -1,    40,   313,    -1,
      41,   315,    -1,    42,   180,    -1,    43,   181,    -1,    44,
     184,    -1,    45,   188,    -1,    46,   189,    -1,    47,   190,
      -1,    48,   195,    -1,    49,   196,    -1,    50,   205,    -1,
      51,   214,    -1,    52,   230,    -1,    53,   246,    -1,    54,
     247,    -1,    55,   251,    -1,    56,   252,    -1,    57,   253,
      -1,    58,   255,    -1,    59,   257,    -1,    60,   261,    -1,
      61,   265,    -1,    62,   270,    -1,    63,   343,    -1,    64,
     345,    -1,    65,   347,    -1,    66,   349,    -1,    67,   351,
      -1,    68,   317,    -1,    69,   321,    -1,    70,   323,    -1,
      71,   326,    -1,    72,   330,    -1,    73,   334,    -1,    74,
     341,    -1,    75,   353,    -1,    76,    -1,    77,    -1,    77,
      -1,    78,    -1,    77,    -1,    78,    -1,    80,    -1,    82,
      -1,    -1,    -1,   179,   182,   179,   183,   179,    -1,    -1,
      -1,    -1,   179,   185,   179,   186,   179,   187,   179,    -1,
     178,    -1,   179,    -1,    -1,    -1,    -1,   177,   191,   177,
     192,   177,   193,   194,    83,    -1,   194,   177,    -1,    -1,
     177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     178,   197,   178,   198,   178,   199,   178,   200,   178,   201,
     178,   202,   178,   203,   178,   204,   178,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   179,   206,   179,   207,
     179,   208,   179,   209,   179,   210,   179,   211,   179,   212,
     179,   213,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   178,
     215,   178,   216,   178,   217,   178,   218,   178,   219,   178,
     220,   178,   221,   178,   222,   178,   223,   178,   224,   178,
     225,   178,   226,   178,   227,   178,   228,   178,   229,   178,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   179,   231,   179,   232,
     179,   233,   179,   234,   179,   235,   179,   236,   179,   237,
     179,   238,   179,   239,   179,   240,   179,   241,   179,   242,
     179,   243,   179,   244,   179,   245,   179,    -1,   107,    -1,
      81,    -1,    -1,    -1,    -1,   179,   248,   179,   249,   179,
     250,   179,    -1,    79,    -1,    82,    -1,    76,    -1,   178,
      -1,    -1,   178,   254,   178,    -1,    -1,   179,   256,   179,
      -1,    -1,    -1,    -1,   178,   258,   178,   259,   178,   260,
      -1,    -1,    -1,    -1,   179,   262,   179,   263,   179,   264,
      -1,    -1,    -1,    -1,    -1,   178,   266,   178,   267,   178,
     268,   178,   269,    -1,    -1,    -1,    -1,    -1,   179,   271,
     179,   272,   179,   273,   179,   274,    -1,   180,    -1,    87,
     276,    88,    -1,   276,   180,    -1,    -1,   181,    -1,    87,
     278,    88,    -1,   278,   181,    -1,    -1,   184,    -1,    87,
     280,    88,    -1,   280,   184,    -1,    -1,   188,    -1,    87,
     282,    88,    -1,   282,   188,    -1,    -1,   189,    -1,    87,
     284,    88,    -1,   284,   189,    -1,    -1,   190,    -1,    87,
     286,    88,    -1,   286,   190,    -1,    -1,   195,    -1,    87,
     288,    88,    -1,   288,   195,    -1,    -1,   196,    -1,    87,
     290,    88,    -1,   290,   196,    -1,    -1,   205,    -1,    87,
     292,    88,    -1,   292,   205,    -1,    -1,   214,    -1,    87,
     294,    88,    -1,   294,   214,    -1,    -1,   230,    -1,    87,
     296,    88,    -1,   296,   230,    -1,    -1,   246,    -1,    87,
     298,    88,    -1,   298,   246,    -1,    -1,   247,    -1,    87,
     300,    88,    -1,   300,   247,    -1,    -1,   251,    -1,    87,
     302,    88,    -1,   302,   251,    -1,    -1,   252,    -1,    87,
     304,    88,    -1,   304,   252,    -1,    -1,   253,    -1,    87,
     306,    88,    -1,   306,   253,    -1,    -1,   255,    -1,    87,
     308,    88,    -1,   308,   255,    -1,    -1,   257,    -1,    87,
     310,    88,    -1,   310,   257,    -1,    -1,   261,    -1,    87,
     312,    88,    -1,   312,   261,    -1,    -1,   265,    -1,    87,
     314,    88,    -1,   314,   265,    -1,    -1,   270,    -1,    87,
     316,    88,    -1,   316,   270,    -1,    -1,    -1,    -1,    -1,
     177,   318,   177,   319,   177,   320,   177,    -1,    -1,   179,
     322,   179,    -1,    -1,    -1,   179,   324,   179,   325,   179,
      -1,    -1,    -1,    -1,   179,   327,   179,   328,   179,   329,
     179,    -1,    -1,    -1,    -1,   179,   331,   179,   332,   179,
     333,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
     335,   179,   336,   179,   337,   179,   338,   179,   339,   179,
     340,   179,    -1,    -1,   177,   342,   177,    -1,   317,    -1,
      87,   344,    88,    -1,   344,   317,    -1,    -1,   321,    -1,
      87,   346,    88,    -1,   346,   321,    -1,    -1,   323,    -1,
      87,   348,    88,    -1,   348,   323,    -1,    -1,   326,    -1,
      87,   350,    88,    -1,   350,   326,    -1,    -1,   330,    -1,
      87,   352,    88,    -1,   352,   330,    -1,    -1,   341,    -1,
      87,   354,    88,    -1,   354,   341,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   210,   210,   217,   218,   221,   222,   225,   228,   229,
     233,   238,   239,   246,   247,   252,   250,   257,   260,   263,
     264,   267,   268,   269,   270,   271,   286,   289,   286,   294,
     297,   298,   293,   302,   306,   307,   310,   311,   314,   315,
     318,   319,   326,   327,   326,   331,   332,   336,   335,   339,
     338,   342,   343,   341,   346,   347,   345,   351,   352,   351,
     356,   357,   361,   360,   364,   363,   367,   366,   370,   369,
     375,   377,   379,   374,   386,   388,   385,   399,   398,   409,
     411,   414,   417,   420,   421,   424,   425,   426,   427,   428,
     429,   433,   434,   432,   439,   440,   438,   443,   445,   449,
     450,   448,   453,   454,   452,   468,   469,   467,   473,   474,
     478,   477,   486,   487,   488,   489,   492,   493,   496,   499,
     502,   505,   508,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   554,   555,   556,   557,   558,
     559,   560,   561,   562,   563,   564,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   625,   626,   629,   630,   633,   634,   637,   641,   644,
     645,   644,   653,   654,   655,   653,   663,   669,   675,   676,
     678,   675,   688,   692,   695,   701,   702,   703,   704,   705,
     706,   707,   708,   701,   719,   720,   721,   722,   723,   724,
     725,   726,   719,   737,   738,   739,   740,   741,   742,   743,
     744,   745,   746,   747,   748,   749,   750,   751,   737,   763,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
     774,   775,   776,   777,   763,   789,   790,   793,   794,   795,
     793,   803,   807,   811,   817,   823,   823,   831,   831,   839,
     840,   841,   839,   848,   849,   850,   848,   857,   858,   859,
     860,   857,   867,   868,   869,   870,   867,   877,   878,   881,
     882,   885,   886,   889,   890,   893,   894,   897,   898,   901,
     902,   905,   906,   909,   910,   913,   914,   917,   918,   921,
     922,   925,   926,   929,   930,   933,   934,   937,   938,   941,
     942,   945,   946,   949,   950,   953,   954,   957,   958,   961,
     962,   965,   966,   969,   970,   973,   974,   977,   978,   981,
     982,   985,   986,   989,   990,   993,   994,   997,   998,  1001,
    1002,  1005,  1006,  1009,  1010,  1013,  1014,  1017,  1018,  1021,
    1022,  1025,  1026,  1029,  1030,  1033,  1034,  1037,  1038,  1041,
    1042,  1047,  1048,  1049,  1047,  1058,  1058,  1066,  1067,  1066,
    1075,  1076,  1077,  1075,  1085,  1086,  1087,  1085,  1095,  1096,
    1097,  1098,  1099,  1100,  1095,  1112,  1112,  1120,  1121,  1124,
    1125,  1128,  1129,  1132,  1133,  1136,  1137,  1140,  1141,  1144,
    1145,  1148,  1149,  1152,  1153,  1156,  1157,  1160,  1161,  1164,
    1165
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_HEADER", "TOK_PROFILE",
  "TOK_COMPONENT", "TOK_META", "TOK_PROTO", "TOK_EXTERNPROTO", "TOK_IS",
  "TOK_DEF", "TOK_USE", "TOK_ROUTE", "TOK_TO", "TOK_IMPORT", "TOK_EXPORT",
  "TOK_AS", "TOK_eventIn", "TOK_eventOut", "TOK_exposedField", "TOK_field",
  "TOK_MFBool", "TOK_MFColor", "TOK_MFColorRGBA", "TOK_MFDouble",
  "TOK_MFFloat", "TOK_MFImage", "TOK_MFInt32", "TOK_MFMatrix3d",
  "TOK_MFMatrix3f", "TOK_MFMatrix4d", "TOK_MFMatrix4f", "TOK_MFNode",
  "TOK_MFRotation", "TOK_MFString", "TOK_MFTime", "TOK_MFVec2d",
  "TOK_MFVec2f", "TOK_MFVec3d", "TOK_MFVec3f", "TOK_MFVec4d",
  "TOK_MFVec4f", "TOK_SFBool", "TOK_SFColor", "TOK_SFColorRGBA",
  "TOK_SFDouble", "TOK_SFFloat", "TOK_SFImage", "TOK_SFInt32",
  "TOK_SFMatrix3d", "TOK_SFMatrix3f", "TOK_SFMatrix4d", "TOK_SFMatrix4f",
  "TOK_SFNode", "TOK_SFRotation", "TOK_SFString", "TOK_SFTime",
  "TOK_SFVec2d", "TOK_SFVec2f", "TOK_SFVec3d", "TOK_SFVec3f",
  "TOK_SFVec4d", "TOK_SFVec4f", "TOK_MFColor4i", "TOK_MFPnt2f",
  "TOK_MFPnt3f", "TOK_MFPnt4f", "TOK_MFPlane", "TOK_SFColor4i",
  "TOK_SFPnt2f", "TOK_SFPnt3f", "TOK_SFPnt4f", "TOK_SFPlane",
  "TOK_SFVolume", "TOK_SFVec2i", "TOK_MFVec2i", "TOK_hex", "TOK_int32",
  "TOK_double", "TOK_string", "TOK_bool", "TOK_NULL", "TOK_Id",
  "TOK_ImageFinished", "TOK_Error", "TOK_ClusterLocal", "TOK_ThreadLocal",
  "'['", "']'", "'{'", "'}'", "'.'", "$accept", "x3dScene",
  "headerStatement", "profileStatement", "profileNameId",
  "componentStatements", "componentStatement", "componentNameId",
  "metaStatements", "metaStatement", "$@1", "metakey", "metavalue",
  "statements", "statement", "nodeStatement", "$@2", "$@3", "$@4", "$@5",
  "$@6", "nodeOptionStatement", "nodeOptions", "nodeOption",
  "protoStatement", "proto", "$@7", "$@8", "interfaceDeclarations",
  "interfaceDeclaration", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "externproto", "$@15", "$@16", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "$@17", "$@18", "$@19", "$@20",
  "routeStatement", "$@21", "$@22", "$@23", "importStatement", "$@24",
  "$@25", "exportStatement", "$@26", "asStatement", "URLList", "node",
  "scriptBody", "scriptBodyElement", "eventInDeclaration", "$@27", "$@28",
  "eventOutDeclaration", "$@29", "$@30", "eventDeclarationEnd",
  "fieldDeclaration", "$@31", "$@32", "$@33", "$@34",
  "exposedFieldDeclaration", "$@35", "$@36", "fieldDeclarationEnd",
  "nodeBodyElement", "$@37", "fieldEnd", "nodeNameId", "nodeTypeId",
  "fieldId", "eventInId", "eventOutId", "fieldType", "fieldValue", "int32",
  "double", "float", "sfboolValue", "sfcolorValue", "$@38", "$@39",
  "sfcolorRGBAValue", "$@40", "$@41", "$@42", "sfdoubleValue",
  "sffloatValue", "sfimageValue", "$@43", "$@44", "$@45", "pixels",
  "sfint32Value", "sfmatrix3dValue", "$@46", "$@47", "$@48", "$@49",
  "$@50", "$@51", "$@52", "$@53", "sfmatrix3fValue", "$@54", "$@55",
  "$@56", "$@57", "$@58", "$@59", "$@60", "$@61", "sfmatrix4dValue",
  "$@62", "$@63", "$@64", "$@65", "$@66", "$@67", "$@68", "$@69", "$@70",
  "$@71", "$@72", "$@73", "$@74", "$@75", "$@76", "sfmatrix4fValue",
  "$@77", "$@78", "$@79", "$@80", "$@81", "$@82", "$@83", "$@84", "$@85",
  "$@86", "$@87", "$@88", "$@89", "$@90", "$@91", "sfnodeValue",
  "sfrotationValue", "$@92", "$@93", "$@94", "sfstringValue",
  "sftimeValue", "sfvec2dValue", "$@95", "sfvec2fValue", "$@96",
  "sfvec3dValue", "$@97", "$@98", "$@99", "sfvec3fValue", "$@100", "$@101",
  "$@102", "sfvec4dValue", "$@103", "$@104", "$@105", "$@106",
  "sfvec4fValue", "$@107", "$@108", "$@109", "$@110", "mfboolValue",
  "sfboolValues", "mfcolorValue", "sfcolorValues", "mfcolorRGBAValue",
  "sfcolorRGBAValues", "mfdoubleValue", "sfdoubleValues", "mffloatValue",
  "sffloatValues", "mfimageValue", "sfimageValues", "mfint32Value",
  "sfint32Values", "mfmatrix3dValue", "sfmatrix3dValues",
  "mfmatrix3fValue", "sfmatrix3fValues", "mfmatrix4dValue",
  "sfmatrix4dValues", "mfmatrix4fValue", "sfmatrix4fValues", "mfnodeValue",
  "sfnodeValues", "mfrotationValue", "sfrotationValues", "mfstringValue",
  "sfstringValues", "mftimeValue", "sftimeValues", "mfvec2dValue",
  "sfvec2dValues", "mfvec2fValue", "sfvec2fValues", "mfvec3dValue",
  "sfvec3dValues", "mfvec3fValue", "sfvec3fValues", "mfvec4dValue",
  "sfvec4dValues", "mfvec4fValue", "sfvec4fValues", "sfcolor4iValue",
  "$@111", "$@112", "$@113", "sfpnt2fValue", "$@114", "sfpnt3fValue",
  "$@115", "$@116", "sfpnt4fValue", "$@117", "$@118", "$@119",
  "sfplaneValue", "$@120", "$@121", "$@122", "sfVolumeValue", "$@123",
  "$@124", "$@125", "$@126", "$@127", "$@128", "sfvec2iValue", "$@129",
  "mfcolor4iValue", "sfcolor4iValues", "mfpnt2fValue", "sfpnt2fValues",
  "mfpnt3fValue", "sfpnt3fValues", "mfpnt4fValue", "sfpnt4fValues",
  "mfplaneValue", "sfplaneValues", "mfvec2iValue", "sfvec2iValues", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,    91,    93,   123,
     125,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    92,    93,    94,    94,    95,    95,    96,    97,    97,
      98,    99,    99,   100,   100,   102,   101,   103,   104,   105,
     105,   106,   106,   106,   106,   106,   108,   109,   107,   110,
     111,   112,   107,   107,   113,   113,   114,   114,   115,   115,
     116,   116,   118,   119,   117,   120,   120,   122,   121,   123,
     121,   124,   125,   121,   126,   127,   121,   129,   130,   128,
     131,   131,   133,   132,   134,   132,   135,   132,   136,   132,
     138,   139,   140,   137,   142,   143,   141,   145,   144,   146,
     146,   147,   148,   149,   149,   150,   150,   150,   150,   150,
     150,   152,   153,   151,   155,   156,   154,   157,   157,   159,
     160,   158,   161,   162,   158,   164,   165,   163,   166,   166,
     168,   167,   167,   167,   167,   167,   169,   169,   170,   171,
     172,   173,   174,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   177,   177,   178,   178,   179,   179,   180,   180,   182,
     183,   181,   185,   186,   187,   184,   188,   189,   191,   192,
     193,   190,   194,   194,   195,   197,   198,   199,   200,   201,
     202,   203,   204,   196,   206,   207,   208,   209,   210,   211,
     212,   213,   205,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   214,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   230,   246,   246,   248,   249,   250,
     247,   251,   251,   251,   252,   254,   253,   256,   255,   258,
     259,   260,   257,   262,   263,   264,   261,   266,   267,   268,
     269,   265,   271,   272,   273,   274,   270,   275,   275,   276,
     276,   277,   277,   278,   278,   279,   279,   280,   280,   281,
     281,   282,   282,   283,   283,   284,   284,   285,   285,   286,
     286,   287,   287,   288,   288,   289,   289,   290,   290,   291,
     291,   292,   292,   293,   293,   294,   294,   295,   295,   296,
     296,   297,   297,   298,   298,   299,   299,   300,   300,   301,
     301,   302,   302,   303,   303,   304,   304,   305,   305,   306,
     306,   307,   307,   308,   308,   309,   309,   310,   310,   311,
     311,   312,   312,   313,   313,   314,   314,   315,   315,   316,
     316,   318,   319,   320,   317,   322,   321,   324,   325,   323,
     327,   328,   329,   326,   331,   332,   333,   330,   335,   336,
     337,   338,   339,   340,   334,   342,   341,   343,   343,   344,
     344,   345,   345,   346,   346,   347,   347,   348,   348,   349,
     349,   350,   350,   351,   351,   352,   352,   353,   353,   354,
     354
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     1,     2,     0,     0,     4,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     0,     0,     5,     0,
       0,     0,     8,     2,     3,     0,     2,     0,     1,     1,
       1,     1,     0,     0,    10,     2,     0,     0,     4,     0,
       4,     0,     0,     6,     0,     0,     6,     0,     0,     8,
       2,     0,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     0,     0,    11,     0,     0,     7,     0,     4,     2,
       0,     1,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     0,     0,     6,     0,     0,     6,     0,     2,     0,
       0,     6,     0,     0,     6,     0,     0,     6,     1,     3,
       0,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     5,     0,     0,     0,     7,     1,     1,     0,     0,
       0,     8,     2,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     1,     1,     0,     0,     0,
       7,     1,     1,     1,     1,     0,     3,     0,     3,     0,
       0,     0,     6,     0,     0,     0,     6,     0,     0,     0,
       0,     8,     0,     0,     0,     0,     8,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     0,     0,     0,     7,     0,     3,     0,     0,     5,
       0,     0,     0,     7,     0,     0,     0,     7,     0,     0,
       0,     0,     0,     0,    13,     0,     3,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   119,    19,
      21,    22,    40,    41,    23,    24,    25,    26,     0,    42,
      57,   118,    29,    33,    70,    74,    77,    35,    18,    16,
       0,     0,     0,     0,     0,    80,    37,    27,    46,    61,
      30,     0,     0,     0,    78,     0,     0,     0,     0,    35,
     122,    71,    75,    79,    38,    39,    34,    36,    84,    28,
       0,     0,     0,     0,    43,    45,     0,     0,     0,     0,
      58,    60,    31,     0,    80,     0,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,    47,
      49,    54,    51,     0,    62,    64,    68,    66,     0,     0,
       0,    76,    90,     0,     0,     0,     0,   120,    82,   113,
     112,   114,   115,    83,    86,    87,    88,    89,    85,   110,
       0,     0,     0,     0,    20,     0,     0,     0,     0,   313,
     311,   312,   392,    59,   389,    81,    32,    72,    91,    94,
     105,   102,    99,     0,   121,    48,    50,    55,    52,     0,
      63,    65,    69,    67,     0,     0,     0,     0,     0,     0,
       0,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,     0,   111,     0,   116,     0,
       0,    44,   390,   391,     0,    92,    95,   106,   103,   100,
     237,   238,   340,   337,   176,   235,   236,   344,   239,   341,
     177,   348,   242,   345,   178,   233,   234,   352,   246,   349,
     179,   356,   247,   353,   180,   231,   232,   360,   248,   357,
     181,   364,   254,   361,   182,   368,   255,   365,   183,   372,
     264,   369,   184,   376,   273,   373,   185,   380,   289,   377,
     186,   306,   384,   305,   381,   187,   388,   307,   385,   188,
     189,   396,   314,   393,   190,   400,   315,   397,   191,   404,
     317,   401,   192,   408,   319,   405,   193,   412,   323,   409,
     194,   416,   327,   413,   195,   420,   332,   417,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     450,   421,   447,   218,   454,   425,   451,   219,   458,   427,
     455,   220,   462,   430,   459,   221,   466,   434,   463,   222,
     223,   224,   225,   226,   227,   438,   228,   445,   229,   470,
     467,   230,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    53,    73,    97,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,     0,    93,    96,   107,     0,   108,   104,   101,
     338,   339,   342,   343,   240,   346,   347,   243,   350,   351,
     354,   355,   358,   359,   249,   362,   363,   366,   367,   256,
     370,   371,   265,   374,   375,   274,   378,   379,   290,   382,
     383,   386,   387,   308,   394,   395,   398,   399,   316,   402,
     403,   318,   406,   407,   320,   410,   411,   324,   414,   415,
     328,   418,   419,   333,   448,   449,   422,   452,   453,   426,
     456,   457,   428,   460,   461,   431,   464,   465,   435,   439,
     446,   468,   469,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   241,   244,   250,   257,   266,   275,   291,
     309,   321,   325,   329,   334,   423,   429,   432,   436,   440,
       0,   253,     0,     0,     0,     0,     0,   322,   326,     0,
       0,     0,     0,     0,     0,   245,     0,   258,   267,   276,
     292,   310,   330,   335,   424,   433,   437,   441,   251,   252,
       0,     0,     0,     0,   331,   336,     0,   259,   268,   277,
     293,   442,     0,     0,     0,     0,     0,   260,   269,   278,
     294,   443,     0,     0,     0,     0,     0,   261,   270,   279,
     295,   444,     0,     0,     0,     0,   262,   271,   280,   296,
       0,     0,     0,     0,   263,   272,   281,   297,     0,     0,
     282,   298,     0,     0,   283,   299,     0,     0,   284,   300,
       0,     0,   285,   301,     0,     0,   286,   302,     0,     0,
     287,   303,     0,     0,   288,   304
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   343,    47,    66,    52,    69,
     159,    57,    65,    77,    31,    32,    50,   153,    67,    85,
     180,   181,   183,   280,   182,   279,    33,    51,   158,    68,
      91,   185,   186,   188,   187,    34,    53,    93,   215,    35,
      54,    94,    36,    55,    64,   193,    79,    95,   173,   174,
     216,   489,   175,   217,   490,   543,   176,   220,   493,   219,
     492,   177,   218,   491,   545,   178,   203,   276,    42,    37,
     179,   205,    71,   546,   547,   318,   308,   298,   293,   299,
     496,   625,   303,   498,   626,   660,   309,   313,   319,   502,
     627,   661,   676,   323,   327,   505,   628,   662,   690,   702,
     712,   722,   730,   331,   507,   629,   663,   691,   703,   713,
     723,   731,   335,   509,   630,   664,   692,   704,   714,   724,
     732,   738,   742,   746,   750,   754,   758,   762,   339,   511,
     631,   665,   693,   705,   715,   725,   733,   739,   743,   747,
     751,   755,   759,   763,   344,   348,   514,   632,   666,   194,
     353,   357,   517,   361,   519,   365,   521,   633,   667,   369,
     523,   634,   668,   373,   525,   635,   669,   694,   377,   527,
     636,   670,   695,   294,   494,   300,   495,   304,   497,   310,
     499,   314,   500,   320,   501,   324,   503,   328,   504,   332,
     506,   336,   508,   340,   510,   345,   512,   349,   513,   350,
     214,   354,   515,   358,   516,   362,   518,   366,   520,   370,
     522,   374,   524,   378,   526,   402,   529,   637,   671,   406,
     531,   410,   533,   638,   414,   535,   639,   672,   418,   537,
     640,   673,   426,   538,   641,   674,   696,   706,   716,   428,
     539,   403,   528,   407,   530,   411,   532,   415,   534,   419,
     536,   431,   540
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -275
static const yytype_int16 yypact[] =
{
      37,  -275,    71,    50,  -275,     2,  -275,  -275,  -275,    88,
      67,  -275,   110,  -275,  -275,  -275,    82,  -275,   356,  -275,
    -275,    58,    58,    94,    94,    94,    94,    94,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,   104,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,   102,  -275,  -275,
     106,   118,    58,   116,   134,   185,  -275,  -275,  -275,  -275,
    -275,   129,    94,    94,  -275,   465,   156,   125,   148,   102,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
     943,   943,   943,   943,  -275,  -275,   943,   943,   943,   943,
    -275,  -275,  -275,   224,   185,   100,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   161,  -275,  -275,  -275,  -275,    93,   156,
      94,  -275,  -275,   943,   943,   943,   596,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
     170,   129,   238,   238,  -275,   170,   129,   238,   238,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   833,  -275,  -275,  -275,  -275,  -275,    80,
    -275,  -275,  -275,  -275,    46,   231,   170,   129,   238,   238,
     238,   269,   259,   318,   382,   387,    77,    97,   394,   399,
     401,   419,    54,   426,    93,   434,   440,   448,   468,   470,
     488,   490,    47,    25,    25,   154,    25,   438,   438,   154,
      25,   154,    25,    66,    25,   127,   154,   154,    25,   154,
      25,   154,    25,   101,   492,   494,   496,   507,   438,    25,
      25,    25,    25,   438,   438,   109,  -275,   319,  -275,   888,
     888,  -275,  -275,  -275,   170,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,   238,   269,   259,   318,   382,   387,    77,    97,
     394,   399,   401,   419,    54,   426,    93,   434,   440,   448,
     468,   470,   488,   490,    47,    25,    25,   154,    25,   438,
     438,   154,    25,   154,    25,    66,    25,   127,   154,   154,
      25,   154,    25,   154,    25,   101,   492,   494,   496,   507,
     438,    25,    25,    25,    25,   438,  -275,  -275,  -275,   321,
     321,   833,   833,   833,    99,   114,    25,   120,    25,   122,
     257,    23,   438,    62,   277,   154,   281,    25,   295,   154,
     297,    25,    42,   300,    25,   303,   312,   154,   316,    25,
     342,   154,   344,    25,   346,   154,   348,    25,    75,   438,
     351,    25,   367,    25,   375,    25,   379,    25,    25,   438,
      83,  -275,   238,  -275,  -275,  -275,   323,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,   238,    25,    25,   438,   154,    25,
     154,    25,    25,   154,    25,   154,    25,   438,    25,    25,
      25,    25,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
      25,  -275,   154,    25,   154,    25,    25,  -275,  -275,   154,
      25,   438,    25,    25,    25,  -275,   422,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
     154,    25,   154,    25,  -275,  -275,    25,  -275,  -275,  -275,
    -275,  -275,   154,    25,   154,    25,    25,  -275,  -275,  -275,
    -275,  -275,   154,    25,   154,    25,    25,  -275,  -275,  -275,
    -275,  -275,   154,    25,   154,    25,  -275,  -275,  -275,  -275,
     154,    25,   154,    25,  -275,  -275,  -275,  -275,   154,    25,
    -275,  -275,   154,    25,  -275,  -275,   154,    25,  -275,  -275,
     154,    25,  -275,  -275,   154,    25,  -275,  -275,   154,    25,
    -275,  -275,   154,    25,  -275,  -275
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   157,  -275,    -5,  -275,  -275,  -275,  -275,
    -275,   284,  -275,  -275,   267,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,   287,  -275,  -275,  -275,   289,
    -275,  -275,   304,  -275,   282,  -275,   233,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,   -89,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,    30,  -275,  -275,  -275,    34,    61,
    -163,  -147,  -119,    -8,  -170,  -142,    91,  -223,  -230,  -138,
    -275,  -275,  -158,  -275,  -275,  -275,  -213,  -195,  -177,  -275,
    -275,  -275,  -275,  -180,  -160,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -200,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -206,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -216,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -231,  -228,  -275,  -275,  -275,  -151,
    -222,  -191,  -275,  -253,  -275,  -244,  -275,  -275,  -275,  -243,
    -275,  -275,  -275,  -254,  -275,  -275,  -275,  -275,  -259,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,   249,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -257,  -275,  -275,  -275,  -241,
    -275,  -240,  -275,  -275,  -262,  -275,  -275,  -275,  -268,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -274,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     302,   430,   312,   399,   424,   395,   330,   398,   338,   423,
     347,   420,   379,    30,   360,   396,   368,   397,   376,   207,
     208,   302,   390,   312,   212,   213,   391,   330,   421,   338,
     422,   347,   382,   278,   393,   360,   389,   368,   210,   376,
       1,   405,   409,   413,   417,   388,   405,   409,   413,   417,
     387,   383,    23,    24,     5,   287,   288,   289,    43,    44,
      45,    46,   206,   283,    23,    24,   394,   211,   385,   285,
     384,     4,   149,   150,   151,   152,    23,    24,   154,   155,
     156,   157,    39,    40,     7,   322,   381,    21,    22,   386,
      23,    24,    25,    10,    26,    27,    72,    73,   286,   315,
     316,   162,   295,   296,   392,   380,   322,    21,    22,   486,
     487,   562,    25,    60,    26,    27,    16,   163,   164,   165,
     166,   401,   189,   341,    28,   190,   401,   290,   191,   291,
     579,   425,   427,   427,   282,   341,    28,   488,   315,   316,
      28,   342,    80,    81,    82,    83,    13,   341,    28,    14,
     565,   315,   316,   315,   316,   198,   199,   200,   202,   315,
     316,    19,    28,   604,   317,    86,    87,    88,    89,   189,
     281,   621,   190,   315,   316,   191,    41,   315,   316,   290,
     192,   291,   167,    48,   321,   315,   316,   550,   400,    56,
     168,   295,   296,    58,   197,   277,   429,   295,   296,   305,
     306,    63,   552,   189,    30,    59,   190,    61,   555,   191,
     558,    70,   302,    84,   312,   399,   424,   395,   330,   398,
     338,   423,   347,   420,   379,    62,   360,   396,   368,   397,
     376,   305,   306,   302,   390,   312,    90,   160,   391,   330,
     421,   338,   422,   347,   382,    78,   393,   360,   389,   368,
     184,   376,   204,   405,   409,   413,   417,   388,   405,   409,
     413,   417,   387,   383,   551,   590,   622,   602,   617,   541,
     599,   605,   614,   554,   302,   557,   593,   312,   394,   596,
     385,   580,   384,   330,   572,   582,   559,   338,   578,   608,
     347,   583,   611,   585,   577,   360,   591,   322,   381,   368,
     597,   386,   574,   376,   603,   561,   571,   405,   609,   409,
     612,   413,   615,   417,   618,   619,   392,   380,   322,   326,
     167,   334,   284,   566,   563,   587,   352,   356,   432,   364,
     542,   372,   624,   401,   295,   296,   295,   296,   401,   556,
     326,   209,   334,   425,   568,   560,   297,   352,   356,   290,
     364,   291,   372,    92,   305,   306,   292,   553,   295,   296,
     564,   322,   169,    21,    22,   567,    23,    24,    25,   570,
      26,    27,   305,   306,   295,   296,   161,   295,   296,   623,
     305,   306,   170,   573,   171,   576,   401,   606,   581,   305,
     306,   584,   196,   295,   296,   295,   296,   620,   427,   172,
     586,   544,   643,   644,   589,   301,   647,   195,   649,   650,
       0,   652,     0,   654,     0,   656,   657,   658,   659,   305,
     306,   295,   296,   305,   306,   295,   296,     0,   295,   296,
     592,     0,   595,     0,   598,     0,   601,   675,    28,   607,
     678,     0,   680,   681,   295,   296,     0,   683,     0,   685,
     686,   687,   295,   296,     0,   610,   295,   296,     0,   305,
     306,   642,     0,   613,   295,   296,     0,   616,   698,   307,
     700,   305,   306,   701,   311,     0,   295,   296,   305,   306,
     708,   325,   710,   711,     0,   645,   329,     0,   333,     0,
     718,     0,   720,   721,     0,   655,   295,   296,   315,   316,
     727,     0,   729,   295,   296,   688,   337,     0,   735,     0,
     737,   305,   306,   346,   315,   316,   741,   305,   306,     0,
     745,   351,   548,   549,   749,   295,   296,   355,   753,   684,
       0,   326,   757,   334,   689,   359,   761,     0,   352,   356,
     765,   364,     0,   372,     0,   305,   306,   295,   296,     0,
      74,    75,   326,    76,   334,   363,     0,   367,     0,   352,
     356,     0,   364,     0,   372,   305,   306,   295,   296,   295,
     296,   295,   296,   295,   296,   371,     0,   375,     0,   404,
       0,   408,     0,   412,   295,   296,     0,     0,     0,     0,
       0,     0,     0,     0,   416,   326,   569,     0,     0,   334,
     575,     0,     0,     0,     0,     0,   352,   356,   588,     0,
       0,   364,   594,     0,     0,   372,   600,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
       0,     0,     0,     0,     0,     0,     0,     0,   201,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   646,
       0,   648,     0,     0,   651,     0,   653,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   677,     0,   679,     0,     0,     0,     0,
     682,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   697,     0,   699,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   707,     0,   709,     0,     0,     0,     0,
       0,     0,     0,   717,     0,   719,     0,     0,     0,     0,
       0,     0,     0,   726,     0,   728,     0,     0,     0,     0,
       0,   734,     0,   736,     0,     0,     0,     0,     0,   740,
       0,     0,     0,   744,     0,     0,     0,   748,     0,     0,
       0,   752,     0,     0,     0,   756,     0,     0,     0,   760,
       0,     0,     0,   764,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   274,   275,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148
};

static const yytype_int16 yycheck[] =
{
     223,   275,   225,   262,   272,   258,   229,   261,   231,   271,
     233,   268,   242,    18,   237,   259,   239,   260,   241,   182,
     183,   244,   253,   246,   187,   188,   254,   250,   269,   252,
     270,   254,   245,   203,   256,   258,   252,   260,   185,   262,
       3,   264,   265,   266,   267,   251,   269,   270,   271,   272,
     250,   246,    10,    11,     4,   218,   219,   220,    24,    25,
      26,    27,   181,   214,    10,    11,   257,   186,   248,   216,
     247,     0,    80,    81,    82,    83,    10,    11,    86,    87,
      88,    89,    21,    22,    82,   227,   244,     7,     8,   249,
      10,    11,    12,     5,    14,    15,    62,    63,   217,    76,
      77,     1,    77,    78,   255,   243,   248,     7,     8,   279,
     280,    88,    12,    52,    14,    15,     6,    17,    18,    19,
      20,   263,    76,    81,    82,    79,   268,    80,    82,    82,
      88,   273,   274,   275,    88,    81,    82,   284,    76,    77,
      82,    87,    17,    18,    19,    20,    79,    81,    82,    82,
      88,    76,    77,    76,    77,   163,   164,   165,   166,    76,
      77,    79,    82,    88,    87,    17,    18,    19,    20,    76,
      90,    88,    79,    76,    77,    82,    82,    76,    77,    80,
      87,    82,    82,    79,    87,    76,    77,    88,    87,    87,
      90,    77,    78,    87,   160,   203,    87,    77,    78,    77,
      78,    16,    88,    76,   209,    87,    79,    91,    88,    82,
      88,    82,   435,    88,   437,   474,   484,   470,   441,   473,
     443,   483,   445,   480,   454,    91,   449,   471,   451,   472,
     453,    77,    78,   456,   465,   458,    88,    13,   466,   462,
     481,   464,   482,   466,   457,    89,   468,   470,   464,   472,
      89,   474,    82,   476,   477,   478,   479,   463,   481,   482,
     483,   484,   462,   458,   494,   518,   540,   526,   536,   432,
     524,   528,   534,   496,   497,   498,   520,   500,   469,   522,
     460,   512,   459,   506,   507,   513,   499,   510,   511,   530,
     513,   514,   532,   515,   510,   518,   519,   439,   456,   522,
     523,   461,   508,   526,   527,   500,   506,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   467,   455,   460,   228,
      82,   230,    91,   503,   501,   516,   235,   236,     9,   238,
       9,   240,     9,   475,    77,    78,    77,    78,   480,   497,
     249,   184,   251,   485,   504,    88,    87,   256,   257,    80,
     259,    82,   261,    69,    77,    78,    87,   495,    77,    78,
     502,   503,    95,     7,     8,    88,    10,    11,    12,    88,
      14,    15,    77,    78,    77,    78,    94,    77,    78,   542,
      77,    78,    95,    88,    95,    88,   528,   529,    88,    77,
      78,    88,   159,    77,    78,    77,    78,   539,   540,    95,
      88,   490,   625,   626,    88,    87,   629,   158,   631,   632,
      -1,   634,    -1,   636,    -1,   638,   639,   640,   641,    77,
      78,    77,    78,    77,    78,    77,    78,    -1,    77,    78,
      88,    -1,    88,    -1,    88,    -1,    88,   660,    82,    88,
     663,    -1,   665,   666,    77,    78,    -1,   670,    -1,   672,
     673,   674,    77,    78,    -1,    88,    77,    78,    -1,    77,
      78,   624,    -1,    88,    77,    78,    -1,    88,   691,    87,
     693,    77,    78,   696,    87,    -1,    77,    78,    77,    78,
     703,    87,   705,   706,    -1,   627,    87,    -1,    87,    -1,
     713,    -1,   715,   716,    -1,   637,    77,    78,    76,    77,
     723,    -1,   725,    77,    78,    83,    87,    -1,   731,    -1,
     733,    77,    78,    87,    76,    77,   739,    77,    78,    -1,
     743,    87,   492,   493,   747,    77,    78,    87,   751,   671,
      -1,   440,   755,   442,   676,    87,   759,    -1,   447,   448,
     763,   450,    -1,   452,    -1,    77,    78,    77,    78,    -1,
      85,    86,   461,    88,   463,    87,    -1,    87,    -1,   468,
     469,    -1,   471,    -1,   473,    77,    78,    77,    78,    77,
      78,    77,    78,    77,    78,    87,    -1,    87,    -1,    87,
      -1,    87,    -1,    87,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,   504,   505,    -1,    -1,   508,
     509,    -1,    -1,    -1,    -1,    -1,   515,   516,   517,    -1,
      -1,   520,   521,    -1,    -1,   524,   525,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   628,
      -1,   630,    -1,    -1,   633,    -1,   635,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   662,    -1,   664,    -1,    -1,    -1,    -1,
     669,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   690,    -1,   692,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   702,    -1,   704,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   712,    -1,   714,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   722,    -1,   724,    -1,    -1,    -1,    -1,
      -1,   730,    -1,   732,    -1,    -1,    -1,    -1,    -1,   738,
      -1,    -1,    -1,   742,    -1,    -1,    -1,   746,    -1,    -1,
      -1,   750,    -1,    -1,    -1,   754,    -1,    -1,    -1,   758,
      -1,    -1,    -1,   762,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    93,    94,     0,     4,    95,    82,    96,    97,
       5,    98,   100,    79,    82,    99,     6,   101,   105,    79,
     103,     7,     8,    10,    11,    12,    14,    15,    82,   106,
     107,   116,   117,   128,   137,   141,   144,   171,   102,   171,
     171,    82,   170,   170,   170,   170,   170,   108,    79,   104,
     118,   129,   110,   138,   142,   145,    87,   113,    87,    87,
     171,    91,    91,    16,   146,   114,   109,   120,   131,   111,
      82,   174,   170,   170,    85,    86,    88,   115,    89,   148,
      17,    18,    19,    20,    88,   121,    17,    18,    19,    20,
      88,   132,   113,   139,   143,   149,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   175,
     175,   175,   175,   119,   175,   175,   175,   175,   130,   112,
      13,   146,     1,    17,    18,    19,    20,    82,    90,   116,
     137,   141,   144,   150,   151,   154,   158,   163,   167,   172,
     122,   123,   126,   124,    89,   133,   134,   136,   135,    76,
      79,    82,    87,   147,   251,   301,   148,   170,   175,   175,
     175,    82,   175,   168,    82,   173,   174,   172,   172,   105,
     173,   174,   172,   172,   302,   140,   152,   155,   164,   161,
     159,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   169,   175,   176,   127,
     125,    90,    88,   251,    91,   173,   174,   172,   172,   172,
      80,    82,    87,   180,   275,    77,    78,    87,   179,   181,
     277,    87,   179,   184,   279,    77,    78,    87,   178,   188,
     281,    87,   179,   189,   283,    76,    77,    87,   177,   190,
     285,    87,   177,   195,   287,    87,   178,   196,   289,    87,
     179,   205,   291,    87,   178,   214,   293,    87,   179,   230,
     295,    81,    87,   107,   246,   297,    87,   179,   247,   299,
     301,    87,   178,   252,   303,    87,   178,   253,   305,    87,
     179,   255,   307,    87,   178,   257,   309,    87,   179,   261,
     311,    87,   178,   265,   313,    87,   179,   270,   315,   180,
     181,   184,   188,   189,   190,   195,   196,   205,   214,   230,
     246,   247,   251,   252,   253,   255,   257,   261,   265,   270,
      87,   177,   317,   343,    87,   179,   321,   345,    87,   179,
     323,   347,    87,   179,   326,   349,    87,   179,   330,   351,
     317,   321,   323,   326,   330,   177,   334,   177,   341,    87,
     341,   353,     9,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,   176,   176,   173,   153,
     156,   165,   162,   160,   276,   278,   182,   280,   185,   282,
     284,   286,   191,   288,   290,   197,   292,   206,   294,   215,
     296,   231,   298,   300,   248,   304,   306,   254,   308,   256,
     310,   258,   312,   262,   314,   266,   316,   271,   344,   318,
     346,   322,   348,   324,   350,   327,   352,   331,   335,   342,
     354,   172,     9,   157,   157,   166,   175,   176,   166,   166,
      88,   180,    88,   181,   179,    88,   184,   179,    88,   188,
      88,   189,    88,   190,   177,    88,   195,    88,   196,   178,
      88,   205,   179,    88,   214,   178,    88,   230,   179,    88,
     246,    88,   247,   179,    88,   252,    88,   253,   178,    88,
     255,   179,    88,   257,   178,    88,   261,   179,    88,   265,
     178,    88,   270,   179,    88,   317,   177,    88,   321,   179,
      88,   323,   179,    88,   326,   179,    88,   330,   179,   179,
     177,    88,   341,   172,     9,   183,   186,   192,   198,   207,
     216,   232,   249,   259,   263,   267,   272,   319,   325,   328,
     332,   336,   172,   179,   179,   177,   178,   179,   178,   179,
     179,   178,   179,   178,   179,   177,   179,   179,   179,   179,
     187,   193,   199,   208,   217,   233,   250,   260,   264,   268,
     273,   320,   329,   333,   337,   179,   194,   178,   179,   178,
     179,   179,   178,   179,   177,   179,   179,   179,    83,   177,
     200,   209,   218,   234,   269,   274,   338,   178,   179,   178,
     179,   179,   201,   210,   219,   235,   339,   178,   179,   178,
     179,   179,   202,   211,   220,   236,   340,   178,   179,   178,
     179,   179,   203,   212,   221,   237,   178,   179,   178,   179,
     204,   213,   222,   238,   178,   179,   178,   179,   223,   239,
     178,   179,   224,   240,   178,   179,   225,   241,   178,   179,
     226,   242,   178,   179,   227,   243,   178,   179,   228,   244,
     178,   179,   229,   245,   178,   179
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
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
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  YYUSE (yyvaluep);

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
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
        case 3:

/* Line 1464 of yacc.c  */
#line 217 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)) == false) { YYABORT; } ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 218 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->checkHeader() == true) { YYABORT; } ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 221 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 235 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 252 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 254 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 286 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(1) - (1)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 289 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString1.c_str(), 
                                            0,
                                            SKEL->_tmpBitVector1     ); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 294 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 297 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(4) - (4)].stringVal); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 298 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString2.c_str(), 
                                            SKEL->_tmpString1.c_str(),
                                            SKEL->_tmpBitVector1     ); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 303 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 314 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::Cluster; ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 315 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::MT;      ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 326 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 327 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 328 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 336 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 337 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 339 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 340 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 342 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 343 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 344 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 346 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 347 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 348 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 351 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 352 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 353 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 361 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 362 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 364 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 365 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 367 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 368 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 370 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 371 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 375 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 377 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 379 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 382 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 386 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 388 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 390 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 399 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 401 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 410 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 411 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 417 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 433 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 434 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 435 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 439 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 440 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 441 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 445 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 449 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 450 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 451 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 453 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 454 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { 
               SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), 0, (yyvsp[(4) - (4)].stringVal)); 

               Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(4) - (4)].stringVal));

               if(SKEL->getMapFieldTypes() == true)
                 iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(4) - (4)].stringVal), iFieldTypeId);

               SKEL->getLexer()->expectType(iFieldTypeId);
             ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 464 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 468 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 469 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 470 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 474 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 478 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 485 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 493 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 625 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 626 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 629 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 630 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); ;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 633 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 634 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 638 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    ;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 641 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 644 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 645 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 647 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 653 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 654 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 655 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 657 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 664 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 670 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    ;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 675 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 676 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 678 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 683 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 689 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 696 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 701 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 702 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 703 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 704 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 705 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 706 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 707 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 708 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 710 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(7) - (17)].doubleVal), (yyvsp[(13) - (17)].doubleVal),
            (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal),
            (yyvsp[(5) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    ;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 719 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 720 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 721 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 722 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 723 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 724 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 725 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 726 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 728 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[(1) - (17)].floatVal),  (yyvsp[(7) - (17)].floatVal), (yyvsp[(13) - (17)].floatVal),
            (yyvsp[(3) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal),
            (yyvsp[(5) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    ;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 737 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 738 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 739 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 740 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 741 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 742 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 743 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 744 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 745 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 746 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 747 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 748 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 749 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 750 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 751 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 753 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(9) - (31)].doubleVal), (yyvsp[(17) - (31)].doubleVal), (yyvsp[(25) - (31)].doubleVal),
            (yyvsp[(3) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal),
            (yyvsp[(5) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal),
            (yyvsp[(7) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    ;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 763 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 764 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 765 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 766 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 767 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 768 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 769 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 770 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 771 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 772 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 773 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 774 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 775 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 776 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 777 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 779 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[(1) - (31)].floatVal),  (yyvsp[(9) - (31)].floatVal), (yyvsp[(17) - (31)].floatVal), (yyvsp[(25) - (31)].floatVal),
            (yyvsp[(3) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal),
            (yyvsp[(5) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal),
            (yyvsp[(7) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    ;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 790 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 793 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 794 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 795 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 797 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    ;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 804 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 808 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 812 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    ;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 818 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 823 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 825 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    ;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 831 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 833 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 839 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 840 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 841 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 842 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    ;}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 848 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 849 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 850 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 851 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    ;}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 857 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 858 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 859 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 860 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 861 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    ;}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 867 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 868 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 869 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 870 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 871 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    ;}
    break;

  case 421:

/* Line 1464 of yacc.c  */
#line 1047 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 422:

/* Line 1464 of yacc.c  */
#line 1048 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 423:

/* Line 1464 of yacc.c  */
#line 1049 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 424:

/* Line 1464 of yacc.c  */
#line 1051 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    ;}
    break;

  case 425:

/* Line 1464 of yacc.c  */
#line 1058 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 426:

/* Line 1464 of yacc.c  */
#line 1060 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 427:

/* Line 1464 of yacc.c  */
#line 1066 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 428:

/* Line 1464 of yacc.c  */
#line 1067 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 429:

/* Line 1464 of yacc.c  */
#line 1069 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 430:

/* Line 1464 of yacc.c  */
#line 1075 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 431:

/* Line 1464 of yacc.c  */
#line 1076 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 432:

/* Line 1464 of yacc.c  */
#line 1077 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 433:

/* Line 1464 of yacc.c  */
#line 1079 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 434:

/* Line 1464 of yacc.c  */
#line 1085 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 435:

/* Line 1464 of yacc.c  */
#line 1086 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 436:

/* Line 1464 of yacc.c  */
#line 1087 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 437:

/* Line 1464 of yacc.c  */
#line 1089 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 438:

/* Line 1464 of yacc.c  */
#line 1095 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue();  ;}
    break;

  case 439:

/* Line 1464 of yacc.c  */
#line 1096 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 440:

/* Line 1464 of yacc.c  */
#line 1097 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 441:

/* Line 1464 of yacc.c  */
#line 1098 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 442:

/* Line 1464 of yacc.c  */
#line 1099 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 443:

/* Line 1464 of yacc.c  */
#line 1100 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 444:

/* Line 1464 of yacc.c  */
#line 1102 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[(3) - (13)].floatVal), (yyvsp[(5) - (13)].floatVal), (yyvsp[(7) - (13)].floatVal), (yyvsp[(9) - (13)].floatVal), (yyvsp[(11) - (13)].floatVal), (yyvsp[(13) - (13)].floatVal));
        
        bv.setState((yyvsp[(1) - (13)].intVal));

        SKEL->addVolumeValue(bv);
    ;}
    break;

  case 445:

/* Line 1464 of yacc.c  */
#line 1112 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 446:

/* Line 1464 of yacc.c  */
#line 1114 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[(1) - (3)].intVal), (yyvsp[(3) - (3)].intVal)));
    ;}
    break;



/* Line 1464 of yacc.c  */
#line 3862 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
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
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 1167 "/home/gerrit/Projects/OpenSG/OSG2/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

