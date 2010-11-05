/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
#include <sstream>

#include <boost/format.hpp>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"
#include "OSGViewport.h"

#include "OSGPerfMonitorForeground.h"
#include "OSGPerfMonitor.h"

#include "OSGStatisticsDefaultFont.h"
#include "OSGTextTXFFace.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextTXFGlyph.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPerfMonitorForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGPerfMonitorForeground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerfMonitorForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    /*
    if(ePhase == TypeObject::SystemPost)
    {
    }
    */
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PerfMonitorForeground::PerfMonitorForeground(void) :
    Inherited(), _face(0), _texchunk(NULL), _texenvchunk(NULL)
{
    _texenvchunk = TextureEnvChunk::create();    
    _texenvchunk->setEnvMode(GL_MODULATE);   
}

PerfMonitorForeground::PerfMonitorForeground(const PerfMonitorForeground &source) :
    Inherited   (source),
    _face       (source._face),
    _texchunk   (source._texchunk),
    _texenvchunk(source._texenvchunk)
{
}

PerfMonitorForeground::~PerfMonitorForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PerfMonitorForeground::cycleMode(int increment)
{
    int next_mode(getMode());
    next_mode += increment;
    if (next_mode >= PerfMonitorForeground::MODE_END)
    {
        next_mode = 0;
    }
    if (next_mode < 0)
    {
        next_mode = PerfMonitorForeground::MODE_END - 1;
    }

    setMode(static_cast<UInt32>(next_mode));
}


void PerfMonitorForeground::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PerfMonitorForeground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PerfMonitorForeground NI" << std::endl;
}

/*! Initialize the text used. We may use the default compiled into the library. 
*/
void PerfMonitorForeground::initText(const std::string &family, Real32 size)
{
    // Cleanup
    if (_face != 0)
        OSG::subRef(_face);
    
    // Create the font
    if (!family.empty())
    {
        TextTXFParam param;
        param.size = static_cast<UInt32>(size);
        _face = TextTXFFace::create(family, TextFace::STYLE_PLAIN, param);
        if (_face != 0)
        {
            _texchunk = TextureObjChunk::create();
            ImageUnrecPtr texture = _face->getTexture();
            _texchunk->setImage(texture);
            _texchunk->setWrapS(GL_CLAMP);
            _texchunk->setWrapT(GL_CLAMP);
            _texchunk->setMinFilter(GL_NEAREST);
            _texchunk->setMagFilter(GL_NEAREST);
        }
    }

    // We failed to create the font - fallback to the default font
    if (_face == 0)
    {
        _face = StatisticsDefaultFont::the()->getFace();
        _texchunk = StatisticsDefaultFont::the()->getTexture();
    }

    // Increment reference counters
    OSG::addRef(_face);    

    // Init the text for the chart
    mode_names = boost::assign::map_list_of
                  (PerfMonitorForeground::Text,              "Text")
                  (PerfMonitorForeground::PercentLines,      "PercentLines")
                  (PerfMonitorForeground::PercentTotalLines, "PercentTotalLines")
                  (PerfMonitorForeground::MaxLines,          "MaxLines")
                  (PerfMonitorForeground::ThreadTiming,      "ThreadTiming");
}

/** Draw the foreground on the viewport. */
void PerfMonitorForeground::draw(DrawEnv *pEnv)
{
   // -- Check all early exit and lazy initialization code -- //
   // If we aren't active, then exit immediately
   if (!getActive())
   { return; }

   return;

   /*

   // Find the dimensions of the viewport and any other params needed for rendering
   Real32 vpWidth  = Real32(pPort->getPixelWidth());
   Real32 vpHeight = Real32(pPort->getPixelHeight());   

   // If we have an empty or NULL vp, then don't do anything
   if(vpWidth < 1 || vpHeight < 1)
      return;
   Real32 vpAspectRatio = vpWidth/vpHeight;

   // Lazy init of the font face
   if(NULL == _face)
   { 
      initText(getFamily(), 10); //getSize());       
   }   

   // --- BUILD UP TEXT AND DATA TO DRAW --- //
   PerfMonitorBase::sample_pair_vector_t samples = PerfMonitor::the()->getFlatSampleTree();
   unsigned num_samples(samples.size());
   PerfMonitorForeground::Mode render_mode = PerfMonitorForeground::Mode(getMode());

   std::vector<std::string> output_lines;       // This will be the list of lines of text

   // Put some basic stats at the top of the output
   boost::format stats_formatter("FPS: %s");
   std::string stats_line = boost::str(stats_formatter % PerfMonitor::the()->getFrameRate(10));
   output_lines.push_back(stats_line);
   
   // compute the max length of the prefix strings ("   sample_name")
   unsigned indent_size(2);
   unsigned max_len    (0);
   for (unsigned i=0; i<num_samples;++i)
   {
      const unsigned cur_len((samples[i].mDepth*indent_size) + samples[i].mSample->mName.size());
      if(cur_len > max_len)
      { max_len = cur_len; }
   }

   // Now create the lines of text
   OSG_ASSERT(mode_names.count(render_mode) == 1);
   std::string mode_name = mode_names[render_mode];   
   std::string header_string = boost::str(
         boost::format("%s%s %=10s %=10s %=7s") % mode_name
                                                % std::string(max_len-mode_name.size(), ' ')
                                                % "Avg" % "Max" % "%");
   boost::format formatter("%s [%8.5f] [%8.5f] [%5.3f]");      // Formatter for each line

   output_lines.push_back(header_string);
   for (unsigned i=0; i<num_samples; ++i)
   {      
      unsigned sample_depth      = samples[i].mDepth;
      NestedSampleInfoPtr sample = samples[i].mSample;

      // Create a correctly spaced "prefix" string with indent, name, and filler
      std::string indent_str(sample_depth*2, ' ');
      std::string name_string(indent_str + sample->mName);
      std::string filler_string(max_len - name_string.size(), ' ');
      name_string += filler_string;
      std::string str_out = boost::str(formatter % name_string
                                                 % sample->mAverage
                                                 % sample->mMax
                                                 % sample->mPercentage);
      output_lines.push_back(str_out);
   }

   // --- Create chart data to render -- //
   // - We allocate all buffers but only fill them if we are in that mode.
   // Chart data vectors that is used when rendering normalized data (percentages, etc)
   // Note: all buffers *must* have max_samples entries to be valid
   std::vector< std::vector<float> > normalized_chart_data;
   unsigned max_samples = PerfMonitorBase::max_samples;

   if (PerfMonitorForeground::PercentLines == render_mode)
   {
      for(unsigned i=0;i<num_samples;++i)
      {
         std::vector<float> percent_samples = samples[i].mSample->getPercentageSamples();
         percent_samples.resize(max_samples, 0.0f);
         normalized_chart_data.push_back(percent_samples);
      }
   }
   // Create new data that has percentage of each sample out of total time.
   else if (PerfMonitorForeground::PercentTotalLines == render_mode)
   {
      std::vector<float> total_values = samples[0].mSample->getSamples();
      total_values.resize(max_samples, 0.0f);

      for(unsigned i=0;i<num_samples;++i)
      {
         std::vector<float> values = samples[i].mSample->getSamples();
         values.resize(max_samples, 0.0f);
         for (unsigned j=0;j<max_samples;j++)
         {
            float total_value(total_values[j]);
            if (total_value == 0.0)
            { values[j] = 0.0; }
            else
            { values[j] = values[j] / total_value; }
         }
         normalized_chart_data.push_back(values);
      }
   }
   // List of samples normalized by the max value in each set
   else if (PerfMonitorForeground::MaxLines == render_mode)
   {
      for (unsigned i=0;i<num_samples;++i)
      {
         std::vector<float> values = samples[i].mSample->getSamples();
         float max_value=0.0f;
         // find max value
         for (unsigned j=0;j<values.size();j++)
         { max_value = OSG::osgMax(values[j], max_value); }
         // normalize the values based on max value
         if (max_value != 0.0f)
         {
            for(unsigned j=0;j<values.size();j++)
            {  values[j] = values[j]/max_value; }
         }
         values.resize(max_samples, 0.0f);
         normalized_chart_data.push_back(values);
      }
   }

   // --- LAYOUT THE TEXT and DATA --- //
   // Now layout the text to draw it on the screen
   TextLayoutParam layoutParam;
   layoutParam.spacing = 1.1;
   layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
   layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;

   TextLayoutResult layoutResult;
   _face->layout(output_lines, layoutParam, layoutResult);

   unsigned num_lines(output_lines.size());
   Real32 est_height(float(num_lines)*1.1f);

   // layoutResult.textBounds is almost the number of lines and characters in size
   //  - It takes into account spacing and stuff like that
   Real32 scale       = 1.0f / _face->getScale();         // Scale to get to pixels or num pixels in size ??
   Real32 size        = _face->getParam().size;           // Size of the face in pixels?
   Real32 textBlockWidth   = layoutResult.textBounds.x() * scale;    // Num base font pixels in size ??
   Real32 textBlockHeight  = layoutResult.textBounds.y() * scale;    // Num base font pixels in size ??
   Real32 chartBlockWidth(0.0), chartBlockHeight(0.0);
   if (PerfMonitorForeground::Text != render_mode)
   {
      chartBlockWidth  = textBlockWidth * 2.0;           // Hack for now, should be based on window size
      chartBlockHeight = textBlockHeight;
   }
   // Panel is larger then just text, we add on size/2 spacing and two margins
   Real32 panelWidth  = textBlockWidth  + chartBlockWidth  + size + (getTextMargin().x() * 2.0f);
   Real32 panelHeight = textBlockHeight +                  + size + (getTextMargin().y() * 2.0f);

   // Scale the size of the virtual surfaced based on what can fit
   float surf_mult(1.0);
   if (panelHeight > vpHeight)
   { surf_mult = (panelHeight/vpHeight); }

   Real32 surfaceWidth  = vpWidth  * surf_mult;
   Real32 surfaceHeight = vpHeight * surf_mult;

   // ---- SETUP THE VIRTUAL VIEWPORT ---- //   
   // Now setup the GL state for "drawing" the text
   // Note on ortho: We want to map one unit to one pixel on the
   // screen. Some sources in the internet say that we should
   // add an offset of -0.375 to prevent rounding errors. Don't
   // know if that is true, but it seems to work.
   glPushAttrib(GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_COLOR_MATERIAL);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   //glOrtho(0 - 0.375, (panelHeight*vpAspectRatio) - 0.375, 0 - 0.375, panelHeight - 0.375, 0, 1);
   glOrtho(0 - 0.375, surfaceWidth - 0.375, 0 - 0.375, surfaceHeight - 0.375, 0, 1);   

   // --- DRAW EVERYTHING --- //
   // Let's do some simple form of layout management
   // - just determining the place to put the "text box"
   Real32 startX(0), startY(surfaceHeight);
   glTranslatef(startX, startY, 0.0);

   // draw background
   glColor4fv((GLfloat*)getBgColor().getValuesRGBA());
   glBegin(GL_QUADS);
      glVertex2f(0, -panelHeight);               // LL
      glVertex2f(panelWidth, -panelHeight);      // LR
      glVertex2f(panelWidth, 0);                 // UR
      glVertex2f(0, 0);                          // UL
   glEnd();

   // draw border
   if(getBorderColor().alpha() >= 0.0f)
   {
      glColor4fv((GLfloat*)getBorderColor().getValuesRGBA());
      glBegin(GL_LINE_LOOP);
         Real32 left(getBorderOffset().x()), bottom(-panelHeight+1+getBorderOffset().y()),
                right(panelWidth -1 -getBorderOffset().x()), top(-1 - getBorderOffset().y());
         glVertex2f(left,  bottom);  // LL
         glVertex2f(right, bottom);  // LR
         glVertex2f(right, top);     // UR
         glVertex2f(left,  top);     // UL
      glEnd();
   }

   // Create some colors for the chart bars (alternative color for better visibility)
   std::vector<OSG::Color4f> chart_colors;
   OSG::Color4f bg_color = getBgColor();
   OSG::Color4f chart_color1 = OSG::Color4f(1.0,1.0,1.0,0.0);
   OSG::Color4f chart_color2 = (bg_color * 0.2f);
   chart_color2[3] = 0.4;
   chart_colors.push_back(chart_color1);
   chart_colors.push_back(chart_color2);
   unsigned next_base_color_idx(0);

   // Now render chart if needed
   if ( (PerfMonitorForeground::PercentLines      == render_mode) ||
        (PerfMonitorForeground::PercentTotalLines == render_mode) ||
        (PerfMonitorForeground::MaxLines          == render_mode) )
   {
   glPushMatrix();
      // Go to upper left of chart area
      glTranslatef(( 0.5 * size) + getTextMargin().x() + textBlockWidth, 
                   (-0.5 * size) - getTextMargin().y(), 0.0);
      float left (0.0);
      float right(chartBlockWidth);
      float sample_height(1.1f * size);          // XXX: ???
      float value_width(chartBlockWidth/float(max_samples));  // Amount to move right for each chart value

      // Skip the first line since it is the header and skip another to get to bottom of sample line
      unsigned num_header_lines(2);
      for (unsigned i=0;i<num_header_lines;i++)
      {  glTranslatef(0.0, -sample_height, 0.0); }
      glTranslatef(0.0, -sample_height, 0.0);

      // Alternate colors for the base color      
      for(unsigned i=0; i<num_samples;++i)
      {
         // Draw border box
         glColor4fv(chart_colors[next_base_color_idx].getValuesRGBA());
         next_base_color_idx += 1;
         if (next_base_color_idx >= chart_colors.size())
         { next_base_color_idx = 0; }

         glBegin(GL_QUADS);
            glVertex2f(-textBlockWidth,           0.0);      // LL
            glVertex2f(right,                     0.0);      // LR
            glVertex2f(right,           sample_height);      // UR
            glVertex2f(-textBlockWidth, sample_height);      // UL
         glEnd();

         // Draw the data
         OSG::Color3f base_color(1.0, 1.0, 0.0);
         OSG::Color3f high_color(1.0, 0.4, 0.0);
         OSG::Color3f cur_color;
         std::vector<float>& norm_data(normalized_chart_data[i]);
         OSG_ASSERT(norm_data.size() == max_samples);

         glBegin(GL_LINE_STRIP);            
            for (unsigned x=0;x<max_samples;++x)
            {
               float cur_val(norm_data[x]);
               cur_color = (base_color*(1.0-cur_val)) + (high_color*cur_val);
               glColor3fv(cur_color.getValuesRGB());
               glVertex2f(float(x)*value_width, norm_data[x]*size);
            }
         glEnd();

         // Go to next line
         glTranslatef(0.0, -sample_height, 0.0);
      }

   glPopMatrix();
   }

   // Now render the text
   // - first offset by the margins into the text area
   glPushMatrix();
   glTranslatef(( 0.5 * size) + getTextMargin().x(), 
                (-0.5 * size) - getTextMargin().y(), 0.0);

   _texchunk   ->activate(pEnv);       // Active the texture for the text
   _texenvchunk->activate(pEnv);
   
   // draw text
   glColor4fv((GLfloat *) getColor().getValuesRGBA());
   glPushMatrix();
   glScalef(scale, scale, 1);
   _face->drawCharacters(layoutResult);
   glPopMatrix();

   _texchunk   ->deactivate(pEnv);
   _texenvchunk->deactivate(pEnv);
   glPopMatrix();

   // Go back to the initial state
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();

   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();

   glPopAttrib();

   */
}

OSG_END_NAMESPACE
