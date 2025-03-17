/**
 * @file LevelLoader.h
 * @author Conner O'Sullivan
 *
 * Class used for Loading the levels
 */

#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include "Game.h"

/**
 * Class responsible for loading levels from XML files.
 */
class LevelLoader
{
public:
    LevelLoader(Game* game);
    void Load(const wxString& filename);
    void XmlItems(wxXmlNode* node);
    void XmlItem(wxXmlNode* node);
    void LoadConveyorProducts(const std::shared_ptr<Item>& conveyor, wxXmlNode* node);

private:
    Game* mGame; ///< Game instance
};


#endif //LEVELLOADER_H
