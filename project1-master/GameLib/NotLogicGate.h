/**
 * @file NotLogicGate.h
 * @author Soami Kapadia
 *
 *
 */

#ifndef NOTLOGICGATE_H
#define NOTLOGICGATE_H
#include "LogicGate.h"


/**
 * @class NotLogicGate
 * @brief Class for the NOT logic gate.
 *
 * Represents the NOT logic gate used in the game.
 */
class NotLogicGate : public LogicGate
{
private:
    /**
     * @brief Size of the NOT gate.
     *
     * Defines the size of the NOT gate for graphical representation.
     */

public:
    /**
     * @brief Constructor for the NOT Logic Gate.
     *
     * @param game The game this NOT gate belongs to.
     */
    NotLogicGate(Game* game);

    /// Default constructor (disabled)
    NotLogicGate() = delete;

    /// Copy constructor (disabled)
    NotLogicGate(const NotLogicGate&) = delete;

    /// Assignment operator (disabled)
    void operator=(const NotLogicGate&) = delete;

    /**
     * @brief Draw the NOT Logic Gate.
     *
     * @param gc Pointer to the wxGraphicsContext used for drawing.
     */
    void Draw(wxGraphicsContext* gc) override;

    /**
     * Compute the output state of the NOT gate
     */
    void ComputeOutput() override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitNotLogicGate(this);
        visitor->VisitLogicGate(this);
    }
};


#endif //NOTLOGICGATE_H
