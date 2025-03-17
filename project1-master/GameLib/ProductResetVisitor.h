/**
 * @file ProductResetVisitor.h
 * @author Conner O'Sullivan
 *
 *
 */

#ifndef PRODUCTRESETVISITOR_H
#define PRODUCTRESETVISITOR_H
#include "Conveyor.h"
#include "ItemVisitor.h"
#include "Product.h"


/**
 * @class ProductResetVisitor
 * @brief A visitor that resets the position of products on a conveyor.
 *
 * The `ProductResetVisitor` class checks the reset and start states of a conveyor
 * and, if applicable, resets the positions of products on the conveyor.
 * It is part of the `ItemVisitor` hierarchy.
 */
class ProductResetVisitor : public ItemVisitor
{
public:

    /**
     * @brief Visits a conveyor to check and set its reset and start states.
     *
     * Sets the `mReset` and `mStart` flags based on the conveyor's state and stores a pointer to the conveyor.
     * @param conveyor The conveyor to visit.
     */
    void VisitConveyor(Conveyor* conveyor) override
    {
        mReset = conveyor->GetReset();
        mStart = conveyor->GetStarted();
        mConveyor = conveyor;
    }

    /**
     * @brief Visits a product to reset its position if the conveyor's reset and start states are active.
     *
     * If both `mStart` and `mReset` are true, this function resets the product’s position
     * and then deactivates the reset state on the conveyor.
     * @param product The product to visit and potentially reset.
     */
    void VisitProduct(Product* product) override
    {
        if (!mConveyor)
        {
            return;
        }
        if (mStart && mReset)
        {
            product->ResetPosition();
            mConveyor->SetReset(false);
        }
    }
private:
    bool mReset = false; ///< boolean that sets the state of reset
    bool mStart = false; ///< boolean of whether the reset is starting or not
    Conveyor* mConveyor; ///< Pointer to the conveyor being visited.
};


#endif //PRODUCTRESETVISITOR_H
