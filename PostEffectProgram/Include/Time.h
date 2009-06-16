#pragma once

#include	<windows.h>

class Time
{
public:

	Time();
	~Time();

	// =========================================================
	// M�thodes publiques

	inline float GetDeltaTime() { return m_DeltaTime; }		// Temps �coul� depuis le dernier tour moteur (s)
	inline float GetDeltaTimeF() { return m_DeltaTimeF; }	// Temps �coul� depuis la derni�re frame (s)
	float GetTime();										// Temps depuis la cr�ation du System (s)

	float GetDeltaTimeMs();
	float GetDeltaTimeFMs();
	float GetTimeMs();

	void EndE();	// Fin d'un tour moteur (System)
	void EndF();	// Fin d'une frame (System)

protected:

	// =========================================================
	// Donn�es prot�g�es

	float			m_Freq;
	LARGE_INTEGER	m_TimeStart;
	LARGE_INTEGER	m_StartDeltaTime;
	float			m_DeltaTime;
	float			m_DeltaTimeF;

};
