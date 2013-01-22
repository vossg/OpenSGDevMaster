
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

    setVaoGLId(               
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

    if(getVaoGLId() > 0)
        Window::destroyGLObject(getVaoGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*! OpenGL object handler. Used for DisplayList caching.
*/

UInt32 Geometry::handleClassicGL(DrawEnv                 *pEnv, 
                                 UInt32                   id, 
                                 Window::GLObjectStatusE  mode,
                                 UInt32                   uiOptions)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32                   glid;
    Window                  *pWin = pEnv->getWindow();

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

        GeoPumpGroup::PropertyCharacteristics prop = uiOptions;

        if(((prop & (GeoPumpGroup::SingleIndexed | 
                     GeoPumpGroup::NonIndexed    )) == 0x0000))
        {
            GeoPumpGroup::GeoPump pump = GeoPumpGroup::findGeoPump(pEnv, prop);

            glNewList(glid, GL_COMPILE);

            if(pump)
            {
                pump(pEnv,
                     getLengths(),      getTypes(),
                     getMFProperties(), getMFPropIndices());
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
                              getMFProperties(), getMFPropIndices());

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
            Int32 vaoGlid = getVaoGLId();

            pWin->validateGLObject(vaoGlid, pEnv, prop);
        
            UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid);

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
                                  getMFProperties(), getMFPropIndices());
                    
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
                             UInt32                   uiOptions)
{
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    UInt32   glid;
    Window  *pWin = pEnv->getWindow();

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

        GeoPumpGroup::PropertyCharacteristics prop = uiOptions;

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
                     getMFProperties(), getMFPropIndices());
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
                              getMFProperties(), getMFPropIndices());

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
            Int32 vaoGlid = getVaoGLId();

            pWin->validateGLObject(vaoGlid, pEnv, prop);
        
            UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid);

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
                                  getMFProperties(), getMFPropIndices());
                    
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
        SWARNING << "Geometry::handleAttDestroyGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
#endif
}

UInt32 Geometry::handleVAOGL(DrawEnv                 *pEnv, 
                             UInt32                   id, 
                             Window::GLObjectStatusE  mode,
                             UInt32                   uiOptions)
{
    UInt32   glid;
    Window  *pWin = pEnv->getWindow();

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

        GeoPumpGroup::PropertyCharacteristics prop = uiOptions;

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

            pWin->setGLObjectInfo(id, UInt32(rc));

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
    Window *pWin       = pEnv->getWindow();
    bool    usesShader = false;
    
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

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    // store glColor.
    Color4f color;

    if(getColors() != NULL)
        glGetFloatv(GL_CURRENT_COLOR, color.getValuesRGBA());
#endif

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

            pWin->validateGLObject(glid, pEnv, prop);
            
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
                     getMFProperties(), getMFPropIndices());
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
                    pWin->validateGLObject(glid, pEnv, prop);
                
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
                             getMFProperties(), getMFPropIndices());
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
                     getMFProperties(), getMFPropIndices());
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
        Int32 vaoGlid = getVaoGLId();
        
        pWin->validateGLObject(vaoGlid, pEnv, prop);
        
        UInt32 uiValidVAO = pWin->getGLObjectInfo(vaoGlid);

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

                    pWin->validateGLObject(glid, pEnv, prop);

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
                                  getMFPropIndices());

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
        if(getDlistCache())
        {
#if !defined(OSG_OGL_COREONLY)
            Window::refreshGLObject(getClassicGLId());
#endif
            Window::refreshGLObject(getAttGLId    ());
            Window::refreshGLObject(getVaoGLId    ());
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
