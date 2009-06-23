#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Types.h"
#include "GraphicEntity.h"
#include "Light.h"

#include <vector>
using namespace std;

class Scene
{
	vector<GraphicEntity*>	m_pEntitiesList;
	vector<Light*>			m_pLightsList;

public:
	Scene ()	{};
	~Scene ();

	void	Destroy ();

	GraphicEntity*	CreateGraphicEntity ();
	Light*			CreateLight (Light::Type _type);

	void			DeleteGraphicEntity (GraphicEntity* _pGraphicEntity);
	void			DeleteLight (Light* _pLight);

	vector<GraphicEntity*>*		GetGraphicEntityList ()		{ return &m_pEntitiesList; };
	vector<Light*>*				GetLightList ()				{ return &m_pLightsList; };
};