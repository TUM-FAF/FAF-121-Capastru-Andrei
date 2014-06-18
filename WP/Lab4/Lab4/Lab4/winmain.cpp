#include <windows.h>

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

int gameTop = 20;
int gameBot = 440;
int gameLeft = 20;
int gameRight = 620;
int x = 320;
int padLeft, padRight, ballLeft, ballRight, bX, bY;
bool gameOn = false;
int dir = 0;
int curPos = gameLeft+2;
int space = 5;
int blockW = 60;
int blockH = 15;
bool blockExists = true;
int level[40] = {0,1,1,1,1,1,1,1,0, 9,
               0,1,2,3,4,3,2,1,0, 9,
               0,1,1,1,1,1,1,1,0};
int originalLevel[40] = {0,1,1,1,1,1,1,1,0, 9,
                   0,1,2,3,4,3,2,1,0, 9,
                   0,1,1,1,1,1,1,1,0};

int levSize = sizeof(level)/sizeof(int);
int curY = 100;
bool blocksleft = false;
const int ID_TIMER = 1;

char szClassName[ ] = "Windows Application";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               
    MSG messages;            
    WNDCLASSEX winClass;        

   
    winClass.hInstance = hThisInstance;
    winClass.lpszClassName = szClassName;
    winClass.lpfnWndProc = WindowProcedure;     
    winClass.style = CS_DBLCLKS;                 
    winClass.cbSize = sizeof (WNDCLASSEX);
    winClass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    winClass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    winClass.hCursor = LoadCursor (NULL, IDC_ARROW);
    winClass.lpszMenuName = NULL;                 
    winClass.cbClsExtra = 0;                      
    winClass.cbWndExtra = 0;                      
    winClass.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&winClass))
        return 0;

    hwnd = CreateWindowEx (
           0,                   
           szClassName,         
           "Arkanoid",       
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT,       
           CW_USEDEFAULT,       
           640,                 
           480,                 
           HWND_DESKTOP,        
           NULL,                
           hThisInstance,       
           NULL                 
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}




LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int ret;
	HBRUSH blueBar, whiteBar, redBar, greenBar, blackBar;
    PAINTSTRUCT ps;
    RECT blocks[40];
    POINT point;
    switch (message)                  
    {
        case WM_DESTROY:
		{
            KillTimer(hwnd, ID_TIMER);
            PostQuitMessage (0);      
		}break;

        case WM_CREATE:
		{
            ret = SetTimer(hwnd, ID_TIMER, 10, NULL);
            if(ret==0)
            {
                MessageBox(hwnd, "Could not set Timer", "Error", MB_OK);
            }
		}break;
        
		case WM_TIMER:
		{
            InvalidateRect(hwnd, NULL, TRUE);
		}break;

        case WM_PAINT:
            HDC hdc;
            // Define Brushes
            redBar = CreateSolidBrush(RGB(255,0,0));
            greenBar = CreateSolidBrush(RGB(0,255,0));
            blueBar = CreateSolidBrush(RGB(0,0,255));
            whiteBar = CreateSolidBrush(RGB(255,255,255));
            blackBar = CreateSolidBrush(RGB(0,0,0));

            // Define Drawing Area
            hdc = BeginPaint(hwnd, &ps);
                // Write Text

            TextOut(hdc, 200, 1, "Welcome to Arkanoid!(press space to begin)", 42);
            SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
            Rectangle(hdc, gameLeft, gameTop, gameRight, gameBot);
            DeleteObject(GetStockObject(HOLLOW_BRUSH));

            // Create Paddle
            SelectObject(hdc, blueBar);
            padLeft = x - 60;
            padRight = x + 60;
            Rectangle(hdc, padLeft, gameBot-30, padRight, gameBot-20);
            DeleteObject(blueBar);

            // Create Blocks
            for(int i=0; i<levSize; i++)
            {
                // map level by numbers
                // 0=nothing
                // 1=one-hit block
                // 2=two-hitblock
                // 3=new row
                switch(level[i])
                {
                    case 0:
                        curPos += (blockW + space);
                        break;
                    case 1:
                        SetRect(&blocks[i], curPos, curY, curPos+blockW, curY+blockH);
                        FillRect(hdc, &blocks[i], greenBar);
                        curPos += (blockW + space);
                        break;
                    case 2:
                        SetRect(&blocks[i], curPos, curY, curPos+blockW, curY+blockH);
                        FillRect(hdc, &blocks[i], whiteBar);
                        curPos += (blockW + space);
                        break;
                    case 3:
                        SetRect(&blocks[i], curPos, curY, curPos+blockW, curY+blockH);
                        FillRect(hdc, &blocks[i], redBar);
                        curPos += (blockW + space);
                        break;
                    case 4:
                        SetRect(&blocks[i], curPos, curY, curPos+blockW, curY+blockH);
                        FillRect(hdc, &blocks[i], blackBar);
                        curPos += (blockW + space);
                        break;
                    case 9:
                        curY += (blockH + 30);
                        curPos = gameLeft+2;
                    default:
                        break;
                }
            }//endfor
            // Restore Variables
            curPos = gameLeft+2;
            curY = 100;

            // Create Ball
            SelectObject(hdc, redBar);
                if(!gameOn)
                {
                        ballLeft = x - 5;
                        ballRight = x + 5;
                        bX = ballLeft;
                        bY = gameBot-40;
                        // Find if all blocks are gone
                        if(!blocksleft)
                        {
                            for(int i=0;i<levSize;i++)
                            {
                                level[i] = originalLevel[i];
                            }
                        }
						Ellipse(hdc, ballLeft, gameBot-40, ballRight, gameBot-30);
                        KillTimer(hwnd, ID_TIMER);
                }
                else
                {
                    // update the ball direction
                    switch(dir)
                    {
                        case 0: //ur
                            bX += 3;
                            bY += -3;
                            break;
                        case 1: //ul
                            bX += -3;
                            bY += -3;
                            break;
                        case 2: //dr
                            bX += 3;
                            bY += 3;
                            break;
                        case 3: //dl
                            bX += -3;
                            bY += 3;
                            break;
                        default:
                            break;
                    }
                    // draw the ball
					Ellipse(hdc, bX, bY, bX+10, bY+10);
                    // end game when too low
                    if(bY+10>=gameBot)
                    {
                        dir = 0;
                        gameOn=false;
                    }
                    // collision detection
                    else
                    {
                        // left wall
                        if(bX<=gameLeft && dir==1){dir=0;} // ul->ur
                        if(bX<=gameLeft && dir==3){dir=2;} // dl->dr
                        // right wall
                        if(bX+10>=gameRight && dir==0){dir=1;} // ur->ul
                        if(bX+10>=gameRight && dir==2){dir=3;} // dr->dl
                        // top wall
                        if(bY<=gameTop && dir==0){dir=2;} // ur->dr
                        if(bY<=gameTop && dir==1){dir=3;} // ul->dl
                        //                                  paddle detection...
                        //     left         right          top           bottom       direction  change
                        if(bX+10>=padLeft && bX<=padRight && 
							bY+10>=gameBot-35 && bY+10<=gameBot-15 && 
							dir==2){dir=0;} // dr->ur

                        if(bX+10>=padLeft && bX<=padRight 
							&& bY+10>=gameBot-35 && bY+10<=gameBot-15 &&
							dir==3){dir=1;} // dl->ul

                        // block detection
                        point.x = bX;
                        point.y = bY;
                        // detect collision by block
                        for(int i=0; i<levSize; i++)
                        {
                            if(PtInRect(&blocks[i], point))
                            {
                                // empty block
                                SetRectEmpty(&blocks[i]);
                                // switch two hit block to one hit block
                                switch(level[i])
                                {
                                    case 1: 
										level[i] = 0;
										break;
                                    case 2: 
										level[i] = 1;
										break;
                                    case 3: 
										level[i] = 2;
										break;
                                    case 4: 
										level[i] = 3;
										break;
                                    default:
										break;
                                }
                                // change direction on contact
                                switch(dir)
                                {
                                    case 0:
										dir=2;
										break; // ur->dr
                                    
									case 1:
										dir=3;
										break; // ul->dl
                                    
									case 2:
										dir=0;
											break; // dr->ur
                                    
									case 3:
										dir=1;
										break; // dl->ul
                                    
									default:
										break;
                                }
                            }
                        }
                        // Check the blocks...
                        for(int i=0;i<levSize;i++)
                        {
                            if(level[i]!=0||level[i]!=9)
                            {
                                blocksleft=true;
                            }
                        }
                    }
                }
        DeleteObject(redBar);
        EndPaint(hwnd, &ps);
        ReleaseDC(hwnd, hdc);
        break;
		case WM_MOUSEWHEEL:
        {
			SendMessage(hwnd, WM_TIMER
        }
        case WM_KEYDOWN:
        {
            switch(wParam)
            {
                // key detection
                // -> Move Paddle RIGHT
                // <- Move Paddle LEFT
                // Spc START GAME
                case VK_RIGHT:
                    if(padRight<=gameRight){x += 15;}else{x = gameRight-41;}
                    break;
                case VK_LEFT:
                    if(padLeft>=gameLeft){x += -15;}else{x = gameLeft+41;}
                    break;
                case VK_SPACE:
                    gameOn = true;
                    blocksleft = false;
                    SetTimer(hwnd, ID_TIMER, 10, NULL);
                    break;
                default:
                    break;
            }
        }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}