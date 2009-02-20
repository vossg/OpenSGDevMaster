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

#include "OSGConfig.h"

#include <sstream>

#include "OSGPerfMonitor.h"
//#include <boost/format.hpp>
#include "OSGBaseInitFunctions.h"
#include "OSGSingletonHolder.ins"
#include "OSGBaseFunctions.h"
#include "OSGThread.h"

OSG_USING_NAMESPACE
OSG_BEGIN_NAMESPACE
OSG_SINGLETON_INST(PerfMonitorBase, addPostFactoryExitFunction);

void NestedSampleInfo::updateFrame()
{
    typedef subsample_map_t::iterator iter_type;

    // Update the children
    for (iter_type i = mSubSamples.begin(); i != mSubSamples.end(); ++i)
    {
        (*i).second->updateFrame();
    }

    // Compute the limit on number of samples to hold
    UInt32 sample_limit = NestedPerfTracker::max_samples;

    // Compute my sample value and average
    mSamples.push_front(mTimeSummer);
    mTimeSummer = 0.0;
    while(mSamples.size() > sample_limit)
    {
        mSamples.pop_back();
    }

    // Compute max and average
    mMax = 0.0f;
    Real32 total(0.0f);
    for(UInt32 i=0;i<mSamples.size();++i)
    {
        Real32 val(mSamples[i]);
        total += val;
        if (val > mMax)
        {
            mMax = val;
        }
    }
    if (mSamples.size() > 0)
    {
       mAverage = total / static_cast<Real32>(mSamples.size());
    }

    // Calculate the percentages of averages for each subsample
    for (iter_type i = mSubSamples.begin(); i != mSubSamples.end(); ++i)
    {
        NestedSampleInfoPtr child((*i).second);
        child->calcPercentage(mAverage);      
    }
}

void NestedSampleInfo::calcPercentage(const Real32 parentAverage)
{
    if(parentAverage == 0.0f)
    {
        mPercentage = 0.0;
    }
    else
    {
        mPercentage = mAverage/parentAverage;
    }

    // Add the percentage to the list
    mPctSamples.push_front(mPercentage);
    while(mPctSamples.size() > NestedPerfTracker::max_samples)
    {
        mPctSamples.pop_back();
    }
}

std::string NestedSampleInfo::outString(UInt32 indent, bool detailed)
{
    std::ostringstream ostring;
    //std::string indent_str(indent*2, ' ');
    std::string indent_str("  ");
    ostring << indent_str << mName << "[" << mPercentage << "] [" << mAverage
            << "]\n";
    // boost::format("[%.4f] [%.4f]\n")%mPercentage%mAverage;
    if (detailed)
    {
        ostring << "     samples:[";
        typedef sample_list_t::iterator iter_type;
        for (iter_type i = mSamples.begin(); i != mSamples.end(); ++i)
        {
            ostring << (*i) << ", ";
        }
        ostring << "]\n";
    }

    std::string ret_string = ostring.str();
    typedef subsample_map_t::iterator iter_type;
    for (iter_type i = mSubSamples.begin(); i != mSubSamples.end(); ++i)
    {
        ret_string += (*i).second->outString(indent + 1, detailed);
    }
    return ret_string;
}

void NestedPerfTracker::updateFrame()
{
    // Update the entire tree
    mPerfRoot->updateFrame();

    // Compute average for root
    mPerfRoot->mAverage = 0.0;
    typedef NestedSampleInfo::subsample_map_t::iterator iter_type;
    for(iter_type i = mPerfRoot->mSubSamples.begin();
        i != mPerfRoot->mSubSamples.end(); ++i)
    {
        mPerfRoot->mAverage += (*i).second->mAverage;
    }

    // Compute overall framerate
    OSG::TimeStamp cur_time(OSG::getTimeStamp());
    Real32 frame_time = OSG::getTimeStampMsecs(cur_time-mLastFrameStart);
    mLastFrameStart = cur_time;
    mFrameTimes.push_front(frame_time);
    while (mFrameTimes.size() > max_samples)
    {
        mFrameTimes.pop_back();
    }
    Real32 av_frame_time = std::accumulate(mFrameTimes.begin(),
                                           mFrameTimes.end(), 0.0)
                              / static_cast<Real32>(mFrameTimes.size());
    mFrameRate = 1.0 / av_frame_time;
}

std::string NestedPerfTracker::outString(bool detailed)
{
    std::string ret_val = mPerfRoot->outString(1, detailed);
    return ret_val;
}

NestedPerfTracker::sample_pair_vector_t NestedPerfTracker::getFlatSampleTree(
    UInt32 depth,
    NestedSampleInfoPtr curNode
)
{
    NestedPerfTracker::sample_pair_vector_t sample_list;
    if (curNode.get() == NULL)
    {
        curNode = mPerfRoot;
    }
    sample_list.push_back(SamplePair(depth, curNode));

    typedef NestedSampleInfo::subsample_map_t::iterator iter_type;
    for(iter_type i = curNode->mSubSamples.begin();
        i != curNode->mSubSamples.end(); ++i)
    {
        NestedPerfTracker::sample_pair_vector_t sub_sample_list = 
            getFlatSampleTree(depth+1, (*i).second);
        sample_list.insert(sample_list.end(), 
                           sub_sample_list.begin(), sub_sample_list.end());
    }
    return sample_list;
}

Real32 NestedPerfTracker::getFrameRate(UInt32 avgOverFrames) const
{
    if (0 == avgOverFrames)
    { 
        return mFrameRate; 
    }
    else
    {
        avgOverFrames = OSG::osgMin(avgOverFrames,
                                    static_cast<UInt32>(mFrameTimes.size()));
        Real32 av_frame_time =
            std::accumulate(mFrameTimes.begin(),
                            mFrameTimes.begin() + avgOverFrames, 0.0)
                / static_cast<Real32>(avgOverFrames);
        Real32 frame_rate = 1.0 / av_frame_time;
        return frame_rate;
    }
}

UInt32 NestedPerfTracker::max_samples = 500;


PerfMonitorBase::PerfMonitorBase()
    : mEnabled(false) 
    , mDataLock(NULL)
    , mCurrentFrameNum(0)
    , mFlushingRate(600)
    , mOutFile(NULL)
{      
    mDataLock = OSG::Lock::get("PerfMonitor::mDataLock");
    mStartTimeMs = OSG::getTimeStampMsecs(OSG::getTimeStamp());
}

void PerfMonitorBase::reset()
{
    mDataLock->acquire();
    mFlushingRate = 600;
    setOutputFile("");      // Clear the output file
    mSamples.clear();
    mDataLock->release();
}

void PerfMonitorBase::enable(bool val)
{ 
    mEnabled = val; 
}

void PerfMonitorBase::sample(SampleType sampleType, const std::string& name,
                             OSG::Real32 metricValue, const std::string& desc)
{
    if(! mEnabled)
    {
        return;
    }

    OSG::Real64 sample_time = getTimeStampMs(); 
    OSG::UInt64 tid         = getThreadId();

    SampleData sample_data(tid, sample_time, sampleType, name, metricValue,
                           desc);
   
    // XXX: This is expensive.  We need a better way to do this
    //      that allows for lock-free collection of samples.
    mDataLock->acquire();         
    mSamples.push_back(sample_data);
    mDataLock->release();

    // TODO: Update helpers
   
}

/** Called once per "frame" to update internal data structures. */
void PerfMonitorBase::updateFrame()
{
    mCurrentFrameNum += 1;
    sample(FRAME, "frame", mCurrentFrameNum);

    mDataLock->acquire();

    // TODO: Update helpers

    // Flush as needed
    if ((mSamples.size() % mFlushingRate) == 0)
    {
       flushOutput();
       mSamples.clear();
    }

    mDataLock->release();
}

/** Return the id of the current thread. */
OSG::UInt64 PerfMonitorBase::getThreadId() const
{
#ifdef WIN32
    return OSG::UInt64(GetCurrentThreadId());
#else
    return OSG::UInt64(pthread_self());
#endif
}

void PerfMonitorBase::setOutputFile(const std::string& filename)
{
    // Close up old file if needed
    if (mOutFile != NULL)
    { 
        mOutFile->close(); 
        delete mOutFile;
        mOutFile = NULL;
    }

    if (filename != "")
    {
        // Open the file if needed
        mOutFile = new std::ofstream(filename.c_str(), std::ios_base::trunc);
    }
}

void PerfMonitorBase::flushOutput()
{
    if (NULL == mOutFile)
    {
        return;
    }

    for(UInt32 i = 0; i < mSamples.size(); ++i)
    {
        SampleData cur_sample = mSamples[i];
        (*mOutFile) << cur_sample.thread_id << ","
                    << std::setprecision(20) << std::fixed
                    << cur_sample.timestamp << ","
                    << static_cast<UInt32>(cur_sample.type) << ","
                    << std::scientific << std::setprecision(20)
                    << cur_sample.metric_value << ","
                    << '"' << cur_sample.name << '"' << ","
                    << '"' << cur_sample.desc << '"' << std::endl;
    }

    mOutFile->flush();
}

void PerfMonitorBase::printSamples()
{
    for(UInt32 i = 0; i < mSamples.size(); ++i)
    {
        SampleData cur_sample = mSamples[i];
        std::cout << i << ": " 
                  << "  tid: " << cur_sample.thread_id
                  << "  ts: " <<  cur_sample.timestamp
                  << "  type: " << static_cast<UInt32>(cur_sample.type)
                  << "  metric: " << cur_sample.metric_value
                  << "  name: " << cur_sample.name
                  << "  desc: " << cur_sample.desc << std::endl;
    }
}

OSG_END_NAMESPACE
