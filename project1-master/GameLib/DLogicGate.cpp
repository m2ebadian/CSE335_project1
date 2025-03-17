/**
 * @file DLogicGate.cpp
 * @author Soami Kapadia, Daniel Wills
 */


#include "pch.h"
#include "DLogicGate.h"

/**
 * @brief Size of the D Flip Flop gate in pixels.
 * @return wxSize
 */
const wxSize DGateSize(50, 75);

/// Gap between the edge of the flip flop and the labels
const int DGateLabelMargin = 3;

/// Font size for labels
const int DGateFontSize = 15;


/**
 * @brief Constructor for the D Flip Flop Logic Gate.
 *
 * Initializes the D Flip Flop logic gate with the specified game object.
 */
DLogicGate::DLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(DGateSize);

    // Get location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    const wxPoint InputPinLocation1((x - w / 1.2), (y + h / 4.0));
    const wxPoint InputPinLocation2((x - w / 1.2), (y - h / 4.0));
    const wxPoint OutputPinLocation1((x + w / 1.2), (y + h / 4.0));
    const wxPoint OutputPinLocation2((x + w / 1.2), (y - h / 4.0));

    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation1)); // Clock
    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation2)); // D
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation1)); // Q
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation2)); // Q'

    auto outputGates = GetOutputPins();
    outputGates[0]->SetState(State::One);
    outputGates[1]->SetState(State::Zero);

}


/**
 * @brief Draws the D Flip Flop logic gate.
 *
 * This function creates and draws the shape of the D Flip Flop gate on the given
 * gc context using Bezier curves.
 */
void DLogicGate::Draw(wxGraphicsContext* gc)
{
    // Get position and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    DrawPins(gc);

    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);

    // Bottom input
    //gc->StrokeLine((x - w / 3), (y + h / 4.0), (x - w / 1.2), (y + h / 4));
    //gc->DrawEllipse(((-h / 20) + x - w / 1.2), ((-h / 20) + y + h / 4.0), h / 10, h / 10);

    // Top input
    //gc->StrokeLine((x - w / 3), (y - h / 4.0), (x - w / 1.2), (y - h / 4));
    //gc->DrawEllipse(((-h / 20) + x - w / 1.2), ((-h / 20) + y - h / 4.0), h / 10, h / 10);

    // Bottom output
    //gc->StrokeLine((x + w / 3), (y + h / 4.0), (x + w / 1.2), (y + h / 4));
    //gc->DrawEllipse(((-h / 20) + x + w / 1.2), ((-h / 20) + y + h / 4.0), h / 10, h / 10);

    // Top output
    //gc->StrokeLine((x + w / 3), (y - h / 4.0), (x + w / 1.2), (y - h / 4));
    //gc->DrawEllipse(((-h / 20) + x + w / 1.2), ((-h / 20) + y - h / 4.0), h / 10, h / 10);


    // Draw the flip-flop rectangle
    wxRect2DDouble rect(x - w / 2, y - h / 2, w, h);
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->DrawRectangle(rect.m_x, rect.m_y, rect.m_width, rect.m_height);

    // Cut the height into fourths
    double fourth = h / 4;

    // Draw Clock input with triangle
    wxPoint2DDouble p1(rect.m_x, y + fourth - DGateFontSize / 2);
    wxPoint2DDouble p2(p1.m_x + DGateFontSize, y + fourth);
    wxPoint2DDouble p3(p1.m_x, y + fourth + DGateFontSize / 2);

    auto path = gc->CreatePath();
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2);
    path.AddLineToPoint(p3);
    path.CloseSubpath();
    gc->DrawPath(path);

    // Draw fonts
    auto font = gc->CreateFont(DGateFontSize, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
    gc->SetFont(font);

    wxString text = "Q";
    wxDouble textWidth, textHeight;
    gc->GetTextExtent(text, &textWidth, &textHeight);

    wxDouble halfTextHeight = textHeight / 2;

    wxString text2 = "Q'";
    gc->GetTextExtent(text2, &textWidth, &textHeight);
    wxDouble halfText2Height = textHeight / 2;

    // Draw D at top
    gc->DrawText(L"D", rect.m_x + DGateLabelMargin, y - fourth - halfTextHeight);

    // Draw Q at top
    gc->DrawText(text, rect.m_x + w - textWidth - DGateLabelMargin, y - fourth - halfTextHeight);

    // Draw Q' at the bottom
    gc->DrawText(text2, rect.m_x + w - textWidth - DGateLabelMargin, y + fourth - halfText2Height);
}

void DLogicGate::ComputeOutput()
{
    auto inputPins = GetPinInputs();
    auto outputPins = GetOutputPins();
    
    // Get D and Clock inputs
    auto dInput = inputPins[1];    // D
    auto clockInput = inputPins[0]; // Clock
    
    // Get Q and Q' outputs
    auto qOutput = outputPins[1];    // Q
    auto qBarOutput = outputPins[0];  // Q'

     // On clock rising edge (transition from 0 to 1)
    if (mPreviousClockState == State::Zero && clockInput->GetState() == State::One)
    {
        // Transfer D input to Q output
        if (dInput->GetState() == State::One)
        {
            qOutput->SetState(State::One);
            qBarOutput->SetState(State::Zero);
        }
        else if (dInput->GetState() == State::Zero)
        {
            qOutput->SetState(State::Zero);
            qBarOutput->SetState(State::One);
        }
    }

    // Store current clock state for next time
    mPreviousClockState = clockInput->GetState();
}
