//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "resource.h"
#include "backbuffer.h"

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

HMENU g_hMenu;

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
    switch (_uiMsg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);

        return(0);
		break;
    }
	case WM_LBUTTONDOWN:
	{
		CGame::GetInstance().m_bClickToHandle = true;
		return(0);
		break;
	}
	case WM_LBUTTONUP:
	{
		CGame::GetInstance().m_bClickReleaseToHandle = true;
		return(0);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(_wParam))
		{
		case ID_FILE_QUIT:
		{
			PostQuitMessage(0);
			break;
		}
		case ID_FILE_NEWGAME:
		{
			HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();
			HWND hWnd = CGame::GetInstance().GetWindow();
			int iWidth = (CGame::GetInstance().GetBackBuffer())->GetWidth();
			int iHeight = (CGame::GetInstance().GetBackBuffer())->GetHeight();

			CGame::DestroyInstance();
			CGame::GetInstance().Initialise(hInstance, hWnd, iWidth, iHeight);

			if (CGame::GetInstance().IsEasyMode())
			{
				CheckMenuItem(g_hMenu, ID_FILE_ENABLEEASYMODE, MF_CHECKED);
			}
			else
			{
				CheckMenuItem(g_hMenu, ID_FILE_ENABLEEASYMODE, MF_UNCHECKED);
			}
			break;
		}
		case ID_FILE_ENABLEEASYMODE:
		{
			CGame::GetInstance().ToggleEasyMode();

			if (CGame::GetInstance().IsEasyMode())
			{
				CheckMenuItem(g_hMenu, ID_FILE_ENABLEEASYMODE, MF_CHECKED);
			}
			else
			{
				CheckMenuItem(g_hMenu, ID_FILE_ENABLEEASYMODE, MF_UNCHECKED);
			}
			break;
		}
		default:
			break;
		}

		return(0);
		break;
	}

    default:
		break;
    } 

    return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND 
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
    WNDCLASSEX winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = WindowProc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = _hInstance;
    winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
    winclass.lpszMenuName = NULL;
    winclass.lpszClassName = WINDOW_CLASS_NAME;
    winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&winclass))
    {
        // Failed to register.
        return (0);
    }

	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

    HWND hwnd; 
    hwnd = CreateWindowEx(NULL,
                  WINDOW_CLASS_NAME,
                  _pcTitle,
                  WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 
                  CW_USEDEFAULT, CW_USEDEFAULT,
                  _iWidth, _iHeight,
                  NULL,
                  g_hMenu,
                  _hInstance,
                  NULL);
    
    if (!hwnd)
    {
        // Failed to create.
        return (0);
    }

    return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    const int kiWidth = 1300;
    const int kiHeight = 900;

    HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Solitaire");

    if (!CGame::GetInstance().Initialise(_hInstance, hwnd, kiWidth, kiHeight))
    {
        // Failed
        return (0);
    }

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			CGame::GetInstance().ExecuteOneFrame();

			// Check win condition
			if (CGame::GetInstance().CheckWinCondition())
			{
				MessageBoxA(hwnd, "You Won", "You Won", MB_OK);

				CGame::DestroyInstance();
				if (!CGame::GetInstance().Initialise(_hInstance, hwnd, kiWidth, kiHeight))
				{
					// Failed
					return (0);
				}
			}
        }
    }

    CGame::DestroyInstance();

    return (static_cast<int>(msg.wParam));
}
