
// ������ ���� ���� CMobleThread ,  CMobleThreadMgr Ŭ������ �ּ��� �޾ƺ��ų�
// �Ǵ� �ڽŸ��� Thread Wrapping  Ŭ������ ����� ������
// �ϼ��� �л��� slack ����-���� �� �÷� �ּ���
// ���� �˻� ����, ������ ����? ������ 2025/09/09 ���� 10�ñ���
// ������ �ͼ� �ٸ� �л� ���⺻ ���� �ؼ� ���� ���� 09/09�� �����׽�Ʈ�� ������ ��ü �մϴ�
// �ٸ� �л��� ���⺻ ���� �Ͽ��� ��� ��ó ǥ��!
// ���� ������ ���� ������ ����
// â�Ƿ� ������ ����, �ڵ� �ٸ��� ������ ����, ���� �̸� ���ϼ� ������ ����
// �� �ٸ� �л� ���⺻�� �ڵ带 �ٸ��� �Ǵ� �����̸� ��������� �������� ���� �� �� ����
// �ڵ� �ٸ���, �����̸� ���ϼ����� �ְ����� �������� ä�� ( ��! �α� ���⺻(��ó�� ���� ���� ���⺻)��  ����� �ݿ��� ����)
// �α� ���⺻�� ������ �л��� ������ ����
// �ڵ�� �ܼ��ϰ�(������) �������̰� �ۼ�

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

    printf("������ ���̵�  �Ŵ����� 0�� �ε��� ID = %d\n", (unsigned long)mgr.GetThreadIdByIndex(0));
    printf("������ ���̵�  �Ŵ����� 1�� �ε��� ID = %d\n", (unsigned long)mgr.GetThreadIdByIndex(1));

    mgr.ExitWaitAll();
    mgr.CloseAll();
    return 0;
}
