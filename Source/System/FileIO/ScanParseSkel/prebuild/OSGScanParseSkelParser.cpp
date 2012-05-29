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
#line 80 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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
#line 41 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"

    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;



/* Line 214 of yacc.c  */
#line 212 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 49 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


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
#line 264 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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
#define YYNRULES  471
/* YYNRULES -- Number of states.  */
#define YYNSTATES  767

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
     805,   813,   815,   817,   819,   821,   823,   824,   828,   829,
     833,   834,   835,   836,   843,   844,   845,   846,   853,   854,
     855,   856,   857,   866,   867,   868,   869,   870,   879,   881,
     885,   888,   889,   891,   895,   898,   899,   901,   905,   908,
     909,   911,   915,   918,   919,   921,   925,   928,   929,   931,
     935,   938,   939,   941,   945,   948,   949,   951,   955,   958,
     959,   961,   965,   968,   969,   971,   975,   978,   979,   981,
     985,   988,   989,   991,   995,   998,   999,  1001,  1005,  1008,
    1009,  1011,  1015,  1018,  1019,  1021,  1025,  1028,  1029,  1031,
    1035,  1038,  1039,  1041,  1045,  1048,  1049,  1051,  1055,  1058,
    1059,  1061,  1065,  1068,  1069,  1071,  1075,  1078,  1079,  1081,
    1085,  1088,  1089,  1090,  1091,  1092,  1100,  1101,  1105,  1106,
    1107,  1113,  1114,  1115,  1116,  1124,  1125,  1126,  1127,  1135,
    1136,  1137,  1138,  1139,  1140,  1141,  1155,  1156,  1160,  1162,
    1166,  1169,  1170,  1172,  1176,  1179,  1180,  1182,  1186,  1189,
    1190,  1192,  1196,  1199,  1200,  1202,  1206,  1209,  1210,  1212,
    1216,  1219
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
     250,   179,    -1,    79,    -1,    82,    -1,    76,    -1,    77,
      -1,   178,    -1,    -1,   178,   254,   178,    -1,    -1,   179,
     256,   179,    -1,    -1,    -1,    -1,   178,   258,   178,   259,
     178,   260,    -1,    -1,    -1,    -1,   179,   262,   179,   263,
     179,   264,    -1,    -1,    -1,    -1,    -1,   178,   266,   178,
     267,   178,   268,   178,   269,    -1,    -1,    -1,    -1,    -1,
     179,   271,   179,   272,   179,   273,   179,   274,    -1,   180,
      -1,    87,   276,    88,    -1,   276,   180,    -1,    -1,   181,
      -1,    87,   278,    88,    -1,   278,   181,    -1,    -1,   184,
      -1,    87,   280,    88,    -1,   280,   184,    -1,    -1,   188,
      -1,    87,   282,    88,    -1,   282,   188,    -1,    -1,   189,
      -1,    87,   284,    88,    -1,   284,   189,    -1,    -1,   190,
      -1,    87,   286,    88,    -1,   286,   190,    -1,    -1,   195,
      -1,    87,   288,    88,    -1,   288,   195,    -1,    -1,   196,
      -1,    87,   290,    88,    -1,   290,   196,    -1,    -1,   205,
      -1,    87,   292,    88,    -1,   292,   205,    -1,    -1,   214,
      -1,    87,   294,    88,    -1,   294,   214,    -1,    -1,   230,
      -1,    87,   296,    88,    -1,   296,   230,    -1,    -1,   246,
      -1,    87,   298,    88,    -1,   298,   246,    -1,    -1,   247,
      -1,    87,   300,    88,    -1,   300,   247,    -1,    -1,   251,
      -1,    87,   302,    88,    -1,   302,   251,    -1,    -1,   252,
      -1,    87,   304,    88,    -1,   304,   252,    -1,    -1,   253,
      -1,    87,   306,    88,    -1,   306,   253,    -1,    -1,   255,
      -1,    87,   308,    88,    -1,   308,   255,    -1,    -1,   257,
      -1,    87,   310,    88,    -1,   310,   257,    -1,    -1,   261,
      -1,    87,   312,    88,    -1,   312,   261,    -1,    -1,   265,
      -1,    87,   314,    88,    -1,   314,   265,    -1,    -1,   270,
      -1,    87,   316,    88,    -1,   316,   270,    -1,    -1,    -1,
      -1,    -1,   177,   318,   177,   319,   177,   320,   177,    -1,
      -1,   179,   322,   179,    -1,    -1,    -1,   179,   324,   179,
     325,   179,    -1,    -1,    -1,    -1,   179,   327,   179,   328,
     179,   329,   179,    -1,    -1,    -1,    -1,   179,   331,   179,
     332,   179,   333,   179,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,   335,   179,   336,   179,   337,   179,   338,   179,
     339,   179,   340,   179,    -1,    -1,   177,   342,   177,    -1,
     317,    -1,    87,   344,    88,    -1,   344,   317,    -1,    -1,
     321,    -1,    87,   346,    88,    -1,   346,   321,    -1,    -1,
     323,    -1,    87,   348,    88,    -1,   348,   323,    -1,    -1,
     326,    -1,    87,   350,    88,    -1,   350,   326,    -1,    -1,
     330,    -1,    87,   352,    88,    -1,   352,   330,    -1,    -1,
     341,    -1,    87,   354,    88,    -1,   354,   341,    -1,    -1
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
     793,   803,   807,   811,   815,   821,   827,   827,   835,   835,
     843,   844,   845,   843,   852,   853,   854,   852,   861,   862,
     863,   864,   861,   871,   872,   873,   874,   871,   881,   882,
     885,   886,   889,   890,   893,   894,   897,   898,   901,   902,
     905,   906,   909,   910,   913,   914,   917,   918,   921,   922,
     925,   926,   929,   930,   933,   934,   937,   938,   941,   942,
     945,   946,   949,   950,   953,   954,   957,   958,   961,   962,
     965,   966,   969,   970,   973,   974,   977,   978,   981,   982,
     985,   986,   989,   990,   993,   994,   997,   998,  1001,  1002,
    1005,  1006,  1009,  1010,  1013,  1014,  1017,  1018,  1021,  1022,
    1025,  1026,  1029,  1030,  1033,  1034,  1037,  1038,  1041,  1042,
    1045,  1046,  1051,  1052,  1053,  1051,  1062,  1062,  1070,  1071,
    1070,  1079,  1080,  1081,  1079,  1089,  1090,  1091,  1089,  1099,
    1100,  1101,  1102,  1103,  1104,  1099,  1116,  1116,  1124,  1125,
    1128,  1129,  1132,  1133,  1136,  1137,  1140,  1141,  1144,  1145,
    1148,  1149,  1152,  1153,  1156,  1157,  1160,  1161,  1164,  1165,
    1168,  1169
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
     247,   251,   251,   251,   251,   252,   254,   253,   256,   255,
     258,   259,   260,   257,   262,   263,   264,   261,   266,   267,
     268,   269,   265,   271,   272,   273,   274,   270,   275,   275,
     276,   276,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   290,   290,
     291,   291,   292,   292,   293,   293,   294,   294,   295,   295,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   304,   305,   305,
     306,   306,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   314,   315,   315,
     316,   316,   318,   319,   320,   317,   322,   321,   324,   325,
     323,   327,   328,   329,   326,   331,   332,   333,   330,   335,
     336,   337,   338,   339,   340,   334,   342,   341,   343,   343,
     344,   344,   345,   345,   346,   346,   347,   347,   348,   348,
     349,   349,   350,   350,   351,   351,   352,   352,   353,   353,
     354,   354
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
       7,     1,     1,     1,     1,     1,     0,     3,     0,     3,
       0,     0,     0,     6,     0,     0,     0,     6,     0,     0,
       0,     0,     8,     0,     0,     0,     0,     8,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     0,     0,     0,     7,     0,     3,     0,     0,
       5,     0,     0,     0,     7,     0,     0,     0,     7,     0,
       0,     0,     0,     0,     0,    13,     0,     3,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0
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
     314,   311,   312,   393,    59,   390,    81,    32,    72,    91,
      94,   105,   102,    99,     0,   121,    48,    50,    55,    52,
       0,    63,    65,    69,    67,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,     0,     0,   111,     0,   116,
       0,     0,    44,   391,   392,     0,    92,    95,   106,   103,
     100,   237,   238,   341,   338,   176,   235,   236,   345,   239,
     342,   177,   349,   242,   346,   178,   233,   234,   353,   246,
     350,   179,   357,   247,   354,   180,   231,   232,   361,   248,
     358,   181,   365,   254,   362,   182,   369,   255,   366,   183,
     373,   264,   370,   184,   377,   273,   374,   185,   381,   289,
     378,   186,   306,   385,   305,   382,   187,   389,   307,   386,
     188,   189,   397,   315,   394,   190,   401,   316,   398,   191,
     405,   318,   402,   192,   409,   320,   406,   193,   413,   324,
     410,   194,   417,   328,   414,   195,   421,   333,   418,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   451,   422,   448,   218,   455,   426,   452,   219,   459,
     428,   456,   220,   463,   431,   460,   221,   467,   435,   464,
     222,   223,   224,   225,   226,   227,   439,   228,   446,   229,
     471,   468,   230,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    53,    73,
      97,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,    93,    96,   107,     0,   108,   104,
     101,   339,   340,   343,   344,   240,   347,   348,   243,   351,
     352,   355,   356,   359,   360,   249,   363,   364,   367,   368,
     256,   371,   372,   265,   375,   376,   274,   379,   380,   290,
     383,   384,   387,   388,   308,   395,   396,   399,   400,   317,
     403,   404,   319,   407,   408,   321,   411,   412,   325,   415,
     416,   329,   419,   420,   334,   449,   450,   423,   453,   454,
     427,   457,   458,   429,   461,   462,   432,   465,   466,   436,
     440,   447,   469,   470,    98,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   109,   241,   244,   250,   257,   266,   275,
     291,   309,   322,   326,   330,   335,   424,   430,   433,   437,
     441,     0,   253,     0,     0,     0,     0,     0,   323,   327,
       0,     0,     0,     0,     0,     0,   245,     0,   258,   267,
     276,   292,   310,   331,   336,   425,   434,   438,   442,   251,
     252,     0,     0,     0,     0,   332,   337,     0,   259,   268,
     277,   293,   443,     0,     0,     0,     0,     0,   260,   269,
     278,   294,   444,     0,     0,     0,     0,     0,   261,   270,
     279,   295,   445,     0,     0,     0,     0,   262,   271,   280,
     296,     0,     0,     0,     0,   263,   272,   281,   297,     0,
       0,   282,   298,     0,     0,   283,   299,     0,     0,   284,
     300,     0,     0,   285,   301,     0,     0,   286,   302,     0,
       0,   287,   303,     0,     0,   288,   304
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   344,    47,    66,    52,    69,
     159,    57,    65,    77,    31,    32,    50,   153,    67,    85,
     180,   181,   183,   281,   182,   280,    33,    51,   158,    68,
      91,   185,   186,   188,   187,    34,    53,    93,   216,    35,
      54,    94,    36,    55,    64,   194,    79,    95,   173,   174,
     217,   490,   175,   218,   491,   544,   176,   221,   494,   220,
     493,   177,   219,   492,   546,   178,   204,   277,    42,    37,
     179,   206,    71,   547,   548,   319,   309,   299,   294,   300,
     497,   626,   304,   499,   627,   661,   310,   314,   320,   503,
     628,   662,   677,   324,   328,   506,   629,   663,   691,   703,
     713,   723,   731,   332,   508,   630,   664,   692,   704,   714,
     724,   732,   336,   510,   631,   665,   693,   705,   715,   725,
     733,   739,   743,   747,   751,   755,   759,   763,   340,   512,
     632,   666,   694,   706,   716,   726,   734,   740,   744,   748,
     752,   756,   760,   764,   345,   349,   515,   633,   667,   195,
     354,   358,   518,   362,   520,   366,   522,   634,   668,   370,
     524,   635,   669,   374,   526,   636,   670,   695,   378,   528,
     637,   671,   696,   295,   495,   301,   496,   305,   498,   311,
     500,   315,   501,   321,   502,   325,   504,   329,   505,   333,
     507,   337,   509,   341,   511,   346,   513,   350,   514,   351,
     215,   355,   516,   359,   517,   363,   519,   367,   521,   371,
     523,   375,   525,   379,   527,   403,   530,   638,   672,   407,
     532,   411,   534,   639,   415,   536,   640,   673,   419,   538,
     641,   674,   427,   539,   642,   675,   697,   707,   717,   429,
     540,   404,   529,   408,   531,   412,   533,   416,   535,   420,
     537,   432,   541
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -305
static const yytype_int16 yypact[] =
{
      35,  -305,    69,    59,  -305,    25,  -305,  -305,  -305,   139,
       7,  -305,   146,  -305,  -305,  -305,    86,  -305,   127,  -305,
    -305,    85,    85,    89,    89,    89,    89,    89,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,    95,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,   111,  -305,  -305,
     119,   121,    85,   120,   136,   215,  -305,  -305,  -305,  -305,
    -305,   150,    89,    89,  -305,   504,   147,    42,   105,   111,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
     943,   943,   943,   943,  -305,  -305,   943,   943,   943,   943,
    -305,  -305,  -305,   224,   215,    80,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,   156,  -305,  -305,  -305,  -305,   123,   147,
      89,  -305,  -305,   943,   943,   943,   596,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
     166,   150,   168,   168,  -305,   166,   150,   168,   168,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,   833,  -305,  -305,  -305,  -305,  -305,
     362,  -305,  -305,  -305,  -305,    87,   189,   166,   150,   168,
     168,   168,   114,     6,    81,   126,   259,    74,   100,   318,
     397,   426,   428,    91,   434,   123,   440,   448,   468,   470,
     488,   490,   492,    63,    37,    37,    50,    37,    43,    43,
      50,    37,    50,    37,   102,    37,   594,    50,    50,    37,
      50,    37,    50,    37,   258,   494,   496,   507,   510,    43,
      37,    37,    37,    37,    43,    43,   278,  -305,   292,  -305,
     888,   888,  -305,  -305,  -305,   166,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,   168,   114,     6,    81,   126,   259,    74,
     100,   318,   397,   426,   428,    91,   434,   123,   440,   448,
     468,   470,   488,   490,   492,    63,    37,    37,    50,    37,
      43,    43,    50,    37,    50,    37,   102,    37,   594,    50,
      50,    37,    50,    37,    50,    37,   258,   494,   496,   507,
     510,    43,    37,    37,    37,    37,    43,  -305,  -305,  -305,
     311,   311,   833,   833,   833,   271,   104,    37,   279,    37,
     301,   304,    41,    43,    72,   306,    50,   313,    37,   322,
      50,   342,    37,    65,   344,    37,   346,   348,    50,   350,
      37,   368,    50,   376,    37,   381,    50,   383,    37,   103,
      43,   388,    37,   400,    37,   409,    37,   421,    37,    37,
      43,   109,  -305,   168,  -305,  -305,  -305,   315,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,   168,    37,    37,    43,    50,
      37,    50,    37,    37,    50,    37,    50,    37,    43,    37,
      37,    37,    37,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,    37,  -305,    50,    37,    50,    37,    37,  -305,  -305,
      50,    37,    43,    37,    37,    37,  -305,   473,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,    50,    37,    50,    37,  -305,  -305,    37,  -305,  -305,
    -305,  -305,  -305,    50,    37,    50,    37,    37,  -305,  -305,
    -305,  -305,  -305,    50,    37,    50,    37,    37,  -305,  -305,
    -305,  -305,  -305,    50,    37,    50,    37,  -305,  -305,  -305,
    -305,    50,    37,    50,    37,  -305,  -305,  -305,  -305,    50,
      37,  -305,  -305,    50,    37,  -305,  -305,    50,    37,  -305,
    -305,    50,    37,  -305,  -305,    50,    37,  -305,  -305,    50,
      37,  -305,  -305,    50,    37,  -305,  -305
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,   148,  -305,    -3,  -305,  -305,  -305,  -305,
    -305,   261,  -305,  -305,   244,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,   249,  -305,  -305,  -305,   254,
    -305,  -305,   267,  -305,   269,  -305,   207,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -120,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -304,  -305,  -305,  -305,    28,    44,
    -163,  -149,   -78,    -9,  -171,  -143,    90,  -224,  -231,  -128,
    -305,  -305,  -134,  -305,  -305,  -305,  -214,  -196,  -144,  -305,
    -305,  -305,  -305,  -182,  -180,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -201,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -207,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -213,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -232,  -229,  -305,  -305,  -305,  -151,
    -223,  -176,  -305,  -248,  -305,  -243,  -305,  -305,  -305,  -254,
    -305,  -305,  -305,  -253,  -305,  -305,  -305,  -305,  -260,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,   217,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -264,  -305,  -305,  -305,  -242,
    -305,  -241,  -305,  -305,  -259,  -305,  -305,  -305,  -269,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -275,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     303,   431,   313,   400,   425,   421,   331,   398,   339,   399,
     348,   396,   380,   424,   361,    30,   369,   397,   377,   208,
     209,   303,   391,   313,   213,   214,   392,   331,   422,   339,
     423,   348,   383,   279,   394,   361,   211,   369,     1,   377,
     390,   406,   410,   414,   418,   389,   406,   410,   414,   418,
     388,   384,    43,    44,    45,    46,   288,   289,   290,    80,
      81,    82,    83,     5,   284,    39,    40,   386,   286,     4,
     387,   149,   150,   151,   152,    23,    24,   154,   155,   156,
     157,   162,   395,   296,   297,   323,    13,    21,    22,    14,
      72,    73,    25,   298,    26,    27,    60,   163,   164,   165,
     166,    23,    24,   207,   385,   393,   323,     7,   212,   487,
     488,   382,    23,    24,   296,   297,   381,   316,   317,   316,
     317,   402,    86,    87,    88,    89,   402,   306,   307,   563,
      84,   426,   428,   428,    21,    22,   489,    23,    24,    25,
     287,    26,    27,   291,    10,   292,   342,    28,   316,   317,
     316,   317,    16,   580,   199,   200,   201,   203,   296,   297,
     566,   318,   167,   189,   190,    19,   191,    28,   302,   192,
     168,    41,   342,    28,    48,   283,   316,   317,   343,   316,
     317,   296,   297,   342,    28,   316,   317,   322,   198,   549,
     550,   605,   553,    90,   291,   278,   292,   622,    56,   189,
     190,   293,   191,   306,   307,   192,    58,    30,    59,    28,
     193,    61,   303,   308,   313,   400,   425,   421,   331,   398,
     339,   399,   348,   396,   380,   424,   361,    62,   369,   397,
     377,    63,    70,   303,   391,   313,    78,   160,   392,   331,
     422,   339,   423,   348,   383,   184,   394,   361,   205,   369,
     167,   377,   390,   406,   410,   414,   418,   389,   406,   410,
     414,   418,   388,   384,   552,   606,   623,   603,   618,   597,
     542,   591,   600,   555,   303,   558,   615,   313,   594,   386,
     285,   581,   387,   331,   573,   583,   560,   339,   579,   609,
     348,   584,   612,   586,   395,   361,   592,   323,   578,   369,
     598,   433,   575,   377,   604,   562,   572,   406,   610,   410,
     613,   414,   616,   418,   619,   620,   385,   393,   323,   327,
     543,   335,   567,   382,   625,   569,   353,   357,   381,   365,
      92,   373,   210,   402,   316,   317,   296,   297,   402,   169,
     327,   588,   335,   426,   170,   401,   312,   353,   357,   171,
     365,   291,   373,   292,   316,   317,   296,   297,   564,   551,
     565,   323,   172,   161,   557,   430,   197,   556,   554,    21,
      22,   545,    23,    24,    25,   196,    26,    27,   306,   307,
     624,   296,   297,   306,   307,     0,   402,   607,     0,   559,
     296,   297,   561,     0,   568,   306,   307,   621,   428,   306,
     307,   571,   644,   645,     0,   326,   648,     0,   650,   651,
     574,   653,     0,   655,     0,   657,   658,   659,   660,   296,
     297,   296,   297,   306,   307,   306,   307,   296,   297,     0,
     577,     0,   582,     0,   585,     0,   587,   676,   590,     0,
     679,     0,   681,   682,    28,   306,   307,   684,     0,   686,
     687,   688,   282,   296,   297,     0,   593,     0,   306,   307,
     296,   297,   643,     0,   596,   296,   297,     0,   699,   599,
     701,   602,     0,   702,   296,   297,   608,   296,   297,     0,
     709,     0,   711,   712,   330,   646,   296,   297,   611,     0,
     719,     0,   721,   722,     0,   656,     0,   614,   296,   297,
     728,     0,   730,   306,   307,   296,   297,     0,   736,   617,
     738,   296,   297,   334,     0,   338,   742,   306,   307,     0,
     746,   347,     0,     0,   750,   306,   307,   352,   754,   685,
       0,   327,   758,   335,   690,   356,   762,     0,   353,   357,
     766,   365,     0,   373,     0,   296,   297,   306,   307,   316,
     317,     0,   327,     0,   335,   360,   689,   364,     0,   353,
     357,     0,   365,     0,   373,   296,   297,   306,   307,   296,
     297,   296,   297,   296,   297,   368,     0,   372,     0,   376,
       0,   405,     0,   409,   296,   297,     0,   296,   297,    74,
      75,     0,    76,     0,   413,   327,   570,   417,     0,   335,
     576,     0,     0,     0,     0,     0,   353,   357,   589,     0,
       0,   365,   595,     0,     0,   373,   601,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     189,   190,     0,   191,     0,     0,   192,     0,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   647,
       0,   649,     0,     0,   652,     0,   654,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   678,     0,   680,     0,     0,     0,     0,
     683,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   698,     0,   700,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   708,     0,   710,     0,     0,     0,     0,
       0,     0,     0,   718,     0,   720,     0,     0,     0,     0,
       0,     0,     0,   727,     0,   729,     0,     0,     0,     0,
       0,   735,     0,   737,     0,     0,     0,     0,     0,   741,
       0,     0,     0,   745,     0,     0,     0,   749,     0,     0,
       0,   753,     0,     0,     0,   757,     0,     0,     0,   761,
       0,     0,     0,   765,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   275,   276,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148
};

static const yytype_int16 yycheck[] =
{
     224,   276,   226,   263,   273,   269,   230,   261,   232,   262,
     234,   259,   243,   272,   238,    18,   240,   260,   242,   182,
     183,   245,   254,   247,   187,   188,   255,   251,   270,   253,
     271,   255,   246,   204,   257,   259,   185,   261,     3,   263,
     253,   265,   266,   267,   268,   252,   270,   271,   272,   273,
     251,   247,    24,    25,    26,    27,   219,   220,   221,    17,
      18,    19,    20,     4,   215,    21,    22,   249,   217,     0,
     250,    80,    81,    82,    83,    10,    11,    86,    87,    88,
      89,     1,   258,    77,    78,   228,    79,     7,     8,    82,
      62,    63,    12,    87,    14,    15,    52,    17,    18,    19,
      20,    10,    11,   181,   248,   256,   249,    82,   186,   280,
     281,   245,    10,    11,    77,    78,   244,    76,    77,    76,
      77,   264,    17,    18,    19,    20,   269,    77,    78,    88,
      88,   274,   275,   276,     7,     8,   285,    10,    11,    12,
     218,    14,    15,    80,     5,    82,    81,    82,    76,    77,
      76,    77,     6,    88,   163,   164,   165,   166,    77,    78,
      88,    87,    82,    76,    77,    79,    79,    82,    87,    82,
      90,    82,    81,    82,    79,    88,    76,    77,    87,    76,
      77,    77,    78,    81,    82,    76,    77,    87,   160,   493,
     494,    88,    88,    88,    80,   204,    82,    88,    87,    76,
      77,    87,    79,    77,    78,    82,    87,   210,    87,    82,
      87,    91,   436,    87,   438,   475,   485,   481,   442,   473,
     444,   474,   446,   471,   455,   484,   450,    91,   452,   472,
     454,    16,    82,   457,   466,   459,    89,    13,   467,   463,
     482,   465,   483,   467,   458,    89,   469,   471,    82,   473,
      82,   475,   465,   477,   478,   479,   480,   464,   482,   483,
     484,   485,   463,   459,   495,   529,   541,   527,   537,   523,
     433,   519,   525,   497,   498,   499,   535,   501,   521,   461,
      91,   513,   462,   507,   508,   514,   500,   511,   512,   531,
     514,   515,   533,   516,   470,   519,   520,   440,   511,   523,
     524,     9,   509,   527,   528,   501,   507,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   460,   468,   461,   229,
       9,   231,   504,   457,     9,   505,   236,   237,   456,   239,
      69,   241,   184,   476,    76,    77,    77,    78,   481,    95,
     250,   517,   252,   486,    95,    87,    87,   257,   258,    95,
     260,    80,   262,    82,    76,    77,    77,    78,   502,    88,
     503,   504,    95,    94,   498,    87,   159,    88,   496,     7,
       8,   491,    10,    11,    12,   158,    14,    15,    77,    78,
     543,    77,    78,    77,    78,    -1,   529,   530,    -1,    88,
      77,    78,    88,    -1,    88,    77,    78,   540,   541,    77,
      78,    88,   626,   627,    -1,    87,   630,    -1,   632,   633,
      88,   635,    -1,   637,    -1,   639,   640,   641,   642,    77,
      78,    77,    78,    77,    78,    77,    78,    77,    78,    -1,
      88,    -1,    88,    -1,    88,    -1,    88,   661,    88,    -1,
     664,    -1,   666,   667,    82,    77,    78,   671,    -1,   673,
     674,   675,    90,    77,    78,    -1,    88,    -1,    77,    78,
      77,    78,   625,    -1,    88,    77,    78,    -1,   692,    88,
     694,    88,    -1,   697,    77,    78,    88,    77,    78,    -1,
     704,    -1,   706,   707,    87,   628,    77,    78,    88,    -1,
     714,    -1,   716,   717,    -1,   638,    -1,    88,    77,    78,
     724,    -1,   726,    77,    78,    77,    78,    -1,   732,    88,
     734,    77,    78,    87,    -1,    87,   740,    77,    78,    -1,
     744,    87,    -1,    -1,   748,    77,    78,    87,   752,   672,
      -1,   441,   756,   443,   677,    87,   760,    -1,   448,   449,
     764,   451,    -1,   453,    -1,    77,    78,    77,    78,    76,
      77,    -1,   462,    -1,   464,    87,    83,    87,    -1,   469,
     470,    -1,   472,    -1,   474,    77,    78,    77,    78,    77,
      78,    77,    78,    77,    78,    87,    -1,    87,    -1,    87,
      -1,    87,    -1,    87,    77,    78,    -1,    77,    78,    85,
      86,    -1,    88,    -1,    87,   505,   506,    87,    -1,   509,
     510,    -1,    -1,    -1,    -1,    -1,   516,   517,   518,    -1,
      -1,   521,   522,    -1,    -1,   525,   526,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      76,    77,    -1,    79,    -1,    -1,    82,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   629,
      -1,   631,    -1,    -1,   634,    -1,   636,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   663,    -1,   665,    -1,    -1,    -1,    -1,
     670,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   691,    -1,   693,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   703,    -1,   705,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   713,    -1,   715,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   723,    -1,   725,    -1,    -1,    -1,    -1,
      -1,   731,    -1,   733,    -1,    -1,    -1,    -1,    -1,   739,
      -1,    -1,    -1,   743,    -1,    -1,    -1,   747,    -1,    -1,
      -1,   751,    -1,    -1,    -1,   755,    -1,    -1,    -1,   759,
      -1,    -1,    -1,   763,    21,    22,    23,    24,    25,    26,
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
      77,    79,    82,    87,   147,   251,   301,   148,   170,   175,
     175,   175,    82,   175,   168,    82,   173,   174,   172,   172,
     105,   173,   174,   172,   172,   302,   140,   152,   155,   164,
     161,   159,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,   169,   175,   176,
     127,   125,    90,    88,   251,    91,   173,   174,   172,   172,
     172,    80,    82,    87,   180,   275,    77,    78,    87,   179,
     181,   277,    87,   179,   184,   279,    77,    78,    87,   178,
     188,   281,    87,   179,   189,   283,    76,    77,    87,   177,
     190,   285,    87,   177,   195,   287,    87,   178,   196,   289,
      87,   179,   205,   291,    87,   178,   214,   293,    87,   179,
     230,   295,    81,    87,   107,   246,   297,    87,   179,   247,
     299,   301,    87,   178,   252,   303,    87,   178,   253,   305,
      87,   179,   255,   307,    87,   178,   257,   309,    87,   179,
     261,   311,    87,   178,   265,   313,    87,   179,   270,   315,
     180,   181,   184,   188,   189,   190,   195,   196,   205,   214,
     230,   246,   247,   251,   252,   253,   255,   257,   261,   265,
     270,    87,   177,   317,   343,    87,   179,   321,   345,    87,
     179,   323,   347,    87,   179,   326,   349,    87,   179,   330,
     351,   317,   321,   323,   326,   330,   177,   334,   177,   341,
      87,   341,   353,     9,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,   176,   176,   173,
     153,   156,   165,   162,   160,   276,   278,   182,   280,   185,
     282,   284,   286,   191,   288,   290,   197,   292,   206,   294,
     215,   296,   231,   298,   300,   248,   304,   306,   254,   308,
     256,   310,   258,   312,   262,   314,   266,   316,   271,   344,
     318,   346,   322,   348,   324,   350,   327,   352,   331,   335,
     342,   354,   172,     9,   157,   157,   166,   175,   176,   166,
     166,    88,   180,    88,   181,   179,    88,   184,   179,    88,
     188,    88,   189,    88,   190,   177,    88,   195,    88,   196,
     178,    88,   205,   179,    88,   214,   178,    88,   230,   179,
      88,   246,    88,   247,   179,    88,   252,    88,   253,   178,
      88,   255,   179,    88,   257,   178,    88,   261,   179,    88,
     265,   178,    88,   270,   179,    88,   317,   177,    88,   321,
     179,    88,   323,   179,    88,   326,   179,    88,   330,   179,
     179,   177,    88,   341,   172,     9,   183,   186,   192,   198,
     207,   216,   232,   249,   259,   263,   267,   272,   319,   325,
     328,   332,   336,   172,   179,   179,   177,   178,   179,   178,
     179,   179,   178,   179,   178,   179,   177,   179,   179,   179,
     179,   187,   193,   199,   208,   217,   233,   250,   260,   264,
     268,   273,   320,   329,   333,   337,   179,   194,   178,   179,
     178,   179,   179,   178,   179,   177,   179,   179,   179,    83,
     177,   200,   209,   218,   234,   269,   274,   338,   178,   179,
     178,   179,   179,   201,   210,   219,   235,   339,   178,   179,
     178,   179,   179,   202,   211,   220,   236,   340,   178,   179,
     178,   179,   179,   203,   212,   221,   237,   178,   179,   178,
     179,   204,   213,   222,   238,   178,   179,   178,   179,   223,
     239,   178,   179,   224,   240,   178,   179,   225,   241,   178,
     179,   226,   242,   178,   179,   227,   243,   178,   179,   228,
     244,   178,   179,   229,   245,   178,   179
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
#line 217 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)) == false) { YYABORT; } ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 218 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->checkHeader() == true) { YYABORT; } ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 221 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 235 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 252 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 254 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 286 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(1) - (1)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 289 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString1.c_str(), 
                                            0,
                                            SKEL->_tmpBitVector1     ); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 294 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 297 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(4) - (4)].stringVal); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 298 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString2.c_str(), 
                                            SKEL->_tmpString1.c_str(),
                                            SKEL->_tmpBitVector1     ); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 303 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 314 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::Cluster; ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 315 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::MT;      ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 326 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 327 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 328 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 336 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 337 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 339 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 340 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 342 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 343 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 344 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 346 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 347 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 348 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 351 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 352 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 353 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 361 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 362 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 364 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 365 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 367 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 368 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 370 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 371 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 375 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 377 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 379 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 382 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 386 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 388 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 390 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 399 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 401 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 410 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 411 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 417 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 433 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 434 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 435 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 439 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 440 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 441 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 445 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 449 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 450 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 451 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 453 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 454 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
#line 464 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 468 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 469 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 470 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 474 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 478 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
#line 485 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 493 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 625 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 626 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 629 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 630 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); ;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 633 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 634 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 638 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    ;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 641 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 644 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 645 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 647 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 653 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 654 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 655 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 657 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 664 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 670 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    ;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 675 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 676 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 678 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 683 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 689 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 696 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 701 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 702 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 703 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 704 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 705 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 706 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 707 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 708 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 710 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
#line 719 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 720 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 721 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 722 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 723 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 724 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 725 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 726 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 728 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
#line 737 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 738 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 739 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 740 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 741 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 742 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 743 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 744 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 745 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 746 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 747 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 748 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 749 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 750 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 751 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 753 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
#line 763 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 764 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 765 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 766 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 767 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 768 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 769 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 770 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 771 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 772 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 773 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 774 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 775 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 776 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 777 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 779 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
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
#line 790 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 793 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 794 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 795 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 797 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    ;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 804 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 808 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 812 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    ;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 816 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    ;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 822 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 827 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 829 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    ;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 835 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 837 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 843 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 844 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 845 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 846 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    ;}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 852 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 853 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 854 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 855 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    ;}
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 861 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 862 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 863 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 864 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 865 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    ;}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 871 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 872 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 873 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 874 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 875 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    ;}
    break;

  case 422:

/* Line 1464 of yacc.c  */
#line 1051 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 423:

/* Line 1464 of yacc.c  */
#line 1052 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 424:

/* Line 1464 of yacc.c  */
#line 1053 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 425:

/* Line 1464 of yacc.c  */
#line 1055 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    ;}
    break;

  case 426:

/* Line 1464 of yacc.c  */
#line 1062 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 427:

/* Line 1464 of yacc.c  */
#line 1064 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 428:

/* Line 1464 of yacc.c  */
#line 1070 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 429:

/* Line 1464 of yacc.c  */
#line 1071 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 430:

/* Line 1464 of yacc.c  */
#line 1073 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 431:

/* Line 1464 of yacc.c  */
#line 1079 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 432:

/* Line 1464 of yacc.c  */
#line 1080 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 433:

/* Line 1464 of yacc.c  */
#line 1081 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 434:

/* Line 1464 of yacc.c  */
#line 1083 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 435:

/* Line 1464 of yacc.c  */
#line 1089 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 436:

/* Line 1464 of yacc.c  */
#line 1090 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 437:

/* Line 1464 of yacc.c  */
#line 1091 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 438:

/* Line 1464 of yacc.c  */
#line 1093 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 439:

/* Line 1464 of yacc.c  */
#line 1099 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue();  ;}
    break;

  case 440:

/* Line 1464 of yacc.c  */
#line 1100 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 441:

/* Line 1464 of yacc.c  */
#line 1101 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 442:

/* Line 1464 of yacc.c  */
#line 1102 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 443:

/* Line 1464 of yacc.c  */
#line 1103 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 444:

/* Line 1464 of yacc.c  */
#line 1104 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 445:

/* Line 1464 of yacc.c  */
#line 1106 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[(3) - (13)].floatVal), (yyvsp[(5) - (13)].floatVal), (yyvsp[(7) - (13)].floatVal), (yyvsp[(9) - (13)].floatVal), (yyvsp[(11) - (13)].floatVal), (yyvsp[(13) - (13)].floatVal));
        
        bv.setState((yyvsp[(1) - (13)].intVal));

        SKEL->addVolumeValue(bv);
    ;}
    break;

  case 446:

/* Line 1464 of yacc.c  */
#line 1116 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 447:

/* Line 1464 of yacc.c  */
#line 1118 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[(1) - (3)].intVal), (yyvsp[(3) - (3)].intVal)));
    ;}
    break;



/* Line 1464 of yacc.c  */
#line 3871 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
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
#line 1171 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

