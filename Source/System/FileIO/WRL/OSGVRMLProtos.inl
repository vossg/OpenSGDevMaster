
void VRMLFile::createStandardPrototypes(void)
{
#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::resetIndent();
#endif

    preStandardProtos();

#if 0
PROTO Anchor [
    eventIn      MFNode   addChildren
    eventIn      MFNode   removeChildren
    exposedField MFNode   children        []
    exposedField SFString description     ""
    exposedField MFString parameter       []
    exposedField MFString url             []
    field        SFVec3f  bboxCenter      0 0 0
    field        SFVec3f  bboxSize        -1 -1 -1
    ] { }
#endif

 beginProto   ("Anchor");
 {
     beginEventInDecl     ("MFNode", Self::OSGmfNode, "addChildren");
     endEventDecl         ();

     beginEventInDecl     ("MFNode", Self::OSGmfNode, "removeChildren");
     endEventDecl         ();

     beginExposedFieldDecl("MFNode",   Self::OSGmfNode,   "children");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFString", Self::OSGsfString, "description");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "parameter");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f",  Self::OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f",  Self::OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto         ();


#if 0
PROTO Appearance [
  exposedField SFNode material          NULL
  exposedField SFNode texture           NULL
  exposedField SFNode textureTransform  NULL
] { }
#endif

 beginProto("Appearance");
 {
     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "material");
//     addFieldValue         ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "texture");
//     addFieldValue         ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "textureTransform");
//     addFieldValue         ("NULL");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto         ();


#if 0
PROTO AudioClip [
  exposedField   SFString description  ""
  exposedField   SFBool   loop         FALSE
  exposedField   SFFloat  pitch        1.0
  exposedField   SFTime   startTime    0
  exposedField   SFTime   stopTime     0
  exposedField   MFString url          []
  eventOut       SFTime   duration_changed
  eventOut       SFBool   isActive
] { }
#endif

 beginProto("AudioClip");
 {
     beginExposedFieldDecl("SFString", Self::OSGsfString, "description");
     addFieldValue        ("");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "loop");
     addFieldValue        ("FALSE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "pitch");
     addFieldValue        ("1.0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "startTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "stopTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "url");
     endExposedFieldDecl  ();

     beginEventOutDecl      ("SFTime", Self::OSGsfTime, "duration_changed");
     endEventDecl           ();

     beginEventOutDecl      ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl           ();
 }
 endProtoInterface();
 endProto         ();

#if 0
PROTO Background [
  eventIn      SFBool   set_bind
  exposedField MFFloat  groundAngle  []
  exposedField MFColor  groundColor  []
  exposedField MFString backUrl      []
  exposedField MFString bottomUrl    []
  exposedField MFString frontUrl     []
  exposedField MFString leftUrl      []
  exposedField MFString rightUrl     []
  exposedField MFString topUrl       []
  exposedField MFFloat  skyAngle     []
  exposedField MFColor  skyColor     [ 0 0 0  ]
  eventOut     SFBool   isBound
] { }
#endif

 beginProto("Background");
 {
     beginEventInDecl       ("SFBool", Self::OSGsfBool, "set_bind");
     endEventDecl           ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "groundAngle");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFColor", Self::OSGmfColor, "groundColor");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "backUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "bottomUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "frontUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "leftUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "rightUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "topUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "skyAngle");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFColor", Self::OSGmfColor, "skyColor");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isBound");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto         ();



#if 0
PROTO Billboard [
  eventIn      MFNode   addChildren
  eventIn      MFNode   removeChildren
  exposedField SFVec3f  axisOfRotation  0 1 0
  exposedField MFNode   children        []
  field        SFVec3f  bboxCenter      0 0 0
  field        SFVec3f  bboxSize        -1 -1 -1
] { }
#endif

 beginProto("Billboard");
 {
     beginEventInDecl     ("MFNode", Self::OSGmfNode, "addChildren");
     endEventDecl         ();

     beginEventInDecl     ("MFNode", Self::OSGmfNode, "removeChildren");
     endEventDecl         ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "axisOfRotation");
     addFieldValue        ("0 1 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFNode", Self::OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto         ();


#if 0
PROTO Box [
  field    SFVec3f size  2 2 2
] { }
#endif

 beginProto("Box");
 {
     beginFieldDecl("SFVec3f", Self::OSGsfVec3f, "size");
     addFieldValue ("2 2 2");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Collision [
  eventIn      MFNode   addChildren
  eventIn      MFNode   removeChildren
  exposedField MFNode   children        []
  exposedField SFBool   collide         TRUE
  field        SFVec3f  bboxCenter      0 0 0
  field        SFVec3f  bboxSize        -1 -1 -1
  field        SFNode   proxy           NULL
  eventOut     SFTime   collideTime
] { }
#endif

 beginProto("Collision");
 {
     beginEventInDecl      ("MFNode", Self::OSGmfNode, "addChildren");
     endEventDecl          ();

     beginEventInDecl      ("MFNode", Self::OSGmfNode, "removeChildren");
     endEventDecl          ();

     beginExposedFieldDecl("MFNode", Self::OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "collide");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();

     beginFieldDecl       ("SFNode", Self::OSGsfNode, "proxy");
     endFieldDecl         ();

     beginEventOutDecl      ("SFTime", OSGsfTime, "collideTime");
     endEventDecl           ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Color [
  exposedField MFColor color     []
] { }
#endif

 beginProto("Color");
 {
     beginExposedFieldDecl("MFColor", Self::OSGmfColor, "color");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO ColorInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFColor keyValue  []
  eventOut     SFColor value_changed
] { }
#endif

 beginProto("ColorInterpolator");
 {
     beginEventInDecl     ("SFFloat", OSGsfFloat, "set_fraction");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFColor", Self::OSGmfColor, "keyValue");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFColor", Self::OSGsfColor, "value_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Cone [
  field     SFFloat   bottomRadius 1
  field     SFFloat   height       2
  field     SFBool    side         TRUE
  field     SFBool    bottom       TRUE
] { }
#endif

 beginProto("Cone");
 {
     beginFieldDecl("SFFloat", Self::OSGsfFloat, "bottomRadius");
     addFieldValue ("1");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", Self::OSGsfFloat, "height");
     addFieldValue ("2");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "side");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "bottom");
     addFieldValue ("TRUE");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Coordinate [
  exposedField MFVec3f point  []
] { }
#endif

 beginProto("Coordinate");
 {
     beginExposedFieldDecl("MFVec3f", Self::OSGmfVec3f, "point");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO CoordinateInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     MFVec3f value_changed
] { }
#endif

 beginProto("CoordinateInterpolator");
 {
     beginEventInDecl     ("SFFloat", Self::OSGsfFloat, "set_fraction");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFVec3f", Self::OSGmfVec3f, "keyValue");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("MFVec3f", Self::OSGmfVec3f, "value_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Cylinder [
  field    SFBool    bottom  TRUE
  field    SFFloat   height  2
  field    SFFloat   radius  1
  field    SFBool    side    TRUE
  field    SFBool    top     TRUE
] { }
#endif

 beginProto("Cylinder");
 {
     beginFieldDecl("SFBool", Self::OSGsfBool, "bottom");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", Self::OSGsfFloat, "height");
     addFieldValue ("2");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", Self::OSGsfFloat, "radius");
     addFieldValue ("1");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "side");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "top");
     addFieldValue ("TRUE");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO CylinderSensor [
  exposedField SFBool     autoOffset TRUE
  exposedField SFFloat    diskAngle  0.262
  exposedField SFBool     enabled    TRUE
  exposedField SFFloat    maxAngle   -1
  exposedField SFFloat    minAngle   0
  exposedField SFFloat    offset     0
  eventOut     SFBool     isActive
  eventOut     SFRotation rotation_changed
  eventOut     SFVec3f    trackPoint_changed
] { }
#endif

 beginProto("CylinderSensor");
 {
     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "autoOffset");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "diskAngle");
     addFieldValue        ("0.262");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "maxAngle");
     addFieldValue        ("-1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "minAngle");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "offset");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl         ();

     beginEventOutDecl    ("SFRotation",
                           Self::OSGsfRotation,
                           "rotation_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "trackPoint_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO DirectionalLight [
  exposedField SFFloat ambientIntensity  0
  exposedField SFColor color             1 1 1
  exposedField SFVec3f direction         0 0 -1
  exposedField SFFloat intensity         1
  exposedField SFBool  on                TRUE
] { }
#endif

 beginProto("DirectionalLight");
 {
     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "direction");
     addFieldValue        ("0 0 -1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "on");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO ElevationGrid [
  eventIn      MFFloat  set_height
  exposedField SFNode   color             NULL
  exposedField SFNode   normal            NULL
  exposedField SFNode   texCoord          NULL
  field        SFBool   ccw               TRUE
  field        SFBool   colorPerVertex    TRUE
  field        SFFloat  creaseAngle       0
  field        MFFloat  height            []
  field        SFBool   normalPerVertex   TRUE
  field        SFBool   solid             TRUE
  field        SFInt32  xDimension        0
  field        SFFloat  xSpacing          0.0
  field        SFInt32  zDimension        0
  field        SFFloat  zSpacing          0.0

] { }
#endif

 beginProto("ElevationGrid");
 {
     beginEventInDecl     ("MFFloat", Self::OSGmfFloat, "set_height");
     endEventDecl         ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "normal");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "texCoord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "ccw");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "colorPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", Self::OSGsfFloat, "creaseAngle");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("MFFloat", Self::OSGmfFloat, "height");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "normalPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "solid");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFInt32", Self::OSGsfInt32, "xDimension");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", Self::OSGsfFloat, "xSpacing");
     addFieldValue        ("0.0");
     endFieldDecl         ();

     beginFieldDecl       ("SFInt32", Self::OSGsfInt32, "zDimension");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", Self::OSGsfFloat, "zSpacing");
     addFieldValue        ("0.0");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Extrusion [
  eventIn MFVec2f    set_crossSection
  eventIn MFRotation set_orientation
  eventIn MFVec2f    set_scale
  eventIn MFVec3f    set_spine
  field   SFBool     beginCap         TRUE
  field   SFBool     ccw              TRUE
  field   SFBool     convex           TRUE
  field   SFFloat    creaseAngle      0
  field   MFVec2f    crossSection     [ 1 1, 1 -1, -1 -1, -1 1, 1 1 ]
  field   SFBool     endCap           TRUE
  field   MFRotation orientation      0 0 1 0
  field   MFVec2f    scale            1 1
  field   SFBool     solid            TRUE
  field   MFVec3f    spine            [ 0 0 0, 0 1 0 ]
] { }
#endif

 beginProto("Extrusion");
 {
     beginEventInDecl("MFVec2f", Self::OSGmfVec2f, "set_crossSection");
     endEventDecl    ();
     beginEventInDecl("MFRotation", Self::OSGmfRotation, "set_orientation");
     endEventDecl    ();

     beginEventInDecl("MFVec2f", Self::OSGmfVec2f, "set_scale");
     endEventDecl    ();

     beginEventInDecl("MFVec3f", Self::OSGmfVec3f, "set_spine");
     endEventDecl    ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "beginCap");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "ccw");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "convex");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", Self::OSGsfFloat, "creaseAngle");
     addFieldValue ("0");
     endFieldDecl  ();

     beginFieldDecl("MFVec2f", Self::OSGmfVec2f, "crossSection");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "endCap");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("MFRotation", Self::OSGmfRotation, "orientation");
     endFieldDecl  ();

     beginFieldDecl("MFVec2f", Self::OSGmfVec2f, "scale");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "solid");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("MFVec3f", Self::OSGmfVec3f, "spine");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Fog [
  exposedField SFColor  color            1 1 1
  exposedField SFString fogType          "LINEAR"
  exposedField SFFloat  visibilityRange  0
  eventIn      SFBool   set_bind
  eventOut     SFBool   isBound
] { }
#endif

 beginProto("Fog");
 {
     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFString", Self::OSGsfString, "fogType");
     addFieldValue        ("LINEAR");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "visibilityRange");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginEventInDecl     ("SFBool", Self::OSGsfBool, "set_bind");
     endEventDecl         ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isBound");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO FontStyle [
  field SFString family     "SERIF"
  field SFBool   horizontal  TRUE
  field MFString justify     "BEGIN"
  field SFString language    ""
  field SFBool   leftToRight TRUE
  field SFFloat  size       1.0
  field SFFloat  spacing     1.0
  field SFString style       "PLAIN"
  field SFBool   topToBottom TRUE
] { }
#endif

 beginProto("FontStyle");
 {
     beginFieldDecl("SFString", Self::OSGsfString, "family");
     addFieldValue ("SERIF");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "horizontal");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("MFString", Self::OSGmfString, "justify");
     addFieldValue ("BEGIN");
     endFieldDecl  ();

     beginFieldDecl("SFString", Self::OSGsfString, "language");
     addFieldValue ("");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "leftToRight");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", Self::OSGsfFloat, "size");
     addFieldValue ("1.0");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", Self::OSGsfFloat, "spacing");
     addFieldValue ("1.0");
     endFieldDecl  ();

     beginFieldDecl("SFString", Self::OSGsfString, "style");
     addFieldValue ("PLAIN");
     endFieldDecl  ();

     beginFieldDecl("SFBool", Self::OSGsfBool, "topToBottom");
     addFieldValue ("TRUE");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto   ();

#if 0
PROTO Group [
  eventIn      MFNode  addChildren
  eventIn      MFNode  removeChildren
  exposedField MFNode  children   []
  field        SFVec3f bboxCenter 0 0 0
  field        SFVec3f bboxSize   -1 -1 -1
] { }
#endif

 beginProto("Group");
 {
     beginEventInDecl     ("MFNode", Self::OSGmfNode, "addChildren");
     endEventDecl         ();

     beginEventInDecl     ("MFNode", Self::OSGmfNode, "removeChildren");
     endEventDecl         ();

     beginExposedFieldDecl("MFNode", Self::OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO ImageTexture [
  exposedField MFString url     []
  field        SFBool   repeatS TRUE
  field        SFBool   repeatT TRUE
] { }
#endif

 beginProto("ImageTexture");
 {
     beginExposedFieldDecl("MFString", Self::OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "repeatS");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "repeatT");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO IndexedFaceSet [
  eventIn       MFInt32 set_colorIndex
  eventIn       MFInt32 set_coordIndex
  eventIn       MFInt32 set_normalIndex
  eventIn       MFInt32 set_texCoordIndex
  exposedField  SFNode  color             NULL
  exposedField  SFNode  coord             NULL
  exposedField  SFNode  normal            NULL
  exposedField  SFNode  texCoord          NULL
  field         SFBool  ccw               TRUE
  field         MFInt32 colorIndex        []
  field         SFBool  colorPerVertex    TRUE
  field         SFBool  convex            TRUE
  field         MFInt32 coordIndex        []
  field         SFFloat creaseAngle       0
  field         MFInt32 normalIndex       []
  field         SFBool  normalPerVertex   TRUE
  field         SFBool  solid             TRUE
  field         MFInt32 texCoordIndex     []
] { }
#endif

 beginProto("IndexedFaceSet");
 {
     beginEventInDecl       ("MFInt32", Self::OSGmfInt32, "set_colorIndex");
     endEventDecl           ();

     beginEventInDecl       ("MFInt32", Self::OSGmfInt32, "set_coordIndex");
     endEventDecl           ();

     beginEventInDecl       ("MFInt32", Self::OSGmfInt32, "set_normalIndex");
     endEventDecl           ();

     beginEventInDecl       ("MFInt32", Self::OSGmfInt32, "set_texCoordIndex");
     endEventDecl           ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "coord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "normal");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "texCoord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "ccw");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", Self::OSGmfInt32, "colorIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "colorPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "convex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", Self::OSGmfInt32, "coordIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", Self::OSGsfFloat, "creaseAngle");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", Self::OSGmfInt32, "normalIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool",  Self::OSGsfBool, "normalPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool",  Self::OSGsfBool, "solid");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", Self::OSGmfInt32, "texCoordIndex");
     endFieldDecl();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO IndexedLineSet [
  eventIn       MFInt32 set_colorIndex
  eventIn       MFInt32 set_coordIndex
  exposedField  SFNode  color             NULL
  exposedField  SFNode  coord             NULL
  field         MFInt32 colorIndex        []
  field         SFBool  colorPerVertex    TRUE
  field         MFInt32 coordIndex        []
] { }
#endif

 beginProto("IndexedLineSet");
 {
     beginEventInDecl     ("MFInt32", Self::OSGmfInt32, "set_colorIndex");
     endEventDecl         ();

     beginEventInDecl     ("MFInt32", Self::OSGmfInt32, "set_coordIndex");
     endEventDecl         ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "coord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("MFInt32", Self::OSGmfInt32, "colorIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "colorPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", Self::OSGmfInt32, "coordIndex");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Inline [
  exposedField MFString url        []
  field        SFVec3f  bboxCenter 0 0 0
  field        SFVec3f  bboxSize   -1 -1 -1
] { }
#endif

 beginProto("Inline");
 {
     beginExposedFieldDecl("MFString", Self::OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO LOD [
  exposedField MFNode  level    []
  field        SFVec3f center   0 0 0
  field        MFFloat range    []
] { }
#endif

 beginProto("LOD");
 {
     beginExposedFieldDecl("MFNode", Self::OSGmfNode, "level");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("MFFloat", Self::OSGmfFloat, "range");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Material [
  exposedField SFFloat ambientIntensity  0.2
  exposedField SFColor diffuseColor      0.8 0.8 0.8
  exposedField SFColor emissiveColor     0 0 0
  exposedField SFFloat shininess         0.2
  exposedField SFColor specularColor     0 0 0
  exposedField SFFloat transparency      0
] { }
#endif

 beginProto("Material");
 {
     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0.2");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "diffuseColor");
     addFieldValue        ("0.8 0.8 0.8");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "emissiveColor");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "shininess");
     addFieldValue        ("0.2");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "specularColor");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "transparency");
     addFieldValue        ("0");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto         ();


#if 0
PROTO MovieTexture [
  exposedField SFBool   loop       FALSE
  exposedField SFFloat  speed      1
  exposedField SFTime   startTime  0
  exposedField SFTime   stopTime   0
  exposedField MFString url       []
  field        SFBool   repeatS    TRUE
  field        SFBool   repeatT    TRUE
  eventOut     SFFloat  duration_changed
  eventOut     SFBool   isActive
] { }
#endif

 beginProto("MovieTexture");
 {
     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "loop");
     addFieldValue        ("FALSE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "speed");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "startTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "stopTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "repeatS");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "repeatT");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginEventOutDecl    ("SFFloat", Self::OSGsfFloat, "duration_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFBool",  Self::OSGsfBool,  "isActive");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO NavigationInfo [
  eventIn      SFBool   set_bind
  exposedField MFFloat  avatarSize       [ 0.25, 1.6, 0.75 ]
  exposedField SFBool   headlight        TRUE
  exposedField SFFloat  speed            1.0
  exposedField MFString type             "WALK"
  exposedField SFFloat  visibilityLimit  0.0
  eventOut     SFBool   isBound
] { }
#endif

 beginProto("NavigationInfo");
 {
     beginEventInDecl     ("SFBool", Self::OSGsfBool, "set_bind");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "avatarSize");
     addFieldValue        ("0.25");
     addFieldValue        ("1.6 ");
     addFieldValue        ("0.75");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "headlight");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "speed");
     addFieldValue        ("1.0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", Self::OSGmfString, "type");
     addFieldValue        ("WALK");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "visibilityLimit");
     addFieldValue        ("0.0");
     endExposedFieldDecl  ();

     beginEventOutDecl      ("SFBool", Self::OSGsfBool, "isBound");
     endEventDecl           ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Normal [
  exposedField MFVec3f vector []
] { }
#endif

 beginProto("Normal");
 {
     beginExposedFieldDecl("MFVec3f", Self::OSGmfVec3f, "vector");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO NormalInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     MFVec3f value_changed
] { }
#endif

 beginProto("NormalInterpolator");
 {
     beginEventInDecl     ("SFFloat", Self::OSGsfFloat, "set_fraction");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFVec3f", Self::OSGmfVec3f, "keyValue");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("MFVec3f",  Self::OSGmfVec3f, "value_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO OrientationInterpolator [
  eventIn      SFFloat    set_fraction
  exposedField MFFloat    key       []
  exposedField MFRotation keyValue  []
  eventOut     SFRotation value_changed
] { }
#endif

 beginProto("OrientationInterpolator");
 {
     beginEventInDecl     ("SFFloat", Self::OSGsfFloat, "set_fraction");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFRotation", Self::OSGmfRotation, "keyValue");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFRotation", Self::OSGsfRotation, "value_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO PixelTexture [
  exposedField SFImage  image      0 0 0
  field        SFBool   repeatS    TRUE
  field        SFBool   repeatT    TRUE
] { }
#endif

 beginProto("PixelTexture");
 {
     beginExposedFieldDecl("SFImage", Self::OSGsfImage, "image");
//     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "repeatS");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "repeatT");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO PlaneSensor [
  exposedField SFBool  autoOffset  TRUE
  exposedField SFBool  enabled     TRUE
  exposedField SFVec2f maxPosition -1 -1
  exposedField SFVec2f minPosition 0 0
  exposedField SFVec3f offset      0 0 0
  eventOut     SFBool  isActive
  eventOut     SFVec3f trackPoint_changed
  eventOut     SFVec3f translation_changed
] { }
#endif

 beginProto("PlaneSensor");
 {
     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "autoOffset");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", Self::OSGsfVec2f, "maxPosition");
     addFieldValue        ("-1 -1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", Self::OSGsfVec2f, "minPosition");
     addFieldValue        ("0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "offset");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "trackPoint_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "translation_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();


#if 0
PROTO PointLight [
  exposedField SFFloat ambientIntensity  0
  exposedField SFVec3f attenuation       1 0 0
  exposedField SFColor color             1 1 1
  exposedField SFFloat intensity         1
  exposedField SFVec3f location          0 0 0
  exposedField SFBool  on                TRUE
  exposedField SFFloat radius            100
] { }
#endif

 beginProto("PointLight");
 {
     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "attenuation");
     addFieldValue        ("1 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "location");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "on");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "radius");
     addFieldValue        ("100");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO PointSet [
  exposedField  SFNode  color      NULL
  exposedField  SFNode  coord      NULL
] { }
#endif

 beginProto("PointSet");
 {
     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endFieldDecl         ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "coord");
//     addFieldValue        ("NULL");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO PositionInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     SFVec3f value_changed
] { }
#endif

 beginProto("PositionInterpolator");
 {
     beginEventInDecl     ("SFFloat", Self::OSGsfFloat, "set_fraction");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "key");
     endExposedFieldDecl();

     beginExposedFieldDecl("MFVec3f", Self::OSGmfVec3f, "keyValue");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "value_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO ProximitySensor [
  exposedField SFVec3f    center      0 0 0
  exposedField SFVec3f    size        0 0 0
  exposedField SFBool     enabled     TRUE
  eventOut     SFBool     isActive
  eventOut     SFVec3f    position_changed
  eventOut     SFRotation orientation_changed
  eventOut     SFTime     enterTime
  eventOut     SFTime     exitTime
] { }
#endif

 beginProto("ProximitySensor");
 {
     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "size");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "position_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFRotation",
                           Self::OSGsfRotation,
                           "orientation_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "enterTime");
     endEventDecl         ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "exitTime");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO ScalarInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFFloat keyValue  []
  eventOut     SFFloat value_changed
] { }
#endif

 beginProto("ScalarInterpolator");
 {
     beginEventInDecl     ("SFFloat", Self::OSGsfFloat, "set_fraction");
     endEventDecl         ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFFloat", Self::OSGmfFloat, "keyValue");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFFloat", Self::OSGsfFloat, "value_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Script [
  exposedField MFString url           [ ]
  field        SFBool   directOutput  FALSE
  field        SFBool   mustEvaluate  FALSE
] { }
#endif

 beginProto("Script");
 {
     beginExposedFieldDecl("MFString", Self::OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "directOutput");
     addFieldValue        ("FALSE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "mustEvaluate");
     addFieldValue        ("FALSE");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Shape [
  field SFNode appearance NULL
  field SFNode geometry   NULL
] { }
#endif

 beginProto("Shape");
 {
     beginFieldDecl("SFNode", Self::OSGsfNode, "appearance");
//     addFieldValue ("NULL");
     endFieldDecl  ();

     beginFieldDecl("SFNode", Self::OSGsfNode, "geometry");
//     addFieldValue ("NULL");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Sound [
  exposedField SFVec3f  direction     0 0 1
  exposedField SFFloat  intensity     1
  exposedField SFVec3f  location      0 0 0
  exposedField SFFloat  maxBack       10
  exposedField SFFloat  maxFront      10
  exposedField SFFloat  minBack       1
  exposedField SFFloat  minFront      1
  exposedField SFFloat  priority      0
  exposedField SFNode   source        NULL
  field        SFBool   spatialize    TRUE
] { }
#endif

 beginProto("Sound");
 {
     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "direction");
     addFieldValue        ("0 0 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "location");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "maxBack");
     addFieldValue        ("10");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "maxFront");
     addFieldValue        ("10");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "minBack");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "minFront");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "priority");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", Self::OSGsfNode, "source");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", Self::OSGsfBool, "spatialize");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Sphere [
  field SFFloat radius     1
] { }
#endif

 beginProto("Sphere");
 {
     beginFieldDecl("SFFloat", Self::OSGsfFloat, "radius");
     addFieldValue ("1");
     endFieldDecl  ();

     beginFieldDecl("SFInt", Self::OSGsfInt32, "resolution");
     addFieldValue ("8");
     endFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO SphereSensor [
  exposedField SFBool     autoOffset TRUE
  exposedField SFBool     enabled    TRUE
  exposedField SFRotation offset     0 1 0 0
  eventOut     SFBool     isActive
  eventOut     SFRotation rotation_changed
  eventOut     SFVec3f    trackPoint_changed
] { }
#endif

 beginProto("SphereSensor");
 {
     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "autoOffset");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", Self::OSGsfRotation, "offset");
     addFieldValue        ("0 1 0 0");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl         ();

     beginEventOutDecl    ("SFRotation",
                           Self::OSGsfRotation,
                           "rotation_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "trackPoint_changed");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO SpotLight [
  exposedField SFFloat ambientIntensity  0
  exposedField SFVec3f attenuation       1 0 0
  exposedField SFFloat beamWidth         1.570796
  exposedField SFColor color             1 1 1
  exposedField SFFloat cutOffAngle       0.785398
  exposedField SFVec3f direction         0 0 -1
  exposedField SFFloat intensity         1
  exposedField SFVec3f location          0 0 0
  exposedField SFBool  on                TRUE
  exposedField SFFloat radius            100
] { }
#endif

 beginProto("SpotLight");
 {
     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "attenuation");
     addFieldValue        ("1 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "beamWidth");
     addFieldValue        ("1.570796");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", Self::OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "cutOffAngle");
     addFieldValue        ("0.785398");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "direction");
     addFieldValue        ("0 0 -1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "location");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "on");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "radius");
     addFieldValue        ("100");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Switch [
  exposedField    MFNode  choice      []
  exposedField    SFInt32 whichChoice -1
] { }
#endif

 beginProto("Switch");
 {
     beginExposedFieldDecl("MFNode", Self::OSGmfNode, "choice");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFInt32", Self::OSGsfInt32, "whichChoice");
     addFieldValue        ("-1");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Text [
  exposedField  MFString string    []
  field         SFNode   fontStyle NULL
  field         MFFloat  length    []
  field         SFFloat  maxExtent 0.0
] { }
#endif

 beginProto("Text");
 {
     beginExposedFieldDecl("MFString", Self::OSGmfString, "string");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFNode", Self::OSGsfNode, "fontStyle");
//     addFieldValue        ("NULL");
     endFieldDecl         ();

     beginFieldDecl       ("MFFloat", Self::OSGmfFloat, "length");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", Self::OSGsfFloat, "maxExtent");
     addFieldValue        ("0.0");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO TextureCoordinate [
  exposedField MFVec2f point []
] { }
#endif

 beginProto("TextureCoordinate");
 {
     beginExposedFieldDecl("MFVec2f", Self::OSGmfVec2f, "point");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO TextureTransform [
  exposedField SFVec2f center      0 0
  exposedField SFFloat rotation    0
  exposedField SFVec2f scale       1 1
  exposedField SFVec2f translation 0 0
] { }
#endif

 beginProto("TextureTransform");
 {
     beginExposedFieldDecl("SFVec2f", Self::OSGsfVec2f, "center");
     addFieldValue        ("0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "rotation");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", Self::OSGsfVec2f, "scale");
     addFieldValue        ("1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", Self::OSGsfVec2f, "translation");
     addFieldValue        ("0 0");
     endExposedFieldDecl  ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO TimeSensor [
  exposedField SFTime   cycleInterval 1
  exposedField SFBool   enabled       TRUE
  exposedField SFBool   loop          FALSE
  exposedField SFTime   startTime     0
  exposedField SFTime   stopTime      0
  eventOut     SFTime   cycleTime
  eventOut     SFFloat  fraction_changed
  eventOut     SFBool   isActive
  eventOut     SFTime   time
] { }
#endif

 beginProto("TimeSensor");
 {
     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "cycleInterval");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "loop");
     addFieldValue        ("FALSE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "startTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", Self::OSGsfTime, "stopTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "cycleTime");
     endEventDecl         ();

     beginEventOutDecl    ("SFFloat", Self::OSGsfFloat, "fraction_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl         ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "time");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO TouchSensor [
  exposedField SFBool  enabled TRUE
  eventOut     SFVec3f hitNormal_changed
  eventOut     SFVec3f hitPoint_changed
  eventOut     SFVec2f hitTexCoord_changed
  eventOut     SFBool  isActive
  eventOut     SFBool  isOver
  eventOut     SFTime  touchTime
] { }
#endif

 beginProto("TouchSensor");
 {
     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "hitNormal_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec3f", Self::OSGsfVec3f, "hitPoint_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFVec2f", Self::OSGsfVec2f, "hitTexCoord_changed");
     endEventDecl         ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive");
     endEventDecl         ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isOver");
     endEventDecl         ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "touchTime");
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Transform [
  eventIn      MFNode      addChildren
  eventIn      MFNode      removeChildren
  exposedField SFVec3f     center           0 0 0
  exposedField MFNode      children         []
  exposedField SFRotation  rotation         0 0 1  0
  exposedField SFVec3f     scale            1 1 1
  exposedField SFRotation  scaleOrientation 0 0 1  0
  exposedField SFVec3f     translation      0 0 0
  field        SFVec3f     bboxCenter       0 0 0
  field        SFVec3f     bboxSize         -1 -1 -1
] { }
#endif

 beginProto("Transform");
 {
     beginEventInDecl     ("MFNode", Self::OSGsfNode, "addChildren");
     endEventDecl         ();

     beginEventInDecl     ("MFNode", Self::OSGsfNode, "removeChildren");
     endEventDecl         ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFNode", Self::OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", Self::OSGsfRotation, "rotation");
     addFieldValue        ("0 0 1  0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "scale");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", Self::OSGsfRotation, "scaleOrientation");
     addFieldValue        ("0 0 1  0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "translation");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", Self::OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO Viewpoint [
  eventIn      SFBool     set_bind
  exposedField SFFloat    fieldOfView    0.785398
  exposedField SFBool     jump           TRUE
  exposedField SFRotation orientation    0 0 1  0
  exposedField SFVec3f    position       0 0 10
  field        SFString   description    ""
  eventOut     SFTime     bindTime
  eventOut     SFBool     isBound
] { }
#endif

 beginProto("Viewpoint");
 {
     beginEventInDecl     ("SFBool", Self::OSGsfBool, "set_bind");
     endEventDecl         ();

     beginExposedFieldDecl("SFFloat", Self::OSGsfFloat, "fieldOfView");
     addFieldValue        ("0.785398");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "jump");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", Self::OSGsfRotation, "orientation");
     addFieldValue        ("0 0 1  0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "position");
     addFieldValue        ("0 0 10");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFString", Self::OSGsfString, "description");
     addFieldValue        ("");
     endFieldDecl         ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "bindTime");
     endEventDecl         ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isBound" );
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO VisibilitySensor [
  exposedField SFVec3f center   0 0 0
  exposedField SFBool  enabled  TRUE
  exposedField SFVec3f size     0 0 0
  eventOut     SFTime  enterTime
  eventOut     SFTime  exitTime
  eventOut     SFBool  isActive
] { }
#endif

 beginProto("VisibilitySensor");
 {
     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", Self::OSGsfBool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", Self::OSGsfVec3f, "size");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "enterTime");
     endEventDecl         ();

     beginEventOutDecl    ("SFTime", Self::OSGsfTime, "exitTime" );
     endEventDecl         ();

     beginEventOutDecl    ("SFBool", Self::OSGsfBool, "isActive" );
     endEventDecl         ();
 }
 endProtoInterface();
 endProto  ();

#if 0
PROTO WorldInfo [
  field MFString info  []
  field SFString title ""
] { }
#endif

 beginProto("WorldInfo");
 {
     beginFieldDecl("MFString", Self::OSGmfString, "info");
     endFieldDecl  ();

     beginFieldDecl("SFString", Self::OSGsfString, "title");
     addFieldValue("");
     endFieldDecl();
 }
 endProtoInterface();
 endProto  ();

// Custom

#if 0
PROTO Teapot [
  field SFInt    depth 5
  field SFFloat scale 1
] { }
#endif

 beginProto("Teapot");
 {
     beginFieldDecl("SFInt", Self::OSGsfInt32, "depth");
     addFieldValue("5");
     endFieldDecl  ();

     beginFieldDecl("SFInt", Self::OSGsfFloat, "scale");
     addFieldValue("1.0");
     endFieldDecl  ();

/*
     beginFieldDecl("SFString", Self::OSGsfString, "title");
     addFieldValue("");
     endFieldDecl();
 */
 }
 endProtoInterface();
 endProto  ();

 postStandardProtos();

}
