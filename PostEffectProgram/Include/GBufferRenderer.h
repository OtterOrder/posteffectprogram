#pragma once

#include "Singleton.h"
#include "Misc.h"
#include "Time.h"

#include "Camera.h"
#include "RenderTarget.h"
#include "Material.h"

#include <vector>
#include <d3d9.h>

class Scene;
class GraphicEntity;


struct GBuffer
{
	RenderTarget m_pRTSceneDiffuseMap;
	RenderTarget m_pRTSceneNormalMap;
	RenderTarget m_pRTDepthMap;
};

class GBufferRenderer : public Singleton < GBufferRenderer >
{
public:
	GBufferRenderer();
	~GBufferRenderer();

	CFirstPersonCamera  GetCamera() {return m_Camera;}
	void				SetScene(Scene * _scene);		// Pour assigner une scène au GBufferRenderer
	void				Init(PDevice _Device, int _width, int _height);
	void				RenderScene();					// Rendu de la scène appelé à chaque frames
	void				Release();
	void				HandleMessage( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


private:

	void RenderGBufferPass();
	void ComputeMatrices(Matrix _world);
	void Render();

	PDevice							m_pDevice;
	Scene*							m_pScene;			 // Scene 3d courante
	Material						m_GRendererMaterial; // Matériau de rendu pour le GBuffer
	std::vector<GraphicEntity*>*	m_pEntityList;		 // Liste des objets de la scène courante
	CFirstPersonCamera 				m_Camera;			 // Camera FPS
	Matrix							m_mProjection;		 // Matrice de projection	
	Time							m_Timer;
	GBuffer							m_GBuffer;
	int								m_iBackBufferWidth;
	int								m_iBackBufferHeight;

	PSurface						m_pShadowDepth;
	PSurface						m_pOldDepthRT;
};