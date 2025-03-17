/**
 * @file ItemExample.cpp
 * @author Daniel Wills
 */

#include "pch.h"
#include "ItemExample.h"

using namespace std;

/// ItemExample filename
const wstring ItemExampleImageName = L"resources/images/football.png";

/// Constructor
ItemExample::ItemExample(Game* game) : Item(game, ItemExampleImageName)
{
}
