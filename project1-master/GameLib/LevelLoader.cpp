/**
 * @file LevelLoader.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */
#include "pch.h"
#include "LevelLoader.h"

#include "Beam.h"
#include "Conveyor.h"
#include "Game.h"
#include "Sparty.h"
#include "Sensor.h"
#include "Item.h"
#include "Product.h"
#include "Scoreboard.h"

/**
 * LevelLoader constructor
 * @param game The game instance we're loading the level onto
 */
LevelLoader::LevelLoader(Game* game) : mGame(game)
{
}

/**
 * Load the file
 * @param filename The filename we are loading from
 */
void LevelLoader::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load level file");
        return;
    }

    auto root = xmlDoc.GetRoot();

    auto child = root->GetChildren();
    for (; child; child = child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"items")
        {
            XmlItems(child);
        }
    }
}

/**
 * Load all items within the XML
 * @param node The node we are loading items from
 */
void LevelLoader::XmlItems(wxXmlNode* node)
{
    auto itemNode = node->GetChildren();
    for (; itemNode; itemNode = itemNode->GetNext())
    {
        XmlItem(itemNode);
    }
}

/**
 * Creating the specific item
 * @param node The node we are loading items from
 */
void LevelLoader::XmlItem(wxXmlNode* node)
{
    std::shared_ptr<Item> item;
    auto name = node->GetName();

    if (name == L"sparty")
    {
        item = std::make_shared<Sparty>(mGame, 0, wxPoint(0, 0), 0, 0);
    }
    else if (name == L"sensor")
    {
        item = std::make_shared<Sensor>(mGame, std::vector<std::wstring>());
    }
    else if (name == L"beam")
    {
        item = std::make_shared<Beam>(mGame, 0);
    }
    else if (name == L"conveyor")
    {
        item = std::make_shared<Conveyor>(mGame, 0, 0, wxPoint(0, 0));
    }
    else if (name == L"scoreboard")
    {
        std::wstring emptyGoal;
        item = std::make_shared<Scoreboard>(mGame, 0, 0, 10, 0, 0, emptyGoal);
    }

    if (item)
    {
        item->XmlLoad(node);
        mGame->Add(item); // Add the item (like Conveyor) to the game

        // If it's a conveyor, load its nested products
        if (name == L"conveyor")
        {
            LoadConveyorProducts(item, node);
        }
    }
}


/**
 * Load products nested within the conveyor node.
 * @param conveyor The conveyor item to which products are related.
 * @param node The XML node representing the conveyor and its nested products.
 */
void LevelLoader::LoadConveyorProducts(const std::shared_ptr<Item>& conveyor, wxXmlNode* node)
{
    double lastProductY = conveyor->GetY(); // Get the Y position of the conveyor
    std::shared_ptr<Product> lastProduct = nullptr;

    for (wxXmlNode* child = node->GetChildren(); child; child = child->GetNext())
    {
        if (child->GetName() == L"product")
        {
            // Create the product
            auto product = std::make_shared<Product>(mGame, Product::Properties::Square,
                                                     Product::Properties::Green,
                                                     Product::Properties::Izzo, false);
            product->XmlLoad(child);

            // If placement starts with "+", offset from last product
            if (child->GetAttribute(L"placement", L"0").StartsWith("+"))
            {
                lastProductY -= mGame->GetVirtualPixelsY(product->GetPlacement());
            }
            else
            {
                lastProductY = conveyor->GetY() - mGame->GetVirtualPixelsY(product->GetPlacement());
            }

            product->SetLocation(conveyor->GetX(), lastProductY);
            product->SetInitialPosition(conveyor->GetX(), lastProductY); // Set the initial position
            mGame->Add(product); // Add product to the game

            // Update the last product
            lastProduct = product;
        }
    }

    // Tell the last product that it is last
    if (lastProduct != nullptr)
    {
        lastProduct->SetLast();
    }
}
