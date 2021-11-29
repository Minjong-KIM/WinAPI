#include <Windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {
    WNDCLASSEXA win = { 0 };
    win.cbSize = sizeof(win);
    win.style = CS_HREDRAW | CS_VREDRAW;
    win.hInstance = hinstance;
    win.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    win.hCursor = LoadCursor(NULL, IDC_ARROW);
    win.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    win.lpszClassName = "my window";
    win.lpszMenuName = NULL;
    win.lpfnWndProc = WndProc;

    RegisterClassExA(&win);

    HWND hwnd;
    hwnd = CreateWindow(
        L"my window",
        L"Brush",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0, 0, hinstance, 0
    );


    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

    HDC hdc;
    PAINTSTRUCT ps;
    HPEN MyPen, OldPen;
    HBRUSH MyBrush, OldBrush;

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
        MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 255, 0));
        OldPen = (HPEN)SelectObject(hdc, MyPen);
        OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
        Rectangle(hdc, 50, 50, 300, 200);
        SelectObject(hdc, OldPen);
        SelectObject(hdc, OldBrush);
        DeleteObject(MyPen);
        DeleteObject(MyBrush);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}