// // #include <Windows.h>

// // // Declare the window procedure
// // LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
// // {
// //     switch (uMsg)
// //     {
// //         case WM_DESTROY:
// //             PostQuitMessage(0);
// //             return 0;
// //     }

// //     return DefWindowProc(hwnd, uMsg, wParam, lParam);
// // }

// // int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
// // {
// //     // Register the window class
// //     const wchar_t CLASS_NAME[] = L"My Window Class";

// //     WNDCLASS wc = {};
// //     wc.lpfnWndProc = WindowProc;
// //     wc.hInstance = hInstance;
// //     wc.lpszClassName = CLASS_NAME;

// //     RegisterClass(&wc);

// //     // Create the window
// //     HWND hwnd = CreateWindowEx(
// //         0,                       // Optional window styles
// //         CLASS_NAME,              // Window class name
// //         L"My Window",            // Window title
// //         WS_OVERLAPPEDWINDOW,     // Window style

// //         // Position and size
// //         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

// //         NULL,                    // Parent window
// //         NULL,                    // Menu
// //         hInstance,               // Instance handle
// //         NULL                     // Additional application data
// //     );

// //     if (hwnd == NULL)
// //         return 0;

// //     // Display the window
// //     ShowWindow(hwnd, nCmdShow);

// //     // Main message loop
// //     MSG msg = {};
// //     while (GetMessage(&msg, NULL, 0, 0))
// //     {
// //         TranslateMessage(&msg);
// //         DispatchMessage(&msg);
// //     }

// //     return msg.wParam;
// // }



// // // int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
// // // {
// // //     // Register the window class
// // //     const wchar_t CLASS_NAME[] = L"My Window Class";

// // //     WNDCLASS wc = {};
// // //     wc.lpfnWndProc = WindowProc;
// // //     wc.hInstance = hInstance;
// // //     wc.lpszClassName = CLASS_NAME;

// // //     RegisterClass(&wc);

// // //     // Create the window
// // //     HWND hwnd = CreateWindowEx(
// // //         0,
// // //         CLASS_NAME,
// // //         L"My Window",
// // //         WS_OVERLAPPEDWINDOW,
// // //         CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,  // Set window size

// // //         NULL,
// // //         NULL,
// // //         hInstance,
// // //         NULL
// // //     );

// // //     if (hwnd == NULL)
// // //         return 0;

// // //     // Display the window
// // //     ShowWindow(hwnd, nCmdShow);

// // //     // Main message loop
// // //     MSG msg = {};
// // //     while (GetMessage(&msg, NULL, 0, 0))
// // //     {
// // //         TranslateMessage(&msg);
// // //         DispatchMessage(&msg);
// // //     }

// // //     return msg.wParam;
// // // }



// // int main() {
// //     int a = WinMain();
// //     return 0;
// // }



// // #include <Windows.h>

// // LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
// // {
// //     switch (uMsg)
// //     {
// //         case WM_DESTROY:
// //             PostQuitMessage(0);
// //             return 0;
// //     }

// //     return DefWindowProc(hwnd, uMsg, wParam, lParam);
// // }

// // int main()
// // {
// //     // Get the handle to the current instance of the application
// //     HINSTANCE hInstance = GetModuleHandle(NULL);

// //     // Register the window class
// //     const wchar_t CLASS_NAME[] = L"My Window Class";

// //     WNDCLASS wc = {};
// //     wc.lpfnWndProc = WindowProc;
// //     wc.hInstance = hInstance;
// //     wc.lpszClassName = CLASS_NAME;

// //     RegisterClass(&wc);

// //     // Create the window
// //     HWND hwnd = CreateWindowEx(
// //         0,
// //         CLASS_NAME,
// //         L"My Window",
// //         WS_OVERLAPPEDWINDOW,
// //         CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,  // Set window size

// //         NULL,
// //         NULL,
// //         hInstance,
// //         NULL
// //     );

// //     if (hwnd == NULL)
// //         return 0;

// //     // Display the window
// //     ShowWindow(hwnd, SW_SHOWDEFAULT);

// //     // Main message loop
// //     MSG msg = {};
// //     while (GetMessage(&msg, NULL, 0, 0))
// //     {
// //         TranslateMessage(&msg);
// //         DispatchMessage(&msg);
// //     }

// //     return msg.wParam;
// // }


// // #include <Windows.h>

// // LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
// // {
// //     switch (uMsg)
// //     {
// //         case WM_DESTROY:
// //             PostQuitMessage(0);
// //             return 0;
// //     }

// //     return DefWindowProc(hwnd, uMsg, wParam, lParam);
// // }

// // int main()
// // {
// //     // Get the handle to the current instance of the application
// //     HINSTANCE hInstance = GetModuleHandle(NULL);

// //     // Register the window class
// //     const wchar_t* CLASS_NAME = L"My Window Class";

// //     WNDCLASS wc = {};
// //     wc.lpfnWndProc = WindowProc;
// //     wc.hInstance = hInstance;
// //     wc.lpszClassName = CLASS_NAME;

// //     RegisterClass(&wc);

// //     // Create the window
// //     HWND hwnd = CreateWindowEx(
// //         0,
// //         CLASS_NAME,
// //         L"My Window",
// //         WS_OVERLAPPEDWINDOW,
// //         CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,  // Set window size

// //         NULL,
// //         NULL,
// //         hInstance,
// //         NULL
// //     );

// //     if (hwnd == NULL)
// //         return 0;

// //     // Display the window
// //     ShowWindow(hwnd, SW_SHOWDEFAULT);

// //     // Main message loop
// //     MSG msg = {};
// //     while (GetMessage(&msg, NULL, 0, 0))
// //     {
// //         TranslateMessage(&msg);
// //         DispatchMessage(&msg);
// //     }

// //     return msg.wParam;
// // }





























// #include <Windows.h>

// LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
// {
//     switch (uMsg)
//     {
//         case WM_DESTROY:
//             PostQuitMessage(0);
//             return 0;
//     }

//     return DefWindowProcW(hwnd, uMsg, wParam, lParam);
// }

// int main()
// {
//     // Get the handle to the current instance of the application
//     HINSTANCE hInstance = GetModuleHandleW(NULL);

//     // Register the window class
//     const wchar_t* CLASS_NAME = L"My Window Class";

//     WNDCLASSW wc = {};
//     wc.lpfnWndProc = WindowProc;
//     wc.hInstance = hInstance;
//     wc.lpszClassName = CLASS_NAME;

//     RegisterClassW(&wc);

//     // Create the window
//     HWND hwnd = CreateWindowExW(
//         WS_EX_ACCEPTFILES,
//         // 0,
//         CLASS_NAME,
//         L"testing window",
//         WS_OVERLAPPEDWINDOW,
//         // WS_OVERLAPPED | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU,
//         CW_USEDEFAULT, CW_USEDEFAULT, 600, 800,  // Set window size

//         NULL,
//         NULL,
//         hInstance,
//         NULL
//     );

//     if (hwnd == NULL)
//         return 0;

//     // Disable window resizing
//     SetWindowLongPtrW(hwnd, GWL_STYLE, GetWindowLongPtrW(hwnd, GWL_STYLE) & ~WS_THICKFRAME);


//     // Display the window
//     ShowWindow(hwnd, SW_SHOWDEFAULT);

//     // Main message loop
//     MSG msg = {};
//     while (GetMessageW(&msg, NULL, 0, 0))
//     {
//         TranslateMessage(&msg);
//         DispatchMessageW(&msg);
//     }

//     return msg.wParam;
// }



























































