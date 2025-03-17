/**
 * @file ItemEmpty.cpp
 * @author Daniel Wills
 */

#include "pch.h"
#include "ItemEmpty.h"

/// Constructor
ItemEmpty::ItemEmpty(Game* game) : Item(game)
{
 SetLocation(0.0,0.0);
}
