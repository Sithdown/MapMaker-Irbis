// GameManager.h

#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class GameManager
{
private:
    int GameState; // Menu(0), InGame(1)
    int WorldNumber; // Mundo mágico de stanley
    int WorldType;
    int WorldSizeX;
    int WorldSizeY;

    fstream WorldFile;

public:
    //Matriz de tiles (tileid, clip)
    vector<vector<vector<int> > > World;

    GameManager(); // Default constructor
    GameManager(int); // Parameterized constructor
    GameManager(GameManager&); // Copy constructor

    int GetGameState();
    int SetGameState(int);

    int GetCurrentWorldType();
    int SetCurrentWorldType(int);

    int GetCurrentWorldNumber();
    int LoadWorld(int);

    int GetWorldSizeX();
    int GetWorldSizeY();
};



#endif // GAMEMANAGER_H_INCLUDED
