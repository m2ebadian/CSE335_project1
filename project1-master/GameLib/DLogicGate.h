/**
 * @file DLogicGate.h
 * @author Soami Kapadia
 *
 *
 */

#ifndef DLOGICGATE_H
#define DLOGICGATE_H
#include "LogicGate.h"


/**
 * @class DLogicGate
 * @brief Class for the D Flip Flop logic gate.
 *
 * Represents the D Flip Flop logic gate used in the game.
 */
class DLogicGate : public LogicGate
{
private:
    /**
     * @brief Size of the D Flip Flop gate.
     *
     * Defines the size of the D Flip Flop gate for graphical representation.
     */

    State mPreviousClockState = State::Zero;

public:
    /**
     * @brief Constructor for the D Flip Flop Logic Gate.
     *
     * @param game The game this D Flip Flop gate belongs to.
     */
    DLogicGate(Game* game);

    /// Default constructor (disabled)
    DLogicGate() = delete;

    /// Copy constructor (disabled)
    DLogicGate(const DLogicGate&) = delete;

    /// Assignment operator (disabled)
    void operator=(const DLogicGate&) = delete;

    /**
     * @brief Draw the D Flip Flop Logic Gate.
     *
     * @param gc Pointer to the wxGraphicsContext used for drawing.
     */
    void Draw(wxGraphicsContext* gc) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitDLogicGate(this);
        visitor->VisitLogicGate(this);
    }

    /**
     * @brief Computes the output of the D logic gate based on its current inputs.
     *
     * This function processes the input state and calculates the corresponding output for the gate.
     */
    void ComputeOutput() override;
};


#endif //DLOGICGATE_H
