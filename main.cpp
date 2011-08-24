#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>


#include "IDS.h"

#define WM_SIZE                         0x0005

HINSTANCE g_hInst;

/*  Declaración del procedimiento de ventana  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


// Datos de la aplicación
typedef struct stDatos {
   int ValorH;
   int ValorV;
   char Texto[80];
} DATOS;


/*
HWND CreateScrollbar(const HWND hParent,const HINSTANCE hInst,DWORD dwStyle,
                     const RECT& rc,const int id)
{
dwStyle|=WS_CHILD|WS_VISIBLE;
return CreateWindowEx(0,                            //extended styles
                      _T("scrollbar"),              //control 'class' name
                      0,                            //control caption
                      dwStyle,                      //control style
                      rc.left,                      //position: left
                      rc.top,                       //position: top
                      rc.right,                     //width
                      rc.bottom,                    //height
                      hParent,                      //parent window handle
                      //control's ID
                      reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
                      hInst,                        //application instance
                      0);                           //user defined info
}
*/






/*  Esta función es invocada por la función DispatchMessage()  */
LRESULT CALLBACK OnEvent(HWND Handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;
    static DATOS Datos;
    static DATOS *Datoss;

    /* Botón */
    HWND hwndButton;
    HWND hwndScrollBarH;

    switch (msg)                  /* manipulador del mensaje */
    {
        case WM_CREATE:
        {
            Datoss = (DATOS*)lParam;
            hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
            Datos.ValorH = 10;
            Datos.ValorV = 32;

            // Crear botón
            hwndButton = CreateWindowEx(0,                    /* more or ''extended'' styles */
                     TEXT("BUTTON"),                         /* GUI ''class'' to create */
                     TEXT("Horacio"),                        /* GUI caption */
                     WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,   /* control styles separated by | */
                     100,                                     /* LEFT POSITION (Position from left) */
                     10,                                     /* TOP POSITION  (Position from Top) */
                     200,                                    /* WIDTH OF CONTROL */
                     30,                                     /* HEIGHT OF CONTROL */
                     Handle,                                   /* Parent window handle */
                     (HMENU)ID_BUTTON,                        /* control''s ID for WM_COMMAND */
                     g_hInst,                                /* application instance */
                     NULL);

            // Crear Scrollbar Horizontal
            //RECT rh={(64*2+22+5),(720-15),(1024-(64*2+20+27)),15};
            //CreateScrollbar(Handle,hInstance,SBS_HORZ,rh,ID_SCROLLHH);

            // Crear Scrollbar Vertical
            //RECT rv={(1024-20),0,15,(748-20-23)};
            //CreateScrollbar(Handle,hInstance,SBS_VERT,rv,ID_SCROLLVV);
            break;
        }
        case WM_SIZE:
        {
            std::cout << "RESIZE" << std::endl;

            /*

            AQUI QUIERO PODER HACER UN REDRAW DE SFMLView1

            */
        }

        case WM_COMMAND:
        {
            // Menu Archivo --> Abrir diálogo
            if(LOWORD(wParam) == CM_DIALOGO)
            {
                DialogBoxParam(hInstance, "DialogoPrueba", Handle, DlgProc, (LPARAM)&Datos);
            }

            // Menu Archivo --> Abrir diálogo
            if(LOWORD(wParam) == CM_CLOSE)
            {
                PostQuitMessage(0);
            }


            // Menu Ver --> 1440x900
            if(LOWORD(wParam) == CM_SIZEA)
            {
                SetWindowPos(Handle,HWND_TOP,0,0,1440,900,SWP_NOMOVE);
            }

            // Menu Ver --> 1680x1050
            if(LOWORD(wParam) == CM_SIZEB)
            {
                 SetWindowPos(Handle,HWND_TOP,0,0,1680,1050,SWP_NOMOVE);
            }

            // Menu Ver --> 1920x1080
            if(LOWORD(wParam) == CM_SIZEC)
            {
                 SetWindowPos(Handle,HWND_TOP,0,0,1920,1080,SWP_NOMOVE);
            }

            break;
        }

        case WM_DESTROY:
           PostQuitMessage(0);    /* envía un mensaje WM_QUIT a la cola de mensajes */
           break;
        default:                  /* para los mensajes de los que no nos ocupamos */
           return DefWindowProc(Handle, msg, wParam, lParam);
    }
    return 0;
}



















BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static DATOS *Datos;

    switch (msg)                  /* manipulador del mensaje */
    {
        case WM_INITDIALOG:
           Datos = (DATOS*)lParam;
           SetScrollRange(GetDlgItem(hDlg, ID_SCROLLH), SB_CTL,
              0, 100, TRUE);
           SetScrollPos(GetDlgItem(hDlg, ID_SCROLLH), SB_CTL,
              Datos->ValorH, TRUE);
           SetDlgItemInt(hDlg, ID_EDITH, (UINT)Datos->ValorH, FALSE);
           SendDlgItemMessage(hDlg, ID_SCROLLV, SBM_SETRANGE,
              (WPARAM)0, (LPARAM)50);
           SendDlgItemMessage(hDlg, ID_SCROLLV, SBM_SETPOS,
              (WPARAM)Datos->ValorV, (LPARAM)TRUE);
           SetDlgItemInt(hDlg, ID_EDITV, (UINT)Datos->ValorV, FALSE);
           return FALSE;
        case WM_COMMAND:
           switch(LOWORD(wParam)) {
              case IDOK:
                 EndDialog(hDlg, FALSE);
                 return TRUE;
              case IDCANCEL:
                 EndDialog(hDlg, FALSE);
                 break;
           }
           return TRUE;

    }
    return FALSE;
}





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
    WindowClass.lpszMenuName  = "Menu";
    WindowClass.lpszClassName = "SFML App";
    RegisterClass(&WindowClass);

    // Let's create the main window
    //HWND Window = CreateWindow("SFML App", "SFML Win32", WS_SYSMENU | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, 0, 0, 800, 600, NULL, NULL, Instance, NULL);
    HWND Window = CreateWindow("SFML App", "SFML Win32", WS_SYSMENU | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 1680, 1050, NULL, NULL, Instance, NULL);

    // Let's create two SFML views
    HWND View1 = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0,  0, 64*2+22, 748, Window, NULL, Instance, NULL);
    HWND View2 = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 64*2+22+5, 0, (1024-(64*2+20+27)), (748-20-23), Window, NULL, Instance, NULL);
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
