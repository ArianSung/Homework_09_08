#pragma once
#ifndef MOBLE_THREAD_MGR_H
#define MOBLE_THREAD_MGR_H

#include "CMobleThread.h"


#define MOBLE_THREAD_MAX 64

class CMobleThreadMgr
{
public:
    CMobleThreadMgr();
    ~CMobleThreadMgr();

public:
    CMobleThread* CreateThread(BOOL _owned);

    BOOL StartWinThread(CMobleThread* _pThread, LPTHREAD_START_ROUTINE _proc, LPVOID _param);
    BOOL StartCrtThread(CMobleThread* _pThread, unsigned(__stdcall* _proc)(void*), void* _param);

    BOOL Add(CMobleThread* _pThread, BOOL _owned);

    DWORD GetCount();

    BOOL ExitWaitAll(DWORD _timeout = INFINITE);
    int  ExitWaitAny(DWORD _timeout = INFINITE);

    BOOL ExitWaitSingleByIndex(int _index, DWORD _timeout = INFINITE);
    BOOL ExitWaitSingle(CMobleThread* _pThread, DWORD _timeout = INFINITE);
        

    CMobleThread* GetThreadByIndex(int _index);
    HANDLE        GetHandleByIndex(int _index);
    HANDLE        GetHandleByThread(CMobleThread* _pThread);
    int         GetIndexByThread(CMobleThread* _pThread);

    DWORD GetThreadIdByIndex(int _index);


    BOOL          IsRunningByIndex(int _index);

    BOOL RemoveByIndex(int _index);
    BOOL CloseAll();

private:
    BOOL _Append(CMobleThread* _pThread, BOOL _owned);
    void _CompactRemove(int _index);
    void _DeleteIfOwned(int _index);

private:
    CMobleThread* m_threads[MOBLE_THREAD_MAX];
    BOOL          m_owned[MOBLE_THREAD_MAX];
    int           m_count;
};

#endif // MOBLE_THREAD_MGR_H 

