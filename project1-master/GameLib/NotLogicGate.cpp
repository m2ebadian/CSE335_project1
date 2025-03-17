/**
 * @file NotLogicGate.cpp
 * @author Soami Kapadia
 */

#include "pch.h"
#include "NotLogicGate.h"
#include "PinInput.h"
#include "PinOutput.h"


/**
 * @brief Size of the NOT gate in pixels.
 * @return wxSize
 */
const wxSize NotGateSize(50, 50);
/**
 * @brief Constructor for the NOT Logic Gate.
 *
 * Initializes the NOT logic gate with the specified game object.
 */
NotLogicGate::NotLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(NotGateSize);

    // Initialize the input and output pin
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    const wxPoint InputPinLocation((x - w / 1.3), y);
    const wxPoint OutputPinLocation((x + w), y);

    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation));
}

/**
 * @brief Draws the NOT logic gate.
 *
 * This function creates and draws the shape of the NOT gate on the given
 * gc context using Bezier curves.
 */
void NotLogicGate::Draw(wxGraphicsContext* gc)
{
    // The location and size of the gate
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // Create a path to draw the gate shape
    auto path = gc->CreatePath();

    // Define the triangle for the NOT gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 2, y); // Middle right (point)
    wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

    // Create the triangle
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2);
    path.AddLineToPoint(p3);
    path.CloseSubpath();

    // Create the inversion bubble
    double bubbleRadius = w * 0.1; // Adjust size as needed
    wxPoint2DDouble bubbleCenter(x + w / 2 + bubbleRadius, y);
    path.AddCircle(bubbleCenter.m_x, bubbleCenter.m_y, bubbleRadius);

    // Draw pins first
    DrawPins(gc);

    // Set pen and brush for drawing the gate
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);

    // Draw the input pin
    //gc->StrokeLine(x - w / 2, y, x - (w / 1.25), y);
    //gc->DrawEllipse(x - (w / 1.25), y - (h / 20), h / 10, h / 10);

    // Draw the output pin
    //gc->StrokeLine(x + w, y, x + w / 1.5, y);
    //gc->DrawEllipse(x + w / 1.05, y - (h / 20), h / 10, h / 10);

    // Draw the NOT gate shape
    gc->SetBrush(*wxWHITE_BRUSH);

    gc->DrawPath(path);
}

/**
 * Computes the output of the NOT gate.
 */
void NotLogicGate::ComputeOutput()
{
    // Get the input pin
    // Negate the input pin state
    // set it to its output pin

    auto inputPin = GetPinInputs()[0];
    State state = inputPin->GetState();

    if (state == State::Zero)
    {
        state = State::One;
    }
    else if (state == State::One)
    {
        state = State::Zero;
    }
    else
    {
        state = State::Unknown;
    }
    GetOutputPins()[0]->SetState(state);
}
