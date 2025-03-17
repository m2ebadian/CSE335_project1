/**
 * @file GameView.cpp
 * @author Conner O'Sullivan, Daniel Wills, Mehrshad Bagherebadian
 *
 * Implements the Game View Class
 */

#include "pch.h"
#include "GameView.h"
#include "OrLogicGate.h"
#include "AndLogicGate.h"
#include "NotLogicGate.h"
#include "SRLogicGate.h"
#include "DLogicGate.h"
#include "XORLogicGate.h"
#include "LogicGate.h"
#include "ConveyorControlVisitor.h"
#include "ToggleControlPointsVisitor.h"
#include <wx/dcbuffer.h>

#include "DLogicGate.h"
#include "ids.h"
#include "Item.h"
#include "NotLogicGate.h"


using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the Game view class
 * @param parent
 */
void GameView::Initialize(wxFrame* parent)
{
    // Create the window
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    // This will be the background color of the window
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Add binders for events here
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    //Bind(wxEVT_LEFT_DOWN, &GameView::OnMouseClick, this);

    // Gates Menu options
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGate, this, IDM_ADDANDGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGate, this, IDM_ADDORGATE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGate, this, IDM_ADDNOT);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGate, this, IDM_ADDSRFLIPFLOP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGate, this, IDM_ADDDFLIPFLOP);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGate, this, IDM_ADDXORGATE);

    // Level menu options
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL4);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL5);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL6);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL7);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevel, this, IDM_LEVEL8);

    // View menu options
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnShowControlPoints, this, IDM_ADDCONTROLPOINTS);

    // Timer for animation
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}


/**
 * Level>Level [INSERT LEVEL] menu handler
 * @param event Menu event
 */
void GameView::OnLoadLevel(wxCommandEvent& event)
{
    wxString filename;
    switch (event.GetId())
    {
    case IDM_LEVEL0:
        filename = L"resources/levels/level0.xml";
        mGame.SetLevelNum(0);
        break;
    case IDM_LEVEL1:
        filename = L"resources/levels/level1.xml";
        mGame.SetLevelNum(1);
        break;
    case IDM_LEVEL2:
        filename = L"resources/levels/level2.xml";
        mGame.SetLevelNum(2);
        break;
    case IDM_LEVEL3:
        filename = L"resources/levels/level3.xml";
        mGame.SetLevelNum(3);
        break;
    case IDM_LEVEL4:
        filename = L"resources/levels/level4.xml";
        mGame.SetLevelNum(4);
        break;
    case IDM_LEVEL5:
        filename = L"resources/levels/level5.xml";
        mGame.SetLevelNum(5);
        break;
    case IDM_LEVEL6:
        filename = L"resources/levels/level6.xml";
        mGame.SetLevelNum(6);
        break;
    case IDM_LEVEL7:
        filename = L"resources/levels/level7.xml";
        mGame.SetLevelNum(7);
        break;
    case IDM_LEVEL8:
        filename = L"resources/levels/level8.xml";
        mGame.SetLevelNum(8);
        break;
    default:
        return;
    }

    mGame.LoadLevel(filename);
    Refresh();
}

/**
 * Paint event, draws the window
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    // Clear the window
    dc.Clear();

    /// Compute the time that has elapsed
    /// Since the last call to OnPaint
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
    mGame.Update(elapsed);
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftDown(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = int(event.GetY());

    // Create the visitor to handle conveyor control clicks (start/stop buttons)
    ConveyorControlVisitor visitor(x, y);

    // Apply the visitor to all items in the game to check for button clicks
    mGame.Accept(&visitor);

    // If the visitor handled the click, it means a button was clicked, so no need to move items
    if (visitor.WasButtonClicked())
    {
        // Refresh to update the conveyor's start/stop state
        Refresh();
        return;
    }

    // If no button was clicked, proceed with item grabbing/moving logic
    mGrabbedItem = mGame.HitTest(mGame.GetVirtualPixelsX(x), mGame.GetVirtualPixelsY(y));
    if (mGrabbedItem != nullptr)
    {
        // We have selected an item, move it to the end of the list of items
        mGrabbedItem->MoveToFront();
        Refresh();
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void GameView::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void GameView::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(mGame.GetVirtualPixelsX(event.GetX()), mGame.GetVirtualPixelsY(event.GetY()));
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem->Release();
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Menu handler for Add Gates menu options
 * @param event Menu event
 */
void GameView::OnAddGate(wxCommandEvent& event)
{
    shared_ptr<LogicGate> gate;
    switch (event.GetId())
    {
    case IDM_ADDANDGATE:
        gate = make_shared<AndLogicGate>(&mGame);
        break;

    case IDM_ADDORGATE:
        gate = make_shared<OrLogicGate>(&mGame);
        break;

    case IDM_ADDNOT:
        gate = make_shared<NotLogicGate>(&mGame);
        break;

    case IDM_ADDSRFLIPFLOP:
        // Add SR Flip Flop gate
        gate = make_shared<SRLogicGate>(&mGame);
        break;

    case IDM_ADDDFLIPFLOP:
        gate = make_shared<DLogicGate>(&mGame);
        break;

    case IDM_ADDXORGATE:
        // Add XOR Gate
        gate = make_shared<XORLogicGate>(&mGame);
        break;

    default:
        // Handle unexpected event
        break;
    }
    if (gate != nullptr)
    {
        gate->SetLocation(500, 500);
        mGame.Add(gate);
        Refresh();
    }
}

/**
 * Handle the View>Control Points
 * @param event Menu event
 */
void GameView::OnShowControlPoints(wxCommandEvent& event)
{
    bool showControlPoints = event.IsChecked();
    mGame.SetShowControlPoints(showControlPoints); // Save the visibility state
    ToggleControlPointsVisitor visitor(showControlPoints); // Create visitor
    mGame.Accept(&visitor); // Apply to existing gates
    Refresh();
}

/**
 * Handle the timer event
 * @param event Timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}


/**
 * Handle the Start and Stop button when clicked
 * @param event On Click
 */
void GameView::OnMouseClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = int(event.GetY());

    // Create the visitor to handle start/stop
    ConveyorControlVisitor visitor(x, y);

    // Ask the game to apply the visitor to all items
    mGame.Accept(&visitor);

    Refresh(); // Refresh the screen to reflect state changes
}
