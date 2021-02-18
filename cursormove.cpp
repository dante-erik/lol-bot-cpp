#include <iostream>
#include <Windows.h>

int main()
{
    HWND window = FindWindow("TaskManagerWindow", "Task Manager");
    if (window)
    {
        RECT rect = {0};
        GetWindowRect(window, &rect);

        SetForegroundWindow(window);
        SetActiveWindow(window);
        SetFocus(window);
        Sleep(300);
        SetCursorPos(rect.right - 200, rect.bottom - 200);
    }

    return 0;
}