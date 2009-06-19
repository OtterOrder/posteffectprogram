
#include "GBufferRenderer.h"
#include "Scene.h"


GBufferRenderer::GBufferRenderer()
{

}

GBufferRenderer::~GBufferRenderer()
{

}


void GBufferRenderer::RenderScene()
{
	ComputeMatrices();			// Matrices de transformation de l'objet
	RenderGBufferPass();	    // Rendu dans le GBuffer
}

void GBufferRenderer::ComputeMatrices()
{

}

void GBufferRenderer::RenderGBufferPass()
{

	Render();

}




void GBufferRenderer::Render()
{

}
