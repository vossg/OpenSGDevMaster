
import types

import osggen
import pygccxml.declarations 
import pygccxml.declarations as pd

def exposeTemplateType(templateType):

  temp_decl = templateType.decl

  osggen.exposeTemplateInst (temp_decl      )
  osggen.handleClassDefaults(temp_decl, True)
  
  for c in temp_decl.constructors():
    c.exclude()

def customizeWindow(osg, class_name):
  try:
    c = osg.class_(class_name)
    c["init"].exclude()

    c.add_declaration_code("""
namespace
{

void initCallback(bp::object callable)
{
   callable();
}

void wrapInit(OSG::%(class_name)s* self, bp::object callable)
{
   self->init(boost::bind(initCallback, callable));
}

void defaultInit(OSG::%(class_name)s* self)
{
   self->init();
}

}
""" % {'class_name': class_name})

    c.add_registration_code('def("init", defaultInit)')
    c.add_registration_code('def("init", wrapInit, bp::arg("oFunc"))')
  except pygccxml.declarations.matcher.declaration_not_found_t:
    print "Skipping init() handling for", class_name


def handleFindNamedComponent(osg, class_name):
  c = osg.class_(class_name)
  c["findNamedComponent"].exclude()
  c.add_declaration_code("""
namespace
{

OSG::FieldContainerRecPtr
wrapFindNamedComponent(OSG::%s* self,
                       const OSG::Char8* szName)
{
   return OSG::FieldContainerTransitPtr(self->findNamedComponent(szName));
}

}
""" % class_name)

  c.add_registration_code(
     'def("findNamedComponent", wrapFindNamedComponent, (bp::arg("szName")))'
  )


def handlAutoSlotReplace(osg, cname):

  # GCC-XML does not give PyGCCXML enough information to set the default argument correctly
  # for the use of OSG::State::AutoSlotRepalce as the default value of a method parameter of
  # type int. We have to help it out.
  c = osg.class_(cname)

  for mname in ["addChunk", "subChunk", "find"]:
    for decl in c.decls(mname, allow_empty = True):
      for arg in decl.arguments:
        if arg.default_value == "AutoSlotReplace":
          # NOTE: Using a string here is the correct behavior. The value of the string is
          # substituted in the generated code.
          arg.default_value = "OSG::State::AutoSlotReplace"


def dumpSystem(osg):

  cls = osg["ShaderProcVariableBase"]    
  exportable_mems = cls.get_exportable_members()

  if exportable_mems is None:
     exportable_mems = []
  elif exportable_mems and type(exportable_mems[0]) is types.ListType:
     exportable_mems = exportable_mems[0]

  redefined_funcs = cls.redefined_funcs()
  if redefined_funcs is None:
     redefined_funcs = []
  elif redefined_funcs and type(redefined_funcs[0]) is types.ListType:
     redefined_funcs = redefined_funcs[0]

  for member in exportable_mems + redefined_funcs:
    print "mb : ", member
    print "  ]: ", member.ignore
    if hasattr(member, "virtuality"):
       print "  }:", member.virtuality

  print "xxx ", cls.is_wrapper_needed()


  cls = osg["ShaderValueVariableBase"]    
  exportable_mems = cls.get_exportable_members()

  if exportable_mems is None:
     exportable_mems = []
  elif exportable_mems and type(exportable_mems[0]) is types.ListType:
     exportable_mems = exportable_mems[0]

  redefined_funcs = cls.redefined_funcs()
  if redefined_funcs is None:
     redefined_funcs = []
  elif redefined_funcs and type(redefined_funcs[0]) is types.ListType:
     redefined_funcs = redefined_funcs[0]

  for member in exportable_mems + redefined_funcs:
    print "mb : ", member
    print "  ]: ", member.ignore
    if hasattr(member, "virtuality"):
       print "  }:", member.virtuality

  print "xxx ", cls.is_wrapper_needed()

#  print "FOOO ", exportable_mems
#  print "BAAR ", redefined_funcs

  cls = osg["FieldContainer"]
#  osggen.excludeMembers(cls, "createAspectCopy", True)
  cls["createAspectCopy"].ignore = True
  cls["createAspectCopy"].set_virtuality(pd.VIRTUALITY_TYPES.NOT_VIRTUAL)
  cls["createAspectCopy"].already_exposed = False

  exportable_mems = cls.get_exportable_members()

  if exportable_mems is None:
     exportable_mems = []
  elif exportable_mems and type(exportable_mems[0]) is types.ListType:
     exportable_mems = exportable_mems[0]

  redefined_funcs = cls.redefined_funcs()
  if redefined_funcs is None:
     redefined_funcs = []
  elif redefined_funcs and type(redefined_funcs[0]) is types.ListType:
     redefined_funcs = redefined_funcs[0]

  for member in exportable_mems + redefined_funcs:
    print "mb : ", member
    print "  ]: ", member.ignore
    if hasattr(member, "virtuality"):
       print "  }:", member.virtuality
