#ifndef _OSG_REQUEST_H_
#define _OSG_REQUEST_H_

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGContribBackgroundLoaderDef.h>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <iostream>


OSG_BEGIN_NAMESPACE

class Request;
typedef boost::shared_ptr<Request> RequestPtr;
typedef boost::weak_ptr<Request> RequestWeakPtr;   

/** A request to be processed by the background loader.
 */
class OSG_CONTRIBBACKGROUNDLOADER_DLLMAPPING Request
{
protected:
   Request();

public:
   virtual ~Request();

   /** Return a text description of the request.
    * This could be used in a user interface or debug output to provide 
    * a user understandable description.
    */
   virtual std::string getDescription()
   { return std::string("Base Request"); }

   /** Called when it is time to execute the request and "do" something.
    * Ex: load a file.
    */
   virtual void execute() = 0;

   /** Called in the main thread when it is time to sync up
    * and finish the processing.  ex: add child node.
    */
   virtual void sync() = 0;

   /** Return true if the request has been completed. */
   bool isCompleted();

   float getPriority();

   void setPriority(float val);

   static bool comparePriority(RequestPtr lhs, RequestPtr rhs);

   friend class BackgroundLoaderBase;
protected:
   bool   mCompleted;      /**< True once the request has been completed and synced. */
   float  mPriority;       /**< Priority for this request.  lower numbers are higher priority. */
};

OSG_END_NAMESPACE

#endif /*_REQUEST_H_*/
