/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <UnitTest++.h>

// Unit tests for vec classes

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGBaseInitFunctions.h"
#include "OSGCondVar.h"
#include "OSGLock.h"
#include "OSGLog.h"
#include "OSGBaseThread.h"

OSG_USING_NAMESPACE

struct condition_test_data
{
   condition_test_data()
      : notified(0)
      , awoken(0)
   {
      mCondVar = OSG::CondVar::get(NULL);
      mOutputLock = OSG::Lock::get(NULL);
   }

   OSG::CondVar* mCondVar;
   OSG::Lock* mOutputLock;
   int notified;
   int awoken;
};

//#define OSG_CONDVAR_DEBUG

#ifdef OSG_CONDVAR_DEBUG
#  define OUTPUT_BEGIN(data)                    \
      (data)->mOutputLock->acquire();           \
      PWARNING << OSG::BaseThread::getCurrent()->getCName()
#  define OUTPUT_END(data)                      \
      std::endl;                                \
      (data)->mOutputLock->release();
#endif

void condition_test_thread(void* param)
{
   condition_test_data* data = static_cast<condition_test_data*>(param);

#ifdef OSG_CONDVAR_DEBUG
   OUTPUT_BEGIN(data) << ": Locking condvar" << OUTPUT_END(data);
#endif
   data->mCondVar->acquire();
#ifdef OSG_CONDVAR_DEBUG
   OUTPUT_BEGIN(data) << ": Locked condvar" << OUTPUT_END(data);
#endif

   try
   {
      while (!(data->notified > 0))
      {
#ifdef OSG_CONDVAR_DEBUG
         OUTPUT_BEGIN(data) << ": waiting condvar notified: "
            << data->notified << OUTPUT_END(data);
#endif
         data->mCondVar->wait();
#ifdef OSG_CONDVAR_DEBUG
         OUTPUT_BEGIN(data) << ": waited condvar notified: "
            << data->notified << OUTPUT_END(data);
#endif
      }
      data->awoken++;
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(data) << ": awoken: " << data->awoken << OUTPUT_END(data);

      OUTPUT_BEGIN(data) << ": releasing condvar" << OUTPUT_END(data);
#endif
      data->mCondVar->release();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(data) << ": released condvar" << OUTPUT_END(data);
#endif
   }
   catch(...)
   {
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(data) << ": releasing condvar" << OUTPUT_END(data);
#endif
      data->mCondVar->release();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(data) << ": released condvar" << OUTPUT_END(data);
#endif
      throw;
   }
}

SUITE(CondVarTests)
{

TEST(TestSignal)
{
   condition_test_data data;

   OSG::BaseThread* thread = OSG::BaseThread::get(NULL);
   thread->runFunction(&condition_test_thread, &data);
   OSG::osgSleep(250);
   {
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": Locking condvar" << OUTPUT_END(&data);
#endif
      data.mCondVar->acquire();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": Locked condvar" << OUTPUT_END(&data);
#endif

      data.notified++;
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": notified: " << data.notified << OUTPUT_END(&data);

      OUTPUT_BEGIN(&data) << ": signaling condvar" << OUTPUT_END(&data);
#endif
      data.mCondVar->signal();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": signaled condvar" << OUTPUT_END(&data);

      OUTPUT_BEGIN(&data) << ": releasing condvar" << OUTPUT_END(&data);
#endif
      data.mCondVar->release();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": released condvar" << OUTPUT_END(&data);
#endif
   }

   OSG::BaseThread::join(thread);
   OSG_ASSERT(1 == data.awoken);
}

TEST(TestBroadcast)
{
   const int NUMTHREADS = 5;
   std::vector<OSG::BaseThread*> threads;
   condition_test_data data;

   for (int i = 0; i < NUMTHREADS; ++i)
   {
      OSG::BaseThread* thread = OSG::BaseThread::get(NULL);
      thread->runFunction(&condition_test_thread, &data);
      threads.push_back(thread);
   }

   OSG::osgSleep(250);
   {
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": Locking condvar" << OUTPUT_END(&data);
#endif
      data.mCondVar->acquire();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": Locked condvar" << OUTPUT_END(&data);
#endif

      data.notified++;
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": notified: " << data.notified << OUTPUT_END(&data);

      OUTPUT_BEGIN(&data) << ": broadcast condvar" << OUTPUT_END(&data);
#endif
      data.mCondVar->broadcast();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": broadcast condvar done" << OUTPUT_END(&data);

      OUTPUT_BEGIN(&data) << ": releasing condvar" << OUTPUT_END(&data);
#endif
      data.mCondVar->release();
#ifdef OSG_CONDVAR_DEBUG
      OUTPUT_BEGIN(&data) << ": released condvar" << OUTPUT_END(&data);
#endif
   }

   for (int i = 0; i < NUMTHREADS; ++i)
   {
      OSG::BaseThread::join(threads[i]);
   }
   OSG_ASSERT(data.awoken == NUMTHREADS);
}

} // SUITE
