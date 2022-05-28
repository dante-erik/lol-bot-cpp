#include "YuumiBot.hpp"
#include "YuumiBotPixelsAndPoints.hpp"
#include <iostream>

using namespace std::chrono;

YuumiBot::YuumiBot()
	: health{ 1.0, 1.0, 1.0, 1.0, 1.0 },
	weightedKDA{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	kills{ 0, 0, 0, 0, 0 },
	deaths{ 0, 0, 0, 0, 0 },
	assists{ 0, 0, 0, 0, 0 },
	currentAlly(ADC),
	tolerance(0),
	keyClickDuration(50),
	keyClickDurationRandomness(20),
	mouseClickDuration(40),
	mouseClickDurationRandomness(20),
	gameStart(steady_clock::now()),
	qPing(steady_clock::now()),
	wPing(steady_clock::now()),
	ePing(steady_clock::now()),
	rPing(steady_clock::now()),
	buy(steady_clock::now()),
	recall(steady_clock::now()),
	die(steady_clock::now()),
	dragonKill(steady_clock::now()),
	riftHeraldKill(steady_clock::now()),
	baronKill(steady_clock::now()),
	mikaels(steady_clock::now()),
	redemption(steady_clock::now()),
	shurelyas(steady_clock::now()),
	iceSupportItem(steady_clock::now()),
	robot(std::make_unique<Robot>())
{ }

YuumiBot::~YuumiBot() { }

