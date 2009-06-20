#pragma once

#include "Singleton.h"
#include "Misc.h"
#include "Time.h"

#include "Camera.h"
#include "RenderTarget.h"

#include <vector>
#include <d3d9.h>

class Scene;
class GraphicEntity;


struct GBuffer
{
	RenderTarget m_pRTSceneNormalMap;
	RenderTarget m_pRTSceneDiffuseMap;
	RenderTarget m_pRTDepthMap;
};

class GBufferRenderer : public Singleton < GBufferRenderer >
{
public:
	GBufferRenderer();
	~GBufferRenderer();

	CFirstPersonCamera  GetCamera() {return m_Camera;}
	void				SetScene(Scene * _scene);		// Pour assigner une sc�ne au GBufferRenderer
	void				RenderScene();					// Rendu de la sc�ne appel� � chaque frames


private:

	void RenderGBufferPass();
	void ComputeMatrices();
	void Render();

	PDevice							m_pDevice;
	Scene*							m_pScene;			 // Scene 3d courante
	std::vector<GraphicEntity*>*	m_pEntityList;		 // Liste des objets de la sc�ne courante
	CFirstPersonCamera 				m_Camera;			 // Camera FPS
	D3DXMATRIX						m_mProjection;		 // Matrice de projection	
	Time							m_Timer;


};