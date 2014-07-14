
void Geometry::onCreate(const Geometry *source)
{
    Inherited::onCreate(source);

    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

#if !defined(OSG_OGL_COREONLY)
    setClassicGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleClassicGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleClassicDestroyGL));
#endif

    setAttGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleAttGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleAttDestroyGL));

    setClassicVaoGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleVAOGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleVAODestroyGL));
    setAttribVaoGLId(               
        Window::registerGLObject(
            boost::bind(&Geometry::handleVAOGL,
                        GeometryMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &Geometry::handleVAODestroyGL));
}

void Geometry::onDestroy(UInt32 uiContainerId)
{
#if !defined(OSG_OGL_COREONLY)
    if(getClassicGLId() > 0)
        Window::destroyGLObject(getClassicGLId(), 1);
#endif

    if(getAttGLId() > 0)
        Window::destroyGLObject(getAttGLId(), 1);

    if(getClassicVaoGLId() > 0)
        Window::destroyGLObject(getClassicVaoGLId(), 1);

    if(getAttribVaoGLId() > 0)
        Window::destroyGLObject(getAttribVaoGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*! OpenGL object handler. Used for DisplayList caching.
*/

UInt32 Geometry::handleClassicGL(DrawEnv                 *pEnv, 
                                 UInt32                   id, 
                                 Window::GLObjectStatusE  mode,
                                 UInt64                   uiOptions)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32                   glid;
    Window                  *pWin      = pEnv->getWindow();
    GLHandlerOptions         glOptions = { uiOptions };

#ifdef OSG_DEBUG
    Geometry *pAspectGeo = Aspect::convertToCurrent<Geometry *>(this);
    OSG_ASSERT(pAspectGeo == this);
#endif

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        GeoPumpGroup::PropertyCharacteristics prop = glOptions.uiOptions;

        if(((prop & (GeoPumpGroup::SingleIndexed | 
                     GeoPumpGroup::NonIndexed    )) == 0x0000))
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, prop);

            glNewList(glid, GL_COMPILE);

            if(pump)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     glOptions.uiNumInstances             );
            }
            else
            {
                SWARNING << "Geometry::handleClassicGL: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }

            glEndList();
        }
        else if(_sfUseVAO.getValue() == false)
        {
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv,
                                               prop);

            if(pump.drawPump != NULL)
            {
                glNewList(glid, GL_COMPILE);

                pump.drawPump(pEnv,
                              getLengths(),      getTypes(),
                              getMFProperties(), getMFPropIndices(),
                              glOptions.uiNumInstances             );

                glEndList();
            }
            else
            {
                SWARNING << "Geometry::handleClassicGL: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
        else
        {
            Int32 vaoGlid = 
                (glOptions.value & 
                 GeoPumpGroup::UsesShader) ? getAttribVaoGLId () : 
                                             getClassicVaoGLId();

            pWin->validateGLObject(vaoGlid, pEnv, glOptions.value);
        
            UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid) & ValidVAO;

            if(uiValidVAO != 0)
            {
                GeoPumpGroup::SplitGeoPump pump = 
                    GeoPumpGroup::findSplitGeoPump(pEnv,
                                                   prop);

                if(pump.drawPump != NULL)
                {
                    OSGGETGLFUNCBYID_GL3(glBindVertexArray,
                                         osgGlBindVertexArray,
                                         FuncIdBindVertexArray,
                                         pWin);
                    
                    osgGlBindVertexArray(pWin->getGLObjectId(vaoGlid));
                    
                    glNewList(glid, GL_COMPILE);

                    pump.drawPump(pEnv,
                                  getLengths(),      getTypes(),
                                  getMFProperties(), getMFPropIndices(),
                                  glOptions.uiNumInstances             );
                    
                    glEndList();

                    osgGlBindVertexArray(0);
                }
                else
                {
                    SWARNING << "Geometry::drawPrimitives: no Pump found for "
                             << "geometry "
                             << this
                             << std::endl;
                }
            }
        }
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleClassicGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif

    return 0;
}

void Geometry::handleClassicDestroyGL(DrawEnv                 *pEnv, 
                                      UInt32                   id, 
                                      Window::GLObjectStatusE  mode)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry::handleClassicDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

UInt32 Geometry::handleAttGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt64                   uiOptions)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32            glid;
    Window           *pWin = pEnv->getWindow();
    GLHandlerOptions  glOptions = { uiOptions };

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            glid = glGenLists(1);
            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        GeoPumpGroup::PropertyCharacteristics prop = glOptions.uiOptions;

        if(((prop & (GeoPumpGroup::SingleIndexed | 
                     GeoPumpGroup::NonIndexed    )) == 0x0000))
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, 
                                                                   prop);
            glNewList(glid, GL_COMPILE);

            if(pump != NULL)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     glOptions.uiNumInstances             );
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }

            glEndList();
        }
        else if(_sfUseVAO.getValue() == false)
        {
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv, 
                                               prop);

            if(pump.drawPump != NULL)
            {
                glNewList(glid, GL_COMPILE);

                pump.drawPump(pEnv,
                              getLengths(),      getTypes(),
                              getMFProperties(), getMFPropIndices(),
                              glOptions.uiNumInstances             );

                glEndList();
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
        else
        {
            Int32 vaoGlid = 
                (glOptions.value & 
                 GeoPumpGroup::UsesShader) ? getAttribVaoGLId () : 
                                             getClassicVaoGLId();

            pWin->validateGLObject(vaoGlid, pEnv, glOptions.value);
        
            UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid) & ValidVAO;

            if(uiValidVAO != 0)
            {
                GeoPumpGroup::SplitGeoPump pump = 
                    GeoPumpGroup::findSplitGeoPump(pEnv,
                                                   prop);

                if(pump.drawPump != NULL)
                {
                    OSGGETGLFUNCBYID_GL3(glBindVertexArray,
                                         osgGlBindVertexArray,
                                         FuncIdBindVertexArray,
                                         pWin);
                    
                    osgGlBindVertexArray(pWin->getGLObjectId(vaoGlid));
                    
                    glNewList(glid, GL_COMPILE);

                    pump.drawPump(pEnv,
                                  getLengths(),      getTypes(),
                                  getMFProperties(), getMFPropIndices(),
                                  glOptions.uiNumInstances             );
                    
                    glEndList();

                    osgGlBindVertexArray(0);
                }
                else
                {
                    SWARNING << "Geometry::drawPrimitives: no Pump found for "
                             << "geometry "
                             << this
                             << std::endl;
                }
            }
        }
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleAttGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif

    return 0;
}

void Geometry::handleAttDestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32            glid;
    Window           *pWin      = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        glid = pWin->getGLObjectId(id);

        glDeleteLists(glid, 1);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry::handleAttDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

UInt32 Geometry::handleVAOGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt64                   uiOptions)
{
    UInt32            glid;
    Window           *pWin      = pEnv->getWindow();
    GLHandlerOptions  glOptions = { uiOptions };

    if(mode == Window::initialize || mode == Window::needrefresh ||
       mode == Window::reinitialize)
    {
        if(mode == Window::initialize)
        {
            OSGGETGLFUNCBYID_GL3_ES(glGenVertexArrays,
                                    osgGlGenVertexArrays,
                                    FuncIdGenVertexArrays,
                                    pWin);

            osgGlGenVertexArrays(1, &glid);

            pWin->setGLObjectId(id, glid);
        }
        else
        {
            glid = pWin->getGLObjectId(id);
        }

        GeoPumpGroup::PropertyCharacteristics prop = glOptions.uiOptions;

        GeoPumpGroup::SplitGeoPump pump = GeoPumpGroup::findSplitGeoPump(pEnv, 
                                                                         prop);
        if(pump.setupPump != NULL)
        {
            OSGGETGLFUNCBYID_GL3_ES(glBindVertexArray,
                                    osgGlBindVertexArray,
                                    FuncIdBindVertexArray,
                                    pWin);

            osgGlBindVertexArray(glid);

            bool rc = pump.setupPump(pEnv,
                                     getLengths(),      getTypes(),
                                     getMFProperties(), getMFPropIndices());

            UInt32 uiObjInfo = rc ? ValidVAO : 0x00;
            
            uiObjInfo |= (prop & GeoPumpGroup::UsesShader);

            pWin->setGLObjectInfo(id, uiObjInfo);

            osgGlBindVertexArray(0);
        }
        else
        {
            SWARNING << "Geometry::handleAttGL: no Pump found for geometry "
                     << this
                     << std::endl;
        }
    }
    else
    {
        SWARNING << "Geometry(" << this << "::handleAttGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }

    return 0;
}

void Geometry::handleVAODestroyGL(DrawEnv                 *pEnv, 
                                  UInt32                   id, 
                                  Window::GLObjectStatusE  mode)
{
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        OSGGETGLFUNCBYID_GL3_ES(glDeleteVertexArrays,
                                osgGlDeleteVertexArrays,
                                FuncIdDeleteVertexArrays,
                                pWin);

        glid = pWin->getGLObjectId(id);

        osgGlDeleteVertexArrays(1, &glid);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last geometry user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "Geometry::handleAttDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
}

void Geometry::drawPrimitives(DrawEnv *pEnv)
{
    this->drawPrimitives(pEnv, 1);
}

void Geometry::drawPrimitives(DrawEnv *pEnv, UInt32 uiNumInstances)
{
    Window *pWin       = pEnv->getWindow();
    bool    usesShader = false;

    if(!pWin->hasExtOrVersion(_arbDrawInstanced, 0x0300, 0x0200))
    {
        uiNumInstances = 1;
    }

    // Quick solution must be cleaned up.
    if(_sfUseAttribCalls.getValue() == true)
    {
        usesShader = true;
    }
#ifdef OSG_OGL_VERTEXATTRIB_FUNCS
    else
    {
        if(pEnv->getActiveShader() != 0)
        {
            if((pEnv->getRequiredOGLFeature() & 
                HardwareContext::HasAttribAliasing) == 0x0000)
            {
                usesShader = true;
            }
            else
            {
                usesShader = (pEnv->getWindow()->getOGLFeatures() &
                              HardwareContext::HasAttribAliasing   ) != 0x0000;
            }
        }
    }
#endif

    GeoPumpGroup::PropertyCharacteristics prop;

    prop = GeoPumpGroup::characterizeGeometry(this);

    if(usesShader)
        prop |= GeoPumpGroup::UsesShader;

    GLHandlerOptions glOptions;

    glOptions.uiOptions      = prop;
    glOptions.uiNumInstances = uiNumInstances;

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // store glColor.
    Color4f color;

    if(getColors() != NULL)
        glGetFloatv(GL_CURRENT_COLOR, color.getValuesRGBA());
#endif

    if(_sfPatchVertices.getValue() != 0)
    {
        OSGGETGLFUNCBYID_GL3(glPatchParameteri,
                             osgGlPatchParameteri,
                             Geometry::FuncPatchParameterI,
                             pWin                         );

        osgGlPatchParameteri(GL_PATCH_VERTICES, _sfPatchVertices.getValue());
    }

    if(((prop & (GeoPumpGroup::SingleIndexed | 
                 GeoPumpGroup::NonIndexed    )) == 0x0000))
    {
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
        if(getDlistCache() == true)
        {
            Int32 glid;

            if(usesShader)
            {
                glid = getAttGLId();
            }
            else
            {
                glid = getClassicGLId();
            }

            pWin->validateGLObject(glid, pEnv, glOptions.value);
            
            glCallList(pEnv->getWindow()->getGLObjectId(glid));
        }
        else
#endif
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, 
                                                                   prop);
            if(pump != NULL)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     uiNumInstances                       );
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
    }
    else if(_sfUseVAO.getValue() == false)
    {
#if (!defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)) &&  \
    !defined(__APPLE__)
        if(getDlistCache() == true && uiNumInstances == 1)
        {
            Int32 glid;

            if(usesShader)
            {
                glid = getAttGLId();
            }
            else
            {
                glid = getClassicGLId();
            }
            
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv,
                                               prop);

            if(pump.setupPump != NULL)
            {
                bool rc = pump.setupPump(pEnv,
                                         getLengths(),      
                                         getTypes(),
                                         getMFProperties(), 
                                         getMFPropIndices());
                
                if(rc == true)
                {
                    pWin->validateGLObject(glid, pEnv, glOptions.value);
                
                    glCallList(pEnv->getWindow()->getGLObjectId(glid));
                
                    pump.shutdownPump(pEnv,
                                      getLengths(),      
                                      getTypes(),
                                      getMFProperties(), 
                                      getMFPropIndices());
                }
                else // fallback 
                {
                    GeoPumpGroup::GeoPump pump = 
                        GeoPumpGroup::findGeoPump(pEnv, 
                                                  prop);
                    if(pump != NULL)
                    {
                        pump(pEnv,
                             getLengths(),      getTypes(),
                             getMFProperties(), getMFPropIndices(),
                             uiNumInstances                       );
                    }
                }
            }
        }
        else
#endif
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, 
                                                                   prop);
            if(pump != NULL)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices(),
                     uiNumInstances                       );
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found for "
                         << "geometry "
                         << this
                         << std::endl;
            }
        }
    }
    else
    {
        Int32 vaoGlid = 
                (glOptions.value & 
                 GeoPumpGroup::UsesShader) ? getAttribVaoGLId () : 
                                             getClassicVaoGLId();
        
        pWin->validateGLObject(vaoGlid, pEnv, glOptions.value);
        
        UInt32 uiVAOInfo = pWin->getGLObjectInfo(vaoGlid);

#ifdef OSG_DEBUG
        if((prop      & GeoPumpGroup::UsesShader) != 
           (uiVAOInfo & GeoPumpGroup::UsesShader)   )
        {
            fprintf(stderr, "vao shader settings not equal : %04x | %04x\n",
                    (prop      & GeoPumpGroup::UsesShader),
                    (uiVAOInfo & GeoPumpGroup::UsesShader));
        }
#endif

        if((uiVAOInfo & ValidVAO) != 0)
        {
            GeoPumpGroup::SplitGeoPump pump = 
                GeoPumpGroup::findSplitGeoPump(pEnv,
                                               prop);

            if(pump.drawPump != NULL)
            {
                OSGGETGLFUNCBYID_GL3(glBindVertexArray,
                                     osgGlBindVertexArray,
                                     FuncIdBindVertexArray,
                                     pWin);

#if (!defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)) && \
    !defined(__APPLE__)
                if(getDlistCache() == true && uiNumInstances == 1 &&
                   pWin->hasVAODListProblems() == false)
                {
                    Int32 glid;
                    
                    if(usesShader)
                    {
                        glid = getAttGLId();
                    }
                    else
                    {
                        glid = getClassicGLId();
                    }

                    pWin->validateGLObject(glid, pEnv, glOptions.value);

                    osgGlBindVertexArray(
                        pEnv->getWindow()->getGLObjectId(vaoGlid));

                    glCallList(pEnv->getWindow()->getGLObjectId(glid));

                    osgGlBindVertexArray(0);
                }
                else
#endif
                {
                    osgGlBindVertexArray(
                        pEnv->getWindow()->getGLObjectId(vaoGlid));

                    pump.drawPump(pEnv,
                                  getLengths(),      
                                  getTypes(),
                                  getMFProperties(), 
                                  getMFPropIndices(),
                                  uiNumInstances    );

                    osgGlBindVertexArray(0);
                }
            }
            else
            {
                SWARNING << "Geometry::drawPrimitives: no Pump found "
                         << "for geometry "
                         << this
                         << std::endl;
            }
        }
    }


#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // restore glColor.
    if(getColors() != NULL)
        glColor4fv(color.getValuesRGBA());
#endif
}

void Geometry::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
#if !defined(OSG_OGL_COREONLY)
    // Handle change to the display list cache field.
    if(whichField & DlistCacheFieldMask)
    {
        if(getDlistCache())
        {
            // Ensure that we have OpenGL objects for display list.
            if(getClassicGLId() == 0)
            {
                setClassicGLId(               
                    Window::registerGLObject(
                        boost::bind(&Geometry::handleClassicGL, 
                                    GeometryMTUncountedPtr(this), 
                                    _1, _2, _3, _4),
                        &Geometry::handleClassicDestroyGL));
            }
            if(getAttGLId() == 0)
            {
                setAttGLId(               
                    Window::registerGLObject(
                        boost::bind(&Geometry::handleAttGL, 
                                    GeometryMTUncountedPtr(this), 
                                    _1, _2, _3, _4),
                        &Geometry::handleAttDestroyGL));
            }
        }
        else
        {
            // Delete old display list objects.
            if(getClassicGLId() != 0)
            {
                Window::destroyGLObject(getClassicGLId(), 1);

                setClassicGLId(0);
            }
            if(getAttGLId() != 0)
            {
                Window::destroyGLObject(getAttGLId(), 1);

                setAttGLId(0);
            }
        }
    }
#endif

    // If something changed inside the geometry fields and we are using
    // display lists, refresh them.
    if(whichField & (TypesFieldMask | LengthsFieldMask |
                     PropertiesFieldMask | PropIndicesFieldMask))
    {
        if(this->getDlistCache() == true)
        {
#if !defined(OSG_OGL_COREONLY)
            Window::refreshGLObject(getClassicGLId());
#endif
            Window::refreshGLObject(getAttGLId    ());
        }

        if(this->getUseVAO() == true)
        {
            Window::refreshGLObject(getClassicVaoGLId());
            Window::refreshGLObject(getAttribVaoGLId ());
        }
    }

    if(whichField & PropertiesFieldMask)
    {
        for(UInt32 i = 0; i < _mfParents.size(); i++)
        {
            _mfParents[i]->invalidateVolume();
        }

        _volumeCache.setValid();
        _volumeCache.setEmpty();
    }

    Inherited::changed(whichField, origin, details);
}
