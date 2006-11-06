
#include <UnitTest++.h>

// Unit tests for MultiPool class

#include <vector>
#include <OpenSG/OSGLog.h>

#include <OpenSG/OSGMultiPool.h>

OSG_USING_NAMESPACE

// make the test noisy. Not like it's supposed ot be used, but good for
// debugging
#if 0
#define OUT(a)   FLOG(a)
#else
#define OUT(a)
#endif

SUITE(MultiPoolTests)
{

struct elBase
{
    elBase(void)
    {
        OUT(("elBase %p\n", this));
    }
    
    virtual ~elBase()
    {
        OUT(("~elBase %p\n", this));        
    }
    
  private:
    virtual void reset(void)
    {
        OUT(("elBase::reset %p\n", this));
        return;
    }
    
    friend class MultiPool<elBase>::TypeStore;
};

struct el1 : public elBase
{
    static el1 Proto;
    Int32 a;

    el1(void) : a(1) 
    {
        OUT(("el1 %p\n", this));
    }
    
    virtual ~el1()
    {
        OUT(("~el1 %p\n", this));
        a = -11;
    }
    
  private:
    virtual void reset(void)
    {
        OUT(("el1::reset %p\n", this));
        a = -1;
    }
    
    friend class MultiPool<elBase>::TypeStore;
};
el1 el1::Proto;

struct el2 : public elBase
{
    static el2 Proto;
    Int32 a;
    Int32 b;

    el2(void) : a(2), b(3) 
    {
        OUT(("el2 %p\n", this));
    }
    
    virtual ~el2()
    {
        OUT(("~el2 %p\n", this));
        a = -12;
        b = -13;
    }

  private:
    virtual void reset(void)
    {
        OUT(("el2::reset %p\n", this));
        a = -2;
        b = -3;
    }
    
    friend class MultiPool<elBase>::TypeStore;
};
el2 el2::Proto;


TEST(CreateAndInit)
{
    OUT(("CreateAndInit: start\n"));
    MultiPool<elBase> pool;
    
    el1 *val1 = pool.create(el1::Proto);   
    CHECK(val1 != 0);
    CHECK(val1->a == 1);
    
    el1 *val2 = pool.create(el1::Proto);
    CHECK(val2 != 0);
    CHECK(val1 != val2);
    CHECK(val2->a == 1);
    OUT(("CreateAndInit: end\n"));
}

TEST(ReuseDataAndCallReset)
{
    OUT(("ReuseDataAndCallReset: start\n"));
    MultiPool<elBase> pool;
    
    el1 *val1 = pool.create(el1::Proto);   
    CHECK(val1 != 0);
    CHECK(val1->a == 1);
    
    pool.freeAll();
    el1 *val2 = pool.create(el1::Proto);
    CHECK(val2 != 0);
    CHECK(val1 == val2);
    CHECK(val1->a == -1);
    OUT(("ReuseDataAndCallReset: end\n"));
}

TEST(CreateMoreThanOneBlock)
{
    OUT(("CreateMoreThanOneBlock: start\n"));
    MultiPool<elBase> pool;
    std::vector<el1 *> v;

    UInt16 cnt = MultiPool<elBase>::TypeStore::BLOCKSIZE * 4;
    
    for(UInt16 i = 0; i < cnt; ++i)
        v.push_back(pool.create(el1::Proto));
    
    for(UInt16 i = 0; i < cnt; ++i)
        CHECK(v[i]->a == 1);
    
    pool.freeAll();

    for(UInt16 i = 0; i < cnt; ++i)
        v.push_back(pool.create(el1::Proto));
    
    for(UInt16 i = 0; i < cnt; ++i)
        CHECK(v[i]->a == -1);
        
    OUT(("CreateMoreThanOneBlock: end\n"));
}

} // SUITE
