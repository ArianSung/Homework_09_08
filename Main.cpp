
// 강제성 없는 과제 CMobleThread ,  CMobleThreadMgr 클래스에 주석을 달아보거나
// 또는 자신만의 Thread Wrapping  클래스를 만들어 보세요
// 완성한 학생은 slack 과제-제출 에 올려 주세요
// 과제 검사 없음, 강제성 없음? 기한은 2025/09/09 오전 10시까지
// 오전에 와서 다른 학생 제출본 참고 해서 제출 가능 09/09일 일일테스트를 과제로 대체 합니다
// 다른 학생의 제출본 참고 하였을 경우 출처 표기!
// 제출 순서에 따른 가산점 있음
// 창의력 가산점 있음, 코드 줄맞춤 가산점 있음, 변수 이름 통일성 가산점 있음
// 즉 다른 학생 제출본의 코드를 줄맞춤 또는 변수이름 변경등으로 가산점을 얻을 수 도 있음
// 코드 줄맞춤, 변수이름 통일성등은 주관적인 관점에서 채점 ( 단! 인기 제출본(출처로 많이 사용된 제출본)은  충분히 반영할 예정)
// 인기 제출본을 참고한 학생도 가산점 있음
// 코드는 단순하고(논리기준) 직관적이게 작성

#include <stdio.h>
#include "CMobleThread.h"
#include "CMobleThreadMgr.h"

DWORD WINAPI WorkerFuncA(LPVOID _p)
{
    int i;
    i = 0;
    while (i < 5)
    {
        printf("[A] %d/5\n", i + 1);
        Sleep(300);
        i = i + 1;
    }
    return 0;
}

DWORD WINAPI WorkerFuncB(LPVOID _p)
{
    int i;
    i = 0;
    while (i < 8)
    {
        printf("[B] %d/8\n", i + 1);
        Sleep(200);
        i = i + 1;
    }
    return 0;
}

int main()
{
    CMobleThreadMgr mgr;
    CMobleThread* t1 = mgr.CreateThread(TRUE);
    CMobleThread* t2 = mgr.CreateThread(TRUE);

    mgr.StartWinThread(t1, WorkerFuncA, NULL);
    mgr.StartWinThread(t2, WorkerFuncB, NULL);

    printf("스레드 아이디  매니저의 0번 인덱스 ID = %d\n", (unsigned long)mgr.GetThreadIdByIndex(0));
    printf("스레드 아이디  매니저의 1번 인덱스 ID = %d\n", (unsigned long)mgr.GetThreadIdByIndex(1));

    mgr.ExitWaitAll();
    mgr.CloseAll();
    return 0;
}
