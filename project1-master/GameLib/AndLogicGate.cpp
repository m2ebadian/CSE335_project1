/**
 * @file AndLogicGate.cpp
 * @author Soami Kapadia
 * @brief Implementation of the AND logic gate class.
 */

#include "pch.h"
#include "AndLogicGate.h"

/**
 * @brief Size of the AND gate in pixels.
 * @return wxSize
 */
const wxSize AndGateSize(75, 50);


/**
 * @brief Constructor for the AND Logic Gate.
 *
 * Initializes the AND logic gate with the specified game object.
 */
AndLogicGate::AndLogicGate(Game* game): LogicGate(game)
{
    SetGateSize(AndGateSize);

    // Get the location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    const wxPoint InputPinLocation1(x - w / 1.3, y + h / 4.5);
    const wxPoint InputPinLocation2(x - w / 1.3, y - h / 4.5);
    const wxPoint OutputPinLocation1(x + w / 1.25, y);

    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation1));
    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation2));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation1));
}

/**
 * @brief Draws the AND logic gate.
 *
 * This function creates and draws the shape of the AND gate on the given
 * graphics context using Bezier curves.
 */
void AndLogicGate::Draw(wxGraphicsContext* gc)
{
    // The location and size of the gate
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // Create a path to draw the gate shape
    auto path = gc->CreatePath();

    // Define the points for the rectangular part of the AND gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 4, y + h / 2); // Bottom right (before curve)
    wxPoint2DDouble p4(x - w / 2, y - h / 2); // Top left

    // Create the path for the AND gate
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2);

    // Create a semicircle to the right side of the gate
    path.AddArc(x + w / 4, y, h / 2, M_PI / 2, -M_PI / 2, false);

    path.AddLineToPoint(p4);
    path.CloseSubpath();

    // Draw pins first
    DrawPins(gc);

    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);

    // Bottom input
    //gc->StrokeLine((x - w / 3), (y + h / 4.5), (x - w / 1.5), (y + h / 4.5));
    //gc->DrawEllipse((x - w / 1.3), ((-h / 20) + y + h / 4.5), h / 10, h / 10);

    // Top input
    //gc->StrokeLine((x - w / 3), (y - h / 4.5), (x - w / 1.5), (y - h / 4.5));
    //gc->DrawEllipse((x - w / 1.3), ((-h / 20) + y - h / 4.5), h / 10, h / 10);

    // Middle output
    //gc->StrokeLine((x + w / 3), (y), (x + w / 1.5), (y));
    //gc->DrawEllipse((x + w / 1.5), ((-h / 20) + y), h / 10, h / 10);

    // Set pen and brush for drawing the gate
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxWHITE_BRUSH);

    // Draw the AND gate shape
    gc->DrawPath(path);
}

/**
 * @brief Computes the logic for the AND gate.
 */
void AndLogicGate::ComputeOutput()
{
    // Get input pins
    auto inputPin1 = GetPinInputs()[0];
    auto inputPin2 = GetPinInputs()[1];

    // Get output pins
    auto outputPin = GetOutputPins()[0];

    // Calculate state and set the output pin state
    if (inputPin1->GetState() == State::One && inputPin2->GetState() == State::One)
    {
        outputPin->SetState(State::One);
    }
    else if (inputPin1->GetState() == State::Zero || inputPin2->GetState() == State::Zero)
    {
        outputPin->SetState(State::Zero);
    }
    else
    {
        outputPin->SetState(State::Unknown);
    }
}
