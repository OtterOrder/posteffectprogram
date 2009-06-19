#include	"RenderTarget.h"
#include	<assert.h>

//----------------------------------------------------------------------------------------------
RenderTarget::RenderTarget(void)
{
	m_pSurface = NULL;
	m_pTexture = NULL;
}

RenderTarget::RenderTarget(u32 _width, u32 _height)
{
	m_pSurface = NULL;
	m_pTexture = NULL;

	m_width  = _width;
	m_height = _height;
}

//----------------------------------------------------------------------------------------------
RenderTarget::~RenderTarget(void)
{
	Release();
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------
HRESULT RenderTarget::Create (PDevice _pDevice)
{
	assert (_pDevice);

	Release ();

	HRESULT result = D3DXCreateTexture(	_pDevice,
										m_width,
										m_height,
										1,
										D3DUSAGE_RENDERTARGET,
										D3DFMT_A8R8G8B8,
										D3DPOOL_DEFAULT,
										&m_pTexture );

	assert(m_pTexture);

	m_pTexture->GetSurfaceLevel(0, &m_pSurface);

	return result;
}

void RenderTarget::operator = (const RenderTarget& _RenderTarget)
{
	m_width		= _RenderTarget.m_width;
	m_height	= _RenderTarget.m_height;

	m_pSurface	= _RenderTarget.m_pSurface;
	m_pTexture	= _RenderTarget.m_pTexture;
}