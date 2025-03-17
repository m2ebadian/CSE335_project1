/**
 * @file Banner.h
 * @author Tyler Nguyen
 *
 * Banner Class that shows up at the beginning & end of the game
 */
#ifndef BANNER_H
#define BANNER_H

#include "Item.h"

/**
 * Banner Class
 */
class Banner : public Item
{
private:
    std::wstring mText; ///< The text to display on banner
    bool mVisible = true; ///< Whether the banner is visible
    int mLevelWidth = 1150; ///< The width of the level
    int mLevelHeight = 800; ///< The height of the level
    double mTime = 0; ///< The time the banner has been visible in centi seconds


public:
    Banner(Game* game, std::wstring& text);

    void Draw(wxGraphicsContext* graphics) override;

    void Update(double elapsed) override;

    /// Default constructor (disabled)
    Banner() = delete;
    /// Copy constructor (disabled)
    Banner(const Banner&) = delete;
    /// Assignment operator (disabled)
    void operator=(const Banner&) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override
    {
        visitor->VisitBanner(this);
    }
};


#endif //BANNER_H
