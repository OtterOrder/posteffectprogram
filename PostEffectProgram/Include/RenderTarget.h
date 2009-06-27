#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Misc.h"

class RenderTarget
{
	Vector2i m_Size;

	PTexture	m_pTexture;
	PSurface	m_pSurface;

public:
	RenderTarget(void);
	virtual ~RenderTarget(void);

	void Release ();
	HRESULT Create (Vector2i _size, Format _format = D3DFMT_A8R8G8B8);

	PTexture GetTexture ()	{ return m_pTexture; };
	PSurface GetSurface ()	{ return m_pSurface; };

	void operator = (const RenderTarget& _RenderTarget);
};