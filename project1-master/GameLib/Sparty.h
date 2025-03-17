/**
 * @file Sparty.h
 * @author Conner O'Sullivan
 *
 *
 */

#ifndef SPARTY_H
#define SPARTY_H

#include "Item.h"
#include "PinInput.h"

/**
 * Sparty Class
 */
class Sparty : public Item
{
public:
    Sparty(Game* game, double height, wxPoint pin, double kickDuration, double kickSpeed);
    void Update(double elapsed) override;
    void StartKick(); ///< Handles starting the kick
    void AnimateKick(double elapsed); ///< Handles animating the kick
    void ResetKick(); ///< resets the boot back to original position
    bool IsProductInKickRange(const Product& product); ///< handles checking if a product is in the kick range
    void KickProduct(); ///< Handles kicking the product off the conveyor
    void Draw(wxGraphicsContext* graphics) override; ///< draws the sparty

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitSparty(this);
    }

    /// Default constructor (disabled)
    Sparty() = delete;

    /// Copy constructor (disabled)
    Sparty(const Sparty&) = delete;

    /// Assignment operator
    void operator=(const Sparty&) = delete;

    void XmlLoad(wxXmlNode* node) override;


    /**
     * @brief Checks if Sparty is currently in the kicking state.
     *
     * @return `true` if Sparty is kicking, `false` otherwise.
     */
    bool GetKicking() {return mIsKicking;}


    /**
     * @brief Retrieves Sparty's current kicking speed.
     *
     * @return The kicking speed as a double.
     */
    double GetKickSpeed() {return mKickSpeed;} ///< returns the kicking speed

private:
    wxPoint mPin; ///< Input pin location
    double mKickDuration; ///< Duration of the kick animation
    double mKickSpeed; ///< Speed of the kick
    bool mIsKicking; ///< Whether Sparty is currently kicking
    double mKickTime; ///< Time elapsed in the current kick
    std::unique_ptr<wxBitmap> mBootBitmap; ///< Bitmap for the boot image
    std::unique_ptr<wxBitmap> mFrontBitmap; ///< Bitmap for the front image
    std::unique_ptr<wxBitmap> mBackBitmap; ///< Bitmap for back foot
    double mHeight; ///< Height desired for Sparty
    double mCurrentBootRotation; ///< Tracks the current rotation of the boot
    bool mProductKicked; ///< Tracks whether a product has already been kicked in the current cycle
    std::shared_ptr<InputLogicGate> mInputPin; ///< Sparty's input pin (Uses an invisible logic gate)
    State mPreviousState; ///< Tracks the previous state of the input pin

};


#endif //SPARTY_H
