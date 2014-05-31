#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include <iostream>

using namespace std;

POINT pointPen;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
int GetWidth(HWND);                       
int GetEraserWidth(HWND);                 
COLORREF GetColor(HWND, HWND, HWND);       
COLORREF GetFillColor(HWND, HWND, HWND);  

char szClassName[] = "Lab3";
HINSTANCE hInstance;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{    
	HWND hwnd;
    MSG msg;            
    WNDCLASSEX winClass;

    winClass.hInstance		= hInst;
    winClass.lpszClassName	= szClassName;
    winClass.lpfnWndProc	= WinProc;      
    winClass.style			= CS_DBLCLKS;              
    winClass.cbSize			= sizeof(WNDCLASSEX);
    winClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
    winClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
    winClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
    winClass.lpszMenuName	= NULL;                        
    winClass.cbClsExtra		= 0;                             
    winClass.cbWndExtra		= 0;                             
    winClass.hbrBackground	= (HBRUSH)CreateSolidBrush(RGB(240, 240, 240));  

    if(!RegisterClassEx(&winClass))
	{
		int nResult=GetLastError();
		MessageBox(NULL,
			"Window class creation failed",
			"Window Class Failed",
			MB_ICONERROR);
		return 0;
	}

    hwnd = CreateWindowEx(
           0,                  
           szClassName,        
           "NotMSPaint",       
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT,       
           CW_USEDEFAULT,       
           650,                 
           550,                 
           HWND_DESKTOP,        
           NULL,       
           hInst,      
           NULL    
           );

    ShowWindow(hwnd, nShowCmd);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    return 0;
}

LRESULT CALLBACK WinProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hPen, hLine, hRect, hEllipse, hEraser, hWidth, hEraserWidth;
    static HWND hred, hgreen, hblue, hrgb, hbez, hcheck;
    static HWND hredFill, hgreenFill, hblueFill, hClear;
    int			width;
    int			mouseX, mouseY;

    static POINT line, lineStart;

    static BOOL	blStartEllipse;
    static RECT ellipse;

    static BOOL blStartRectangle;
    static RECT rct;

    static int   bezStatus = 0;
    static POINT bezPoints[4];
    static POINT bezPoint;

    static RECT gradient = {470, 450, 630, 480};
    static RECT area     = {40, 40, 450, 490};
    static RECT prevRect;

    static HDC	  hdcImage;
    static BITMAP bitRectBMP;
   
	
    static HBITMAP  hImage = NULL;
    static COLORREF curColor, fillColor;

    hImage = (HBITMAP)LoadImage(hInstance, "image.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hImage, sizeof(bitRectBMP), &bitRectBMP);

	HDC			hDC;
    PAINTSTRUCT	Ps;
	HBRUSH		NewBrush, brush1;
	HPEN		linePen, linePen2;		
    HDC			hdc = GetDC(hwnd);

    POINT Pt[4] = { {20,   12}, 
					{88,  246}, 
					{364, 192},
					{250,  48} };

	PolyBezierTo(hdc,Pt,4);
    
	switch (message)
    {
		 case WM_CREATE:
		 {
			hPen = CreateWindow( TEXT("Button"), TEXT("Pen"),
						WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
						20, 10,
						45, 20,
						hwnd,(HMENU)ID_PEN,
						NULL, NULL);

			hLine = CreateWindow( TEXT("Button"), TEXT("Line"),
						WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
						75, 10,
						50, 20,
						hwnd,(HMENU)ID_LINE,
						hInstance, NULL);

			hEllipse = CreateWindow( TEXT("Button"), TEXT("Ellipse"),
						WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
						135, 10,
						65, 20,
						hwnd,(HMENU)ID_ELIPSE,
						NULL, NULL);

			hRect = CreateWindow( TEXT("Button"), TEXT("Rectangle"),
						WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
						205, 10,
						85, 20,
						hwnd,(HMENU)ID_LINE,
						NULL, NULL);

			hbez = CreateWindow( TEXT("Button"), TEXT("Beizier"),
						WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
						290, 10,
						90, 20,
						hwnd,(HMENU)ID_LINE,
						NULL, NULL);

			hEraser = CreateWindow( TEXT("Button"), TEXT("Eraser"),
						WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
						370, 10,
						90, 20,
						hwnd,(HMENU)ID_LINE,
						NULL, NULL);


			CreateWindow(TEXT("BUTTON"), TEXT("Border style:"),
							WS_VISIBLE | WS_CHILD | BS_GROUPBOX ,
							470, 35,
							160, 100,
							hwnd, (HMENU)500,
							NULL, NULL);

			CreateWindow(TEXT("Static"), TEXT("Width:"),
							WS_VISIBLE | WS_CHILD,
							475, 60,
							45, 20,
							hwnd,(HMENU)550,
							NULL, NULL);

			hWidth = CreateWindow( TEXT("Edit"), TEXT("4"),
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						530, 55,
						30, 20,
						hwnd,(HMENU)ID_WIDTH,
						NULL, NULL);

			CreateWindow(TEXT("Static"), TEXT("Color:"),
							WS_VISIBLE | WS_CHILD,
							475, 110,
							45, 20,
							hwnd,(HMENU)550,
							NULL, NULL);

			hred = CreateWindow(TEXT("Edit"), TEXT("0"),
						WS_VISIBLE | WS_CHILD | WS_BORDER,
						530, 110,
						30, 20,
						hwnd,(HMENU)ID_R,
						NULL, NULL);

			hgreen = CreateWindow(TEXT("Edit"), TEXT("0"),
							WS_VISIBLE | WS_CHILD | WS_BORDER,
							560, 110,
							30, 20,
							hwnd,(HMENU)ID_G,
							NULL, NULL);

			hblue = CreateWindow(TEXT("Edit"), TEXT("0"),
							WS_VISIBLE | WS_CHILD | WS_BORDER,
							590, 110,
							30, 20,
							hwnd,(HMENU)ID_B,
							NULL, NULL);

			hrgb = CreateWindow (TEXT("STATIC"), TEXT("  R  |  G   |  B"),
							WS_VISIBLE | WS_CHILD,
							530, 90,
							90, 20,
							hwnd, (HMENU)ID_RGB,
							NULL, NULL);

			CreateWindow(TEXT("BUTTON"), TEXT("Filling style:"),
							WS_VISIBLE | WS_CHILD | BS_GROUPBOX ,
							470, 140,
							160, 100,
							hwnd, (HMENU)600,
							NULL, NULL);

			CreateWindow(TEXT("Static"), TEXT("Fill"),
							WS_VISIBLE | WS_CHILD,
							475, 165,
							45, 20,
							hwnd,(HMENU)550,
							NULL, NULL);

			hcheck = CreateWindow(TEXT("BUTTON"), TEXT(" "),
							WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
							530, 165,
							50, 20,
							hwnd,(HMENU)ID_FILL,
							NULL, NULL);

			CreateWindow(TEXT("Static"), TEXT("Color:"),
							WS_VISIBLE | WS_CHILD,
							475, 215,
							45, 20,
							hwnd,(HMENU)590,
							NULL, NULL);

			CreateWindow (TEXT("STATIC"), TEXT("  R  |  G   |  B"),
							WS_VISIBLE | WS_CHILD,
							530, 190,
							90, 20,
							hwnd, (HMENU)700,
							NULL, NULL);

			hredFill = CreateWindow(TEXT("Edit"), TEXT("255"),
							WS_VISIBLE | WS_CHILD | WS_BORDER,
							530, 215,
							30, 20,
							hwnd,(HMENU)ID_R1,
							NULL, NULL);

			hgreenFill = CreateWindow(TEXT("Edit"), TEXT("255"),
							WS_VISIBLE | WS_CHILD | WS_BORDER,
							560, 215,
							30, 20,
							hwnd,(HMENU)ID_G1,
							NULL, NULL);

			hblueFill = CreateWindow(TEXT("Edit"), TEXT("255"),
							WS_VISIBLE | WS_CHILD | WS_BORDER,
							590, 215,
							30, 20,
							hwnd,(HMENU)ID_B1,
							NULL, NULL);

			hClear = CreateWindow(TEXT("Button"), TEXT("Clear"),
							WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
							470, 250,
							160, 30,
							hwnd, (HMENU)ID_CLEAR,
							NULL, NULL);
		}break;

		case WM_COMMAND:
	    {
			 switch(LOWORD(wParam))
			 {
				case ID_CLEAR:
				{
					InvalidateRect(hwnd, &area, FALSE);
					InvalidateRect(hwnd, &area, TRUE);
				}break;
				
				default:
					return 0;
			}
		}break;

		case WM_MOUSEMOVE:
		{
			mouseX = GET_X_LPARAM(lParam);
			mouseY = GET_Y_LPARAM(lParam);

			if (mouseX > 40 && mouseX < 450 && mouseY > 40 && mouseY < 490 )  
			if(wParam & MK_LBUTTON)
			{
				if (Button_GetCheck(hPen) == BST_CHECKED)
				{
					width = GetWidth(hWidth);                       
					curColor = GetColor(hred, hgreen, hblue); 

					linePen = CreatePen(PS_SOLID, width, curColor);
					SelectObject(hdc, linePen);

					MoveToEx(hdc, mouseX, mouseY, NULL);
					LineTo(hdc, pointPen.x, pointPen.y);
					DeleteObject(linePen);

					pointPen.x = mouseX;
					pointPen.y = mouseY;
				}

				if (Button_GetCheck(hLine) == BST_CHECKED)
				{
					width = GetWidth(hWidth);
					curColor = GetColor(hred, hgreen, hblue);

					linePen = CreatePen(PS_SOLID, width, RGB(255, 255, 255));  
					SelectObject(hdc, linePen);
					MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
					LineTo(hdc, line.x, line.y);
					DeleteObject(linePen);

					linePen = CreatePen(PS_SOLID, width, curColor);            
					SelectObject(hdc, linePen);
					MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
					LineTo(hdc, mouseX, mouseY);
					DeleteObject(linePen);

					line.x = mouseX;
					line.y = mouseY;
				}

				if((wParam == MK_LBUTTON) && (Button_GetCheck(hEraser) == BST_CHECKED))
				{
					int eraser_width = GetEraserWidth(hEraserWidth);  

					rct.left = mouseX - (eraser_width / 2);
					rct.right = mouseX + (eraser_width / 2);
					rct.top = mouseY - (eraser_width / 2);
					rct.bottom = mouseY + (eraser_width / 2);
					InvalidateRect(hwnd, &rct, FALSE);
					SendMessage(hwnd, WM_PAINT, 0, 0);
				}
			}
		}break;
		  
		case WM_LBUTTONUP :
		{
			mouseX = GET_X_LPARAM(lParam);
				mouseY = GET_Y_LPARAM(lParam);

				if (mouseX > 30 && mouseX < 450 && mouseY > 30 && mouseY < 490 )
				{
				if (Button_GetCheck(hLine) == BST_CHECKED)
				{
					width = GetWidth(hWidth);
					curColor = GetColor(hred, hgreen, hblue);

					SelectObject(hdc, CreatePen(PS_SOLID, width, RGB(255, 255, 255)));
					MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
					LineTo(hdc, line.x, line.y);

					linePen = CreatePen(PS_SOLID, width, curColor);
					SelectObject(hdc, linePen);
					MoveToEx(hdc, lineStart.x, lineStart.y, NULL);
					LineTo(hdc, mouseX, mouseY);
					DeleteObject(linePen);

					line.x = mouseX;
					line.y = mouseY;
				}

				if(blStartEllipse)
				{
					width = GetWidth(hWidth);
					curColor = GetColor(hred, hgreen, hblue);

					linePen2 = CreatePen(PS_DASHDOTDOT, width, curColor);

					if (Button_GetCheck(hcheck) == BST_CHECKED)          // check if the user want to fill the figure
					{
						fillColor = GetFillColor(hredFill, hgreenFill, hblueFill);
						NewBrush   = CreateSolidBrush(fillColor);
					}
					else
					{
						NewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);       // if not, the brush is NULL
					}

					SelectObject(hdc, linePen2);
					SelectObject(hdc, NewBrush);

					Ellipse(hdc, ellipse.left, ellipse.top, mouseX, mouseY);
					DeleteObject(linePen2);
					DeleteObject(NewBrush);

					blStartEllipse = false;
				}

				if(blStartRectangle)
				{
					width = GetWidth(hWidth);
					curColor = GetColor(hred, hgreen, hblue);

					linePen2=CreatePen(PS_DASHDOTDOT, width, curColor);

					if (Button_GetCheck(hcheck) == BST_CHECKED)
					{
						fillColor = GetFillColor(hredFill, hgreenFill, hblueFill);
						NewBrush   = CreateSolidBrush(fillColor);
					}
					else
					{
						NewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					}

					SelectObject(hdc, linePen2);
					SelectObject(hdc, NewBrush);
					Rectangle(hdc, rct.left, rct.top, mouseX, mouseY);

					DeleteObject(linePen2);
					DeleteObject(NewBrush);

					blStartRectangle = false;
				}

				if(bezStatus == 1)             // bazier check point
				{
					bezPoint.x = mouseX;
					bezPoint.y = mouseY;
					bezPoints[1] = bezPoint;
					bezStatus = 2;
				}

				if(bezStatus == 3)
				{
					
					bezPoint.x = mouseX;
					bezPoint.y = mouseY;
					bezPoints[3] = bezPoint;
					bezStatus = 0;
					SelectObject(hdc, linePen2);
					PolyBezier(hdc, bezPoints, 4);
					DeleteObject(linePen2);
				}
			}
		}break;

		case WM_LBUTTONDOWN:
		{
			mouseX = GET_X_LPARAM(lParam);
			mouseY = GET_Y_LPARAM(lParam);

			if (mouseX > 30 && mouseX < 450 && mouseY > 30 && mouseY < 490 )
			{
				if(wParam == MK_LBUTTON)
				{
					if (Button_GetCheck(hPen) == BST_CHECKED)
					{
						pointPen.x = mouseX;
						pointPen.y = mouseY;
					}

					if (Button_GetCheck(hLine) == BST_CHECKED)
					{
						lineStart.x = mouseX;
						lineStart.y = mouseY;
						line.x = mouseX;
						line.y = mouseY;
					}

					if((wParam == MK_LBUTTON) && (Button_GetCheck(hEllipse) == BST_CHECKED))
					{
						ellipse.left = mouseX;
						ellipse.top = mouseY;
						blStartEllipse = true;
					}

					if((wParam == MK_LBUTTON) && (Button_GetCheck(hRect) == BST_CHECKED))
					{
						rct.left = mouseX;
						rct.top = mouseY;
						blStartRectangle = true;
					}

					if((wParam == MK_LBUTTON) && (Button_GetCheck(hbez) == BST_CHECKED))
					{
						if(bezStatus == 0)
						{
							bezPoint.x = mouseX;
							bezPoint.y = mouseY;
							bezPoints[0] = bezPoint;
							bezStatus = 1;
						}
						else
						{
							bezPoint.x = mouseX;
							bezPoint.y = mouseY;
							bezPoints[2] = bezPoint;
							bezStatus = 3;
						}
					}
				}
			}
		}break;

		case WM_PAINT:
		{
			hDC = BeginPaint(hwnd, &Ps);

			brush1 = CreateSolidBrush(RGB(255, 255, 255));    

			FillRect(hdc, &area, brush1);
			DeleteObject(brush1);

			HBRUSH hBrush;

			prevRect.top = gradient.top;
			prevRect.bottom = gradient.bottom;
			
			hdcImage = CreateCompatibleDC(hdc);
			SelectObject(hdcImage, hRect);
			BitBlt(hdc, 470, 300, bitRectBMP.bmWidth, bitRectBMP.bmHeight, hdcImage, 0, 0, SRCCOPY);
			DeleteDC(hdcImage);


			for(int i = 0; i < (gradient.right - gradient.left); i++)
			{
				int red;
				red = i * 255 / (gradient.right - gradient.left);
				prevRect.left  = gradient.left  + i;
				prevRect.right = gradient.left + i + 1;
				hBrush = CreateSolidBrush(RGB(red, 0, (red-121)>0? red-121:red ));
				FillRect(hdc, &prevRect, hBrush);
				DeleteObject(hBrush);
			}
			EndPaint(hwnd, &Ps);
		break;
		}
			case WM_DESTROY:
			{
				PostQuitMessage(0);		
				return 0;
			};
			default:                     
			return DefWindowProc(hwnd, message, wParam, lParam);
		}

    return 0;
}

int GetWidth(HWND input)
{
    static int result;
    static int iLength = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input, WM_GETTEXT, iLength+1, (LPARAM)szText);
    result = atoi(szText);
    _itoa(result, szText, 10);
    SendMessage(input, WM_SETTEXT, 0, (LPARAM)szText);
    free(szText);
    return result;
}

int GetEraserWidth(HWND input)
{
    static int result;
    static int iLength = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input, WM_GETTEXT, iLength+1, (LPARAM)szText);
    result = atoi(szText);
    free(szText);
    return result;
}

COLORREF GetColor(HWND input1, HWND input2, HWND input3)
{
    static COLORREF color;
    static int r, g, b;

    int iLength = SendMessage(input1, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input1, WM_GETTEXT, iLength+1, (LPARAM)szText);
    r = atoi(szText);

    iLength = SendMessage(input2, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input2, WM_GETTEXT, iLength+1, (LPARAM)szText);
    g = atoi(szText);

    iLength = SendMessage(input3, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input3, WM_GETTEXT, iLength+1, (LPARAM)szText);
    b = atoi(szText);
    free(szText);

    color = RGB (r, g, b);

    return color;
}

COLORREF GetFillColor(HWND input1, HWND input2, HWND input3)
{
    static COLORREF color;
    static int r, g, b;

    int iLength = SendMessage(input1, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input1, WM_GETTEXT, iLength+1, (LPARAM)szText);
    r = atoi(szText);

    iLength = SendMessage(input2, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input2, WM_GETTEXT, iLength+1, (LPARAM)szText);
    g = atoi(szText);

    iLength = SendMessage(input3, WM_GETTEXTLENGTH, 0, 0);
    szText = (char*)malloc(iLength+1);
    SendMessage(input3, WM_GETTEXT, iLength+1, (LPARAM)szText);
    b = atoi(szText);
    free(szText);

    color = RGB (r, g, b);

    return color;
}

