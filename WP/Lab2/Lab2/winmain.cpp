#pragma comment( lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <stdlib.h>
#include <string>
#include "resources.h"

LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX winClass;

	ZeroMemory(&winClass,sizeof(WNDCLASSEX));
	winClass.cbClsExtra=NULL;
	winClass.cbSize=sizeof(WNDCLASSEX);
	winClass.cbWndExtra=NULL;
	winClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	winClass.hIcon=LoadIcon (NULL, IDI_APPLICATION);
	winClass.hIconSm=LoadIcon (NULL, IDI_APPLICATION);
	winClass.hInstance=hInstance;
	winClass.lpfnWndProc=(WNDPROC)WinProc;
	winClass.lpszClassName="Window Class";
	winClass.lpszMenuName=MAKEINTRESOURCE(Menu);
	winClass.style=CS_HREDRAW|CS_VREDRAW;

	if(!RegisterClassEx(&winClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"Window class creation failed",
			"Window Class Failed",
			MB_ICONERROR);
	}

	//receive screen dimensions
	int screenHeight = GetSystemMetrics(SM_CYSCREEN); 
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);

	HWND hWnd=CreateWindowEx(NULL,
			"Window Class",
			"Lab#2",
			WS_OVERLAPPEDWINDOW| 
			WS_HSCROLL | WS_VSCROLL,
			screenWidth/6,		//leftx
			screenHeight/7,		//lefty
			screenWidth - 2*screenWidth/6, //rightx
			screenHeight - 2*screenHeight/7, //righty
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
	static int  iColorID[5] = { 
		WHITE_BRUSH,  LTGRAY_BRUSH, GRAY_BRUSH,
		DKGRAY_BRUSH, BLACK_BRUSH 
	};
    static int  iSelection = IDM_WHITE ;
    static HMENU  hMenu;

	switch(msg)
	{

		//minmaxinfo - setting limits on window dimensions
		case WM_GETMINMAXINFO:
		{
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			MINMAXINFO* mmi = (MINMAXINFO*)lParam;
			mmi->ptMinTrackSize.x = 3*screenWidth/6;
			mmi->ptMinTrackSize.y = 3*screenHeight/7;
			mmi->ptMaxTrackSize.x = screenWidth - 2*screenWidth/6;
			mmi->ptMaxTrackSize.y = screenHeight - 2*screenHeight/7;
		}break;
		//end getminmaxinfo

		case WM_CREATE:
		{
			SetScrollRange(hWnd, SB_VERT, 0, 100, FALSE);
		}
		break;
		//end wm_create

		case WM_VSCROLL:
		{
			switch(LOWORD(wParam))
			{
			case SB_THUMBPOSITION:
				{
					SetScrollPos(hWnd, SB_VERT, 50, FALSE); 
				}break;
				
			}
		}break;
		//end wm_vscroll

		case WM_COMMAND:
		{
			hMenu = GetMenu (hWnd) ;

			switch (LOWORD (wParam))
				{
				case IDM_RESTART :
						MessageBeep (0) ;
						return 0 ;

				case IDM_EXIT :
						SendMessage (hWnd, WM_CLOSE, 0, 0L) ;
						return 0 ;

				case IDM_WHITE :          // Note: Logic below
				case IDM_LTGRAY :         //   assumes that IDM_WHITE
				case IDM_GRAY :           //   through IDM_BLACK are
				case IDM_DKGRAY :         //   consecutive numbers in
				case IDM_BLACK :          //   the order shown here.
						CheckMenuItem (hMenu, iSelection, MF_UNCHECKED) ;
						iSelection = LOWORD (wParam) ;
						CheckMenuItem (hMenu, iSelection, MF_CHECKED) ;
						SetClassLong (hWnd, GCL_HBRBACKGROUND,
							(LONG) GetStockObject 
								(iColorID[LOWORD (wParam) - IDM_WHITE])) ;

						InvalidateRect (hWnd, NULL, TRUE) ;
						return 0 ;

				case IDM_HELP :
						MessageBox (hWnd, "Help not yet implemented!",
							"Lab#2", MB_ICONEXCLAMATION | MB_OK) ;
						return 0 ;

				case IDM_ABOUT :
						MessageBox (hWnd, "Menu Demonstration Program.",
							"Lab#2", MB_ICONINFORMATION | MB_OK) ;
						return 0 ;
			}
			//end switch()
		}break;
		//end wm_command

		case WM_PAINT:
		{

		}break;

		//end wm_paint
		case WM_SIZE:
        {

        }break;
	
		case WM_DESTROY:
		{
			PostQuitMessage(0);		
			return 0;
		}
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
