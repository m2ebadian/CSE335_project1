/**
 * @file Product.h
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 *
 * Declaration of the Product class representing individual items on the conveyor.
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include "Item.h"
#include <map>
#include <string>

/**
 * @class Product
 * @brief Represents a product item on the conveyor with specific properties.
 *
 * The `Product` class handles the attributes and behavior of individual products
 * on the conveyor, such as color, shape, and content. Products can be kicked,
 * drawn, updated based on conveyor speed, and interact with visitors.
 *
 * ### Properties:
 * - `Properties`: Enum defining possible product attributes (e.g., color, shape, content).
 * - `Types`: Enum categorizing properties into types (e.g., color, shape, content).
 */

class Product : public Item
{
public:
    /// The possible product properties.
    enum class Properties { None, Red, Green, Blue, White, Square, Circle, Diamond, Izzo, Smith, Football, Basketball };

    /// The property types
    enum class Types { Color, Shape, Content };

    /// Mapping from the XML strings for properties to the Properties enum and the type of the property.
    static const std::map<std::wstring, Properties> NamesToProperties;

    /// Mapping from a property to its type
    static const std::map<Properties, Types> PropertiesToTypes;

    /// Mapping from content properties to their associated image
    static const std::map<Properties, std::wstring> PropertiesToContentImages;

    Product(Game* game, Properties shape, Properties color, Properties content, bool kick);
    void Draw(wxGraphicsContext* graphics) override;
    void XmlLoad(wxXmlNode* node) override;

    /// Default constructor (disabled)
    Product() = delete;

    /// Copy constructor (disabled)
    Product(const Product&) = delete;

    /// Assignment operator
    void operator=(const Product&) = delete;

    /// Get the placement offset @return the placement offset in the Y Direction
    double GetPlacement() const { return mPlacement; }

    void Update(double conveyorSpeed, double elapsed);
    void HasLeftBeam();

    /**
     * @brief Applies a kick to the product, causing it to move at a specified speed.
     *
     * This function is called to apply a kicking action to the product, which adjusts its movement speed.
     * @param kickspeed The speed at which the product is kicked.
     */
    void Kicked(double kickspeed);

    /**
     * Sets the current product as the last one on the conveyor
     */
    void SetLast() { mLast = true; }


    /**
     * @brief Retrieves the color property of the product.
     *
     * @return The color property of the product as a `Properties` enum value.
     */
    Properties GetColor() const { return mColor; }

    /**
     * @brief Retrieves the shape property of the product.
     *
     * @return The shape property of the product as a `Properties` enum value.
     */
    Properties GetShape() const { return mShape; }

    /**
     * @brief Retrieves the content property of the product.
     *
     * @return The content property of the product as a `Properties` enum value.
     */
    Properties GetContent() const { return mContent; }

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitProduct(this);
    }

    void ResetPosition();

    void SetInitialPosition(double x, double y);

private:
    Properties mShape; ///< Shape of the product
    Properties mColor; ///< Color of the product
    Properties mContent; ///< Content of the product
    bool mKick; ///< Bool determining whether the product should be kicked
    double mPlacement{}; ///< Used for getting the true Y value of the product (like an offset)
    wxBitmap mContentBitmap; ///< Bitmap for the content
    bool mLast = false; ///< Is this product the last one on the conveyor?
    double mLastProductDelay = false; ///< Delay for the last product
    bool mKicked = false; ///< Bool determining if the product's been kicked
    double mKickSpeed; ///< Speed of which the product is kicked
    double mInitialX; ///< Initial x
    double mInitialY; ///< initial y
};


#endif //PRODUCT_H
