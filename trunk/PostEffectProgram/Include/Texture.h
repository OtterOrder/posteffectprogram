#pragma once

#include <d3dx9.h>

#include "Misc.h"

class Texture
{
public:
	ImageInfo	m_TextureInfo;
	PTexture	m_pTexture;

	Texture(void);
	~Texture(void);

	void Release ();

	HRESULT Load (PDevice _pDevice, cStr _pFileName);
};
