/**
* @file BeamDetectionVisitor.h
 * @author Mehrshad Bagherebadian
 *
 * Visitor that visits a beam object and checks if a product has broken beam
 */

#ifndef BEAMDETECTIONVISITOR_H
#define BEAMDETECTIONVISITOR_H

class Beam;
class OrLogicGate;
class Product;

#include "ItemVisitor.h"
#include "Beam.h"
#include "Product.h"
#include "OrLogicGate.h"



/**
 * @class BeamDetectionVisitor
 * @brief Detects if products intersect with a beam in the conveyor system.
 *
 * This visitor checks for intersections between products and a specified beam.
 * After visiting items, `UpdateBeamState()` updates the beam's detection status.
 */
class BeamDetectionVisitor : public ItemVisitor
{
public:
 BeamDetectionVisitor() : mProductDetected(false), mCurrentBeam(nullptr) {}

 /**
  * @brief Sets the current beam for detection and resets the product detection flag.
  * @param beam The beam to be set as the current beam for detection.
  */
 void VisitBeam(Beam* beam) override
 {
  mCurrentBeam = beam;
  mProductDetected = false;  //> Reset detection for this beam
 }

 /**
 * @brief Checks if a product intersects with the current beam.
 *
 * Calculates the product's bounding box and checks if it overlaps with the beam's range.
 * @param product The product to check for intersection.
 */
 void VisitProduct(Product* product) override
 {
  if (!mCurrentBeam) return;  //> Ensure a beam is set before processing

  int senderX = mCurrentBeam->GetX() + mCurrentBeam->GetSenderOffset();
  int senderY = mCurrentBeam->GetY();
  int receiverX = mCurrentBeam->GetX();
  int receiverY = mCurrentBeam->GetY();

  /// Calculate Product's bounding box
  int productX = product->GetX();
  int productY = product->GetY();
  int productHalfWidth = product->GetWidth() / 2;
  int productHalfHeight = product->GetHeight() / 2;

  // Calculate the product's bounding box coordinates
  int productLeftX = productX - productHalfWidth;
  int productRightX = productX + productHalfWidth;
  int productTopY = productY - productHalfHeight;
  int productBottomY = productY + productHalfHeight;

  // Check if the Product overlaps with the beam range
  bool withinXRange = (productRightX > senderX && productLeftX < receiverX);
  bool withinYRange = (productBottomY > senderY && productTopY < receiverY);

  if (withinXRange && withinYRange)
  {
   mProductDetected = true;  //> Mark as detected if Product intersects the beam
   mCurrentBeam->GetGame()->SetItemHitThisCycle(true);
   mCurrentBeam->GetGame()->SetItemPreviouslyHit(true);
   mCurrentBeam->GetGame()->SetCurrentProduct(product);
  }
 }

 /**
  * @brief Updates the beam's detection state based on whether a product was detected.
  *
  * This function should be called after visiting products to finalize the beam's state.
  */
 void UpdateBeamState()
 {
  if (mCurrentBeam)
  {
   mCurrentBeam->DetectProduct(mProductDetected);
  }
 }

private:
 /**
 * @brief Pointer to the beam currently being checked for product detection.
 */
 Beam* mCurrentBeam;           // The beam currently being checked

 /**
  * @brief Flag indicating whether a product was detected within the beam's range.
  */
 bool mProductDetected;        // Whether a product was detected within the beam path
};


#endif //BEAMDETECTIONVISITOR_H
