////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "GameManager.h"
#include "InputHandler.h"
#include "Drawer.h"

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>


#define IDBUTTON 102
HINSTANCE g_hInst;

////////////////////////////////////////////////////////////
/// Function called whenever one of our windows receives a message
///
////////////////////////////////////////////////////////////
LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, World!");

    HWND hwndButton;

    switch (Message)
    {
        case WM_PAINT:
        {
           hdc = BeginPaint(Handle, &ps);

            // Here your application is laid out.
            // For this introduction, we just print out "Hello, World!"
            // in the top left corner.
            TextOut(hdc,
                5, 5,
                greeting, _tcslen(greeting));
            // End application specific layout section.

            EndPaint(Handle, &ps);
            return 0;
        }

        case WM_COMMAND:{
            if(((HWND)LParam) && (HIWORD(WParam) == BN_CLICKED)){
                int iMID;
                iMID = LOWORD(WParam);
                switch(iMID){
                    case IDBUTTON:{
                        MessageBox(Handle, (LPCTSTR)"¡Deja de darme clicks, me hases cosquillas!",  (LPCTSTR) "MENSAJE DE HORACIO", MB_OK|MB_ICONEXCLAMATION);
                        break;
                    }
                    default:
                        break;
                }
            }
            break;
        }

        case WM_CREATE:
        {
            hwndButton = CreateWindowEx(0,                    /* more or ''extended'' styles */
                     TEXT("BUTTON"),                         /* GUI ''class'' to create */
                     TEXT("Horacio"),                        /* GUI caption */
                     WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,   /* control styles separated by | */
                     10,                                     /* LEFT POSITION (Position from left) */
                     10,                                     /* TOP POSITION  (Position from Top) */
                     200,                                    /* WIDTH OF CONTROL */
                     30,                                     /* HEIGHT OF CONTROL */
                     Handle,                                   /* Parent window handle */
                     (HMENU)IDBUTTON,                        /* control''s ID for WM_COMMAND */
                     g_hInst,                                /* application instance */
                     NULL);
            break;
        }

        // Quit when we close the main window
        case WM_CLOSE :
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(Handle, Message, WParam, LParam);
}

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \param Instance : Instance of the application
///
/// \return Error code
///
////////////////////////////////////////////////////////////
INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE, LPSTR, INT)
{
    // Define a class for our main window
    WNDCLASS WindowClass;
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = &OnEvent;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = Instance;
    WindowClass.hIcon         = NULL;
    WindowClass.hCursor       = 0;
    WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
    WindowClass.lpszMenuName  = NULL;
    WindowClass.lpszClassName = "SFML App";
    RegisterClass(&WindowClass);

    // Let's create the main window
    HWND Window = CreateWindow("SFML App", "SFML Win32", WS_SYSMENU | WS_VISIBLE, 0, 0, 800, 600, NULL, NULL, Instance, NULL);

    // Let's create two SFML views
    HWND View1 = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 50,  100, 300, 400, Window, NULL, Instance, NULL);
    HWND View2 = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 400, 100, 300, 400, Window, NULL, Instance, NULL);
    sf::RenderWindow SFMLView1(View1);
    sf::RenderWindow SFMLView2(View2);


    // Cargar imgs
    sf::Texture Image1, Image2;
    if (!Image1.LoadFromFile("images/sprites/image1.png") || !Image2.LoadFromFile("images/sprites/image2.png"))
        return EXIT_FAILURE;
    sf::Sprite Sprite1(Image1);
    sf::Sprite Sprite2(Image2);


    // Loop until a WM_QUIT message is received
    MSG Message;
    Message.message = ~WM_QUIT;
    while (Message.message != WM_QUIT)
    {
        if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
        {
            // If a message was waiting in the message queue, process it
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
        else
        {
            // Clear views
            SFMLView1.Clear();
            SFMLView2.Clear();

            // Draw sprite 1 on view 1
            SFMLView1.Draw(Sprite1);

            // Draw sprite 2 on view 2
            SFMLView2.Draw(Sprite2);

            // Display each view on screen
            SFMLView1.Display();
            SFMLView2.Display();
        }

    }

    // Destroy the main window
    DestroyWindow(Window);

    // Don't forget to unregister the window class
    UnregisterClass("SFML App", Instance);

    return EXIT_SUCCESS;
}
