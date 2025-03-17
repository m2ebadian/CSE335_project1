/**
 * @file ItemGrabbableExample.cpp
 * @author Daniel Wills
 */

#include "pch.h"
#include "ItemGrabbableExample.h"

using namespace std;

/// ItemGrabbableExample filename
const wstring ItemGrabbableExampleImageName = L"resources/images/basketball.png";

/// Constructor
ItemGrabbableExample::ItemGrabbableExample(Game* game) : ItemGrabbable(game, ItemGrabbableExampleImageName)
{
}
