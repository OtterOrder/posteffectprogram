
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


void GBufferRenderer::RenderScene()
{
	ComputeMatrices();			// Matrices de transformation de l'objet
	RenderGBufferPass();	    // Rendu dans le GBuffer
}

void GBufferRenderer::ComputeMatrices()
{
	GraphicEntity::Iterator GEntityIt;
	D3DXMATRIX viewProj, WorldViewProj;
	D3DXMatrixMultiply(&viewProj, m_Camera.GetViewMatrix(), m_Camera.GetProjMatrix());

	for(GEntityIt=m_pEntityList->begin();  GEntityIt != m_pEntityList->end(); GEntityIt++)
	{	
		D3DXMatrixMultiply(&WorldViewProj, &(*GEntityIt)->GetWorldMatrix(), &viewProj);
	}
	
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

	GraphicEntity::Iterator GEntityIt;
	for(GEntityIt=m_pEntityList->begin();  GEntityIt != m_pEntityList->end(); GEntityIt++)
	{
	//	(*GEntityIt)->Draw();
	}

	m_Timer.EndF();

}
