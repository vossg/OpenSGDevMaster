
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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
#line 81 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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
#line 213 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
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

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

#define SKEL (static_cast<ScanParseSkel *>(pSkel))

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif



/* Line 264 of yacc.c  */
#line 261 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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
# if YYENABLE_NLS
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
#define YYLAST   896

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  261
/* YYNRULES -- Number of rules.  */
#define YYNRULES  467
/* YYNRULES -- Number of states.  */
#define YYNSTATES  761

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
     263,   264,   271,   272,   273,   280,   282,   286,   287,   291,
     293,   295,   297,   299,   301,   305,   307,   309,   311,   313,
     315,   317,   319,   321,   323,   325,   327,   329,   331,   333,
     335,   337,   339,   341,   343,   345,   347,   349,   351,   353,
     355,   357,   359,   361,   363,   365,   367,   369,   371,   373,
     375,   377,   379,   381,   383,   385,   387,   389,   391,   393,
     395,   397,   399,   401,   403,   405,   407,   409,   411,   413,
     415,   417,   419,   421,   424,   427,   430,   433,   436,   439,
     442,   445,   448,   451,   454,   457,   460,   463,   466,   469,
     472,   475,   478,   481,   484,   487,   490,   493,   496,   499,
     502,   505,   508,   511,   514,   517,   520,   523,   526,   529,
     532,   535,   538,   541,   544,   547,   550,   553,   556,   559,
     562,   565,   568,   571,   574,   577,   580,   583,   586,   588,
     590,   592,   594,   596,   598,   600,   602,   603,   604,   610,
     611,   612,   613,   621,   623,   625,   626,   627,   628,   637,
     640,   641,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   742,   743,   744,   745,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   755,
     756,   757,   789,   791,   793,   794,   795,   796,   804,   806,
     808,   810,   812,   813,   817,   818,   822,   823,   824,   825,
     832,   833,   834,   835,   842,   843,   844,   845,   846,   855,
     856,   857,   858,   859,   868,   870,   874,   877,   878,   880,
     884,   887,   888,   890,   894,   897,   898,   900,   904,   907,
     908,   910,   914,   917,   918,   920,   924,   927,   928,   930,
     934,   937,   938,   940,   944,   947,   948,   950,   954,   957,
     958,   960,   964,   967,   968,   970,   974,   977,   978,   980,
     984,   987,   988,   990,   994,   997,   998,  1000,  1004,  1007,
    1008,  1010,  1014,  1017,  1018,  1020,  1024,  1027,  1028,  1030,
    1034,  1037,  1038,  1040,  1044,  1047,  1048,  1050,  1054,  1057,
    1058,  1060,  1064,  1067,  1068,  1070,  1074,  1077,  1078,  1079,
    1080,  1081,  1089,  1090,  1094,  1095,  1096,  1102,  1103,  1104,
    1105,  1113,  1114,  1115,  1116,  1124,  1125,  1126,  1127,  1128,
    1129,  1130,  1144,  1145,  1149,  1151,  1155,  1158,  1159,  1161,
    1165,  1168,  1169,  1171,  1175,  1178,  1179,  1181,  1185,  1188,
    1189,  1191,  1195,  1198,  1199,  1201,  1205,  1208
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    94,    95,    97,   100,   105,    -1,     3,
      -1,    -1,     4,    96,    -1,    -1,    82,    -1,    97,    98,
      -1,    -1,     5,    99,    -1,    82,    -1,    79,    -1,   100,
     101,    -1,    -1,    -1,     6,   103,   102,   104,    -1,    79,
      -1,    79,    -1,   105,   106,    -1,    -1,   107,    -1,   116,
      -1,   137,    -1,   141,    -1,   144,    -1,    -1,    -1,   169,
     108,   113,   109,   148,    -1,    -1,    -1,    -1,    10,   168,
     110,   169,   111,   113,   112,   148,    -1,    11,   168,    -1,
      87,   114,    88,    -1,    -1,   114,   115,    -1,    -1,    85,
      -1,    86,    -1,   117,    -1,   128,    -1,    -1,    -1,     7,
     169,   118,    87,   120,    88,   119,    89,   105,    90,    -1,
     120,   121,    -1,    -1,    -1,    17,   173,   122,   171,    -1,
      -1,    18,   173,   123,   172,    -1,    -1,    -1,    20,   173,
     124,   170,   125,   174,    -1,    -1,    -1,    19,   173,   126,
     170,   127,   174,    -1,    -1,    -1,     8,   169,   129,    87,
     131,    88,   130,   147,    -1,   131,   132,    -1,    -1,    -1,
      17,   173,   133,   171,    -1,    -1,    18,   173,   134,   172,
      -1,    -1,    20,   173,   135,   170,    -1,    -1,    19,   173,
     136,   170,    -1,    -1,    -1,    -1,    12,   168,   138,    91,
     172,   139,    13,   168,   140,    91,   171,    -1,    -1,    -1,
      14,   168,   142,    91,   168,   143,   146,    -1,    -1,    15,
     168,   145,   146,    -1,    16,   168,    -1,    -1,   299,    -1,
      89,   149,    90,    -1,   149,   150,    -1,    -1,   165,    -1,
     151,    -1,   154,    -1,   158,    -1,   161,    -1,     1,    -1,
      -1,    -1,    17,   173,   152,   171,   153,   157,    -1,    -1,
      -1,    18,   173,   155,   172,   156,   157,    -1,    -1,     9,
     170,    -1,    -1,    -1,    20,   173,   159,   170,   160,   164,
      -1,    -1,    -1,    19,   173,   162,   170,   163,   164,    -1,
     174,    -1,   173,     9,   170,    -1,    -1,   170,   166,   167,
      -1,   137,    -1,   116,    -1,   141,    -1,   144,    -1,   174,
      -1,   173,     9,   170,    -1,    82,    -1,    82,    -1,    82,
      -1,    82,    -1,    82,    -1,    21,    -1,    22,    -1,    23,
      -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,
      -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,
      -1,    21,   273,    -1,    22,   275,    -1,    23,   277,    -1,
      24,   279,    -1,    25,   281,    -1,    26,   283,    -1,    27,
     285,    -1,    28,   287,    -1,    29,   289,    -1,    30,   291,
      -1,    31,   293,    -1,    32,   295,    -1,    33,   297,    -1,
      34,   299,    -1,    35,   301,    -1,    36,   303,    -1,    37,
     305,    -1,    38,   307,    -1,    39,   309,    -1,    40,   311,
      -1,    41,   313,    -1,    42,   178,    -1,    43,   179,    -1,
      44,   182,    -1,    45,   186,    -1,    46,   187,    -1,    47,
     188,    -1,    48,   193,    -1,    49,   194,    -1,    50,   203,
      -1,    51,   212,    -1,    52,   228,    -1,    53,   244,    -1,
      54,   245,    -1,    55,   249,    -1,    56,   250,    -1,    57,
     251,    -1,    58,   253,    -1,    59,   255,    -1,    60,   259,
      -1,    61,   263,    -1,    62,   268,    -1,    63,   341,    -1,
      64,   343,    -1,    65,   345,    -1,    66,   347,    -1,    67,
     349,    -1,    68,   315,    -1,    69,   319,    -1,    70,   321,
      -1,    71,   324,    -1,    72,   328,    -1,    73,   332,    -1,
      74,   339,    -1,    75,   351,    -1,    76,    -1,    77,    -1,
      77,    -1,    78,    -1,    77,    -1,    78,    -1,    80,    -1,
      82,    -1,    -1,    -1,   177,   180,   177,   181,   177,    -1,
      -1,    -1,    -1,   177,   183,   177,   184,   177,   185,   177,
      -1,   176,    -1,   177,    -1,    -1,    -1,    -1,   175,   189,
     175,   190,   175,   191,   192,    83,    -1,   192,   175,    -1,
      -1,   175,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   176,   195,   176,   196,   176,   197,   176,   198,   176,
     199,   176,   200,   176,   201,   176,   202,   176,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   204,   177,
     205,   177,   206,   177,   207,   177,   208,   177,   209,   177,
     210,   177,   211,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     176,   213,   176,   214,   176,   215,   176,   216,   176,   217,
     176,   218,   176,   219,   176,   220,   176,   221,   176,   222,
     176,   223,   176,   224,   176,   225,   176,   226,   176,   227,
     176,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   229,   177,
     230,   177,   231,   177,   232,   177,   233,   177,   234,   177,
     235,   177,   236,   177,   237,   177,   238,   177,   239,   177,
     240,   177,   241,   177,   242,   177,   243,   177,    -1,   107,
      -1,    81,    -1,    -1,    -1,    -1,   177,   246,   177,   247,
     177,   248,   177,    -1,    79,    -1,    82,    -1,    76,    -1,
     176,    -1,    -1,   176,   252,   176,    -1,    -1,   177,   254,
     177,    -1,    -1,    -1,    -1,   176,   256,   176,   257,   176,
     258,    -1,    -1,    -1,    -1,   177,   260,   177,   261,   177,
     262,    -1,    -1,    -1,    -1,    -1,   176,   264,   176,   265,
     176,   266,   176,   267,    -1,    -1,    -1,    -1,    -1,   177,
     269,   177,   270,   177,   271,   177,   272,    -1,   178,    -1,
      87,   274,    88,    -1,   274,   178,    -1,    -1,   179,    -1,
      87,   276,    88,    -1,   276,   179,    -1,    -1,   182,    -1,
      87,   278,    88,    -1,   278,   182,    -1,    -1,   186,    -1,
      87,   280,    88,    -1,   280,   186,    -1,    -1,   187,    -1,
      87,   282,    88,    -1,   282,   187,    -1,    -1,   188,    -1,
      87,   284,    88,    -1,   284,   188,    -1,    -1,   193,    -1,
      87,   286,    88,    -1,   286,   193,    -1,    -1,   194,    -1,
      87,   288,    88,    -1,   288,   194,    -1,    -1,   203,    -1,
      87,   290,    88,    -1,   290,   203,    -1,    -1,   212,    -1,
      87,   292,    88,    -1,   292,   212,    -1,    -1,   228,    -1,
      87,   294,    88,    -1,   294,   228,    -1,    -1,   244,    -1,
      87,   296,    88,    -1,   296,   244,    -1,    -1,   245,    -1,
      87,   298,    88,    -1,   298,   245,    -1,    -1,   249,    -1,
      87,   300,    88,    -1,   300,   249,    -1,    -1,   250,    -1,
      87,   302,    88,    -1,   302,   250,    -1,    -1,   251,    -1,
      87,   304,    88,    -1,   304,   251,    -1,    -1,   253,    -1,
      87,   306,    88,    -1,   306,   253,    -1,    -1,   255,    -1,
      87,   308,    88,    -1,   308,   255,    -1,    -1,   259,    -1,
      87,   310,    88,    -1,   310,   259,    -1,    -1,   263,    -1,
      87,   312,    88,    -1,   312,   263,    -1,    -1,   268,    -1,
      87,   314,    88,    -1,   314,   268,    -1,    -1,    -1,    -1,
      -1,   175,   316,   175,   317,   175,   318,   175,    -1,    -1,
     177,   320,   177,    -1,    -1,    -1,   177,   322,   177,   323,
     177,    -1,    -1,    -1,    -1,   177,   325,   177,   326,   177,
     327,   177,    -1,    -1,    -1,    -1,   177,   329,   177,   330,
     177,   331,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175,   333,   177,   334,   177,   335,   177,   336,   177,   337,
     177,   338,   177,    -1,    -1,   175,   340,   175,    -1,   315,
      -1,    87,   342,    88,    -1,   342,   315,    -1,    -1,   319,
      -1,    87,   344,    88,    -1,   344,   319,    -1,    -1,   321,
      -1,    87,   346,    88,    -1,   346,   321,    -1,    -1,   324,
      -1,    87,   348,    88,    -1,   348,   324,    -1,    -1,   328,
      -1,    87,   350,    88,    -1,   350,   328,    -1,    -1,   339,
      -1,    87,   352,    88,    -1,   352,   339,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   206,   206,   213,   214,   217,   218,   221,   224,   225,
     229,   234,   235,   242,   243,   248,   246,   253,   256,   259,
     260,   263,   264,   265,   266,   267,   282,   285,   282,   290,
     293,   294,   289,   298,   302,   303,   306,   307,   310,   311,
     314,   315,   322,   323,   322,   327,   328,   332,   331,   335,
     334,   338,   339,   337,   342,   343,   341,   347,   348,   347,
     352,   353,   357,   356,   360,   359,   363,   362,   366,   365,
     371,   373,   375,   370,   382,   384,   381,   395,   394,   405,
     407,   410,   413,   416,   417,   420,   421,   422,   423,   424,
     425,   429,   430,   428,   435,   436,   434,   439,   441,   445,
     446,   444,   451,   452,   450,   456,   457,   461,   460,   469,
     470,   471,   472,   475,   476,   479,   482,   485,   488,   491,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   593,   594,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   605,   608,   609,
     612,   613,   616,   617,   620,   624,   627,   628,   627,   636,
     637,   638,   636,   646,   652,   658,   659,   661,   658,   671,
     675,   678,   684,   685,   686,   687,   688,   689,   690,   691,
     684,   702,   703,   704,   705,   706,   707,   708,   709,   702,
     720,   721,   722,   723,   724,   725,   726,   727,   728,   729,
     730,   731,   732,   733,   734,   720,   746,   747,   748,   749,
     750,   751,   752,   753,   754,   755,   756,   757,   758,   759,
     760,   746,   772,   773,   776,   777,   778,   776,   786,   790,
     794,   800,   806,   806,   814,   814,   822,   823,   824,   822,
     831,   832,   833,   831,   840,   841,   842,   843,   840,   850,
     851,   852,   853,   850,   860,   861,   864,   865,   868,   869,
     872,   873,   876,   877,   880,   881,   884,   885,   888,   889,
     892,   893,   896,   897,   900,   901,   904,   905,   908,   909,
     912,   913,   916,   917,   920,   921,   924,   925,   928,   929,
     932,   933,   936,   937,   940,   941,   944,   945,   948,   949,
     952,   953,   956,   957,   960,   961,   964,   965,   968,   969,
     972,   973,   976,   977,   980,   981,   984,   985,   988,   989,
     992,   993,   996,   997,  1000,  1001,  1004,  1005,  1008,  1009,
    1012,  1013,  1016,  1017,  1020,  1021,  1024,  1025,  1030,  1031,
    1032,  1030,  1041,  1041,  1049,  1050,  1049,  1058,  1059,  1060,
    1058,  1068,  1069,  1070,  1068,  1078,  1079,  1080,  1081,  1082,
    1083,  1078,  1095,  1095,  1103,  1104,  1107,  1108,  1111,  1112,
    1115,  1116,  1119,  1120,  1123,  1124,  1127,  1128,  1131,  1132,
    1135,  1136,  1139,  1140,  1143,  1144,  1147,  1148
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
  "fieldDeclaration", "$@31", "$@32", "exposedFieldDeclaration", "$@33",
  "$@34", "fieldDeclarationEnd", "nodeBodyElement", "$@35", "fieldEnd",
  "nodeNameId", "nodeTypeId", "fieldId", "eventInId", "eventOutId",
  "fieldType", "fieldValue", "int32", "double", "float", "sfboolValue",
  "sfcolorValue", "$@36", "$@37", "sfcolorRGBAValue", "$@38", "$@39",
  "$@40", "sfdoubleValue", "sffloatValue", "sfimageValue", "$@41", "$@42",
  "$@43", "pixels", "sfint32Value", "sfmatrix3dValue", "$@44", "$@45",
  "$@46", "$@47", "$@48", "$@49", "$@50", "$@51", "sfmatrix3fValue",
  "$@52", "$@53", "$@54", "$@55", "$@56", "$@57", "$@58", "$@59",
  "sfmatrix4dValue", "$@60", "$@61", "$@62", "$@63", "$@64", "$@65",
  "$@66", "$@67", "$@68", "$@69", "$@70", "$@71", "$@72", "$@73", "$@74",
  "sfmatrix4fValue", "$@75", "$@76", "$@77", "$@78", "$@79", "$@80",
  "$@81", "$@82", "$@83", "$@84", "$@85", "$@86", "$@87", "$@88", "$@89",
  "sfnodeValue", "sfrotationValue", "$@90", "$@91", "$@92",
  "sfstringValue", "sftimeValue", "sfvec2dValue", "$@93", "sfvec2fValue",
  "$@94", "sfvec3dValue", "$@95", "$@96", "$@97", "sfvec3fValue", "$@98",
  "$@99", "$@100", "sfvec4dValue", "$@101", "$@102", "$@103", "$@104",
  "sfvec4fValue", "$@105", "$@106", "$@107", "$@108", "mfboolValue",
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
  "$@109", "$@110", "$@111", "sfpnt2fValue", "$@112", "sfpnt3fValue",
  "$@113", "$@114", "sfpnt4fValue", "$@115", "$@116", "$@117",
  "sfplaneValue", "$@118", "$@119", "$@120", "sfVolumeValue", "$@121",
  "$@122", "$@123", "$@124", "$@125", "$@126", "sfvec2iValue", "$@127",
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
     160,   158,   162,   163,   161,   164,   164,   166,   165,   165,
     165,   165,   165,   167,   167,   168,   169,   170,   171,   172,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   175,   175,
     176,   176,   177,   177,   178,   178,   180,   181,   179,   183,
     184,   185,   182,   186,   187,   189,   190,   191,   188,   192,
     192,   193,   195,   196,   197,   198,   199,   200,   201,   202,
     194,   204,   205,   206,   207,   208,   209,   210,   211,   203,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   212,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   228,   244,   244,   246,   247,   248,   245,   249,   249,
     249,   250,   252,   251,   254,   253,   256,   257,   258,   255,
     260,   261,   262,   259,   264,   265,   266,   267,   263,   269,
     270,   271,   272,   268,   273,   273,   274,   274,   275,   275,
     276,   276,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   290,   290,
     291,   291,   292,   292,   293,   293,   294,   294,   295,   295,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   304,   305,   305,
     306,   306,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   314,   316,   317,
     318,   315,   320,   319,   322,   323,   321,   325,   326,   327,
     324,   329,   330,   331,   328,   333,   334,   335,   336,   337,
     338,   332,   340,   339,   341,   341,   342,   342,   343,   343,
     344,   344,   345,   345,   346,   346,   347,   347,   348,   348,
     349,   349,   350,   350,   351,   351,   352,   352
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
       0,     6,     0,     0,     6,     1,     3,     0,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     0,     5,     0,
       0,     0,     7,     1,     1,     0,     0,     0,     8,     2,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     1,     1,     0,     0,     0,     7,     1,     1,
       1,     1,     0,     3,     0,     3,     0,     0,     0,     6,
       0,     0,     0,     6,     0,     0,     0,     0,     8,     0,
       0,     0,     0,     8,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     0,     0,
       0,     7,     0,     3,     0,     0,     5,     0,     0,     0,
       7,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,    13,     0,     3,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   116,    19,
      21,    22,    40,    41,    23,    24,    25,    26,     0,    42,
      57,   115,    29,    33,    70,    74,    77,    35,    18,    16,
       0,     0,     0,     0,     0,    80,    37,    27,    46,    61,
      30,     0,     0,     0,    78,     0,     0,     0,     0,    35,
     119,    71,    75,    79,    38,    39,    34,    36,    84,    28,
       0,     0,     0,     0,    43,    45,     0,     0,     0,     0,
      58,    60,    31,     0,    80,     0,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,    47,
      49,    54,    51,     0,    62,    64,    68,    66,     0,     0,
       0,    76,    90,     0,     0,     0,     0,   117,    82,   110,
     109,   111,   112,    83,    86,    87,    88,    89,    85,   107,
       0,     0,     0,     0,    20,     0,     0,     0,     0,   310,
     308,   309,   389,    59,   386,    81,    32,    72,    91,    94,
     102,    99,     0,   118,    48,    50,    55,    52,     0,    63,
      65,    69,    67,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,   108,     0,   113,     0,     0,    44,
     387,   388,     0,    92,    95,   103,   100,   234,   235,   337,
     334,   173,   232,   233,   341,   236,   338,   174,   345,   239,
     342,   175,   230,   231,   349,   243,   346,   176,   353,   244,
     350,   177,   228,   229,   357,   245,   354,   178,   361,   251,
     358,   179,   365,   252,   362,   180,   369,   261,   366,   181,
     373,   270,   370,   182,   377,   286,   374,   183,   303,   381,
     302,   378,   184,   385,   304,   382,   185,   186,   393,   311,
     390,   187,   397,   312,   394,   188,   401,   314,   398,   189,
     405,   316,   402,   190,   409,   320,   406,   191,   413,   324,
     410,   192,   417,   329,   414,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   447,   418,   444,
     215,   451,   422,   448,   216,   455,   424,   452,   217,   459,
     427,   456,   218,   463,   431,   460,   219,   220,   221,   222,
     223,   224,   435,   225,   442,   226,   467,   464,   227,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    56,    53,    73,    97,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114,     0,    93,
      96,   104,     0,   105,   101,   335,   336,   339,   340,   237,
     343,   344,   240,   347,   348,   351,   352,   355,   356,   246,
     359,   360,   363,   364,   253,   367,   368,   262,   371,   372,
     271,   375,   376,   287,   379,   380,   383,   384,   305,   391,
     392,   395,   396,   313,   399,   400,   315,   403,   404,   317,
     407,   408,   321,   411,   412,   325,   415,   416,   330,   445,
     446,   419,   449,   450,   423,   453,   454,   425,   457,   458,
     428,   461,   462,   432,   436,   443,   465,   466,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,   238,   241,
     247,   254,   263,   272,   288,   306,   318,   322,   326,   331,
     420,   426,   429,   433,   437,     0,   250,     0,     0,     0,
       0,     0,   319,   323,     0,     0,     0,     0,     0,     0,
     242,     0,   255,   264,   273,   289,   307,   327,   332,   421,
     430,   434,   438,   248,   249,     0,     0,     0,     0,   328,
     333,     0,   256,   265,   274,   290,   439,     0,     0,     0,
       0,     0,   257,   266,   275,   291,   440,     0,     0,     0,
       0,     0,   258,   267,   276,   292,   441,     0,     0,     0,
       0,   259,   268,   277,   293,     0,     0,     0,     0,   260,
     269,   278,   294,     0,     0,   279,   295,     0,     0,   280,
     296,     0,     0,   281,   297,     0,     0,   282,   298,     0,
       0,   283,   299,     0,     0,   284,   300,     0,     0,   285,
     301
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   340,    47,    66,    52,    69,
     159,    57,    65,    77,    31,    32,    50,   153,    67,    85,
     180,   181,   183,   278,   182,   277,    33,    51,   158,    68,
      91,   185,   186,   188,   187,    34,    53,    93,   214,    35,
      54,    94,    36,    55,    64,   193,    79,    95,   173,   174,
     215,   486,   175,   216,   487,   539,   176,   218,   489,   177,
     217,   488,   541,   178,   202,   274,    42,    37,   179,   204,
      71,   542,   543,   315,   305,   295,   290,   296,   492,   620,
     300,   494,   621,   655,   306,   310,   316,   498,   622,   656,
     671,   320,   324,   501,   623,   657,   685,   697,   707,   717,
     725,   328,   503,   624,   658,   686,   698,   708,   718,   726,
     332,   505,   625,   659,   687,   699,   709,   719,   727,   733,
     737,   741,   745,   749,   753,   757,   336,   507,   626,   660,
     688,   700,   710,   720,   728,   734,   738,   742,   746,   750,
     754,   758,   341,   345,   510,   627,   661,   194,   350,   354,
     513,   358,   515,   362,   517,   628,   662,   366,   519,   629,
     663,   370,   521,   630,   664,   689,   374,   523,   631,   665,
     690,   291,   490,   297,   491,   301,   493,   307,   495,   311,
     496,   317,   497,   321,   499,   325,   500,   329,   502,   333,
     504,   337,   506,   342,   508,   346,   509,   347,   213,   351,
     511,   355,   512,   359,   514,   363,   516,   367,   518,   371,
     520,   375,   522,   399,   525,   632,   666,   403,   527,   407,
     529,   633,   411,   531,   634,   667,   415,   533,   635,   668,
     423,   534,   636,   669,   691,   701,   711,   425,   535,   400,
     524,   404,   526,   408,   528,   412,   530,   416,   532,   428,
     536
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -273
static const yytype_int16 yypact[] =
{
      30,  -273,    13,    36,  -273,   -29,  -273,  -273,  -273,    61,
      10,  -273,    54,  -273,  -273,  -273,     2,  -273,   169,  -273,
    -273,    34,    34,    39,    39,    39,    39,    39,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,    67,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,    64,  -273,  -273,
      69,    73,    34,    72,    99,   126,  -273,  -273,  -273,  -273,
    -273,   122,    39,    39,  -273,   121,   119,    79,   105,    64,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
     823,   823,   823,   823,  -273,  -273,   823,   823,   823,   823,
    -273,  -273,  -273,   199,   126,   353,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,   137,  -273,  -273,  -273,  -273,    26,   119,
      39,  -273,  -273,   823,   823,   823,   823,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
     149,   122,   153,   153,  -273,   149,   122,   153,   153,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,   633,  -273,  -273,  -273,  -273,  -273,   154,  -273,
    -273,  -273,  -273,    55,   226,   149,   122,   153,   153,   116,
       6,   123,   279,   416,   110,   112,   445,   457,   464,   469,
      63,   471,    26,   477,   482,   484,   495,   498,   506,   509,
      47,   302,   302,   318,   302,   419,   419,   318,   302,   318,
     302,    76,   302,    96,   318,   318,   302,   318,   302,   318,
     302,   118,   514,   525,   532,   546,   419,   302,   302,   302,
     302,   419,   419,   247,  -273,   320,  -273,   768,   768,  -273,
    -273,  -273,   149,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,   153,
     116,     6,   123,   279,   416,   110,   112,   445,   457,   464,
     469,    63,   471,    26,   477,   482,   484,   495,   498,   506,
     509,    47,   302,   302,   318,   302,   419,   419,   318,   302,
     318,   302,    76,   302,    96,   318,   318,   302,   318,   302,
     318,   302,   118,   514,   525,   532,   546,   419,   302,   302,
     302,   302,   419,  -273,  -273,  -273,   322,   322,   633,   633,
      38,   255,   302,   267,   302,   281,   299,    24,   419,    71,
     339,   318,   341,   302,   343,   318,   345,   302,    51,   348,
     302,   364,   372,   318,   376,   302,   380,   318,   384,   302,
     396,   318,   398,   302,    94,   419,   404,   302,   424,   302,
     438,   302,   442,   302,   302,   419,    97,  -273,   153,  -273,
    -273,  -273,   326,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,   153,
     302,   302,   419,   318,   302,   318,   302,   302,   318,   302,
     318,   302,   419,   302,   302,   302,   302,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,   302,  -273,   318,   302,   318,
     302,   302,  -273,  -273,   318,   302,   419,   302,   302,   302,
    -273,   147,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,   318,   302,   318,   302,  -273,
    -273,   302,  -273,  -273,  -273,  -273,  -273,   318,   302,   318,
     302,   302,  -273,  -273,  -273,  -273,  -273,   318,   302,   318,
     302,   302,  -273,  -273,  -273,  -273,  -273,   318,   302,   318,
     302,  -273,  -273,  -273,  -273,   318,   302,   318,   302,  -273,
    -273,  -273,  -273,   318,   302,  -273,  -273,   318,   302,  -273,
    -273,   318,   302,  -273,  -273,   318,   302,  -273,  -273,   318,
     302,  -273,  -273,   318,   302,  -273,  -273,   318,   302,  -273,
    -273
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,   143,  -273,    -6,  -273,  -273,  -273,  -273,
    -273,   268,  -273,  -273,   245,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,   253,  -273,  -273,  -273,   257,
    -273,  -273,   269,  -273,   256,  -273,   203,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -113,  -273,  -273,  -273,  -273,
    -273,  -273,  -105,  -273,  -273,  -273,    32,    58,  -163,  -133,
     -75,   -11,  -187,   117,  -119,  -221,  -152,  -138,  -273,  -273,
    -157,  -273,  -273,  -273,  -211,  -193,  -178,  -273,  -273,  -273,
    -273,  -183,  -179,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -198,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -204,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -214,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -225,  -218,  -273,  -273,  -273,  -149,  -216,  -190,
    -273,  -245,  -273,  -253,  -273,  -273,  -273,  -241,  -273,  -273,
    -273,  -252,  -273,  -273,  -273,  -273,  -257,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,   233,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -244,  -273,  -273,  -273,  -239,  -273,  -238,
    -273,  -273,  -260,  -273,  -273,  -273,  -265,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -272,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     299,   427,   309,   396,   393,   421,   327,   395,   335,   420,
     344,   392,    30,     4,   357,   276,   365,   394,   373,   206,
     207,   299,   417,   309,   211,   212,   387,   327,   418,   335,
     419,   344,   379,     1,   388,   357,   386,   365,   390,   373,
       5,   402,   406,   410,   414,   385,   402,   406,   410,   414,
     384,   380,   209,     7,   285,   286,    43,    44,    45,    46,
      16,    23,    24,   382,   281,   391,    10,   381,   383,   149,
     150,   151,   152,    23,    24,   154,   155,   156,   157,    39,
      40,    19,   283,   292,   293,   378,    23,    24,   376,    13,
     483,   484,    14,   294,    72,    73,    80,    81,    82,    83,
     312,   313,   189,   377,   389,   190,   205,   323,   191,   331,
      60,   210,   557,   192,   349,   353,    28,   361,   287,   369,
     288,    41,    86,    87,    88,    89,   545,   287,   323,   288,
     331,   189,   338,    28,   190,   349,   353,   191,   361,   574,
     369,   284,    63,   280,   338,    28,    48,   312,   313,   485,
     339,    56,   198,   199,   200,   201,    58,   338,    28,   560,
      59,    21,    22,    61,    23,    24,    25,    84,    26,    27,
     312,   313,   189,   312,   313,   190,    21,    22,   191,    23,
      24,    25,   599,    26,    27,   616,   312,   313,   312,   313,
      62,   275,   197,    90,   312,   313,   287,   314,   288,   318,
     292,   293,    30,   289,    70,   397,    74,    75,    78,    76,
     298,   299,   160,   309,   396,   393,   421,   327,   395,   335,
     420,   344,   392,   312,   313,   357,   184,   365,   394,   373,
     683,   203,   299,   417,   309,   167,    28,   387,   327,   418,
     335,   419,   344,   379,   279,   388,   357,   386,   365,   390,
     373,    28,   402,   406,   410,   414,   385,   402,   406,   410,
     414,   384,   380,   588,   617,   597,   537,   612,   594,   585,
     609,   549,   299,   552,   382,   309,   391,   591,   381,   383,
     600,   327,   567,   575,   554,   335,   573,   603,   344,   578,
     606,   577,   572,   357,   586,   580,   378,   365,   592,   376,
     569,   373,   598,   556,   566,   402,   604,   406,   607,   410,
     610,   414,   613,   614,   377,   389,   561,   282,   323,   558,
     331,   563,   582,   312,   313,   349,   353,   208,   361,   429,
     369,   538,   292,   293,   426,   619,   551,    92,   546,   323,
     169,   331,   319,   547,   292,   293,   349,   353,   170,   361,
     161,   369,   171,   548,   162,   550,   302,   303,   302,   303,
      21,    22,   196,   319,   172,    25,   304,    26,    27,   553,
     163,   164,   165,   166,   540,   618,   292,   293,   398,   292,
     293,   323,   564,   398,   544,   331,   570,   555,   422,   424,
     424,   195,   349,   353,   583,   302,   303,   361,   589,   638,
     639,   369,   595,   642,     0,   644,   645,     0,   647,     0,
     649,     0,   651,   652,   653,   654,   302,   303,   292,   293,
     302,   303,   292,   293,     0,   292,   293,   562,     0,   565,
       0,   568,     0,   571,   670,   167,   576,   673,     0,   675,
     676,   302,   303,   168,   678,     0,   680,   681,   682,   302,
     303,     0,   579,   292,   293,     0,   637,   302,   303,     0,
     581,   292,   293,     0,   584,   693,     0,   695,   587,     0,
     696,     0,   590,   302,   303,   292,   293,   703,     0,   705,
     706,   292,   293,     0,   593,     0,   596,   713,     0,   715,
     716,     0,   602,   292,   293,   312,   313,   722,     0,   724,
       0,   292,   293,   308,   641,   730,   643,   732,     0,   646,
       0,   648,   605,   736,     0,   292,   293,   740,     0,   292,
     293,   744,   302,   303,     0,   748,   608,     0,     0,   752,
     611,     0,   322,   756,   292,   293,     0,   760,   672,     0,
     674,   302,   303,     0,   326,   677,   292,   293,   292,   293,
       0,   330,     0,   319,   302,   303,   334,     0,   343,   302,
     303,   292,   293,     0,   348,     0,   692,     0,   694,   352,
       0,   356,   302,   303,   319,   292,   293,     0,   702,     0,
     704,     0,   360,   302,   303,   364,   292,   293,   712,   398,
     714,   292,   293,   368,   398,     0,   372,     0,   721,   422,
     723,   401,   292,   293,     0,     0,   729,     0,   731,   292,
     293,     0,   405,     0,   735,   559,   319,     0,   739,   409,
       0,     0,   743,   292,   293,     0,   747,     0,     0,     0,
     751,     0,     0,   413,   755,     0,     0,     0,   759,     0,
       0,   398,   601,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   615,   424,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   640,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   650,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   679,     0,     0,     0,     0,   684,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   272,   273,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148
};

static const yytype_int16 yycheck[] =
{
     221,   273,   223,   260,   257,   270,   227,   259,   229,   269,
     231,   256,    18,     0,   235,   202,   237,   258,   239,   182,
     183,   242,   266,   244,   187,   188,   251,   248,   267,   250,
     268,   252,   243,     3,   252,   256,   250,   258,   254,   260,
       4,   262,   263,   264,   265,   249,   267,   268,   269,   270,
     248,   244,   185,    82,   217,   218,    24,    25,    26,    27,
       6,    10,    11,   246,   213,   255,     5,   245,   247,    80,
      81,    82,    83,    10,    11,    86,    87,    88,    89,    21,
      22,    79,   215,    77,    78,   242,    10,    11,   240,    79,
     277,   278,    82,    87,    62,    63,    17,    18,    19,    20,
      76,    77,    76,   241,   253,    79,   181,   226,    82,   228,
      52,   186,    88,    87,   233,   234,    82,   236,    80,   238,
      82,    82,    17,    18,    19,    20,    88,    80,   247,    82,
     249,    76,    81,    82,    79,   254,   255,    82,   257,    88,
     259,   216,    16,    88,    81,    82,    79,    76,    77,   282,
      87,    87,   163,   164,   165,   166,    87,    81,    82,    88,
      87,     7,     8,    91,    10,    11,    12,    88,    14,    15,
      76,    77,    76,    76,    77,    79,     7,     8,    82,    10,
      11,    12,    88,    14,    15,    88,    76,    77,    76,    77,
      91,   202,   160,    88,    76,    77,    80,    87,    82,    87,
      77,    78,   208,    87,    82,    87,    85,    86,    89,    88,
      87,   432,    13,   434,   471,   468,   481,   438,   470,   440,
     480,   442,   467,    76,    77,   446,    89,   448,   469,   450,
      83,    82,   453,   477,   455,    82,    82,   462,   459,   478,
     461,   479,   463,   454,    90,   463,   467,   461,   469,   465,
     471,    82,   473,   474,   475,   476,   460,   478,   479,   480,
     481,   459,   455,   516,   536,   522,   429,   532,   520,   514,
     530,   492,   493,   494,   457,   496,   466,   518,   456,   458,
     524,   502,   503,   508,   495,   506,   507,   526,   509,   510,
     528,   509,   506,   514,   515,   511,   453,   518,   519,   451,
     504,   522,   523,   496,   502,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   452,   464,   499,    91,   437,   497,
     439,   500,   512,    76,    77,   444,   445,   184,   447,     9,
     449,     9,    77,    78,    87,     9,   493,    69,   490,   458,
      95,   460,   225,    88,    77,    78,   465,   466,    95,   468,
      94,   470,    95,   491,     1,    88,    77,    78,    77,    78,
       7,     8,   159,   246,    95,    12,    87,    14,    15,    88,
      17,    18,    19,    20,   487,   538,    77,    78,   261,    77,
      78,   500,   501,   266,   489,   504,   505,    88,   271,   272,
     273,   158,   511,   512,   513,    77,    78,   516,   517,   620,
     621,   520,   521,   624,    -1,   626,   627,    -1,   629,    -1,
     631,    -1,   633,   634,   635,   636,    77,    78,    77,    78,
      77,    78,    77,    78,    -1,    77,    78,    88,    -1,    88,
      -1,    88,    -1,    88,   655,    82,    88,   658,    -1,   660,
     661,    77,    78,    90,   665,    -1,   667,   668,   669,    77,
      78,    -1,    88,    77,    78,    -1,   619,    77,    78,    -1,
      88,    77,    78,    -1,    88,   686,    -1,   688,    88,    -1,
     691,    -1,    88,    77,    78,    77,    78,   698,    -1,   700,
     701,    77,    78,    -1,    88,    -1,    88,   708,    -1,   710,
     711,    -1,    88,    77,    78,    76,    77,   718,    -1,   720,
      -1,    77,    78,    87,   623,   726,   625,   728,    -1,   628,
      -1,   630,    88,   734,    -1,    77,    78,   738,    -1,    77,
      78,   742,    77,    78,    -1,   746,    88,    -1,    -1,   750,
      88,    -1,    87,   754,    77,    78,    -1,   758,   657,    -1,
     659,    77,    78,    -1,    87,   664,    77,    78,    77,    78,
      -1,    87,    -1,   436,    77,    78,    87,    -1,    87,    77,
      78,    77,    78,    -1,    87,    -1,   685,    -1,   687,    87,
      -1,    87,    77,    78,   457,    77,    78,    -1,   697,    -1,
     699,    -1,    87,    77,    78,    87,    77,    78,   707,   472,
     709,    77,    78,    87,   477,    -1,    87,    -1,   717,   482,
     719,    87,    77,    78,    -1,    -1,   725,    -1,   727,    77,
      78,    -1,    87,    -1,   733,   498,   499,    -1,   737,    87,
      -1,    -1,   741,    77,    78,    -1,   745,    -1,    -1,    -1,
     749,    -1,    -1,    87,   753,    -1,    -1,    -1,   757,    -1,
      -1,   524,   525,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   535,   536,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   622,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   632,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   666,    -1,    -1,    -1,    -1,   671,    21,
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
     107,   116,   117,   128,   137,   141,   144,   169,   102,   169,
     169,    82,   168,   168,   168,   168,   168,   108,    79,   104,
     118,   129,   110,   138,   142,   145,    87,   113,    87,    87,
     169,    91,    91,    16,   146,   114,   109,   120,   131,   111,
      82,   172,   168,   168,    85,    86,    88,   115,    89,   148,
      17,    18,    19,    20,    88,   121,    17,    18,    19,    20,
      88,   132,   113,   139,   143,   149,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   173,
     173,   173,   173,   119,   173,   173,   173,   173,   130,   112,
      13,   146,     1,    17,    18,    19,    20,    82,    90,   116,
     137,   141,   144,   150,   151,   154,   158,   161,   165,   170,
     122,   123,   126,   124,    89,   133,   134,   136,   135,    76,
      79,    82,    87,   147,   249,   299,   148,   168,   173,   173,
     173,   173,   166,    82,   171,   172,   170,   170,   105,   171,
     172,   170,   170,   300,   140,   152,   155,   162,   159,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   167,   173,   174,   127,   125,    90,
      88,   249,    91,   171,   172,   170,   170,    80,    82,    87,
     178,   273,    77,    78,    87,   177,   179,   275,    87,   177,
     182,   277,    77,    78,    87,   176,   186,   279,    87,   177,
     187,   281,    76,    77,    87,   175,   188,   283,    87,   175,
     193,   285,    87,   176,   194,   287,    87,   177,   203,   289,
      87,   176,   212,   291,    87,   177,   228,   293,    81,    87,
     107,   244,   295,    87,   177,   245,   297,   299,    87,   176,
     250,   301,    87,   176,   251,   303,    87,   177,   253,   305,
      87,   176,   255,   307,    87,   177,   259,   309,    87,   176,
     263,   311,    87,   177,   268,   313,   178,   179,   182,   186,
     187,   188,   193,   194,   203,   212,   228,   244,   245,   249,
     250,   251,   253,   255,   259,   263,   268,    87,   175,   315,
     341,    87,   177,   319,   343,    87,   177,   321,   345,    87,
     177,   324,   347,    87,   177,   328,   349,   315,   319,   321,
     324,   328,   175,   332,   175,   339,    87,   339,   351,     9,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   174,   174,   171,   153,   156,   163,   160,
     274,   276,   180,   278,   183,   280,   282,   284,   189,   286,
     288,   195,   290,   204,   292,   213,   294,   229,   296,   298,
     246,   302,   304,   252,   306,   254,   308,   256,   310,   260,
     312,   264,   314,   269,   342,   316,   344,   320,   346,   322,
     348,   325,   350,   329,   333,   340,   352,   170,     9,   157,
     157,   164,   173,   174,   164,    88,   178,    88,   179,   177,
      88,   182,   177,    88,   186,    88,   187,    88,   188,   175,
      88,   193,    88,   194,   176,    88,   203,   177,    88,   212,
     176,    88,   228,   177,    88,   244,    88,   245,   177,    88,
     250,    88,   251,   176,    88,   253,   177,    88,   255,   176,
      88,   259,   177,    88,   263,   176,    88,   268,   177,    88,
     315,   175,    88,   319,   177,    88,   321,   177,    88,   324,
     177,    88,   328,   177,   177,   175,    88,   339,   170,     9,
     181,   184,   190,   196,   205,   214,   230,   247,   257,   261,
     265,   270,   317,   323,   326,   330,   334,   170,   177,   177,
     175,   176,   177,   176,   177,   177,   176,   177,   176,   177,
     175,   177,   177,   177,   177,   185,   191,   197,   206,   215,
     231,   248,   258,   262,   266,   271,   318,   327,   331,   335,
     177,   192,   176,   177,   176,   177,   177,   176,   177,   175,
     177,   177,   177,    83,   175,   198,   207,   216,   232,   267,
     272,   336,   176,   177,   176,   177,   177,   199,   208,   217,
     233,   337,   176,   177,   176,   177,   177,   200,   209,   218,
     234,   338,   176,   177,   176,   177,   177,   201,   210,   219,
     235,   176,   177,   176,   177,   202,   211,   220,   236,   176,
     177,   176,   177,   221,   237,   176,   177,   222,   238,   176,
     177,   223,   239,   176,   177,   224,   240,   176,   177,   225,
     241,   176,   177,   226,   242,   176,   177,   227,   243,   176,
     177
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

/* Line 1455 of yacc.c  */
#line 213 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)) == false) { YYABORT; } ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 214 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->checkHeader() == true) { YYABORT; } ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 217 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 231 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 248 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 250 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 282 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(1) - (1)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 285 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString1.c_str(), 
                                            0,
                                            SKEL->_tmpBitVector1     ); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 290 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); 
                            SKEL->_tmpBitVector1 = 
                                TypeTraits<BitVector>::BitsClear; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 293 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(4) - (4)].stringVal); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 294 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode(SKEL->_tmpString2.c_str(), 
                                            SKEL->_tmpString1.c_str(),
                                            SKEL->_tmpBitVector1     ); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 299 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 310 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::Cluster; ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 311 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpBitVector1 |= FCLocal::MT;      ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 322 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 323 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 324 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 332 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 333 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 335 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 336 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 338 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 339 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 340 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 342 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 343 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 344 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 347 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 348 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 349 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 357 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 358 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 360 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 361 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 363 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 364 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 366 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 367 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 371 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 373 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 375 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 378 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 382 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 384 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 386 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 395 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 397 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 406 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 407 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 413 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 429 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 430 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 431 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 435 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 436 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 437 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 441 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 445 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 446 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 447 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 451 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 452 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 453 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 457 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 461 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 468 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 476 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 608 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 609 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 612 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 613 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 616 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 617 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 621 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 624 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 627 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 628 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 630 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 636 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 637 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 638 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 640 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 647 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 653 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 658 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 659 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 661 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 666 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 672 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 679 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 684 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 685 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 686 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 687 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 688 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 689 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 690 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 691 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 693 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(7) - (17)].doubleVal), (yyvsp[(13) - (17)].doubleVal),
            (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal),
            (yyvsp[(5) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 702 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 703 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 704 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 705 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 706 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 707 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 708 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 709 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 711 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[(1) - (17)].floatVal),  (yyvsp[(7) - (17)].floatVal), (yyvsp[(13) - (17)].floatVal),
            (yyvsp[(3) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal),
            (yyvsp[(5) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 720 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 721 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 722 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 723 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 724 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 725 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 726 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 727 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 728 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 729 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 730 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 731 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 732 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 733 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 734 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 736 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(9) - (31)].doubleVal), (yyvsp[(17) - (31)].doubleVal), (yyvsp[(25) - (31)].doubleVal),
            (yyvsp[(3) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal),
            (yyvsp[(5) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal),
            (yyvsp[(7) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 746 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 747 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 748 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 749 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 750 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 751 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 752 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 753 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 754 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 755 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 756 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 757 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 758 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 759 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 760 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 762 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[(1) - (31)].floatVal),  (yyvsp[(9) - (31)].floatVal), (yyvsp[(17) - (31)].floatVal), (yyvsp[(25) - (31)].floatVal),
            (yyvsp[(3) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal),
            (yyvsp[(5) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal),
            (yyvsp[(7) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 773 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 776 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 777 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 778 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 780 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 787 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 791 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 795 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 801 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 806 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 808 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 814 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 816 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 822 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 823 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 824 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 825 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 831 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 832 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 833 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 834 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 840 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 841 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 842 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 843 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 844 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    ;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 850 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 851 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 852 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 853 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 854 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 1030 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 1031 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 1032 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 1034 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 1041 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 1043 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 1049 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 1050 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 1052 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 1058 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 1059 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 1060 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 1062 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 1068 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 1069 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 1070 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 1072 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 1078 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue();  ;}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 1079 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 1080 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 1081 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 1082 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 1083 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 1085 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[(3) - (13)].floatVal), (yyvsp[(5) - (13)].floatVal), (yyvsp[(7) - (13)].floatVal), (yyvsp[(9) - (13)].floatVal), (yyvsp[(11) - (13)].floatVal), (yyvsp[(13) - (13)].floatVal));
        
        bv.setState((yyvsp[(1) - (13)].intVal));

        SKEL->addVolumeValue(bv);
    ;}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 1095 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 1097 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[(1) - (3)].intVal), (yyvsp[(3) - (3)].intVal)));
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 3790 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
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



/* Line 1675 of yacc.c  */
#line 1150 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

