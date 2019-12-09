#pragma once
#ifndef CTHREAD_H_
#define CTHREAD_H_

#include <windows.h>

// ��װ���߳���
class CThread
{
public:
	CThread()
		: m_bStopped(false)
	{
		m_hThread = CreateThread(NULL, 0, StartRoutine, this, CREATE_SUSPENDED, &m_nId);
	}

	virtual ~CThread()
	{
		if (m_hThread) {
			CloseHandle(m_hThread);
		}
	}

protected:
	// ִ�к���������Ӧ��ʵ����������������߳�ʲôҲ����
	virtual void Run()
	{
	}

public:
	// ��ʼִ���߳�
	virtual void Start()
	{
		ResumeThread(m_hThread);
	}

	// �߳��Ƿ�ֹͣ
	bool Stopped()
	{
		return m_bStopped;
	}


	void Join()
	{
		if (m_hThread) {
			WaitForSingleObject(m_hThread, INFINITE);
		}
	}

private:
	// �߳�ִ�е���ʼ��ַ��Ҳ���̺߳���
	static DWORD WINAPI StartRoutine(LPVOID param)
	{
		CThread* thread = (CThread*)param;
		thread->Run();
		thread->m_bStopped = true;
		return 0;
	}

private:
	HANDLE          m_hThread;      // �߳̾��
	bool            m_bStopped;     // �߳��Ƿ�ֹͣ
	DWORD           m_nId;          // �߳�ID
};

// ��װ�Ļ�������
class CMutex
{

public:
	CMutex()
	{
		// ������������
		m_hMutex = CreateMutex(NULL, FALSE, NULL);
	}
	~CMutex()
	{
		// �ͷŻ�������
		if (m_hMutex)
			CloseHandle(m_hMutex);
	}

public:
	// ��������ȡ����������������Դ
	bool Lock()
	{
		if (m_hMutex)
		{
			return WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0;
		}
		return false;
	}

	// ��ͼ������Դ���жϵ�ǰ�Ļ������Ƿ�ռ�á�
	// ����true˵������Ϊ��ռ��״̬���ɻ�ø���������false˵������Ϊռ��״̬����ȴ����ͷ�
	bool TryLock()
	{
		if (m_hMutex) {
			return WaitForSingleObject(m_hMutex, 0) == WAIT_OBJECT_0;
		}
		return false;
	}

	// �������ͷŻ�������
	void Unlock()
	{
		if (m_hMutex)
			ReleaseMutex(m_hMutex);
	}

private:
	HANDLE          m_hMutex;       // ���������
};

// ���������ĳ���
// ֻҪ�����ö���������Դ�����˳���(�ö���)������ʱ���ͷ���
class CLock
{
public:
	CLock(CMutex* mutex)
		: m_mutex(mutex)
	{
		m_bLocked = m_mutex->Lock();
	}

	~CLock()
	{
		if (m_bLocked)
			m_mutex->Unlock();
	}

private:
	// ���ø�ֵ������
	CLock& operator = (CLock&)
	{
		return *this;
	}

private:
	CMutex* m_mutex;        // ���������������
	bool            m_bLocked;      // �������Ƿ�����(ռ��)
};

#endif  // CTHREAD_H_