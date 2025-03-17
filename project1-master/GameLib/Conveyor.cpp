
/**
 * @file Conveyor.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */


#include "pch.h"
#include "Conveyor.h"
#include "Product.h"
#include "ConveyorProductMoveVisitor.h"
#include "Game.h"
#include "ScoreboardVisitor.h"

/// Image directory
const std::wstring DirectoryContainingImages = L"resources/images/";
/// Image for the background (base) of the conveyor
const std::wstring ConveyorBackgroundImage = DirectoryContainingImages + L"conveyor-back.png";
/// Image for the conveyor belt
const std::wstring ConveyorBeltImage = DirectoryContainingImages + L"conveyor-belt.png";
/// Image for the conveyor control panel when stopped.
const std::wstring ConveyorPanelStoppedImage = DirectoryContainingImages + L"conveyor-switch-stop.png";
/// Image for the conveyor control panel when started.
const std::wstring ConveyorPanelStartedImage = DirectoryContainingImages + L"conveyor-switch-start.png";

// Rectangle representing the location of the start button relative to the panel @returns wxRect
//const wxRect StartButtonRect(35, 29, 95, 36);
// Rectangle representing the location of the stop button relative to the panel @returns wxRect
//const wxRect StopButtonRect(35, 87, 95, 36);

/**
 * Constructor for Conveyor.
 *
 * @param game The game this item is a member of
 * @param speed How fast the conveyor will be going
 * @param height The height to draw the conveyor in virtual pixels
 * @param panelLocation Locaiton of the panel relative to the conveyor
 */
Conveyor::Conveyor(Game* game, int speed, double height, wxPoint panelLocation)
    : Item(game, ConveyorBackgroundImage), mPanelLocation(panelLocation), mSpeed(speed), mHeight(height)
{
    wxImage backgroundImage(ConveyorBackgroundImage);
    mBackgroundBitmap = wxBitmap(backgroundImage);
    wxImage beltImage(ConveyorBeltImage);
    mBeltBitmap = wxBitmap(beltImage);
    wxImage panelStartedImage(ConveyorPanelStartedImage);
    mPanelStartedBitmap = wxBitmap(panelStartedImage);
    wxImage panelStoppedImage(ConveyorPanelStoppedImage);
    mPanelStoppedBitmap = wxBitmap(panelStoppedImage);
}

/**
 * Draws the conveyor on the given graphics context.
 * NOTE: UNSURE IF THIS IS THE INTENDED SOLUTION
 *
 * GetX() - newWidth / 2, GetY() - mHeight is because the X & Y provided is
 * where the XML wants the conveyor to be centered at, we have to adjust these values when
 * drawing in order to compensate as by default that's where the top left corner will be originated from.
 *
 * @param graphics The graphics context to draw on.
 */
void Conveyor::Draw(wxGraphicsContext* graphics)
{
    // Draw the background
    double aspectRatio = mBackgroundBitmap.GetWidth() / (1.0 * mBackgroundBitmap.GetHeight());
    double newWidth = mHeight * aspectRatio;
    graphics->DrawBitmap(mBackgroundBitmap, GetX() - newWidth / 2, GetY() - mHeight / 2, newWidth, mHeight);

    // Calculate belt dimensions
    double beltWidth = mBeltBitmap.GetWidth();
    double beltHeight = mBeltBitmap.GetHeight();
    double scaledBeltWidth = mHeight * (beltWidth / beltHeight);

    // Wrap the mBeltOffset when it exceeds the height of the belt
    if (mBeltOffset >= beltHeight)
    {
        mBeltOffset -= beltHeight;
    }

    // First draw: belt with the vertical offset
    graphics->DrawBitmap(mBeltBitmap, GetX() - scaledBeltWidth / 2, GetY() - mBeltOffset - mHeight / 2, scaledBeltWidth, beltHeight);

    // Second draw: ensure seamless wrapping by drawing the belt immediately after the first one
    graphics->DrawBitmap(mBeltBitmap, GetX() - scaledBeltWidth / 2, GetY() - mBeltOffset + beltHeight - mHeight / 2, scaledBeltWidth, beltHeight);

    // Handle the case where the first draw doesn't fill the screen
    if (mBeltOffset > 0)
    {
        graphics->DrawBitmap(mBeltBitmap, GetX() - scaledBeltWidth / 2, GetY() - mBeltOffset - beltHeight - mHeight / 2, scaledBeltWidth, beltHeight);
    }

    // Special case for initial drawing: ensure the full belt is drawn
    if (mBeltOffset == 0)
    {
        graphics->DrawBitmap(mBeltBitmap, GetX() - scaledBeltWidth / 2, GetY() - mHeight / 2 + beltHeight, scaledBeltWidth, beltHeight);
    }

    // Draw the control panel
    wxBitmap panelBitmap = mStarted ? mPanelStartedBitmap : mPanelStoppedBitmap;
    graphics->DrawBitmap(panelBitmap, GetX() + mPanelLocation.x, GetY() + mPanelLocation.y,
                         panelBitmap.GetWidth(), panelBitmap.GetHeight());
    // Uncomment the following code to draw button outlines for debugging
    /*
    wxPen buttonPen(*wxRED, 3);
    graphics->SetPen(buttonPen);
    graphics->SetBrush(wxNullBrush);
    graphics->PushState();
    graphics->Translate(GetX() + mPanelLocation.x, GetY() + mPanelLocation.y);
    graphics->DrawRectangle(StartButtonRect.GetX(), StartButtonRect.GetY(), StartButtonRect.GetWidth(), StartButtonRect.GetHeight());
    graphics->DrawRectangle(StopButtonRect.GetX(), StopButtonRect.GetY(), StopButtonRect.GetWidth(), StopButtonRect.GetHeight());
    graphics->PopState();
    */
}

/**
* Update the conveyor belt for animation
* @param elapsed
*/
void Conveyor::Update(double elapsed)
{
    if (mStarted)
    {
        // Apply a scaling factor to slow down the speed
        // Update the vertical offset based on speed, elapsed time, and speed factor
        mBeltOffset -= mSpeed * elapsed;

        // Move all the products on the conveyor
        MoveProducts(elapsed);

        // Wrap around if the offset exceeds the belt height for vertical wrapping
        double beltHeight = mBeltBitmap.GetHeight();
        if (mBeltOffset < 0)
        {
            mBeltOffset += beltHeight;
        }

        // Debugging - ensure this is called
        //std::cout << "Updating Conveyor and moving products...\n";

    }
}


/**
 * Move all the products on the conveyor.
 * @param elapsed The time elapsed since the last update.
 */
void Conveyor::MoveProducts(double elapsed)
{
    //std::cout << "Conveyor::MoveProducts called with elapsed time: " << elapsed << std::endl;

    // Create the visitor with conveyor speed and elapsed time
    ConveyorProductMoveVisitor moveVisitor(mSpeed, elapsed);

    // Assuming all products are contained in a collection in Game, apply visitor to each
    GetGame()->Accept(&moveVisitor);

    // Bring each product to the front after moving
    for (auto product : moveVisitor.GetMovedProducts())  // Assuming GetMovedProducts() returns the products moved
    {
        product->MoveToFront();
    }

    moveVisitor.MoveProducts();  // Actually move the products


}


/**
 *  Starts the conveyor belt
 */
void Conveyor::Start()
{
    mStarted = true;

    // Reset the level score when start button is pressed
    ScoreboardVisitor scoreVisitor;
    GetGame()->Accept(&scoreVisitor);
    Scoreboard* scoreboard = scoreVisitor.GetScoreboard();
    if (scoreboard)
    {
        scoreboard->ResetLevelScore();
    }
}

/**
 * Stops the conveyor belt
 */
void Conveyor::Stop()
{
    mStarted = false;
    mReset = true;
}

/**
 * Handles mouse clicks to start or stop the conveyor.
 * @param x X position of the mouse click.
 * @param y Y position of the mouse click.
 */
void Conveyor::OnMouseClick(int x, int y)
{
    // Convert the click coordinates to the panel's coordinate system
    int panelX = GetX() + mPanelLocation.x;
    int panelY = GetY() + mPanelLocation.y;
    // Check if the Start button was clicked
    if (StartButtonRect.Contains(x - panelX, y - panelY) && !mStarted)
    {
        Start(); // Start the conveyor
        //std::cout << "Start button clicked, conveyor started" << std::endl;
    }
    // Check if the Stop button was clicked
    if (StopButtonRect.Contains(x - panelX, y - panelY))
    {
        Stop(); // Stop the conveyor
        //std::cout << "Stop button clicked, conveyor stopped" << std::endl;
    }
}


/**
 * Load the Conveyor from an XML node
 * @param node The node we are loading the Conveyor from
 */
void Conveyor::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    double panelX, panelY;
    node->GetAttribute(L"speed", L"0").ToInt(&mSpeed);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
    wxString panel = node->GetAttribute(L"panel", L"0,0");
    wxArrayString panelParts = wxSplit(panel, ',');
    if (panelParts.GetCount() == 2)
    {
        // Convert the pane; values to doubles
        panelParts[0].ToDouble(&panelX);
        panelParts[1].ToDouble(&panelY);
    }
    mPanelLocation = wxPoint(panelX, panelY);
}



