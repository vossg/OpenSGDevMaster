
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
     TOK_Error = 339
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
#line 211 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
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
#line 258 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"

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
#define YYLAST   967

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  256
/* YYNRULES -- Number of rules.  */
#define YYNRULES  459
/* YYNRULES -- Number of states.  */
#define YYNSTATES  751

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    89,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,     2,    88,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    29,    32,    33,    34,    39,    41,    43,
      46,    47,    49,    51,    53,    55,    57,    58,    62,    63,
      64,    71,    74,    76,    78,    79,    80,    91,    94,    95,
      96,   101,   102,   107,   108,   109,   116,   117,   118,   125,
     126,   127,   136,   139,   140,   141,   146,   147,   152,   153,
     158,   159,   164,   165,   166,   167,   179,   180,   181,   189,
     190,   195,   198,   199,   201,   205,   208,   209,   211,   213,
     215,   217,   219,   221,   222,   223,   230,   231,   232,   239,
     240,   243,   244,   245,   252,   253,   254,   261,   263,   267,
     268,   272,   274,   276,   278,   280,   282,   286,   288,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   322,   324,   326,   328,   330,
     332,   334,   336,   338,   340,   342,   344,   346,   348,   350,
     352,   354,   356,   358,   360,   362,   364,   366,   368,   370,
     372,   374,   376,   378,   380,   382,   384,   386,   388,   390,
     392,   394,   396,   398,   400,   402,   405,   408,   411,   414,
     417,   420,   423,   426,   429,   432,   435,   438,   441,   444,
     447,   450,   453,   456,   459,   462,   465,   468,   471,   474,
     477,   480,   483,   486,   489,   492,   495,   498,   501,   504,
     507,   510,   513,   516,   519,   522,   525,   528,   531,   534,
     537,   540,   543,   546,   549,   552,   555,   558,   561,   564,
     567,   569,   571,   573,   575,   577,   579,   581,   583,   584,
     585,   591,   592,   593,   594,   602,   604,   606,   607,   608,
     609,   618,   621,   622,   624,   625,   626,   627,   628,   629,
     630,   631,   632,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   738,   770,   772,   774,   775,   776,   777,
     785,   787,   789,   791,   793,   794,   798,   799,   803,   804,
     805,   806,   813,   814,   815,   816,   823,   824,   825,   826,
     827,   836,   837,   838,   839,   840,   849,   851,   855,   858,
     859,   861,   865,   868,   869,   871,   875,   878,   879,   881,
     885,   888,   889,   891,   895,   898,   899,   901,   905,   908,
     909,   911,   915,   918,   919,   921,   925,   928,   929,   931,
     935,   938,   939,   941,   945,   948,   949,   951,   955,   958,
     959,   961,   965,   968,   969,   971,   975,   978,   979,   981,
     985,   988,   989,   991,   995,   998,   999,  1001,  1005,  1008,
    1009,  1011,  1015,  1018,  1019,  1021,  1025,  1028,  1029,  1031,
    1035,  1038,  1039,  1041,  1045,  1048,  1049,  1051,  1055,  1058,
    1059,  1060,  1061,  1062,  1070,  1071,  1075,  1076,  1077,  1083,
    1084,  1085,  1086,  1094,  1095,  1096,  1097,  1105,  1106,  1107,
    1108,  1109,  1110,  1111,  1125,  1126,  1130,  1132,  1136,  1139,
    1140,  1142,  1146,  1149,  1150,  1152,  1156,  1159,  1160,  1162,
    1166,  1169,  1170,  1172,  1176,  1179,  1180,  1182,  1186,  1189
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      91,     0,    -1,    92,    93,    95,    98,   103,    -1,     3,
      -1,    -1,     4,    94,    -1,    -1,    82,    -1,    95,    96,
      -1,    -1,     5,    97,    -1,    82,    -1,    79,    -1,    98,
      99,    -1,    -1,    -1,     6,   101,   100,   102,    -1,    79,
      -1,    79,    -1,   103,   104,    -1,    -1,   105,    -1,   109,
      -1,   130,    -1,   134,    -1,   137,    -1,    -1,   162,   106,
     141,    -1,    -1,    -1,    10,   161,   107,   162,   108,   141,
      -1,    11,   161,    -1,   110,    -1,   121,    -1,    -1,    -1,
       7,   162,   111,    85,   113,    86,   112,    87,   103,    88,
      -1,   113,   114,    -1,    -1,    -1,    17,   166,   115,   164,
      -1,    -1,    18,   166,   116,   165,    -1,    -1,    -1,    20,
     166,   117,   163,   118,   167,    -1,    -1,    -1,    19,   166,
     119,   163,   120,   167,    -1,    -1,    -1,     8,   162,   122,
      85,   124,    86,   123,   140,    -1,   124,   125,    -1,    -1,
      -1,    17,   166,   126,   164,    -1,    -1,    18,   166,   127,
     165,    -1,    -1,    20,   166,   128,   163,    -1,    -1,    19,
     166,   129,   163,    -1,    -1,    -1,    -1,    12,   161,   131,
      89,   165,   132,    13,   161,   133,    89,   164,    -1,    -1,
      -1,    14,   161,   135,    89,   161,   136,   139,    -1,    -1,
      15,   161,   138,   139,    -1,    16,   161,    -1,    -1,   292,
      -1,    87,   142,    88,    -1,   142,   143,    -1,    -1,   158,
      -1,   144,    -1,   147,    -1,   151,    -1,   154,    -1,     1,
      -1,    -1,    -1,    17,   166,   145,   164,   146,   150,    -1,
      -1,    -1,    18,   166,   148,   165,   149,   150,    -1,    -1,
       9,   163,    -1,    -1,    -1,    20,   166,   152,   163,   153,
     157,    -1,    -1,    -1,    19,   166,   155,   163,   156,   157,
      -1,   167,    -1,   166,     9,   163,    -1,    -1,   163,   159,
     160,    -1,   130,    -1,   109,    -1,   134,    -1,   137,    -1,
     167,    -1,   166,     9,   163,    -1,    82,    -1,    82,    -1,
      82,    -1,    82,    -1,    82,    -1,    21,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,
      73,    -1,    21,   266,    -1,    22,   268,    -1,    23,   270,
      -1,    24,   272,    -1,    25,   274,    -1,    26,   276,    -1,
      27,   278,    -1,    28,   280,    -1,    29,   282,    -1,    30,
     284,    -1,    31,   286,    -1,    32,   288,    -1,    33,   290,
      -1,    34,   292,    -1,    35,   294,    -1,    36,   296,    -1,
      37,   298,    -1,    38,   300,    -1,    39,   302,    -1,    40,
     304,    -1,    41,   306,    -1,    42,   171,    -1,    43,   172,
      -1,    44,   175,    -1,    45,   179,    -1,    46,   180,    -1,
      47,   181,    -1,    48,   186,    -1,    49,   187,    -1,    50,
     196,    -1,    51,   205,    -1,    52,   221,    -1,    53,   237,
      -1,    54,   238,    -1,    55,   242,    -1,    56,   243,    -1,
      57,   244,    -1,    58,   246,    -1,    59,   248,    -1,    60,
     252,    -1,    61,   256,    -1,    62,   261,    -1,    63,   334,
      -1,    64,   336,    -1,    65,   338,    -1,    66,   340,    -1,
      67,   342,    -1,    68,   308,    -1,    69,   312,    -1,    70,
     314,    -1,    71,   317,    -1,    72,   321,    -1,    73,   325,
      -1,    74,   332,    -1,    75,   344,    -1,    76,    -1,    77,
      -1,    77,    -1,    78,    -1,    77,    -1,    78,    -1,    80,
      -1,    82,    -1,    -1,    -1,   170,   173,   170,   174,   170,
      -1,    -1,    -1,    -1,   170,   176,   170,   177,   170,   178,
     170,    -1,   169,    -1,   170,    -1,    -1,    -1,    -1,   168,
     182,   168,   183,   168,   184,   185,    83,    -1,   185,   168,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   169,   188,   169,   189,   169,   190,   169,   191,
     169,   192,   169,   193,   169,   194,   169,   195,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,   197,
     170,   198,   170,   199,   170,   200,   170,   201,   170,   202,
     170,   203,   170,   204,   170,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   169,   206,   169,   207,   169,   208,   169,   209,   169,
     210,   169,   211,   169,   212,   169,   213,   169,   214,   169,
     215,   169,   216,   169,   217,   169,   218,   169,   219,   169,
     220,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,   222,
     170,   223,   170,   224,   170,   225,   170,   226,   170,   227,
     170,   228,   170,   229,   170,   230,   170,   231,   170,   232,
     170,   233,   170,   234,   170,   235,   170,   236,   170,    -1,
     105,    -1,    81,    -1,    -1,    -1,    -1,   170,   239,   170,
     240,   170,   241,   170,    -1,    79,    -1,    82,    -1,    76,
      -1,   169,    -1,    -1,   169,   245,   169,    -1,    -1,   170,
     247,   170,    -1,    -1,    -1,    -1,   169,   249,   169,   250,
     169,   251,    -1,    -1,    -1,    -1,   170,   253,   170,   254,
     170,   255,    -1,    -1,    -1,    -1,    -1,   169,   257,   169,
     258,   169,   259,   169,   260,    -1,    -1,    -1,    -1,    -1,
     170,   262,   170,   263,   170,   264,   170,   265,    -1,   171,
      -1,    85,   267,    86,    -1,   267,   171,    -1,    -1,   172,
      -1,    85,   269,    86,    -1,   269,   172,    -1,    -1,   175,
      -1,    85,   271,    86,    -1,   271,   175,    -1,    -1,   179,
      -1,    85,   273,    86,    -1,   273,   179,    -1,    -1,   180,
      -1,    85,   275,    86,    -1,   275,   180,    -1,    -1,   181,
      -1,    85,   277,    86,    -1,   277,   181,    -1,    -1,   186,
      -1,    85,   279,    86,    -1,   279,   186,    -1,    -1,   187,
      -1,    85,   281,    86,    -1,   281,   187,    -1,    -1,   196,
      -1,    85,   283,    86,    -1,   283,   196,    -1,    -1,   205,
      -1,    85,   285,    86,    -1,   285,   205,    -1,    -1,   221,
      -1,    85,   287,    86,    -1,   287,   221,    -1,    -1,   237,
      -1,    85,   289,    86,    -1,   289,   237,    -1,    -1,   238,
      -1,    85,   291,    86,    -1,   291,   238,    -1,    -1,   242,
      -1,    85,   293,    86,    -1,   293,   242,    -1,    -1,   243,
      -1,    85,   295,    86,    -1,   295,   243,    -1,    -1,   244,
      -1,    85,   297,    86,    -1,   297,   244,    -1,    -1,   246,
      -1,    85,   299,    86,    -1,   299,   246,    -1,    -1,   248,
      -1,    85,   301,    86,    -1,   301,   248,    -1,    -1,   252,
      -1,    85,   303,    86,    -1,   303,   252,    -1,    -1,   256,
      -1,    85,   305,    86,    -1,   305,   256,    -1,    -1,   261,
      -1,    85,   307,    86,    -1,   307,   261,    -1,    -1,    -1,
      -1,    -1,   168,   309,   168,   310,   168,   311,   168,    -1,
      -1,   170,   313,   170,    -1,    -1,    -1,   170,   315,   170,
     316,   170,    -1,    -1,    -1,    -1,   170,   318,   170,   319,
     170,   320,   170,    -1,    -1,    -1,    -1,   170,   322,   170,
     323,   170,   324,   170,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   168,   326,   170,   327,   170,   328,   170,   329,   170,
     330,   170,   331,   170,    -1,    -1,   168,   333,   168,    -1,
     308,    -1,    85,   335,    86,    -1,   335,   308,    -1,    -1,
     312,    -1,    85,   337,    86,    -1,   337,   312,    -1,    -1,
     314,    -1,    85,   339,    86,    -1,   339,   314,    -1,    -1,
     317,    -1,    85,   341,    86,    -1,   341,   317,    -1,    -1,
     321,    -1,    85,   343,    86,    -1,   343,   321,    -1,    -1,
     332,    -1,    85,   345,    86,    -1,   345,   332,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   202,   202,   209,   210,   213,   214,   217,   220,   221,
     225,   230,   231,   238,   239,   244,   242,   249,   252,   255,
     256,   259,   260,   261,   262,   263,   266,   266,   269,   270,
     268,   272,   276,   277,   284,   285,   284,   289,   290,   294,
     293,   297,   296,   300,   301,   299,   304,   305,   303,   309,
     310,   309,   314,   315,   319,   318,   322,   321,   325,   324,
     328,   327,   333,   335,   337,   332,   344,   346,   343,   357,
     356,   367,   369,   372,   375,   378,   379,   382,   383,   384,
     385,   386,   387,   391,   392,   390,   397,   398,   396,   401,
     403,   407,   408,   406,   413,   414,   412,   418,   419,   423,
     422,   431,   432,   433,   434,   437,   438,   441,   444,   447,
     450,   453,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     570,   571,   574,   575,   578,   579,   582,   586,   589,   590,
     589,   598,   599,   600,   598,   608,   614,   620,   621,   623,
     620,   633,   637,   640,   646,   647,   648,   649,   650,   651,
     652,   653,   646,   664,   665,   666,   667,   668,   669,   670,
     671,   664,   682,   683,   684,   685,   686,   687,   688,   689,
     690,   691,   692,   693,   694,   695,   696,   682,   708,   709,
     710,   711,   712,   713,   714,   715,   716,   717,   718,   719,
     720,   721,   722,   708,   734,   735,   738,   739,   740,   738,
     748,   752,   756,   762,   768,   768,   776,   776,   784,   785,
     786,   784,   793,   794,   795,   793,   802,   803,   804,   805,
     802,   812,   813,   814,   815,   812,   822,   823,   826,   827,
     830,   831,   834,   835,   838,   839,   842,   843,   846,   847,
     850,   851,   854,   855,   858,   859,   862,   863,   866,   867,
     870,   871,   874,   875,   878,   879,   882,   883,   886,   887,
     890,   891,   894,   895,   898,   899,   902,   903,   906,   907,
     910,   911,   914,   915,   918,   919,   922,   923,   926,   927,
     930,   931,   934,   935,   938,   939,   942,   943,   946,   947,
     950,   951,   954,   955,   958,   959,   962,   963,   966,   967,
     970,   971,   974,   975,   978,   979,   982,   983,   986,   987,
     992,   993,   994,   992,  1003,  1003,  1011,  1012,  1011,  1020,
    1021,  1022,  1020,  1030,  1031,  1032,  1030,  1040,  1041,  1042,
    1043,  1044,  1045,  1040,  1057,  1057,  1065,  1066,  1069,  1070,
    1073,  1074,  1077,  1078,  1081,  1082,  1085,  1086,  1089,  1090,
    1093,  1094,  1097,  1098,  1101,  1102,  1105,  1106,  1109,  1110
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
  "TOK_ImageFinished", "TOK_Error", "'['", "']'", "'{'", "'}'", "'.'",
  "$accept", "x3dScene", "headerStatement", "profileStatement",
  "profileNameId", "componentStatements", "componentStatement",
  "componentNameId", "metaStatements", "metaStatement", "$@1", "metakey",
  "metavalue", "statements", "statement", "nodeStatement", "$@2", "$@3",
  "$@4", "protoStatement", "proto", "$@5", "$@6", "interfaceDeclarations",
  "interfaceDeclaration", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "externproto", "$@13", "$@14", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "$@15", "$@16", "$@17", "$@18",
  "routeStatement", "$@19", "$@20", "$@21", "importStatement", "$@22",
  "$@23", "exportStatement", "$@24", "asStatement", "URLList", "node",
  "scriptBody", "scriptBodyElement", "eventInDeclaration", "$@25", "$@26",
  "eventOutDeclaration", "$@27", "$@28", "eventDeclarationEnd",
  "fieldDeclaration", "$@29", "$@30", "exposedFieldDeclaration", "$@31",
  "$@32", "fieldDeclarationEnd", "nodeBodyElement", "$@33", "fieldEnd",
  "nodeNameId", "nodeTypeId", "fieldId", "eventInId", "eventOutId",
  "fieldType", "fieldValue", "int32", "double", "float", "sfboolValue",
  "sfcolorValue", "$@34", "$@35", "sfcolorRGBAValue", "$@36", "$@37",
  "$@38", "sfdoubleValue", "sffloatValue", "sfimageValue", "$@39", "$@40",
  "$@41", "pixels", "sfint32Value", "sfmatrix3dValue", "$@42", "$@43",
  "$@44", "$@45", "$@46", "$@47", "$@48", "$@49", "sfmatrix3fValue",
  "$@50", "$@51", "$@52", "$@53", "$@54", "$@55", "$@56", "$@57",
  "sfmatrix4dValue", "$@58", "$@59", "$@60", "$@61", "$@62", "$@63",
  "$@64", "$@65", "$@66", "$@67", "$@68", "$@69", "$@70", "$@71", "$@72",
  "sfmatrix4fValue", "$@73", "$@74", "$@75", "$@76", "$@77", "$@78",
  "$@79", "$@80", "$@81", "$@82", "$@83", "$@84", "$@85", "$@86", "$@87",
  "sfnodeValue", "sfrotationValue", "$@88", "$@89", "$@90",
  "sfstringValue", "sftimeValue", "sfvec2dValue", "$@91", "sfvec2fValue",
  "$@92", "sfvec3dValue", "$@93", "$@94", "$@95", "sfvec3fValue", "$@96",
  "$@97", "$@98", "sfvec4dValue", "$@99", "$@100", "$@101", "$@102",
  "sfvec4fValue", "$@103", "$@104", "$@105", "$@106", "mfboolValue",
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
  "$@107", "$@108", "$@109", "sfpnt2fValue", "$@110", "sfpnt3fValue",
  "$@111", "$@112", "sfpnt4fValue", "$@113", "$@114", "$@115",
  "sfplaneValue", "$@116", "$@117", "$@118", "sfVolumeValue", "$@119",
  "$@120", "$@121", "$@122", "$@123", "$@124", "sfvec2iValue", "$@125",
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
     335,   336,   337,   338,   339,    91,    93,   123,   125,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    90,    91,    92,    92,    93,    93,    94,    95,    95,
      96,    97,    97,    98,    98,   100,    99,   101,   102,   103,
     103,   104,   104,   104,   104,   104,   106,   105,   107,   108,
     105,   105,   109,   109,   111,   112,   110,   113,   113,   115,
     114,   116,   114,   117,   118,   114,   119,   120,   114,   122,
     123,   121,   124,   124,   126,   125,   127,   125,   128,   125,
     129,   125,   131,   132,   133,   130,   135,   136,   134,   138,
     137,   139,   139,   140,   141,   142,   142,   143,   143,   143,
     143,   143,   143,   145,   146,   144,   148,   149,   147,   150,
     150,   152,   153,   151,   155,   156,   154,   157,   157,   159,
     158,   158,   158,   158,   158,   160,   160,   161,   162,   163,
     164,   165,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   173,   174,
     172,   176,   177,   178,   175,   179,   180,   182,   183,   184,
     181,   185,   185,   186,   188,   189,   190,   191,   192,   193,
     194,   195,   187,   197,   198,   199,   200,   201,   202,   203,
     204,   196,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   205,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   221,   237,   237,   239,   240,   241,   238,
     242,   242,   242,   243,   245,   244,   247,   246,   249,   250,
     251,   248,   253,   254,   255,   252,   257,   258,   259,   260,
     256,   262,   263,   264,   265,   261,   266,   266,   267,   267,
     268,   268,   269,   269,   270,   270,   271,   271,   272,   272,
     273,   273,   274,   274,   275,   275,   276,   276,   277,   277,
     278,   278,   279,   279,   280,   280,   281,   281,   282,   282,
     283,   283,   284,   284,   285,   285,   286,   286,   287,   287,
     288,   288,   289,   289,   290,   290,   291,   291,   292,   292,
     293,   293,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     309,   310,   311,   308,   313,   312,   315,   316,   314,   318,
     319,   320,   317,   322,   323,   324,   321,   326,   327,   328,
     329,   330,   331,   325,   333,   332,   334,   334,   335,   335,
     336,   336,   337,   337,   338,   338,   339,   339,   340,   340,
     341,   341,   342,   342,   343,   343,   344,   344,   345,   345
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     1,     2,     0,     0,     4,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     0,     3,     0,     0,
       6,     2,     1,     1,     0,     0,    10,     2,     0,     0,
       4,     0,     4,     0,     0,     6,     0,     0,     6,     0,
       0,     8,     2,     0,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     0,     0,    11,     0,     0,     7,     0,
       4,     2,     0,     1,     3,     2,     0,     1,     1,     1,
       1,     1,     1,     0,     0,     6,     0,     0,     6,     0,
       2,     0,     0,     6,     0,     0,     6,     1,     3,     0,
       3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       5,     0,     0,     0,     7,     1,     1,     0,     0,     0,
       8,     2,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     1,     1,     0,     0,     0,     7,
       1,     1,     1,     1,     0,     3,     0,     3,     0,     0,
       0,     6,     0,     0,     0,     6,     0,     0,     0,     0,
       8,     0,     0,     0,     0,     8,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       0,     0,     0,     7,     0,     3,     0,     0,     5,     0,
       0,     0,     7,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,    13,     0,     3,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    14,
       0,     8,    20,    12,    11,    10,     0,    13,     2,    17,
      15,     0,     0,     0,     0,     0,     0,     0,   108,    19,
      21,    22,    32,    33,    23,    24,    25,    26,     0,    34,
      49,   107,    28,    31,    62,    66,    69,     0,    18,    16,
       0,     0,     0,     0,     0,    72,    76,    27,    38,    53,
      29,     0,     0,     0,    70,     0,     0,     0,     0,   111,
      63,    67,    71,    82,     0,     0,     0,     0,   109,    74,
     102,   101,   103,   104,    75,    78,    79,    80,    81,    77,
      99,     0,     0,     0,     0,    35,    37,     0,     0,     0,
       0,    50,    52,    30,     0,    72,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,    83,
      86,    94,    91,     0,    39,    41,    46,    43,     0,    54,
      56,    60,    58,     0,     0,    68,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,     0,     0,   100,     0,   105,     0,     0,
       0,     0,    20,     0,     0,     0,     0,   302,   300,   301,
     381,    51,   378,    73,    64,   110,    84,    87,    95,    92,
     226,   227,   329,   326,   165,   224,   225,   333,   228,   330,
     166,   337,   231,   334,   167,   222,   223,   341,   235,   338,
     168,   345,   236,   342,   169,   220,   221,   349,   237,   346,
     170,   353,   243,   350,   171,   357,   244,   354,   172,   361,
     253,   358,   173,   365,   262,   362,   174,   369,   278,   366,
     175,   295,   373,   294,   370,   176,   377,   296,   374,   177,
     178,   385,   303,   382,   179,   389,   304,   386,   180,   393,
     306,   390,   181,   397,   308,   394,   182,   401,   312,   398,
     183,   405,   316,   402,   184,   409,   321,   406,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     439,   410,   436,   207,   443,   414,   440,   208,   447,   416,
     444,   209,   451,   419,   448,   210,   455,   423,   452,   211,
     212,   213,   214,   215,   216,   427,   217,   434,   218,   459,
     456,   219,     0,    40,    42,    47,    44,     0,    55,    57,
      61,    59,     0,     0,    89,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,     0,    36,   379,
     380,     0,     0,    85,    88,    96,     0,    97,    93,   327,
     328,   331,   332,   229,   335,   336,   232,   339,   340,   343,
     344,   347,   348,   238,   351,   352,   355,   356,   245,   359,
     360,   254,   363,   364,   263,   367,   368,   279,   371,   372,
     375,   376,   297,   383,   384,   387,   388,   305,   391,   392,
     307,   395,   396,   309,   399,   400,   313,   403,   404,   317,
     407,   408,   322,   437,   438,   411,   441,   442,   415,   445,
     446,   417,   449,   450,   420,   453,   454,   424,   428,   435,
     457,   458,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    45,    65,    90,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    98,   230,   233,
     239,   246,   255,   264,   280,   298,   310,   314,   318,   323,
     412,   418,   421,   425,   429,     0,   242,     0,     0,     0,
       0,     0,   311,   315,     0,     0,     0,     0,     0,     0,
     234,     0,   247,   256,   265,   281,   299,   319,   324,   413,
     422,   426,   430,   240,   241,     0,     0,     0,     0,   320,
     325,     0,   248,   257,   266,   282,   431,     0,     0,     0,
       0,     0,   249,   258,   267,   283,   432,     0,     0,     0,
       0,     0,   250,   259,   268,   284,   433,     0,     0,     0,
       0,   251,   260,   269,   285,     0,     0,     0,     0,   252,
     261,   270,   286,     0,     0,   271,   287,     0,     0,   272,
     288,     0,     0,   273,   289,     0,     0,   274,   290,     0,
       0,   275,   291,     0,     0,   276,   292,     0,     0,   277,
     293
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    15,    12,    17,
      38,    20,    49,    18,    29,   313,    47,    52,    68,    31,
      32,    50,   168,    66,    96,   238,   239,   241,   467,   240,
     466,    33,    51,   173,    67,   102,   243,   244,   246,   245,
      34,    53,   104,   413,    35,    54,   105,    36,    55,    64,
     251,    57,    65,    84,    85,   176,   414,    86,   177,   415,
     473,    87,   179,   417,    88,   178,   416,   475,    89,   163,
     235,    42,    37,    90,   256,    70,   476,   477,   288,   278,
     268,   263,   269,   420,   610,   273,   422,   611,   645,   279,
     283,   289,   426,   612,   646,   661,   293,   297,   429,   613,
     647,   675,   687,   697,   707,   715,   301,   431,   614,   648,
     676,   688,   698,   708,   716,   305,   433,   615,   649,   677,
     689,   699,   709,   717,   723,   727,   731,   735,   739,   743,
     747,   309,   435,   616,   650,   678,   690,   700,   710,   718,
     724,   728,   732,   736,   740,   744,   748,   314,   318,   438,
     617,   651,   252,   323,   327,   441,   331,   443,   335,   445,
     618,   652,   339,   447,   619,   653,   343,   449,   620,   654,
     679,   347,   451,   621,   655,   680,   264,   418,   270,   419,
     274,   421,   280,   423,   284,   424,   290,   425,   294,   427,
     298,   428,   302,   430,   306,   432,   310,   434,   315,   436,
     319,   437,   320,   412,   324,   439,   328,   440,   332,   442,
     336,   444,   340,   446,   344,   448,   348,   450,   372,   453,
     622,   656,   376,   455,   380,   457,   623,   384,   459,   624,
     657,   388,   461,   625,   658,   396,   462,   626,   659,   681,
     691,   701,   398,   463,   373,   452,   377,   454,   381,   456,
     385,   458,   389,   460,   401,   464
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -230
static const yytype_int16 yypact[] =
{
       1,  -230,    36,    88,  -230,    42,  -230,  -230,  -230,   126,
      31,  -230,    79,  -230,  -230,  -230,    62,  -230,   141,  -230,
    -230,    68,    68,    72,    72,    72,    72,    72,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,    90,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,    99,  -230,  -230,
     103,   104,    68,   107,   120,   188,  -230,  -230,  -230,  -230,
    -230,   143,    72,    72,  -230,    97,    56,   119,    99,  -230,
    -230,  -230,  -230,  -230,   894,   894,   894,   894,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,   894,   894,   894,   894,  -230,  -230,   894,   894,   894,
     894,  -230,  -230,  -230,   213,   188,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,   554,  -230,  -230,  -230,  -230,   154,  -230,
    -230,  -230,  -230,   105,    72,  -230,   164,   143,   169,   169,
     -17,   151,   241,   286,   290,   115,   118,   387,   401,   403,
     405,    78,   420,   105,   425,   436,   445,   454,   470,   486,
     553,   -28,    52,    52,    87,    52,    57,    57,    87,    52,
      87,    52,    80,    52,   211,    87,    87,    52,    87,    52,
      87,    52,   121,   555,   557,   559,   568,    57,    52,    52,
      52,    52,    57,    57,   125,  -230,   249,  -230,   164,   143,
     169,   169,  -230,   164,   143,   169,   169,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   169,  -230,  -230,  -230,  -230,   111,  -230,  -230,
    -230,  -230,    96,   174,   262,   262,   554,   554,   135,   130,
      52,   134,    52,   136,   214,   -26,    57,     7,   219,    87,
     226,    52,   237,    87,   239,    52,    46,   256,    52,   258,
     268,    87,   270,    52,   272,    87,   274,    52,   284,    87,
     368,    52,    81,    57,   370,    52,   374,    52,   381,    52,
     384,    52,    52,    57,    94,  -230,   839,   839,  -230,  -230,
    -230,   164,   169,  -230,  -230,  -230,   277,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   -17,   151,   241,   286,   290,   115,   118,   387,
     401,   403,   405,    78,   420,   105,   425,   436,   445,   454,
     470,   486,   553,   -28,    52,    52,    87,    52,    57,    57,
      87,    52,    87,    52,    80,    52,   211,    87,    87,    52,
      87,    52,    87,    52,   121,   555,   557,   559,   568,    57,
      52,    52,    52,    52,    57,  -230,  -230,  -230,  -230,   169,
      52,    52,    57,    87,    52,    87,    52,    52,    87,    52,
      87,    52,    57,    52,    52,    52,    52,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,    52,  -230,    87,    52,    87,
      52,    52,  -230,  -230,    87,    52,    57,    52,    52,    52,
    -230,   100,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,    87,    52,    87,    52,  -230,
    -230,    52,  -230,  -230,  -230,  -230,  -230,    87,    52,    87,
      52,    52,  -230,  -230,  -230,  -230,  -230,    87,    52,    87,
      52,    52,  -230,  -230,  -230,  -230,  -230,    87,    52,    87,
      52,  -230,  -230,  -230,  -230,    87,    52,    87,    52,  -230,
    -230,  -230,  -230,    87,    52,  -230,  -230,    87,    52,  -230,
    -230,    87,    52,  -230,  -230,    87,    52,  -230,  -230,    87,
      52,  -230,  -230,    87,    52,  -230,  -230,    87,    52,  -230,
    -230
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,    25,  -230,   -15,  -230,  -230,  -230,   218,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
     233,  -230,  -230,  -230,   243,  -230,  -230,   245,  -230,   197,
    -230,   253,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
     -91,  -230,  -230,  -230,  -230,  -230,  -230,   -88,  -230,  -230,
    -230,    45,   122,  -159,  -176,   -71,     3,  -129,   -87,   112,
    -182,  -200,  -195,  -230,  -230,  -194,  -230,  -230,  -230,  -193,
    -192,  -191,  -230,  -230,  -230,  -230,  -190,  -184,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -197,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -185,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -189,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -186,  -183,  -230,
    -230,  -230,  -181,  -177,  -158,  -230,  -172,  -230,  -178,  -230,
    -230,  -230,  -187,  -230,  -230,  -230,  -167,  -230,  -230,  -230,
    -230,  -166,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   158,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -163,  -230,
    -230,  -230,  -169,  -230,  -168,  -230,  -230,  -164,  -230,  -230,
    -230,  -203,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -229,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     272,   349,   282,    30,     1,   400,   300,   350,   308,   351,
     317,   352,   357,   353,   330,   354,   338,   355,   346,   258,
     259,   272,   359,   282,   356,   358,   360,   300,   394,   308,
     361,   317,   367,   362,   237,   330,     4,   338,   363,   346,
     366,   375,   379,   383,   387,   365,   375,   379,   383,   387,
     285,   286,   260,   368,   261,   369,    23,    24,   364,   391,
     491,   392,   403,   260,   390,   261,   393,   408,   262,    43,
      44,    45,    46,    91,    92,    93,    94,   159,   160,   161,
     162,   405,   406,   285,   286,    16,   410,   411,    23,    24,
      23,    24,     5,   494,   164,   165,   166,   167,    73,   292,
     169,   170,   171,   172,    21,    22,   257,    71,    72,    25,
      13,    26,    27,    14,    74,    75,    76,    77,    21,    22,
     292,    23,    24,    25,     7,    26,    27,   311,    28,   265,
     266,    10,   508,   285,   286,   371,    97,    98,    99,   100,
     371,    19,    95,    39,    40,   395,   397,   397,    21,    22,
      28,    23,    24,    25,    41,    26,    27,   285,   286,   311,
      28,   311,    28,   312,   275,   276,   236,   533,   404,    48,
     285,   286,   247,   409,    60,   248,   285,   286,   249,    78,
     550,   247,   469,   673,   248,    79,    56,   249,    58,    59,
     250,   285,   286,    28,   285,   286,    61,   285,   286,   468,
     287,   285,   286,   291,    63,   101,   370,   265,   266,    62,
     399,   265,   266,   275,   276,   260,   481,   261,   480,   254,
     484,   479,   487,    28,   482,    69,   174,   485,   265,   266,
     488,   470,   490,   500,   492,   551,   267,   495,   483,   272,
     486,   242,   282,   465,   497,   506,   255,   503,   300,   501,
     509,    78,   308,   507,   511,   317,   512,   546,   402,   525,
     330,   520,   514,   471,   338,   526,   522,   407,   346,   532,
     519,   472,   375,   538,   379,   541,   383,   544,   387,   547,
     548,   528,   516,    80,   531,   537,   609,   247,   540,   534,
     248,   265,   266,   249,   543,   607,   275,   276,    81,   296,
     489,   304,   175,   265,   266,   496,   322,   326,    82,   334,
      83,   342,   499,   608,   275,   276,   265,   266,   265,   266,
     296,   103,   304,   502,   474,   505,   271,   322,   326,   478,
     334,   253,   342,   265,   266,   275,   276,   605,   606,   493,
     292,     0,   510,     0,   513,   275,   276,   265,   266,   275,
     276,   265,   266,     0,   515,     0,   518,     0,   521,     0,
     524,   275,   276,   275,   276,   371,   535,   265,   266,     0,
     527,   277,   272,   349,   282,   281,   549,   397,   300,   350,
     308,   351,   317,   352,   357,   353,   330,   354,   338,   355,
     346,     0,    30,   272,   359,   282,   356,   358,   360,   300,
     394,   308,   361,   317,   367,   362,     0,   330,     0,   338,
     363,   346,   366,   375,   379,   383,   387,   365,   375,   379,
     383,   387,     0,     0,     0,   368,     0,   369,   628,   629,
     364,   391,   632,   392,   634,   635,   390,   637,   393,   639,
       0,   641,   642,   643,   644,   265,   266,   265,   266,     0,
     627,   265,   266,     0,   530,     0,   536,     0,   265,   266,
     539,   265,   266,   660,   275,   276,   663,   542,   665,   666,
     545,   292,   295,   668,     0,   670,   671,   672,   265,   266,
     275,   276,   265,   266,     0,     0,   299,     0,   303,     0,
     307,     0,   292,     0,   683,     0,   685,   265,   266,   686,
       0,     0,   275,   276,     0,   316,   693,   371,   695,   696,
     321,     0,   371,   275,   276,     0,   703,   395,   705,   706,
       0,   325,   265,   266,     0,   630,   712,     0,   714,     0,
     329,   275,   276,     0,   720,   640,   722,     0,     0,   333,
     296,   498,   726,     0,   304,   504,   730,   265,   266,     0,
     734,   322,   326,   517,   738,   337,   334,   523,   742,     0,
     342,   529,   746,   275,   276,     0,   750,     0,     0,   669,
       0,   341,     0,     0,   674,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     265,   266,   265,   266,   265,   266,   265,   266,   345,     0,
     374,     0,   378,     0,   382,   265,   266,     0,     0,     0,
       0,     0,     0,   386,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   296,     0,   304,     0,     0,     0,     0,   322,   326,
       0,   334,     0,   342,     0,     0,     0,     0,     0,     0,
       0,     0,   296,     0,   304,     0,     0,     0,     0,   322,
     326,     0,   334,     0,   342,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   631,     0,   633,     0,     0,
     636,     0,   638,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   662,
       0,   664,     0,     0,     0,     0,   667,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   682,     0,   684,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   692,
       0,   694,     0,     0,     0,     0,     0,     0,     0,   702,
       0,   704,     0,     0,     0,     0,     0,     0,     0,   711,
       0,   713,     0,     0,     0,     0,     0,   719,     0,   721,
       0,     0,     0,     0,     0,   725,     0,     0,     0,   729,
       0,     0,     0,   733,     0,     0,     0,   737,     0,     0,
       0,   741,     0,     0,     0,   745,     0,     0,     0,   749,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   233,   234,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158
};

static const yytype_int16 yycheck[] =
{
     182,   201,   184,    18,     3,   234,   188,   202,   190,   203,
     192,   204,   209,   205,   196,   206,   198,   207,   200,   178,
     179,   203,   211,   205,   208,   210,   212,   209,   231,   211,
     213,   213,   219,   214,   163,   217,     0,   219,   215,   221,
     218,   223,   224,   225,   226,   217,   228,   229,   230,   231,
      76,    77,    80,   220,    82,   221,    10,    11,   216,   228,
      86,   229,   238,    80,   227,    82,   230,   243,    85,    24,
      25,    26,    27,    17,    18,    19,    20,    74,    75,    76,
      77,   240,   241,    76,    77,     6,   245,   246,    10,    11,
      10,    11,     4,    86,    91,    92,    93,    94,     1,   186,
      97,    98,    99,   100,     7,     8,   177,    62,    63,    12,
      79,    14,    15,    82,    17,    18,    19,    20,     7,     8,
     207,    10,    11,    12,    82,    14,    15,    81,    82,    77,
      78,     5,    86,    76,    77,   222,    17,    18,    19,    20,
     227,    79,    86,    21,    22,   232,   233,   234,     7,     8,
      82,    10,    11,    12,    82,    14,    15,    76,    77,    81,
      82,    81,    82,    85,    77,    78,   163,    86,   239,    79,
      76,    77,    76,   244,    52,    79,    76,    77,    82,    82,
      86,    76,    86,    83,    79,    88,    87,    82,    85,    85,
      85,    76,    77,    82,    76,    77,    89,    76,    77,    88,
      85,    76,    77,    85,    16,    86,    85,    77,    78,    89,
      85,    77,    78,    77,    78,    80,    86,    82,   418,   174,
      86,    86,    86,    82,   419,    82,    13,   421,    77,    78,
     423,   412,   424,   430,   425,   464,    85,   427,   420,   421,
     422,    87,   424,   402,   428,   434,    82,   432,   430,   431,
     436,    82,   434,   435,   437,   437,   438,   460,     9,   446,
     442,   443,   439,    89,   446,   447,   444,   242,   450,   451,
     442,     9,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   448,   440,    65,   450,   454,     9,    76,   456,   452,
      79,    77,    78,    82,   458,   471,    77,    78,    65,   187,
      86,   189,   105,    77,    78,    86,   194,   195,    65,   197,
      65,   199,    86,   472,    77,    78,    77,    78,    77,    78,
     208,    68,   210,    86,   415,    86,    85,   215,   216,   417,
     218,   173,   220,    77,    78,    77,    78,   466,   467,   426,
     427,    -1,    86,    -1,    86,    77,    78,    77,    78,    77,
      78,    77,    78,    -1,    86,    -1,    86,    -1,    86,    -1,
      86,    77,    78,    77,    78,   452,   453,    77,    78,    -1,
      86,    85,   554,   573,   556,    85,   463,   464,   560,   574,
     562,   575,   564,   576,   581,   577,   568,   578,   570,   579,
     572,    -1,   407,   575,   583,   577,   580,   582,   584,   581,
     603,   583,   585,   585,   591,   586,    -1,   589,    -1,   591,
     587,   593,   590,   595,   596,   597,   598,   589,   600,   601,
     602,   603,    -1,    -1,    -1,   592,    -1,   593,   610,   611,
     588,   600,   614,   601,   616,   617,   599,   619,   602,   621,
      -1,   623,   624,   625,   626,    77,    78,    77,    78,    -1,
     609,    77,    78,    -1,    86,    -1,    86,    -1,    77,    78,
      86,    77,    78,   645,    77,    78,   648,    86,   650,   651,
      86,   558,    85,   655,    -1,   657,   658,   659,    77,    78,
      77,    78,    77,    78,    -1,    -1,    85,    -1,    85,    -1,
      85,    -1,   579,    -1,   676,    -1,   678,    77,    78,   681,
      -1,    -1,    77,    78,    -1,    85,   688,   594,   690,   691,
      85,    -1,   599,    77,    78,    -1,   698,   604,   700,   701,
      -1,    85,    77,    78,    -1,   612,   708,    -1,   710,    -1,
      85,    77,    78,    -1,   716,   622,   718,    -1,    -1,    85,
     428,   429,   724,    -1,   432,   433,   728,    77,    78,    -1,
     732,   439,   440,   441,   736,    85,   444,   445,   740,    -1,
     448,   449,   744,    77,    78,    -1,   748,    -1,    -1,   656,
      -1,    85,    -1,    -1,   661,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      77,    78,    77,    78,    77,    78,    77,    78,    85,    -1,
      85,    -1,    85,    -1,    85,    77,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   559,    -1,   561,    -1,    -1,    -1,    -1,   566,   567,
      -1,   569,    -1,   571,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   580,    -1,   582,    -1,    -1,    -1,    -1,   587,
     588,    -1,   590,    -1,   592,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   613,    -1,   615,    -1,    -1,
     618,    -1,   620,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   647,
      -1,   649,    -1,    -1,    -1,    -1,   654,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   675,    -1,   677,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   687,
      -1,   689,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   697,
      -1,   699,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   707,
      -1,   709,    -1,    -1,    -1,    -1,    -1,   715,    -1,   717,
      -1,    -1,    -1,    -1,    -1,   723,    -1,    -1,    -1,   727,
      -1,    -1,    -1,   731,    -1,    -1,    -1,   735,    -1,    -1,
      -1,   739,    -1,    -1,    -1,   743,    -1,    -1,    -1,   747,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    91,    92,     0,     4,    93,    82,    94,    95,
       5,    96,    98,    79,    82,    97,     6,    99,   103,    79,
     101,     7,     8,    10,    11,    12,    14,    15,    82,   104,
     105,   109,   110,   121,   130,   134,   137,   162,   100,   162,
     162,    82,   161,   161,   161,   161,   161,   106,    79,   102,
     111,   122,   107,   131,   135,   138,    87,   141,    85,    85,
     162,    89,    89,    16,   139,   142,   113,   124,   108,    82,
     165,   161,   161,     1,    17,    18,    19,    20,    82,    88,
     109,   130,   134,   137,   143,   144,   147,   151,   154,   158,
     163,    17,    18,    19,    20,    86,   114,    17,    18,    19,
      20,    86,   125,   141,   132,   136,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   166,
     166,   166,   166,   159,   166,   166,   166,   166,   112,   166,
     166,   166,   166,   123,    13,   139,   145,   148,   155,   152,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   160,   166,   167,   115,   116,
     119,   117,    87,   126,   127,   129,   128,    76,    79,    82,
      85,   140,   242,   292,   161,    82,   164,   165,   163,   163,
      80,    82,    85,   171,   266,    77,    78,    85,   170,   172,
     268,    85,   170,   175,   270,    77,    78,    85,   169,   179,
     272,    85,   170,   180,   274,    76,    77,    85,   168,   181,
     276,    85,   168,   186,   278,    85,   169,   187,   280,    85,
     170,   196,   282,    85,   169,   205,   284,    85,   170,   221,
     286,    81,    85,   105,   237,   288,    85,   170,   238,   290,
     292,    85,   169,   243,   294,    85,   169,   244,   296,    85,
     170,   246,   298,    85,   169,   248,   300,    85,   170,   252,
     302,    85,   169,   256,   304,    85,   170,   261,   306,   171,
     172,   175,   179,   180,   181,   186,   187,   196,   205,   221,
     237,   238,   242,   243,   244,   246,   248,   252,   256,   261,
      85,   168,   308,   334,    85,   170,   312,   336,    85,   170,
     314,   338,    85,   170,   317,   340,    85,   170,   321,   342,
     308,   312,   314,   317,   321,   168,   325,   168,   332,    85,
     332,   344,     9,   164,   165,   163,   163,   103,   164,   165,
     163,   163,   293,   133,   146,   149,   156,   153,   267,   269,
     173,   271,   176,   273,   275,   277,   182,   279,   281,   188,
     283,   197,   285,   206,   287,   222,   289,   291,   239,   295,
     297,   245,   299,   247,   301,   249,   303,   253,   305,   257,
     307,   262,   335,   309,   337,   313,   339,   315,   341,   318,
     343,   322,   326,   333,   345,   163,   120,   118,    88,    86,
     242,    89,     9,   150,   150,   157,   166,   167,   157,    86,
     171,    86,   172,   170,    86,   175,   170,    86,   179,    86,
     180,    86,   181,   168,    86,   186,    86,   187,   169,    86,
     196,   170,    86,   205,   169,    86,   221,   170,    86,   237,
      86,   238,   170,    86,   243,    86,   244,   169,    86,   246,
     170,    86,   248,   169,    86,   252,   170,    86,   256,   169,
      86,   261,   170,    86,   308,   168,    86,   312,   170,    86,
     314,   170,    86,   317,   170,    86,   321,   170,   170,   168,
      86,   332,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,   167,   167,   164,   163,     9,
     174,   177,   183,   189,   198,   207,   223,   240,   250,   254,
     258,   263,   310,   316,   319,   323,   327,   163,   170,   170,
     168,   169,   170,   169,   170,   170,   169,   170,   169,   170,
     168,   170,   170,   170,   170,   178,   184,   190,   199,   208,
     224,   241,   251,   255,   259,   264,   311,   320,   324,   328,
     170,   185,   169,   170,   169,   170,   170,   169,   170,   168,
     170,   170,   170,    83,   168,   191,   200,   209,   225,   260,
     265,   329,   169,   170,   169,   170,   170,   192,   201,   210,
     226,   330,   169,   170,   169,   170,   170,   193,   202,   211,
     227,   331,   169,   170,   169,   170,   170,   194,   203,   212,
     228,   169,   170,   169,   170,   195,   204,   213,   229,   169,
     170,   169,   170,   214,   230,   169,   170,   215,   231,   169,
     170,   216,   232,   169,   170,   217,   233,   169,   170,   218,
     234,   169,   170,   219,   235,   169,   170,   220,   236,   169,
     170
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
#line 209 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)) == false) { YYABORT; } ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 210 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { if(SKEL->checkHeader() == true) { YYABORT; } ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 213 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 227 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->componentElement((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 244 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 246 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 266 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(1) - (1)].stringVal), 0); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 269 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 270 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginNode((yyvsp[(4) - (4)].stringVal), SKEL->_tmpString1.c_str()); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 273 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->use((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 284 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 285 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProtoInterface(); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 286 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endProto(); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 294 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 295 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 297 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 298 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 300 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 301 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 302 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 304 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 305 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 306 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 309 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 310 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProtoInterface(); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 311 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExternProto(); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 319 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 320 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 322 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 323 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 325 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 326 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 328 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 329 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 333 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 335 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 337 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 340 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 344 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 346 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 348 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 357 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 359 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 368 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 369 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.stringVal) = 0; ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 375 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endNode(); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 391 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 392 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 393 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 397 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 398 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 399 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endEventDecl(); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 403 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(2) - (2)].stringVal)); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 407 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 408 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 409 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endFieldDecl(); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 413 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 414 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 415 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endExposedFieldDecl(); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 419 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 423 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 430 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->endField(); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 438 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->is((yyvsp[(3) - (3)].stringVal)); ;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 570 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 571 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 574 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); ;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 575 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); ;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 578 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); ;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 579 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); ;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 583 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    ;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 586 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); ;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 589 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 590 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 592 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 598 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 599 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 600 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 602 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 609 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 615 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    ;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 620 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 621 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 623 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    ;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 628 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->endImage();
    ;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 634 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    ;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 641 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    ;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 646 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 647 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 648 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 649 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 650 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 651 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 652 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 653 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 655 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(7) - (17)].doubleVal), (yyvsp[(13) - (17)].doubleVal),
            (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal),
            (yyvsp[(5) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    ;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 664 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 665 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 666 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 667 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 668 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 669 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 670 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 671 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 673 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[(1) - (17)].floatVal),  (yyvsp[(7) - (17)].floatVal), (yyvsp[(13) - (17)].floatVal),
            (yyvsp[(3) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal),
            (yyvsp[(5) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    ;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 682 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 683 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 684 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 685 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 686 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 687 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 688 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 689 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 690 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 691 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 692 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 693 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 694 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 695 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 696 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 698 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(9) - (31)].doubleVal), (yyvsp[(17) - (31)].doubleVal), (yyvsp[(25) - (31)].doubleVal),
            (yyvsp[(3) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal),
            (yyvsp[(5) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal),
            (yyvsp[(7) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    ;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 708 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 709 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 710 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 711 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 712 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 713 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 714 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 715 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 716 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 717 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 718 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 719 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 720 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 721 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 722 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 724 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[(1) - (31)].floatVal),  (yyvsp[(9) - (31)].floatVal), (yyvsp[(17) - (31)].floatVal), (yyvsp[(25) - (31)].floatVal),
            (yyvsp[(3) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal),
            (yyvsp[(5) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal),
            (yyvsp[(7) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    ;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 735 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->nullNode(); ;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 738 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 739 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 740 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 742 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    ;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 749 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 753 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    ;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 757 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { /* Not VRML conformant */
        SKEL->addBufferAsStringValue();
    ;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 763 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    ;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 768 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 770 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    ;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 776 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 778 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 784 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 785 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 786 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 787 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    ;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 793 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 794 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 795 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 796 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    ;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 802 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 803 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 804 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 805 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 806 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    ;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 812 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 813 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 814 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 815 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 816 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    ;}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 992 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 993 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 994 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 996 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    ;}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 1003 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 1005 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    ;}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 1011 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 1012 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 1014 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    ;}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 1020 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 1021 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 1022 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 1024 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 1030 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 1031 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 1032 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 1034 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    ;}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 1040 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue();  ;}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 1041 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 1042 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 1043 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 1044 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 1045 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->appendValue(); ;}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 1047 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        BoxVolume bv((yyvsp[(3) - (13)].floatVal), (yyvsp[(5) - (13)].floatVal), (yyvsp[(7) - (13)].floatVal), (yyvsp[(9) - (13)].floatVal), (yyvsp[(11) - (13)].floatVal), (yyvsp[(13) - (13)].floatVal));
        
        bv.setState((yyvsp[(1) - (13)].intVal));

        SKEL->addVolumeValue(bv);
    ;}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 1057 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    { SKEL->beginValue(); ;}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 1059 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"
    {
        SKEL->appendValue();
        SKEL->addVec2iValue(Vec2i((yyvsp[(1) - (3)].intVal), (yyvsp[(3) - (3)].intVal)));
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 3750 "/home/gerrit/Projects/OpenSG/svn/OpenSG.build/Build/OSGSystem/OSGScanParseSkelParser.cpp"
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
#line 1112 "/home/gerrit/Projects/OpenSG/svn/OpenSG/Source/System/FileIO/ScanParseSkel/OSGScanParseSkelParser.yy"


int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

