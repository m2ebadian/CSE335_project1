/**
* @file OrLogicGate.cpp
 * @author Soami Kapadia, Daniel Wills
 * @brief Implementation of the OR logic gate class.
 */

#include "pch.h"
#include "OrLogicGate.h"
#include "LogicGate.h"


using namespace std;
/**
 * @brief Size of the OR gate in pixels.
 * @return wxSize
 */
const wxSize OrGateSize(75, 50);


/**
 * @brief Constructor for the OR Logic Gate.
 *
 * Initializes the OR logic gate with the specified game object.
 */
OrLogicGate::OrLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(OrGateSize);

    // Get the location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    const wxPoint InputPinLocation1((x - w / 1.5), (y + h / 4.5));
    const wxPoint InputPinLocation2((x - w / 1.5), (y - h / 4.5));
    const wxPoint OutputPinLocation1((x + w / 1.5), (y));

    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation1));
    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation2));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation1));
}

/**
 * @brief Draws the OR logic gate.
 *
 * This function creates and draws the shape of the OR gate on the given
 * graphics context using Bezier curves.
 */
void OrLogicGate::Draw(wxGraphicsContext* gc)
{
    // Create a path to draw the OR gate shape
    auto path = gc->CreatePath();

    // Get the location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // Define the points for the OR gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
    wxPoint2DDouble p2(x + w / 2, y); // Center right
    wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

    // Control points used to create the Bezier curves
    auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
    auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
    auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

    // Create the path for the gate
    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
    path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
    path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
    path.CloseSubpath();


    DrawPins(gc);

    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);

    // Bottom input
    //gc->StrokeLine((x - w / 3), (y + h / 4.5), (x - w / 1.5), (y + h / 4.5));
    //gc->DrawEllipse((x - w / 1.5), ((-h / 20) + y + h / 4.5), h / 10, h / 10);

    // Top input
    //gc->StrokeLine((x - w / 3), (y - h / 4.5), (x - w / 1.5), (y - h / 4.5));
    //gc->DrawEllipse((x - w / 1.5), ((-h / 20) + y - h / 4.5), h / 10, h / 10);

    // Middle output
    //gc->StrokeLine((x + w / 3), (y), (x + w / 1.5), (y));
    //gc->DrawEllipse((x + w / 1.5), ((-h / 20) + y), h / 10, h / 10);


    // Set pen and brush
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxWHITE_BRUSH);

    // Draw the path
    gc->DrawPath(path);
}

/**
 * @brief Compute Output of Or Gate
 */
void OrLogicGate::ComputeOutput()
{
 for (auto inputPin : GetPinInputs())
 {
  if (inputPin->GetState() == State::Unknown)
  {
   /// Since OR gate only has one output state
   GetOutputPins()[0]->SetState(State::Unknown);
  }

  if (inputPin->GetState() == State::One)
  {
   GetOutputPins()[0]->SetState(State::One);
   return;
  }
 }

 GetOutputPins()[0]->SetState(State::Zero);
}

