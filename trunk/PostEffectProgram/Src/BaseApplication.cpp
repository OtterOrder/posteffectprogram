
#include "BaseApplication.h"
#include <assert.h>

BaseApplication* BaseApplication::m_App = NULL;

BaseApplication::BaseApplication()
{

}

BaseApplication::~BaseApplication()
{
	if(m_Hwnd)
	{
		DestroyWindow(m_Hwnd);
		UnregisterClass( "PostEffectProgram", m_Instance );
	}
}

void BaseApplication::MakeWindow()
{
	m_WindowWidth  = 800;
	m_WindowHeight = 600;

	// Définition de la classe de la fenêtre
	WNDCLASSEX WindowClass;
	WindowClass.cbSize        = sizeof(WNDCLASSEX);
	WindowClass.style         = 0;
	WindowClass.lpfnWndProc   = GlobalWindowProc;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = m_Instance;
	WindowClass.hIcon         = NULL;
	WindowClass.hCursor       = 0;
	WindowClass.hbrBackground = 0;
	WindowClass.lpszMenuName  = NULL;
	WindowClass.lpszClassName = "PostEffectProgram";
	WindowClass.hIconSm       = NULL;
	RegisterClassEx(&WindowClass);

	// Création de la fenêtre
	m_Hwnd = CreateWindow("PostEffectProgram", "PostEffectProgram", WS_SYSMENU, 100, 100, m_WindowWidth, m_WindowHeight, NULL, NULL, m_Instance, NULL);
	assert(m_Hwnd != NULL);
	ShowWindow(m_Hwnd, SW_NORMAL);
}

void BaseApplication::Run()
{
	MakeWindow();

	m_Renderer = GBufferRenderer::GetSingleton();
	m_Renderer->Initialize(m_Hwnd, m_WindowWidth, m_WindowHeight);

	OnInitialize();

	MainLoop();

}

void BaseApplication::MainLoop()
{
	MSG Message;
	while (m_IsRunning)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// Traitement des messages Windows
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			// Mise à jour de la scène
			OnUpdate();

			// Rendu de la scène
			m_Renderer->RenderScene();
		}
	}

}

void BaseApplication::Exit()
{

}

LRESULT CALLBACK BaseApplication::GlobalWindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	return m_App->WindowProc(Hwnd, Message, WParam, LParam);
}

LRESULT CALLBACK BaseApplication::WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	/*switch (Message)
	{
	
	}*/

	return DefWindowProc(Hwnd, Message, WParam, LParam);
}