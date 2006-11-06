
#include <UnitTest++.h>

// Unit tests for vec classes

#include <OpenSG/OSGVector.h>

OSG_USING_NAMESPACE

SUITE(Vector)
{

TEST(InstantiateAllVectorTypes)
{
    Vec1f v1f;
    Vec2f v2f;
    Vec3f v3f;
    Vec4f v4f;
    Vec1b v1b;
    Vec2b v2b;
    Vec3b v3b;
    Vec4b v4b;
    
    CHECK(true);
}



TEST(InstantiateAllPointTypes)
{
    Pnt1f p1f;
    Pnt2f p2f;
    Pnt3f p3f;
    Pnt4f p4f;
    Pnt1b p1b;
    Pnt2b p2b;
    Pnt3b p3b;
    Pnt4b p4b;
    
    CHECK(true);
}

} // SUITE
