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

#ifndef _OSG_PERF_MONITOR_
#define _OSG_PERF_MONITOR_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGTime.h"
#include "OSGConfig.h"
#include "OSGSingletonHolder.h"
#include "OSGLock.h"

#include <boost/shared_ptr.hpp>

#include <deque>
#include <vector>
#include <string>
#include <numeric>
#include <iostream>

#include "OSGDeprecatedCPP.h"

OSG_BEGIN_NAMESPACE

class NestedSampleInfo;
typedef boost::shared_ptr<NestedSampleInfo> NestedSampleInfoPtr;

/*! \ingroup BaseGrpPerfMon
 *  \nohierarchy
 * Helper class to hold samples and sub samples.
 * A node in the "performance tree".
 */
class OSG_BASE_DLLMAPPING NestedSampleInfo
{
  public:
#ifdef OSG_STL_HAS_HASH_MAP
#if !defined(WIN32) && !defined(_LIBCPP_VERSION)
    /*! \nohierarchy */
    struct string_hash
    {
        size_t operator()(const std::string &s) const
        {
            return OSG_STDEXTENSION_NAMESPACE::__stl_hash_string(s.c_str());
        }
    };

    typedef OSG_STDEXTENSION_NAMESPACE::hash_map<std::string, NestedSampleInfoPtr,string_hash> subsample_map_t;
#else
    typedef OSG_STDEXTENSION_NAMESPACE::hash_map<std::string, NestedSampleInfoPtr> subsample_map_t;
#endif
#else
    typedef std::map<std::string, NestedSampleInfoPtr> subsample_map_t;
#endif
    typedef std::deque<Real32>  sample_list_t;
    typedef std::vector<Real32> sample_vector_t;

    NestedSampleInfo(const std::string& name)
        : mName(name)
        , mTimeSummer(0)
        , mStartTime(0)
        , mMax(0.0)
        , mAverage(0.0)
        , mPercentage(0.0)
    {;}

    static NestedSampleInfoPtr create(const std::string& name)
    {
        return NestedSampleInfoPtr(new NestedSampleInfo(name));      
    }

    void start()
    {
        mStartTime = OSG::getTimeStamp();
    }
    void stop()
    {
       OSG::TimeStamp stop_time(OSG::getTimeStamp());
       OSG::TimeStamp sample_time(stop_time - mStartTime);
       addTime(OSG::getTimeStampMsecs(sample_time));
    }

    void addTime(Real32 sample)
    {
        mTimeSummer += sample;
    }

    /** Update all our internal values and the settings of children. */
    void updateFrame();

    /**
     * Helper to recalculate the percentage given the average of the parent.
     */
    void calcPercentage(const Real32 parentAverage);

    /**
     * "print" the details of this sample and its children to a string that
     * is returned.
     */
    std::string outString(UInt32 indent=0, bool detailed=false);

    // -- Accessors -- //
    sample_vector_t getSamples() const
    {
        return sample_vector_t(mSamples.begin(), mSamples.end());
    }
    sample_vector_t getPercentageSamples() const
    {
        return sample_vector_t(mPctSamples.begin(), mPctSamples.end());
    }
    const std::string& getName() const
    {
        return mName;
    }
    Real32 getAverage() const
    {
        return mAverage;
    }
    Real32 getPercentage() const
    {
        return mPercentage;
    }

public:
   std::string      mName;        /**< Name of the sample. */
   subsample_map_t  mSubSamples;  /**< Other sample infos below us. map: name --> NestedSampleInfoPtr */
   Real32           mTimeSummer;  /**< Running time summer. Moved to samples once per frame. */
   sample_list_t    mSamples;     /**< List of samples we have collected. */
   sample_list_t    mPctSamples;  /**< List of percentage samples we have collected. (running list of percentages) */
   OSG::TimeStamp   mStartTime;   /**< The last start time we tried. */
   Real32           mMax;         /**< The maximum sample. */
   Real32           mAverage;     /**< Average time in seconds. */
   Real32           mPercentage;  /**< Percentage of time consumed relative to siblings. */   
};

/*! \ingroup GrpBasePerfMon
 *  \nohierarchy
 * Performance tracker that tracks the performance of nested calls.  This is
 * useful for later visualization of the performance from these values. 
 */
class OSG_BASE_DLLMAPPING NestedPerfTracker
{
public:
    /*! \nohierarchy */
    class SamplePair
    {
    public:
        SamplePair(UInt32 depth_, NestedSampleInfoPtr sample_)
            : depth(depth_)
            , sample(sample_)
        {
        }

        bool operator==(const SamplePair& rhs) const
        {
            return depth == rhs.depth && sample == rhs.sample;
        }

        UInt32              depth;
        NestedSampleInfoPtr sample;
    };

    typedef std::vector<NestedSampleInfoPtr> sample_stack_t;
    typedef std::deque<Real32>       frame_times_list_t;
    typedef std::vector<Real32>      frame_times_vector_t;
    typedef std::vector<SamplePair>  sample_pair_vector_t;

protected:
    template <class SingletonT>
    friend class OSG::SingletonHolder;

    NestedPerfTracker()
        : mEnabled(false)
        , mLastFrameStart(OSG::getTimeStamp())
        , mFrameRate(0.0)
    {
        mPerfRoot = NestedSampleInfo::create("root");
        mCurSampleStack.push_back(mPerfRoot);
    }

public:
    void enable(bool val = true)
    {
        mEnabled = val;
    }

    void enter(const std::string& name)
    {
        if(! mEnabled)
        {
            return;
        }

        // Get the current sample we are in and then get it's subsample for
        // the new entry
        NestedSampleInfoPtr cur_sample = mCurSampleStack.back();
        if(cur_sample->mSubSamples.find(name) == cur_sample->mSubSamples.end())
        {
            cur_sample->mSubSamples[name] = NestedSampleInfo::create(name);
        }
        NestedSampleInfoPtr sub_sample = cur_sample->mSubSamples[name];

        // Start the time and append it to the back of the stack
        sub_sample->start();
        mCurSampleStack.push_back(sub_sample);
   }

    void exit(const std::string& name)
    {
        if(! mEnabled)
        {
            return;
        }

        NestedSampleInfoPtr cur_sample = mCurSampleStack.back();
        OSG_ASSERT(mCurSampleStack.size() > 1);
        cur_sample->stop();
        mCurSampleStack.pop_back();
    }

    /**
     * Helper method to add a sampled time without using enter and exit.
     * This is useful when we have data from another source and just want to
     * add it.
     */
    void addSampledTime(const std::string& name, Real32 timeVal)
    {
        if(! mEnabled)
        {
            return;
        }

        // Get the current sample we are in and then get it's subsample for
        // the new entry
        NestedSampleInfoPtr cur_sample = mCurSampleStack.back();
        if(! cur_sample->mSubSamples.count(name))
        {
            cur_sample->mSubSamples[name] = NestedSampleInfo::create(name);
        }
        NestedSampleInfoPtr sub_sample = cur_sample->mSubSamples[name];
        sub_sample->addTime(timeVal);
    }

    /**
     * Update the periodic performance information such as percentages
     * and anything else that we can calculate continuously.
     */
    void updateFrame();

    /** "print" the details of this all samples in the tree to a string. */
    std::string outString(bool detailed=false);

    /**
     * Return a flat tree of sample nodes.
     * [(depth,sample), ...]
     */
    sample_pair_vector_t getFlatSampleTree(
        UInt32 depth = 0,
        NestedSampleInfoPtr curNode = NestedSampleInfoPtr()
    );

    // --- Accessors --- //
    bool getEnabled() const
    {
        return mEnabled;
    }

    /**
     * Return the average frame rate.
     *
     * @param avgOverFrames If 0, then over all frames we know about.
     */
    Real32 getFrameRate(UInt32 avgOverFrames = 0) const;

    frame_times_vector_t getFrameTimes() const
    {
        return frame_times_vector_t(mFrameTimes.begin(), mFrameTimes.end());
    }

    UInt32 getMaxSamples() const
    {
        return max_samples;
    }

public:
   NestedSampleInfoPtr      mPerfRoot;
   bool               mEnabled;
   sample_stack_t     mCurSampleStack;
   OSG::TimeStamp     mLastFrameStart;
   frame_times_list_t mFrameTimes;
   Real32             mFrameRate;

   static UInt32      max_samples;  /**<< The maximum number of samples to collect. */
};


/*! \ingroup GrpBasePerfMon
 *  \nohierarchy
 * Central class for all performance monitoring.
 * This class is a singleton that provides the interface for collecting
 * performance monitoring data.  It makes use of other helper classes to
 * aggregate and analyze this data as needed.
 * 
 * @note Samples are collected per thread, but in order to reduce sampling
 *       overhead (ie locking), we do not extend the list of available threads
 *       on each sample.  Instead, we only update the potential thread list
 *       once per frame.  If a new thread is detected, it is added to a new
 *       thread list that is cleared as part of the frame update.
 * 
 * File format:
 *    One line per sample.  Each list is a list of comma separated values.
 *  <thread id: int>,<timestamp: double>,<type: int>,<metric: double>,<name:"string",<desc: "string">
*/
class OSG_BASE_DLLMAPPING PerfMonitorBase
{
public:
    enum SampleType
    {
        ENTER  =   0, /**< Enter a region. */
        EXIT   =   1, /**< Exit a region. */
        MARK   =  10, /**< Mark point for something interesting. */
        METRIC =  11, /**< Store a metric value. */
        FRAME  = 100, /**< Store marker for the end/start of a frame. */
        LAST
    };

    /*! \nohierarchy
        Data for a single sample. 
     */
    struct SampleData
    {
        SampleData()
        {;}
 
        SampleData(OSG::UInt64 tid, OSG::Real64 timestamp,
                   SampleType type, const std::string& name,
                   OSG::Real32 metricValue = 0.0,
                   const std::string& desc = "")
            : thread_id(tid)
            , timestamp(timestamp)
            , type(type)
            , metric_value(metricValue)
            , name(name)
            , desc(desc)
        {
        }

        bool operator==(const SampleData& rhs) const
        {
            return ( (rhs.thread_id == thread_id) &&
                     (rhs.timestamp == timestamp) &&
                     (rhs.type == type) &&
                     (rhs.metric_value == metric_value) &&
                     (rhs.desc == desc) &&
                     (rhs.name == name));
        }

        OSG::UInt64 thread_id;	  /**< unique id of the thread for the sample. */
        OSG::Real64 timestamp;	  /**< timestamp when the sample occured. */
        SampleType  type;		  /**< The type of sample collected. */
        OSG::Real32 metric_value;	  /**< Value of any metric collected. */
        std::string name;		  /**< Name for the sample. */
        std::string desc;		  /**< Extended description of the sample. */
    };

    typedef std::vector<SampleData> sample_data_list_t;

protected:
    template <class SingletonT>
    friend class OSG::SingletonHolder;

    PerfMonitorBase();
    ~PerfMonitorBase(void);

public:
    /** Reset the performance collection. */
    void reset();

    void enable(bool val = true);

    /**
     * Enter a sample for the performance monitor.
     * @arg sampleType: The type of sample that we should add.
     * @arg desc: A text description (name, label, etc) to go with the sample.
     */
    void sample(SampleType sampleType, const std::string& name,
                OSG::Real32 metricValue = 0.0, const std::string& desc = "");

    /** Called once per "frame" to update internal data structures. */
    void updateFrame();

    // --- Accessors --- //
    bool getEnabled() const
    {
        return mEnabled;
    }

    /** Return the id of the current thread. */
    OSG::UInt64 getThreadId() const;

   OSG::Real64 getTimeStampMs()
   {
       return OSG::getTimeStampMsecs(OSG::getTimeStamp()) - mStartTimeMs;
   }

    // --- Output Processing --- //
    /** Set the output file to use for data dumping. */
    void setOutputFile(const std::string& filename);

    /** Set the output file flush rate. */
    void setOutputFlushRate(OSG::UInt64 rate)
    {
        mFlushingRate = rate;
    }

    /** Periodically called to flush the output file. */
    void flushOutput();

    /** Helper to print samples to std::out. */
    void printSamples();

public:
    bool                mEnabled;  /**< Indicates that the performance monitor should be active. */   
    sample_data_list_t  mSamples;  /**< Samples collected for all known threads. */

    /** Must be acquired if updating the data structure of any shared resource. */
    OSG::LockRefPtr mDataLock;    

    /** Data flushing. */
    OSG::UInt64    mCurrentFrameNum; /**< The current frame number. */
    OSG::Real64    mStartTimeMs;     /**< The start time for the system in milliseconds. */
    OSG::UInt64    mFlushingRate;    /**< Number of frames between data flushes. */
    std::ofstream* mOutFile;  /**< The output file to use. */
};

#if defined(WIN32)
OSG_BASE_EXPIMP_TMPL
template class OSG_BASE_DLLMAPPING SingletonHolder<PerfMonitorBase>;
#endif

typedef SingletonHolder<PerfMonitorBase> PerfMonitor;

   
OSG_END_NAMESPACE

#endif

