/**
 * @file GameTest.cpp
 * @author Conner O'Sullivan
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Item.h>

// To test for file save
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <Sparty.h>
#include <Sensor.h>
#include <Beam.h>
#include <Product.h>
#include <Conveyor.h>
#include <Scoreboard.h>
#include <ItemVisitor.h>
#include <SRLogicGate.h>
#include <GameView.h>


using namespace std;

class GameTest : public ::testing::Test
{
protected:
    /**
     * Create a path to a place to put temp files
     * @author Tyler Nguyen
     */
    wxString TempPath()
    {
        auto path = wxFileName::GetTempDir() + L"/game";
        if (!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }
        return path;
    }

    /**
     * Read a file into a wstring and return it
     * @author Tyler Nguyen
     * @param filename Name of the file to read
     * @return File contents
     */
    wstring ReadFile(const wxString& filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());
        return str;
    }
};

TEST_F(GameTest, Construct)
{
    Game game;
}

TEST_F(GameTest, VirtualPrecisionTest)
{
    // spawn in some moveable items
    Game game;
    auto srLogicGate = make_shared<SRLogicGate>(&game);
    srLogicGate->SetLocation(500, 500);
    game.Add(srLogicGate);

    ASSERT_TRUE(srLogicGate->HitTest(500,500));

    // Now resize the window
    // Now resize the window
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Test Frame");
    GameView gameView;
    gameView.Initialize(frame);
    gameView.SetSize(800, 600);

    int vX = game.GetVirtualPixelsX(500);
    int vY = game.GetVirtualPixelsY(500);
    // click on them again and see if they are hit.
    ASSERT_TRUE(srLogicGate->HitTest(vX,vY));

    // destroy the frame
    frame->Destroy();
}

TEST_F(GameTest, HitTest)
{
    //CREATE A HIT-TEST TEST
}

// Define the TestVisitor class
class TestVisitor : public ItemVisitor
{
public:
    void VisitSparty(Sparty* sparty) override { mNumSpartys++; }
    void VisitSensor(Sensor* sensor) override { mNumSensors++; }
    void VisitBeam(Beam* beam) override { mNumBeams++; }
    void VisitProduct(Product* product) override { mNumProducts++; }
    void VisitConveyor(Conveyor* conveyor) override { mNumConveyors++; }
    void VisitScoreboard(Scoreboard* scoreboard) override { mNumScoreboards++; }

    int mNumSpartys = 0;
    int mNumSensors = 0;
    int mNumBeams = 0;
    int mNumProducts = 0;
    int mNumConveyors = 0;
    int mNumScoreboards = 0;
};

// Test case for the visitor pattern
TEST_F(GameTest, Visitor)
{
    // Construct a game object
    Game game;

    // Add some items of each type with nonimportant starting values
    auto item1 = std::make_shared<Sparty>(&game, 180.0, wxPoint(100, 200), 2.0, 5.0);
    auto item2 = std::make_shared<Sensor>(&game, std::vector<std::wstring>{});
    auto item3 = std::make_shared<Beam>(&game, 10);
    auto item4 = std::make_shared<Product>(&game, Product::Properties::Square, Product::Properties::Green,
                                           Product::Properties::Izzo, false);
    auto item5 = std::make_shared<Conveyor>(&game, 5, 100.0, wxPoint(300, 400));
    std::wstring emptyGoal;
    auto item6 = std::make_shared<Scoreboard>(&game, 0, 0, 0, 0,0, emptyGoal);

    game.Add(item1);
    game.Add(item2);
    game.Add(item3);
    game.Add(item4);
    game.Add(item5);
    game.Add(item6);

    // Create a TestVisitor and accept it in the game
    TestVisitor visitor;
    game.Accept(&visitor);

    // Verify the counts of each item type
    ASSERT_EQ(1, visitor.mNumSpartys) << L"Visitor number of Spartys";
    ASSERT_EQ(1, visitor.mNumSensors) << L"Visitor number of Sensors";
    ASSERT_EQ(1, visitor.mNumBeams) << L"Visitor number of Beams";
    ASSERT_EQ(1, visitor.mNumProducts) << L"Visitor number of Products";
    ASSERT_EQ(1, visitor.mNumConveyors) << L"Visitor number of Conveyors";
    ASSERT_EQ(1, visitor.mNumScoreboards) << L"Visitor number of Scoreboards";

    // New blank game
    Game game2;
    TestVisitor visitor2;
    game2.Accept(&visitor2);

    // Verify the counts of each item type
    ASSERT_EQ(0, visitor2.mNumSpartys) << L"Visitor number of Spartys";
    ASSERT_EQ(0, visitor2.mNumSensors) << L"Visitor number of Sensors";
    ASSERT_EQ(0, visitor2.mNumBeams) << L"Visitor number of Beams";
    ASSERT_EQ(0, visitor2.mNumProducts) << L"Visitor number of Products";
    ASSERT_EQ(0, visitor2.mNumConveyors) << L"Visitor number of Conveyors";
    ASSERT_EQ(0, visitor2.mNumScoreboards) << L"Visitor number of Scoreboards";
}
