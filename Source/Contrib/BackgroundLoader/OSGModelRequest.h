#ifndef _OSG_MODEL_REQUEST_H_
#define _OSG_MODEL_REQUEST_H_

#include <OpenSG/OSGContribBackgroundLoaderDef.h>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <OpenSG/OSGNode.h>

#include <OpenSG/OSGRequest.h>

OSG_BEGIN_NAMESPACE

class ModelRequest;
typedef boost::shared_ptr<ModelRequest> ModelRequestPtr;
typedef boost::weak_ptr<ModelRequest> ModelRequestWeakPtr;   

/** A request for loading a model.
 * 
 * note: We hold on using refptrs, so all objects passed to us must have a positive ref count.
 */
class OSG_CONTRIBBACKGROUNDLOADER_DLLMAPPING ModelRequest : 
    public boost::enable_shared_from_this<ModelRequest>, public Request
{
protected:
   ModelRequest();

public:
   static ModelRequestPtr create()
   {
      return ModelRequestPtr(new ModelRequest);
   }

   virtual ~ModelRequest();

   ModelRequestPtr init(OSG::NodeRefPtr parent, const std::string& filename)
   {
      mParent = parent;
      mFilename = filename;

      return shared_from_this();
   }

   virtual std::string getDescription();
   virtual void execute();
   virtual void sync();

protected:
   // Note: We use RefPtrs so the code can still work
   //  even if the original nodes have been left to cleanup in the main program.  (ie. removed)
   //
   OSG::NodeRefPtr mParent;      /**< The node that we are supposed to load the model under. */
   OSG::NodeRefPtr mModel;       /**< The model that we loaded. */
   std::string     mFilename;
};

OSG_END_NAMESPACE

#endif /*_OSG_MODEL_REQUEST_H_*/
