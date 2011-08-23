// InputHandler.h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED

using namespace std;

class InputHandler
{
private:
    int ButtonPressed;

    void LeftKey();
    void RightKey();
    void UpKey();
    void DownKey();
    void EscapeKey();
    void SpaceKey();

    void MouseLeftClick();
    void MouseLeftRelease();

public:
    sf::Event Event;

    InputHandler(); // Default constructor
    InputHandler(InputHandler&); // Copy constructor

    bool EventCheck(sf::Window&);
    void HandleEventInput();
    void HandleInput();

    bool MouseOverSprite(sf::Sprite&);

    int GetButtonPressed();
    int SetButtonPressed(int);
    void ButtonAction(int);

};

#endif // INPUTHANDLER_H_INCLUDED
