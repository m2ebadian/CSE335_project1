/**
 * @file PinInput.h
 * @author Daniel Wills
 *
 * Input pin base class
 */

#ifndef PININPUT_H
#define PININPUT_H

#include "PinOutput.h"
#include "Game.h"
#include "Pin.h"

class Item;

/**
 * Input pin base class
 */
class PinInput: public Pin
{
private:

    /// Output pin we are connected to
    PinOutput* mLine = nullptr;

public:
    PinInput(LogicGate* owner, wxPoint location);

    void Draw(wxGraphicsContext* gc) override;

    wxPoint GetAbsoluteLocation();

    bool Catch(PinOutput* rod, wxPoint lineEnd);

    /**
     * Set the line that has caught this pin
     * @param line
     */
    void SetLine(PinOutput* line) { mLine = line; }

    /**
    * Get the line variable of the input pin
    * @return mLine
    */
    PinOutput* GetLine() { return mLine; }

    /// Sets the current state of the input pin
    void SetState(State state) override;
};


#endif //PININPUT_H
