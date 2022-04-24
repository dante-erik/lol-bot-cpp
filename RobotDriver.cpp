#include "Robot.hpp"
#include <iostream>
#include <Windows.h>
#include <fstream>

int* screenshot(int& width, int& height) {
	HDC hdc = GetDC(NULL); // get the desktop device context
	HDC cdc = CreateCompatibleDC(hdc); // create a device context to use yourself
	height = (int)GetSystemMetrics(SM_CYVIRTUALSCREEN); // get the width and height of the screen
	width = 16 * height / 9; // only capture left monitor for dual screen setups, for both screens use (int)GetSystemMetrics(SM_CXVIRTUALSCREEN);
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, width, height); // create a bitmap
	SelectObject(cdc, hbitmap); // use the previously created device context with the bitmap
	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = width;
	bmi.biHeight = -height; // flip image upright
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 3 * width * height;
	BitBlt(cdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY); // copy from desktop device context to bitmap device context
	ReleaseDC(NULL, hdc);
	int* image = new int[width * height];
	GetDIBits(cdc, hbitmap, 0, height, image, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
	DeleteObject(hbitmap);
	DeleteDC(cdc);
	return image;
}

void CaptureScreen(const char* filename)
{
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetDC(hDesktopWnd);
	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);

	

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = nScreenWidth;
	bmi.bmiHeader.biHeight = nScreenHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* pPixels = new RGBQUAD[nScreenWidth * nScreenHeight];

	SYSTEMTIME st;

	GetSystemTime(&st);
	wprintf(L"%i:%i:%i.%i\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	for (int i = 0; i < 1000; i++) {

		BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);

		GetDIBits(
			hCaptureDC,
			hCaptureBitmap,
			0,
			nScreenHeight,
			pPixels,
			&bmi,
			DIB_RGB_COLORS
		);
	}

	GetSystemTime(&st);
	wprintf(L"%i:%i:%i.%i\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	// write:
	int p;
	int x, y;
	std::ofstream file;
	file.open(filename);
	file << "P3\n1920\n1080\n255\n";
	for (y = 0; y < nScreenHeight; y++) {
		for (x = 0; x < nScreenWidth; x++) {
			p = (nScreenHeight - y - 1) * nScreenWidth + x; // upside down
			file << (int)pPixels[p].rgbRed << " ";
			file << (int)pPixels[p].rgbGreen << " ";
			file << (int)pPixels[p].rgbBlue << "\n";
		}
	}
	file.close();

	delete[] pPixels;

	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
}

HRESULT SavePixelsToFile32bppPBGRA(UINT width, UINT height, UINT stride, LPBYTE pixels, LPWSTR filePath, const GUID& format)
{
	if (!filePath || !pixels)
		return E_INVALIDARG;

	HRESULT hr = S_OK;
	IWICImagingFactory* factory = nullptr;
	IWICBitmapEncoder* encoder = nullptr;
	IWICBitmapFrameEncode* frame = nullptr;
	IWICStream* stream = nullptr;
	GUID pf = GUID_WICPixelFormat32bppPBGRA;
	BOOL coInit = CoInitialize(nullptr);

	HRCHECK(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory)));
	HRCHECK(factory->CreateStream(&stream));
	HRCHECK(stream->InitializeFromFilename(filePath, GENERIC_WRITE));
	HRCHECK(factory->CreateEncoder(format, nullptr, &encoder));
	HRCHECK(encoder->Initialize(stream, WICBitmapEncoderNoCache));
	HRCHECK(encoder->CreateNewFrame(&frame, nullptr)); // we don't use options here
	HRCHECK(frame->Initialize(nullptr)); // we dont' use any options here
	HRCHECK(frame->SetSize(width, height));
	HRCHECK(frame->SetPixelFormat(&pf));
	HRCHECK(frame->WritePixels(height, stride, stride * height, pixels));
	HRCHECK(frame->Commit());
	HRCHECK(encoder->Commit());

cleanup:
	RELEASE(stream);
	RELEASE(frame);
	RELEASE(encoder);
	RELEASE(factory);
	if (coInit) CoUninitialize();
	return hr;
}

int main() {
	Sleep(4000);

	Robot robot;

	SYSTEMTIME st;

	GetSystemTime(&st);
	wprintf(L"%i:%i:%i.%i\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	for(int i = 0; i < 1; i++)
	robot.updateScreenBuffer();

	GetSystemTime(&st);
	wprintf(L"%i:%i:%i.%i\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	std::ofstream file;
	file.open("BitBltScreenCap.ppm");
	file << "P3 1920 1080 255\n";

	for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			file << (int)robot.getRed({ x,y }) << " " << (int)robot.getGreen({ x,y }) << " " << (int)robot.getBlue({ x,y }) << "\n";
		}
	}

	//robot.updateScreenBuffer();

	/*for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			robot.setCursorPos({ x, y });
		}
	}

	while (true) {
		robot.updateScreenBuffer();
		POINT p = { 1920 / 2, 1080 / 2 };
		std::cout << (int)robot.getRed(p) << " " << (int)robot.getGreen(p) << " " << (int)robot.getBlue(p) << "\n";
		std::cout << "Is pixel equal: " << robot.isPixelEqual({ p, 200, 0, 200 }) << std::endl;
		std::cout << "Is pixel similar: " << robot.isPixelSimilar({ p, 40, 40, 40 }, 20) << std::endl << std::endl;
		Sleep(1000);
	}*/











	/*std::cout << "made it here 2" << std::endl;

	SYSTEMTIME st;

	GetSystemTime(&st);
	wprintf(L"%i:%i:%i.%i\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	for(int i = 0; i < 1000; i++)
	robot.updateScreenBuffer();

	GetSystemTime(&st);
	wprintf(L"%i:%i:%i.%i\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	std::cout << "updated screen buffer" << std::endl;

	std::ofstream file;
	file.open("ScreenImageMethod1.ppm");
	file << "P3 1920 1080 255\n";
	for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			file << (int)robot.getRed({ x,y }) << " " << (int)robot.getGreen({ x,y }) <<  " " << (int)robot.getBlue({x,y}) << "\n";
		}
	}
	file.close();

	std::cout << "2" << std::endl;
	file.open("ppmtest.ppm");
	std::cout << "3" << std::endl;
	file << "P3\n1920\n1080\n255\n";
	std::cout << "4" << std::endl;
	for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			file << "255 ";
			file << "0 ";
			file << "0\n";
		}
	}
	std::cout << "5" << std::endl;
	file.close();
	std::cout << "6" << std::endl;

	CaptureScreen("ScreenImageMethod2.ppm");*/

	//int width = 1920, height = 1080;
	//int* image = screenshot(width, height);

	//// access pixel colors for position (x|y)
	//int x = 0, y = 0;
	//int color = image[x + y * width];
	//int red = (color >> 16) & 255;
	//int green = (color >> 8) & 255;
	//int blue = color & 255;

	//file.open("ScreenImageMethod3.ppm");
	//file << "P6 1920 1080 255\n";
	//for (int y = 0; y < 1080; y++) {
	//	for (int x = 0; x < 1920; x++) {
	//		color = image[x + y * width];
	//		file << (char)((color >> 16) & 255) << (char)((color >> 8) & 255) << (char)(color & 255);
	//	}
	//}
	//file.close();

	//delete[] image;

	//robot.getRGBQUAD({ 0,0 });

	/*for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			std::cout << "(x, y): (" << x << ", " << y << ")\n" <<
				"(r, g, b): (" << robot.getRGBQUAD({ x,y }).rgbRed <<
				", " << robot.getRGBQUAD({ x,y }).rgbGreen <<
				", " << robot.getRGBQUAD({ x,y }).rgbBlue << ")\n\n";
		}
		std::cout << std::endl;
	}*/

	//for(int x = 0; x < 1921; x++)
	//	for(int y = 0; y < 1081; y++) { 
	//		robot.setCursorPos({ x,y });
	//		//Sleep(1);
	//	}
			

	//std::cout << robot.getScancode('.') << std::endl;

	//robot.escapeKeyClick(30);

	//for (int fkey = 1; fkey < 13; fkey++)
		//robot.fKeyClick(fkey, 30);

	//robot.keyClick("`1234567890-=qwertyuiop[]\\asdfghjkl;'", 37, 30);

	
	//robot.enterKeyClick(30);

	//robot.ctrlPlusKeyClick('s');
	//robot.shiftPlusKeyClick('a');

	//std::cout << "VK_LSHIFT =  " << VK_LSHIFT << std::endl;
	//std::cout << "DIK_LSHIFT = " << DIK_LSHIFT << std::endl;


	/*std::cout << robot.setCursorPos({ 0, 0 }) << std::endl;
	Sleep(1000);

	std::cout << robot.setCursorPos({ 1920/2, 1080/2 }) << std::endl;
	Sleep(1000);

	std::cout << robot.leftDown() << std::endl;
	robot.leftUp({ 1100, 700 });

	Sleep(1000);

	robot.keyClick("abc", 3);*/

	//robot.rightDown();
	//robot.rightUp({ 400,800 });

	//Sleep(1000);



	{
	//SetCursorPos(1000, 300);

	//for (int x = 0; x < 1920; x+=1) {
	//	for (int y = 0; y < 1080; y+=1) {
	//		SetCursorPos(x, y);
	//		//Sleep(2);
	//	}
	//}


	//INPUT ipmouse;
	//ipmouse.type = INPUT_MOUSE;

	//ipmouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	//SendInput(1, &ipmouse, sizeof(INPUT));

	////Sleep(100);

	//SetCursorPos(200, 200);

	//ipmouse.mi.dwFlags = MOUSEEVENTF_LEFTUP;

	//SendInput(1, &ipmouse, sizeof(INPUT));

	////Sleep(100);

	//INPUT ip;
	//ip.type = INPUT_KEYBOARD; // Set type to keyboard

	//ip.ki.wVk = 0; // Virtual keystroke isn't used
	//ip.ki.wScan = (BYTE)0x23; // Hardware scan code for 'H' key
	//ip.ki.dwFlags = KEYEVENTF_SCANCODE; // KEYEVENTF_SCANCODE flag to specify wScan is used, and wVk is ignored 
	//ip.ki.time = 0; // No delay
	//ip.ki.dwExtraInfo = 0; // No extra info

	////for (int i = 0; i < 10; i++) {
	//	ip.ki.dwFlags = KEYEVENTF_SCANCODE;

	//	SendInput(1, &ip, sizeof(INPUT));

	//	Sleep(1000);

	//	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP OR'ed with KEYEVENTF_SCANCODE to create a key release
	//	SendInput(1, &ip, sizeof(INPUT));

	//	Sleep(1000);
	////}
	//	

	////Robot robot;

	////robot.setCursorPos({ 100,100 });
}

	std::cout << "done!" << std::endl;

	return 0;
}