#include	"Time.h"

//******************************************************************

Time::Time()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency( &freq );
	QueryPerformanceCounter( &m_TimeStart );

	m_Freq				= (float)freq.QuadPart;
	m_StartDeltaTime	= m_TimeStart;
	m_DeltaTime			= 0.f;
	m_DeltaTimeF		= 0.f;
}

//******************************************************************

Time::~Time()
{
}

//******************************************************************

float Time::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter( &currentTime );
	return (float)(currentTime.QuadPart-m_TimeStart.QuadPart) / m_Freq;
}

//******************************************************************

float Time::GetDeltaTimeMs()
{
	return GetDeltaTime()*1000.f;
}

//******************************************************************

float Time::GetDeltaTimeFMs()
{
	return GetDeltaTimeF()*1000.f;
}

//******************************************************************

float Time::GetTimeMs()
{
	return GetTime()*1000.f;
}

//******************************************************************

void Time::EndE()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter( &currentTime );

	m_DeltaTime			= (float)(currentTime.QuadPart-m_StartDeltaTime.QuadPart) / m_Freq;
	m_StartDeltaTime	= currentTime;
	m_DeltaTimeF		+= m_DeltaTime;
}

//******************************************************************

void Time::EndF()
{
	m_DeltaTimeF = 0.f;
}
