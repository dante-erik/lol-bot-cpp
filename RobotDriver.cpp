#include "Robot.hpp"
#include <iostream>
#include <Windows.h>
#include <fstream>

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
	file << "P3 " << robot.width() << " " << robot.height() << " 255\n";

	for (int y = 0; y < robot.height(); y++) {
		for (int x = 0; x < robot.width(); x++) {
			file << (int)robot.getRed({ x,y }) << ' ' << (int)robot.getGreen({ x,y }) << ' ' << (int)robot.getBlue({ x,y }) << '\n';
		}
	}

	std::cout << "done!" << std::endl;

	return 0;
}