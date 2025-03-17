/**
 * @file ScoreboardVisitor.h
 * @author Tyler Nguyen
 *
 * Visitor that retrieves the scoreboard item
 */
 
#ifndef SCOREBOARDVISITOR_H
#define SCOREBOARDVISITOR_H

#include "ItemVisitor.h"
#include "Scoreboard.h"

/**
 * Visitor that retrieves the scoreboard item
 */
class ScoreboardVisitor : public ItemVisitor
{
private:
 Scoreboard* mScoreboard = nullptr; ///< The scoreboard item
public:
 /**
  * Grab the scoreboard item
  * @param scoreboard
  */
 void VisitScoreboard(Scoreboard* scoreboard) override
 {
  mScoreboard = scoreboard;
 }

 /**
  * return the scoreboard item
  * @return the scoreboard item
  */
 Scoreboard* GetScoreboard() { return mScoreboard; }
};

#endif //SCOREBOARDVISITOR_H
