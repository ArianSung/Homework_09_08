#include "CMobleThread.h"
#include <stdio.h>

CMobleThread::CMobleThread()
{
    m_hThread = NULL;
    m_threadId = 0;
}

CMobleThread::~CMobleThread()
{
    if (m_hThread != NULL)
    {
        CloseHandleSafe();
    }
}

BOOL CMobleThread::StartWinThread(LPTHREAD_START_ROUTINE _proc, LPVOID _param) // 디폴트 _param = NULL
{
    if (m_hThread != NULL)
    {
        return FALSE;
    }
    m_hThread = CreateThread(NULL, 0, _proc, _param, 0, &m_threadId);
    if (m_hThread == NULL)
    {
        m_threadId = 0;
        return FALSE;
    }
    return TRUE;
}

BOOL CMobleThread::StartCrtThread(unsigned(__stdcall* _proc)(void*), void* _param) // 디폴트 _param = NULL
{
    uintptr_t hv;
    unsigned tid;
    if (m_hThread != NULL)
    {
        return FALSE;
    }
    hv = _beginthreadex(NULL, 0, _proc, _param, 0, &tid);
    if (hv == 0)
    {
        m_threadId = 0;
        return FALSE;
    }
    m_hThread = (HANDLE)hv;
    m_threadId = (DWORD)tid;
    return TRUE;
}

BOOL CMobleThread::ExitWait(DWORD _timeout) //디폴트 _timeout = INFINITE
{
    DWORD dwRet;
    if (m_hThread == NULL)
    {
        return FALSE;
    }
    dwRet = WaitForSingleObject(m_hThread, _timeout);
    if (dwRet == WAIT_OBJECT_0)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL CMobleThread::CloseHandleSafe()
{
    if (m_hThread == NULL)
    {
        return FALSE;
    }
    CloseHandle(m_hThread);
    m_hThread = NULL;
    m_threadId = 0;
    return TRUE;
}

HANDLE CMobleThread::GetHandle()
{
    return m_hThread;
}

BOOL CMobleThread::IsRunning()
{
    DWORD code;
    if (m_hThread == NULL)
    {
        return FALSE;
    }
    if (GetExitCodeThread(m_hThread, &code) == 0)
    {
        return FALSE;
    }
    return (code == STILL_ACTIVE);
}

DWORD CMobleThread::GetThreadId()
{
    return m_threadId;
}
