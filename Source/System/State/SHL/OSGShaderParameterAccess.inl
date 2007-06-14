/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

template<class ParameterType, class ValueType> inline
bool ShaderParameterAccess::setParameter(const Char8     *name, 
                                         const ValueType &value)
{
    typedef typename ParameterType::ObjPtr ParamPtr;

    if(name == NULL)
        return false;

    updateMap();

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        //ParameterType::Ptr p = 
        //    ParameterType::Ptr::dcast(_parameters[(*it).second]);

        ParamPtr p = dynamic_cast<ParamPtr>(
            _parameters.getParameters()[(*it).second]);

        if(p == NullFC)
        {
            FWARNING(("ShaderParameterAccess::setParameter : Parameter "
                      "'%s' has wrong type!\n", name));
            return false;
        }

        p->setValue(value);
    }
    else
    {
        //ParameterType::Ptr p = ParameterType::create();

        ParamPtr p = ParameterType::create();

        if(p != NullFC)
        {
            p->setName (name );
            p->setValue(value);

            _parameters.addParameter(p);

            _parametermap.insert(
                std::pair<std::string, 
                          UInt32>(name, 
                                  _parameters.getParameters().size() - 1));

            _mapsize = _parameters.getParameters().size();
        }
    }

    return true;
}

template<class ParameterType, class ValueType> inline
bool ShaderParameterAccess::setMParameter(const char      *name, 
                                          const ValueType &value)
{
    typedef typename ParameterType::ObjPtr ParamPtr;

    if(name == NULL)
        return false;

    updateMap();

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        //ParameterType::Ptr p = ParameterType::Ptr::dcast(_parameters[(*it).second]);
        ParamPtr p = dynamic_cast<ParamPtr>(
            _parameters.getParameters()[(*it).second]);

        if(p == NullFC)
        {
            FWARNING(("ShaderParameterAccess::setMParameter : Parameter '%s' "
                      "has wrong type!\n", name));

            return false;
        }

        p->editValue() = value;
    }
    else
    {
        //ParameterType::Ptr p = ParameterType::create();
        ParamPtr p = ParameterType::create();

        if(p != NullFC)
        {
            p->setName(name );

            p->editValue() = value;

            _parameters.addParameter(p);

            _parametermap.insert(
                std::pair<std::string, 
                          UInt32>(name, 
                                  _parameters.getParameters().size()-1));

            _mapsize = _parameters.getParameters().size();
        }
    }
    return true;
}

template<class ParameterType, class ValueType> inline
bool ShaderParameterAccess::getParameter(const Char8 *name, ValueType &value)
{
    typedef typename ParameterType::ObjPtr ParamPtr;

    if(name == NULL)
        return false;

    updateMap();

    parameterIt it = _parametermap.find(name);
    
    if(it != _parametermap.end())
    {
        ParamPtr p = dynamic_cast<ParamPtr>(
            _parameters.getParameters()[(*it).second]);

        if(p == NullFC)
        {
            FWARNING(("ShaderParameterAccess::getParameter : Parameter "
                      "'%s' has wrong type!\n", name));

            return false;
        }

        value = p->getValue();
    }
    else
    {
        FINFO(("ShaderParameterAccess::getParameter : Parameter '%s' "
               "doesn't exist!\n", name));

        return false;
    }

    return true;
}

OSG_END_NAMESPACE

#define OSGSHADERPARAMETERACCESS_INLINE_CVSID "@(#)$Id$"
