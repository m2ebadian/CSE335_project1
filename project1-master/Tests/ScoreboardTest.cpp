/**
 * @file ScoreboardTest.cpp
 * @author Tyler Nguyen
 *
 * This file contains tests for the Scoreboard class.
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Game.h>
#include <Scoreboard.h>

using namespace std;

class ScoreboardTest : public ::testing::Test
{
};

// Test the Scoreboard constructor
TEST_F(ScoreboardTest, Constructor)
{
 Game* game;
 wstring goal = L"Goal";
 auto scoreboard = std::make_shared<Scoreboard>(game, 700, 40, 10, -5, 0, goal);

 // Assert the starting level score is 0
 ASSERT_EQ(scoreboard->GetLevelScore(), 0);

 // Assert the starting game score is 0 as well.
 ASSERT_EQ(scoreboard->GetGameScore(), 0);
}

TEST_F(ScoreboardTest, UpdateScore)
{
 // Create a scoreboard
 Game* game;
 wstring goal = L"Goal";
 auto scoreboard = std::make_shared<Scoreboard>(game, 700, 40, 10, -5,0, goal);

 // Increment the score if good kick
 scoreboard->UpdateLevelScore(true, true);
 ASSERT_EQ(scoreboard->GetLevelScore(), 10);

 // Increment score if not kicked, and it was correct choice
 scoreboard->UpdateLevelScore(false, false);
 scoreboard->UpdateLevelScore(false, false);
 scoreboard->UpdateLevelScore(false, false);

 // Score should be 40
 ASSERT_EQ(scoreboard->GetLevelScore(), 40);

 // Decrease score if it was a bad kick
 scoreboard->UpdateLevelScore(true, false);

 ASSERT_EQ(scoreboard->GetLevelScore(), 35);

 // Decrease score if item should have been kicked
 scoreboard->UpdateLevelScore(false, true);

 ASSERT_EQ(scoreboard->GetLevelScore(), 30);
}