#include <fstream>
#include <windows.h>
#include <WinUser.h>
#include <wingdi.h>

void CaptureScreen(char*);

int main(){

	CaptureScreen("lmao.txt");

}

void CaptureScreen(char *filename){
    int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    HWND hDesktopWnd = GetDesktopWindow();
    HDC hDesktopDC = GetDC(hDesktopWnd);
    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
    SelectObject(hCaptureDC, hCaptureBitmap); 

    BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0,0, SRCCOPY|CAPTUREBLT); 

    BITMAPINFO bmi = {0}; 
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader); 
    bmi.bmiHeader.biWidth = nScreenWidth; 
    bmi.bmiHeader.biHeight = nScreenHeight; 
    bmi.bmiHeader.biPlanes = 1; 
    bmi.bmiHeader.biBitCount = 32; 
    bmi.bmiHeader.biCompression = BI_RGB; 

    RGBQUAD *pPixels = new RGBQUAD[nScreenWidth * nScreenHeight]; 

    GetDIBits(
        hCaptureDC, 
        hCaptureBitmap, 
        0,  
        nScreenHeight,  
        pPixels, 
        &bmi,  
        DIB_RGB_COLORS
    );  

    // write:
    int p;
    int x, y;

	std::ofstream file(filename);
    //FILE *fp = fopen(filename, "wb");
    for(y = 0; y < nScreenHeight; y++){
        for(x = 0; x < nScreenWidth; x++){
            p = (nScreenHeight-y-1)*nScreenWidth+x; // upside down
            unsigned char r = pPixels[p].rgbRed;
            unsigned char g = pPixels[p].rgbGreen;
            unsigned char b = pPixels[p].rgbBlue;
            file << "x: " << x << " y: " << y << " p: " << p << " red: " << (int)r << " green: " << (int)g << " blue :" << (int)b << "\n";
        }
    }

	file << std::flush;

    delete [] pPixels; 

    ReleaseDC(hDesktopWnd, hDesktopDC);
    DeleteDC(hCaptureDC);
    DeleteObject(hCaptureBitmap);
}