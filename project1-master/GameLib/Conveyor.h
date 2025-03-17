/**
 * @file Conveyor.h
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 *
 *
 */

#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "Item.h"
#include "Game.h"

/// @return Rectangle of start button
const wxRect StartButtonRect(35, 29, 95, 36); // Check the dimensions and placement

/// @return Rectangle of stop button
const wxRect StopButtonRect(35, 87, 95, 36); // Ensure these match the actual button images

/**
 * Conveyor Belt Class
 */
class Conveyor : public Item

{
private:
    wxBitmap mBackgroundBitmap; ///< Bitmap for coneyorbelt background
    wxBitmap mBeltBitmap; ///< Bitmap for the belt
    wxBitmap mPanelStartedBitmap; ///< Bitmap for the panel when started is on
    wxBitmap mPanelStoppedBitmap; ///< Bitmap for the panel when stopped is on
    wxPoint mPanelLocation; ///< Location for the stop/start panel
    bool mStarted = false; ///< Keeps track of state of conveyorbelt
    double mHeight; ///< Height of conveyor belt
    int mSpeed; ///< Speed at which conveyorbelt moves
    double mBeltOffset = 0; ///< Keeps track of how far the belt has moved
    bool mReset = false; ///< sets the current state of resetting the conveyor to false

public:
    Conveyor(Game* game, int speed, double height, wxPoint panelLocation);
    void Draw(wxGraphicsContext* graphics) override;
    void Start();
    void Stop();
    void XmlLoad(wxXmlNode* node) override;
    void OnMouseClick(int x, int y);
    void MoveProducts(double elapsed);
    void Update(double elapsed) override;

    /// Expose the panel location so visitors can access it @return location of the panel
    wxPoint GetPanelLocation() const { return mPanelLocation; }

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitConveyor(this);
    }

    /**
    * Sets reset state
    * @param reset bool that we set our conveyor to
    */
    void SetReset(bool reset) { mReset = reset; }

    /**
    * Gets reset state
    * @return mReset bool that is used to determine reset
    */
    bool GetReset() { return mReset; }

    /**
    * Gets start state
    * @return Started bool that is used to determined if we are strating
    */
    bool GetStarted() { return mStarted; }
};


#endif //CONVEYOR_H
