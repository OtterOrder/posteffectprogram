
#include "GBufferRenderer.h"
#include "Scene.h"
#include "GraphicEntity.h"



GBufferRenderer::GBufferRenderer()
{
	m_fZNear=0.5f;
	m_fZFar=300.f;
}

GBufferRenderer::~GBufferRenderer()
{

}

void GBufferRenderer::SetScene(Scene *_scene)
{
	m_pScene=_scene;
	m_pEntityList=m_pScene->GetGraphicEntityList();
}

void GBufferRenderer::Init(PDevice _Device, u32 _width, u32 _height)
{
	m_pDevice=_Device;
	m_BackBufferWidth=_width;
	m_BackBufferHeight=_height;

	m_Camera.SetProjParams(D3DX_PI/4, (float)_width/_height, m_fZNear, m_fZFar);
	m_Camera.SetViewParams(&D3DXVECTOR3(-100.f, 100.f, -100.f), &D3DXVECTOR3(0.f, 0.f, 0.f));

	// Initialisation shader
	m_GRendererMaterial.SetShader(m_pDevice, "..\\Datas\\Shaders\\VSGbuffer.vsh", "VSTest", "..\\Datas\\Shaders\\PSGbuffer.psh", "PSTextureDisplay");

	// Initialisation Render target
	m_GBuffer.m_pRTSceneDiffuseMap.Create(m_pDevice, Vector2i(_width, _height));
	m_GBuffer.m_pRTSceneNormalMap.Create(m_pDevice, Vector2i(_width, _height));
	m_GBuffer.m_pRTDepthMap.Create(m_pDevice, Vector2i(_width, _height));
	m_pDevice->CreateDepthStencilSurface( _width, _height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pShadowDepth, NULL );

}


void GBufferRenderer::RenderScene()
{
	m_Camera.FrameMove(m_Timer.GetDeltaTime());

	if(SUCCEEDED(m_pDevice->BeginScene()))
	{
		m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,125), 1.0f, 0 );

		RenderGBufferPass();	    // Rendu dans le GBuffer

		m_pDevice->EndScene();
	}

	m_pDevice->Present( NULL, NULL, NULL, NULL );

	m_Timer.EndF();
	m_Timer.EndE();
}

void GBufferRenderer::ComputeMatrices(Matrix _world)
{
	GraphicEntity::Iterator GEntityIt;
	Matrix viewProj, WorldViewProj;
	MatrixMultiply(&viewProj, m_Camera.GetViewMatrix(), m_Camera.GetProjMatrix());
	MatrixMultiply(&WorldViewProj, &_world, &viewProj);
	m_GRendererMaterial.m_pShader->SetVSMatrix(m_pDevice, "g_mWorld", _world);
	m_GRendererMaterial.m_pShader->SetVSMatrix(m_pDevice, "g_mWorldViewProjection", WorldViewProj);
	m_GRendererMaterial.m_pShader->SetPSFloat(m_pDevice, "g_fZNear", m_fZNear);
	m_GRendererMaterial.m_pShader->SetPSFloat(m_pDevice, "g_fZFar", m_fZFar);
	
}

void GBufferRenderer::RenderGBufferPass()
{

	// Assignation des render target
	m_pDevice->SetRenderTarget(0, m_GBuffer.m_pRTSceneDiffuseMap.GetSurface());
	m_pDevice->SetRenderTarget(1, m_GBuffer.m_pRTSceneNormalMap.GetSurface());
	m_pDevice->SetRenderTarget(2, m_GBuffer.m_pRTDepthMap.GetSurface());

	m_pDevice->GetDepthStencilSurface( &m_pOldDepthRT );
	m_pDevice->SetDepthStencilSurface( m_pShadowDepth );

	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,125), 1.0f, 0 );
	Render();

	D3DXSaveTextureToFile("testdiff.bmp", D3DXIFF_BMP, m_GBuffer.m_pRTSceneDiffuseMap.GetTexture(), NULL);
	D3DXSaveTextureToFile("testnormal.bmp", D3DXIFF_BMP, m_GBuffer.m_pRTSceneNormalMap.GetTexture(), NULL);
	D3DXSaveTextureToFile("testz.bmp", D3DXIFF_BMP, m_GBuffer.m_pRTDepthMap.GetTexture(), NULL);

	// Désactivation render target
	PSurface pd3dBackBufferSurface;
	m_pDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO, &pd3dBackBufferSurface);
	m_pDevice->SetRenderTarget(0,pd3dBackBufferSurface);
	pd3dBackBufferSurface->Release();
	m_pDevice->SetRenderTarget(1, NULL);
	m_pDevice->SetRenderTarget(2, NULL);
	m_pDevice->SetDepthStencilSurface( m_pOldDepthRT );
	SAFE_RELEASE( m_pOldDepthRT );

}

void GBufferRenderer::Render()
{
	GraphicEntity::Iterator GEntityIt;
	for(GEntityIt=m_pEntityList->begin();  GEntityIt != m_pEntityList->end(); GEntityIt++)
	{
		// Récupération des textures des matériaux respectifs à chaque entités
		m_GRendererMaterial.m_pDiffuseMap=(*GEntityIt)->GetMaterial()->m_pDiffuseMap;
		m_GRendererMaterial.m_pNormalMap=(*GEntityIt)->GetMaterial()->m_pNormalMap;;
		m_GRendererMaterial.Apply(m_pDevice);
		ComputeMatrices((*GEntityIt)->GetWorldMatrix());
		(*GEntityIt)->DrawWithoutMaterial(m_pDevice);
		m_GRendererMaterial.m_pDiffuseMap=NULL;
		m_GRendererMaterial.m_pNormalMap=NULL;
	}
}

void GBufferRenderer::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	m_Camera.HandleMessages(hWnd, msg, wParam, lParam);
}

void GBufferRenderer::Release()
{
	m_GBuffer.m_pRTSceneDiffuseMap.Release();
	m_GBuffer.m_pRTSceneNormalMap.Release();
	m_GBuffer.m_pRTDepthMap.Release();
	SAFE_RELEASE(m_pShadowDepth);
}

