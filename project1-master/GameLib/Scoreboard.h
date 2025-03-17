/**
 * @file Scoreboard.h
 * @author Tyler Nguyen
 *
 * Scoreboard for the game
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Item.h"

/**
 * Scoreboard class
 */
class Scoreboard : public Item
{
private:
    wxPoint mPosition; ///< Position of the scoreboard
    int mLevel; ///< The score for the level
    int mGameScore = 0; ///< The score for the game
    int mGoodScore = 10; ///< The score for good kicks
    int mBadScore = 0; ///< The score for bad kicks
    std::wstring mGoal; ///< The goal for the level

public:
    Scoreboard(Game* game, int x, int y, int goodScore, int badScore, int gameScore, std::wstring& goal);

    /// Default constructor (disabled)
    Scoreboard() = delete;
    /// Copy constructor (disabled)
    Scoreboard(const Scoreboard&) = delete;
    /// Assignment operator (disabled)
    void operator=(const Scoreboard&) = delete;


    void Draw(wxGraphicsContext* graphics) override;
    void XmlLoad(wxXmlNode* node) override;

    void UpdateLevelScore(bool spartyKicked, bool itemWantsBeingKicked);

    /// Add level score to game score
    void AddLevelScoreToGameScore() { mGameScore += mLevel; }

    /**
     * Get the level score
     * @return the score of the scoreboard
     */
    int GetLevelScore() const { return mLevel; }

    /**
     * Get the game score
     * @return the score of the game
     */
    int GetGameScore() const { return mGameScore; }

 /**
  * @brief Sets the game score.
  *
  * This function updates the game score with the provided value.
  *
  * @param score The new score to set for the game.
  */
    void SetGameScore(int score) { mGameScore = score; }

    /**
     * Reset the Level score
     */
    void ResetLevelScore() { mLevel = 0; }

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitScoreboard(this);
    }
};


#endif //SCOREBOARD_H
