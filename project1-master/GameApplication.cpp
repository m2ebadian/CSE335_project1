/**
 * @file GameApplication.cpp
 * @author Conner O'Sullivan
 */

#include "pch.h"
#include "GameApplication.h"
#include <MainFrame.h>

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#elif __APPLE__
#include <malloc/malloc.h>
#endif

/**
 * Initialize the application.
 * @return
 */
bool GameApplication::OnInit()
{
#ifdef WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
