/**
 * @file ConveyorProductMoveVisitor.h
 * @author Mehrshad Bagherebadian
 *
 *
 */

#ifndef CONVEYORPRODUCTMOVEVISITOR_H
#define CONVEYORPRODUCTMOVEVISITOR_H


#include "ItemVisitor.h"
#include "Product.h"
#include <vector>

class Conveyor;
class Product;
class Game;


/**
 * Visitor that moves products along the conveyor belt.
 */
class ConveyorProductMoveVisitor : public ItemVisitor
{
public:
    /**
     * Constructor for the visitor
     * @param conveyorSpeed speed the conveyor is moving
     * @param elapsed time elapsed
     */
    ConveyorProductMoveVisitor(double conveyorSpeed, double elapsed)
        : mConveyorSpeed(conveyorSpeed), mElapsed(elapsed)
    {
    }

    /**
     * Visit a product and add it to the temporary list for moving later.
     * @param product The product being visited.
     */
    void VisitProduct(Product* product) override
    {
        mTempProducts.push_back(product);
    }


    /**
    * Move all collected products at once.
    */
    void MoveProducts()
    {
        for (Product* product : mTempProducts)
        {
            product->Update(mConveyorSpeed, mElapsed);  // Move each product
        }
        mTempProducts.clear();  // Clear the list after moving
    }


    /**
 * Get the products that were moved during this visit.
 * @return Vector of products moved
 */
    const std::vector<Product*>& GetMovedProducts() const
    {
        return mTempProducts;
    }

private:
    double mConveyorSpeed; ///< Speed of the conveyor belt
    double mElapsed; ///< Time elapsed since the last update
    std::vector<Product*> mTempProducts; ///< Temporary list of products to move
};


#endif //CONVEYORPRODUCTMOVEVISITOR_H

