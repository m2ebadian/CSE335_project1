/**
 * @file InputLogicGate.cpp
 * @author Daniel Wills, Saomi Kapadia, Mehrshad Bagherebadian, Tyler Nguyen, Conner O'Sullivan
 */

#include "pch.h"
#include "InputLogicGate.h"

using namespace std;

/**
 * @brief Size of the gate in pixels.
 * @return wxSize
 */
const wxSize InputGateSize(0, 0);

/**
 * @brief Constructor for the Input Logic Gate.
 *
 * Initializes the Input logic gate with the specified game object.
 */
InputLogicGate::InputLogicGate(Game* game) : LogicGate(game)
{
    SetGateSize(InputGateSize);
    const wxPoint InputPinLocation((0), (0));
    CreateInputPin(std::make_shared<PinInput>(this, InputPinLocation));
}

/**
 * @brief Draws the Input logic gate.
 *
 * This function creates and draws the shape of the Input gate on the given
 * graphics context using Bezier curves.
 */
void InputLogicGate::Draw(wxGraphicsContext* gc)
{
    DrawPins(gc);
}

State InputLogicGate::GetInputPinValue()
{
    if (!GetPinInputs().empty())
    {
        auto InputPins = GetPinInputs();
        auto input = InputPins[0];
        return input->GetState();
    }
    return State::Unknown;
}
