#pragma once
#ifndef MOBLE_THREAD_H
#define MOBLE_THREAD_H

#include <windows.h>
#include <process.h>



class CMobleThread
{
public:
    CMobleThread();
    ~CMobleThread();

public:
    BOOL StartWinThread(LPTHREAD_START_ROUTINE _proc, LPVOID _param = NULL);
    BOOL StartCrtThread(unsigned(__stdcall* _proc)(void*), void* _param = NULL);

    BOOL ExitWait(DWORD _timeout = INFINITE);
    BOOL CloseHandleSafe();

    HANDLE GetHandle();
    BOOL   IsRunning();

    DWORD  GetThreadId();

private:
    HANDLE m_hThread;
    DWORD  m_threadId;
};

#endif //MOBLE_THREAD_H
