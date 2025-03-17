/**
 * @file LoadTest.cpp
 * @author Conner O'Sullivan
 */
#include <pch.h>
#include <gtest/gtest.h>
#include <wx/filename.h>
#include <regex>
#include <string>
#include <fstream>
#include <Game.h>
#include <ItemCounter.h>


using namespace std;

class LoadTest : public ::testing::Test
{

};

TEST_F(LoadTest, LoadLevel)
{
    // Path to the level file
    wxString file = L"resources/levels/level1.xml";

    // Create a game and load the level
    Game game;
    game.LoadLevel(file);

    // Create an ItemCounter Visitor and accept it in the game
    ItemCounter counter;
    game.Accept(&counter);

    int numSensors = counter.GetNumSensors();
    int numSpartys = counter.GetNumSpartys();
    int numBeams = counter.GetNumBeams();
    int numProducts = counter.GetNumProducts();
    int numConveyors = counter.GetNumConveyors();
    int numScoreboards = counter.GetNumScoreboards();
    int numLogicGate = counter.GetNumLogicGates();

    // Verify the total number of items
    int totalItems = numSensors + numSpartys + numBeams + numProducts + numConveyors + numScoreboards + numLogicGate;

    ASSERT_EQ(10, totalItems) << L"Total number of items loaded";
    ASSERT_EQ(2, numLogicGate) << L"Total number of logic gates loaded";
    ASSERT_EQ(0, numSensors) << L"Number of sensors loaded";
    ASSERT_EQ(1, numSpartys) << L"Number of spartys loaded";
    ASSERT_EQ(1, numBeams) << L"Number of beams loaded";
    ASSERT_EQ(4, numProducts) << L"Number of products loaded";
    ASSERT_EQ(1, numConveyors) << L"Number of conveyors loaded";
    ASSERT_EQ(1, numScoreboards) << L"Number of scoreboards loaded";
}
