/**
 * @file Game.cpp
 * @author Tyler Nguyen, Daniel Wills
 */
#include "pch.h"
#include "Game.h"
#include "Conveyor.h"
#include "Item.h" ///< this is for testing example items
#include "ItemExample.h" ///< this is for testing example items
#include "ItemGrabbableExample.h"
#include "Sparty.h"
#include "Product.h"
#include "Scoreboard.h"
#include "Banner.h"
#include "LogicGate.h"
#include "LevelLoader.h"

// Visitors
#include "UpdateVisitor.h"
#include "BeamDetectionVisitor.h"
#include "ScoreboardVisitor.h"
#include "ProductResetVisitor.h"
#include "SensorDetectionVisitor.h"
#include "SpartyProductVisitor.h"

#include <wx/xml/xml.h>
#include <memory>

#include "StopConveyorVisitor.h"

using namespace std;

/// Initial item X location
const int InitialX = 600;

/// Initial item Y location
const int InitialY = 600;

/// Last level
const int LastLevelNum = 8;

/// Load delay used for levels
const double LevelLoadDelay = 3.0;

// This is for the Banner
/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(24, 69, 59);

/// Color to draw a rectangle enclosing the level notice text @return wxColour of the Banner color
wxColour LevelNoticeBackgrounds(255, 255, 255, 200);

/// Padding to add to the left and right side of the level
/// notice background rectangle in virtual pixels
const double LevelNoticePadding = 20;

/// Width of the level notice Box
const double LevelNoticeWidth = 820;

/// constant that makes banner look centered.
const double eighteenth = 0.18;


/**
 * Game Constructor
 */
Game::Game()
{
    LoadLevel(L"resources/levels/level1.xml");
    /*
     * NOTE: COMMENTED THIS OUT SO TESTING WILL WORK OTHERWISE IT WILL LOAD INCORRECTLY AS WHEN THE GAME IS GENERATED
     * A BUNCH OF EXTRA ITEMS WILL BE IN IT.
    // GENERAL NOTE: We'll have to load in the values (x,y, height, etc. with XML so the hard coding is temporary)

    // NOTE: Uses a custom Draw funciton. Might want to refactor later to avoid redundant code but works for now!
    shared_ptr<Sparty> sparty = make_shared<Sparty>(this, 300, wxPoint(800, 500), 0.25, 1000);
    Add(sparty);
    sparty->SetLocation(345, 390);

    // Vector of outputs for the sensor
    std::vector<std::wstring> sensorOutputs = {L"red", L"green", L"izzo"};
    // Create sensor with the output panels
    shared_ptr<Sensor> sensor = make_shared<Sensor>(this, sensorOutputs);
    // Add the sensor to the game
    Add(sensor);
    // Set the location of the sensor
    sensor->SetLocation(150, 450);

    // NOTE: Uses a custom Draw funciton. Might want to refactor later to avoid redundant code but works for now!
    shared_ptr<Conveyor> conveyor = make_shared<Conveyor>(this, 100, 900, wxPoint(60, -390));
    Add(conveyor);
    conveyor->SetLocation(150, 450);

    // Create products and add them to the conveyor
    shared_ptr<Product> product1 = make_shared<Product>(this, Product::Properties::Square, Product::Properties::Green,
                                                        Product::Properties::Izzo, false);
    Add(product1);
    product1->SetLocation(150, 350);


    shared_ptr<Product> product2 = make_shared<Product>(this, Product::Properties::Square, Product::Properties::Red,
                                                        Product::Properties::None, true);
    Add(product2);
    product2->SetLocation(150, 200);


    shared_ptr<Product> product3 = make_shared<Product>(this, Product::Properties::Diamond, Product::Properties::Blue,
                                                        Product::Properties::None, true);
    Add(product3);
    product3->SetLocation(150, 50);

    shared_ptr<Beam> beam = make_shared<Beam>(this, -185); // Assuming -185 is the sender offset
    Add(beam);
    beam->SetLocation(242, 437);


    shared_ptr<Item> itemExample = make_shared<ItemExample>(this); ///< this is for testing example items
    Add(itemExample); ///< this is for testing example items
    itemExample->SetLocation(242, 50);

    shared_ptr<Item> itemGrabbableExample = make_shared<ItemGrabbableExample>(this);
    ///< this is for testing example items
    Add(itemGrabbableExample); ///< this is for testing example items
    itemGrabbableExample->SetLocation(500, 500); ///< this is for testing example items
    */
}

/**
 * Draw the Game
 * @param graphics The graphics context to draw on
 * @param width The width of the window
 * @param height The height of the window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext>& graphics, int width, int height)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = mLevelWidth;
    int pixelHeight = mLevelHeight;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    // Makes it so stuff doesn't appear out of bounds (sets the clipping region to the visible area)
    graphics->Clip(0, 0, pixelWidth, pixelHeight);

    //
    // Draw in virtual pixels on the graphics context
    //

    // Set the background color to green
    wxBrush background(wxColour(230, 255, 230, 255));
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);

    // Drawing code goes here
    for (auto& item : mItems)
    {
        item->Draw(graphics.get());
    }

    // Draw the end banner
    if (mHasLevelEnded)
    {
        DrawEndBanner(graphics.get());
    }

    graphics->PopState();
}

/**
 * Add an item to the Game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
    item->SetShowControlOutputPins(mShowControlPoints); //Sets new gates with the correct state
}

/**
 * Deletes an item from mItems and pushes it to the back of the vector.
 * This allows the item to be drawn last, meaning it is displayed on top of
 * everything else.
 * @param item std::shared_ptr<Item>, a shared pointer of type item.
*/
void Game::BringItemToFront(Item* item)
{
    // Find the shared_ptr corresponding to rawPtr
    auto loc = std::find_if(mItems.begin(), mItems.end(),
                            [item](std::shared_ptr<Item> ptr)
                            {
                                return ptr.get() == item;
                            });
    auto itemPtr = *loc;
    if (loc != end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(itemPtr);
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<IDraggable> Game::HitTest(double x, double y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        // Did we click on something contained in the drawable?
        auto draggable = (*i)->HitDraggable(x, y);
        if (draggable != nullptr)
        {
            return draggable;
        }

        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return nullptr;
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTestDefault(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }
    return nullptr;
}

/**
 * Load the Level from an XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the level from.
 */
void Game::LoadLevel(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load level file");
        return;
    }

    ClearLevel();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Parse level size
    wxString sizeStr = root->GetAttribute(L"size", L"1150,800");
    wxArrayString sizeParts = wxSplit(sizeStr, L',');
    if (sizeParts.size() == 2)
    {
        // Convert the pin values to doubles
        sizeParts[0].ToInt(&mLevelWidth);
        sizeParts[1].ToInt(&mLevelHeight);
    }

    LevelLoader loader(this);
    loader.Load(filename);

    // Extract level number from filename --> This is for displaying the banner
    const wxString levelStr = filename.BeforeLast('.').AfterLast('l'); //
    long levelNum = 0;
    levelStr.ToLong(&levelNum);
    // Create and display banner
    std::wstring text = L"Level " + std::to_wstring(levelNum) + L" Begin";
    auto banner = make_shared<Banner>(this, text);
    Add(banner);
}

/**
 * Clear the Game data.
 *
 * Deletes all known items in the Game.
 */
void Game::ClearLevel()
{
    mItems.clear();
}

//**
// * Handle the virtual precision mouse down event
// * @param x X location in pixels
// * @param y Y location in pixels
// */
/*
shared_ptr<Item> Game::OnLeftDown(int x, int y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    // Perform actions with the new virtual coordinates
    auto item = HitTest(oX, oY);
    if (item != nullptr)
    {
        // We have selected an item, move it to the end of the list of items
        BringItemToFront(item);
        return item;
    }
    return nullptr;
}
*/

/**
 * Draw the 'Level Complete' Banner at the end of the game
 * @param gc The graphics context to draw on
 */
void Game::DrawEndBanner(wxGraphicsContext* gc)
{
    if (mVisible)
    {
        // Set the brush and pen for the background rectangle
        gc->SetBrush(wxBrush(LevelNoticeBackgrounds, wxBRUSHSTYLE_SOLID));
        gc->SetPen(wxPen(LevelNoticeBackgrounds, 0, wxPENSTYLE_TRANSPARENT));

        // Figure out location to draw text
        int centerX = mLevelWidth * eighteenth;
        int centerY = (mLevelHeight / 2) - (NoticeSize / 2);

        // Figure out the size of the rectangle
        gc->DrawRectangle(centerX - LevelNoticePadding, centerY - (LevelNoticePadding / 2),
                                LevelNoticeWidth,
                                NoticeSize + LevelNoticePadding + 10);

        // Set font and font size for text
        auto font = gc->CreateFont(NoticeSize, L"Arial", wxFONTFLAG_BOLD, LevelNoticeColor);
        gc->SetFont(font);
        gc->DrawText("Level Complete!", centerX, centerY);
    }
}

/**
 * Try to catch an input pin at the new location of the wire end
 *
 * @param pinOutput Pin Output we are trying to catch from
 * @param lineEnd The line end point
 */
void Game::TryToCatch(PinOutput* pinOutput, wxPoint lineEnd)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->Catch(pinOutput, lineEnd))
        {
            return;
        }
    }
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto& item : mItems)
    {
        if (item != nullptr)
        {
            item->Accept(visitor); // Each item accepts the visitor only once
        }
    }
}


/**
 * Remove an item from the game
 * @param item The item to remove
 */
void Game::RemoveItem(Item* item)
{
    //auto loc = find(std::begin(mItems), std::end(mItems), item);
    //if (loc != std::end(mItems))
    //{
    //    mItems.erase(loc);
    //}
}

/**
 * Update the game
 * @param elapsed
 */
void Game::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }

    // Create the BeamDetectionVisitor
    BeamDetectionVisitor beamVisitor;

    // Apply the visitor to all items
    for (auto& item : mItems)
    {
        item->Accept(&beamVisitor); // Each item accepts the visitor
    }
    if ((!mWasItemHitThisCycle) && (mWasItemPreviouslyHit))
    {
        mCurrentProduct->HasLeftBeam();
        mWasItemPreviouslyHit = false;
    }
    mWasItemHitThisCycle = false;

    // Update the state of the beam after all visits
    beamVisitor.UpdateBeamState();

    // Create the BeamDetectionVisitor
    SensorDetectionVisitor sensorVisitor;

    // Apply the visitor to all items
    for (auto& item : mItems)
    {
        item->Accept(&sensorVisitor); // Each item accepts the visitor
    }

    // Update the state of the beam after all visits
    sensorVisitor.UpdateSensorState();

    SpartyProductVisitor spartyProdVisit;
    for (auto& item : mItems)
    {
        item->Accept(&spartyProdVisit);
    }

    ProductResetVisitor productResetVisitor;
    for (auto& item : mItems)
    {
        item->Accept(&productResetVisitor);
    }

    if (mHasLevelEnded)
    {
        if (mLevelLoadDelay > 0)
        {
            mLevelLoadDelay -= elapsed;
        }
        if (mLevelLoadDelay <= 0)
        {
            mHasLevelEnded = false; // end timer.
            mLevelLoadDelay = LevelLoadDelay; // reset timer back to normal delay
            LoadNextLevel();
        }
    }
}

/**
 * Display Level complete banner and move to next level
 */
void Game::LevelComplete()
{
    // Stop everything from moving
    // display level complete banner
    mVisible = true;


    // Get the current level score from scoreboard
    ScoreboardVisitor scoreVisitor;
    Accept(&scoreVisitor);
    Scoreboard* scoreboard = scoreVisitor.GetScoreboard();
    if (scoreboard)
    {
        mGameScore += scoreboard->GetLevelScore();
        scoreboard->AddLevelScoreToGameScore();
    }

    StopConveyorVisitor stopConveyorVisitor;
    Accept(&stopConveyorVisitor);


    // wait a certain amount of time
    // indicates to update to set timer
    mHasLevelEnded = true;
}

void Game::LoadNextLevel()
{
    // move to next level
    if (mCurrLevelNum < LastLevelNum)
    {
        mCurrLevelNum += 1;
    }
    else
    {
        mCurrLevelNum = LastLevelNum;
    }
    wxString filename = L"resources/levels/level" + std::to_wstring(mCurrLevelNum) + ".xml";
    LoadLevel(filename);

    // Pass the accumulated game score to next level.
    ScoreboardVisitor scoreVisitor;
    Accept(&scoreVisitor);

    Scoreboard* scoreboard = scoreVisitor.GetScoreboard();
    if (scoreboard)
    {
        scoreboard->SetGameScore(mGameScore);
    }
}
