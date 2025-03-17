/**
 * @file AndLogicGate.h
 * @author Soami Kapadia
 *
 *
 */

#ifndef ANDLOGICGATE_H
#define ANDLOGICGATE_H
#include "LogicGate.h"

/**
 * @class AndLogicGate
 * @brief Class for the AND logic gate.
 *
 * Represents the AND logic gate used in the game.
 */
class AndLogicGate : public LogicGate
{
private:
    /**
     * @brief Size of the AND gate.
     *
     * Defines the size of the AND gate for graphical representation.
     */

public:
    /**
     * @brief Constructor for the AND Logic Gate.
     *
     * @param game The game this AND gate belongs to.
     */
    AndLogicGate(Game* game);

    /// Default constructor (disabled)
    AndLogicGate() = delete;

    /// Copy constructor (disabled)
    AndLogicGate(const AndLogicGate&) = delete;

    /// Assignment operator (disabled)
    void operator=(const AndLogicGate&) = delete;

    /**
     * @brief Draw the AND Logic Gate.
     *
     * @param gc Pointer to the wxGraphicsContext used for drawing.
     */
    void Draw(wxGraphicsContext* gc) override;
    void ComputeOutput() override;

    /**
    * @brief Accept a visitor
    *
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitAndLogicGate(this);
        visitor->VisitLogicGate(this);
    }
};


#endif //ANDLOGICGATE_H
