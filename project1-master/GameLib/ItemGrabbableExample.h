/**
 * @file ItemGrabbableExample.h
 * @author Daniel Wills
 *
 * Class for an Item of type ItemGrabbableExample
 */

#ifndef ITEMGRABBABLEEXAMPLE_H
#define ITEMGRABBABLEEXAMPLE_H
#include "ItemGrabbable.h"

/**
 * Class for an Item of type ItemGrabbableExample
 */
class ItemGrabbableExample : public ItemGrabbable
{
private:

public:
    /// Default constructor (disabled)
    ItemGrabbableExample() = delete;

    /// Copy constructor (disabled)
    ItemGrabbableExample(const ItemGrabbableExample&) = delete;

    /// Assignment operator
    void operator=(const ItemGrabbableExample&) = delete;

    /**
    * Constructor
    * @param game Game this Item is a member of
    */
    ItemGrabbableExample(Game* game);

    /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitItemGrabbableExample(this);
    }
};


#endif //ITEMGRABBABLEEXAMPLE_H
