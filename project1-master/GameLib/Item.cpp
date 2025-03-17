/**
 * @file Item.cpp
 * @author Daniel Wills
 */

#include "pch.h"
#include "Item.h"

#include "Game.h"

using namespace std;

/**
 * Constructor for items with images
 * @param game The game this item is a member of
 * @param imageFilename the filename of the item image
 */
Item::Item(Game* game, const std::wstring& imageFilename) : mGame(game)
{
    mItemImage = make_unique<wxImage>(imageFilename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}

/**
 * Constructor for items without images
 * @param game The game this item is a member of
 */
Item::Item(Game* game) : mGame(game)
{
}


/**
 * Destructor
 */
Item::~Item()
{
}


void Item::Draw(wxGraphicsContext* gc)
{
    double width = mItemBitmap->GetWidth();
    double height = mItemBitmap->GetHeight();

    wxGraphicsBitmap graphicsBitmap = gc->CreateBitmap(*mItemBitmap);
    gc->DrawBitmap(graphicsBitmap,
                   int(GetX() - width / 2),
                   int(GetY() - height / 2),
                   width,
                   height);
}

/**
 * This draggable thing should be moved to the front
 * of the list of items.
 */
void Item::MoveToFront()
{
    mGame->BringItemToFront(this);
}

void Item::SetLocation(double x, double y)
{
    mX = x;
    mY = y;
}


/**
 * Load the placement of an item from an XML node
 * @param node The node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
    long x, y;
    node->GetAttribute(L"x", L"0").ToLong(&x);
    node->GetAttribute(L"y", L"0").ToLong(&y);
    mX = (int)x;
    mY = (int)y;
}
