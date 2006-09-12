/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

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
/* Tokens.  */
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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





