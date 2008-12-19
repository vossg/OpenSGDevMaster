#include <OSGRequest.h>
#include <iostream>

OSG_USING_NAMESPACE
OSG_BEGIN_NAMESPACE

Request::Request()
   : mCompleted(false)
   , mPriority(100.0)
{;}

Request::~Request()
{;}

bool Request::isCompleted()
{ return mCompleted; }

float Request::getPriority()
{ return mPriority; }

void Request::setPriority(float val)
{ mPriority = val; }

bool Request::comparePriority(RequestPtr lhs, RequestPtr rhs)
{
   return (lhs->getPriority() < rhs->getPriority());
}

OSG_END_NAMESPACE
