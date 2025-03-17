/**
 * @file Beam.h
 * @author Conner O'Sullivan
 *
 *
 */

#ifndef BEAM_H
#define BEAM_H

#include "Item.h"

/**
 * Beam class
 */
class Beam : public Item
{
private:
    int mSenderOffset; ///< How much to the left to place the beamsender image
    int mOutputPinVal; ///< Keeps track of the state of output pin (0 or 1)
    std::unique_ptr<wxBitmap> mSenderBitmap; ///< Bitmap for sender
    std::unique_ptr<wxBitmap> mReceiverBitmap; ///< Bitmap for reciever
    std::shared_ptr<OutputLogicGate> mOutputPin; ///< Beam's output pin (Uses an invisible logic gate)


public:
    Beam(Game* game, int senderOffset);
    void Draw(wxGraphicsContext* graphics) override;
    void DetectProduct(bool productDetected);
    int GetOutputPinVal() const;
    void XmlLoad(wxXmlNode* node) override;

    /**
     * @brief Retrieves the sender offset for the item.
     * @return The sender offset as an integer.
     */
    int GetSenderOffset() const { return mSenderOffset; }

    /**
     * @brief Retrieves the width of the receiver bitmap.
     * @return The width of the receiver bitmap as an integer.
     */
    int GetWidth() const { return mReceiverBitmap->GetWidth(); }

    /**
    * @brief Retrieves the height of the receiver bitmap.
    * @return The height of the receiver bitmap as an integer.
    */
    int GetHeight() const { return mReceiverBitmap->GetHeight(); }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitBeam(this);
    }

     /**
    * @brief Updates the beam's state based on current conditions.
    *
    * This function performs any necessary updates to the beam, such as adjusting its
    * state or checking for interactions with other objects.
    */
    void UpdateBeam();

};


#endif //BEAM_H