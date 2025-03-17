/**
 * @file ToggleControlPointsVisitor.h
 * @author Conner O'Sullivan
 *
 * Visitor to change the show control state of the wires
 *
 * NOTE: WILL ALSO HAVE TO IMPLEMENT THIS FOR THE PANEL PINS AND THE BEAM PIN
 */

#ifndef TOGGLECONTROLPOINTSVISITOR_H
#define TOGGLECONTROLPOINTSVISITOR_H

#include "ItemVisitor.h"



/**
 * @class ToggleControlPointsVisitor
 * @brief A visitor that toggles the display of control points for wires and pins.
 *
 * The `ToggleControlPointsVisitor` class is used to change the visibility of control
 * points on wires, panel pins, and beam pins. It sets a visibility flag that determines
 * if additional control information for these items should be shown.
 *
 * @note Implementation may also be required for panel pins and beam pins.
 */
class ToggleControlPointsVisitor : public ItemVisitor
{
public:
    /**
     * Constructor for the visitor
     *
     * @param showCurve Bool determining whether we want the extra info or not
     */
    ToggleControlPointsVisitor(bool showCurve) : mShowControl(showCurve)
    {
    }

    /**
     * Visit the logicGate so it toggles the curve control point view
     *
     * @param logicGate the output pin we're visiting
     */
    void VisitLogicGate(LogicGate* logicGate) override
    {
        logicGate->SetShowControlOutputPins(mShowControl);
    }

private:
    bool mShowControl; ///< To store the show/hide flag
};

#endif //TOGGLECONTROLPOINTSVISITOR_H
