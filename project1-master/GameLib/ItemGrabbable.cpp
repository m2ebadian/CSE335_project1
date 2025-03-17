/**
 * @file ItemGrabbable.cpp
 * @author Daniel Wills
 */

#include "pch.h"
#include "ItemGrabbable.h"

using namespace std;

/**
 * Constructor
 * @param game The game this grabbable item is a member of
 * @param imageFilename the filename of the grabbable item image
 */
ItemGrabbable::ItemGrabbable(Game* game, const std::wstring& imageFilename) :
    Item(game, imageFilename)
{
}


bool ItemGrabbable::HitTest(int x, int y)
{
    double wid = GetItemBitmap()->GetWidth();
    double hit = GetItemBitmap()->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }
    return !GetItemImage()->IsTransparent((int)testX, (int)testY);
}
