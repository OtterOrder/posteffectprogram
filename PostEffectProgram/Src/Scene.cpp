#include "Scene.h"

//******************************************************************************************************************************
GraphicEntity* Scene::CreateGraphicEntity ()
{
	m_pEntitiesList.push_back(new GraphicEntity());
	return m_pEntitiesList.back();
}

//******************************************************************************************************************************
/*
Light* Scene::CreateLight ()
{
	m_pEntitiesList.push_back(new Light());
	return m_pEntitiesList.back();
}
//*/

//******************************************************************************************************************************
void Scene::DeleteGraphicObject (GraphicEntity* _pGraphicEntity)
{
	GraphicEntity::Iterator GEntityIt;

	for (GEntityIt = m_pEntitiesList.begin(); GEntityIt != m_pEntitiesList.end(); GEntityIt++)
	{
		if (_pGraphicEntity == *GEntityIt)
		{
			SAFE_DELETE(_pGraphicEntity);
			m_pEntitiesList.erase(GEntityIt);
			return;
		}
	}
}

//******************************************************************************************************************************
/*
void Scene::DeleteLight (Light* _pLight)
{
	Light::Iterator LightIt;

	for (LightIt = m_pLightsList.begin(); LightIt != m_pLightsList.end(); LightIt++)
	{
		if (_pLight == *LightIt)
		{
			SAFE_DELETE(_pLight);
			m_pLightsList.erase(LightIt);
			return;
		}
	}
}
//*/