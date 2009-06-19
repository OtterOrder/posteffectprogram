#pragma once

#include "GraphicEntity.h"
#include <list>


class GBufferRenderer
{
public:
	GBufferRenderer() {}
	~GBufferRenderer() {}

	struct GBuffer
	{
		IDirect3DTexture9* m_pRTSceneNormalMap;
		IDirect3DTexture9* m_pRTSceneDiffuseMap;
		IDirect3DTexture9* m_pRTDepthMap;
	};

	
	void RenderScene(){}


protected:

	void ComputeMatrices() {}

	// Scene

private:


};