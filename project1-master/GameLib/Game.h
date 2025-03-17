/**
 * @file Game.h
 * @author Tyler Nguyen, Daniel Wills, Mehrshad Bagherebadian
 *
 * Main Game Class
 */

#ifndef GAME_H
#define GAME_H

#include <memory>

#include "IDraggable.h"
#include "ItemVisitor.h"
#include "PinOutput.h"
#include "ScoreUpdateVisitor.h"

class Item;

/**
 * Main Game Class
 */
class Game
{
private:
    double mScale = 1; ///< The scale of the game view

    double mXOffset = 0; ///< The horizontal offset of the game view

    double mYOffset = 0; ///< The vertical offset of the game view

    std::vector<std::shared_ptr<Item>> mItems; ///< All the items that populate the game

    int mLevelWidth = 1150; ///< Width of the level in Virtual Pixels (This is just a default value)

    int mLevelHeight = 800; ///< Height of the level in Virtual Pixels (This is just a default value)

    bool mShowControlPoints = false; ///< Track the control visibility state

    int mCurrLevelNum = 1; ///< Current level number

    double mLevelLoadDelay = 3.0; ///< Delay between the level ending and a new level being loaded in

    bool mHasLevelEnded = false; ///< Indicates if the level has ended

    int mGameScore = 0; ///< The games score

    bool mWasItemHitThisCycle = 0; ///< The items hit by beam this visitor cycle
    bool mWasItemPreviouslyHit = false; ///< Determines if an item was previously hit by veam
    Product* mCurrentProduct = nullptr; ///< The current product under the beam

    std::wstring mText; ///< The text to display on banner
    bool mVisible = true; ///< Whether the banner is visible

public:
    Game(); // Default constructor

    void Add(std::shared_ptr<Item> item);

    void BringItemToFront(Item* item);

    std::shared_ptr<IDraggable> HitTest(double x, double y);
    std::shared_ptr<Item> HitTestDefault(int x, int y);

    void LoadLevel(const wxString& filename);

    void ClearLevel();

    //std::shared_ptr<Item> OnLeftDown(int x, int y);

    void OnDraw(std::shared_ptr<wxGraphicsContext>& graphics, int width, int height); // Draw the game

    /**
     * Get the virtual pixel x values
     * @param x the x location
     * @return x val of virtual pixels
     */
    double GetVirtualPixelsX(int x) { return (x - mXOffset) / mScale; }

    /**
     * Get the virtual pixel y values
     * @param y the y location
     * @return the y value in virtual pixels
     */
    double GetVirtualPixelsY(int y) { return (y - mYOffset) / mScale; }

    void TryToCatch(PinOutput* pinOutput, wxPoint lineEnd);
    void Accept(ItemVisitor* visitor);

    void RemoveItem(Item* item);
    void Update(double elapsed);

    /**
     * Sets the control point view state
     * @param show determines whether its on or off
     */
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }


    /**
    * @brief Marks the current level as complete and triggers any associated actions.
    *
    * This function is called when the player completes the current level, updating game state and progressing as needed.
    */

    void LevelComplete();

    /**
     * @brief Sets the current level number.
     *
     * @param newLevelNum The new level number to set.
     */
    void SetLevelNum(int newLevelNum) { mCurrLevelNum = newLevelNum; }


    /**
    * @brief Loads the next level in the game sequence.
    *
    * Advances to and initializes the next level, updating any necessary game state.
    */
    void LoadNextLevel();

    /**
     * @brief set the value of mItemsHitThisCycle
     *
     * @param state
     */
    void SetItemHitThisCycle(bool state) { mWasItemHitThisCycle = state; }


    /**
     * @brief sets the bool of mWasItemPreviouslyHit to new state
     *
     * @param state
     */
    void SetItemPreviouslyHit(bool state) { mWasItemPreviouslyHit = state; }

    /**
     * @brief sets a new value for mCurrentProduct
     *
     * @param newProduct
     */
    void SetCurrentProduct(Product* newProduct) { mCurrentProduct = newProduct; }

    void DrawEndBanner(wxGraphicsContext* graphics);
};


#endif //GAME_H
