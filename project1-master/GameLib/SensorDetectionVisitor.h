/**
 * @file SensorDetectionVisitor.h
 * @author Mehrshad Bagherebadian
 *
 * @brief Declaration of the SensorDetectionVisitor class, which detects products within the range of a sensor and activates sensor output pins accordingly.
 *
 * This file defines the SensorDetectionVisitor class, a visitor that checks if products
 * are within a sensor's detection range and activates the corresponding output pins based
 * on product properties like color, shape, and content.
 */
 
#ifndef SENSORDETECTIONVISITOR_H
#define SENSORDETECTIONVISITOR_H



#include "ItemVisitor.h"
#include "Product.h"
#include "Sensor.h"

class Product;
class Sensor;


/**
 * @class SensorDetectionVisitor
 * @brief A visitor that detects products within a sensor's range and activates output pins.
 *
 * The `SensorDetectionVisitor` class iterates over `Sensor` and `Product` items, checking
 * if a product is within the sensor’s detection range. If a product is detected, the class
 * activates sensor output pins based on the product's properties (color, shape, and content).
 */

class SensorDetectionVisitor : public ItemVisitor
{
public:
    /**
     * Constructor for SensorDetectionVisitor.
     * Initializes with no sensor set and no product detected.
     */
    SensorDetectionVisitor() : mProductInRange(false), mCurrentSensor(nullptr) {}

    /**
     * Set the current sensor to detect products for.
     * @param sensor The sensor to detect for
     */
    void VisitSensor(Sensor* sensor) override
    {
        mCurrentSensor = sensor;
        mProductInRange = false;  // Reset detection for this sensor
    }

    /**
     * Detect if a product is within range of the current sensor and activate pins accordingly.
     * @param product The product to check
     */
    void VisitProduct(Product* product) override
    {
        if (!mCurrentSensor) return;  // Ensure a sensor is set before processing

        // Check if product is within sensor range
        if (mCurrentSensor->IsProductInRange(*product))
        {
            mProductInRange = true;

            // Activate output pins based on product properties
            ActivatePinsForProperties(product);
        }
    }

    /**
     * After visiting, update the sensor state if a product was detected.
     */
    void UpdateSensorState()
    {
        if (mCurrentSensor)
        {
            // Activate pins based on detection results
            if (!mProductInRange)
            {
                mCurrentSensor->ResetAllPins();
            }
        }
    }

private:
    /**
     * @brief Pointer to the current sensor being checked for product detection.
     */
    Sensor* mCurrentSensor;       //> The sensor currently being checked

    /**
     * @brief Flag indicating whether a product is within the sensor's detection range.
     */
    bool mProductInRange;         //> Whether a product was detected within the sensor range

    /**
     * Helper method to activate sensor pins based on product properties.
     * @param product The product whose properties are checked
     */
    void ActivatePinsForProperties(Product* product)
    {
        /// Activate color pins
        switch (product->GetColor())
        {
            case Product::Properties::Red:
                //std::cout << " - Color: Red" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"red");
                break;
            case Product::Properties::Green:
                //std::cout << " - Color: Green" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"green");
                break;
            case Product::Properties::Blue:
                //std::cout << " - Color: Blue" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"blue");
                break;
            case Product::Properties::White:
                //std::cout << " - Color: White" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"white");
                break;
            default:
                //std::cout << " - Color: None" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"none");
                break;
        }

        // Activate shape pins
        switch (product->GetShape())
        {
            case Product::Properties::Square:
                //std::cout << " - Shape: Square" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"square");
                break;
            case Product::Properties::Circle:
                //std::cout << " - Shape: Circle" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"circle");
                break;
            case Product::Properties::Diamond:
                //std::cout << " - Shape: Diamond" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"diamond");
                break;
            default:
                break;
        }

        /// Activate content pins
        switch (product->GetContent())
        {
            case Product::Properties::Izzo:
                //std::cout << " - Content: Izzo" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"izzo");
                break;
            case Product::Properties::Smith:
                //std::cout << " - Content: Smith" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"smith");
                break;
            case Product::Properties::Basketball:
                //std::cout << " - Content: Basketball" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"basketball");
                break;
            case Product::Properties::Football:
                //std::cout << " - Content: Football" << std::endl;
                mCurrentSensor->ActivateOutputPin(L"football");
                break;
            default:
                break;
        }
    }
};




#endif //SENSORDETECTIONVISITOR_H
