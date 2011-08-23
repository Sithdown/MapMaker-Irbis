// InputHandler.cpp

#include <iostream>
#include <SFML/Window.hpp>
#include "GameManager.h"
#include "InputHandler.h"
#include "Drawer.h"


using namespace std;

// Default constructor
InputHandler::InputHandler()
{
    ButtonPressed = -1;
}

// Copy constructor
InputHandler::InputHandler(InputHandler& IH)
{
    Event = IH.Event;
    ButtonPressed = IH.GetButtonPressed();
}


bool InputHandler::EventCheck(sf::Window& App)
{
    return App.PollEvent(Event);
}


void InputHandler::HandleEventInput()
{
    if (Event.Type == sf::Event::MouseButtonPressed)
    {
        switch (Event.MouseButton.Button)
        {
        case sf::Mouse::Left :
            MouseLeftClick();
            break;
        }
    }

    if (Event.Type == sf::Event::MouseButtonReleased)
    {
        switch (Event.MouseButton.Button)
        {
        case sf::Mouse::Left :
            MouseLeftRelease();
            break;
        }
    }

    if (Event.Type == sf::Event::KeyPressed)
    {
        switch (Event.Key.Code)
        {
        case sf::Keyboard::Escape :
            EscapeKey();
            break;

        }
    }


}


void InputHandler::HandleInput()
{
    extern sf::RenderWindow App;

    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))  UpKey();

}


void InputHandler::UpKey()
{
    extern GameManager::GameManager ManagerIrbis;
    extern Drawer::Drawer DrawerIrbis;
    int dir = 0;

    /*
    if(ManagerIrbis.GetGameState() == 1)
    {
        if (DrawerIrbis.GetPlayerFacing() != dir )
        {
            DrawerIrbis.SetPlayerFacing(dir);
        }

        DrawerIrbis.MovePlayer(dir);
    }
    */
}


void InputHandler::EscapeKey()
{
    extern GameManager::GameManager ManagerIrbis;

    if(ManagerIrbis.GetGameState() == 0)
    {
        ManagerIrbis.SetGameState(1);
    }
    else
    {
        ManagerIrbis.SetGameState(0);
    }
}




bool InputHandler::MouseOverSprite(sf::Sprite& Sprite)
{
    extern sf::RenderWindow App;
    sf::Vector2i mousepos = sf::Mouse::GetPosition(App);
    sf::Vector2f sprpos = Sprite.GetPosition();
    sf::Vector2f sprsize = Sprite.GetSize();

    return ((mousepos.x > sprpos.x ) && (mousepos.x < (sprpos.x + sprsize.x)) && (mousepos.y > sprpos.y ) && (mousepos.y < (sprpos.y + sprsize.y)));
}


void InputHandler::MouseLeftClick()
{
    extern GameManager::GameManager ManagerIrbis;
    extern Drawer::Drawer DrawerIrbis;

    for (int i=0; i < DrawerIrbis.GetTotalButtons(); i++)
    {
        if (ManagerIrbis.GetGameState() == DrawerIrbis.ButtonsGameState[i])
        {
            if (MouseOverSprite(DrawerIrbis.Buttons[i]))
            {
                SetButtonPressed(i);
            }
        }
    }
}


void InputHandler::MouseLeftRelease()
{
    extern GameManager::GameManager ManagerIrbis;
    extern Drawer::Drawer DrawerIrbis;

    for (int i=0; i < DrawerIrbis.GetTotalButtons(); i++)
    {
        if ((ManagerIrbis.GetGameState() == DrawerIrbis.ButtonsGameState[i]) && (GetButtonPressed() == i))
        {
            if (MouseOverSprite(DrawerIrbis.Buttons[i]))
            {
                ButtonAction(i);
            }
        }
    }

    SetButtonPressed(-1);
}


int InputHandler::GetButtonPressed()
{
    return ButtonPressed;
}


int InputHandler::SetButtonPressed(int BP)
{
    ButtonPressed = BP;
    return GetButtonPressed();
}


void InputHandler::ButtonAction(int buttonid)
{
    extern sf::RenderWindow App;
    extern GameManager::GameManager ManagerIrbis;
    extern Drawer::Drawer DrawerIrbis;

    switch (buttonid)
    {
        case 0:
            ManagerIrbis.SetGameState(1);
        break;

        case 1:
            App.Close();
        break;
    }
}
