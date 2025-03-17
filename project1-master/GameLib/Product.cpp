/**
 * @file Product.cpp
 * @author Conner O'Sullivan, Mehrshad Bagherebadian
 */

#include "pch.h"
#include "Product.h"
#include "Game.h"
#include "Conveyor.h"
#include "ScoreUpdateVisitor.h"


/// Image directory
const std::wstring DirectoryContainingImages = L"resources/images/";

/// Image for basketball
const std::wstring BasketballImage = DirectoryContainingImages + L"basketball.png";

/// Image for football
const std::wstring FootballImage = DirectoryContainingImages + L"football.png";

/// Image for Izzo
const std::wstring IzzoImage = DirectoryContainingImages + L"izzo.png";

/// Image for Smith
const std::wstring SmithImage = DirectoryContainingImages + L"smith.png";

/// Default product size in pixels
std::wstring ProductDefaultSize = L"80";

/// Size to draw content relative to the product size
double ContentScale = 0.8;

/// Color to use for "red" @returns red color
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green" @returns green color
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue" @returns blue color
const wxColor UofMBlue(0, 39, 76);

/// Delay after last product has left beam or
/// been kicked before we end the level.
const double LastProductDelay = 3;

const std::map<std::wstring, Product::Properties> Product::NamesToProperties = {
    {L"red", Product::Properties::Red},
    {L"green", Product::Properties::Green},
    {L"blue", Product::Properties::Blue},
    {L"white", Product::Properties::White},
    {L"square", Product::Properties::Square},
    {L"circle", Product::Properties::Circle},
    {L"diamond", Product::Properties::Diamond},
    {L"izzo", Product::Properties::Izzo},
    {L"smith", Product::Properties::Smith},
    {L"basketball", Product::Properties::Basketball},
    {L"football", Product::Properties::Football},
    {L"none", Product::Properties::None},
};

const std::map<Product::Properties, Product::Types> Product::PropertiesToTypes = {
    {Product::Properties::Red, Product::Types::Color},
    {Product::Properties::Green, Product::Types::Color},
    {Product::Properties::Blue, Product::Types::Color},
    {Product::Properties::White, Product::Types::Color},
    {Product::Properties::Square, Product::Types::Shape},
    {Product::Properties::Circle, Product::Types::Shape},
    {Product::Properties::Diamond, Product::Types::Shape},
    {Product::Properties::Izzo, Product::Types::Content},
    {Product::Properties::Smith, Product::Types::Content},
    {Product::Properties::Football, Product::Types::Content},
    {Product::Properties::Basketball, Product::Types::Content},
    {Product::Properties::None, Product::Types::Content}
};

const std::map<Product::Properties, std::wstring> Product::PropertiesToContentImages = {
    {Product::Properties::Izzo, L"izzo.png"},
    {Product::Properties::Smith, L"smith.png"},
    {Product::Properties::Football, L"football.png"},
    {Product::Properties::Basketball, L"basketball.png"}
};

/**
 * Constructor for the product.
 *
 * @param game The game this product is a member of
 * @param shape The shape the product takes
 * @param color The color of the product
 * @param content The content the product contains
 * @param kick Indicated whether the product should be kicked
 */
Product::Product(Game* game, Properties shape, Properties color, Properties content, bool kick)
    : Item(game, SmithImage), mShape(shape), mColor(color), mContent(content), mKick(kick)
{
}

/**
 * Draws a product on the given graphics context.
 *
 * @param graphics The graphics context to draw on.
 */
void Product::Draw(wxGraphicsContext* graphics)
{
    // Set the color based on the product's color property
    wxColour color;
    switch (mColor)
    {
    case Properties::Red:
        color = OhioStateRed;
        break;
    case Properties::Green:
        color = MSUGreen;
        break;
    case Properties::Blue:
        color = UofMBlue;
        break;
    case Properties::White:
        color = *wxWHITE;
        break;
    default:
        break;
    }

    // Set the brush and pen for drawing
    graphics->SetBrush(wxBrush(color));
    graphics->SetPen(wxPen(color));

    // Draw the shape based on the product's shape property
    double size = std::stod(ProductDefaultSize);
    double halfSize = size / 2;
    double x = GetX() - halfSize;
    double y = GetY() - halfSize;

    switch (mShape)
    {
    case Properties::Square:
        graphics->DrawRectangle(x, y, size, size);
        break;

    case Properties::Circle:
        graphics->DrawEllipse(x, y, size, size);
        break;

    case Properties::Diamond:
        graphics->PushState();
        graphics->Translate(GetX(), GetY());
        graphics->Rotate(wxDegToRad(45));
        graphics->DrawRectangle(-halfSize, -halfSize, size, size);
        graphics->PopState();
        break;

    default:
        break;
    }

    // Draw the content if there is any
    if (mContent != Properties::None)
    {
        double contentSize = size * ContentScale;
        double contentX = GetX() - contentSize / 2;
        double contentY = GetY() - contentSize / 2;
        graphics->DrawBitmap(mContentBitmap, contentX, contentY, contentSize, contentSize);
    }
}


/**
 * Update the product's position based on the conveyor's speed and elapsed time.
 * @param conveyorSpeed The speed of the conveyor in virtual pixels per second
 * @param elapsed The elapsed time since the last update
 */
void Product::Update(double conveyorSpeed, double elapsed)
{
    // Upcall to the base class
    Item::Update(elapsed);

    // Calculate movement based on speed and elapsed time
    double movement = conveyorSpeed * elapsed;
    double newY = GetY() + movement;

    if (mKicked)
    {
        double movementX = mKickSpeed*elapsed;
        double newX = GetX() - movementX;
        SetLocation(newX, newY);
    }
    else
    {
        SetLocation(GetX(), newY);
    }

    //std::cout << "Product moved to new position: X = " << GetX() << ", Y = " << newY << std::endl;

    // Check if the product has left the beam, if so
    // End the level if it is the last product
    if(mLastProductDelay > 0)
    {
        mLastProductDelay -= elapsed;
        //std::cout << "Last product delay: " << mLastProductDelay << std::endl;
        if(mLastProductDelay <= 0)
        {
            mLastProductDelay = 0;

            // The level has ended
            GetGame()->LevelComplete();
        }
    }
}

/**
 * Checks when a product has left the beam. Handles scoring and if last item, it ends the level.
 */
void Product::HasLeftBeam()
{
    if (mLast)
    {
        mLastProductDelay = LastProductDelay;
    }
    // Scoring

    // Determine if Sparty was kicked and if the item wants to be kicked
    bool spartyKicked = mKicked;
    bool productWantsKicked = mKick;

    // Create the ScoreUpdateVisitor
    ScoreUpdateVisitor visitor(spartyKicked, productWantsKicked);

    // Accept the visitor
    GetGame()->Accept(&visitor);
}

void Product::Kicked(double kickspeed)
{
    mKicked = true;
    mKickSpeed = kickspeed;
}

/**
 * Load this Product from an XML node
 * @param node The node we are loading the Product from
 */
void Product::XmlLoad(wxXmlNode* node)
{
    wxString shapeStr = node->GetAttribute(L"shape", L"square");
    wxString colorStr = node->GetAttribute(L"color", L"red");
    wxString contentStr = node->GetAttribute(L"content", L"none");
    wxString kickStr = node->GetAttribute(L"kick", L"no");
    wxString placementStr = node->GetAttribute(L"placement", L"0");

    mShape = NamesToProperties.at(shapeStr.ToStdWstring());
    mColor = NamesToProperties.at(colorStr.ToStdWstring());
    mContent = NamesToProperties.at(contentStr.ToStdWstring());
    mKick = (kickStr == L"yes");
    placementStr.ToDouble(&mPlacement);
    if (mContent != Properties::None)
    {
        std::wstring contentImagePath = DirectoryContainingImages + L"/" + PropertiesToContentImages.at(mContent);
        wxImage contentImage(contentImagePath);
        mContentBitmap = wxBitmap(contentImage);
    }
}
/**
 * Sets the initial position of a product (used for reset when stop)
 *
 * @param x location of the product
 * @param y location of the product
 */
void Product::SetInitialPosition(double x, double y)
{
    mInitialX = x;
    mInitialY = y;
}

/**
 * Sets the location when reseting after stop
 */
void Product::ResetPosition()
{
    mKicked = false;
    SetLocation(mInitialX, mInitialY);
}