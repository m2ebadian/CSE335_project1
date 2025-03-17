/**
 * @file SRLogicGate.h
 * @author Tyler Nguyen
 *
 * Class for SR Latch Logic Gate
 */

#ifndef SRLOGICGATE_H
#define SRLOGICGATE_H

#include "LogicGate.h"

/**
 * Class for SR Latch Logic Gate
 */
class SRLogicGate : public LogicGate
{
private:
    bool mSState; ///< S input state tracker
    bool mRState; ///< R input state tracker

public:
    SRLogicGate(Game* game);

    /// Default constructor (disabled)
    SRLogicGate() = delete;
    /// Copy Constructor (disabled)
    SRLogicGate(const SRLogicGate&) = delete;
    /// Assignment Operator (disabled)
    void operator=(const SRLogicGate&) = delete;


    void Draw(wxGraphicsContext* gc) override;
    void ComputeOutput() override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitSRLogicGate(this);
        visitor->VisitLogicGate(this);
    }
};


#endif //SRLOGICGATE_H
