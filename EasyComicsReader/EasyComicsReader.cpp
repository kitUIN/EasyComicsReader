// EasyComicsReader.cpp : 定义应用程序的入口点。
//


#include "EasyComicsReader.h"

#include "UIView.h"


using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::Foundation::Numerics;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

HWND c_hWnd;
HWND c_childhWnd;
HINSTANCE c_hInstance;
UIView c_uiView;

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    c_hInstance = hInstance;
    // The main window class name.
    const wchar_t szWindowClass[] = L"Win32DesktopApp";
    WNDCLASSEX windowClass = { };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hIcon = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_EASYCOMICSREADER));
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = szWindowClass;
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

    if (RegisterClassEx(&windowClass) == NULL)
    {
        MessageBox(NULL, L"Windows registration failed!", L"Error", NULL);
        return 0;
    }

    c_hWnd = CreateWindow(
        szWindowClass,
        L"EasyComicsReader",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (c_hWnd == NULL)
    {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Error", NULL);
        return 0;
    }


    // Begin XAML Island section.
    winrt::init_apartment(apartment_type::single_threaded);
    WindowsXamlManager winxamlmanager = WindowsXamlManager::InitializeForCurrentThread();
    DesktopWindowXamlSource desktopSource;
    auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
    check_hresult(interop->AttachToWindow(c_hWnd));
    HWND hWndXamlIsland = nullptr;
    interop->get_WindowHandle(&hWndXamlIsland);
    SetWindowPos(hWndXamlIsland, 0, 0, 0, 1200, 600, SWP_SHOWWINDOW);

    // Create the XAML content.

    c_uiView.ComicsListInit();
    desktopSource.Content(c_uiView.m_mainStackPanel);

    // End XAML Island section.

    ShowWindow(c_hWnd, nCmdShow);
    UpdateWindow(c_hWnd);

    //Message loop:
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT messageCode, WPARAM wParam, LPARAM lParam)
{

    RECT rcClient;

    switch (messageCode)
    {
    case WM_PAINT:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        //m_buttonClickRevoker.revoke();

        break;

        // Create main window
    case WM_CREATE:
        c_childhWnd = CreateWindowEx(0, L"ChildWClass", NULL, WS_CHILD | WS_BORDER, 0, 0, 0, 0, hWnd, NULL, c_hInstance, NULL);

        return 0;

        // Main window changed size
    case WM_SIZE:
        // Get the dimensions of the main window's client
        // area, and enumerate the child windows. Pass the
        // dimensions to the child windows during enumeration.
        GetClientRect(hWnd, &rcClient);
        MoveWindow(c_childhWnd, 200, 200, 400, 500, TRUE);
        ShowWindow(c_childhWnd, SW_SHOW);

        return 0;

        // Process other messages.

    default:
        return DefWindowProc(hWnd, messageCode, wParam, lParam);
        break;
    }

    return 0;
}