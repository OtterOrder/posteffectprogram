#pragma once

#include	<windows.h>

class Time
{
public:

	Time();
	~Time();

	// =========================================================
	// Méthodes publiques

	inline float GetDeltaTime() { return m_DeltaTime; }		// Temps écoulé depuis le dernier tour moteur (s)
	inline float GetDeltaTimeF() { return m_DeltaTimeF; }	// Temps écoulé depuis la dernière frame (s)
	float GetTime();										// Temps depuis la création du System (s)

	float GetDeltaTimeMs();
	float GetDeltaTimeFMs();
	float GetTimeMs();

	void EndE();	// Fin d'un tour moteur (System)
	void EndF();	// Fin d'une frame (System)

protected:

	// =========================================================
	// Données protégées

	float			m_Freq;
	LARGE_INTEGER	m_TimeStart;
	LARGE_INTEGER	m_StartDeltaTime;
	float			m_DeltaTime;
	float			m_DeltaTimeF;

};
