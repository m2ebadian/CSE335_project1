/**
 * @file OutputLogicGate.cpp
 * @author Daniel Wills, Saomi Kapadia, Mehrshad Bagherebadian, Tyler Nguyen, Conner O'Sullivan
 */

#include "pch.h"
#include "OutputLogicGate.h"

using namespace std;

/**
 * @brief Size of the gate in pixels.
 * @return wxSize
 */
const wxSize OutputGateSize(0, 0);

/**
 * @brief Constructor for the Output Logic Gate.
 *
 * Initializes the Output logic gate with the specified game object.
 */
OutputLogicGate::OutputLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(OutputGateSize);
    const wxPoint OutputPinLocation((0), (0));
    CreateOutputPin(std::make_shared<PinOutput>(this, OutputPinLocation));
}

/**
 * @brief Draws the Output logic gate.
 *
 * This function creates and draws the shape of the Output gate on the given
 * @param gc context using Bezier curves.
 */
void OutputLogicGate::Draw(wxGraphicsContext* gc)
{
    DrawPins(gc);
}

/**
 * Set the output state of the gate.
 * @param state
 */
void OutputLogicGate::SetOutputState(State state)
{
 // Update any connected output pins with the new state
 for (auto& outputPin : GetOutputPins())
 {
   outputPin->SetState(state);
 }
}

