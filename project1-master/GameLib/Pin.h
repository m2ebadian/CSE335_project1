/**
* @file Pin.h
 * @author Soami Kapadia
 *
 * Base class for input and output pins
 */

#ifndef PIN_H
#define PIN_H

#include <wx/graphics.h>

class LogicGate;

/**
 * Pin states
 */
enum class State {One, Zero, Unknown};

/**
 * Base class for all pins
 */
class Pin {
protected:
 /// What logic gate/item does this pin belong to?
 LogicGate* mOwner = nullptr;

 /// The location of the pin relative to the logic gate
 wxPoint mLocation;

 /// Will this pin stay still? (NOTE: WORK AROUND FOR SENSOR MIGHT CHANGE LATER)
 bool mStatic = false;

 /// State of the pin
 State mState;

public:
 /**
  * Constructor
  * @param owner The item this pin belongs to
  * @param location The location relative to the owner
  */
 Pin(LogicGate* owner, wxPoint location) :
     mOwner(owner),
     mLocation(location),
     mState(State::Unknown) {}

 /**
  * Virtual destructor
  */
 virtual ~Pin() {}

 /**
  * Draw the pin
  * @param gc Graphics context to draw on
  */
 virtual void Draw(wxGraphicsContext* gc) = 0;

 /**
  * Set the pin location in pixels relative to the logic gate
  * @param x X location
  * @param y Y location
  */
 virtual void SetLocation(int x, int y) { mLocation = wxPoint(x, y); }

 /**
  * Set this pin as static (won't move)
  */
 void SetStatic() { mStatic = true; }

 /**
  * Get the owner of this pin
  * @return Pin owner
  */
 LogicGate* GetOwner() { return mOwner; }

 /**
  * Get the current state of the Pin
  * @return State enum
  */
 State GetState() { return mState; }

 /**
  * Set a state of the Pin
  * @param state State enum
  */
 virtual void SetState(State state) { mState = state; }

};

#endif //PIN_H