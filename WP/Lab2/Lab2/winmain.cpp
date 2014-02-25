#pragma comment( lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <stdlib.h>

#define SCROLL_1 100

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
		}break;
		//end getminmaxinfo

		case WM_CREATE:
		{
			HINSTANCE hInst = (HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE);
			RECT rect;
			GetClientRect(hWnd, &rect);
			HWND hScroll =    CreateWindowEx(0L,
                       "SCROLLBAR",
                       NULL, // There is no text to display
                       WS_CHILD | WS_VISIBLE,
					   rect.right-40,
                       rect.top,
					   rect.right-20,
					   rect.bottom-20,
                       hWnd,
                       (HMENU)SCROLL_1,
                       hInst,
                       NULL);

			SetScrollRange(hScroll, SB_CTL , 0, 255, false);
			SetScrollPos(hScroll, SB_CTL , 0, FALSE);

		}
		break;
		//end wm_create

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
            {

			}break;
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
