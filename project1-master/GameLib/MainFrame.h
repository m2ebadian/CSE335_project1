/**
 * @file MainFrame.h
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 *
 * Mainframe for the game
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

class GameView;

/**
 * Initialize the MainFrame window
 */
class MainFrame : public wxFrame
{
private:
    /// View class for SpartysBoots
    GameView* mGameView;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

public:
    void Initialize();
};


#endif //MAINFRAME_H
