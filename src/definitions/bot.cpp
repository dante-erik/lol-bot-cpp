#include "../headers/bot.hpp"

bot::bot() : Robot{}, Status{status::WAITING}, hThread{CreateThread(NULL, 0, ::run, this, CREATE_SUSPENDED, lpThreadId)} {};
bot::~bot()
{
    stop();
    CloseHandle(hThread);
}
const void bot::start() { ResumeThread(hThread); }
const void bot::stop() { SuspendThread(hThread); }
bot::status const &bot::get_Status() const { return Status; }
const HANDLE bot::get_hThread() const { return hThread; }
HANDLE bot::get_hThread() { return hThread; }
const LPDWORD bot::get_lpThreadId() const { return lpThreadId; }
LPDWORD bot::get_lpThreadId() { return lpThreadId; }

DWORD WINAPI run(LPVOID lpParam) { return reinterpret_cast<bot *>(lpParam)->run(); }