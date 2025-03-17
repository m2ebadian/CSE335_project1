/**
 * @file Banner.cpp
 * @author Tyler Nguyen
 */

#include "pch.h"
#include "Banner.h"

using namespace std;

/// Level notices duration in seconds
const double LevelNoticeDuration = 2;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(24, 69, 59);

/// Color to draw a rectangle enclosing the level notice text @return wxColour of the Banner color
wxColour LevelNoticeBackground(255, 255, 255, 200);

/// Padding to add to the left and right side of the level
/// notice background rectangle in virtual pixels
const double LevelNoticePadding = 20;

/// Width of the level notice Box
const double LevelNoticeWidth = 690;

/**
 * Constructor for the Banner
 * @param game The game this item is a member of
 * @param text The text we will be displaying
 */
Banner::Banner(Game* game, std::wstring& text) :
    Item(game), mText(text)
{
}

/**
 * Draw the Banner
 * @param graphics The graphics context to draw on
 */
void Banner::Draw(wxGraphicsContext* graphics)
{
    if (mVisible)
    {
        // Set the brush and pen for the background rectangle
        graphics->SetBrush(wxBrush(LevelNoticeBackground, wxBRUSHSTYLE_SOLID));
        graphics->SetPen(wxPen(LevelNoticeBackground, 0, wxPENSTYLE_TRANSPARENT));

        // Figure out the location to draw the text
        // Cut the width into quarters
        double quarter = 0.25;
        double centerX = mLevelWidth * quarter;
        int centerY = (mLevelHeight / 2) - (NoticeSize / 2);

        // Figure out the size of the rectangle
        graphics->DrawRectangle(centerX - LevelNoticePadding, centerY - (LevelNoticePadding / 2),
                                LevelNoticeWidth,
                                NoticeSize + LevelNoticePadding + 10);

        // Set the font and font size
        auto font = graphics->CreateFont(NoticeSize, L"Arial", wxFONTFLAG_BOLD, LevelNoticeColor);
        graphics->SetFont(font);
        graphics->DrawText(mText, centerX, centerY);
    }
}

/**
 * Update the Banner
 * @param elapsed the amount of time passed
 */
void Banner::Update(double elapsed)
{
    // Do the upcall
    Item::Update(elapsed);

    // Now check if we should hide the banner
    if (mTime >= 0)
    {
        mTime += elapsed;
        if (mTime >= LevelNoticeDuration)
        {
            mVisible = false;
        }
    }
}
