/**
 * @file PinInput.cpp
 * @author Daniel Wills
 */

#include "pch.h"
#include "PinInput.h"
#include "LogicGate.h"

/// Default length of line from the pin
static const int DefaultLineLength = 20;

/// Diameter to draw the pin in pixels
const int PinSize = 10;

/// Line with for drawing lines between pins
const int LineWidth = 3;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown= wxColour(128, 128, 128);

/**
 * Constructor
 * @param owner item that owns this input pin
 * @param location Location on the game that the pin is located in
 */
PinInput::PinInput(LogicGate* owner, wxPoint location) : Pin(owner, location)
{
}

/**
 * Draw the input pin
 * @param gc Display context to draw on
 */
void PinInput::Draw(wxGraphicsContext* gc)
{

    if (mLine != nullptr)
    {
        State state = mLine->GetState();
        SetState(state);
    }

    auto loc = GetAbsoluteLocation();

    //gc->SetBrush(*wxGREEN_BRUSH);
    //gc->SetPen(*wxGREEN_PEN);
    //gc->DrawEllipse(loc.x - PinSize, loc.y - PinSize, PinSize * 2, PinSize * 2);

    double lineEndX = loc.x + DefaultLineLength;
    double lineEndY = loc.y;

    // Set color based on state
    if (mState == State::One)
    {
        gc->SetPen(wxPen(ConnectionColorOne, LineWidth));
        gc->SetBrush(wxBrush(ConnectionColorOne)); // Fill color for the circle
    }
    else if (mState == State::Zero)
    {
        gc->SetPen(wxPen(ConnectionColorZero, LineWidth));
        gc->SetBrush(wxBrush(ConnectionColorZero)); // Fill color for the circle
    }
    else
    {
        gc->SetPen(wxPen(ConnectionColorUnknown, LineWidth));
        gc->SetBrush(wxBrush(ConnectionColorUnknown)); // Fill color for the circle
    }

    gc->StrokeLine(loc.x, loc.y, lineEndX, lineEndY);
    gc->SetPen(wxPen(wxColour(0, 0, 0))); // Black outline

    // Draw the pin as a small circle at the end of the line
    gc->DrawEllipse(loc.x - PinSize / 2,
                    loc.y - PinSize / 2,
                    PinSize, PinSize);
}

/**
 * Try to catch a input pin at the new x,y location of the output pin end
 * @param pinOutput output pin we are trying to catch from
 * @param lineEnd The line end point
 * @return true if caught
 */
bool PinInput::Catch(PinOutput* pinOutput, wxPoint lineEnd)
{
    auto loc = GetAbsoluteLocation();
    auto relative = lineEnd - loc;

    if ((relative.x * relative.x + relative.y * relative.y) < PinSize * PinSize)
    {
        if (mLine != nullptr)
        {
            mLine->RemoveCaughtPinInput(this);
        }

        mLine = pinOutput;
        pinOutput->SetCaught(this);
        State state = pinOutput->GetState();
        SetState(state);
        //if (mOwner != nullptr)
        //{
        //    mOwner->ComputeOutput();
        //}
    }

    return false;
}

/**
 * Get the location of the pin
 * @return Location in pixels
 */
wxPoint PinInput::GetAbsoluteLocation()
{
    double pinX = 0;
    double pinY = 0;
    if (!mStatic)
    {
        pinX = mOwner->GetX() + mLocation.x;
        pinY = mOwner->GetY() + mLocation.y;
    }
    else
    {
        pinX = mLocation.x;
        pinY = mLocation.y;
    }
    return wxPoint(pinX, pinY);
}



/**
 * @brief Sets the current state of the input pin and triggers output computation.
 *
 * Updates the state of the pin and calls the owner’s `ComputeOutput` function to process changes.
 * @param state The new state to set for the input pin.
 */
void PinInput::SetState(State state)
{
    mState = state;
    mOwner->ComputeOutput();
}