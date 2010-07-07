#include "OSGFileIOUtils.h"
#include "OSGAction.h"
#include "OSGNameAttachment.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// ------------------------------------------------

FileIONodeFinder::FileIONodeFinder(void)
{
}

void FileIONodeFinder::traverse(NodeUnrecPtr root)
{
    _FoundJoints     .clear();
    _FoundNamedJoints.clear();
    _FoundNamedNodes .clear();
    _FoundNodes      .clear();

    OSG::traverse(root, boost::bind(&FileIONodeFinder::check,
                                    this, _1));
}

Action::ResultE FileIONodeFinder::check(Node * &node)
{
    if(OSG::getName(node) && OSG::getName(node) == _SearchName)
    {
        _FoundNamedNodes.push_back(node);
    }

    return Action::Continue;        
}

const std::vector<Node *> &FileIONodeFinder::getFoundNodes(void) const
{
    return _FoundNodes;
}

const std::vector<Node *> &FileIONodeFinder::getFoundNamedNodes(void) const
{
    return _FoundNamedNodes;
}

const std::vector<Node *> &FileIONodeFinder::getFoundJoints(void) const
{
    return _FoundJoints;
}

const std::vector<Node *> &FileIONodeFinder::getFoundNamedJoints(void) const
{
    return _FoundNamedJoints;
}
void FileIONodeFinder::setSearchName(std::string nodeName)
{
    _SearchName = nodeName;
}

OSG_END_NAMESPACE
