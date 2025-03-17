/**
* @file InputLogicGate.h
* @author  Daniel, Mehrshad, Connor, Tyler, Soami
 * @brief Declaration of the InputLogicGate class for handling input logic gates in the game.
 *
 * This class provides functionality for drawing and managing the input logic gate,
 * including setting input pin values and accepting visitors for processing.
 */
 
#ifndef INPUTLOGICGATE_H
#define INPUTLOGICGATE_H
#include "LogicGate.h"



/**
 * @class InputLogicGate
 * @brief Represents an input logic gate in the game.
 *
 * The `InputLogicGate` class is responsible for managing an input gate,
 * drawing it, and interacting with visitors for processing. This gate
 * accepts an input pin state and is part of the game's logic gate.
 */
class InputLogicGate : public LogicGate
{
private:

public:
    /**
     * @brief Constructor for the Input Logic Gate.
     *
     * @param game The game this Input gate belongs to.
     */
    InputLogicGate(Game* game);

    /// Default constructor (disabled)
    InputLogicGate() = delete;

    /// Copy constructor (disabled)
    InputLogicGate(const InputLogicGate&) = delete;

    /// Assignment operator (disabled)
    void operator=(const InputLogicGate&) = delete;

    /**
     * @brief Draw the Input Logic Gate.
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
        //std::cout << "InputLogicGateAccept" << std::endl;
        visitor->VisitInputLogicGate(this);
        visitor->VisitLogicGate(this);
    }


    /**
    * @brief Retrieves the current value of the input pin.
    *
    * @return The `State` representing the current input pin value.
    */
    State GetInputPinValue();
};



#endif //INPUTLOGICGATE_H
