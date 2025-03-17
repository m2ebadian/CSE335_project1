/**
 * @file ItemVisitor.h
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 *
 * Item visitor base class.
 */

#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

// Forward declarations of game elements
class Sparty;
class Sensor;
class Beam;
class Product;
class Conveyor;
class Scoreboard;
class OrLogicGate;
class AndLogicGate;
class NotLogicGate;
class SRLogicGate;
class DLogicGate;
class XORLogicGate;
class OutputLogicGate;
class InputLogicGate;
class ItemExample;
class ItemGrabbableExample;
class ItemEmpty;
class Banner;
class BannerEnd;
class LogicGate;
class Item;  // Forward declaration for Item


/**
 * Item visitor base class
 */
class ItemVisitor
{
protected:
    /**
     * Constructor.
     */
    ItemVisitor()
    {
    }

public:
    /**
     * Virtual destructor.
     */
    virtual ~ItemVisitor()
    {
    }

    /**
    * Visit a beam object.
    * @param beam the beam we are visiting.
    */
    virtual void VisitBeam(Beam* beam)
    {
    }

    /**
   * Visit a product object.
   * @param product the product we are visiting.
   */
    virtual void VisitProduct(Product* product)
    {
    }

    /**
   * Visit a scoreboard object.
   * @param scoreboard the scoreboard we are visiting.
   */
    virtual void VisitScoreboard(Scoreboard* scoreboard)
    {
    }

    /**
   * Visit a Sensor object.
   * @param sensor the sensor we are visiting.
   */
    virtual void VisitSensor(Sensor* sensor)
    {
    }

    /**
   * Visit a Sparty object.
   * @param sparty the sparty we are visiting.
   */
    virtual void VisitSparty(Sparty* sparty)
    {
    }

    /**
    * Visit a conveyor object.
    * @param conveyor the conveyor we are visiting.
    */
    virtual void VisitConveyor(Conveyor* conveyor)
    {
    }

    /**
     * Visit a logic gate object
     * @param logicGate the logic gate we are visiting
     */
    virtual void VisitLogicGate(LogicGate* logicGate)
    {
    }

    /**
   * Visit an OR logic gate object.
   * @param orLogicGate the OR logic gate we are visiting.
   */
    virtual void VisitOrLogicGate(OrLogicGate* orLogicGate)
    {
    }

    /**
   * Visit an AND logic gate object.
   * @param andLogicGate the OR logic gate we are visiting.
   */
    virtual void VisitAndLogicGate(AndLogicGate* andLogicGate)
    {
    }


    /**
   * Visit an NOT logic gate object.
   * @param notLogicGate the NOT logic gate we are visiting.
   */
    virtual void VisitNotLogicGate(NotLogicGate* notLogicGate)
    {
    }

    /**
  * Visit an XOR logic gate object.
  * @param xorLogicGate the XOR logic gate we are visiting.
  */
    virtual void VisitXORLogicGate(XORLogicGate* xorLogicGate)
    {
    }

    /**
   * Visit an example item.
   * @param itemExample example item we are visiting.
   */
    virtual void VisitItemExample(ItemExample* itemExample)
    {
    }

   /**
   * Visit an empty item.
   * @param itemEmpty empty item we are visiting.
   */
   virtual void VisitItemEmpty(ItemEmpty* itemEmpty)
   {
   }

    /**
   * Visit a draggable example item object.
   * @param itemExample the example item we are visiting.
   */
    virtual void VisitItemGrabbableExample(ItemGrabbableExample* itemExample)
    {
    }

    /**
     * Visit a banner object.
     * @param banner the banner we are visiting.
     */
    virtual void VisitBanner(Banner* banner)
    {
    }

    /**
     * Visit a banner end object.
     * @param bannerEnd the banner end we are visiting.
     */
    virtual void VisitBannerEnd(BannerEnd* bannerEnd)
    {
    }

    /**
     * Visit an SRFlipFlop object.
     * @param srLogicGate the logic gate we are visiting.
     */
    virtual void VisitSRLogicGate(SRLogicGate* srLogicGate)
    {
    }


    /**
    * Visit an DFlipFlop object.
    * @param dLogicGate the DFlipFlopLogicGate we are visiting.
    */
    virtual void VisitDLogicGate(DLogicGate* dLogicGate)
    {
    }

    /**
    * Visit an InputLogicGate object.
    * @param inputLogicGate the InputLogicGate we are visiting.
    */
    virtual void VisitInputLogicGate(InputLogicGate* inputLogicGate)
    {
    }

    /**
    * Visit an OutputLogicGate object.
    * @param outputLogicGate the OutputLogicGate we are visiting.
    */
    virtual void VisitOutputLogicGate(OutputLogicGate* outputLogicGate)
    {
    }

   /**
    * @brief Visits a general item in the system.
    *
    * This function provides a generic visit operation for items that are not specifically handled.
    * It can be overridden for specific item processing as needed.
    * @param item The item to visit.
    */
    virtual void VisitItem(Item* item) {}  // Define VisitItem for general items
};

#endif //ITEMVISITOR_H

