
#include "GBufferRenderer.h"
#include "Scene.h"
#include "GraphicEntity.h"



GBufferRenderer::GBufferRenderer()
{
	m_Camera.SetProjParams(D3DX_PI/4, (float)800/600, 0.1f, 100.f);
}

GBufferRenderer::~GBufferRenderer()
{

}

void GBufferRenderer::SetScene(Scene *_scene)
{
	m_pScene=_scene;
	m_pEntityList=m_pScene->GetGraphicEntityList();
}

void GBufferRenderer::Init(PDevice _Device)
{
	m_pDevice=_Device;
	m_GRendererMaterial.SetShader(m_pDevice, "..\\Datas\\Shaders\\VSTest.vsh", "VSTest", "..\\Datas\\Shaders\\PSTest.psh", "PSTextureDisplay");
}


void GBufferRenderer::RenderScene()
{
	RenderGBufferPass();	    // Rendu dans le GBuffer
}

void GBufferRenderer::ComputeMatrices(Matrix _world)
{
	GraphicEntity::Iterator GEntityIt;
	Matrix viewProj, WorldViewProj;
	MatrixMultiply(&viewProj, m_Camera.GetViewMatrix(), m_Camera.GetProjMatrix());
	MatrixMultiply(&WorldViewProj, &_world, &viewProj);
	m_GRendererMaterial.m_pShader->SetVSMatrix(m_pDevice, "g_mWorldViewProjection", WorldViewProj);

	// SetMatrix
	
}

void GBufferRenderer::RenderGBufferPass()
{

	// Assignation des render targer

	// Assignation du shader
	Render();

}

void GBufferRenderer::Render()
{

	m_Camera.FrameMove(m_Timer.GetDeltaTimeF());

    m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,125), 1.0f, 0 );

	m_pDevice->BeginScene();

	GraphicEntity::Iterator GEntityIt;
	for(GEntityIt=m_pEntityList->begin();  GEntityIt != m_pEntityList->end(); GEntityIt++)
	{
		m_GRendererMaterial.m_pDiffuseMap=(*GEntityIt)->GetMaterial()->m_pDiffuseMap;
		m_GRendererMaterial.m_pNormalMap=(*GEntityIt)->GetMaterial()->m_pNormalMap;;
		m_GRendererMaterial.Apply(m_pDevice);
		ComputeMatrices((*GEntityIt)->GetWorldMatrix());
		(*GEntityIt)->DrawWithoutMaterial(m_pDevice);
		
	}

	m_pDevice->EndScene();

	m_pDevice->Present( NULL, NULL, NULL, NULL );

	m_Timer.EndF();
	m_Timer.EndE();

}
