// Catch2 Headers
#include "catch2/catch_template_test_macros.hpp"
#include "catch2/catch_test_macros.hpp"

// pTK Headers
#include "ptk/util/Vec2.hpp"

TEMPLATE_TEST_CASE("Vec2 Constructors", "[Vec2][template]", int, uint8_t, uint16_t, uint32_t, float, double)
{
    // Testing Vec2 Constructors.

    SECTION("Vec2()")
    {
        pTK::Vec2<TestType> vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
    }

    SECTION("Vec2(T t_x, T t_y)")
    {
        pTK::Vec2<TestType> vec{1, 2};
        REQUIRE(vec.x == 1);
        REQUIRE(vec.y == 2);
    }
}

TEMPLATE_TEST_CASE("Vec2 Copy and Assignment", "[Vec2][template]", int, uint8_t, uint16_t, uint32_t, float, double)
{
    // Testing Vec2 Copy and Assignment.
    pTK::Vec2<TestType> vec{10, 20};

    SECTION("Copy")
    {
        pTK::Vec2<TestType> tmp = vec;
        REQUIRE(vec.x == tmp.x);
        REQUIRE(vec.y == tmp.y);
    }

    SECTION("Assignment")
    {
        pTK::Vec2<TestType> tmp;
        tmp = vec;
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }

    SECTION("Check if vec has changed")
    {
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }
}

TEMPLATE_TEST_CASE("Vec2 Comparison", "[Vec2][template]", int, uint8_t, uint16_t, uint32_t, float, double)
{
    // Testing Vec2 Comparison.
    pTK::Vec2<TestType> vec;
    pTK::Vec2<TestType> vec2;
    pTK::Vec2<TestType> vec3{1, 1};

    SECTION("Equal")
    {
        REQUIRE(vec == vec2);
        REQUIRE_FALSE(vec == vec3);
    }

    SECTION("Not Equal")
    {
        REQUIRE(vec != vec3);
        REQUIRE_FALSE(vec != vec2);
    }
}

TEMPLATE_TEST_CASE("Vec2 operators", "[Vec2][template]", int, unsigned int, float, double)
{
    // Testing Vec2 Operators.

    SECTION("operator+")
    {
        pTK::Vec2<TestType> vec;
        pTK::Vec2<TestType> check;
        pTK::Vec2<TestType> add{10, 20};

        check = vec + add;
        REQUIRE(check.x == 10);
        REQUIRE(check.y == 20);

        check = check + add;
        REQUIRE(check.x == 20);
        REQUIRE(check.y == 40);
    }

    SECTION("operator-")
    {
        if (typeid(TestType) != typeid(unsigned int))
        {
            pTK::Vec2<TestType> vec;
            pTK::Vec2<TestType> check;
            pTK::Vec2<TestType> sub{10, 20};

            check = vec - sub;
            REQUIRE(check.x == -10);
            REQUIRE(check.y == -20);

            check = check - sub;
            REQUIRE(check.x == -20);
            REQUIRE(check.y == -40);
        }
    }

    SECTION("operator*")
    {
        pTK::Vec2<TestType> vec;
        pTK::Vec2<TestType> check;
        pTK::Vec2<TestType> mul{10, 20};

        check = vec * mul;
        REQUIRE(check.x == 0);
        REQUIRE(check.y == 0);

        check = mul * mul;
        REQUIRE(check.x == 100);
        REQUIRE(check.y == 400);
    }

    SECTION("operator/")
    {
        pTK::Vec2<TestType> vec;
        pTK::Vec2<TestType> check;
        pTK::Vec2<TestType> div{10, 20};

        check = vec / div;
        REQUIRE(check.x == 0);
        REQUIRE(check.y == 0);

        check = div / div;
        REQUIRE(check.x == 1);
        REQUIRE(check.y == 1);

        pTK::Vec2<TestType> div2{1, 10};
        check = div / div2;
        REQUIRE(check.x == 10);
        REQUIRE(check.y == 2);
    }

    SECTION("operator+=")
    {
        pTK::Vec2<TestType> check;
        pTK::Vec2<TestType> add{10, 20};

        check += add;
        REQUIRE(check.x == 10);
        REQUIRE(check.y == 20);

        check += add;
        REQUIRE(check.x == 20);
        REQUIRE(check.y == 40);
    }
}

TEST_CASE("Vec2 Conversion")
{
    // Testing Vec2 Conversions.

    SECTION("int to float")
    {
        pTK::Vec2<int> Vi{10, 20};
        pTK::Vec2<float> Vf{Vi};

        REQUIRE(Vf.x == 10);
        REQUIRE(Vf.y == 20);
    }

    SECTION("float to int")
    {
        pTK::Vec2<float> Vf{10.4f, 20.9f};
        pTK::Vec2<int> Vi{Vf};

        REQUIRE(Vi.x == 10);
        REQUIRE(Vi.y == 20);
    }
}
