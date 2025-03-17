/**
 * @file Sparty.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */

#include "pch.h"
#include "Sparty.h"
#include "InputLogicGate.h"
#include "Product.h"
#include "SpartyProductVisitor.h"

/// Image directory
const std::wstring DirectoryContainingImages = L"resources/images/";

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = DirectoryContainingImages + L"sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = DirectoryContainingImages + L"sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = DirectoryContainingImages + L"sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// The maximum rotation for Sparty's boot in radians
const double SpartyBootMaxRotation = 0.8;

/// The point in the kick animation when the product
/// actually is kicked. If the kick duration is 0.25,
/// we kick when 0.25 * 0.35 seconds have elapsed.
const double SpartyKickPoint = 0.35;

/// What percentage of the way down Sparty do we find the tip of his boot?
/// This means the location of the boot when kicking is 80% of the
/// way from the top of the Sparty image.
const double SpartyBootPercentage = 0.80;

/// The start of the end of the scoreboard
const int ScoreboardEnd = 380;

/// Default length of line from the pin
const int DefaultLineLength = 20;

/// Default line width for wire
const int LineWidth = 3;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown= wxColour(128, 128, 128);

/**
 * Constructor for Sparty.
 *
 * @param game The game this item is a member of
 * @param height The height to draw Sparty in virtual pixels (NOTE: MIGHT NEED TO BE IMPLEMENTED DIFFERENTLY)
 * @param pin The location of the input pin for Sparty
 * @param kickDuration The duration of the kick animation in seconds
 * @param kickSpeed The speed of the kick in pixels per second
 */
Sparty::Sparty(Game* game, double height, wxPoint pin, double kickDuration, double kickSpeed)
    : Item(game),
      mIsKicking(false), mKickTime(0), mHeight(height), mCurrentBootRotation(0),
      mProductKicked(), mPreviousState(State::Unknown)

{
    mBootBitmap = std::make_unique<wxBitmap>(SpartyBootImage, wxBITMAP_TYPE_ANY);
    mFrontBitmap = std::make_unique<wxBitmap>(SpartyFrontImage, wxBITMAP_TYPE_ANY);

    mBackBitmap = std::make_unique<wxBitmap>(SpartyBackImage, wxBITMAP_TYPE_ANY);

    mInputPin = std::make_shared<InputLogicGate>(game); //Create the input pin
    game->Add(mInputPin); //Add it to the game
}

/**
 * Draws Sparty on the given graphics context.
 * NOTE: UNSURE IF THIS IS THE INTENDED SOLUTION OR TO HAVE A SEPERATE CLASS FOR THE LEG.... MIGHT BE A GOOD IDEA
 *
 * @param graphics The graphics context to draw on.
 */
void Sparty::Draw(wxGraphicsContext* graphics)
{
    auto state = mInputPin->GetInputPinValue();
    if (state == State::One)
    {
        graphics->SetPen(wxPen(ConnectionColorOne, LineWidth));}
    else if (state == State::Zero)
    {
        graphics->SetPen(wxPen(ConnectionColorZero, LineWidth));
    }
    else
    {
        graphics->SetPen(wxPen(ConnectionColorUnknown, LineWidth));
    }

    double lineEndX = mPin.x + DefaultLineLength; // adjust as needed for spacing
    double lineEndY = mPin.y;

    // Now drawing vertical wire connecting from pin
    double scoreboardHeight = 70;
    double halfOfScreenHeight = 310 + scoreboardHeight;
    graphics->StrokeLine(lineEndX, lineEndY,
                         lineEndX, lineEndY - halfOfScreenHeight);

    // Draw horizontal wire connecting remaining wire from scoreboard
    double conveyorY = 400;
    double endingUpVerticalWire = 320;
    graphics->StrokeLine(lineEndX, lineEndY - halfOfScreenHeight,
                         lineEndX - ScoreboardEnd - endingUpVerticalWire, lineEndY - halfOfScreenHeight);

    // Draw the vertical wire down from the remaining wire to around half of sparty
    double quarterofSpartyHeight = mHeight/4;
    graphics->StrokeLine(lineEndX - ScoreboardEnd - endingUpVerticalWire, lineEndY - halfOfScreenHeight,
                         lineEndX - ScoreboardEnd - endingUpVerticalWire, lineEndY - quarterofSpartyHeight);

    // Now draw remaining wire to connect sparty.
    double distanceToSparty = 105;
    graphics->StrokeLine(lineEndX - ScoreboardEnd - endingUpVerticalWire, lineEndY - quarterofSpartyHeight,
                         lineEndX - ScoreboardEnd - endingUpVerticalWire - distanceToSparty, lineEndY - quarterofSpartyHeight);

    double aspectRatio = mBootBitmap->GetWidth() / (1.0 * mBootBitmap->GetHeight());
    double newWidth = mHeight * aspectRatio;

    double pivotX = GetX();
    double pivotY = GetY();

    //Sparty back foot
    graphics->DrawBitmap(*mBackBitmap, GetX() - newWidth / 2, GetY() - mHeight / 2, newWidth, mHeight);

    //std::cout << "Current Boot Rotation: " << mCurrentBootRotation << std::endl;
    //std::cout << "Pivot: (" << pivotX << ", " << pivotY << ")" << std::endl;
    //std::cout << "Boot Bitmap Size: (" << mBootBitmap->GetWidth() << ", " << mBootBitmap->GetHeight() << ")" << std::endl;

    graphics->PushState();
    graphics->Translate(pivotX, pivotY);
    graphics->Rotate(mCurrentBootRotation);
    graphics->DrawBitmap(*mBootBitmap,  - newWidth / 2, -mHeight / 2, newWidth, mHeight);
    graphics->PopState();

    double frontAspectRatio = mFrontBitmap->GetWidth() / (1.0 * mFrontBitmap->GetHeight());
    double frontNewWidth = mHeight * frontAspectRatio;
    graphics->DrawBitmap(*mFrontBitmap, GetX() - frontNewWidth / 2, GetY() - mHeight / 2, frontNewWidth, mHeight);
    int bootY = int(mHeight * SpartyBootPercentage);
    /*
    wxPen bootablePen(*wxGREEN, 3);
    graphics->SetPen(bootablePen);
    graphics->StrokeLine(GetX() - newWidth/2, GetY() - mHeight/2 + bootY,
                         GetX() + newWidth/2, GetY() - mHeight/2 + bootY );
    */
}

/**
 * Updates the state of Sparty.
 *
 * @param elapsed The time elapsed since the last update.
 */
void Sparty::Update(double elapsed)
{
    State currentState = mInputPin->GetInputPinValue();
    if (currentState == State::One && mPreviousState == State::Zero && !mIsKicking)
    {
        StartKick();
    }

    if (mIsKicking)
    {
        AnimateKick(elapsed);
    }

    mPreviousState = currentState;
}


/**
 * @brief Initiates Sparty's kicking action.
 *
 * Sets Sparty's kicking state to active and resets the kick timer.
 */
void Sparty::StartKick()
{
    mIsKicking = true;
    mKickTime = 0;
//    std::cout << "Kick started!" << std::endl;

}


/**
 * @brief Animates Sparty's kicking action over time.
 *
 * This function progresses the kicking animation based on the elapsed time, updating the boot's rotation to
 * simulate a kicking motion. Once the kick duration is complete, the kick is reset.
 *
 * @param elapsed The time elapsed since the last animation update, in seconds.
 */
void Sparty::AnimateKick(double elapsed)
{
    mKickTime += elapsed;

    if (mKickTime <= mKickDuration)
    {
        double kickProgress = mKickTime / mKickDuration;
        if (kickProgress <= SpartyKickPoint)
        {
            mCurrentBootRotation = (kickProgress / SpartyKickPoint) * SpartyBootMaxRotation;
        }
        else
        {
            double returnProgress = (kickProgress - SpartyKickPoint) / (1 - SpartyKickPoint);
            mCurrentBootRotation = SpartyBootMaxRotation * (1 - returnProgress);
        }
    }
    else
    {
        ResetKick();
    }
}


/**
 * @brief Resets Sparty's kicking action to its initial state.
 *
 * This function stops the kicking action, resets the kick timer and boot rotation, and
 * sets Sparty's kicking state to inactive.
 */
void Sparty::ResetKick()
{
    mIsKicking = false;
    mKickTime = 0;
    mCurrentBootRotation = 0;
    //std::cout << "Kick reset!" << std::endl;
}



/**
 * @brief Checks if a product is within Sparty's kicking range.
 *
 * Determines if the specified product is within the vertical tolerance range of Sparty's kick zone,
 * allowing Sparty to kick the product if within range.
 *
 * @param product The product to check for proximity to Sparty's kick zone.
 * @return `true` if the product is within Sparty's kicking range, `false` otherwise.
 */
bool Sparty::IsProductInKickRange(const Product& product)
{
    // Get product's position
    double productY = product.GetY();
    double productHeight = product.GetHeight();  // Assuming Product has a GetHeight() method

    // Calculate the Y position of the boot's kick zone
    int bootY = int(mHeight * SpartyBootPercentage);
    int kickZoneY = GetY() - mHeight / 2 + bootY;

    // Define a tolerance range for the kick zone

    // Calculate the vertical bounds of the product
    double productTopY = productY - productHeight / 2;
    double productBottomY = productY + productHeight / 2;

    // Check if any part of the product's vertical range is within Sparty's kick zone
    bool withinYRange = (productBottomY >= kickZoneY && productTopY <= kickZoneY);

    return withinYRange;
}



/**
 * Initiates the kick action for Sparty.
 * NOTE: WORK IN PROGRESS THIS IS JUST AN IDEA OF WHAT I THINK IT COULD LOOK LIKE
 */
void Sparty::KickProduct()
{
    // Placeholder: Implement product kicking logic here
    // For example, you could apply velocity to the product or directly remove it from the conveyor.
}

/**
 * Load this Sparty from an XML node
 * @param node The node we are loading Sparty from
 */
void Sparty::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    double pinX, pinY;
    wxString pin;

    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);

    pin = node->GetAttribute(L"pin", L"");
    wxArrayString pinParts = wxSplit(pin, ',');
    if (pinParts.GetCount() == 2)
    {
        // Convert the pin values to doubles
        pinParts[0].ToDouble(&pinX);
        pinParts[1].ToDouble(&pinY);
    }

    mPin = wxPoint(pinX, pinY);
    mInputPin->SetLocation(mPin.x,mPin.y); //Sets the input gate location
    node->GetAttribute(L"kick-duration", L"0").ToDouble(&mKickDuration);
    node->GetAttribute(L"kick-speed", L"0").ToDouble(&mKickSpeed);
}
