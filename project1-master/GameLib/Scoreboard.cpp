/**
 * @file Scoreboard.cpp
 * @author Tyler Nguyen
 */

#include "pch.h"
#include "Scoreboard.h"

#include <sstream>

/// Size of the scoreboard in virtual pixels @return wxSize of Scoreboard
const wxSize ScoreboardSize(380, 100);

/// The spacing from the scores to the instructions presentation
/// in virtual pixels
const int SpacingScoresToInstructions = 40;

/// The spacing between the instruction lines in virtual pixels.
const int SpacingInstructionLines = 17;

using namespace std;

/**
 * @brief Constructor for the Scoreboard.
 *
 * Initializes the scoreboard with the given parameters.
 *
 * @param game The game this item is a member of.
 * @param x The x position of the scoreboard.
 * @param y The y position of the scoreboard.
 * @param goodScore The score for good kicks.
 * @param badScore The score for bad kicks.
 * @param gameScore The initial game score.
 * @param goal The goal for the level.
 */
Scoreboard::Scoreboard(Game* game, int x, int y, int goodScore, int badScore, int gameScore, std::wstring& goal)
    : Item(game), mPosition(x, y), mLevel(0),
      mGameScore(gameScore), mGoodScore(goodScore), mBadScore(badScore), mGoal(goal)
{
}

/**
 * Draw the scoreboard
 * @param graphics The graphics context to draw on
 */
void Scoreboard::Draw(wxGraphicsContext* graphics)
{
    // Draw the scoreboard background
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->SetPen(*wxBLACK_PEN);
    graphics->DrawRectangle(mPosition.x, mPosition.y, ScoreboardSize.GetWidth(), ScoreboardSize.GetHeight());

    // Draw the scores
    auto font = graphics->CreateFont(25, L"Arial", wxFONTFLAG_BOLD, wxColour(24, 69, 59));
    graphics->SetFont(font);
    graphics->SetPen(wxPen(wxColour(24, 6, 59)));

    wxString scoreText = wxString::Format("Level: %d \t\t\t Game: %d", mLevel, mGameScore);
    graphics->DrawText(scoreText, mPosition.x + 10, mPosition.y + 10);

    // Draw the goal of the level
    font = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
    graphics->SetFont(font);

    // This is the y position of the first instruction line
    int instructionY = mPosition.y + 10 + SpacingScoresToInstructions;
    // Create a stream to read the goal
    std::wstringstream goalStream(mGoal);
    // Read the goal line by line and draw it
    std::wstring line;
    while (std::getline(goalStream, line, L'\n'))
    {
        graphics->DrawText(line, mPosition.x + 10, instructionY);
        instructionY += SpacingInstructionLines;
    }
}

/**
 * @brief Updates the level score based on Sparty's action and the item's desired state.
 *
 * @param spartyKicked Indicates whether Sparty kicked the item (`true` if kicked).
 * @param itemWantsBeingKicked Indicates whether the item wanted to be kicked (`true` if yes).
 */
void Scoreboard::UpdateLevelScore(bool spartyKicked, bool itemWantsBeingKicked)
{
    if (spartyKicked)
    {
        if (itemWantsBeingKicked)
        {
            mLevel += mGoodScore;
        }
        else
        {
            mLevel += mBadScore;
        }
    }
    else
    {
        if (itemWantsBeingKicked)
        {
            mLevel += mBadScore;
        }
        else
        {
            mLevel += mGoodScore;
        }
    }
}

/**
 * Load this Scoreboard from an XML node
 * @param node The node we are loading the Scoreboard from
 */
void Scoreboard::XmlLoad(wxXmlNode* node)
{
    node->GetAttribute(L"x", L"0").ToInt(&mPosition.x);
    node->GetAttribute(L"y", L"0").ToInt(&mPosition.y);
    node->GetAttribute(L"good", L"10").ToInt(&mGoodScore);
    node->GetAttribute(L"bad", L"0").ToInt(&mBadScore);

    auto child = node->GetChildren();
    for (; child; child = child->GetNext())
    {
        if (child->GetType() == wxXML_TEXT_NODE)
        {
            mGoal += child->GetContent().ToStdWstring();
        }
        else if (child->GetName() == L"br")
        {
            mGoal += L"\n";
        }
    }
}
