#ifndef _OSG_MODEL_REQUEST_H_
#define _OSG_MODEL_REQUEST_H_

#include "OSGContribBackgroundLoaderDef.h"

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "OSGNode.h"

#include "OSGRequest.h"
#include "OSGChangeList.h"

OSG_BEGIN_NAMESPACE

OSG_GEN_MEMOBJPTR(ChangeList);

class ModelRequest;
typedef boost::shared_ptr<ModelRequest> ModelRequestPtr;
typedef boost::weak_ptr<ModelRequest> ModelRequestWeakPtr;   

/** A request for loading a model.
 * 
 * note: We hold on using refptrs, so all objects passed to us must have a
 * positive ref count. 
 */

class OSG_CONTRIBBACKGROUNDLOADER_DLLMAPPING ModelRequest : 
    public boost::enable_shared_from_this<ModelRequest>, public Request
{
  protected:

    ModelRequest(void);

  public:

    static ModelRequestPtr create(void)
    {
        return ModelRequestPtr(new ModelRequest);
    }

    virtual ~ModelRequest(void);

    ModelRequestPtr init(NodeRefPtr parent, const std::string &filename)
    {
        mParent     = parent;
        mFilename   = filename;
        pChangeList = ChangeList::create();

        return shared_from_this();
    }

    virtual std::string getDescription(      void              );
    virtual void        execute       (      void              );
    virtual void        sync          (      void              );

            void        setVerifyModel(      bool         bVal );
            void        setGraphOp    (const std::string &szVal);

  protected:
  
    // Note: We use RefPtrs so the code can still work
   //  even if the original nodes have been left to cleanup in the main
   //  program.  (ie. removed) 
   //
   NodeUnrecPtr          mParent;      /**< The node that we are supposed to
                                        *   load the model under.            */ 
   NodeUnrecPtr          mModel;       /**< The model that we loaded.        */
   std::string           mFilename;
   ChangeListRefPtr      pChangeList;

   bool                  bVerifyModel;
   std::string           szGraphOp;
};

OSG_END_NAMESPACE

#endif /*_OSG_MODEL_REQUEST_H_*/
