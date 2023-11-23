#include "Timer.h"

CTimer::CTimer() 
	: m_fTimeDelta(0.f)
{
	ZeroMemory(&m_FrameTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_FixTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_LastTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}

HRESULT CTimer::Ready_Timer()
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceFrequency(&m_CpuTick);
	
	return S_OK;
}

_float CTimer::Compute_TimeDelta()
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}

	_float fTimeDelta = float(m_FrameTime.QuadPart - m_LastTime.QuadPart) / m_CpuTick.QuadPart;
	if (m_bSlow)
	{
		m_fAccSlow += fTimeDelta;
		if (m_fAccSlow >= m_fSlowRecovery)
		{
			m_fAccSlow = 0.f;
			m_fTimeScale = 1.f;
			m_bSlow = false;
		}

	}

	m_fTimeDelta = fTimeDelta * m_fTimeScale;

	m_LastTime = m_FrameTime;

	return m_fTimeDelta;
}



CTimer * CTimer::Create(void)
{
	CTimer*		pInstance = new CTimer;

	if (FAILED(pInstance->Ready_Timer()))
	{
		MSG_BOX("Timer Create Failed");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTimer::Free()
{
}
