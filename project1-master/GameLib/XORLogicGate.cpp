/**
 * @file XORLogicGate.cpp
 * @author Mehrshad Bagherebadian
 */

#include "pch.h"
#include "XORLogicGate.h"
#include "LogicGate.h"

using namespace std;

/**
 * @brief Size of the XOR gate in pixels.
 * @return wxSize
 */
const wxSize XorGateSize(75, 50);

/**
 * @brief Constructor for the XOR Logic Gate.
 *
 * Initializes the XOR logic gate with the specified game object.
 */
XORLogicGate::XORLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(XorGateSize);

    // Get the location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    const wxPoint InputPinLocation1((x - w / 1.3), (y + h / 4.5));
    const wxPoint InputPinLocation2((x - w / 1.3), (y - h / 4.5));
    const wxPoint OutputPinLocation1((x + w / 1.25), (y));

    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation1));
    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation2));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation1));
}

/**
 * @brief Draws the XOR logic gate.
 *
 * This function creates and draws the shape of the XOR gate on the given
 * graphics context using Bezier curves.
 */
void XORLogicGate::Draw(wxGraphicsContext* gc)
{
    // Create a path for the OR gate shape
    auto orGatePath = gc->CreatePath();

    // Get the location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // ---- OR Gate Points ---- //
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left of XOR gate
    wxPoint2DDouble p2(x + w / 2, y);         // Center right of XOR gate (tip)
    wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left of XOR gate

    // Control points for OR gate Bezier curves
    auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
    auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
    auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

    // Create the path for the OR gate
    orGatePath.MoveToPoint(p1);
    orGatePath.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
    orGatePath.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
    orGatePath.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
    orGatePath.CloseSubpath();

    // ---- Create the XOR Curve ---- //
    auto xorCurvePath = gc->CreatePath();

    // Define an offset to shift the curve to the left
    wxPoint2DDouble offset(-w * 0.1, 0); // Shift left by 10% of width

    // Points for the leftmost curve of the OR gate, shifted left
    wxPoint2DDouble xorStartPoint = p3 + offset;
    wxPoint2DDouble xorControlPoint1 = p3 + controlPointOffset3 + offset;
    wxPoint2DDouble xorControlPoint2 = p1 + controlPointOffset3 + offset;
    wxPoint2DDouble xorEndPoint = p1 + offset;

    // Move to the start point of XOR curve
    xorCurvePath.MoveToPoint(xorStartPoint);

    // Add the Bezier curve
    xorCurvePath.AddCurveToPoint(xorControlPoint1, xorControlPoint2, xorEndPoint);

    // ---- Draw the OR Gate ---- //
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->DrawPath(orGatePath); // Draw OR gate

    // ---- Draw the XOR Curve ---- //
    wxPen thickPen(wxColour(0, 0, 0), 2);
    gc->SetPen(thickPen);
    gc->StrokePath(xorCurvePath); // Draw XOR curve

    // ---- Inputs and Outputs ---- //
    DrawPins(gc);
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);
}




/**
 * @brief Computes the output of the XOR logic gate based on its input pins.
 *
 * This function evaluates the XOR logic: if both inputs are the same, the output is set to `State::Zero`;
 * if the inputs differ, the output is set to `State::One`. If any input is in an unknown state,
 * the output is also set to `State::Unknown`.
 */
void XORLogicGate::ComputeOutput()
{
    // Get input pins
    auto inputPins = GetPinInputs();
    auto input1 = inputPins[0];
    auto input2 = inputPins[1];
    
    // Get output pin (XOR gate has single output)
    auto outputPin = GetOutputPins()[0];
    
    // If either input is unknown, output is unknown
    if (input1->GetState() == State::Unknown || input2->GetState() == State::Unknown)
    {
        outputPin->SetState(State::Unknown);
        return;
    }
    
    // XOR logic: output is 1 if inputs are different, 0 if they are the same
    if (input1->GetState() == input2->GetState())
    {
        outputPin->SetState(State::Zero);  // Same inputs = 0
    }
    else
    {
        outputPin->SetState(State::One);   // Different inputs = 1
    }
}
