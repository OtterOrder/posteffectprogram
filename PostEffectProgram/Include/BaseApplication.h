#pragma once

#include "GBufferRenderer.h"

class BaseApplication
{
public:

	void Run();

	void Exit();

protected:
	BaseApplication();
	~BaseApplication();

private:

	void MakeWindow();

	void MainLoop();

	virtual void OnInitialize() = 0;

	virtual void OnUpdate() = 0;

	static LRESULT CALLBACK GlobalWindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);

	LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);

	//----------------------------------------------------------
	// Données membres
	//----------------------------------------------------------

	GBufferRenderer*		m_Renderer;		//Instance sur le renderer
	HINSTANCE				m_Instance;
	HWND					m_Hwnd;
	bool					m_IsRunning;
	u32						m_WindowWidth;
	u32						m_WindowHeight;
	static BaseApplication* m_App;			// Pointeur sur l'instance de l'application

};