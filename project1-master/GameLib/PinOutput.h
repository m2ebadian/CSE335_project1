/**
 * @file PinOutput.h
 * @author Daniel Wills
 *
 * The output pin base class
 */

#ifndef PINOUTPUT_H
#define PINOUTPUT_H

#include "IDraggable.h"
#include "Pin.h"

class Item;
class PinInput;

/**
* The output pin base class
*/
class PinOutput : public Pin, public IDraggable
{
private:
    /// Location of the line end when dragging
    wxPoint mLineEnd;

    /// Are we dragging the line?
    bool mDragging = false;

    /// Have we caught anything?
    PinInput* mCaught = nullptr;

    ///Vector that stores the caught PinInputs
    std::vector<PinInput*> mCaughts;

    /// boolean for whether control point should be shown or not
    bool mShowControl = false;

public:
    PinOutput(LogicGate* owner, wxPoint location);
    void SetLocation(double x, double y) override;
    void Draw(wxGraphicsContext* gc) override;
    bool HitTest(int x, int y);
    void MoveToFront() override;
    void Release() override;
    void SetCaught(PinInput* caught);

    void RemoveCaughtPinInput(PinInput* caught);

    /// Maximum offset of Bezier control points relative to line ends
    static constexpr double BezierMaxOffset = 200;

    /// Line with for drawing lines between pins
    static const int LineWidth = 3;

    /// Default length of line from the pin
    static const int DefaultLineLength = 20;

    /**
     * @brief Sets the visibility of control options for this pin.
     *
     * @param showControl A boolean indicating whether control options should be shown (`true`) or hidden (`false`).
     */
    void SetShowControl(bool showControl) { mShowControl = showControl; }
};


#endif //PINOUTPUT_H
