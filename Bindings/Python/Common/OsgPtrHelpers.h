// PyOpenSG is (C) Copyright 2005-2009 by Allen Bierbaum
//
// This file is part of PyOpenSG.
//
// PyOpenSG is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// PyOpenSG is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _OSG_PTR_HELPERS_H_
#define _OSG_PTR_HELPERS_H_

#include <iostream>
#include <typeinfo>
#include <boost/python.hpp>
//#include <boost/python/converter/shared_ptr_deleter.hpp>
#include <OSGConfig.h>
#include <OSGFieldContainer.h>
#include <OSGContainerRefCountPolicies.h>
#include <OSGNode.h>

// This bit is to deal with the cold, hard reality that X11 defines Bool as a
// preprocessor symbol. That symbol interferes with Boost.
#if defined(Bool)
#undef Bool
#endif

#ifndef NDEBUG
//#define DEBUG_PTR_HELPERS 1
#endif


namespace bp = boost::python;

/**
 * @name Meta Functions for Boost.Python.
 *
 * These routines help define the methods needed for registering and handling
 * the OpenSG smart pointer types.
 *
 * Our goal is to make everything be held by RecPtrs and to make it possible
 * to auto-convert to and from those RecPtrs as needed.
 *
 * \code
 * bp::register_ptr_to_python< OSG::Class >();
 * bp::implicitly_convertible< OSG::ClassRecPtr, OSG::Class >();
 * bp::implicitly_convertible< OSG::Class, OSG::Parent >();
 *
 * bp::def("RecPtr", &pyopensg::ToRecPtr<OSG::Class>);
 * bp::def("CPtr", &pyopensg::ToCPtr<OSG::Class>,
 *         bp::return_value_policy<bp::reference_existing_object>());
 * \endcode
 *
 * @see boost::python::register_ptr_to_python
 * @see boost::python::pointee
 *
 * We must register a pointee metafunction and a get_pointer helper function
 * for each smart pointer type we intend to use for storing and passing
 * object references.
 *
 * @note The converters get registered because we are using the RecPtr smart
 *       pointer type as the exposed type's held_type parameter.
 *
 * @see boost::python::to_python_converter
 */
//@{
namespace boost
{

namespace python
{

template<typename ObjectType>
struct pointee< OSG::RefCountPtr<ObjectType, OSG::MemObjRefCountPolicy> >
{
   typedef ObjectType type;
};

template<typename ObjectType>
struct pointee< OSG::RefCountPtr<ObjectType, OSG::RecordedRefCountPolicy> >
{
   typedef ObjectType type;
};

} // namespace python

} // namespace boost
//@}

/**
 * @name Smart Pointer Conversions
 *
 * Register conversion that takes an OpenSG transit pointer and converts it to
 * a recorded, reference counted pointer (such as
 * OSG::RefCountPtr<ObjectType, OSG::RecordedRefCountPolicy>) so that we can
 * actually use it.
 *
 * \code
 * bp::register_ptr_to_python<ptr_type>::execute();
 * \endcode
 *
 * @see boost::python::to_python_converter
 */
//@{
namespace pyopensg
{

/**
 * For a given OpenSG smart pointer type, create an object with the RecPtrType
 * type, and return that object.
 *
 * @see register_transit_to_python
 */
template<typename RecPtrType>
struct ptr_to_python
{
   typedef typename RecPtrType::Object object_type;
   typedef OSG::TransitPtr<object_type> transit_ptr_type;

   static PyObject* convert(const transit_ptr_type& transitObj)
   {
#ifdef DEBUG_PTR_HELPERS
      std::cout << "ptr_to_python: " << typeid(transit_ptr_type).name()
                << " for held object " << std::hex << transitObj.get()
                << std::dec << std::endl;
#endif
      return bp::incref(bp::object(RecPtrType(transitObj.get())).ptr());
   }
};

template<typename ObjectType, typename RecPtrType>
struct register_transit_to_python
{
   static void execute()
   {
      // Conversion from transit pointer to rec pointer.
      bp::to_python_converter<
         OSG::TransitPtr<ObjectType>, ptr_to_python<RecPtrType>
      >();
   }
};

/**
 * Template class to register from_python converter for OpenSG
 * reference-counted memory pointer types. This is needed at least for
 * conversion from None.
 *
 * Based on boost::python::converter::shared_ptr_from_python, found in
 * boost/python/converter/shared_ptr_from_python.hpp.
 */
template<typename PtrType>
struct ptr_from_python
{
   typedef typename PtrType::Object Pointee;   // The type we point to

   ptr_from_python()
   {
      bp::converter::registry::insert(&convertible, &construct,
                                      bp::type_id<PtrType>());
   }

private:

   static void* convertible(PyObject* p)
   {
      // Always produce a pointer from none
      if (Py_None == p)
      {
         return p;
      }
      else
      {
         return NULL;
      }

      /*
      // Otherwise, we can do it if we can get the pointer out
      // XXX: Not sure if all of this is right.
      void* result = bp::converter::get_lvalue_from_python(p,
                                             bp::converter::registered<Pointee>::converters);
      return result;
      */
   }

   static void construct(PyObject* source,
                         bp::converter::rvalue_from_python_stage1_data* data)
   {
      typedef bp::converter::rvalue_from_python_storage<PtrType> data_type;
      void* const storage = reinterpret_cast<data_type*>(data)->storage.bytes;

      // Deal with the "None" case.
      if (data->convertible == source)
      {
         new (storage) PtrType();
      }
      else
      {
         // Shouldn't ever happen.  We can't convert like this from OpenSG
         new (storage) PtrType(static_cast<Pointee*>(data->convertible));

         // XXX: Is this assertion valid? With OpenSG 2.0, it is possible to
         // wrap a raw pointer in a reference-counted smart pointer.
         //assert(
         //   false &&
         //   "Tried to convert a raw OpenSG pointer to a referencec-counted type."
         //);

         //new (storage) PtrType();
      }

      data->convertible = storage;
   }

};

/**
 * Helper for registering an OSG::TransitPtr<ObjectType> instantiation. This
 * is required to convert from the transit pointer that we receive from C++ to
 * the recorded, reference-counted pointer that will be exposed to Python.
 * RecPtrType is already known to Boost.Python as the held type for ObjectType.
 */
template<
     typename ObjectType
   , typename RecPtrType = typename ObjectType::ObjRecPtr
>
struct register_transit
{
   static void execute()
   {
#ifdef DEBUG_PTR_HELPERS
      std::cout << "register_transit: " << typeid(ObjectType).name()
                << std::endl;
#endif   

      // Register the conversion from OSG::TransitPtr<ObjectType> to
      // RecPtrType. We get OSG::TransitPtr<ObjectType> from C++ and want to
      // manage the held object as recorded, reference-counted memory held by
      // a Python object.
      register_transit_to_python<ObjectType, RecPtrType>::execute();

      // Register the conversion from PyObject* to RecPtrType.
      ptr_from_python<RecPtrType>();
   }
};
//@}

/**
 * @name Helper Functions
 *
 * Helper functions for going to/from raw C pointers and recorded pointers.
 */
//@{
/**
 * Helper for converting a raw pointer to a reference-counted smart
 * pointer type.
 */
template<typename ObjectType, typename RefCountPtrType>
RefCountPtrType ToRefCountPtr(typename ObjectType::ObjCPtr object)
{
   return RefCountPtrType(object);
}

/**
 * Helper for extracting the raw pointer from a a reference-counted smart
 * pointer object.
 */
template<typename RefCountPtrType>
typename RefCountPtrType::Object* ToCPtr(const RefCountPtrType& object)
{
   return object.get();
}
//@}

}


#endif /* _OSG_PTR_HELPERS_H_ */
