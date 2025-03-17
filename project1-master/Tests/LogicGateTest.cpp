/**
 * @file LogicGateTest.cpp
 * @author Daniel Wills
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <OrLogicGate.h>
#include <ItemVisitor.h>
#include <SRLogicGate.h>

using namespace std;

class LogicGateTest : public ::testing::Test
{
};



TEST_F(LogicGateTest, OrGateHitTest)
{
 Game game;

 auto logicGate1 = std::make_shared<OrLogicGate>(&game);

 logicGate1->SetLocation(500, 500);
 game.Add(logicGate1);

 // Test center
 ASSERT_TRUE(logicGate1->HitTest(500, 500));

 // Test width
 ASSERT_TRUE(logicGate1->HitTest(500+((logicGate1->GetWidth())/2), 500)); // only right side, since Or logic gate is asymmetrical

 // Test height
 ASSERT_TRUE(logicGate1->HitTest(500+((logicGate1->GetHeight())/2), 500)); // above center
 ASSERT_TRUE(logicGate1->HitTest(500-((logicGate1->GetHeight())/2), 500)); // below center

 // Test on the outside where the hit should not be detected
 ASSERT_FALSE(logicGate1->HitTest(500+logicGate1->GetWidth(), 500+logicGate1->GetHeight()));
}

TEST_F(LogicGateTest, srGateHitTest)
{
 Game game;

 auto logicGate1 = std::make_shared<SRLogicGate>(&game);

 logicGate1->SetLocation(500, 500);
 game.Add(logicGate1);

 // Test center
 ASSERT_TRUE(logicGate1->HitTest(500, 500));

 // Test width
 ASSERT_TRUE(logicGate1->HitTest(500+((logicGate1->GetWidth())/4), 500)); // right side
 ASSERT_TRUE(logicGate1->HitTest(500-((logicGate1->GetWidth())/4), 500)); // left side

 // Test height
 ASSERT_TRUE(logicGate1->HitTest(500+((logicGate1->GetHeight())/4), 500)); // above center
 ASSERT_TRUE(logicGate1->HitTest(500-((logicGate1->GetHeight())/4), 500)); // below center

 // Test on the outside where the hit should not be detected
 ASSERT_FALSE(logicGate1->HitTest(500+logicGate1->GetWidth(), 500+logicGate1->GetHeight()));
}