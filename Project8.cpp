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
        L"KeyDown",
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
    static int x = 100;
    static int y = 100;

    switch (msg)
    {
    case WM_KEYDOWN:
        switch (wparam) {
        case VK_LEFT:
            x -= 8;
            break;
        case VK_RIGHT:
            x += 8;
            break;
        case VK_UP:
            y -= 8;
            break;
        case VK_DOWN:
            y += 8;
            break;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, x, y, L"A", 1);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}