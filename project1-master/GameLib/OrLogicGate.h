/**
* @file OrLogicGate.h
 * @author Soami Kapadia, Daniel Wills
 * @brief Header for the OR logic gate class.
 */

#ifndef ORLOGICGATE_H
#define ORLOGICGATE_H
#include "LogicGate.h"

/**
 * @class OrLogicGate
 * @brief Class for the OR logic gate.
 *
 * Represents the OR logic gate used in the game.
 */
class OrLogicGate : public LogicGate
{
private:
    /**
     * @brief Size of the OR gate.
     *
     * Defines the size of the OR gate for graphical representation.
     */

public:
    /**
     * @brief Constructor for the OR Logic Gate.
     *
     * @param game The game this OR gate belongs to.
     */
    OrLogicGate(Game* game);

    /// Default constructor (disabled)
    OrLogicGate() = delete;

    /// Copy constructor (disabled)
    OrLogicGate(const OrLogicGate&) = delete;

    /// Assignment operator (disabled)
    void operator=(const OrLogicGate&) = delete;

    /**
     * @brief Draw the OR Logic Gate.
     *
     * @param gc Pointer to the wxGraphicsContext used for drawing.
     */
    void Draw(wxGraphicsContext* gc) override;

    /**
    * @brief Accept a visitor
    *
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        //std::cout << "OrLogicGateAccept" << std::endl;
        visitor->VisitOrLogicGate(this);
        visitor->VisitLogicGate(this);
    }

    void ComputeOutput() override;
};

#endif // ORLOGICGATE_H
