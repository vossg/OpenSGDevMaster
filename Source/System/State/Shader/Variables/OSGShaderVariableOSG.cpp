/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGShaderVariableOSG.h"
#include "OSGGLFuncProtos.h"
#include "OSGShaderProgram.h"

#include "OSGDrawEnv.h"
#include "OSGWindow.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGShaderVariableOSGBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderVariableOSG.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderVariableOSG::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderVariableOSG::ShaderVariableOSG(void) :
    Inherited()
{
    setTypeId(ShaderVariable::SHVTypeOSG);
}

ShaderVariableOSG::ShaderVariableOSG(const ShaderVariableOSG &source) :
    Inherited(source)
{
}

ShaderVariableOSG::~ShaderVariableOSG(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderVariableOSG::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & NameFieldMask))
    {
        if(_sfName.getValue() == "OSGWorldMatrix")
        {
            setOsgVarType(OSGWorldMatrix);
            setDependency(SHDObject     );
        }
        else if(_sfName.getValue() == "OSGInvWorldMatrix")
        {
            setOsgVarType(OSGInvWorldMatrix);
            setDependency(SHDObject        );
        }
        else if(_sfName.getValue() == "OSGTransInvWorldMatrix")
        {
            setOsgVarType(OSGTransInvWorldMatrix);
            setDependency(SHDObject             );
        }
        else if(_sfName.getValue() == "OSGCameraOrientation")
        {
            setOsgVarType(OSGCameraOrientation);
            setDependency(SHDScene            );
        }
        else if(_sfName.getValue() == "OSGCameraPosition")
        {
            setOsgVarType(OSGCameraPosition);
            setDependency(SHDScene         );
        }
        else if(_sfName.getValue() == "OSGViewMatrix")
        {
            setOsgVarType(OSGViewMatrix);
            setDependency(SHDScene     );
        }
        else if(_sfName.getValue() == "OSGInvViewMatrix")
        {
            setOsgVarType(OSGInvViewMatrix);
            setDependency(SHDScene        );
        }
        else if(_sfName.getValue() == "OSGProjectionMatrix")
        {
            setOsgVarType(OSGProjectionMatrix);
            setDependency(SHDScene           );
        }
        else if(_sfName.getValue() == "OSGModelViewMatrix")
        {
            setOsgVarType(OSGModelViewMatrix);
            setDependency(SHDObject          );
        }
#ifdef OSG_OGL_COREONLY
        else if(_sfName.getValue() == "OSGNormalMatrix")
        {
            setOsgVarType(OSGNormalMatrix);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGModelViewProjectionMatrix")
        {
            setOsgVarType(OSGModelViewProjectionMatrix);
            setDependency(SHDObject                   );
        }
#endif
        else if(_sfName.getValue() == "OSGStereoLeftEye")
        {
            setOsgVarType(OSGStereoLeftEye);
            setDependency(SHDScene        );
        }
        else if(_sfName.getValue() == "OSGDrawerId")
        {
            setOsgVarType(OSGDrawerId);
            setDependency(SHDScene    );
        }
        else if(_sfName.getValue() == "OSGDrawableId")
        {
            setOsgVarType(OSGDrawableId);
            setDependency(SHDScene     );
        }
        else if(_sfName.getValue() == "OSGNodeId")
        {
            setOsgVarType(OSGNodeId);
            setDependency(SHDObject);
        }
        else if(_sfName.getValue() == "OSGNodeBoxMin")
        {
            setOsgVarType(OSGNodeBoxMin);
            setDependency(SHDObject    );
        }
        else if(_sfName.getValue() == "OSGNodeBoxMax")
        {
            setOsgVarType(OSGNodeBoxMax);
            setDependency(SHDObject    );
        }
        else if(_sfName.getValue() == "OSGNodeBoxCenter")
        {
            setOsgVarType(OSGNodeBoxCenter);
            setDependency(SHDObject       );
        }
        else if(_sfName.getValue() == "OSGNodeWorldBoxMin")
        {
            setOsgVarType(OSGNodeWorldBoxMin);
            setDependency(SHDObject         );
        }
        else if(_sfName.getValue() == "OSGNodeWorldBoxMax")
        {
            setOsgVarType(OSGNodeWorldBoxMax);
            setDependency(SHDObject         );
        }
        else if(_sfName.getValue() == "OSGNodeWorldBoxCenter")
        {
            setOsgVarType(OSGNodeWorldBoxCenter);
            setDependency(SHDObject            );
        }
        else if(_sfName.getValue() == "OSGActiveLightsMask")
        {
            setOsgVarType(OSGActiveLightsMask);
            setDependency(SHDObject          );
        }
        else if(_sfName.getValue() == "OSGLight0Active")
        {
            setOsgVarType(OSGLight0Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight1Active")
        {
            setOsgVarType(OSGLight1Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight2Active")
        {
            setOsgVarType(OSGLight2Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight3Active")
        {
            setOsgVarType(OSGLight3Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight4Active")
        {
            setOsgVarType(OSGLight4Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight5Active")
        {
            setOsgVarType(OSGLight5Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight6Active")
        {
            setOsgVarType(OSGLight6Active);
            setDependency(SHDObject      );
        }
        else if(_sfName.getValue() == "OSGLight7Active")
        {
            setOsgVarType(OSGLight7Active);
            setDependency(SHDObject      );
        }
        else
        {
            setOsgVarType(OSGUnknown);
            setDependency(SHDObject );
        }
    }
}

void ShaderVariableOSG::dump(      UInt32    , 
                             const BitVector ) const
{
    SLOG << "Dump ShaderVariableOSG NI" << std::endl;
}

bool ShaderVariableOSG::isProcedural(void) const
{
    return true;
}

void ShaderVariableOSG::setName(const std::string &value)
{
    Inherited::setName(value);

    if(_sfName.getValue() == "OSGWorldMatrix")
    {
        setOsgVarType(OSGWorldMatrix);
        setDependency(SHDObject     );
    }
    else if(_sfName.getValue() == "OSGInvWorldMatrix")
    {
        setOsgVarType(OSGInvWorldMatrix);
        setDependency(SHDObject        );
    }
    else if(_sfName.getValue() == "OSGTransInvWorldMatrix")
    {
        setOsgVarType(OSGTransInvWorldMatrix);
        setDependency(SHDObject             );
    }
    else if(_sfName.getValue() == "OSGCameraOrientation")
    {
        setOsgVarType(OSGCameraOrientation);
        setDependency(SHDScene            );
    }
    else if(_sfName.getValue() == "OSGCameraPosition")
    {
        setOsgVarType(OSGCameraPosition);
        setDependency(SHDScene         );
    }
    else if(_sfName.getValue() == "OSGViewMatrix")
    {
        setOsgVarType(OSGViewMatrix);
        setDependency(SHDScene     );
    }
    else if(_sfName.getValue() == "OSGInvViewMatrix")
    {
        setOsgVarType(OSGInvViewMatrix);
        setDependency(SHDScene        );
    }
    else if(_sfName.getValue() == "OSGProjectionMatrix")
    {
        setOsgVarType(OSGProjectionMatrix);
        setDependency(SHDScene           );
    }
    else if(_sfName.getValue() == "OSGModelViewMatrix")
    {
        setOsgVarType(OSGModelViewMatrix);
        setDependency(SHDObject         );
    }
#ifdef OSG_OGL_COREONLY
    else if(_sfName.getValue() == "OSGNormalMatrix")
    {
        setOsgVarType(OSGNormalMatrix);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGModelViewProjectionMatrix")
    {
        setOsgVarType(OSGModelViewProjectionMatrix);
        setDependency(SHDObject                   );
    }
#endif
    else if(_sfName.getValue() == "OSGStereoLeftEye")
    {
        setOsgVarType(OSGStereoLeftEye);
        setDependency(SHDScene        );
    }
    else if(_sfName.getValue() == "OSGDrawerId")
    {
        setOsgVarType(OSGDrawerId);
        setDependency(SHDScene   );
    }
    else if(_sfName.getValue() == "OSGDrawableId")
    {
        setOsgVarType(OSGDrawableId);
        setDependency(SHDScene     );
    }
    else if(_sfName.getValue() == "OSGNodeId")
    {
        setOsgVarType(OSGNodeId);
        setDependency(SHDObject);
    }
    else if(_sfName.getValue() == "OSGNodeBoxMin")
    {
        setOsgVarType(OSGNodeBoxMin);
        setDependency(SHDObject    );
    }
    else if(_sfName.getValue() == "OSGNodeBoxMax")
    {
        setOsgVarType(OSGNodeBoxMax);
        setDependency(SHDObject    );
    }
    else if(_sfName.getValue() == "OSGNodeBoxCenter")
    {
        setOsgVarType(OSGNodeBoxCenter);
        setDependency(SHDObject       );
    }
    else if(_sfName.getValue() == "OSGNodeWorldBoxMin")
    {
        setOsgVarType(OSGNodeWorldBoxMin);
        setDependency(SHDObject         );
    }
    else if(_sfName.getValue() == "OSGNodeWorldBoxMax")
    {
        setOsgVarType(OSGNodeWorldBoxMax);
        setDependency(SHDObject         );
    }
    else if(_sfName.getValue() == "OSGNodeWorldBoxCenter")
    {
        setOsgVarType(OSGNodeWorldBoxCenter);
        setDependency(SHDObject            );
    }
    else if(_sfName.getValue() == "OSGActiveLightsMask")
    {
        setOsgVarType(OSGActiveLightsMask);
        setDependency(SHDObject          );
    }
    else if(_sfName.getValue() == "OSGLight0Active")
    {
        setOsgVarType(OSGLight0Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight1Active")
    {
        setOsgVarType(OSGLight1Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight2Active")
    {
        setOsgVarType(OSGLight2Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight3Active")
    {
        setOsgVarType(OSGLight3Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight4Active")
    {
        setOsgVarType(OSGLight4Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight5Active")
    {
        setOsgVarType(OSGLight5Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight6Active")
    {
        setOsgVarType(OSGLight6Active);
        setDependency(SHDObject      );
    }
    else if(_sfName.getValue() == "OSGLight7Active")
    {
        setOsgVarType(OSGLight7Active);
        setDependency(SHDObject      );
    }
    else
    {
        setOsgVarType(OSGUnknown);
        setDependency(SHDObject );
    }
}

void ShaderVariableOSG::evaluate(DrawEnv *pEnv,
                                 Int32   &iLocation)
{
    switch(_sfOsgVarType.getValue())
    {
        case OSGWorldMatrix:
        {
            Matrix m = pEnv->getObjectToWorld();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());
                
                osgGlUniformMatrix4fv(iLocation, 
                                      1, 
                                      GL_FALSE, 
                                      m.getValues());
            }
        }
        break;

        case OSGInvWorldMatrix:
        {
            Matrix m = pEnv->getObjectToWorld();

            m.invert();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGTransInvWorldMatrix:
        {
            Matrix m = pEnv->getObjectToWorld();
            
            m.invert();
            m.transpose();


            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGCameraOrientation:
        {
            Matrix m = pEnv->getCameraToWorld();
            
            m[3].setValues(0, 0, 0, 1);

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGCameraPosition:
        {
            if(iLocation != -1)
            {
                Matrix m = pEnv->getCameraToWorld();

                Vec3f cameraPos(m[3][0], m[3][1], m[3][2]);

                OSGGETGLFUNC(OSGglUniform3fvProc,
                             osgGlUniform3fv,
                             ShaderProgram::getFuncIdUniform3fv());

                osgGlUniform3fv(iLocation, 1, cameraPos.getValues());
            }
        }
        break;

        case OSGViewMatrix:
        {
            Matrix m = pEnv->getCameraViewing();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGInvViewMatrix:
        {
            Matrix m = pEnv->getCameraToWorld();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGProjectionMatrix:
        {
            Matrix m = pEnv->_openGLState.getProjection();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGModelViewMatrix:
        {
            Matrix m = pEnv->_openGLState.getModelView();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

#ifdef OSG_OGL_COREONLY
        case OSGNormalMatrix:
        {
            Matrix m = pEnv->_openGLState.getNormalMatrix();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;

        case OSGModelViewProjectionMatrix:
        {
            Matrix m = pEnv->_openGLState.getModelViewProjection();

            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniformMatrix4fvProc,
                             osgGlUniformMatrix4fv,
                             ShaderProgram::getFuncIdUniformMatrix4fv());

                osgGlUniformMatrix4fv(iLocation, 1, GL_FALSE, m.getValues());
            }
        }
        break;
#endif

        case OSGStereoLeftEye:
        {
        }
        break;

        case OSGDrawerId:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getDrawerId()));
            }
        }
        break;

        case OSGDrawableId:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getDrawableId()));
            }
       }
        break;

        case OSGNodeId:
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform1iProc,
                                 osgGlUniform1i,
                                 ShaderProgram::getFuncIdUniform1i());

                    osgGlUniform1i(iLocation, 
                                   GLint(pEnv->getSGNode()->getId()));
                }
            }
        }
        break;

        case OSGNodeBoxMin:
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform3fProc,
                                 osgGlUniform3f,
                                 ShaderProgram::getFuncIdUniform3f());

                    const BoxVolume &bvBox = pEnv->getSGNode()->getVolume();

                    osgGlUniform3f(iLocation, 
                                   bvBox.getMin()[0],
                                   bvBox.getMin()[1],
                                   bvBox.getMin()[2]);
                }
            }
        }
        break;

        case OSGNodeBoxMax :
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform3fProc,
                                 osgGlUniform3f,
                                 ShaderProgram::getFuncIdUniform3f());

                    const BoxVolume &bvBox = pEnv->getSGNode()->getVolume();

                    osgGlUniform3f(iLocation, 
                                   bvBox.getMax()[0],
                                   bvBox.getMax()[1],
                                   bvBox.getMax()[2]);
                }
            }
        }
        break;

        case OSGNodeBoxCenter:
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform3fProc,
                                 osgGlUniform3f,
                                 ShaderProgram::getFuncIdUniform3f());

                    Pnt3f vBoxCenter;

                    pEnv->getSGNode()->getVolume().getCenter(vBoxCenter);

                    osgGlUniform3f(iLocation, 
                                   vBoxCenter[0],
                                   vBoxCenter[1],
                                   vBoxCenter[2]);
                }
            }
        }
        break;


        case OSGNodeWorldBoxMin:
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform3fProc,
                                 osgGlUniform3f,
                                 ShaderProgram::getFuncIdUniform3f());

                    BoxVolume bvWorldBox;

                    pEnv->getSGNode()->getWorldVolume(bvWorldBox);

                    osgGlUniform3f(iLocation, 
                                   bvWorldBox.getMin()[0],
                                   bvWorldBox.getMin()[1],
                                   bvWorldBox.getMin()[2]);
                }
            }
        }
        break;

        case OSGNodeWorldBoxMax :
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform3fProc,
                                 osgGlUniform3f,
                                 ShaderProgram::getFuncIdUniform3f());

                    BoxVolume bvWorldBox;

                    pEnv->getSGNode()->getWorldVolume(bvWorldBox);

                    osgGlUniform3f(iLocation, 
                                   bvWorldBox.getMax()[0],
                                   bvWorldBox.getMax()[1],
                                   bvWorldBox.getMax()[2]);
                }
            }
        }
        break;

        case OSGNodeWorldBoxCenter:
        {
            if(iLocation != -1)
            {
                if(pEnv->getSGNode() != NULL)
                {
                    OSGGETGLFUNC(OSGglUniform3fProc,
                                 osgGlUniform3f,
                                 ShaderProgram::getFuncIdUniform3f());

                    BoxVolume bvWorldBox;
                    Pnt3f     vWorldBoxCenter;

                    pEnv->getSGNode()->getWorldVolume(bvWorldBox);

                    bvWorldBox.getCenter(vWorldBoxCenter);

                    osgGlUniform3f(iLocation, 
                                   vWorldBoxCenter[0],
                                   vWorldBoxCenter[1],
                                   vWorldBoxCenter[2]);
                }
            }
        }
        break;

        case OSGActiveLightsMask:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState()));
            }
        }
        break;

        case OSGLight0Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0001));
            }
        }
        break;

        case OSGLight1Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0002));
            }
        }
        break;

        case OSGLight2Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0004));
            }
        }
        break;

        case OSGLight3Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0008));
            }
        }
        break;

        case OSGLight4Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0010));
            }
        }
        break;

        case OSGLight5Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0020));
            }
        }
        break;

        case OSGLight6Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0040));
            }
        }
        break;

        case OSGLight7Active:
        {
            if(iLocation != -1)
            {
                OSGGETGLFUNC(OSGglUniform1iProc,
                             osgGlUniform1i,
                             ShaderProgram::getFuncIdUniform1i());

                osgGlUniform1i(iLocation, 
                               GLint(pEnv->getLightState() & 0x0080));
            }
        }
        break;

        default:
        {
        }
        break;
    }
}
