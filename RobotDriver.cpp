#include "Robot.hpp"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <chrono>

BOOL saveScreenshot() {
	std::unique_ptr<Robot> r = std::make_unique<Robot>();

	r->updateScreenBuffer();

	std::ofstream file;
	file.open("screenshot image pp3.ppm");
	file << "P3\n" << r->width() << " " << r->height() << " 255\n";
	for (int y = 0; y < r->height(); y++) {
		for (int x = 0; x < r->width(); x++) {
			file << static_cast<int>(r->getRed({ x,y })) << " "
				<< static_cast<int>(r->getGreen({ x,y })) << " "
				<< static_cast<int>(r->getBlue({ x,y })) << "\n";
		}
	}
	file.close();

	return 0;
}

int main() {
	std::unique_ptr<Robot> r = std::make_unique<Robot>();

	using namespace std::chrono;

	int totalBatches = 10;
	int functionCallsPerBatch = 100;

	time_point<high_resolution_clock> start_point, end_point;
	long long start, end;
	double duration, durationTotal = 0.0, durationAverage;

	for (int batch = 0; batch < totalBatches; batch++) {
		start_point = high_resolution_clock::now();

		for (int functionCall = 0; functionCall < functionCallsPerBatch; functionCall++) {
			r->setCursorPos({ 100,100 });
		}

		end_point = high_resolution_clock::now();

		start = time_point_cast<milliseconds>(start_point).time_since_epoch().count();
		end = time_point_cast<milliseconds>(end_point).time_since_epoch().count();

		duration = (end - start) / static_cast<double>(functionCallsPerBatch);
		durationTotal += duration;

		std::cout << "Test " << batch << ", time per loop block: " << duration << " milliseconds" << std::endl;
	}

	durationAverage = durationTotal / static_cast<double>(totalBatches);

	std::cout << "Average time per loop block: " << durationAverage << " milliseconds" << std::endl;

	saveScreenshot();

	return 0;
}