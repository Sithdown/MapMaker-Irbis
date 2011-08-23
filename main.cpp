#define _WIN32_WINNT 0x0501

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>



/*
    define button id
*/
#define IDB_BUTTON1 1000


/*
    global variables
*/
HINSTANCE hInst = NULL;

HWND hParent = NULL;  // parent window handle
HWND hChild = NULL;  // child window handle

SCROLLINFO si = {0};  // scroll info structure

int iXCurrentScroll = 0;  // current horizontal scroll value
int iYCurrentScroll = 0;   // current vertical scroll value

bool blManualMove = false;  // manual move flag
bool blShutDown = false;  // program shut-down flag


/* declare functions */
void CreateChildWindow ();
void CreateControls ();
void ResizeScrollbars ();
void ScrollChild ();
void SetDefaultFont (HWND);
LRESULT CALLBACK WindowProcedureParent (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedureChild (HWND, UINT, WPARAM, LPARAM);


/*
    start of main program
*/
int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    //MSG messages = {0};  // message structure

    hInst = hThisInstance;

    // Define a class for our main window
    WNDCLASS WindowClass;
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = WindowProcedureParent;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = hThisInstance;
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    WindowClass.lpszMenuName  = "Menu";
    WindowClass.lpszClassName = "SFML App";


    // Register the window class, and if it fails quit the program
    if (!RegisterClass(&WindowClass))
    {
        MessageBox(NULL, "Could not register main window class", "Error", MB_OK | MB_ICONERROR);
        return GetLastError();
    }

    HWND hParent = CreateWindow("SFML App", "SFML Win32", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, HWND_DESKTOP, NULL, hInst, NULL);


    // if the main window couldn't be created, exit with error message
    if (hParent == NULL)
    {
        MessageBox(NULL, "Could not create Parent window", "Error", MB_OK | MB_ICONERROR);
        return GetLastError();
    }

    // Let's create two SFML views
    HWND View1 = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0,  0, 64*2+22, 748, hParent, NULL, hInst, NULL);
    HWND View2 = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 64*2+22+5, 0, (1024-(64*2+20+27)), (748-20-23), hParent, NULL, hInst, NULL);
    sf::RenderWindow SFMLView1(View1);
    sf::RenderWindow SFMLView2(View2);

    // Cargar imgs
    sf::Texture Image1, Image2;
    if (!Image1.LoadFromFile("images/sprites/image1.png") || !Image2.LoadFromFile("images/sprites/image2.png"))
        return EXIT_FAILURE;
    sf::Sprite Sprite1(Image1);
    sf::Sprite Sprite2(Image2);

    // create the child window
    CreateChildWindow();

    // create child buttons if the child
    // window was created successfully
    CreateControls();

    // show the main window, along with children
    ShowWindow(hParent, nCmdShow);
    ShowWindow(hChild, SW_SHOW);

    // set initial child window position
    iXCurrentScroll = -5;
    iYCurrentScroll = -5;

    // scroll child window to initial position
    ScrollChild();

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
}


/*
    create the child window that will be scrolled
*/
void CreateChildWindow ()
{
    WNDCLASS wincl;  // window class structure

    // child window structure
    wincl.lpszClassName = "WindowScrollChild";

    // this child window uses a different message loop
    // than the parent window
    wincl.lpfnWndProc = WindowProcedureChild;
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.hbrBackground = CreateSolidBrush(RGB(245,245,255));

    // Register the window class
    if (!RegisterClass(&wincl))
    {
        MessageBox(NULL, "Could not register child window class", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    // create child window
    hChild = CreateWindow (
                 "WindowScrollChild",  // child window class name
                 "Child window",        // window text
                 WS_OVERLAPPEDWINDOW | WS_CHILD,
                 0,         // window x position
                 0,         // window y position
                 400,       // window width
                 400,       // window height
                 hParent,   // parent
                 NULL,      // no menu/ID
                 hInst,     // instance handler
                 NULL       // no extra creation data
             );

    // if child window couldn't be created, display error
    if (hChild == NULL)
    {
        MessageBox(hParent, "Could not create Child window", "Error", MB_OK | MB_ICONEXCLAMATION);
    }
}


/*
    create three controls on child window
*/
void CreateControls ()
{
    // create static text
    HWND hStatic1 = CreateWindowEx (
                        0,               // no extended styles
                        "STATIC",        // control class name
                        "Static text control",    // text
                        WS_CHILD | WS_VISIBLE,  // styles
                        120,               // x position
                        100,             // y position
                        150,             // width
                        18,              // height
                        hChild,          // parent
                        NULL,            // no menu/ID
                        hInst,           // instance handler
                        NULL             // no extra creation data
                    );

    // if button can't be created, display error
    if (hStatic1 == NULL)
    {
        MessageBox(hParent, "Could not create static text control.", "Error", MB_OK | MB_ICONEXCLAMATION);
    }

    // make font nice
    SetDefaultFont(hStatic1);

    // create edit control
    HWND hEdit1 = CreateWindowEx (
                      0,                 // no extended styles
                      "EDIT",          // control class name
                      "Edit control",    // text
                      WS_CHILD | WS_VISIBLE,  // styles
                      120,               // x position
                      125,               // y position
                      150,               // width
                      18,                // height
                      hChild,            // parent
                      NULL,              // no menu/ID
                      hInst,             // instance handler
                      NULL               // no extra creation data
                  );
    // if button can't be created, display error
    if (hEdit1 == NULL)
    {
        MessageBox(hParent, "Could not create edit control.", "Error", MB_OK | MB_ICONEXCLAMATION);
    }

    // make font nice
    SetDefaultFont(hEdit1);

    // create button
    HWND hButton1 = CreateWindowEx (
                        0,              // no extended styles
                        "BUTTON",       // button control class name
                        "OK",  // button text
                        WS_CHILD | WS_VISIBLE | ES_LEFT,  // button styles
                        220,            // button x position
                        150,            // button y position
                        50,            // button width
                        28,             // button height
                        hChild,         // parent
                        (HMENU)IDB_BUTTON1,  // control ID
                        hInst,          // instance handler
                        NULL            // no extra creation data
                    );

    // if button can't be created, display error
    if (hButton1 == NULL)
    {
        MessageBox(hParent, "Could not create button control.", "Error", MB_OK | MB_ICONEXCLAMATION);
    }

    // make font nice
    SetDefaultFont(hButton1);
}


/*
    update scroll bar info
*/
void ResizeScrollbars ()
{
    int iXMinScroll = -5;
    int iYMinScroll = -5;

    int iXMaxScroll = 0;
    int iYMaxScroll = 0;

    int iXPageSize = 0;
    int iYPageSize = 0;

    int iXScrollPadding = 0;
    int iYScrollPadding = 0;

    int iChildWidth = 0;
    int iChildHeight = 0;

    RECT rParent = {0};
    RECT rChild = {0};
    POINT pChild = {0};

    // get parent's client rect
    GetClientRect(hParent, &rParent);

    // get child's window rect
    GetWindowRect(hChild, &rChild);

    // child width
    iChildWidth = (rChild.right - rChild.left);
    iChildHeight = (rChild.bottom - rChild.top);

    // scroll padding
    iXScrollPadding = 100;
    iYScrollPadding = 100;

    // page size
    iXPageSize = (rParent.right - rParent.left);
    iYPageSize = (rParent.bottom - rParent.top);

    // maximum scroll size
    iYMaxScroll = (iChildHeight + iYScrollPadding);
    iXMaxScroll = (iChildWidth + iXScrollPadding);

    // current child position
    pChild.x = rChild.left;
    pChild.y = rChild.top;
    ScreenToClient(hParent, &pChild);

    // set current scroll
    iXCurrentScroll = -pChild.x;
    iYCurrentScroll = -pChild.y;

    // zero-out si struct
    memset(&si, 0, sizeof(si));

    // set horizontal scrollbar info
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = iXMinScroll;
    si.nMax = iXMaxScroll;
    si.nPage = iXPageSize;
    si.nPos = iXCurrentScroll;

    SetScrollInfo(hParent, SB_HORZ, &si, true);

    // zero-out si struct
    memset(&si, 0, sizeof(si));

    // set vertical scrollbar info
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = iYMinScroll;
    si.nMax = iYMaxScroll;
    si.nPage = iYPageSize;
    si.nPos = iYCurrentScroll;

    SetScrollInfo(hParent, SB_VERT, &si, true);
}


/*
    scroll child window
*/
void ScrollChild()
{
    RECT rChild = {0};

    // make sure we don't go negative with our position
    if (iXCurrentScroll < -5) iXCurrentScroll = -5;
    if (iYCurrentScroll < -5) iYCurrentScroll = -5;

    // get child window rect
    GetWindowRect(hChild, &rChild);

    // scroll child window
    MoveWindow(hChild, -iXCurrentScroll, -iYCurrentScroll, rChild.right - rChild.left, rChild.bottom - rChild.top, true);
}


/*
    set control to default GUI font
*/
void SetDefaultFont (HWND hwnd)
{
    SendMessage(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
}


/*
    main window procedure called by DispatchMessage
*/
LRESULT CALLBACK WindowProcedureParent (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // process messages by ID
    switch (message)
    {
    // a window was resized
    case WM_SIZE:
    {
        ResizeScrollbars();
        return 0;
    }
    break;

    // user changed horizontal scrollbar position
    case WM_HSCROLL:
    {
        int iXNewPos = 0;  // new x scroll position value

        // figure out which method user used to change position
        switch (LOWORD(wParam))
        {
        // User clicked the scroll bar shaft left of the scroll box
        case SB_PAGEUP:
        {
            iXNewPos = iXCurrentScroll - 50;
        }
        break;

        // User clicked the scroll bar shaft right of the scroll box
        case SB_PAGEDOWN:
        {
            iXNewPos = iXCurrentScroll + 50;
        }
        break;

        // User clicked the left arrow
        case SB_LINEUP:
        {
            iXNewPos = iXCurrentScroll - 10;
        }
        break;

        // User clicked the right arrow
        case SB_LINEDOWN:
        {
            iXNewPos = iXCurrentScroll + 10;
        }
        break;

        // User dragged the scroll box
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
        {
            // zero-out si struct
            memset(&si, 0, sizeof(si));

            si.cbSize = sizeof(si);
            si.fMask = SIF_TRACKPOS;

            GetScrollInfo(hParent, SB_HORZ, &si);

            iXNewPos = si.nTrackPos;
        }
        break;

        default:
            iXNewPos = iXCurrentScroll;
        }

        // reset the current scroll position value
        iXCurrentScroll = iXNewPos;

        // scroll child window with new position
        ScrollChild();

        return 0;
    }
    break;

    // user changed vertical scrollbar position
    case WM_VSCROLL:
    {
        int iYNewPos = 0;    // new Y scroll position value

        // figure out which method user used to change position
        switch (LOWORD(wParam))
        {
        // User clicked the scroll bar shaft above the scroll box.
        case SB_PAGEUP:
        {
            iYNewPos = iYCurrentScroll - 50;
        }
        break;

        // User clicked the scroll bar shaft below the scroll box.
        case SB_PAGEDOWN:
        {
            iYNewPos = iYCurrentScroll + 50;
        }
        break;

        // User clicked the top arrow.
        case SB_LINEUP:
        {
            iYNewPos = iYCurrentScroll - 10;
        }
        break;

        // User clicked the bottom arrow.
        case SB_LINEDOWN:
        {
            iYNewPos = iYCurrentScroll + 10;
        }
        break;

        // User dragged the scroll box.
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
        {
            // zero-out si struct
            memset(&si, 0, sizeof(si));

            si.cbSize = sizeof(si);
            si.fMask = SIF_TRACKPOS;

            GetScrollInfo(hParent, SB_VERT, &si);

            iYNewPos = si.nTrackPos;
        }
        break;

        default:
            iYNewPos = iYCurrentScroll;
        }

        iYCurrentScroll = iYNewPos;

        // scroll child window with new position
        ScrollChild();

        return 0;
    }
    break;

    // user closed window
    case WM_DESTROY:
    {
        // set program shut-down flag
        blShutDown = true;

        // tell program to terminate
        PostQuitMessage(0);
    }
    break;

    default:
        // process messages we don't deal with
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}


/*
    child window procedure called by DispatchMessage
*/
LRESULT CALLBACK WindowProcedureChild (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // process messages by ID
    switch (message)
    {
    // set our manual move flag if user tries
    // to move the child window manually
    case WM_ENTERSIZEMOVE:
    {
        blManualMove = true;
        return 0;
    }
    break;

    // un-set our manual move flag when user
    // stops trying to move window manually
    case WM_EXITSIZEMOVE:
    {
        blManualMove = false;
        return 0;
    }
    break;

    // child window has been moved
    // programmatically or manually
    case WM_MOVE:
    {
        // if user is moving child window manually, this
        // will make it 'snap back' to where it belongs
        if (blManualMove)
        {
            ScrollChild();
            return 0;
        }

        // update our scrolling info
        ResizeScrollbars();
        return 0;
    }
    break;

    // child window has been sized
    // programmatically or manually
    case WM_SIZE:
    {
        // update our scrolling info
        ResizeScrollbars();
        return 0;
    }
    break;

    // beep if user clicks button
    case WM_COMMAND:
    {
        // if 'OK' button was pressed, beep
        if (LOWORD(wParam) == IDB_BUTTON1)
        {
            MessageBeep(0);

            return 0;
        }
    }
    break;

    // end example if child is closed
    case WM_DESTROY:
    {
        // if the program isn't shutting down and user
        // closes child window, display message
        if (blShutDown == false)
        {
            MessageBox(
                hParent,
                "The child window has been closed.\n\nThis example program will now end.",
                "Child window closed",
                MB_OK | MB_ICONEXCLAMATION
            );

            // tell program to terminate
            PostQuitMessage(0);

            return 0;
        }
    }
    break;

    default:
        // process messages we don't deal with
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
