
#include "Renderer.h"

PDevice Renderer::m_pd3dDevice = NULL;

Renderer::Renderer()
{
	m_BackBufferSize = Vector2i(800, 600);

	m_pD3D = NULL;
}

Renderer::~Renderer()
{

}

HRESULT Renderer::Initialize(HWND Hwnd)
{
	m_hWnd=Hwnd;

	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth  = m_BackBufferSize.x;
	d3dpp.BackBufferHeight = m_BackBufferSize.y;
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
		&d3dpp, &m_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE);

	Setup();

	return S_OK;

}

HRESULT Renderer::Destroy()
{
	Release();

	SAFE_RELEASE(m_pd3dDevice);

	SAFE_RELEASE(m_pD3D);

	return S_OK;
}