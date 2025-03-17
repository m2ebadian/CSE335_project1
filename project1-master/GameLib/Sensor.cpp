/**
 * @file Sensor.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */

#include "pch.h"
#include "Sensor.h"
#include "OutputLogicGate.h"
#include "Product.h"
#include "SensorDetectionVisitor.h"


/// Default length of line from the pin
const int DefaultLineLength = 20;

/// Image directory
const std::wstring DirectoryContainingImages = L"resources/images/";

/// The image file for the sensor cable
const std::wstring SensorCableImage = DirectoryContainingImages + L"sensor-cable.png";

/// The image file for the sensor camera
const std::wstring SensorCameraImage = DirectoryContainingImages + L"sensor-camera.png";

/// How far below Y location of the sensor system is the panel top?
const int PanelOffsetY = 87;

/// How much space for each property @return size of the property
const wxSize PropertySize(100, 40);

/// Size of a shape as a property in virtual pixels @return size of the property
const double PropertyShapeSize = 32;

/// Range where a product is viewed by the sensor relative
/// to the Y coordinate of the sensor.
const int SensorRange[] = {-40, 15};

/// The background color to draw the sensor panel @return panel color
const wxColour PanelBackgroundColor(128, 128, 128);

/// Color to use for "red" @return color of red products
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green" @return color of green products
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue" @return color of blue products
const wxColor UofMBlue(0, 39, 76);

/// Image for basketball
const std::wstring BasketballImage = DirectoryContainingImages + L"basketball.png";

/// Image for football
const std::wstring FootballImage = DirectoryContainingImages + L"football.png";

/// Image for Izzo
const std::wstring IzzoImage = DirectoryContainingImages + L"izzo.png";

/// Image for Smith
const std::wstring SmithImage = DirectoryContainingImages + L"smith.png";

/**
 * Constructor for the sensor
 *
 * @param game The game this sensor is a member of
 * @param outputs The output panels supported by the sensor
 */
Sensor::Sensor(Game* game, std::vector<std::wstring> outputs)
    : Item(game, SensorCameraImage), mOutputs(outputs)
{
    wxImage cameraImage(SensorCameraImage);
    wxImage cableImage(SensorCableImage);

    mCameraBitmap = wxBitmap(cameraImage);
    mCableBitmap = wxBitmap(cableImage);

    mImagesLoaded = true;
}

/**
 * Draws the sensor on the given graphics context.
 * NOTE: OUTPUT PANELS STILL NEED TO BE IMPLEMENTED
 *
 * @param graphics The graphics context to draw on.
 */
void Sensor::Draw(wxGraphicsContext* graphics)
{
    if (!mImagesLoaded)
    {
        // This should not happen if images are loaded in the constructor
        return;
    }

    // Get the position of the sensor
    double x = GetX();
    double y = GetY();

    // Calculate positions
    int cameraX = x - mCameraBitmap.GetWidth() / 2;
    int cameraY = y - mCameraBitmap.GetHeight() / 2;
    int cableX = x - mCableBitmap.GetWidth() / 2;
    int cableY = cameraY;

    // Draw the camera and cable
    graphics->DrawBitmap(mCableBitmap, cableX, cableY, mCableBitmap.GetWidth(), mCableBitmap.GetHeight());
    graphics->DrawBitmap(mCameraBitmap, cameraX, cameraY, mCameraBitmap.GetWidth(), mCameraBitmap.GetHeight());

    // Define the starting position for the panels
    double panelX = x + mCableBitmap.GetWidth() / 2;
    double panelY = y + PanelOffsetY;

    // Draw the panels
    for (size_t i = 0; i < mOutputs.size(); ++i)
    {
        const auto& output = mOutputs[i];

        // Set the panel color based on the output name
        wxColour panelColor;
        if (output == L"red")
        {
            panelColor = OhioStateRed;
        }
        else if (output == L"green")
        {
            panelColor = MSUGreen;
        }
        else if (output == L"blue")
        {
            panelColor = UofMBlue;
        }
        else if (output == L"white")
        {
            panelColor = *wxWHITE;
        }
        else
        {
            panelColor = PanelBackgroundColor; // Default color
        }

        // Draw the panel background
        graphics->SetBrush(wxBrush(panelColor));
        graphics->SetPen(*wxBLACK_PEN);
        graphics->DrawRectangle(panelX, panelY, PropertySize.GetWidth(), PropertySize.GetHeight());

        // Draw the panel content based on the output name
        if (mPanelImages.find(output) != mPanelImages.end())
        {
            wxBitmap contentBitmap = mPanelImages[output];
            double contentX = panelX + (PropertySize.GetWidth() - PropertyShapeSize) / 2;
            double contentY = panelY + (PropertySize.GetHeight() - PropertyShapeSize) / 2;
            graphics->DrawBitmap(contentBitmap, contentX, contentY, PropertyShapeSize, PropertyShapeSize);
        }
        else if (output == L"circle")
        {
            double shapeX = panelX + (PropertySize.GetWidth() - PropertyShapeSize) / 2;
            double shapeY = panelY + (PropertySize.GetHeight() - PropertyShapeSize) / 2;
            graphics->SetBrush(*wxWHITE_BRUSH);
            graphics->SetPen(*wxBLACK_PEN);
            graphics->DrawEllipse(shapeX, shapeY, PropertyShapeSize, PropertyShapeSize);
        }
        else if (output == L"square")
        {
            double shapeX = panelX + (PropertySize.GetWidth() - PropertyShapeSize) / 2;
            double shapeY = panelY + (PropertySize.GetHeight() - PropertyShapeSize) / 2;
            graphics->SetBrush(*wxWHITE_BRUSH);
            graphics->SetPen(*wxBLACK_PEN);
            graphics->DrawRectangle(shapeX, shapeY, PropertyShapeSize, PropertyShapeSize);
        }
        else if (output == L"diamond")
        {
            double shapeX = panelX + (PropertySize.GetWidth() - PropertyShapeSize) / 2;
            double shapeY = panelY + (PropertySize.GetHeight() - PropertyShapeSize) / 2;
            graphics->SetBrush(*wxWHITE_BRUSH);
            graphics->SetPen(*wxBLACK_PEN);
            graphics->PushState();
            graphics->Translate(shapeX + PropertyShapeSize / 2, shapeY + PropertyShapeSize / 2);
            graphics->Rotate(wxDegToRad(45));
            graphics->DrawRectangle(-PropertyShapeSize / 2, -PropertyShapeSize / 2, PropertyShapeSize,
                                    PropertyShapeSize);
            graphics->PopState();
        }
        if (i < mOutputGates.size())
        {
            wxPoint pinLocation(panelX + PropertySize.GetWidth(), panelY + PropertySize.GetHeight() / 2);
            mOutputGates[i]->SetLocation(pinLocation.x + DefaultLineLength, pinLocation.y);
        }
        // Move to the next panel position
        panelY += PropertySize.GetHeight();
    }

    // Draw lines indicating sensor range
    /*
    graphics->SetPen(*wxRED_PEN);
    graphics->StrokeLine(GetX() - mCameraBitmap.GetWidth() / 2, GetY() + SensorRange[0],
                         GetX() + mCameraBitmap.GetWidth() / 2, GetY() + SensorRange[0]);
    graphics->StrokeLine(GetX() - mCameraBitmap.GetWidth() / 2, GetY() + SensorRange[1],
                         GetX() + mCameraBitmap.GetWidth() / 2, GetY() + SensorRange[1]);
    */
}



/**
 * @brief Updates the sensor's detection state by applying a detection visitor.
 *
 * This function creates a `SensorDetectionVisitor` and applies it to all items in the game
 * to check for products within the sensor's range. It then updates the sensor's state based
 * on the visitor's results.
 */
void Sensor::Update()
{
    // Create the detection visitor
    SensorDetectionVisitor visitor;

    // Apply the visitor to all items in the game (or conveyor)
    visitor.VisitSensor(this);  // Set this sensor in the visitor
    GetGame()->Accept(&visitor);

    // Update sensor state based on the visitor's detection results
    visitor.UpdateSensorState();
}


/**
 * @brief Checks if a product is within the sensor's detection range.
 *
 * Determines whether the specified product is within the horizontal and vertical bounds
 * of the sensor's detection range, based on the sensor's position and detection area.
 * @param product The product to check for range.
 * @return `true` if the product is within the sensor's range, `false` otherwise.
 */
bool Sensor::IsProductInRange(const Product& product)
{
    // Get product's position
    double productX = product.GetX();
    double productY = product.GetY();
    double productHeight = product.GetHeight();

    // Get sensor's position
    double sensorX = GetX();
    double sensorY = GetY();

    // Calculate the horizontal bounds of the sensor's detection range (based on mCameraBitmap width)
    double sensorLeftX = sensorX - mCameraBitmap.GetWidth() / 2;
    double sensorRightX = sensorX + mCameraBitmap.GetWidth() / 2;

    // Calculate the vertical bounds of the product
    double productTopY = productY - productHeight / 2;
    double productBottomY = productY + productHeight / 2;

    // Check if the product's position is within both the horizontal and vertical range of the sensor
    bool withinXRange = (productX >= sensorLeftX && productX <= sensorRightX);
    bool withinYRange = (productBottomY >= sensorY + SensorRange[0] && productTopY <= sensorY + SensorRange[1]);

    return withinXRange && withinYRange;
}


/**
 * @brief Activates the output pin associated with a specified property.
 *
 * Finds the output pin corresponding to the provided property and sets its state to active (`State::One`).
 * @param property The property name as a wide string that determines which output pin to activate.
 */
void Sensor::ActivateOutputPin(const std::wstring& property)
{
    // Find and activate the output gate associated with the property
    auto it = std::find(mOutputs.begin(), mOutputs.end(), property);
    if (it != mOutputs.end())
    {
        size_t index = std::distance(mOutputs.begin(), it);
        if (index < mOutputGates.size())
        {
            mOutputGates[index]->SetOutputState(State::One);
            //std::wcout << L"Activated output pin for property: " << property << std::endl;
        }
    }
}



/**
 * @brief Resets all output pins to an inactive state.
 *
 * Sets each output pin in `mOutputGates` to the inactive state, typically represented by `State::Zero`.
 */
void Sensor::ResetAllPins()
{
    // Set all output pins to the inactive state (e.g., State::Zero)
    for (auto& gate : mOutputGates)
    {
        gate->SetOutputState(State::Zero);
    }
}




/**
 * Load this Sensor from an XML node
 * @param node The node we are loading the Sensor from
 */
void Sensor::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    wxXmlNode* child = node->GetChildren();
    while (child)
    {
        std::wstring outputName = child->GetName().ToStdWstring();
        mOutputs.push_back(outputName);

        // Load the image for the panel if it matches specific names
        if (outputName == L"izzo" || outputName == L"smith" || outputName == L"basketball" || outputName == L"football")
        {
            std::wstring contentImagePath;
            if (outputName == L"izzo")
            {
                contentImagePath = IzzoImage;
            }
            else if (outputName == L"smith")
            {
                contentImagePath = SmithImage;
            }
            else if (outputName == L"basketball")
            {
                contentImagePath = BasketballImage;
            }
            else if (outputName == L"football")
            {
                contentImagePath = FootballImage;
            }

            wxImage contentImage(contentImagePath);
            mPanelImages[outputName] = wxBitmap(contentImage);
        }
        // Create a new OutputLogicGate for the panel
        auto outputGate = std::make_shared<OutputLogicGate>(GetGame());
        mOutputGates.push_back(outputGate);
        outputGate->SetOutputState(State::Zero);
        GetGame()->Add(outputGate);

        // Go to the next panel
        child = child->GetNext();
    }
}
