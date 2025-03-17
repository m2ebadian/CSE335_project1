/**
* @file OutputLogicGate.h
* @author Daniel Wills, Mehrshad Bagherebadian, Conner, Tyler, Saomi
 * @brief Declaration of the OutputLogicGate class, representing an output logic gate in the game.
 *
 * This file contains the definition of the OutputLogicGate class, which handles
 * the output logic gate functionality, including drawing and interacting with visitors.
 */
 
#ifndef OUTPUTLOGICGATE_H
#define OUTPUTLOGICGATE_H
#include "LogicGate.h"



/**
 * @class OutputLogicGate
 * @brief Represents an output logic gate in the game.
 *
 * The `OutputLogicGate` class is responsible for managing an output gate, drawing it,
 * setting its output state, and processing visitors. This class is part of the logic gate
 * hierarchy in the game.
 */
class OutputLogicGate : public LogicGate
{
private:

public:
    /**
     * @brief Constructor for the Output Logic Gate.
     *
     * @param game The game this Output gate belongs to.
     */
    OutputLogicGate(Game* game);

    /// Default constructor (disabled)
    OutputLogicGate() = delete;

    /// Copy constructor (disabled)
    OutputLogicGate(const OutputLogicGate&) = delete;

    /// Assignment operator (disabled)
    void operator=(const OutputLogicGate&) = delete;

    /// Draw the output logic gate
    void Draw(wxGraphicsContext* gc) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        //std::cout << "OutputLogicGateAccept" << std::endl;
        visitor->VisitOutputLogicGate(this);
        visitor->VisitLogicGate(this);
    }

    /// Set the output state to the correct state
    void SetOutputState(State state);

    /**
     * @brief Computes the output state of the output logic gate.
     *
     * This function is responsible for calculating the gate's output state based on its inputs.
     * It can be overridden to implement specific logic in derived classes.
     */
    void ComputeOutput() override {};
};



#endif //OUTPUTLOGICGATE_H
