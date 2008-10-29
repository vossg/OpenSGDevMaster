/*

Header for PLY polygon files.

- Greg Turk, March 1994

A PLY file contains a single polygonal _object_.

An object is composed of lists of _elements_.  Typical elements are
vertices, faces, edges and materials.

Each type of element for a given object has one or more _properties_
associated with the element type.  For instance, a vertex element may
have as properties three floating-point values x,y,z and three unsigned
chars for red, green and blue.

---------------------------------------------------------------

Copyright (c) 1994 The Board of Trustees of The Leland Stanford
Junior University.  All rights reserved.   
  
Permission to use, copy, modify and distribute this software and its   
documentation for any purpose is hereby granted without fee, provided   
that the above copyright notice and this permission notice appear in   
all copies of this software and that you do not sell the software.   
  
THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,   
EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY   
WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.   

-- Changes

- Modified for inclusion in OpenSG.

*/

#ifndef __PLY_H__
#define __PLY_H__

#include <iostream>
#include <vector>
#include <OSGConfig.h>


OSG_BEGIN_NAMESPACE

const int PLY_ASCII     = 1;        /* ascii PLY file */
const int PLY_BINARY_BE = 2;        /* binary PLY file, big endian */
const int PLY_BINARY_LE = 3;        /* binary PLY file, little endian */

const int PLY_OKAY  =  0;           /* ply routine worked okay */
const int PLY_ERROR = -1;           /* error in ply routine */

/* scalar data types supported by PLY format */

const int PLY_START_TYPE = 0;
const int PLY_CHAR       = 1;
const int PLY_SHORT      = 2;
const int PLY_INT        = 3;
const int PLY_UCHAR      = 4;
const int PLY_USHORT     = 5;
const int PLY_UINT       = 6;
const int PLY_FLOAT      = 7;
const int PLY_DOUBLE     = 8;
const int PLY_END_TYPE   = 9;

const bool PLY_SCALAR = false;
const bool PLY_LIST   = true;


struct PlyProperty {    /* description of a property */

  std::string name;                     /* property name */
  int external_type;                    /* file's data type */
  int internal_type;                    /* program's data type */
  int offset;                           /* offset bytes of prop in a struct */

  bool is_list;                         /* 1 = list, 0 = scalar */
  int count_external;                   /* file's count type */
  int count_internal;                   /* program's count type */
  int count_offset;                     /* offset byte for list count */

};

struct PlyElement {     /* description of an element */
  std::string name;               /* element name */
  int num;                        /* number of elements in this object */
  int size;                       /* size of element (bytes) or -1 if variable */
  std::vector<PlyProperty> props; /* list of properties in the file */
  std::vector<char>   store_prop; /* flags: property wanted by user? */
  int other_offset;               /* offset to un-asked-for props, or -1 if none*/
  int other_size;                 /* size of other_props structure */
};

struct PlyOtherProp {   /* describes other properties in an element */
  std::string name;             /* element name */
  int size;                     /* size of other_props */
  int nprops;                   /* number of properties in other_props */
  PlyProperty **props;          /* list of properties in other_props */
};

struct OtherData { /* for storing other_props for an other element */
  void *other_props;
};

struct OtherElem {     /* data for one "other" element */
  std::string elem_name;       /* names of other elements */
  int elem_count;              /* count of instances of each element */
  OtherData **other_data;      /* actual property data for the elements */
  PlyOtherProp *other_props;   /* description of the property data */
};

struct PlyFile {             /* description of PLY file */
  std::ostream *ofp;                 /* output file pointer */
  std::istream *ifp;                 /* input file pointer */
  int file_type;                     /* ascii or binary */
  float version;                     /* version number of file */
  std::vector<PlyElement> elems;     /* list of elements */
  std::vector<std::string> comments; /* list of comments */
  std::vector<std::string> obj_info; /* list of object info items */
  PlyElement *which_elem;            /* which element we're currently writing */
  std::vector<OtherElem> other_elems; /* Elements not interpreterd by user */
  bool reverse_bytes;
};


/*** delcaration of routines ***/

extern PlyFile *ply_write(std::ostream *, int, char **, int);
//extern PlyFile *ply_open_for_writing(char *, int, char **, int, float *);
extern void ply_describe_element(PlyFile *, char *, int, int, PlyProperty *);
extern void ply_describe_property(PlyFile *, char *, PlyProperty *);
extern void ply_element_count(PlyFile *, char *, int);
extern void ply_header_complete(PlyFile *);
extern void ply_put_element_setup(PlyFile *, const std::string&);
extern void ply_put_element(PlyFile *, void *);
extern void ply_put_comment(PlyFile *, char *);
extern void ply_put_obj_info(PlyFile *, char *);
extern PlyFile *ply_read(std::istream *, std::vector<std::string>&);
//extern PlyFile *ply_open_for_reading( char *, int *, char ***, int *, float *);
extern bool ply_get_element_description(PlyFile *, const std::string&, int*, std::vector<PlyProperty>&);
extern void ply_get_element_setup( PlyFile *, char *, int, PlyProperty *);
extern void ply_get_property(PlyFile *, const std::string&, PlyProperty *);
extern PlyOtherProp *ply_get_other_properties(PlyFile *, char *, int);
extern void ply_get_element(PlyFile *, void *);
extern std::vector<std::string>& ply_get_comments(PlyFile *, int *);
extern std::vector<std::string>& ply_get_obj_info(PlyFile *, int *);
extern void ply_close(PlyFile *);
extern void ply_get_info(PlyFile *, float *, int *);
extern std::vector<OtherElem>& ply_get_other_element (PlyFile *, char *, int);
extern void ply_describe_other_elements ( PlyFile *, const std::vector<OtherElem>&);
extern void ply_put_other_elements (PlyFile *);

extern int equal_strings(const char *, const char *);

OSG_END_NAMESPACE

#endif /* !__PLY_H__ */

