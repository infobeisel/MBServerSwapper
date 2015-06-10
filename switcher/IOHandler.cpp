#include "IOHandler.h"
#define _WIN32_WINNT 0x0500 // need this for having the INPUT-datastructure

#include "GameValueProvider.h"
#include <iostream>
#include <cmath>
#include <d3dx9.h>
#include <Commctrl.h>



#define MYMENU_EXIT         (WM_APP + 101)
#define MYMENU_MESSAGEBOX   (WM_APP + 102) 

#define HIDEBORDERX 0
#define HIDEBORDERY 0
#define HIDEBORDERXR 0
#define HIDEBORDERYB 0
typedef LRESULT(__stdcall *WITHWINDOW)(HWND window);

IOHandler* IOHandler::instance = 0;

IOHandler* IOHandler::get()
{
  if( instance == 0 )
    instance = new IOHandler();
  return instance;
}
IOHandler::~IOHandler()
{
    //dtor
}

DWORD WINAPI updateLoadingAnimation(LPVOID lpParam) {
	/*
	HWND window = GameValueProvider::get()->getGameMainWindow();
	HBITMAP loadingImage = (HBITMAP)LoadImage(NULL, L"loading_screen_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	RECT rect;
	GetWindowRect(
		window,
		&rect
		);
	std::cout << rect.right << "  " << rect.bottom;
	PAINTSTRUCT 	ps;
	HDC 			hdc;
	BITMAP 			bitmap;
	HDC 			hdcMem;
	HGDIOBJ 		oldBitmap;
	
		hdc = GetDC(window);

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, loadingImage);

		GetObject(loadingImage, sizeof(bitmap), &bitmap);
		DWORD res;
		while (true) {
			//RedrawWindow(window, 0, 0,	RDW_INTERNALPAINT	);
			//StretchBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			//SendMessageTimeout(window, WM_PAINT, 0, 0, SMTO_BLOCK, 30, &res);
			RedrawWindow(window, 0, 0,
				RDW_ERASE | RDW_INVALIDATE
				);

		
		}

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		ReleaseDC(window, hdc);*/
	return 1;
}

void IOHandler::startLoadingAnimation(HWND window) {
	/*hThreadArray[0] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		updateLoadingAnimation,       // thread function name
		0,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray[0]);   // returns the thread identifier 
	 */
	
	//DWORD procId;
	////GetWindowThreadProcessId(window, &procId);
//int res = myInjector.Inject(TEXT("E:\\CppProjects\\switcher\\switcher\\ConsoleApplication1.dll"), TEXT("mb_warband.exe"), procId);
//	SetForegroundWindow(
	//	window
	//	);
	//std::cout << "dll injected " << res << "\n";
	RECT rect;
	GetWindowRect(window, &rect);
	SetWindowPos(animWindow, 0, -HIDEBORDERX, -HIDEBORDERY, rect.right + HIDEBORDERX, rect.bottom + HIDEBORDERY, SWP_NOACTIVATE);
	ShowWindow(animWindow, SW_SHOWNOACTIVATE);
	initAnimation(animWindow);
	ShowCursor(FALSE);
		

}

void IOHandler::stopLoadingAnimation(HWND window) {
	//TerminateThread(hThreadArray[0], 0);

	//BUGGY UGLY REMOVE!
	//HWND buggyHWND = FindWindowEx(window,NULL,NULL, L"Loading Screen");
	//DestroyWindow(window);
	//ShowWindow(buggyHWND, SW_HIDE);

	RECT rect;
	GetWindowRect(window, &rect);
	SetWindowPos(animWindow,NULL, -20, -40, 0, 0, SWP_NOACTIVATE);
	ShowWindow(animWindow, SW_SHOWNOACTIVATE);
	//initAnimation(animWindow);
	//ShowCursor(FALSE);


	//do it clean!!! later...
	//CInjector myInjector;
	//int res = myInjector.Unload(TEXT("ConsoleApplication1.dll"), TEXT("mb_warband.exe"));
	//std::cout << "dll unloaded " << res << "\n";
	//SendMessage(window, WM_SETREDRAW, TRUE, 0);
}

void IOHandler::initAnimationWindow(HWND window) {
	hThreadArray[0] = CreateThread(0, NULL, ThreadProc, (LPVOID)L"Loading Screen", NULL, NULL);

}


void IOHandler::setCursorPos(double percentX, double percentY) {
    int* res = GameValueProvider::get()->getResolution();
    //coordinates in the window
    double x = (double) percentX * (double)1e-2 * (double)*res;
    double y = (double) percentY * (double)1e-2 * (double)*(res+1);
    //windowed mode-> window offset
    x += (double)(*(res + 5) + (double)(*(res + 2) - *(res + 0)) );
    y += (double)(*(res + 7) + (double)(*(res + 3) - *(res + 1)) );
    //use of windows-func
    SetCursorPos(round(x),round(y));

}
double* IOHandler::getCursorPos() {
    double ret[2] = {0,0};
    int* res = GameValueProvider::get()->getResolution();
    POINT pt;
    GetCursorPos(&pt);
    ret[0] = (double)1e2 * (((double)(pt.x - ((double)(*(res + 5) + (double)(*(res + 2) - *(res + 0)) )))) / (double)*(res));
    ret[1] = (double)1e2 * (((double)(pt.y - ((double)(*(res + 7) + (double)(*(res + 3) - *(res + 1)) )))) / (double)*(res+1));
    return ret;

}


void IOHandler::fireMouseClick(int button) {
    INPUT    Input={0};													// Create our input.
   switch(button) {
        //left click
        case MOUSE_LEFT_CLICK:

            Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
            Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
            SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

            ZeroMemory(&Input,sizeof(INPUT));									// Fills a block of memory with zeros.
            Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
            Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
            SendInput( 1, &Input, sizeof(INPUT) );
            break;
        //right click
        case MOUSE_RIGHT_CLICK:
            break;
        //scrolldown
        case MOUSE_SCROLL_DOWN:

            Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
            Input.mi.dwFlags  = MOUSEEVENTF_WHEEL;
            Input.mi.mouseData = -(WHEEL_DELTA);
            SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

            break;
    }


}







int start = 0;					//Flag for knowing if already loaded

//WndProc for the new window
static DWORD getBaseAdress(DWORD dwPID);
//Register our windows Class
BOOL RegisterWindowClass(wchar_t szClassName[])
{
	WNDCLASSEX wc;
	wc.hInstance = (HINSTANCE)IOHandler::get()->getAnimationThread();
	wc.lpszClassName = (LPCWSTR)L"InjectedWindowClass";
	wc.lpszClassName = (LPCWSTR)szClassName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_DBLCLKS;
	wc.cbSize = sizeof (WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	if (!RegisterClassEx(&wc))
		return 0;
}
//Creating our windows Menu
HMENU CreateDLLWindowMenu()
{
	HMENU hMenu;
	hMenu = CreateMenu();
	HMENU hMenuPopup;
	if (hMenu == NULL)
		return FALSE;

	return hMenu;
}

//The new thread
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	MSG messages;
	wchar_t *pString = reinterpret_cast<wchar_t * > (lpParam);
	HMENU hMenu = CreateDLLWindowMenu();
	RegisterWindowClass(L"InjectedWindowClass");
	HWND wind = GameValueProvider::get()->getGameMainWindow();

	
	HWND hwnd = CreateWindowEx(0, L"InjectedWindowClass", pString, WS_MAXIMIZE | WS_EX_OVERLAPPEDWINDOW | WS_EX_TOPMOST, -20, -40, 0, 0, wind, hMenu,NULL, NULL);
	RECT rect;
	IOHandler::get()->setAnimWindow(hwnd);
	GetWindowRect(hwnd, &rect);
	SetWindowPos(hwnd, 0, -HIDEBORDERX, -HIDEBORDERY, rect.right + HIDEBORDERX, rect.bottom + HIDEBORDERY, SWP_NOACTIVATE);
	ShowWindow(hwnd, SW_SHOWNOACTIVATE);
	initAnimation(hwnd);
	//ShowCursor(FALSE);

	//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE ) | WS_EX_LAYERED);
	// Make this window 70% alpha
	//SetLayeredWindowAttributes(hwnd, 0, (255 * 70) / 100, LWA_ALPHA);
	while (GetMessage(&messages, NULL, 0, 0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	return 1;
}

//Our new windows proc
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	std::wstringstream wss;
	std::wstring str;
	wss << message;
	wss >> str;
	LPCWSTR result = str.c_str();
	//HDC dc = GetDC(hwnd);
	//TextOut(dc, 5, 5, result, 1);
	//ReleaseDC(hwnd, dc);



	switch (message)
	{

	case WM_MOUSEACTIVATE:
		return MA_NOACTIVATEANDEAT;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	}




	return 0;
}




#define RENDEROFFSETX 0
#define RENDEROFFSETY 0
#define LOADINGSCREENPATH L"loading_screen_1.bmp"

static HWND workWindow;
static WNDPROC wndprocOrig;
static UINT subclassId;
static DWORD refData;
static HBITMAP loadingImage;
/*
static HDC LoadBitmapToHDC(LPCTSTR bitmap_name, HBITMAP& hBitmap)
{
hBitmap = ::LoadBitmap(::AfxGetInstanceHandle(), bitmap_name);
// Create a MemDC to draw to.
HDC MemDC = ::CreateCompatibleDC(NULL);
SelectObject(MemDC, hBitmap);
return MemDC;
}*/
static void initAnimation(HWND window) {
	loadingImage = (HBITMAP)LoadImage(0, LOADINGSCREENPATH, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	DWORD error = GetLastError();

	BITMAP 			bitmap;
	HDC 			hdcMem;
	HGDIOBJ 		oldBitmap;

	RECT rect;
	GetWindowRect(window, &rect); // resolution
	//error section
	HDC hdc = GetDC(window);
	std::wstringstream wss;
	std::wstring str;
	wss << error;
	wss << LOADINGSCREENPATH;
	wss >> str;
	LPCWSTR result = str.c_str();
	if (loadingImage == NULL) TextOut(hdc, 50, 50, result, 44);

	//Draw
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, loadingImage);
	GetObject(loadingImage, sizeof(bitmap), &bitmap);
	DWORD res;
	StretchBlt(hdc, 0, RENDEROFFSETY, rect.right + RENDEROFFSETX, rect.bottom + RENDEROFFSETY, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
	ReleaseDC(window, hdc);
}
