#pragma once

#include <d3dx9.h>
#include "Singleton.h"
#include "Misc.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	HRESULT Initialize(HWND Hwnd);
	HRESULT Destroy();

	u32	 GetBackbufferWidth(){ return m_BackBufferWidth; }
	u32	 GetBackbufferHeight(){ return m_BackBufferHeight; }

	static inline PDevice GetDevice() { return m_pd3dDevice; }

protected:

	virtual void Setup() = 0 ;
	virtual void Release() = 0 ;

	HWND					m_hWnd;
	LPDIRECT3D9             m_pD3D; 
	static PDevice			m_pd3dDevice;

	u32						m_BackBufferWidth;
	u32						m_BackBufferHeight;
};