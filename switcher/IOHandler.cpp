#include "IOHandler.h"
#define _WIN32_WINNT 0x0500 // need this for having the INPUT-datastructure
#define WM_LOADINGSCREEN WM_USER+0


#include "GameValueProvider.h"
#include <iostream>
#include <cmath>

#include <Commctrl.h>



#define MYMENU_EXIT         (WM_APP + 101)
#define MYMENU_MESSAGEBOX   (WM_APP + 102) 

#define RENDEROFFSETX 0
#define RENDEROFFSETY 0
#define LOADINGSCREENPATHS {L"loading_screen_1.bmp",L"loading_screen_2.bmp",L"loading_screen_3.bmp"}
#define LOADINGSCREENPATHSNUM 3
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


void IOHandler::startLoadingAnimation(HWND window) {
	
	RECT rect;
	GetWindowRect(window, &rect);
	if (GameValueProvider::get()->isFullScreen()) {
		rect.right = (int)GetSystemMetrics(SM_CXSCREEN);
		rect.bottom = (int)GetSystemMetrics(SM_CYSCREEN);
	}


	SetWindowPos(animWindow, NULL,
	  	     rect.left,
		     rect.top,
		     rect.right,
		     rect.bottom,
		SWP_NOREDRAW | SWP_SHOWWINDOW | SWP_NOACTIVATE
		);


	//set animWindow to Foreground (to paint over other windows which were activated while playing the game)
	SendMessageTimeout(animWindow, WM_LOADINGSCREEN, 0, 0, SMTO_NORMAL, 3000, NULL);
	//set this window to foreground again
	setWindowToForeground(window);

	SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(window, RGB(0, 0, 0), (255 * 2) / 100, LWA_ALPHA);
	


	initAnimation(animWindow);
	ShowCursor(false);


}

void IOHandler::stopLoadingAnimation(HWND window) {
	
	//setWindowToForeground(animWindow);
	SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(window, RGB(0, 0, 0), (255 * 100) / 100, LWA_ALPHA);
	//setWindowToForeground(window);
	ShowWindow(animWindow, SW_HIDE);
	ShowCursor(true);


}


void IOHandler::setWindowToForeground(HWND window) {
	DWORD foreThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	DWORD appThread = GetCurrentThreadId();

	if (foreThread != appThread)
	{
		AttachThreadInput(foreThread, appThread, true);
		BringWindowToTop(window);
		ShowWindow(window, SW_SHOW);
		AttachThreadInput(foreThread, appThread, false);
	}
	else
	{
		BringWindowToTop(window);
		ShowWindow(window, SW_SHOW);
	}

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
	double framex = (double)(*(res + 2));
	double framey = (double)(*(res + 3));

	x += (double)(*(res + 5) + framex - *(res + 0));
	y += (double)(*(res + 7) + framey - *(res + 1));
	//std::cout << (double)(*(res + 5) + framex - *(res + 0)) << "    " << (double)(*(res + 7) + framey - *(res + 1)) << "\n";
	
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

	RECT rect;
	GetWindowRect(wind, &rect);
	if (GameValueProvider::get()->isFullScreen()) {
		rect.right = (int) GetSystemMetrics(SM_CXSCREEN);
		rect.bottom = (int)GetSystemMetrics(SM_CYSCREEN);
	}
	HWND hwnd = CreateWindowEx(0, L"InjectedWindowClass", NULL,  WS_POPUP | WS_EX_LAYERED, 0, 0, rect.right, rect.bottom, NULL, hMenu, NULL, NULL);
	if (GameValueProvider::get()->isFullScreen()) {

	}
	IOHandler::get()->setAnimWindow(hwnd);
	ShowWindow(hwnd, SW_HIDE);


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
	//std::cout << message << "||\n";

	switch (message)
	{

	case WM_MOUSEACTIVATE:
		return MA_NOACTIVATEANDEAT;
	case WM_LOADINGSCREEN:
		std::cout <<"message:" << message << "  wParam: " << &wParam << " lParam : " << lParam << "||\n";
		IOHandler::get()->setWindowToForeground(hwnd);
		return 1;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

static void initAnimation(HWND window) {
	std::vector<LPCWSTR> imagepaths = LOADINGSCREENPATHS;
	//load all images initially
	for (int i = 0; i < LOADINGSCREENPATHSNUM; i++) {
		IOHandler::get()->loadingImages.push_back((HBITMAP)LoadImage(0, imagepaths.at(i), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

		
	}
	//select a loading image
	diceNewImage(3);
	redraw(window,& IOHandler::get()->loadingImages);
	
}

static void diceNewImage(int numImages) {
	IOHandler::get()->activeLoadingImageIndex = rand() % numImages;
}


static void redraw(HWND window,std::vector<HBITMAP>* images){
	DWORD error = GetLastError();

	BITMAP 			bitmap;
	HDC 			hdcMem;
	HGDIOBJ 		oldBitmap;
	RECT rect;
	GetWindowRect(window, &rect); // resolution
	//error section

	std::cout << "draw image at " << rect.right << " x " << rect.bottom << "\n";
	std::wstringstream wss;
	std::wstring str;
	wss << error;
	wss >> str;
	LPCWSTR result = str.c_str();
	int index = IOHandler::get()->activeLoadingImageIndex;
	HDC hdc = GetDC(window);
	if (images->at(index) == NULL) TextOut(hdc, 50, 50, result, 44);
	//Draw
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, images->at(index));
	GetObject(images->at(index), sizeof(bitmap), &bitmap);
	DWORD res;
	StretchBlt(hdc, 0, RENDEROFFSETY, rect.right + RENDEROFFSETX, rect.bottom + RENDEROFFSETY, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
	ReleaseDC(window, hdc);
}