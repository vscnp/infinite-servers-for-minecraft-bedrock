#include "framework.h"
#include "102+ servers.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#define MAX_LOADSTRING 100

// id
#define ID_SAVE 1001
#define ID_NAMEINPUT 1002
#define ID_ADDRESSINPUT 1003
#define ID_PORTINPUT 1004

HINSTANCE hInst;                        
WCHAR szTitle[MAX_LOADSTRING];         
WCHAR szWindowClass[MAX_LOADSTRING];   

HWND hTextBox1, hTextBox2, hTextBox3;
HWND hLabel1, hLabel2, hLabel3;
HWND hSaveButton;

HBRUSH hBackgroundBrush; 

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY102SERVERS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY102SERVERS));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY102SERVERS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    hBackgroundBrush = CreateSolidBrush(RGB(255, 255, 255));

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }

    hLabel1 = CreateWindowW(L"STATIC", L"Please enter server name:", WS_CHILD | WS_VISIBLE, 10, 10, 0, 20, hWnd, nullptr, hInstance, nullptr);
    hTextBox1 = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 30, 0, 25, hWnd, (HMENU)ID_NAMEINPUT, hInstance, nullptr);
    hLabel2 = CreateWindowW(L"STATIC", L"Please enter IP or Address:", WS_CHILD | WS_VISIBLE, 10, 65, 0, 20, hWnd, nullptr, hInstance, nullptr);
    hTextBox2 = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 85, 0, 25, hWnd, (HMENU)ID_ADDRESSINPUT, hInstance, nullptr);
    hLabel3 = CreateWindowW(L"STATIC", L"Please enter port:", WS_CHILD | WS_VISIBLE, 10, 120, 0, 20, hWnd, nullptr, hInstance, nullptr);
    hTextBox3 = CreateWindowW(L"EDIT", L"19132", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 140, 0, 25, hWnd, (HMENU)ID_PORTINPUT, hInstance, nullptr);

    hSaveButton = CreateWindowW(L"BUTTON", L"Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 200, 100, 25, hWnd, (HMENU)ID_SAVE, hInstance, nullptr);

    HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MS Gothic");
    SendMessage(hLabel1, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hTextBox1, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hLabel2, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hTextBox2, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hLabel3, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hTextBox3, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hSaveButton, WM_SETFONT, (WPARAM)hFont, TRUE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetBkColor(hdcStatic, RGB(255, 255, 255)); 
        SetTextColor(hdcStatic, RGB(0, 0, 0));      

        return (INT_PTR)hBackgroundBrush;
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        switch (wmId) {
        case ID_SAVE:
            if (wmEvent == BN_CLICKED) {
                AddServers::SaveButtonClicked(hWnd);
            }
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);

        int width = rect.right - 20;

        SetWindowPos(hLabel1, nullptr, 10, 10, width, 20, SWP_NOZORDER);
        SetWindowPos(hTextBox1, nullptr, 10, 30, width, 25, SWP_NOZORDER);

        SetWindowPos(hLabel2, nullptr, 10, 75, width, 20, SWP_NOZORDER);
        SetWindowPos(hTextBox2, nullptr, 10, 95, width, 25, SWP_NOZORDER);

        SetWindowPos(hLabel3, nullptr, 10, 140, width, 20, SWP_NOZORDER);
        SetWindowPos(hTextBox3, nullptr, 10, 160, width, 25, SWP_NOZORDER);

        SetWindowPos(hSaveButton, nullptr, 10, 200, 100, 25, SWP_NOZORDER);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

bool AddServers::AddServerToList(const std::wstring& path, HWND hWnd) {
    WCHAR serverName[256];
    WCHAR serverAddress[256];
    WCHAR portText[256];
    GetWindowText(hTextBox1, serverName, sizeof(serverName) / sizeof(serverName[0]));
    GetWindowText(hTextBox2, serverAddress, sizeof(serverAddress) / sizeof(serverAddress[0]));
    GetWindowText(hTextBox3, portText, sizeof(portText) / sizeof(portText[0]));  

    std::wofstream outputFile(path, std::ios::app);
    if (outputFile.is_open()) {
        std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
        outputFile.imbue(utf8_locale);
        if (!AddServers::IsEmpty(serverName) && !AddServers::IsEmpty(serverAddress) && !AddServers::IsEmpty(portText)) {
            outputFile << L"\n" << GetNumberOfServers(path) + 1 << L":" << serverName << L":" << serverAddress << L":" << portText << L":0";
            outputFile.close();
            std::wcout << L"Server added successfully." << std::endl;

            SetWindowText(hTextBox1, L"");
            SetWindowText(hTextBox2, L"");
            SetWindowText(hTextBox3, L"19132");
        } else {
            MessageBox(hWnd, L"Unable to add server.\n Please enter server name, address and port.", L"Info", MB_OK | MB_ICONINFORMATION);
            return false;
        }
    } else {
        std::wcerr << L"Failed to open the external_servers.txt file for writing." << std::endl;
        return false;
    }
    
    return true;
}

int AddServers::GetNumberOfServers(const std::wstring& path) {
    std::wifstream inputFile(path);
    if (inputFile.is_open()) {
        std::wstring line;
        int count = 0;
 
        while (std::getline(inputFile, line)) {
            if (!line.empty()) {
                count++;
            }
        }

        inputFile.close();
        return count;
    } else {
        std::wcerr << L"Failed to open the external_servers.txt file for reading." << std::endl;
        return -1;
    }
}

void AddServers::SaveButtonClicked(HWND hWnd) {
    const std::wstring& filePath = L"%localappdata%\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\LocalState\\games\\com.mojang\\minecraftpe\\external_servers.txt";
    WCHAR expandedPath[MAX_PATH];
    if (ExpandEnvironmentStrings(filePath.c_str(), expandedPath, MAX_PATH) == 0)
    {
        std::wcerr << L"Failed to expand environment variables in the file path. Error Code: " << GetLastError() << std::endl;
        return;
    }
    if (AddServers::AddServerToList(expandedPath, hWnd)) {
        MessageBox(hWnd, L"Added server to list!\nPlease restart Minecraft.", L"Info", MB_OK | MB_ICONINFORMATION);
    }
}