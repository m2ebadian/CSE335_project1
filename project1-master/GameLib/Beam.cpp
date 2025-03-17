/**
 * @file Beam.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */

#include "pch.h"
#include "Beam.h"
#include "BeamDetectionVisitor.h"

#include "OutputLogicGate.h"

/// Image directory
const std::wstring DirectoryContainingImages = L"resources/images/";

/// Image for the beam sender and receiver when red
const std::wstring BeamRedImage = DirectoryContainingImages + L"beam-red.png";

/// Image for the beam sender and receiver when green
const std::wstring BeamGreenImage = DirectoryContainingImages + L"beam-green.png";

/// X offset for the beam pin in pixels
/// This is larger than normal to get it past Sparty's feet
const int BeamPinOffset = 80;

/**
 * Constructor for Beam
 *
 * @param game The game this item is a member of
 * @param senderOffset  Indicates how much to the left to place the beam sender image
 */
Beam::Beam(Game* game, int senderOffset)
    : Item(game, BeamGreenImage), mSenderOffset(senderOffset), mOutputPinVal(0)
{
    mSenderBitmap = std::make_unique<wxBitmap>(BeamGreenImage, wxBITMAP_TYPE_ANY);

    // Mirror the reciever
    wxImage receiverImage(BeamGreenImage, wxBITMAP_TYPE_ANY);
    receiverImage = receiverImage.Mirror();
    mReceiverBitmap = std::make_unique<wxBitmap>(receiverImage);
    mOutputPin = std::make_unique<OutputLogicGate>(game);
    game->Add(mOutputPin);
    mOutputPin->SetOutputState(State::Zero);
}

/**
 * Draws the beam on the given graphics context.
 *
 * @param graphics The graphics context to draw on.
 */
void Beam::Draw(wxGraphicsContext* graphics)
{
    /// Define colors for the active and inactive line states
    wxColour activeColor = wxColour(255, 0, 0);   // Red for active state
    wxColour inactiveColor = wxColour(0, 0, 0);   // Black for inactive state
    int lineWidth = 3;  ///< Line width to match the output pin's style
    int pinRadius = 5;  ///< Adjust this value if the pin circle is larger or smaller

    // Calculate positions
    int senderX = GetX() + mSenderOffset - mSenderBitmap->GetWidth() / 2;
    int senderY = GetY() - mSenderBitmap->GetHeight() / 2;
    int receiverX = GetX() - mReceiverBitmap->GetWidth() / 2;
    int receiverY = GetY() - mReceiverBitmap->GetHeight() / 2;

    // Beam line colors
    wxPen laser1(wxColour(255, 200, 200, 100), 8);
    wxPen laser2(wxColour(255, 0, 0, 175), 4);

    // Get middle of the sender/reciever so the beam is centered
    int senderMiddleY = senderY + mSenderBitmap->GetHeight() / 2;
    int receiverMiddleY = receiverY + mReceiverBitmap->GetHeight() / 2;

    //Draw the beams
    graphics->SetPen(laser1);
    graphics->StrokeLine(senderX + mSenderBitmap->GetWidth() / 2, senderMiddleY,
                         receiverX + mReceiverBitmap->GetWidth() / 2, receiverMiddleY);

    graphics->SetPen(laser2);
    graphics->StrokeLine(senderX + mSenderBitmap->GetWidth() / 2, senderMiddleY,
                         receiverX + mReceiverBitmap->GetWidth() / 2, receiverMiddleY);



    /// Determine color based on mOutputPinVal (1 for active, 0 for inactive)
    wxColour lineColor = (mOutputPinVal == 1) ? activeColor : inactiveColor;

    /// Calculate the x-coordinate for the start of the line, offset by the pin radius
    int pinStartX = receiverX + mReceiverBitmap->GetWidth() / 2 + BeamPinOffset - pinRadius;
    mOutputPin->SetLocation(pinStartX + pinRadius, receiverMiddleY);  // Set location of the pin center

    /// Draw the line from the receiver edge to just before the output pin circle
    graphics->SetPen(wxPen(lineColor, lineWidth));
    graphics->StrokeLine(receiverX + mReceiverBitmap->GetWidth() / 2, receiverMiddleY, pinStartX, receiverMiddleY);

    // Draw sender/recievers
    graphics->DrawBitmap(*mSenderBitmap, senderX, senderY, mSenderBitmap->GetWidth(), mSenderBitmap->GetHeight());
    graphics->DrawBitmap(*mReceiverBitmap, receiverX, receiverY, mReceiverBitmap->GetWidth(),
                         mReceiverBitmap->GetHeight());


}


/**
 * Detects if a product is breaking the beam and updates output state.
 * This is called after applying BeamDetectionVisitor.
 * @param productDetected True if a product is detected breaking the beam, false otherwise
 */
void Beam::DetectProduct(bool productDetected)
{
    if (productDetected)
    {
        if (mOutputPinVal == 0)  // Only update if not already active
        {
            mOutputPinVal = 1;
            // Change beam images to active state (red)
            mSenderBitmap = std::make_unique<wxBitmap>(BeamRedImage, wxBITMAP_TYPE_ANY);

            wxImage receiverImage(BeamRedImage, wxBITMAP_TYPE_ANY);
            receiverImage = receiverImage.Mirror();
            mReceiverBitmap = std::make_unique<wxBitmap>(receiverImage);
            mOutputPin->SetOutputState(State::One);
        }
    }
    else
    {
        if (mOutputPinVal == 1)  // Only update if not already inactive
        {
            mOutputPinVal = 0;
            // Change beam images to inactive state (green)
            mSenderBitmap = std::make_unique<wxBitmap>(BeamGreenImage, wxBITMAP_TYPE_ANY);

            wxImage receiverImage(BeamGreenImage, wxBITMAP_TYPE_ANY);
            receiverImage = receiverImage.Mirror();
            mReceiverBitmap = std::make_unique<wxBitmap>(receiverImage);
            mOutputPin->SetOutputState(State::Zero);
        }
    }
}


void Beam::UpdateBeam()
{
    // Create the visitor without passing 'this' as a parameter
    BeamDetectionVisitor visitor;

    // Apply the visitor to all items through the Game object
    GetGame()->Accept(&visitor);

    // Update beam state based on the visitor's detection results
    visitor.UpdateBeamState();
}



/**
 * Gets the value of the output pin (0 or 1)
 * @return Value of the pin (zero or one) depending on the state
 */
int Beam::GetOutputPinVal() const
{
    return mOutputPinVal;
}



/**
 * Load the Beam from an XML node
 * @param node The node we are loading the Beam from
 */
void Beam::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    node->GetAttribute(L"sender", L"0").ToInt(&mSenderOffset);
}
