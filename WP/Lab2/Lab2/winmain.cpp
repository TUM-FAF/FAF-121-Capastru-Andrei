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
	winClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	winClass.hIcon=LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON));//icon
	winClass.hIconSm=LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON));//icon
	winClass.hInstance=hInstance;
	winClass.lpfnWndProc=(WNDPROC)WinProc;
	winClass.lpszClassName="Window Class";
	winClass.lpszMenuName=MAKEINTRESOURCE(Menu); //using menu form rc file
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
	
	RegisterHotKey(hWnd, IDH_BGCHANGER, MOD_CONTROL, VK_SPACE);
	RegisterHotKey(hWnd, IDH_EXITHOTKEY, MOD_CONTROL, 0x4D);
	
	
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
	static HINSTANCE hinst;
	static int  iColorID[5] = { 
		WHITE_BRUSH,  LTGRAY_BRUSH, GRAY_BRUSH,
		DKGRAY_BRUSH, BLACK_BRUSH };
    static int  iSelection = IDM_WHITE ;
    static HMENU  hMenu;
	static HWND hEdit;

	static int scrollVar=0;
	static int prevX = 0;
	static int prevY= 0;
	static int addX=0; // 0 is initial
	static int addY=0; // 0 is initial

	SCROLLINFO si;
	static int scrollY = 0, scrollX = 0;
	addX = -scrollX;
	addY = -scrollY;

	static int text;

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
			hinst = ((LPCREATESTRUCT)lParam)->hInstance;
			CreateWindowEx(0L, "SCROLLBAR",
						   NULL, // There is no text to display
						   WS_CHILD | WS_VISIBLE,
						   50,
						   20,
						   420,
						   21,
						   hWnd,
						   (HMENU)IDC_SCROLLBOTTOM,
						   GetModuleHandle(NULL),
						   NULL);

			si.nMax = 255;
			si.nMin = 0;
			si.nPos = 0;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_POS ;
			SetScrollInfo(GetDlgItem(hWnd, IDC_SCROLLBOTTOM), SB_CTL, &si, TRUE);
	
			//CreateWindowEx(0L, "SCROLLBAR",
			//			   NULL, // There is no text to display
			//			   WS_CHILD | WS_VISIBLE,
			//			   50,
			//			   20,
			//			   420,
			//			   21,
			//			   hWnd,
			//			   (HMENU)IDC_SCROLLTOP,
			//			   GetModuleHandle(NULL),
			//			   NULL);
			si.nMax = 255;
			si.nMin = 0;
			si.nPos = 0;
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_POS ;
			SetScrollInfo(GetDlgItem(hWnd, IDC_SCROLLTOP), SB_CTL, &si, TRUE);

			CreateWindowEx(WS_EX_CLIENTEDGE,
				"LISTBOX",
				NULL,
				WS_CHILD | WS_VISIBLE| LBS_NOTIFY|
				LBS_NOINTEGRALHEIGHT | LBS_DISABLENOSCROLL, 
				50,
				100,
				200,
				100,
				hWnd,
				(HMENU)IDC_LISTBOX,
				GetModuleHandle(NULL),
				NULL);
			SendMessage(GetDlgItem(hWnd, IDC_LISTBOX), LB_ADDSTRING,TRUE, (LPARAM)"GRAY");
			SendMessage(GetDlgItem(hWnd, IDC_LISTBOX), LB_ADDSTRING,TRUE, (LPARAM)"White");
			SendMessage(GetDlgItem(hWnd, IDC_LISTBOX), LB_ADDSTRING,TRUE, (LPARAM)"BLACK");


			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				WS_EX_CLIENTEDGE|ES_MULTILINE| WS_VSCROLL,
				50,
				100,
				200,
				100,
				hWnd,
				(HMENU)IDC_EDIT,
				GetModuleHandle(NULL),
				NULL);

			HGDIOBJ hfDefault=GetStockObject(2);
			SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			SendMessage(hEdit,
				WM_SETTEXT,
				NULL,
				(LPARAM)"Insert text here...");

		}break;
		//end wm_create

		case WM_VSCROLL:
        if (!lParam) 
        {
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;

            GetScrollInfo(hWnd, SB_VERT, &si);

            int tempScrollY = si.nPos;
            int maxLimit = si.nMax - si.nPage + 1;

            switch (LOWORD(wParam))
            {
            case SB_LEFT:
                tempScrollY = 0;
                break;

            case SB_RIGHT:
                tempScrollY = maxLimit;
                break;

            case SB_LINELEFT:                       
                tempScrollY = max(0, si.nPos-5);
                break;

            case SB_PAGELEFT:
                {
                    RECT rct;
                    GetClientRect(hWnd, &rct);
                    tempScrollY = max(0, si.nPos - (rct.bottom -rct.top));
                }               
                break;

            case SB_LINERIGHT:
                tempScrollY = min(maxLimit, si.nPos+5);
                break;                  

            case SB_PAGERIGHT:
                {
                    RECT rct;
                    GetClientRect(hWnd, &rct);
                    tempScrollY = min(maxLimit, si.nPos + (rct.bottom -rct.top));
                }               
                break;

            case SB_THUMBTRACK:
            case SB_THUMBPOSITION:
                {                   
                    tempScrollY = HIWORD(wParam);
                }
                break;

            default:
                break;
            }

            ScrollWindow(hWnd, 0, scrollY - tempScrollY, NULL, NULL);
            scrollY = tempScrollY;
            si.nPos = scrollY;
            SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
        }break;
		//end wm_vscroll

		case WM_HSCROLL:
		{
			if (!lParam)
				{
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;

				GetScrollInfo(hWnd, SB_HORZ, &si);

				int tempScrollX = si.nPos;
				int maxLimit = si.nMax - si.nPage + 1;

				switch (LOWORD(wParam))
				{
					case SB_LEFT:
						tempScrollX = 0;
						break;

					case SB_RIGHT:
						tempScrollX = maxLimit;
						break;

					case SB_LINELEFT:                       
						tempScrollX = max(0, si.nPos-5);
						break;

					case SB_PAGELEFT:
						{
							RECT rct;
							GetClientRect(hWnd, &rct);
							tempScrollX = max(0, si.nPos - (rct.right -rct.left));
						}               
						break;

					case SB_LINERIGHT:
						tempScrollX = min(maxLimit, si.nPos+5);
						break;                  

					case SB_PAGERIGHT:
						{
							RECT rct;
							GetClientRect(hWnd, &rct);
							tempScrollX = min(maxLimit, si.nPos + (rct.right - rct.left));
						}               
						break;

					case SB_THUMBTRACK:
					case SB_THUMBPOSITION:
						{                   
							tempScrollX = HIWORD(wParam);
						}
						break;

					default:
						break;
				}

				ScrollWindow(hWnd, scrollX - tempScrollX, 0, NULL, NULL);
				scrollX = tempScrollX;
				si.nPos = scrollX;
				SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			}
			else
			{
				int scrollId = GetDlgCtrlID((HWND)lParam);
				switch (scrollId)
				{
					
					case IDC_SCROLLBOTTOM:
					{
						si.cbSize = sizeof(SCROLLINFO);
						si.fMask = SIF_POS | SIF_RANGE;

						GetScrollInfo((HWND)lParam, SB_CTL, &si);

						switch (LOWORD(wParam))
						{
						case SB_LEFT:
							si.nPos = 0;
							scrollVar = -1;
							break;

						case SB_RIGHT:
							si.nPos =255;
							scrollVar = 1;
							break;

						case SB_LINELEFT:                       
							si.nPos =scrollVar= max(si.nMin, si.nPos-5);
							scrollVar=-1;
							break;

						case SB_PAGELEFT:
							{
								scrollVar=-1;
								si.nPos = 0;
							}break;

						case SB_LINERIGHT:
							si.nPos =min(si.nMax, si.nPos+5);
							scrollVar =1; 
							break;                  

						case SB_PAGERIGHT:
							{
								scrollVar = 1;
								si.nPos = 255;
							}break;

						case SB_THUMBTRACK:     
						case SB_THUMBPOSITION:
							si.nPos = (int)HIWORD(wParam);
							scrollVar = (int)HIWORD(wParam);
							break;
						default:
							break;

						}//end switch
						RECT rct;
						RECT rect;
						GetWindowRect(hWnd, &rect);
						rct.left = 0;
						rct.top = 0;
						rct.right = SendMessage(GetDlgItem(hWnd, IDC_SCROLLBOTTOM), SBM_GETPOS, 0, 0);
						rct.bottom = SendMessage(GetDlgItem(hWnd, IDC_SCROLLBOTTOM), SBM_GETPOS, 0, 0);
						AdjustWindowRect(&rct, WS_OVERLAPPEDWINDOW, TRUE);
						SetWindowPos(hWnd, HWND_TOP, 0, 0, 
							rect.right - rect.left - scrollVar/50, 
							rect.bottom - rect.top - scrollVar/50, 
							SWP_NOMOVE | SWP_NOREPOSITION);
						si.fMask = SIF_POS;
						InvalidateRect(hWnd, &rct, TRUE);
						SetScrollInfo((HWND)lParam, SB_CTL, &si, TRUE);
					}break;//end case IDC_SCOLLBOTTOM
					//case IDC_SCROLLTOP:
					//{
					//	si.cbSize = sizeof(SCROLLINFO);
					//	si.fMask = SIF_POS | SIF_RANGE;

					//	GetScrollInfo((HWND)lParam, SB_CTL, &si);

					//	switch (LOWORD(wParam))
					//	{
					//	case SB_LEFT:
					//		si.nPos = 0;
					//		break;

					//	case SB_RIGHT:
					//		si.nPos = 255;
					//		break;

					//	case SB_LINELEFT:                       
					//		si.nPos = max(si.nMin, si.nPos-5);
					//		break;

					//	case SB_PAGELEFT:
					//		si.nPos = max(si.nMin, si.nPos-20);
					//		break;

					//	case SB_LINERIGHT:
					//		si.nPos = min(si.nMax, si.nPos+5);
					//		break;                  

					//	case SB_PAGERIGHT:
					//		si.nPos = min(si.nMax, si.nPos+20);
					//		break;

					//	case SB_THUMBTRACK:     
					//	case SB_THUMBPOSITION:
					//		si.nPos = (int)HIWORD(wParam);
					//		break;
					//	default:
					//		break;
					//	}//end switch
					//	text = si.nPos;
					//	InvalidateRect(hEdit, NULL, NULL);
					//	si.fMask = SIF_POS;
					//	SetScrollInfo(GetDlgItem(hWnd, IDC_SCROLLTOP), SB_HORZ, &si, TRUE);
					//}break;//end case IDC_SCROLLTOP
				}//end switch
			} //end else*/
		}
		//end wm_hscroll

		case WM_HOTKEY:
			{
				switch(LOWORD(wParam))
				{
				case IDH_BGCHANGER:
					{
						SendMessage(hWnd, WM_COMMAND, (WPARAM)IDM_RANDOM, NULL);
					}break;
				case IDH_EXITHOTKEY:
					{
						SendMessage(hWnd, WM_DESTROY, NULL, NULL);
					}break;
				}
			}break;
		//end wm_hotkey

		case WM_COMMAND:
			{
				hMenu = GetMenu(hWnd) ;
				static int red, green, blue;
				red = rand()%255;
				blue = rand()%255;
				green = rand()%255;
				HBRUSH brush = CreateSolidBrush(RGB(red, green, blue));

				switch (LOWORD(wParam))
					{
					case IDM_RESTART:
						{
							red = green = blue = 255;
							brush = CreateSolidBrush(RGB(red, green, blue));
							CheckMenuItem (hMenu, iSelection, MF_UNCHECKED) ;
							iSelection = IDM_WHITE ;				// restarts BgColor menu to White
							CheckMenuItem (hMenu, iSelection, MF_CHECKED) ;
							SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, LONG(brush));
							InvalidateRect (hWnd, NULL, TRUE) ;
							MessageBeep (0) ;
							addX = addY = 0;
							SetScrollPos(hWnd, SB_VERT, 0, TRUE);
							SetScrollPos(hWnd, SB_HORZ, 0, TRUE);
							SetScrollPos(GetDlgItem(hWnd, IDC_SCROLLTOP), SBS_HORZ, 0, TRUE);
							SetScrollPos(hWnd,IDC_SCROLLBOTTOM, 0, TRUE);
							SendMessage(hEdit,
								WM_SETTEXT,
								NULL,
								(LPARAM)"Insert text here...");
							SendMessage(hWnd, WM_SIZE, 0L, 0L);
						}break;

					case IDM_EXIT:
						{
							SendMessage (hWnd, WM_CLOSE, 0, 0L) ;
							return 0 ;
						}
					case IDM_RANDOM:
						{
							CheckMenuItem (hMenu, iSelection, MF_UNCHECKED) ;
							iSelection = LOWORD (wParam) ;
							CheckMenuItem (hMenu, iSelection, MF_CHECKED) ;
							SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, LONG(brush));
							InvalidateRect (hWnd, NULL, TRUE) ;
							return 0 ;
						}break;
					case IDM_WHITE :          
					case IDM_LTGRAY :         
					case IDM_GRAY :           
					case IDM_DKGRAY :         
					case IDM_BLACK :
						{
							CheckMenuItem (hMenu, iSelection, MF_UNCHECKED) ;
							iSelection = LOWORD (wParam) ;
							CheckMenuItem (hMenu, iSelection, MF_CHECKED) ;
							SetClassLong (hWnd, GCL_HBRBACKGROUND,
								(LONG) GetStockObject 
									(iColorID[LOWORD (wParam) - IDM_WHITE])) ; //select color iColorID[index-1]  
							InvalidateRect (hWnd, NULL, TRUE) ;
						}break;	
					case IDM_HELP:
						{
							MessageBox (hWnd, "CTRL+SPACE - change background color\nCTRL+M - exit",
								"Lab#2", MB_ICONEXCLAMATION | MB_OK) ;
						}break;
					case IDM_ABOUT:
						{
							MessageBox (hWnd, "Developed by @andrewcap",
								"Lab#2", MB_ICONINFORMATION | MB_OK);
						}break;
					case IDC_LISTBOX:
						{
							switch(HIWORD(wParam))
							{
								case LBN_DBLCLK:
									int listElemId= SendMessage(GetDlgItem(hWnd, IDC_LISTBOX), LB_GETCURSEL, 0,0);
									{
										if( listElemId == 0 )
										{
											SendMessage(hWnd, WM_COMMAND, (WPARAM)IDM_GRAY, NULL); 
										}
										if( listElemId == 1 )
										{
											SendMessage(hWnd, WM_COMMAND, (WPARAM)IDM_WHITE, NULL); 
										}
										if( listElemId == 2 )
										{
											SendMessage(hWnd, WM_COMMAND, (WPARAM)IDM_BLACK, NULL); 
										}
									}break;
							}
						}break;
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
			RECT rcWind;
			GetWindowRect(hWnd, &rcWind);

			SetWindowPos(GetDlgItem(hWnd, IDC_EDIT), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 +20+addX,
				(rcWind.bottom-rcWind.top)/2-50+addY, 
				200, 
				100, 
				SWP_NOSIZE); // editbox position

			SetWindowPos(GetDlgItem(hWnd, IDC_LISTBOX), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 -200+addX,
				(rcWind.bottom-rcWind.top)/2-50+addY, 
				200, 
				100, 
				SWP_NOSIZE); //listbox position

			SetWindowPos(GetDlgItem(hWnd, IDC_SCROLLBOTTOM), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 -200+addX,
				(rcWind.bottom-rcWind.top)/2+70+addY, 
				200, 
				600, 
				SWP_NOSIZE); //mainscrollbar position

			SetWindowPos(GetDlgItem(hWnd, IDC_SCROLLTOP), 
				HWND_TOP, 
				(rcWind.right-rcWind.left)/2 -200+addX,
				(rcWind.bottom-rcWind.top)/2-90+addY, 
				200, 
				600, 
				SWP_NOSIZE); //scrollbar position
			
        }break;
		//end wm_size

		case WM_SETCURSOR:
		{
			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(LoadCursor(hinst, MAKEINTRESOURCE(IDC_CURSOR)));
				return TRUE;
			}
		}break;


		case WM_DESTROY:
		{
			UnregisterHotKey(hWnd, IDH_BGCHANGER);
			UnregisterHotKey(hWnd, IDH_EXITHOTKEY);
			PostQuitMessage(0);		
			return 0;
		}
		//end wm_destroy
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
