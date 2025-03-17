/**
 * @file ItemExample.h
 * @author Daniel Wills
 *
 * Class for an Item of type ItemExample
 */

#ifndef ITEMEXAMPLE_H
#define ITEMEXAMPLE_H
#include "Item.h"

/**
 * Class for an Item of type ItemExample
 */
class ItemExample : public Item
{
private:

public:
    /// Default constructor (disabled)
    ItemExample() = delete;

    /// Copy constructor (disabled)
    ItemExample(const ItemExample&) = delete;

    /// Assignment operator
    void operator=(const ItemExample&) = delete;

    /**
     * Constructor
     * @param game Game this Item is a member of
     */
    ItemExample(Game* game);

    /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitItemExample(this);
    }
};


#endif //ITEMEXAMPLE_H
