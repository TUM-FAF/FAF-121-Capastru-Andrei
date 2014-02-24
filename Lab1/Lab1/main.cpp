#pragma comment( lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <stdlib.h>


#define IDC_EDIT			101		// Edit box identifier
#define IDC_EDIT_CUSTOM		100		// 
#define IDC_CHANGE_BUTTON	102	    // ChangerIdentifier
#define IDC_EXIT_BUTTON		103		// Exit Button
    
LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX winClass;
	ZeroMemory(&winClass,sizeof(WNDCLASSEX));
	winClass.cbClsExtra=NULL;
	winClass.cbSize=sizeof(WNDCLASSEX);
	winClass.cbWndExtra=NULL;
	winClass.hbrBackground=(HBRUSH)COLOR_WINDOW;
	winClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	winClass.hIcon=NULL;
	winClass.hIconSm=NULL;
	winClass.hInstance=hInstance;
	winClass.lpfnWndProc=(WNDPROC)WinProc;
	winClass.lpszClassName="Window Class";
	winClass.lpszMenuName=NULL;
	winClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&winClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"Window class creation failed",
			"Window Class Failed",
			MB_ICONERROR);
	}

	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);


	
	HWND hWnd=CreateWindowEx(NULL,
			"Window Class",
			"Lab#1",
			WS_OVERLAPPEDWINDOW |WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
			screenWidth/6,
			screenHeight/7,
			screenWidth - 2*screenWidth/6,
			screenHeight - 2*screenHeight/7,
			NULL,
			NULL,
			hInstance,
			NULL);

	if(!hWnd)
	{
		int nResult=GetLastError();

		MessageBox(NULL,
			"Window creation failed",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(hWnd,nShowCmd);

	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HFONT hFont;
	static bool fontDeterminer;
	switch(msg)
	{
		case WM_GETMINMAXINFO:
		{
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			MINMAXINFO* mmi = (MINMAXINFO*)lParam;
			mmi->ptMinTrackSize.x = 3*screenWidth/6;
			mmi->ptMinTrackSize.y = 3*screenHeight/7;
			mmi->ptMaxTrackSize.x = screenWidth - 2*screenWidth/6;
			mmi->ptMaxTrackSize.y = screenHeight - 2*screenHeight/7;
		}
		break;
		//end getminmaxinfo

		case WM_CREATE:
		{
			CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL,
				50,
				100,
				200,
				100,
				hWnd,
				(HMENU)IDC_EDIT,
				GetModuleHandle(NULL),
				NULL);

			CreateWindowEx(NULL,
				"BUTTON",
				"EXIT",
				WS_TABSTOP|WS_VISIBLE|SS_CENTER |
				WS_CHILD|BS_DEFPUSHBUTTON,
				0, 0, 100, 24,
				hWnd,
				(HMENU)IDC_EXIT_BUTTON,
				GetModuleHandle(NULL),
				NULL);

			CreateWindowEx(NULL,
				"BUTTON",
				"ChangeEverything!",
				WS_TABSTOP|WS_VISIBLE|SS_CENTER |
				WS_CHILD|BS_DEFPUSHBUTTON,
				0, 0, 200, 100,
				hWnd,
				(HMENU)IDC_CHANGE_BUTTON,
				GetModuleHandle(NULL),
				NULL);

			hFont = CreateFont(20, 0, 10, 1, 0, FALSE, 0, 0, 0, 0, 2, 0, 0, "Calibri");
			SendMessage(GetDlgItem(hWnd, IDC_CHANGE_BUTTON), WM_SETFONT, (WPARAM)hFont, TRUE);
		}
		break;
		//end wm_create

	
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
            {
				case IDC_EXIT_BUTTON:
				{
					PostQuitMessage(0);
					return 0;
				}
				break;
				case IDC_CHANGE_BUTTON:
				{
					static int a,b,c;
					a=rand() % 255;
					b=rand() % 255;
					c=rand() % 255;
					RECT rect;
					GetClientRect(hWnd, &rect);
					HBRUSH brush = CreateSolidBrush(RGB(c, b, a));
					SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
					
					fontDeterminer=!fontDeterminer;
					hFont = CreateFont(20, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, (fontDeterminer ? "Calibri" : "Courier New"));
					SendMessage(GetDlgItem(hWnd, IDC_CHANGE_BUTTON), WM_SETFONT, (WPARAM)hFont, TRUE);

					hFont = CreateFont(19, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, (fontDeterminer ? "Courier New" : "Times New Roman"));
					SendMessage(GetDlgItem(hWnd, IDC_EDIT), WM_SETFONT, (WPARAM)hFont, TRUE);

					InvalidateRect(hWnd, &rect, TRUE);
				}
				break;
				
			default:
			break;
			}

		}
		break;
		//end wm_command
		case WM_SIZE:
        {
			RECT rcWind;
			GetWindowRect(hWnd, &rcWind);

			SetWindowPos(GetDlgItem(hWnd, IDC_EXIT_BUTTON), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 - 50,
				(rcWind.bottom-rcWind.top) - 100, 
				0, 
				0, 
				SWP_NOSIZE);
			
			SetWindowPos(GetDlgItem(hWnd, IDC_CHANGE_BUTTON), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 - 100,
				(rcWind.bottom-rcWind.top)/2 - (rcWind.bottom-rcWind.top)/3, 
				0, 
				0, 
				SWP_NOSIZE);

			SetWindowPos(GetDlgItem(hWnd, IDC_EDIT), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 - (rcWind.right-rcWind.left)/3,
				(rcWind.bottom-rcWind.top)/2, 
				200, 
				100, 
				SWP_NOSIZE);
			
        }
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
		
		default:
			break;
	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}