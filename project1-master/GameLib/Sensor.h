/**
 * @file Sensor.h
 * @author Conner O'Sullivan
 *
 *
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <map>

#include "Item.h"
#include "ItemEmpty.h"

/**
 * Sensor class
 */
class Sensor : public Item
{
private:
    std::vector<std::wstring> mOutputs; ///< The outputs supported by the sensor
    std::map<std::wstring, wxBitmap> mPanelImages; ///< Map that stores bitmaps of panel images and their names
    wxBitmap mCameraBitmap; ///< Camera's bitmap
    wxBitmap mCableBitmap; ///< Cable bitmap
    bool mImagesLoaded = false; ///< Bool that checks if images are already loaded
    std::vector<std::shared_ptr<OutputLogicGate>> mOutputGates; ///< Output gates for the sensor
    std::vector<wxRect> mPanelLocations; ///< Member variable to store panel locations

public:
    Sensor(Game* game, std::vector<std::wstring> outputs);

    /// Draws the sensor
    void Draw(wxGraphicsContext* graphics) override;

    /// Loads the sensor from the XML file
    void XmlLoad(wxXmlNode* node) override;


    /// Resets all the pins to their Zero state
    void ResetAllPins();

    /// Activates output pin to its correct state
    void ActivateOutputPin(const std::wstring& property);

    /// Checks if a product is in range and returns boolean
    bool IsProductInRange(const Product& product);

    /**
     * @brief Updates the state of the sensor or item.
     *
     * This function performs any necessary updates to the object’s state, such as checking conditions or updating attributes.
     */
    void Update();

    /**
     * @brief Accepts a visitor for the sensor.
     *
     * This function allows an `ItemVisitor` to visit the sensor, enabling operations to be performed on it.
     * @param visitor The visitor instance to accept.
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitSensor(this);
    }

};

#endif //SENSOR_H
