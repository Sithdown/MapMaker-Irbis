// Drawer.cpp

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "GameManager.h"
#include "Drawer.h"
#include "utilidades.h"

using namespace std;

Drawer::Drawer()
{
}


Drawer::Drawer(bool valido)
{
    extern sf::RenderWindow App;

    if (valido)
    {
        CameraOffsetX = 0;
        CameraOffsetY = 0;
        PlayerFacing = 0;

        // Menu images
        MenuBGim.LoadFromFile("images/sprites/MenuBG.tga");
        MenuBG.SetTexture(MenuBGim);
        MenuBG.SetPosition(0.f, 0.f);

        MenuButton1.LoadFromFile("images/sprites/MenuButton1.png");
        MenuButton2.LoadFromFile("images/sprites/MenuButton2.png");


        // Button array init
        // 0, Menu, Play; 1, Menu, Exit;
        TotalButtons = 2;
        sf::Sprite TempSprite;

        for (int i=0; i < TotalButtons; i++)
        {
            Buttons.push_back(TempSprite);
        }

        Buttons[0].SetTexture(MenuButton1);
        Buttons[0].SetPosition(150.f, 150.f);
        ButtonsGameState.push_back(0);

        Buttons[1].SetTexture(MenuButton2);
        Buttons[1].SetPosition(900.f, 550.f);
        ButtonsGameState.push_back(0);

        //Worlds name
        WorldsName.push_back("forest");

        WorldTypeLoaded = -1;
        WorldNumberLoaded = -1;
    }
}


Drawer::Drawer(Drawer& DR)
{
    Drawer(true);
}


void Drawer::Draw()
{
    extern sf::RenderWindow App;
    extern GameManager::GameManager ManagerIrbis;

    // Clear screen
    App.Clear();

    switch (ManagerIrbis.GetGameState())
    {
    case 0 :
        DrawMenu(App);
        break;

    case 1 :
        DrawGame(ManagerIrbis, App);
        break;
    }

    // Display window contents on screen
    App.Display();
}


void Drawer::DrawMenu(sf::RenderWindow& App)
{
    App.Draw(MenuBG);

    for (int i=0; i < TotalButtons; i++)
    {
        if(ButtonsGameState[i] == 0)
        {
            App.Draw(Buttons[i]);
        }
    }
}


void Drawer::DrawGame(GameManager::GameManager& ManagerIrbis, sf::RenderWindow& App)
{
    DrawWorld(ManagerIrbis, App);
    App.Draw(Player);
    DrawGUI(ManagerIrbis, App);

    for (int i=0; i < TotalButtons; i++)
    {
        if(ButtonsGameState[i] == 1)
        {
            App.Draw(Buttons[i]);
        }
    }
}


void Drawer::DrawWorld(GameManager::GameManager& ManagerIrbis, sf::RenderWindow& App)
{
    //Load textures
    if (WorldTypeLoaded != ManagerIrbis.GetCurrentWorldType())
    {
        cout << "Cargando texturas" << endl; //Verbose
        int totaltiles = 2; // Cantidad de tiles diferentes
        string WorldPath = "images/tiles/" + WorldsName[ManagerIrbis.GetCurrentWorldNumber()] + "/";

        sf::Texture TempTile;

        for (int i=0; i < totaltiles; i++)
        {
            TileImages.push_back(TempTile);
            TileImages[i].LoadFromFile(WorldPath + ThreeDigits(i) + ".tga");
            cout << WorldPath + ThreeDigits(i) + ".tga cargado" << endl;
        }

    WorldTypeLoaded = ManagerIrbis.GetCurrentWorldType();
    cout << "Texturas cargadas" << endl; //Verbose
    }


    //Load World sprites
    if (WorldNumberLoaded != ManagerIrbis.GetCurrentWorldNumber())
    {
        cout << "Cargando sprites" << endl; //Verbose
        for (int i=0; i < ManagerIrbis.GetWorldSizeX(); i++)
        {
            sf::Sprite tmpsprt;
            vector<sf::Sprite> tmpvsprt (ManagerIrbis.GetWorldSizeY(), tmpsprt);

            for (int j=0; j < ManagerIrbis.GetWorldSizeY(); j++)
            {
                cout << "Cargando un sprite" << endl; //Verbose
                tmpvsprt[j].SetTexture(TileImages[ManagerIrbis.World[i][j][0]]);
                tmpvsprt[j].SetPosition(i*128.f, j*128.f);

            }

            WorldTileSprites.push_back(tmpvsprt);
        }
    WorldNumberLoaded = ManagerIrbis.GetCurrentWorldNumber();
    cout << "Sprites cargados" << endl; //Verbose
    }

    //Reposition sprites
    if ((CameraOffsetX != LastCameraOffsetX) || (CameraOffsetY != LastCameraOffsetY))
    {
        for (int i=0; i < ManagerIrbis.GetWorldSizeX(); i++)
        {
            for (int j=0; j < ManagerIrbis.GetWorldSizeY(); j++)
            {
                WorldTileSprites[i][j].SetPosition(CameraOffsetX + i*128.f, CameraOffsetY + j*128.f);
            }
        }
        LastCameraOffsetX = CameraOffsetX;
        LastCameraOffsetY = CameraOffsetY;
    }

    //Draw World sprites
    for (int i=0; i < ManagerIrbis.GetWorldSizeX(); i++)
    {
        for (int j=0; j < ManagerIrbis.GetWorldSizeY(); j++)
        {
            App.Draw(WorldTileSprites[i][j]);
        }
    }
}


void Drawer::DrawGUI(GameManager::GameManager& ManagerIrbis, sf::RenderWindow& App)
{

}

/*
bool Drawer::CheckColission(int dir)
{
    extern GameManager::GameManager ManagerIrbis;

    bool colission = false;
    for (int i=0; i < ManagerIrbis.GetWorldSizeX(); i++)
    {
        for (int j=0; j < ManagerIrbis.GetWorldSizeY(); j++)
        {
            //Comprueba que sea un tile con colisión
            if (ManagerIrbis.World[i][j][1] == 1)
            {
                // Comprueba si el player comparte algún punto en X con el tile
                if (((Player.GetPosition().x >= WorldTileSprites[i][j].GetPosition().x) &&
                (Player.GetPosition().x <= (WorldTileSprites[i][j].GetPosition().x + WorldTileSprites[i][j].GetSize().x))) ||
                (((Player.GetPosition().x + Player.GetSize().x) >= WorldTileSprites[i][j].GetPosition().x) &&
                ((Player.GetPosition().x + Player.GetSize().x) <= (WorldTileSprites[i][j].GetPosition().x + WorldTileSprites[i][j].GetSize().x))))
                {
                    // Comprueba si el player comparte algún punto en Y con el tile
                    if ((((Player.GetPosition().y >= WorldTileSprites[i][j].GetPosition().y)) &&
                    (Player.GetPosition().y <= (WorldTileSprites[i][j].GetPosition().y + WorldTileSprites[i][j].GetSize().y))) ||
                    (((Player.GetPosition().y + Player.GetSize().y) >= WorldTileSprites[i][j].GetPosition().y) &&
                    (Player.GetPosition().y + Player.GetSize().y) <= (WorldTileSprites[i][j].GetPosition().y + WorldTileSprites[i][j].GetSize().y)))
                    {
                        colission = true;
                    }
                }
            }
        }
    }

    return colission;
}
*/

int Drawer::GetTotalButtons()
{
    return TotalButtons;
}
