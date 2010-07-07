#ifndef _OSGFILEIOUTILS_H_
#define _OSGFILEIOUTILS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGNode.h"
#include "OSGAction.h"
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING FileIONodeFinder
{
  public:

    FileIONodeFinder(void);

    void traverse(NodeUnrecPtr root);

    const std::vector<Node *> &getFoundNodes      (void) const;
    const std::vector<Node *> &getFoundNamedNodes (void) const;
    const std::vector<Node *> &getFoundJoints     (void) const;
    const std::vector<Node *> &getFoundNamedJoints(void) const;

    void setSearchName(std::string nodeName);

  private:

    Action::ResultE check(Node * &node);

    std::vector<Node *> _FoundJoints;
    std::vector<Node *> _FoundNamedJoints;
    std::vector<Node *> _FoundNamedNodes;
    std::vector<Node *> _FoundNodes;
    std::string         _SearchName;
};


OSG_END_NAMESPACE

#endif /* _OSGFILEIOUTILS_H_ */
