#include <stdio.h>
#include "CMobleThreadMgr.h"


CMobleThreadMgr::CMobleThreadMgr()
{
   m_count = 0;
    
   for(int i=0;i < MOBLE_THREAD_MAX;++i)
   {
        m_threads[i] = NULL;
        m_owned[i] = FALSE;
   }
}

CMobleThreadMgr::~CMobleThreadMgr()
{
    CloseAll();
}

BOOL CMobleThreadMgr::_Append(CMobleThread* _pThread, BOOL _owned)
{
    if (_pThread == NULL)
    {
        return FALSE;
    }
    if (m_count >= MOBLE_THREAD_MAX)
    {
        return FALSE;
    }
    m_threads[m_count] = _pThread;
    m_owned[m_count] = _owned;
    m_count += 1;
    return TRUE;
}

void CMobleThreadMgr::_DeleteIfOwned(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return;
    }
    if (m_owned[_index] == TRUE)
    {
        if (m_threads[_index] != NULL)
        {
            delete m_threads[_index];
        }
    }
    m_threads[_index] = NULL;
    m_owned[_index] = FALSE;

    return;
}

void CMobleThreadMgr::_CompactRemove(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return;
    }
    if (_index != (m_count - 1))
    {
        m_threads[_index] = m_threads[m_count - 1];
        m_owned[_index] = m_owned[m_count - 1];
    }
    m_threads[m_count - 1] = NULL;
    m_owned[m_count - 1] = FALSE;
    m_count = m_count - 1;
    return;
}

CMobleThread* CMobleThreadMgr::CreateThread(BOOL _owned)
{
    CMobleThread* p = NULL;
    BOOL ok = FALSE;

    p = new CMobleThread();
    if (p == NULL)
    {
        return NULL;
    }
    ok = _Append(p, _owned);
    if (ok == FALSE)
    {
        delete p;
        return NULL;
    }
    return p;
}

BOOL CMobleThreadMgr::StartWinThread(CMobleThread* _pThread, LPTHREAD_START_ROUTINE _proc, LPVOID _param)
{
    BOOL ok = FALSE;
    if (_pThread == NULL)
    {
        return FALSE;
    }
    ok = _pThread->StartWinThread(_proc, _param);
    if (ok == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CMobleThreadMgr::StartCrtThread(CMobleThread* _pThread, unsigned(__stdcall* _proc)(void*), void* _param)
{
    BOOL ok = FALSE;
    if (_pThread == NULL)
    {
        return FALSE;
    }
    ok = _pThread->StartCrtThread(_proc, _param);
    if (ok == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CMobleThreadMgr::Add(CMobleThread* _pThread, BOOL _owned)
{
    return _Append(_pThread, _owned);
}

DWORD CMobleThreadMgr::GetCount()
{
    return m_count;
}

BOOL CMobleThreadMgr::ExitWaitAll(DWORD _timeout)
{
    HANDLE arr[MOBLE_THREAD_MAX] = { NULL };
    
    DWORD dwRet = 0;

    if (m_count == 0)
    {
        return TRUE;
    }

    
    for(int i=0;i < m_count; ++i)
    {
        arr[i] = m_threads[i]->GetHandle();
    
    }

    dwRet = WaitForMultipleObjects(m_count, arr, TRUE, _timeout);
    if (dwRet >= WAIT_OBJECT_0 && dwRet < (WAIT_OBJECT_0 + m_count))
    {
        return TRUE;
    }
    return FALSE;
}

int CMobleThreadMgr::ExitWaitAny(DWORD _timeout)
{
    HANDLE arr[MOBLE_THREAD_MAX] = { NULL };
    DWORD dwRet = 0;
    int idx = -1;

    if (m_count == 0)
    {
        return -1;
    }

    
    for(int i=0;i < m_count;++i)
    {
        arr[i] = m_threads[i]->GetHandle();
    
    }

    dwRet = WaitForMultipleObjects(m_count, arr, FALSE, _timeout);
    if (dwRet >= WAIT_OBJECT_0 && dwRet < (WAIT_OBJECT_0 + m_count))
    {
        idx = (int)(dwRet - WAIT_OBJECT_0);

        if (idx < 0 || idx >= MOBLE_THREAD_MAX)
        {
            return -1;
        }
        
        if (m_threads[idx] != NULL)
        {
            m_threads[idx]->CloseHandleSafe();
        }
        _DeleteIfOwned(idx);
        _CompactRemove(idx);
        return idx;
        

        
    }
    return -1;
}

BOOL CMobleThreadMgr::ExitWaitSingleByIndex(int _index, DWORD _timeout)
{
    CMobleThread* p = NULL;
    BOOL ok = FALSE;
    if (_index >= m_count || _index < 0)
    {
        return FALSE;
    }
    p = m_threads[_index];
    if (p == NULL)
    {
        return FALSE;
    }
    ok = p->ExitWait(_timeout);
    return ok;
}

BOOL CMobleThreadMgr::ExitWaitSingle(CMobleThread* _pThread, DWORD _timeout)
{
    if (_pThread == NULL)
    {
        return FALSE;
    }
    if (_pThread->GetHandle() == NULL)
    {
        return FALSE;
    }
    return _pThread->ExitWait(_timeout);
}

CMobleThread* CMobleThreadMgr::GetThreadByIndex(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return NULL;
    }
    return m_threads[_index];
}

HANDLE CMobleThreadMgr::GetHandleByIndex(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return NULL;
    }
    if (m_threads[_index] == NULL)
    {
        return NULL;
    }
    return m_threads[_index]->GetHandle();
}

HANDLE CMobleThreadMgr::GetHandleByThread(CMobleThread* _pThread)
{
    if (_pThread == NULL)
    {
        return NULL;
    }
    return _pThread->GetHandle();
}

int CMobleThreadMgr::GetIndexByThread(CMobleThread* _pThread)
{

    if (_pThread == NULL)
    {
        return (-1);
    }

    for(int i= 0;i < m_count; ++i)
    {
        if (m_threads[i] == _pThread)
        {
            return i;
        }

    }
    return (-1);
}

DWORD CMobleThreadMgr::GetThreadIdByIndex(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return 0;
    }
    if (m_threads[_index] == NULL)
    {
        return 0;
    }
    return m_threads[_index]->GetThreadId();
}


BOOL CMobleThreadMgr::IsRunningByIndex(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return FALSE;
    }
    if (m_threads[_index] == NULL)
    {
        return FALSE;
    }
    return m_threads[_index]->IsRunning();
}

BOOL CMobleThreadMgr::RemoveByIndex(int _index)
{
    if (_index >= m_count || _index < 0)
    {
        return FALSE;
    }
    _DeleteIfOwned(_index);
    _CompactRemove(_index);
    return TRUE;
}

BOOL CMobleThreadMgr::CloseAll()
{
    
    for(int i=0;i < m_count;++i)
    {
        if (m_threads[i] != NULL)
        {
            m_threads[i]->CloseHandleSafe();
        }
        _DeleteIfOwned(i);
    
    }
    m_count = 0;
    return TRUE;
}
