// Drawer.h

#ifndef DRAWER_H_INCLUDED
#define DRAWER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace std;

class Drawer
{
private:
    int TotalButtons;
    int PlayerFacing;

    float CameraOffsetX;
    float CameraOffsetY;

    float LastCameraOffsetX;
    float LastCameraOffsetY;

    // Images
    sf::Texture MenuBGim, MenuButton1, MenuButton2;

    //Worlds names / relative paths
    vector<string> WorldsName;

    int WorldTypeLoaded;
    int WorldNumberLoaded;

    //Tile images array
    vector<sf::Texture> TileImages;
    vector< vector<sf::Sprite> > WorldTileSprites;

public:

    // Sprites
    sf::Sprite MenuBG;
    sf::Sprite Player;

    vector<sf::Sprite> Buttons;
    vector<int> ButtonsGameState;

    Drawer(); // Default constructor
    Drawer(bool); // Parameterized constructor
    Drawer(Drawer&); // Copy constructor

    void Draw();
    void DrawMenu(sf::RenderWindow&);
    void DrawGame(GameManager::GameManager&, sf::RenderWindow&);
    void DrawWorld(GameManager::GameManager&, sf::RenderWindow&);
    void DrawGUI(GameManager::GameManager&, sf::RenderWindow&);


    int GetTotalButtons();
};

#endif // DRAWER_H_INCLUDED
