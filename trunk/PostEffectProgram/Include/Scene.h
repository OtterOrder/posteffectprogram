#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Types.h"
#include "GraphicEntity.h"

#include <vector>
using namespace std;

class Scene
{
	vector<GraphicEntity*>	m_pEntitiesList;
	//vector<*Light>			m_pLightsList;

public:
	Scene ()	{};
	~Scene ()	{};

	GraphicEntity*	CreateGraphicEntity ();
	//Light*			CreateLight ();

	void			DeleteGraphicObject (GraphicEntity* _pGraphicEntity);
	//void			DeleteLight (Light* _pLight);
};