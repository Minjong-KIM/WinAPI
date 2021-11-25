#include <Windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {
    WNDCLASSEXA win = { 0 };
    win.cbSize = sizeof(win);// COUNT OF BYTE.
    win.style = CS_HREDRAW | CS_VREDRAW;// Defines the style of the window.
    win.hInstance = hinstance;// Number of programs using this window class.
    win.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// Set the background color of the window.
    win.hCursor = LoadCursor(NULL, IDC_ARROW);// Set the shape of the mouse cursor.
    win.hIcon = LoadIcon(NULL, IDI_APPLICATION);// icon when minimized.
    win.lpszClassName = "my window";// Defines the name of the window class.
    win.lpszMenuName = NULL;// Set the menu to be used by this program.
    win.lpfnWndProc = WndProc;//Specifies the window's message handling function. The name is mostly set to "WndProc".

    RegisterClassExA(&win);// This is the registration process to use Windows

    HWND hwnd;
    hwnd = CreateWindow(
        L"my window",//lpszClassName.
        L"First",
        WS_OVERLAPPEDWINDOW,//Style.
        CW_USEDEFAULT,//Coordinate x.
        CW_USEDEFAULT,//Coordinate y.
        CW_USEDEFAULT,//Width.
        CW_USEDEFAULT,//Height.
        0, 0, hinstance, 0
    );

    //The window created by the CreateWindow function only exists in memory,and has not yet been displayed on the screen.
    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);// Processing keyboard input messages
        DispatchMessageA(&msg);// Pass the message to the message handling function (WndProc)
    }// This process is repeated until the WM_QUIT message is delivered, that is, until the program ends.

    return msg.wParam;// This value is the exit code delivered from the WM_QUIT message.
}
//define Wndclass -> CreateWindow -> ShowWindow -> Message loop

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);//Send a WM_QUIT message by calling the PostQuitMessage function.
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}