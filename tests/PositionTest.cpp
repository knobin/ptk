#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ptk/util/Position.hpp"

TEST_CASE("Constructors")
{
    // Testing Constructors with correct data.
    float cX = 50.0f;
    float cY = 300.0f;
    
    SECTION("Position()")
    {
        pTK::Position pos;
        
        REQUIRE(pos.getX() == 0.0f);
        REQUIRE(pos.getY() == 0.0f);
    }
    
    SECTION("Position(float width, float height)")
    {
        pTK::Position pos{cX, cY};
        
        REQUIRE(pos.getX() == cX);
        REQUIRE(pos.getY() == cY);
    }
}

TEST_CASE("Getters and Setters")
{
    // Testing Getters and Setters.
    float cX = 55.0f;
    float cY = 350.0f;
    
    SECTION("setX(float x)")
    {
        pTK::Position pos;
        pos.setX(cX);
        REQUIRE(pos.getX() == cX);
    }
    
    SECTION("setY(float y)")
    {
        pTK::Position pos;
        pos.setY(cY);
        REQUIRE(pos.getY() == cY);
    }
    
    SECTION("setPosition(float x, float y)")
    {
        pTK::Position pos;
        pos.setPosition(cX, cY);
        REQUIRE(pos.getX() == cX);
        REQUIRE(pos.getY() == cY);
    }
    
    SECTION("setPosition(const Position& pos)")
    {
        pTK::Position pos;
        pos.setPosition(cX, cY);
        REQUIRE(pos.getX() == cX);
        REQUIRE(pos.getY() == cY);
    }
}

TEST_CASE("Copy and Assignment")
{
    // Testing Rectangle Copy and Assignment.
    float cX = 949.0f;
    float cY = 84.0f;
    
    pTK::Position pos;
    pos.setPosition(cX, cY);
    
    SECTION("Copy")
    {
        pTK::Position tmp = pos;
        REQUIRE(tmp.getX() == cX);
        REQUIRE(tmp.getY() == cY);
    }
    
    SECTION("Assignment")
    {
        pTK::Position tmp;
        tmp = pos;
        REQUIRE(tmp.getX() == cX);
        REQUIRE(tmp.getY() == cY);
    }
}

TEST_CASE ("Comparison")
{
    // Testing Transformable Comparison.
    float cX = 57.0f;
    float cY = 384.0f;
    
    pTK::Position pos;
    pos.setPosition(cX, cY);
    
    pTK::Position p1 = pos;
    
    pTK::Position p2;
    p2.setY(cY);
    
    pTK::Position p3;
    p3.setX(cX);
    
    SECTION("Equal")
    {
        REQUIRE(pos == p1);
        REQUIRE_FALSE(pos == p2);
        REQUIRE_FALSE(pos == p3);
    }
    
    SECTION("Not Equal")
    {
        REQUIRE(pos != p2);
        REQUIRE(pos != p3);
        REQUIRE(p2 != p3);
        REQUIRE_FALSE(pos != p1);
    }
}



