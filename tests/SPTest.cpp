#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ptk/util/SP.hpp"

class Base
{
public:
    Base() : i{0} {}
    Base(int in) : i{in} {}
    virtual ~Base() = default;
    
    virtual std::string str() const
    {
        return "Base";
    }
    
    int i;
};

class Derived : public Base
{
public:
    Derived() = default;
    ~Derived() = default;
    
    std::string str() const override
    {
        return "Derived";
    }
};

TEST_CASE("Constructor")
{
    SECTION("SP()")
    {
        pTK::SP<Base> ptr;
        REQUIRE(ptr.get() == nullptr);
    }
    
    SECTION("SP(T*)")
    {
        pTK::SP<Base> ptr(new Base());
        REQUIRE(ptr.get() != nullptr);
        REQUIRE(ptr->str() == "Base");
        REQUIRE(ptr->i == 0);
    }
}

TEST_CASE("reset")
{
    SECTION("reset()")
    {
        pTK::SP<Base> ptr(new Base(5));
        REQUIRE(ptr.get() != nullptr);
        REQUIRE(ptr->i == 5);
        ptr.reset();
        REQUIRE(ptr.get() == nullptr);
    }
    
    SECTION("reset(T*)")
    {
        pTK::SP<Base> ptr(new Base(5));
        REQUIRE(ptr.get() != nullptr);
        REQUIRE(ptr->i == 5);
        ptr.reset(new Base(10));
        REQUIRE(ptr.get() != nullptr);
        REQUIRE(ptr->i == 10);
    }
}

TEST_CASE("Polymorphism")
{
    pTK::SP<Base> ptr;
    ptr = new Base(10);
    ptr = new Derived();
    pTK::SP<Derived> der(new Derived());
    pTK::SP<Base> ptr2(der);
    pTK::SP<Base> test(new Derived());
    REQUIRE(ptr2->str() == "Derived");
    REQUIRE(ptr->str() == "Derived");
    REQUIRE(test->str() == "Derived");
}

TEST_CASE("Copy and Assignment")
{
    // Testing Widget Copy and Assignment.
    pTK::SP<Base> ptr(new Base(5));
    
    SECTION("Copy")
    {
        pTK::SP<Base> tmp = ptr;
        REQUIRE(ptr.get() != nullptr);
        REQUIRE(ptr->str() == "Base");
        REQUIRE(ptr->i == 5);
    }
    
    SECTION("Assignment")
    {
        pTK::SP<Base> tmp;
        tmp = ptr;
        REQUIRE(ptr.get() != nullptr);
        REQUIRE(ptr->str() == "Base");
        REQUIRE(ptr->i == 5);
    }
}
