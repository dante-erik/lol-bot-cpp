#pragma once

#include "../../cpp-robot/lib/Robot.hpp"

#define pure = 0

class bot : protected Robot
{
public:
    enum class status
    {
        SUSPENDED,
        RUNNING,
        COMPLETED
    };

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
    const void stop(status stat = status::SUSPENDED);
    virtual status const &get_Status() const;
    const HANDLE get_hThread() const;
    HANDLE get_hThread();
    const LPDWORD get_lpThreadId() const;
    LPDWORD get_lpThreadId();
    friend DWORD WINAPI run(LPVOID lpParam);
};



#undef pure