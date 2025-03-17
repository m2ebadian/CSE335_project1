/**
 * @file PinOutput.cpp
 * @author Daniel Wills, Conner O'Sullivan
 */

#include "pch.h"
#include "PinOutput.h"
#include "Item.h"
#include "LogicGate.h"
#include "PinInput.h"

/// Default length of line from the pin
const int DefaultLineLength = 20;

/// Diameter to draw the pin in pixels
const int PinSize = 10;

/// offset for the pin name when mShowControl is on
const int pinNameOffset = 25;

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
 * @param owner Item that owns this pin
 * @param location Location on the game that the pin is located in
 */
PinOutput::PinOutput(LogicGate* owner, wxPoint location) : Pin(owner, location)
{
}

/**
 * Set the location of the end of the wire as we drag it
 * @param x X location in pixels
 * @param y Y location in pixels
 */
void PinOutput::SetLocation(double x, double y)
{
    mDragging = true;
    mCaught = nullptr;
    mLineEnd = wxPoint(int(x), int(y));
}

/**
 * Draw this output pin.
 *
 * This is just used in development to see where the
 * pin is supposed to be.
 *
 * @param gc Device context to draw on
 */
void PinOutput::Draw(wxGraphicsContext* gc)
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

    // Update line end coordinates based on pin location
    double lineEndX = pinX; // Using the calculated pinX
    double lineEndY = pinY; // Using the calculated pinY

    // Set pen for the line based on state
    if (GetState() == State::One)
    {
        gc->SetPen(wxPen(ConnectionColorOne, LineWidth));
        gc->SetBrush(wxBrush(ConnectionColorOne)); // Fill color for the circle
    }
    else if (GetState() == State::Zero)
    {
        gc->SetPen(wxPen(ConnectionColorZero, LineWidth));
        gc->SetBrush(wxBrush(ConnectionColorZero)); // Fill color for the circle
    }
    else
    {
        gc->SetPen(wxPen(ConnectionColorUnknown, LineWidth));
        gc->SetBrush(wxBrush(ConnectionColorUnknown)); // Fill color for the circle
    }

    // Draw line to the pin's location
    gc->StrokeLine(pinX - DefaultLineLength, pinY, lineEndX, lineEndY);

    gc->SetPen(wxPen(wxColour(0, 0, 0))); // Black outline

    // Draw the filled circle at the end of the line
    gc->DrawEllipse(pinX - PinSize / 2,
                    pinY - PinSize / 2,
                    PinSize, PinSize);

    //gc->SetBrush(*wxRED_BRUSH);
    //gc->SetPen(*wxRED_PEN);
    //gc->DrawEllipse(pinX - PinSize, pinY - PinSize, PinSize * 2, PinSize * 2);

    if (mDragging)
    {
        if (GetState() == State::One)
        {
            gc->SetPen(wxPen(ConnectionColorOne, LineWidth));
        }
        else if (GetState() == State::Zero)
        {
            gc->SetPen(wxPen(ConnectionColorZero, LineWidth));
        }
        else
        {
            gc->SetPen(wxPen(ConnectionColorUnknown, LineWidth));
        }

        // Calculate control points for the Bezier curve
        wxPoint2DDouble p1(pinX, pinY);
        wxPoint2DDouble p4(mLineEnd.x, mLineEnd.y);

        double distance = std::hypot(p4.m_x - p1.m_x, p4.m_y - p1.m_y);
        double offset = std::min(BezierMaxOffset, distance);

        wxPoint2DDouble p2(p1.m_x + offset, p1.m_y);
        wxPoint2DDouble p3(p4.m_x - offset, p4.m_y);

        // Create the Bezier path
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(p1.m_x, p1.m_y);
        path.AddCurveToPoint(p2.m_x, p2.m_y, p3.m_x, p3.m_y, p4.m_x, p4.m_y);

        // Draw the Bezier curve
        gc->StrokePath(path);

        if (mShowControl)
        {
            // Label points with red dots and their names
            wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
            gc->SetFont(font, *wxRED);
            gc->SetBrush(*wxRED_BRUSH);
            gc->SetPen(*wxRED_PEN);
            gc->DrawEllipse(p1.m_x - 2, p1.m_y - 2, 4, 4);
            gc->DrawEllipse(p2.m_x - 2, p2.m_y - 2, 4, 4);
            gc->DrawEllipse(p3.m_x - 2, p3.m_y - 2, 4, 4);
            gc->DrawEllipse(p4.m_x - 2, p4.m_y - 2, 4, 4);
            gc->DrawText("p1", p1.m_x, p1.m_y - pinNameOffset);
            gc->DrawText("p2", p2.m_x, p2.m_y - pinNameOffset);
            gc->DrawText("p3", p3.m_x, p3.m_y - pinNameOffset);
            gc->DrawText("p4", p4.m_x, p4.m_y - pinNameOffset);

            // Draw the green rhombus around the Bezier curve area
            gc->SetPen(wxPen(*wxGREEN, 1));
            wxGraphicsPath rhombus = gc->CreatePath();
            rhombus.MoveToPoint(p1.m_x, p1.m_y);
            rhombus.AddLineToPoint(p2.m_x, p2.m_y);
            rhombus.AddLineToPoint(p4.m_x, p4.m_y);
            rhombus.AddLineToPoint(p3.m_x, p3.m_y);
            rhombus.CloseSubpath();
            gc->StrokePath(rhombus);
        }
    }

    for (auto caughtPin : mCaughts)
    {
        if (caughtPin != nullptr)
        {
            if (GetState() == State::One)
            {
                gc->SetPen(wxPen(ConnectionColorOne, LineWidth));
            }
            else if (GetState() == State::Zero)
            {
                gc->SetPen(wxPen(ConnectionColorZero, LineWidth));
            }
            else
            {
                gc->SetPen(wxPen(ConnectionColorUnknown, LineWidth));
            }

            wxPoint inputPin = caughtPin->GetAbsoluteLocation();

            // Calculate control points for the Bezier curve
            wxPoint2DDouble p1(pinX, pinY);
            wxPoint2DDouble p4(inputPin.x, inputPin.y);

            double distance = std::hypot(p4.m_x - p1.m_x, p4.m_y - p1.m_y);
            double offset = std::min(BezierMaxOffset, distance);

            wxPoint2DDouble p2(p1.m_x + offset, p1.m_y);
            wxPoint2DDouble p3(p4.m_x - offset, p4.m_y);

            // Create the Bezier path
            wxGraphicsPath path = gc->CreatePath();
            path.MoveToPoint(p1.m_x, p1.m_y);
            path.AddCurveToPoint(p2.m_x, p2.m_y, p3.m_x, p3.m_y, p4.m_x, p4.m_y);

            // Draw the Bezier curve
            gc->StrokePath(path);

            if (mShowControl)
            {
                // Label points with red dots and their names
                wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
                gc->SetFont(font, *wxRED);
                gc->SetBrush(*wxRED_BRUSH);
                gc->SetPen(*wxRED_PEN);
                gc->DrawEllipse(p1.m_x - 2, p1.m_y - 2, 4, 4);
                gc->DrawEllipse(p2.m_x - 2, p2.m_y - 2, 4, 4);
                gc->DrawEllipse(p3.m_x - 2, p3.m_y - 2, 4, 4);
                gc->DrawEllipse(p4.m_x - 2, p4.m_y - 2, 4, 4);
                gc->DrawText("p1", p1.m_x, p1.m_y - pinNameOffset);
                gc->DrawText("p2", p2.m_x, p2.m_y - pinNameOffset);
                gc->DrawText("p3", p3.m_x, p3.m_y - pinNameOffset);
                gc->DrawText("p4", p4.m_x, p4.m_y - pinNameOffset);

                // Draw the green rhombus around the Bezier curve area
                gc->SetPen(wxPen(*wxGREEN, 1));
                wxGraphicsPath rhombus = gc->CreatePath();
                rhombus.MoveToPoint(p1.m_x, p1.m_y);
                rhombus.AddLineToPoint(p2.m_x, p2.m_y);
                rhombus.AddLineToPoint(p4.m_x, p4.m_y);
                rhombus.AddLineToPoint(p3.m_x, p3.m_y);
                rhombus.CloseSubpath();
                gc->StrokePath(rhombus);
            }
        }
    }
}

/**
 * Did we click on the pin end?
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return Did we click on it?
 */
bool PinOutput::HitTest(int x, int y)
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
    return (pinX - x) * (pinX - x) + (pinY - y) * (pinY - y) < PinSize * PinSize;
}

/**
 * Move the logic gate to the front
 */
void PinOutput::MoveToFront()
{
    mOwner->GetGame()->BringItemToFront(mOwner);
}

/**
 * Release after moving
 */
void PinOutput::Release()
{
    if (mDragging)
    {
        // The mouse has been released. See if there
        // is an input pin we can catch?
        mOwner->GetGame()->TryToCatch(this, mLineEnd);
    }

    mDragging = false;
}

/**
 * Set the caught input pin
 * @param caught Caught input pin
 */
void PinOutput::SetCaught(PinInput* caught)
{
    if (caught != nullptr)
    {
        //if (caught->GetOwner() != mOwner)
        //{
            mCaughts.push_back(caught);
            //if (mOwner != nullptr)
            //{
            //    mOwner->ComputeOutput();
            //}
        //}
    }
}

/**
 * Removes a caught pin
 * @param caught the input pin the wire is attached to
 */
void PinOutput::RemoveCaughtPinInput(PinInput* caught)
{
    int i = -1;
    for (auto element : mCaughts)
    {
        i += 1;
        if (element == caught)
        {
            break;
        }
    }

    if (i != -1)
    {
        mCaughts[i] = nullptr;
    }
}