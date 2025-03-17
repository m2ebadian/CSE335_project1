/**
* @file Item.h
 * @author Daniel Wills
 */

#ifndef ITEM_H
#define ITEM_H

#include "IDraggable.h"
#include "GameVisitor.h"
#include "ItemVisitor.h"

class Game;
class PinOutput;


/**
 * Base class for any item in our game.
 */

class Item : public IDraggable
{
private:
    /// The game this item is contained in
    Game* mGame;

    // Item location in the game
    double mX = 0; ///< X location for the center of the item
    double mY = 0; ///< Y location for the center of the item

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

protected:
    Item(Game* game, const std::wstring& imageFilename);

    // For scoreboard since it doesn't take an image filename
    Item(Game* game);

public:
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item&) = delete;

    /// Assignment operator
    void operator=(const Item&) = delete;

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Draw this item
     * @param gc Device context to draw on
     */
    virtual void Draw(wxGraphicsContext* gc);

    /**
     * Test this DRAGGABLE item to see if it has been clicked on
     * @param x X location on the game to test in pixels
     * @param y Y location on the game to test in pixels
     * @return true if clicked on
     */
    virtual bool HitTest(int x, int y) { return false; };

    /**
    * Test this item to see if it has been clicked on
    * @param x X location on the game to test in pixels
    * @param y Y location on the game to test in pixels
    * @return true if clicked on
    */
    virtual bool HitTestDefault(int x, int y) { return false; };

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) override;

    virtual void XmlLoad(wxXmlNode* node);


    /**
     * Get the item bitmap
     * @return the bitmap of the item object
     */
    std::unique_ptr<wxBitmap>& GetItemBitmap() { return mItemBitmap; }

    /**
     * Get the item bitmap
     * @return the bitmap of the item object
     */
    std::unique_ptr<wxImage>& GetItemImage() { return mItemImage; }


    void MoveToFront() override;

    /**
    * Release after moving
    */
    void Release() override {}

    /**
     * Try to catch a wire at the new x,y location of the pin end
     * @param pinOutput input pin we are trying to catch from
     * @param lineEnd The line end point
     * @return true if caught
     */
    virtual bool Catch(PinOutput* pinOutput, wxPoint lineEnd) { return false; }

    /**
    * Test to see if we clicked on some draggable inside the item.
    * @param x X location clicked on
    * @param y Y location clicked on
    * @return Whatever we clicked on or NULL if none
    */
    virtual std::shared_ptr<IDraggable> HitDraggable(int x, int y) { return nullptr; }

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game* GetGame() { return mGame; }


    /**
    * Accept a visitor.
    * @param visitor The visitor that is interacting with this item.
    */
    virtual void Accept(GameVisitor* visitor)
    {
        visitor->VisitItem(this); // Let the visitor handle the specific visit logic for Item
    }

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed)
    {
    }

    /**
    * Handles showing or hiding control output pins for the logic gate
    * @param showControl Boolean that indicates whether to show or hide the control view for the curve
    */
    virtual void SetShowControlOutputPins(bool showControl) {}


 /**
 * Get the width of the item.
 * @return Width in pixels
 */
 int GetWidth() const
    {
     return mItemBitmap ? mItemBitmap->GetWidth() : 0;
    }

 /**
  * Get the height of the item.
  * @return Height in pixels
  */
 int GetHeight() const
    {
     return mItemBitmap ? mItemBitmap->GetHeight() : 0;
    }

};


#endif //ITEM_H
