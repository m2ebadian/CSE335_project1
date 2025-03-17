/**
* @file GameVisitor.h
 * @author Mehrshad Bagherebadian
 *
 *
 */

#ifndef GAMEVISITOR_H
#define GAMEVISITOR_H


// Forward declarations of game elements
class Sparty;
class Sensor;
class Item;
class ItemGrabbable;

/**
 * Game visitor base class.
 *
 * This class defines visit methods for different types of game objects.
 * Derived visitor classes can implement specific behaviors for each object type.
 */
class GameVisitor
{
protected:
    /**
     * Constructor.
     * Protected to ensure this is an abstract class.
     */
    GameVisitor()
    {
    }

public:
    /**
     * Virtual destructor.
     */
    virtual ~GameVisitor()
    {
    }

    /**
    * Visit an ItemGrabbable object.
    * @param itemGrabbable ItemGrabbable object we are visiting.
    */
    virtual void VisitItemGrabbable(ItemGrabbable* itemGrabbable)
    {
    }


    /**
     * Visit a generic Item object.
     * @param item Generic item object we are visiting.
     */
    virtual void VisitItem(Item* item)
    {
    }
};


#endif //GAMEVISITOR_H
