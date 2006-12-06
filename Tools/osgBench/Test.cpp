/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGGeoIgnorePumpGroup.h>

#include "Test.h"

Test::Test(void) :
    _win(NULL), _scene(OSG::NullFC), _near(0), _far(0),
    _froms(), _oris(), _fovs(), 
    _minTime(-1), _nFrames(0), _headlight(true),
    _statsLevel(0), _time(0), _nRenderedFrames(0), _stats(),
    _verbose(false), _useRenderTraversal(false)
{
}

Test::~Test()
{
}

// Set up scene characteristics

void Test::setScene(NodeBase &scene)
{
    _scene = scene.getNode();
}

void Test::setScene(OSG::NodePtr scene)
{
    _scene = scene;
}

void Test::setWindow(TestWindow &win)
{
    _win = &win;
}

void Test::setHeadlight(bool on)
{
    _headlight = on;
}
     
void Test::setNearFar(OSG::Real32 n, OSG::Real32 f)
{
    _near = n;
    _far = f;
}

// Setup Test Frames

// clear all the data
void Test::clear(void)
{
    _froms.clear();
    _oris.clear();
    _fovs.clear();
}

// MinTime takes precedence, the path is repeated fully until the time is
// reached

void Test::setNFrames(OSG::UInt32 nframes)
{
    _nFrames = nframes;
}
   
void Test::setMinTime(OSG::Real32 minTime)
{
    _minTime = minTime;
}

void Test::addFromAtUp(OSG::Pnt3f from, OSG::Pnt3f at, OSG::Vec3f up)
{
    OSG::Matrix m;
    
    OSG::MatrixLookAt(m, from, at, up);
                           
    _froms.push_back(from);
    _oris.push_back(OSG::Quaternion(m));
}

void Test::addFromAtUp(OSG::Real32 fromx, OSG::Real32 fromy, OSG::Real32 fromz, 
                       OSG::Real32 atx,   OSG::Real32 aty,   OSG::Real32 atz, 
                       OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz)
{
    addFromAtUp(OSG::Pnt3f(fromx, fromy, fromz), 
                OSG::Pnt3f(atx, aty, atz),
                OSG::Vec3f(upx, upy, upz));
}

// Define Path from VRML-Style Positon/Quaternion Strings
void Test::addFromOri(OSG::Char8 *from, OSG::Char8 *ori)
{
    OSG::Char8 *f = from, *o = ori;
    OSG::UInt32 frames = 0;
    
    while(f && *f && o && *o)
    {
        OSG::Pnt3f v;
        OSG::Quaternion q;
        
        const OSG::Char8 *grmbl=f;
#if defined(OSG_VERSION) && OSG_VERSION >= 020000
        if (!OSG::FieldTraits<OSG::Pnt3f>::getFromCString(v, grmbl))
#elif defined(OSG_VERSION) && OSG_VERSION >= 010300
        if (!OSG::FieldDataTraits<OSG::Pnt3f>::getFromString(v, grmbl))
#else
        if (OSG::FieldDataTraits<OSG::Pnt3f>::getFromString(v, grmbl))
#endif
        {
            FWARNING(("Test::addFromOri: error reading from: '%s'!\n",
                        f));
            return;
        }
        
        grmbl=o;
#if defined(OSG_VERSION) && OSG_VERSION >= 020000
        if (!OSG::FieldTraits<OSG::Quaternion>::getFromCString(q, grmbl))
#elif defined(OSG_VERSION) && OSG_VERSION >= 010300
        if (!OSG::FieldDataTraits<OSG::Quaternion>::getFromString(q, grmbl))
#else
        if (OSG::FieldDataTraits<OSG::Quaternion>::getFromString(q, grmbl))
#endif
        {
            FWARNING(("Test::addFromOri: error reading ori: '%s'!\n",
                        o));
            return;
        }
        
        _froms.push_back(v);
        _oris.push_back(q);             
        
        f = strchr(f, ',');
        if(f)
            ++f;
        
        o = strchr(o, ',');
        if(o)
            ++o;
    }
}

// Make a rotational path around the whole model
void Test::makeOrbit(OSG::Real32 upx, OSG::Real32 upy, OSG::Real32 upz)
{
    if(_scene == OSG::NullFC)
    {
        FWARNING(("Test::makeOrbit: need scene!\n"));
        return;
    }
    
    OSG::commitChanges();
    _scene->updateVolume();
    
    OSG::DynamicVolume volume;
    _scene->getWorldVolume(volume);
    
    OSG::Pnt3f center;
    volume.getCenter(center);
    
    OSG::Real32 dia = (volume.getMax() - volume.getMin()).length();
    
    OSG::Vec3f up(upx,upy,upz);
    OSG::Vec3f dir, right;
    
    up.normalize();
    
    dir = up.cross(OSG::Vec3f(1,0,0));
    if(dir.squareLength() < OSG::Eps)
    {
        dir = up.cross(OSG::Vec3f(0,1,0));
        
        if(dir.squareLength() < OSG::Eps)
        {
            dir = up.cross(OSG::Vec3f(0,0,1));
            if(dir.squareLength() < OSG::Eps)
            {
                up.setValues(0,1,0);
                dir.setValues(0,0,1);
            }
        }
    }
    
    dir.normalize();
    right = dir.cross(up);
    up = right.cross(dir);
    
    dir *= dia;
    right *= dia;
    
    _froms.clear();
    _oris.clear();
    
    // Add a few sensible camera locations
    // Using 4 gives bad results, a few more are necessary
    
    const OSG::Real32 nPoints = 100.f;
    
    for(int i = 0; i <= nPoints; ++i)
    {
        OSG::Real32 c = OSG::osgcos( M_PI * 2.f / nPoints * i);
        OSG::Real32 s = OSG::osgsin( M_PI * 2.f / nPoints * i);
        
        addFromAtUp(center + dir * c + right * s, center, up);        
    }
}

// Make a pirouette inside the model
void Test::makePirouette(OSG::Real32 upx,   OSG::Real32 upy,   OSG::Real32 upz)
{
    if(_scene == OSG::NullFC)
    {
        FWARNING(("Test::makePirouette: need scene!\n"));
        return;
    }
    
    _scene->updateVolume();
    
    OSG::DynamicVolume volume;
    _scene->getWorldVolume(volume);
    
    OSG::Pnt3f center;
    volume.getCenter(center);
    
    OSG::Real32 dia = (volume.getMax() - volume.getMin()).length() * .5;
    
    OSG::Vec3f up(upx,upy,upz);
    OSG::Vec3f dir, right;
    
    up.normalize();
    
    dir = up.cross(OSG::Vec3f(1,0,0));
    if(dir.squareLength() < OSG::Eps)
    {
        dir = up.cross(OSG::Vec3f(0,1,0));
        
        if(dir.squareLength() < OSG::Eps)
        {
            dir = up.cross(OSG::Vec3f(0,0,1));
            if(dir.squareLength() < OSG::Eps)
            {
                up.setValues(0,1,0);
                dir.setValues(0,0,1);
            }
        }
    }
    
    dir.normalize();
    right = dir.cross(up);
    up = right.cross(dir);
    
    dir *= dia;
    right *= dia;
    
    _froms.clear();
    _oris.clear();
     
    addFromAtUp(center, center + dir * OSG::Sqrt2                     , up);
    addFromAtUp(center, center + dir              + right             , up);
    
    addFromAtUp(center, center                    + right * OSG::Sqrt2, up);
    addFromAtUp(center, center - dir              + right             , up);
    
    addFromAtUp(center, center - dir * OSG::Sqrt2                     , up);
    addFromAtUp(center, center - dir              - right             , up);
    
    addFromAtUp(center, center                    - right * OSG::Sqrt2, up);
    addFromAtUp(center, center + dir              - right             , up);
    
    addFromAtUp(center, center + dir * OSG::Sqrt2                     , up);
   
}

// add a FOV to animate
void Test::addFov(OSG::Real32 fov)
{
    _fovs.push_back(fov);
}

// Run Test
void Test::setStatistics(OSG::UInt16 level)
{
    _statsLevel = level;
}

OSG::UInt16 Test::getStatistics(void)
{
    return _statsLevel;
}

void Test::setVerbose(bool verbose)
{
    _verbose = verbose;
}

void Test::useRenderTraversal(bool val)
{
    _useRenderTraversal = val;
}

void Test::setIgnoreGeometry(bool ignore)
{
    static bool isIgnored = false;
    static OSG::GeoPumpGroup* igp = new OSG::GeoIgnorePumpGroup;
    
    std::vector<OSG::GeoPumpGroup*> &p = OSG::GeoPumpGroup::getActiveGroups();
    
    if(ignore && !isIgnored)
    {
        p.insert(p.begin(), igp);
        isIgnored = true;
    }
    else if(!ignore && isIgnored)
    {
        p.erase(p.begin());
        isIgnored = false;
    }
}

// little helper function that runs the test loop. The main reason for this
// function is being able to profile it, without the initialisation.

void Test::runLoop( std::vector<OSG::Matrix> &views,
                    std::vector<OSG::Real32> &fovs)
{
    OSG::Time start, stop;
    OSG::SimpleSceneManager *ssm = _win->getSSM();

    start = OSG::getSystemTime();
    
    do
    {        
        if(_statsLevel)
        {
            OSG::UInt32 ss = _stats.size();

            _stats.resize(_stats.size() + views.size());

            if(_statsLevel > 1)
            {
                for(OSG::UInt32 i = ss; i < _stats.size(); ++i)
                {
                    _stats[i].getElem(OSG::Geometry::statNTriangles);
                }
            }
        }
        
        for(OSG::UInt32 i = 0; i < views.size(); ++i, ++_nRenderedFrames)
        {
            if(_verbose)
                SWARNING << "Test::run: Frame " << i << " ("
                         << _nRenderedFrames << ") fov " 
                         << fovs[i] << ", view" << std::endl << views[i] 
                         << std::endl;
            _win->setCamera(views[i]);
            _win->setFov(fovs[i]);
            
            if(_statsLevel)
            {
                if(_useRenderTraversal)
                    ssm->getRenderTraversalAction()->setStatistics(&_stats[_nRenderedFrames]);
                else
                    ssm->getAction()->setStatistics(&_stats[_nRenderedFrames]);
            }
    
            OSG::Thread::getCurrentChangeList()->commitChanges();
            
            _win->redraw();
        }
    }
    while(_minTime > 0 && OSG::getSystemTime() - start < _minTime);
   
    _win->finish();
    
    stop = OSG::getSystemTime();

    _time = stop - start;  

    if(_statsLevel)
    {
        if(_useRenderTraversal)
            ssm->getRenderTraversalAction()->setStatistics(NULL);
        else
            ssm->getAction()->setStatistics(NULL);
    }
}

void Test::run(void)
{
    if(!_win || !_win->isOpen())
    {
        FWARNING(("Test::run: window not ready!\n"));
        return;
    }
    if(!_scene)
    {
        FWARNING(("Test::run: no scene!\n"));
        return;
    }
    if(_froms.empty())
    {
        FWARNING(("Test::run: no views!\n"));
        return;
    }
    if(_oris.empty())
    {
        FWARNING(("Test::run: no views!\n"));
        return;
    }
    if(_froms.size() != _oris.size())
    {
        FWARNING(("Test::run: _froms.size() != _oris.size()!\n"));
        return;        
    }
    
    if(_fovs.empty())
    {
        FWARNING(("Test::run: no fovs!\n"));
        return;
    }
    
    std::vector<OSG::Matrix> views;
    std::vector<OSG::Real32> fovs;
   
    expandData(views, fovs);
    
    OSG::Time start, stop;
    OSG::SimpleSceneManager *ssm = _win->getSSM();
    
    _win->setScene(_scene);
    ssm->setHeadlight(_headlight);
    ssm->setUseTraversalAction(_useRenderTraversal);
   
    _stats.clear();
 
    OSG::Thread::getCurrentChangeList()->commitChanges();
    _win->showAll();
    _win->redraw();
    
    if(_near > 0 && _far > 0)
    {
        _win->setNearFar(_near, _far);
        if(_verbose)
            FWARNING(("Test::run: near=%f, far=%f\n", _near, _far));
    }
      
    _nRenderedFrames = 0;
    
    _win->finish();

    runLoop(views, fovs);
}


Image Test::snapshot(OSG::UInt32 frame)
{
    if(!_win || !_win->isOpen())
    {
        FWARNING(("Test::snapshot: window not ready!\n"));
        return Image();
    }
    if(!_scene)
    {
        FWARNING(("Test::snapshot: no scene!\n"));
        return Image();
    }
    if(_froms.empty())
    {
        FWARNING(("Test::snapshot: no views!\n"));
        return Image();
    }
    if(_oris.empty())
    {
        FWARNING(("Test::snapshot: no views!\n"));
        return Image();
    }
    if(_froms.size() != _oris.size())
    {
        FWARNING(("Test::snapshot: _froms.size() != _oris.size()!\n"));
        return Image();        
    }
    
    if(_fovs.empty())
    {
        FWARNING(("Test::snapshot: no fovs!\n"));
        return Image();
    }
    
    std::vector<OSG::Matrix> views;
    std::vector<OSG::Real32> fovs;
   
    expandData(views, fovs);
    
    if(frame >= views.size())
    {
        FWARNING(("Test::snapshot: frame >= views.size()!\n"));
        return Image();            
    }
    
    OSG::SimpleSceneManager *ssm = _win->getSSM();
    
    _win->setScene(_scene);
    ssm->setHeadlight(_headlight);

    _win->setCamera(views[frame]);
    _win->setFov(fovs[frame]);
    
    if(_useRenderTraversal)
        ssm->getRenderTraversalAction()->setStatistics(NULL);
    else
        ssm->getAction()->setStatistics(NULL);
    
    OSG::ImagePtr img;
    
    img = _win->snapshot();
    
    return Image(img);
}

// Get Results

OSG::Real32 Test::getFPS(void)
{
    return _nRenderedFrames / _time;
}

OSG::Real32 Test::getTime(void)
{
    return _time;
}

OSG::UInt32 Test::getNRenderedFrames(void)
{
    return _nRenderedFrames;
}

OSG::Real64 Test::getStatValue(OSG::Char8 *name, OSG::UInt32 frame)
{
    if(_stats.size() <= frame)
    {
        FWARNING(("Test::getStatValue: no statistics for frame %d!\n", frame));
        return -1;
    }
    
    OSG::Real64 val;
    std::string n(name);
    
#if defined(OSG_VERSION) && OSG_VERSION >= 13
    if(!_stats[frame].getValue(n, val))
    {
        FWARNING(("Test::getStatValue: no statistics value '%s'!\n", name));
        return -1;
    }
#else
    OSG::StatElemDescBase *desc = OSG::StatElemDescBase::findDescByName(name);
    if(!desc)
    {
        FWARNING(("Test::getStatValue: name not known '%s'!\n", name));
        return -1;
    }
    OSG::StatElem *el = _stats[frame].getElem(*desc, false);
    if(!el)
    {
        FWARNING(("Test::getStatValue: no statistics value '%s'!\n", name));
        return -1;
    }
    val = el->getValue();
#endif
    
    return val;   
}


// expand the animation data to have nFrames elements

void Test::expandData(std::vector<OSG::Matrix>& views, std::vector<OSG::Real32> &fovs)
{
    views.resize(_nFrames);
    fovs.resize(_nFrames);
    
    // interpolate the values to get _nFrames values
    
    OSG::Real32 vscale = (_froms.size() - 1) / (_nFrames - 1.f);
    OSG::Real32 fscale = (_fovs.size() - 1) / (_nFrames - 1.f);
    
    for(OSG::UInt32 i = 0; i < _nFrames; ++i)
    {
        OSG::UInt32 vi = static_cast<OSG::UInt32>(OSG::osgfloor(i * vscale));
        OSG::Real32 v = i * vscale - vi;
        
        if(v < OSG::Eps)
        {
            views[i].setTransform(_froms[vi].subZero(), _oris[vi]);
        }
        else
        {
            OSG::Quaternion q;           
            q.slerpThis(_oris[vi], _oris[vi+1], v);

            OSG::Pnt3f p = _froms[vi] + v * (_froms[vi+1] - _froms[vi]);

            views[i].setTransform(p.subZero(), q);
        }
 
        OSG::UInt32 fi = static_cast<OSG::UInt32>(OSG::osgfloor(i * fscale));
        OSG::Real32 f = i * fscale - fi;
        
        if(f < OSG::Eps)
        {
            fovs[i] = _fovs[fi];
        }
        else
        {
            fovs[i] = _fovs[fi] * (1.f  - f) + _fovs[fi + 1] * f;;
        }
    }   
}
