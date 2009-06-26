#include "Texture.h"

//******************************************************************************************************************************
Texture::Texture(void)
{
	m_pTexture = NULL;
}

//******************************************************************************************************************************
Texture::~Texture(void)
{
	Release ();
}

//******************************************************************************************************************************
void Texture::Release ()
{
	SAFE_RELEASE(m_pTexture);
}

//******************************************************************************************************************************
HRESULT Texture::Load (PDevice _pDevice, cStr _pFileName)
{
	Release();

	if( FAILED( D3DXCreateTextureFromFileEx(_pDevice,
											_pFileName,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											0,
											D3DFMT_A8R8G8B8,
											D3DPOOL_MANAGED,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											0,
											&m_TextureInfo,
											NULL,
											&m_pTexture ) ) )
	{
		m_pTexture = NULL;
		return E_FAIL;
	}

	return S_OK;
}