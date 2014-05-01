#pragma comment( lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <stdlib.h>
#include <string>
//#include "resources.h"

LRESULT CALLBACK WinProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX winClass;

	ZeroMemory(&winClass,sizeof(WNDCLASSEX));
	winClass.cbClsExtra=NULL;
	winClass.cbSize=sizeof(WNDCLASSEX);
	winClass.cbWndExtra=NULL;
	winClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.hCursor = LoadCursor(hInstance, NULL);
	winClass.hIcon=LoadIcon (hInstance, NULL);//icon
	winClass.hIconSm=LoadIcon (hInstance, NULL);//icon
	winClass.hInstance=hInstance;
	winClass.lpfnWndProc=(WNDPROC)WinProc;
	winClass.lpszClassName="Window Class";
	//winClass.lpszMenuName=MAKEINTRESOURCE(Menu); //using menu form rc file
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
	
	//registering hotkey
	
	//RegisterHotKey(hWnd, IDH_BGCHANGER, MOD_CONTROL, VK_SPACE);
	//RegisterHotKey(hWnd, IDH_EXITHOTKEY, MOD_CONTROL, 0x4D);
	
	
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

		//minmaxinfo - setting limits on window dimensions
		case WM_GETMINMAXINFO:
		{
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			MINMAXINFO* mmi = (MINMAXINFO*)lParam;
			mmi->ptMinTrackSize.x = 3*screenWidth/6;
			mmi->ptMinTrackSize.y = 4*screenHeight/7;
			mmi->ptMaxTrackSize.x = screenWidth - 1*screenWidth/6;
			mmi->ptMaxTrackSize.y = screenHeight - 1*screenHeight/7;
		}break;
		//end getminmaxinfo
		

		case WM_CREATE:
		{
			
		}break;
		//end wm_create
		case WM_PAINT:
		{

		}break;
		//end wm_paint

		case WM_SIZE:
        {	
        }break;
		//end wm_size

		case WM_SETCURSOR:
		{

		}break;


		case WM_DESTROY:
		{
			//UnregisterHotKey(hWnd, IDH_BGCHANGER);
			//UnregisterHotKey(hWnd, IDH_EXITHOTKEY);
			PostQuitMessage(0);		
			return 0;
		}
		//end wm_destroy
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
