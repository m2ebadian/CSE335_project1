/**
 * @file SRLogicGate.cpp
 * @author Tyler Nguyen and Daniel Wills
 */

#include "pch.h"
#include "SRLogicGate.h"


using namespace std;

/// Size of the Flip Flop in pixels @return wxSize (size of the FlipFlop)
const wxSize SRFlipFlopSize(50, 75);

/// Gap between the edge of the flip-flop and the labels
const int SRFlipFlopLabelMargin = 3;

/**
 * Constructor for SR Logic Gate
 * @param game The game this SR Logic Gate belongs to
 */
SRLogicGate::SRLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(SRFlipFlopSize);

    // Get location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    const wxPoint InputPinLocation1((x - w / 1.2), (y + h / 2.75));
    const wxPoint InputPinLocation2((x - w / 1.2), (y - h / 2.75));
    const wxPoint OutputPinLocation1((x + w / 1.2), (y + h / 2.75));
    const wxPoint OutputPinLocation2((x + w / 1.2), (y - h / 2.75));

    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation1));
    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation2));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation1));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation2));
    auto output = GetOutputPins();
    output[1]->SetState(State::Zero); //Q
    output[0]->SetState(State::One); //Q'
}

/**
 * Draw the SR logic gate
 * @param gc the graphics context we are drawing on
 */
void SRLogicGate::Draw(wxGraphicsContext* gc)
{
    // Create path to draw SR Flip Flop
    auto path = gc->CreatePath();

    // Get location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // Define points for SR Flip Flop
    wxPoint2DDouble topLeft(x - w / 2, y - h / 2);
    wxPoint2DDouble topRight(x + w / 2, y - h / 2);
    wxPoint2DDouble bottomRight(x + w / 2, y + h / 2);
    wxPoint2DDouble bottomLeft(x - w / 2, y + h / 2);

    // Draw SR Flip Flop
    path.MoveToPoint(topLeft);
    path.AddLineToPoint(topRight);
    path.AddLineToPoint(bottomRight);
    path.AddLineToPoint(bottomLeft);
    path.CloseSubpath();


    DrawPins(gc);

    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);

    // Bottom input
    //gc->StrokeLine((x - w / 3), (y + h / 2.75), (x - w / 1.2), (y + h / 2.75));
    //gc->DrawEllipse(((-h / 20) + x - w / 1.2), ((-h / 20) + y + h / 2.75), h / 10, h / 10);

    // Top input
    //gc->StrokeLine((x - w / 3), (y - h / 2.75), (x - w / 1.2), (y - h / 2.75));
    //gc->DrawEllipse(((-h / 20) + x - w / 1.2), ((-h / 20) + y - h / 2.75), h / 10, h / 10);

    // Bottom output
    //gc->StrokeLine((x + w / 3), (y + h / 2.75), (x + w / 1.2), (y + h / 2.75));
    //gc->DrawEllipse(((-h / 20) + x + w / 1.2), ((-h / 20) + y + h / 2.75), h / 10, h / 10);

    // Top output
    //gc->StrokeLine((x + w / 3), (y - h / 2.75), (x + w / 1.2), (y - h / 2.75));
    //gc->DrawEllipse(((-h / 20) + x + w / 1.2), ((-h / 20) + y - h / 2.75), h / 10, h / 10);


    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->DrawPath(path);

    // Draw the Labels S, R, Q, Q'
    auto font = gc->CreateFont(15, L"Arial",
                               wxFONTFLAG_BOLD, *wxBLACK);
    gc->SetFont(font);
    gc->DrawText("S", x - w / 2 + SRFlipFlopLabelMargin, y - h / 2 + SRFlipFlopLabelMargin); //S
    gc->DrawText("R", x - w / 2 + SRFlipFlopLabelMargin, y + h / 2 - SRFlipFlopLabelMargin - 15); //R
    gc->DrawText("Q", x + w / 2 - SRFlipFlopLabelMargin - 14, y - h / 2 + SRFlipFlopLabelMargin); //Q
    gc->DrawText("Q'", x + w / 2 - SRFlipFlopLabelMargin - 14, y + h / 2 - SRFlipFlopLabelMargin - 15); //Q'
}

/**
 * Main logic behind the SR Logic gate, changes the pin states.
 */
void SRLogicGate::ComputeOutput()
{
    auto inputPins = GetPinInputs();

    auto sInput = inputPins[1];
    auto rInput = inputPins[0];

    auto output = GetOutputPins();
    auto qOut = output[1];
    auto qBarOut = output[0];

    auto sState = sInput->GetState();
    auto rState = rInput->GetState();

    if (sState == State::One && rState == State::One) {
        qOut->SetState(State::Zero);
        qBarOut->SetState(State::Zero);
    }
    else if (sState == State::One) {
        qOut->SetState(State::One);
        qBarOut->SetState(State::Zero);
    } else if (rState == State::One)
    {
        qOut->SetState(State::Zero);
        qBarOut->SetState(State::One);
    }
}
