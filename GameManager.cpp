// GameManager.cpp

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include "GameManager.h"
#include "utilidades.h"

using namespace std;


// Default constructor
GameManager::GameManager()
{
    GameState = 0;
    WorldNumber = -1;
    WorldType = -1;

    // Verbose
    cout << "GameManager creado con el constructor por defecto" << endl;
}

// Parameterized constructor
GameManager::GameManager(int GS)
{
    GameState = GS;
    WorldNumber = -1;
    WorldType = -1;

    // Verbose
    cout << "GameManager creado con el constructor parametrizado" << endl;
}


// Copy constructor
GameManager::GameManager(GameManager& GM)
{
    GameState = GM.GetGameState();
    WorldType = GM.GetCurrentWorldType();
    WorldNumber = GM.GetCurrentWorldNumber();

    // Verbose
    cout << "GameManager creado con el constructor de copia" << endl;
}


int GameManager::GetGameState()
{
    return GameState;
}


int GameManager::SetGameState(int GS)
{
    // Verbose
    cout << "GameState cambiado de " << GameState << " a " << GS << endl;

    GameState = GS;
    return GetGameState();
}


int GameManager::GetCurrentWorldType()
{
    return WorldType;
}


int GameManager::SetCurrentWorldType(int CWT)
{
    WorldType = CWT;
    return GetCurrentWorldType();
}


int GameManager::GetCurrentWorldNumber()
{
    return WorldNumber;
}


int GameManager::LoadWorld(int CW)
{
    WorldNumber = CW;
    string filepathstr ("maps/map"+ThreeDigits(WorldNumber+1)+".imf");
    char * filepath = new char [filepathstr.size()+1];
    strcpy (filepath, filepathstr.c_str());
    WorldFile.open(filepath);

    WorldFile >> WorldType >> WorldSizeX >> WorldSizeY;

    //Inicialización del mundo
    vector<int> tupla (2, -1);
    vector<vector<int> > cell (WorldSizeY, tupla);
    World.clear();

    for (int i=0; i < WorldSizeX; i++)
    {
        World.push_back(cell);
    }

    for (int i=0; i < WorldSizeX; i++)
    {
        for (int j=0; j < WorldSizeY; j++)
        {
            for (int k=0; k < 2; k++)
            {
                WorldFile >> World[i][j][k];
            }
        }
    }

    WorldFile.close();
    return GetCurrentWorldNumber();
}


int GameManager::GetWorldSizeX()
{
    return WorldSizeX;
}

int GameManager::GetWorldSizeY()
{
    return WorldSizeY;
}
