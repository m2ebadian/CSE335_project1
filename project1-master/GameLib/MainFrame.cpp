/**
 * @file MainFrame.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"SpartyBoots", wxDefaultPosition, wxSize(1150, 800));

    auto sizer = new wxBoxSizer(wxVERTICAL);

    mGameView = new GameView();
    mGameView->Initialize(this);

    sizer->Add(mGameView, 1, wxEXPAND | wxALL);
    SetSizer(sizer);
    Layout();


    /// create the menu bar
    auto menuBar = new wxMenuBar();


    /// create the menu options
    auto fileMenu = new wxMenu();
    auto viewMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto gatesMenu = new wxMenu();
    auto helpMenu = new wxMenu();


    /// add the menu options to the menu bar
    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(viewMenu, L"&View");
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(gatesMenu, L"&Gates");
    menuBar->Append(helpMenu, L"&Help");


    /// menu settings for file and help
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");


    ///adding the option to see the control points to the View menu
    viewMenu->AppendCheckItem(IDM_ADDCONTROLPOINTS, L"&Control Points", L"Turn on Control Points");


    ///adding the levels that will be loaded to the Level Menu
    levelMenu->Append(IDM_LEVEL0, L"&Level 0", L"Play Level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Play Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Play Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Play Level 3");
    levelMenu->Append(IDM_LEVEL4, L"&Level 4", L"Play Level 4");
    levelMenu->Append(IDM_LEVEL5, L"&Level 5", L"Play Level 5");
    levelMenu->Append(IDM_LEVEL6, L"&Level 6", L"Play Level 6");
    levelMenu->Append(IDM_LEVEL7, L"&Level 7", L"Play Level 7");
    levelMenu->Append(IDM_LEVEL8, L"&Level 8", L"Play Level 8");

    /// adding the gates that can be added to the game to the Gates menu
    gatesMenu->Append(IDM_ADDANDGATE, L"&AND", L"Add an AND gate");
    gatesMenu->Append(IDM_ADDORGATE, L"&OR", L"Add an OR gate");
    gatesMenu->Append(IDM_ADDNOT, L"&NOT", L"Add a NOT gate");
    gatesMenu->Append(IDM_ADDSRFLIPFLOP, L"&SR Flip Flop", L"Add a SR Flip Flop");
    gatesMenu->Append(IDM_ADDDFLIPFLOP, L"&D Flip Flop", L"Add a D Flip Flop");
    gatesMenu->Append(IDM_ADDXORGATE, L"&XOR", L"Add an XOR Gate");

    SetMenuBar(menuBar);

    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    /// Binding the About menu event
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    /// Existing bindings, including Exit:
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}


/**
 * Exit menu option handlers
 * @param event exit event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


/**
 * Menu event handler for WxID_ABOUT
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to SpartyBoots!",
                 L"About SpartyBoots",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window
 * @param event close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}
