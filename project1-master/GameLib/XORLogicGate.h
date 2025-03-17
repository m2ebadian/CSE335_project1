/**
 * @file XORLogicGate.h
 * @author Mehrshad Bagherebadian
 *
 *
 */
 
#ifndef XORLOGICGATE_H
#define XORLOGICGATE_H



#include "LogicGate.h"

/**
 * @class XORLogicGate
 * @brief Class for the XOR logic gate.
 *
 * Represents the XOR logic gate used in the game.
 */
class XORLogicGate : public LogicGate
{
public:
 /**
  * @brief Constructor for the XOR Logic Gate.
  *
  * @param game The game this XOR gate belongs to.
  */
 XORLogicGate(Game* game);

 /// Default constructor (disabled)
 XORLogicGate() = delete;

 /// Copy constructor (disabled)
 XORLogicGate(const XORLogicGate&) = delete;

 /// Assignment operator (disabled)
 void operator=(const XORLogicGate&) = delete;

 /**
  * @brief Draw the XOR Logic Gate.
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
  visitor->VisitXORLogicGate(this);
  visitor->VisitLogicGate(this);
 }


 /// Computes the output of the XOR logic gate and can be override if necessary
 void ComputeOutput() override;
};

#endif //XORLOGICGATE_H
