/**
 * @file ScoreUpdateVisitor.h
 * @author Tyler Nguyen
 *
 * Visitor that updates the score
 */

#ifndef SCOREUPDATEVISITOR_H
#define SCOREUPDATEVISITOR_H

#include "ItemVisitor.h"
#include "Scoreboard.h"

/**
 * Visitor that updates the score
 */
class ScoreUpdateVisitor : public ItemVisitor
{
private:
    /// if Sparty kicked or not
    bool mSpartyKicked;
    /// if item wants to be kicked
    bool mProductWantsKick;

public:
    /**
     * Constructor for the visitor
     * @param spartyKicked if Sparty kicked or not
     * @param productWantsKick if item wants to be kicked
     */
    ScoreUpdateVisitor(bool spartyKicked, bool productWantsKick) :
        mSpartyKicked(spartyKicked), mProductWantsKick(productWantsKick) {}

    /**
     * Visitor that updates the score
     * @param scoreboard
     */
    void VisitScoreboard(Scoreboard* scoreboard) override
    {
        scoreboard->UpdateLevelScore(mSpartyKicked, mProductWantsKick);
    }
};


#endif //SCOREUPDATEVISITOR_H
