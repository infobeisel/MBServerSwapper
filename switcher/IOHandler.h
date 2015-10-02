#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <Windows.h>
#define MAX_THREADS 1
#include "injector.h"
#include <d3d9.h>
#include <vector>
static void initAnimation(HWND window);

static void 	diceNewImage(int numImages);
static void redraw(HWND window, std::vector<HBITMAP>* ims);


DWORD WINAPI ThreadProc(LPVOID lpParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class IOHandler
{
    public:
        IOHandler(){}
        static IOHandler* get();
        virtual ~IOHandler();
        /** left upper corner is (0,0) **/
        void setCursorPos(double percentX , double percentY);
        double* getCursorPos();
        void fireMouseClick(int button);
        /**starts an own thread, which updates the loading screen until it is stopped by stopLoadingAnimation() **/
		void startLoadingAnimation(HWND window);
		void stopLoadingAnimation(HWND window);
		void initAnimationWindow(HWND window);

		HANDLE getAnimationThread() { return hThreadArray[0]; }
		void setAnimWindow(HWND window) { animWindow = window; };
		void setWindowToForeground(HWND window);

		int activeLoadingImageIndex;
		std::vector<HBITMAP> loadingImages;
    protected:
    private:
        static IOHandler* instance;
		DWORD   dwThreadIdArray[MAX_THREADS];
		HANDLE  hThreadArray[MAX_THREADS];
		CInjector myInjector;
		HWND animWindow;



		
};

#endif // IOHANDLER_H
