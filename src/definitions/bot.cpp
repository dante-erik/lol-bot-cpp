#include <iostream>

#include "../headers/bot.hpp"

DWORD WINAPI run(LPVOID lpParam) { return reinterpret_cast<bot *>(lpParam)->run(); }

bot::bot() : Robot{}, Status{status::SUSPENDED}, hThread{} {
    // Sleep(50);
    // std::cout << "constructing bot...";
    // Sleep(2500);
    hThread = CreateThread(NULL, 0, ::run, this, CREATE_SUSPENDED, lpThreadId);
    // std::cout << "done\n";
};
bot::~bot()
{
    stop();
    CloseHandle(hThread);
}
const void bot::start() {
    ResumeThread(hThread);
    Status = status::RUNNING;
}
const void bot::stop(status status) {
    SuspendThread(hThread);
    Status = status;
}
bot::status const &bot::get_Status() const { return Status; }
const HANDLE bot::get_hThread() const { return hThread; }
HANDLE bot::get_hThread() { return hThread; }
const LPDWORD bot::get_lpThreadId() const { return lpThreadId; }
LPDWORD bot::get_lpThreadId() { return lpThreadId; }
