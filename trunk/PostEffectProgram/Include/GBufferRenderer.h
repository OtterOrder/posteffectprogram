#pragma once

#include "Singleton.h"
#include "Types.h"
#include "Camera.h"
#include <list>
#include <d3d9.h>

class Scene;


class GBufferRenderer : public Singleton < GBufferRenderer >
{
public:
	GBufferRenderer();
	~GBufferRenderer();

	struct GBuffer
	{
		PTexture m_pRTSceneNormalMap;
		PTexture m_pRTSceneDiffuseMap;
		PTexture m_pRTDepthMap;
	};

	
	void RenderScene();


protected:

	void RenderGBufferPass();
	void ComputeMatrices();
	void Render();

	Scene*					m_pScene;			 // Scene 3d
	CFirstPersonCamera 	    m_Camera;			 // Camera FPS


};