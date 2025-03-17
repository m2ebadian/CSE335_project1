/**
 * @file ItemCounter.h
 * @author Conner O'Sullivan
 *
 *
 */

#ifndef ITEMCOUNTER_H
#define ITEMCOUNTER_H

#include "ItemVisitor.h"

/**
 * Iterator that counts the number of each item type. Used for LoadTest
 */
class ItemCounter : public ItemVisitor
{
private:
    int mNumSpartys = 0; ///< the number of spartys
    int mNumSensors = 0; ///< the number of sensors
    int mNumBeams = 0; ///< the number of beams
    int mNumProducts = 0; ///< the number of products
    int mNumConveyors = 0; ///< the number of conveyors
    int mNumScoreboards = 0; ///< the number of scoreboards
    int mNumBeginnerBanners = 0; ///< the number of beginner banners
    int mLogicGates = 0; ///< Number of logic gates

public:
    /**
     * Gets the number of Sparty items
     * @return Number of Sparty items
     */
    int GetNumSpartys() { return mNumSpartys; }

 /**
 * Gets the number of logic gate items
 * @return Number of logic gate items
 */
 int GetNumLogicGates() {return mLogicGates;}

    /**
     * Gets the number of Sensor items
     * @return Number of Sensor items
     */
    int GetNumSensors() { return mNumSensors; }

    /**
     * Gets the number of Beam items
     * @return Number of Beam items
     */
    int GetNumBeams() { return mNumBeams; }

    /**
     * Gets the number of Product items
     * @return Number of Product items
     */
    int GetNumProducts() { return mNumProducts; }

    /**
     * Gets the number of Conveyor items
     * @return Number of Conveyor items
     */
    int GetNumConveyors() { return mNumConveyors; }

    /**
     * Gets the number of Scoreboard items
     * @return Number of Scoreboard items
     */
    int GetNumScoreboards() { return mNumScoreboards; }

    /**
     * Visit a Sparty item
     * @param sparty Sparty item to visit
     */
    void VisitSparty(Sparty* sparty) override { mNumSpartys++; }

    /**
     * Visit a Sensor item
     * @param sensor Sensor item to visit
     */
    void VisitSensor(Sensor* sensor) override { mNumSensors++; }

    /**
     * Visit a Beam item
     * @param beam Beam item to visit
     */
    void VisitBeam(Beam* beam) override { mNumBeams++; }

    /**
     * Visit a Product item
     * @param product Product item to visit
     */
    void VisitProduct(Product* product) override { mNumProducts++; }

    /**
     * Visit a Conveyor item
     * @param conveyor Conveyor item to visit
     */
    void VisitConveyor(Conveyor* conveyor) override { mNumConveyors++; }

    /**
     * Visit a Scoreboard item
     * @param scoreboard Scoreboard item to visit
     */
    void VisitScoreboard(Scoreboard* scoreboard) override { mNumScoreboards++; }

    /**
     * Visit a Beginner Banner item
     * @param banner banner item to visit
     */
    void VisitBanner(Banner* banner) override { mNumBeginnerBanners++; }

 /**
 * Visit a Logic Gate item
 * @param logicGate logic gate item to visit
 */
 void VisitLogicGate(LogicGate* logicGate) override {mLogicGates++;};


};


#endif //ITEMCOUNTER_H
