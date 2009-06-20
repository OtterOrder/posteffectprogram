#pragma once

#include "Singleton.h"
#include "Types.h"
#include "Camera.h"
#include "Time.h"
#include <vector>
#include <d3d9.h>

class Scene;
class GraphicEntity;


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

	
	CFirstPersonCamera  GetCamera() {return m_Camera;}
	void				SetScene(Scene * _scene);		// Pour assigner une scène au GBufferRenderer
	void				RenderScene();					// Rendu de la scène appelé à chaque frames


private:

	void RenderGBufferPass();
	void ComputeMatrices();
	void Render();

	PDevice							m_pDevice;
	Scene*							m_pScene;			 // Scene 3d courante
	std::vector<GraphicEntity*>*	m_pEntityList;		 // Liste des objets de la scène courante
	CFirstPersonCamera 				m_Camera;			 // Camera FPS
	D3DXMATRIX						m_mProjection;		 // Matrice de projection	
	Time							m_Timer;


};