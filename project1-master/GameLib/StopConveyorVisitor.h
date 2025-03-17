/**
 * @file StopConveyorVisitor.h
 * @author Conner O'Sullivan
 *
 *
 */
 
#ifndef STOPCONVEYORVISITOR_H
#define STOPCONVEYORVISITOR_H

#include "ItemVisitor.h"
#include "Conveyor.h"

/**
 * @class StopConveyorVisitor
 * @brief A visitor class to stop conveyor items.
 *
 * The StopConveyorVisitor class is a concrete implementation of the
 * ItemVisitor base class, specifically designed to stop conveyor items in
 * the simulation when visited.
 */

class StopConveyorVisitor : public ItemVisitor
{
 public:

 /**
 * @brief Stops the conveyor item.
 *
 * This function overrides the VisitConveyor function from the ItemVisitor
 * class. It stops the conveyor by calling the Stop method on the given
 * Conveyor pointer.
 *
 * @param conveyor Pointer to the conveyor item to be stopped.
 */

 void VisitConveyor(Conveyor* conveyor) override
 {
  conveyor->Stop();
 }

};


#endif //STOPCONVEYORVISITOR_H
