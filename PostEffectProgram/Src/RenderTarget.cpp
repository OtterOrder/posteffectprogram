#include	"RenderTarget.h"
#include	<assert.h>

//******************************************************************************************************************************
RenderTarget::RenderTarget(void)
{
	m_pSurface = NULL;
	m_pTexture = NULL;
}

//******************************************************************************************************************************
RenderTarget::~RenderTarget(void)
{
	Release();
}

//******************************************************************************************************************************
void RenderTarget::Release ()
{
	if (m_pSurface)
	{
		m_pSurface->Release();
		m_pSurface = NULL;
	}

	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//******************************************************************************************************************************
HRESULT RenderTarget::Create (PDevice _pDevice, Vector2i _size, Format _format)
{
	assert (_pDevice);

	Release ();

	HRESULT result = D3DXCreateTexture(	_pDevice,
										_size.x,
										_size.y,
										1,
										D3DUSAGE_RENDERTARGET,
										_format,
										D3DPOOL_DEFAULT,
										&m_pTexture );

	assert(m_pTexture);

	m_pTexture->GetSurfaceLevel(0, &m_pSurface);

	return result;
}

//******************************************************************************************************************************
void RenderTarget::operator = (const RenderTarget& _RenderTarget)
{
	m_Size = _RenderTarget.m_Size;

	m_pSurface	= _RenderTarget.m_pSurface;
	m_pTexture	= _RenderTarget.m_pTexture;
}