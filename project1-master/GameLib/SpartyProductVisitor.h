/**
 * @file SpartyProductVisitor.h
 * @author Conner O'Sullivan
 * @brief Declaration of the SpartyProductVisitor class, which manages interactions between Sparty and products.
 *
 * This file defines the SpartyProductVisitor class, responsible for detecting products within Sparty's range
 * and handling actions like kicking the product based on Sparty's current state.
 */

#ifndef SPARTYPRODUCTVISITOR_H
#define SPARTYPRODUCTVISITOR_H

#include "ItemVisitor.h"

class Product;
class Sparty;


/**
 * @class SpartyProductVisitor
 * @brief A visitor that manages interactions between Sparty and products within range.
 *
 * The `SpartyProductVisitor` class checks if products are within Sparty's range and
 * triggers actions such as kicking if Sparty is in kicking mode.
 */
class SpartyProductVisitor : public ItemVisitor
{
public:

    /**
     * @brief Constructor for the SpartyProductVisitor.
     *
     * Initializes the visitor with no active Sparty and no product in range.
     */
    SpartyProductVisitor() : mProductInRange(false), mCurrentSparty(nullptr)
    {
    }


    /**
     * @brief Sets the current Sparty to be checked for product interactions.
     *
     * This function is called to set the active Sparty and reset product detection.
     * @param sparty The Sparty instance to check.
     */
    void VisitSparty(Sparty* sparty) override
    {
        mCurrentSparty = sparty;
        mProductInRange = false;
    }


    /**
     * @brief Checks if a product is within Sparty's kicking range and initiates a kick if possible.
     *
     * This function is called to check for product interactions within Sparty's range,
     * and triggers a kick if Sparty is currently in kicking mode.
     * @param product The product to check for interaction.
     */
    void VisitProduct(Product* product) override
    {
        if (!mCurrentSparty)
        {
            return;
        }

        if (mCurrentSparty->IsProductInKickRange(*product))
        {
            if (mCurrentSparty->GetKicking())
            {
                product->Kicked(mCurrentSparty->GetKickSpeed());
            }
        }
    }

private:
    /**
     * @brief Pointer to the current Sparty instance being checked.
     */
    Sparty* mCurrentSparty;

    /**
     * @brief Flag indicating if a product is within Sparty's range.
     */
    bool mProductInRange;
};


#endif //SPARTYPRODUCTVISITOR_H
