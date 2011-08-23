/*
#include <windows.h>

#include "IDS.h"

//  Declaración del procedimiento de ventana
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

// Declaraciones de tipos
typedef struct stDatos {
   char Texto[80];
} DATOS;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    HWND hwnd;               // Manipulador de ventana
    MSG mensaje;             // Mensajes recibidos por la aplicación
    WNDCLASSEX wincl;        // Estructura de datos para la clase de ventana

    // Estructura de la ventana
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = "NUESTRA_CLASE";
    wincl.lpfnWndProc = WindowProcedure;      // Esta función es invocada por Windows
    wincl.style = CS_DBLCLKS;                 // Captura los doble-clicks
    wincl.cbSize = sizeof (WNDCLASSEX);

    // Usar icono y puntero por defector
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = "Menu";
    wincl.cbClsExtra = 0;                      // Sin información adicional para la
    wincl.cbWndExtra = 0;                      // clase o la ventana
    // Usar el color de fondo por defecto para la ventana
    wincl.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);

    // Registrar la clase de ventana, si falla, salir del programa
    if(!RegisterClassEx(&wincl)) return 0;

    // La clase está registrada, crear la ventana
    hwnd = CreateWindowEx(
           0,                   // Posibilidades de variación
           "NUESTRA_CLASE",     // Nombre de la clase
           "Ejemplo 005",       // Texto del título
           WS_OVERLAPPEDWINDOW, // Tipo por defecto
           CW_USEDEFAULT,       // Windows decide la posición
           CW_USEDEFAULT,       // donde se coloca la ventana
           544,                 // Ancho
           375,                 // Alto en pixels
           HWND_DESKTOP,        // La ventana es hija del escritorio
           NULL,                // Sin menú
           hThisInstance,       // Manipulador de instancia
           NULL                 // No hay datos de creación de ventana
    );

    // Mostrar la ventana
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    // Bucle de mensajes, se ejecuta hasta que haya error o GetMessage devuelva FALSE
    while(TRUE == GetMessage(&mensaje, NULL, 0, 0))
    {
        // Traducir mensajes de teclas virtuales a mensajes de caracteres
        TranslateMessage(&mensaje);
        // Enviar mensaje al procedimiento de ventana
        DispatchMessage(&mensaje);
    }

    // Salir con valor de retorno
    return mensaje.wParam;
}

//  Esta función es invocada por la función DispatchMessage()
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;
    // Variables para diálogo
    static DATOS Datos;

    switch (msg)                  // manipulador del mensaje
    {
        case WM_CREATE:
           hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
           // Inicialización de los datos de la aplicación
           strcpy(Datos.Texto, "Inicial");
           return 0;
           break;
        case WM_COMMAND:
           if(LOWORD(wParam) == CM_DIALOGO)
              DialogBoxParam(hInstance, "DialogoPrueba", hwnd, DlgProc, (LPARAM)&Datos);
           break;
        case WM_DESTROY:
           PostQuitMessage(0);    // envía un mensaje WM_QUIT a la cola de mensajes
           break;
        default:                  // para los mensajes de los que no nos ocupamos
           return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static DATOS *Datos;

    switch (msg)                  // manipulador del mensaje
    {
        case WM_INITDIALOG:
           SendDlgItemMessage(hDlg, ID_TEXTO, EM_LIMITTEXT, 80, 0L);
           Datos = (DATOS *)lParam;
           SetDlgItemText(hDlg, ID_TEXTO, Datos->Texto);
           SetFocus(GetDlgItem(hDlg, ID_TEXTO));
           return FALSE;
        case WM_COMMAND:
           switch(LOWORD(wParam)) {
              case IDOK:
                 GetDlgItemText(hDlg, ID_TEXTO, Datos->Texto, 80);
                 EndDialog(hDlg, FALSE);
                 break;
              case IDCANCEL:
                 EndDialog(hDlg, FALSE);
                 break;
           }
           return TRUE;
    }
    return FALSE;
}

*/
