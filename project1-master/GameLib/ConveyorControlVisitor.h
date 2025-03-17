/**
* @file ConveyorControlVisitor.h
 * @author Mehrshad Bagherebadian
 *
 *
 */

#ifndef CONVEYORCONTROLVISITOR_H
#define CONVEYORCONTROLVISITOR_H


#include "ItemVisitor.h"
#include "Conveyor.h"
#include "Game.h"

/**
 * A visitor that handles control of the conveyor's start and stop functionality.
 */
class ConveyorControlVisitor : public ItemVisitor
{
public:
    /**
     * Constructor for the visitor
     *
     * @param clickX where we clicked in the x coordinates.
     *
     * @param clickY where we clicked in the y coordinates.
     */
    ConveyorControlVisitor(int clickX, int clickY)
        : mClickX(clickX), mClickY(clickY)
    {
    }


    /**
    * Visit a conveyor object and determine if the Start/Stop buttons were clicked.
    * @param conveyor The conveyor being visited.
    */
    void VisitConveyor(Conveyor* conveyor) override
    {
        // Convert mouse click coordinates from screen space to virtual space
        int virtualX = conveyor->GetGame()->GetVirtualPixelsX(mClickX);
        int virtualY = conveyor->GetGame()->GetVirtualPixelsY(mClickY);

        wxPoint panelLocation = conveyor->GetPanelLocation();
        int panelX = conveyor->GetX() + panelLocation.x;
        int panelY = conveyor->GetY() + panelLocation.y;

        // Check if the virtual mouse click occurred within the Start button bounds
        if (StartButtonRect.Contains(virtualX - panelX, virtualY - panelY))
        {
            conveyor->Start();
            //std::cout << "Start button clicked, conveyor started" << std::endl;
            mButtonClicked = true; // Set the flag when the button is clicked
            return; // Exit after starting to avoid further checks
        }

        // Check if the virtual mouse click occurred within the Stop button bounds
        else if (StopButtonRect.Contains(virtualX - panelX, virtualY - panelY))
        {
            conveyor->Stop();
            //std::cout << "Stop button clicked, conveyor stopped" << std::endl;
            mButtonClicked = true; // Set the flag when the button is clicked
        }
    }

    /**
     * Check if a button (Start or Stop) was clicked.
     * @return True if a button was clicked, false otherwise.
     */
    bool WasButtonClicked() const { return mButtonClicked; }

private:
    int mClickX; ///< X position of the mouse click
    int mClickY; ///< Y position of the mouse click
    bool mButtonClicked = false; ///< Whether the button has been clicked
};


#endif //CONVEYORCONTROLVISITOR_H
