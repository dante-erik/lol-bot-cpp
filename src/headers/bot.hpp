#pragma once

#include "../../cpp-robot/lib/Robot.hpp"

#define pure = 0

class bot : protected Robot
{
public:
    enum class status;

private:
    status Status;
    HANDLE hThread;
    LPDWORD lpThreadId;

protected:
    virtual DWORD run() pure;

public:
    bot();
    virtual ~bot();
    const void start();
    const void stop();
    virtual status const &get_Status() const;
    const HANDLE get_hThread() const;
    HANDLE get_hThread();
    const LPDWORD get_lpThreadId() const;
    LPDWORD get_lpThreadId();
    friend DWORD WINAPI run(LPVOID lpParam);
};

enum class bot::status
{
    WAITING,
    RUNNING,
    STOPPED
};

#undef pure