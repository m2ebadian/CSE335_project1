/**
 * @file GameView.h
 * @author Conner O'Sullivan, Daniel Wills, Mehrshad Bagherebadian
 *
 * View class for the game
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"

class Item;

/**
 * View class for the game
 */
class GameView : public wxWindow
{
private:
    /// Create a Game object that describes the game
    Game mGame;

    /// Any item that is currently grabbed
    std::shared_ptr<IDraggable> mGrabbedItem;

    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnAddGate(wxCommandEvent& event);
    void OnShowControlPoints(wxCommandEvent& event);
    void OnLoadLevel(wxCommandEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);

    /// Timer for animation
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    long mTime = 0;

public:

    void Initialize(wxFrame* parent);

    /**
     * Stop the timer so window can close
     */
    void Stop() { mTimer.Stop(); }

    /**
     * @brief Retrieves a pointer to the game instance.
     *
     * @return A pointer to the `Game` instance associated with this object.
     */
    Game* GetGame() {return &mGame;}

    /**
     * End the level
     */
     void LevelComplete() { mGame.LevelComplete();}
};


#endif //GAMEVIEW_H
