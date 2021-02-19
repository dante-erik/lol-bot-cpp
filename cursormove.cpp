#include <iostream>
#include <Windows.h>

//code = Mojave Desert;
void InputEvent(DWORD type, DWORD flag){
	INPUT Input = {0};
	Input.type = type;
	Input.mi.dwFlags = flag;
	::SendInput(1, &Input, sizeof(INPUT));
}

void MouseEvent(DWORD flag){
	InputEvent(INPUT_MOUSE, flag);
}

void LeftDown()
{
	MouseEvent(MOUSEEVENTF_LEFTDOWN);
}

void LeftUp()
{
	MouseEvent(MOUSEEVENTF_LEFTUP);
}

int main()
{

	HWND window = FindWindow("MSPaintApp", "Untitled - Paint");
	if (window)
	{
		RECT rect = {0};
		GetWindowRect(window, &rect);

		SetForegroundWindow(window);
		SetActiveWindow(window);
		SetFocus(window);
		
		SetCursorPos(rect.left + 50 , rect.bottom - 200 );
        Sleep(10);
		LeftDown();
		for (int x = 0; x < 700; x+=5)
		{

			for (int y = 0; y < 300; y+=150)
			{
				Sleep(1);
				SetCursorPos(rect.left + 50 + x, rect.bottom - 200 - y);
			}
		}
		LeftUp();
	}

	return 0;
}
