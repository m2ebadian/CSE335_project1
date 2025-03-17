/**
* @file LogicGate.cpp
 * @brief Implementation of the LogicGate class.
 *
 * This file contains the implementation of the LogicGate class
 * which represents a logic gate in the game.
 *
 * @author Soami Kapadia, Daniel Wills
 */

#include "pch.h"
#include "LogicGate.h"
#include "PinInput.h"
#include "PinOutput.h"


/**
 * Constructor for LogicGate.
 *
 * @param game the game we're adding the gate to
 */
LogicGate::LogicGate(Game* game) : Item(game)
{
}

/**
 * @brief Create the pins for the logic gate.
 *
 * This function creates the input and output pins for the logic gate.
 * It equally spaces the pins by dividing the gate height into 2n parts,
 * placing the pins at odd-numbered positions.
 *
 * @param graphics the graphic context we're drawing on
 */
void LogicGate::DrawPins(wxGraphicsContext* graphics)
{
    for (auto input : mInputPins)
    {
        input->Draw(graphics);
    }

    for (auto output : mOutputPins)
    {
        output->Draw(graphics);
    }
}

/**
 * Destructor
 */
LogicGate::~LogicGate()
{
}

/**
 * Test to see if we clicked on some draggable inside the item.
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return Whatever we clicked on or NULL if none
 */
std::shared_ptr<IDraggable> LogicGate::HitDraggable(int x, int y)
{
    for (auto output : mOutputPins)
        if (output->HitTest(x, y))
        {
            return output;
        }

    return nullptr;
}

/**
 * Did we click on the pin end?
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return Did we click on it?
 */
bool LogicGate::HitTest(int x, int y)
{
    double testX = x - GetX() + GetWidth() / 2;
    double testY = y - GetY() + GetHeight() / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= GetWidth() || testY >= GetHeight())
    {
        // We are outside the image
        return false;
    }
    return true;
}

/**
 * Try to catch a wire at the new x,y location of the pin end
 * @param pinOutput PinOutput we are trying to catch from
 * @param lineEnd The line end point
 * @return true if caught
 */
bool LogicGate::Catch(PinOutput* pinOutput, wxPoint lineEnd)
{
    //Do not let output pins connect to input pins on same logic gate
    //I tried doing (pinOutput->GetOwner() != input->GetOwner()) but it did
    //not seem to work.
    for (auto input : mInputPins)
    {
        if (input->Catch(pinOutput, lineEnd))
        {
            return true;
        }
    }
    return false;
}
