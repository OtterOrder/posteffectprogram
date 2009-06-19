#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Types.h"

class RenderTarget
{
	u32		m_width;
	u32		m_height;

	PTexture	m_pTexture;
	PSurface	m_pSurface;

public:
	RenderTarget(void);
	RenderTarget(u32 _width, u32 _height);
	virtual ~RenderTarget(void);

	void Release ();
	HRESULT Create (PDevice _pDevice);

	PTexture GetTexture ()	{ return m_pTexture; };
	PSurface GetSurface ()	{ return m_pSurface; };

	void operator = (const RenderTarget& _RenderTarget);
};