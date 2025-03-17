/**
 * @file ItemGrabbable.h
 * @author Daniel Wills, Mehrshad Bagherebadian
 *
 * Base class for a grabbable item
 */

#ifndef ITEMGRABBABLE_H
#define ITEMGRABBABLE_H

#include "Item.h"
#include "GameVisitor.h"

/**
 * Base class for a grabbable item
 */
class ItemGrabbable : public Item
{
private:

protected:
    ItemGrabbable(Game* game, const std::wstring& imageFilename);

public:
    /// Default constructor (disabled)
    ItemGrabbable() = delete;

    /// Copy constructor (disabled)
    ItemGrabbable(const ItemGrabbable&) = delete;

    /// Assignment operator
    void operator=(const ItemGrabbable&) = delete;

    /**
     * Test this item to see if it has been clicked on
     * @param x X location on the game to test in pixels
     * @param y Y location on the game to test in pixels
     * @return true if clicked on
     */
    bool HitTest(int x, int y) override;


    /**
    * Accept a visitor.
    * @param visitor The visitor that is interacting with this item.
    */
    void Accept(GameVisitor* visitor) override
    {
        visitor->VisitItem(this); // Let the visitor handle the specific visit logic for Item
    }
};


#endif //ITEMGRABBABLE_H
