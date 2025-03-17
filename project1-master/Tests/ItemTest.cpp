/**
 * @file ItemTest.cpp
 * @author Daniel Wills
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Item.h>


/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game) {}

    void Draw(wxGraphicsContext *gc) override {}
    bool HitTest(int x, int y) override { return false; }
    void Accept(ItemVisitor* visitor) override {};
};

TEST(ItemTest, Construct) {
    Game game;
    ItemMock item(&game);
}

TEST(ItemTest, GettersSetters){
    Game game;
    ItemMock item(&game);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);
}