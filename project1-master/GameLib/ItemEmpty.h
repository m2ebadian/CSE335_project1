/**
 * @file ItemEmpty.h
 * @author Daniel Wills
 *
 * Empty item class
 */
 
#ifndef ITEMEMPTY_H
#define ITEMEMPTY_H
#include "Item.h"

/**
 * Empty item class
 */
class ItemEmpty : public Item
{
private:

public:
 /// Default constructor (disabled)
 ItemEmpty() = delete;

 /// Copy constructor (disabled)
 ItemEmpty(const ItemEmpty&) = delete;

 /// Assignment operator
 void operator=(const ItemEmpty&) = delete;

 /**
  * Constructor
  * @param game Game this Item is a member of
  */
 ItemEmpty(Game* game);


 /**
* Accept a visitor
* @param visitor The visitor we accept
*/
 void Accept(ItemVisitor* visitor) override
 {
  visitor->VisitItemEmpty(this);
 }
};



#endif //ITEMEMPTY_H
