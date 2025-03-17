/**
 * @file LogicGate.h
 * @author Soami Kapadia, Daniel Wills
 * @brief Base class for logic gates and declaration of related utilities.
 *
 */

#ifndef GATE_H
#define GATE_H

#include <vector>
#include <wx/graphics.h>
#include "Item.h"
#include "ItemGrabbable.h"
#include "PinOutput.h"
#include "PinInput.h"

class PinInput;
class PinOutput;

/**
 * @enum States
 * @brief The possible states of pins and gates.
 */
enum class States
{
    One, ///< Logic state one
    Zero, ///< Logic state zero
    Unknown ///< Logic state unknown
};

/**
 * @class LogicGate
 * @brief Base class for a Logic Gate.
 *
 * This applies to all the Gates only. Derived classes must implement the
 * ComputeOutput() function to calculate their specific logic behavior.
 */
class LogicGate : public Item
{
private:
    /// Size of the gate in pixels
    wxSize mGateSize;

    /// Vector containing input pins
    std::vector<std::shared_ptr<PinInput>> mInputPins;

    /// Vector containing output pins
    std::vector<std::shared_ptr<PinOutput>> mOutputPins;

public:
    /// Virtual destructor
    virtual ~LogicGate();

    /// Copy constructor (disabled)
    LogicGate(const LogicGate&) = delete;

    /**
     * @brief Draws the logic gate on the provided graphics context.
     *
     * This pure virtual function must be implemented by derived classes to render the logic gate.
     *
     * @param graphics The graphics context used for drawing.
     */
    void Draw(wxGraphicsContext* graphics) override = 0;

    std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;

    /**
     * @brief Get the width of the gate.
     *
     * @return The width of the gate in pixels.
     */
    double GetWidth() const { return mGateSize.GetWidth(); }

    /**
     * @brief Get the height of the gate.
     *
     * @return The height of the gate in pixels.
     */
    double GetHeight() const { return mGateSize.GetHeight(); }

    bool HitTest(int x, int y) override;

    bool Catch(PinOutput* pinOutput, wxPoint lineEnd) override;

    /**
     * Accept a visitor
     *
     * @param visitor visitor we accept
     */
    void Accept(ItemVisitor* visitor) override
    {
     //std::cout << "Accept" << std::endl;
     visitor->VisitLogicGate(this); // Allow the visitor to process this logic gate
    }

    /**
     * Sets the output pin to display the control
     *
     * @param showControl bool that determines whether the point controls are shown
     */
    void SetShowControlOutputPins(bool showControl) override
    {
     for (auto& pin : mOutputPins)
     {
       pin->SetShowControl(showControl); // Update the PinOutput
      }
    }

    /**
    * @brief Computes the output of the logic gate based on its current input.
    *
    * This function can be overridden in derived classes to define specific output
    * computation logic for different types of gates.
    */
    virtual void ComputeOutput() {};


protected:
    LogicGate(Game* game);

    /// Default constructor (disabled)
    LogicGate() = delete;

    /**
     * @brief Set the gate size.
     *
     * @param size
     */
    void SetGateSize(wxSize size) { mGateSize = size; }

    /// Draws the pins on the logic gate
    void DrawPins(wxGraphicsContext* graphics);

    //void SetPinLocations();
    /**
     * @brief Create an input pin.
     *
     * @param pin The pin to create.
     */
    void CreateInputPin(std::shared_ptr<PinInput> pin) { mInputPins.push_back(pin); }

    /**
     * @brief Create an output pin.
     *
     * @param pin The pin to create.
     */
    void CreateOutputPin(std::shared_ptr<PinOutput> pin) { mOutputPins.push_back(pin); }



     /**
    * @brief Retrieves the output pins of the item.
    * @return A vector of shared pointers to the output pins.
    */
    std::vector<std::shared_ptr<PinOutput>> GetOutputPins() {return mOutputPins;}

     /**
    * @brief Retrieves the input pins of the item.
    * @return A vector of shared pointers to the input pins.
    */
    std::vector<std::shared_ptr<PinInput>> GetPinInputs() { return mInputPins; }
};

#endif //GATE_H
