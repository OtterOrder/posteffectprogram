#include	"PostRenderer.h"

//----------------------------------------------------------------------------------------------
PostRenderer::PostRenderer(void)
{
	m_pBackBuffer				= NULL;

	m_pFrontRenderTarget		= NULL;
	m_pBackRenderTarget			= NULL;

	/*
	MotionBlur* pMotionBlur = new MotionBlur();
	m_pPostEffects.push_back(pMotionBlur);
	*/

	m_PostEffects = 0;

	m_GBuffer = NULL;
}

//----------------------------------------------------------------------------------------------
PostRenderer::~PostRenderer(void)
{
	for (u32 postEffect = 0; postEffect < m_pPostEffects.size(); postEffect++)
	{
		if (m_pPostEffects[postEffect])
			delete m_pPostEffects[postEffect];
	}
}

//----------------------------------------------------------------------------------------------
void PostRenderer::DestroyPostPorcesses ()
{
	for (u32 postEffect = 0; postEffect < m_pPostEffects.size(); postEffect++)
	{
		if (m_pPostEffects[postEffect])
			m_pPostEffects[postEffect]->Destroy();
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
void PostRenderer::SetBackBuffer (PSurface _pBackBuffer)
{
	assert(_pBackBuffer);
	m_pBackBuffer = _pBackBuffer;
}

//----------------------------------------------------------------------------------------------
void PostRenderer::RenderPostEffects ()
{
	m_pDevice->BeginScene();

	for (u32 postEffect = 0; postEffect < m_pPostEffects.size(); postEffect++)
	{
		if (m_pPostEffects[postEffect] && ((m_PostEffects & (1<<postEffect)) == 1<<postEffect))
			m_pPostEffects[postEffect]->Apply();
	}

	if (! (m_pFrontRenderTarget && m_pBackBuffer))
		return;

	m_pDevice->StretchRect(m_pFrontRenderTarget->GetSurface(), NULL, m_pBackBuffer, &m_ScreenRect, D3DTEXF_NONE);

	m_pDevice->EndScene();
}

//----------------------------------------------------------------------------------------------
void PostRenderer::Release ()
{
	SAFE_DELETE(m_pFrontRenderTarget);

	SAFE_DELETE(m_pBackRenderTarget);

	SAFE_RELEASE(m_pBackBuffer);

	for (u32 postEffect = 0; postEffect < m_pPostEffects.size(); postEffect++)
	{
		if (m_pPostEffects[postEffect])
			m_pPostEffects[postEffect]->Release();
	}
}

//----------------------------------------------------------------------------------------------
HRESULT PostRenderer::Create (PDevice _pDevice, u32 _width, u32 _height)
{
	assert (_pDevice);
	m_pDevice = _pDevice;
	m_ScreenSize = Vector2i(_width, _height);

	m_ScreenRect.left		= 0;
	m_ScreenRect.top		= 0;
	m_ScreenRect.right		= m_ScreenSize.x;
	m_ScreenRect.bottom		= m_ScreenSize.y;

	SAFE_NEW(m_pFrontRenderTarget, RenderTarget);
	if (FAILED(m_pFrontRenderTarget->Create(m_pDevice, m_ScreenSize) ))
		return E_FAIL;

	SAFE_NEW(m_pBackRenderTarget, RenderTarget);
	if (FAILED(m_pBackRenderTarget->Create(m_pDevice, m_ScreenSize) ))
		return E_FAIL;

	for (u32 postEffect = 0; postEffect < m_pPostEffects.size(); postEffect++)
	{
		if (m_pPostEffects[postEffect])
			m_pPostEffects[postEffect]->Create(m_pDevice, m_ScreenSize);
	}

	return S_OK;
}

//----------------------------------------------------------------------------------------------
void PostRenderer::SwapSceneRender ()
{
	RenderTarget* _tempRT	= m_pFrontRenderTarget;
	m_pFrontRenderTarget	= m_pBackRenderTarget;
	m_pBackRenderTarget		= _tempRT;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
void PostRenderer::SetRenderTarget (PSurface _pRenderTarget)
{
	if (!_pRenderTarget)
		return;

	m_pDevice->SetRenderTarget(0, _pRenderTarget);
}

//----------------------------------------------------------------------------------------------
PSurface PostRenderer::GetRenderTarget ()
{
	PSurface pRenderTarget = NULL;
	m_pDevice->GetRenderTarget(0, &pRenderTarget);
	return pRenderTarget;
}

//----------------------------------------------------------------------------------------------
void PostRenderer::SetRenderTarget (u32 _level, PSurface _pRenderTarget)
{
	if (!_pRenderTarget)
		return;

	m_pDevice->SetRenderTarget(_level, _pRenderTarget);
}

//----------------------------------------------------------------------------------------------
PSurface PostRenderer::GetRenderTarget (u32 _level)
{
	PSurface pRenderTarget = NULL;
	m_pDevice->GetRenderTarget(_level, &pRenderTarget);
	return pRenderTarget;
}