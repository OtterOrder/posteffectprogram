#pragma once

#include <d3dx9.h>

#include "Types.h"

class Texture
{
public:
	ImageInfo	m_TextureInfo;
	PTexture	m_pTexture;

	Texture(void);
	~Texture(void);

	void Release ();

	HRESULT LoadFromDdsFile (PDevice _pDevice, cStr _pFileName);
};
