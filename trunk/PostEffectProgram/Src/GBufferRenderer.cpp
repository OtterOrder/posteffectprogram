
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

void GBufferRenderer::Setup()
{
	m_pScene = Scene::GetSingleton();
	m_pEntityList=m_pScene->GetGraphicEntityList();

	m_Camera.SetProjParams(D3DX_PI/4, (float)m_BackBufferSize.x/m_BackBufferSize.y, m_fZNear, m_fZFar);
	m_Camera.SetViewParams(&D3DXVECTOR3(-100.f, 100.f, -100.f), &D3DXVECTOR3(0.f, 0.f, 0.f));

	// Initialisation shader
	m_GRendererMaterial.SetShader("..\\Datas\\Shaders\\VSGbuffer.vsh", "VSTest", "..\\Datas\\Shaders\\PSGbuffer.psh", "PSTextureDisplay");

	// Initialisation Render target
	m_GBuffer.m_pRTSceneDiffuseMap.Create(m_BackBufferSize);
	m_GBuffer.m_pRTSceneNormalMap.Create(m_BackBufferSize);
	m_GBuffer.m_pRTDepthMap.Create(m_BackBufferSize, D3DFMT_R32F);
	m_pd3dDevice->CreateDepthStencilSurface( m_BackBufferSize.x, m_BackBufferSize.y, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pShadowDepth, NULL );
}


void GBufferRenderer::RenderScene()
{
	m_Camera.FrameMove(m_Timer.GetDeltaTime());

	if(SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,125), 1.0f, 0 );

		RenderGBufferPass();	    // Rendu dans le GBuffer

		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	m_Timer.EndF();
	m_Timer.EndE();
}

void GBufferRenderer::ComputeMatrices(Matrix _world)
{
	GraphicEntity::Iterator GEntityIt;
	Matrix viewProj, WorldViewProj;
	MatrixMultiply(&viewProj, m_Camera.GetViewMatrix(), m_Camera.GetProjMatrix());
	MatrixMultiply(&WorldViewProj, &_world, &viewProj);
	m_GRendererMaterial.m_pShader->SetVSMatrix("g_mWorldViewProjection", WorldViewProj);
	m_GRendererMaterial.m_pShader->SetPSFloat("g_fZNear", m_fZNear);
	m_GRendererMaterial.m_pShader->SetPSFloat("g_fZFar", m_fZFar);
}

void GBufferRenderer::RenderGBufferPass()
{

	// Assignation des render target
	m_pd3dDevice->SetRenderTarget(0, m_GBuffer.m_pRTSceneDiffuseMap.GetSurface());
	m_pd3dDevice->SetRenderTarget(1, m_GBuffer.m_pRTSceneNormalMap.GetSurface());
	m_pd3dDevice->SetRenderTarget(2, m_GBuffer.m_pRTDepthMap.GetSurface());

	m_pd3dDevice->GetDepthStencilSurface( &m_pOldDepthRT );
	m_pd3dDevice->SetDepthStencilSurface( m_pShadowDepth );

	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,125), 1.0f, 0 );
	Render();

	D3DXSaveTextureToFile("testdiff.bmp", D3DXIFF_BMP, m_GBuffer.m_pRTSceneDiffuseMap.GetTexture(), NULL);
	D3DXSaveTextureToFile("testnormal.bmp", D3DXIFF_BMP, m_GBuffer.m_pRTSceneNormalMap.GetTexture(), NULL);
	D3DXSaveTextureToFile("testz.bmp", D3DXIFF_BMP, m_GBuffer.m_pRTDepthMap.GetTexture(), NULL);

	// Désactivation render target
	PSurface pd3dBackBufferSurface;
	m_pd3dDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO, &pd3dBackBufferSurface);
	m_pd3dDevice->SetRenderTarget(0,pd3dBackBufferSurface);
	pd3dBackBufferSurface->Release();
	m_pd3dDevice->SetRenderTarget(1, NULL);
	m_pd3dDevice->SetRenderTarget(2, NULL);
	m_pd3dDevice->SetDepthStencilSurface( m_pOldDepthRT );
	SAFE_RELEASE( m_pOldDepthRT );
}

void GBufferRenderer::Render()
{
	GraphicEntity::Iterator GEntityIt;
	for(GEntityIt=m_pEntityList->begin();  GEntityIt != m_pEntityList->end(); GEntityIt++)
	{
		// Récupération des textures des matériaux respectifs à chaque entités
		m_GRendererMaterial.m_pDiffuseMap=(*GEntityIt)->GetMaterial()->m_pDiffuseMap;
		m_GRendererMaterial.m_pNormalMap=(*GEntityIt)->GetMaterial()->m_pNormalMap;
		m_GRendererMaterial.m_pSpecularMap=(*GEntityIt)->GetMaterial()->m_pSpecularMap;
		m_GRendererMaterial.Apply();
		ComputeMatrices((*GEntityIt)->GetWorldMatrix());
		(*GEntityIt)->DrawWithoutMaterial();
		m_GRendererMaterial.m_pDiffuseMap=NULL;
		m_GRendererMaterial.m_pNormalMap=NULL;
		m_GRendererMaterial.m_pSpecularMap=NULL;
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

