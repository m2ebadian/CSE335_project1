/**
 * @file UpdateVisitor.h
 * @author Tyler Nguyen
 *
 *
 */

#ifndef UPDATEVISITOR_H
#define UPDATEVISITOR_H

#include "Banner.h"
#include "ItemVisitor.h"
#include "Conveyor.h"

class Conveyor;

/**
 * Visitor class used to update the conveyor
 */
class UpdateVisitor : public ItemVisitor
{
private:
    double mElapsed; ///< Time elapsed since last update

public:
    /**
     * Constructor for the visitor
     * @param elapsed time elapsed
     */
    UpdateVisitor(double elapsed) : mElapsed(elapsed)
    {
    }

    /**
     * Updates the conveyor
     * @param conveyor the conveyor we are visiting
     */
    void VisitConveyor(Conveyor* conveyor) override
    {
        conveyor->Update(mElapsed);  // Call Conveyor's update method
    }
};


#endif //UPDATEVISITOR_H
