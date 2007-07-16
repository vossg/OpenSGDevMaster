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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGSepiaComposer.h>

OSG_USING_NAMESPACE

/*! \class osg::SepiaComposer

 This composer implements the binary swap composition. 
*/

void SepiaComposer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/*----------------------- constructors & destructors ----------------------*/

SepiaComposer::SepiaComposer(void) :
    Inherited()
{
}

SepiaComposer::SepiaComposer(const SepiaComposer &source) :
    Inherited(source)
{
}

SepiaComposer::~SepiaComposer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SepiaComposer::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SepiaComposer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SepiaComposer NI" << std::endl;
}

/*----------------------------- features ---------------------------------*/

/*! Currently it is not possible to do rendering on the client
 */
bool SepiaComposer::getClientRendering()
{
    return false;
}

/*----------------------------- composition -------------------------------*/

void SepiaComposer::open(void)
{
#ifdef OSG_WITH_SEPIA
    // sync all renderers and the client
    Connection *connection=clusterWindow()->getNetwork()->getMainConnection();
    if(isClient())
    {
        connection->wait();
        connection->signal();
    }
    else
    {
        connection->signal();
        connection->wait();
    }

    bool isDisplay;
    _toNode   = clusterId()+1; 
    _fromNode = clusterId()-1; 

    if(isClient())
    {
        _toNode    = SEPIA_NO_NODE;
        isDisplay = true;
    }
    else
    {
        isDisplay = false;
    }
    if(clusterId() == 0)
    {
        _fromNode = SEPIA_NO_NODE;
    }
//    printf("init %d %d\n",getWidth(),getHeight());

    int bfsize = clusterWindow()->getWidth() * clusterWindow()->getHeight() * 4;

    /* open the default Sepia */
    _pam = SepiaOpen(NULL);
    /* set the ServerNet node number for this node */
    SepiaSetNodeNumber(_pam, clusterId());
    /* set the node type: Rendering or Display */
    SepiaSetNodeType(_pam, isDisplay ? DISPLAY_NODE : RENDERING_NODE);
    /* initialize the Sepia */
    SepiaInit(_pam);
    /* Insure that cleanup is done when we exit */
    // !!!! atexit(finalizeSepia);

    SINFO << "Use readPixel Mode" << std::endl;
    /* set the channel format */
    SepiaSetFormat(_pam, TWO_32b_CHANNELS_DISPLAY_ONE);

    if (isDisplay) {
        _pbuffer = SepiaAllocateAlignedMemory (bfsize);
        SepiaLockAndBuildDescriptors (_pam, _pbuffer, NULL, 
                                      bfsize,
                                      isDisplay, 
                                      &_descvirtaddr, 
                                      &_descphysaddr);
    } 
    else
    {
        /*--render node specific setup--*/
        SepiaSetVerbose(_pam,1);

        /* set the comparison to less than and 32 bit Z depth */
        SetCompzParameters(_pam, GL_LESS, Z32);

        /* setup two buffers: one for the pixels and one for the depth information */
        _pbuffer = SepiaAllocateAlignedMemory (bfsize);
        _zbuffer = SepiaAllocateAlignedMemory (bfsize);
        SepiaLockAndBuildDescriptors (_pam, 
                                      _pbuffer, _zbuffer,
                                      bfsize, isDisplay,
                                      &_descvirtaddr,
                                      &_descphysaddr);
    }
#endif
}

void SepiaComposer::composeWindow(void)
{
#ifdef OSG_WITH_SEPIA
    int width=clusterWindow()->getWidth();
    int height=clusterWindow()->getHeight();
    // sync all renderers and the client
    Connection *connection=clusterWindow()->getNetwork()->getMainConnection();
    if(isClient())
    {
        connection->wait();
        connection->signal();
    }
    else
    {
        connection->signal();
        connection->wait();
    }

    // display node ?
    if (isClient()) 
    {
        SepiaStartTransfer(_pam, _fromNode,
                           SEPIA_NO_NODE,
                           _descphysaddr);
        usleep(1000);
        /* wait until we have a buffer to display */
        SepiaWaitTransfer(_pam);
        
        glViewport(0,0,width,height);

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, width, 0, height,-1,1);
        
        glDisable(GL_SCISSOR_TEST);
        glRasterPos2i(0, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelZoom(1.0, 1.0);
        glDrawPixels(width,height,
                     GL_RGBA, GL_UNSIGNED_BYTE,
                     _pbuffer);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
    else
    {
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(	0,						/* GLint x - lower left corner */
                        0,						/* GLint y - lower left corner */
                        width,	                /* GLsizei width */
                        height,	                /* GLsizei height */
                        GL_RGBA,				/* GLenum format */
                        GL_UNSIGNED_BYTE,		/* GLenum type */
                        _pbuffer);
        glReadPixels(	0,						/* GLint x - lower left corner */
                        0,						/* GLint y - lower left corner */
                        width,	                /* GLsizei width */
                        height              ,	/* GLsizei height */
                        GL_DEPTH_COMPONENT,		/* GLenum format */
                        GL_UNSIGNED_INT,		/* GLenum type */
                        _zbuffer);
        
        SepiaStartTransfer(_pam, 
                           _fromNode, 
                           _toNode,
                           _descphysaddr);

        /* wait for the transfer to complete */
        SepiaWaitTransfer(_pam);
    }
#endif
}

void SepiaComposer::close(void)
{
}

/*----------------------------- features ---------------------------------*/

/*----------------------------- helper ------------------------------------*/

/*----------------------------- thread proc -------------------------------*/

