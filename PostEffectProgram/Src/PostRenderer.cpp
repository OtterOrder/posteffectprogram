#include	"PostRenderer.h"

//----------------------------------------------------------------------------------------------
PostRenderer::PostRenderer(void)
{
	m_pBackBuffer				= NULL;

	m_pFrontRenderTarget		= NULL;
	m_pBackRenderTarget			= NULL;

	m_pPostProcesses.push_back(new DefferedLighting());

	m_PostProcesses = 0;

	m_GBuffer = NULL;
}

//----------------------------------------------------------------------------------------------
PostRenderer::~PostRenderer(void)
{
	for (u32 postEffect = 0; postEffect < m_pPostProcesses.size(); postEffect++)
	{
		if (m_pPostProcesses[postEffect])
			delete m_pPostProcesses[postEffect];
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
HRESULT PostRenderer::Initialize (Vector2i _size)
{
	m_ScreenSize = _size;

	m_ScreenQuad.Create(m_ScreenSize);

	m_ScreenRect.left		= 0;
	m_ScreenRect.top		= 0;
	m_ScreenRect.right		= m_ScreenSize.x;
	m_ScreenRect.bottom		= m_ScreenSize.y;

	SAFE_NEW(m_pFrontRenderTarget, RenderTarget);
	if (FAILED(m_pFrontRenderTarget->Create(m_ScreenSize) ))
		return E_FAIL;

	SAFE_NEW(m_pBackRenderTarget, RenderTarget);
	if (FAILED(m_pBackRenderTarget->Create(m_ScreenSize) ))
		return E_FAIL;

	for (u32 postEffect = 0; postEffect < m_pPostProcesses.size(); postEffect++)
	{
		if (m_pPostProcesses[postEffect])
			m_pPostProcesses[postEffect]->Create(m_ScreenSize);
	}

	getDevice->GetRenderTarget(0 , &m_pBackBuffer);

	return S_OK;
}

//----------------------------------------------------------------------------------------------
void PostRenderer::Release ()
{
	SAFE_DELETE(m_pFrontRenderTarget);

	SAFE_DELETE(m_pBackRenderTarget);

	SAFE_RELEASE(m_pBackBuffer);

	for (u32 postEffect = 0; postEffect < m_pPostProcesses.size(); postEffect++)
	{
		if (m_pPostProcesses[postEffect])
			m_pPostProcesses[postEffect]->Release();
	}

	m_ScreenQuad.Release ();
}

//----------------------------------------------------------------------------------------------
void PostRenderer::Destroy ()
{
	for (u32 postEffect = 0; postEffect < m_pPostProcesses.size(); postEffect++)
	{
		if (m_pPostProcesses[postEffect])
			m_pPostProcesses[postEffect]->Destroy();
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
void PostRenderer::RenderPostProcesses ()
{
	getDevice->BeginScene();

	for (u32 postProcess = 0; postProcess < m_pPostProcesses.size(); postProcess++)
	{
		if (m_pPostProcesses[postProcess] && ((m_PostProcesses & (1<<postProcess)) == 1<<postProcess))
			m_pPostProcesses[postProcess]->Apply();
	}

	if (! (m_pFrontRenderTarget && m_pBackBuffer))
		return;

	getDevice->StretchRect(m_pFrontRenderTarget->GetSurface(), NULL, m_pBackBuffer, &m_ScreenRect, D3DTEXF_NONE);

	getDevice->EndScene();
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

	getDevice->SetRenderTarget(0, _pRenderTarget);
}

//----------------------------------------------------------------------------------------------
PSurface PostRenderer::GetRenderTarget ()
{
	PSurface pRenderTarget = NULL;
	getDevice->GetRenderTarget(0, &pRenderTarget);
	return pRenderTarget;
}

//----------------------------------------------------------------------------------------------
void PostRenderer::SetRenderTarget (u32 _level, PSurface _pRenderTarget)
{
	if (!_pRenderTarget)
		return;

	getDevice->SetRenderTarget(_level, _pRenderTarget);
}

//----------------------------------------------------------------------------------------------
PSurface PostRenderer::GetRenderTarget (u32 _level)
{
	PSurface pRenderTarget = NULL;
	getDevice->GetRenderTarget(_level, &pRenderTarget);
	return pRenderTarget;
}