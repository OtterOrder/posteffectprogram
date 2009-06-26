#include "Scene.h"

//******************************************************************************************************************************
Scene::~Scene ()
{
	Destroy();
}

//******************************************************************************************************************************
void Scene::Clear ()
{
	GraphicEntity::Iterator GEntityIt;

	for (GEntityIt = m_pEntitiesList.begin(); GEntityIt != m_pEntitiesList.end(); GEntityIt++)
		SAFE_DELETE((*GEntityIt));

	m_pEntitiesList.clear();


	Light::Iterator LightIt;

	for (LightIt = m_pLightsList.begin(); LightIt != m_pLightsList.end(); LightIt++)
		SAFE_DELETE((*LightIt));

	m_pLightsList.clear();
}

//******************************************************************************************************************************
GraphicEntity* Scene::CreateGraphicEntity ()
{
	m_pEntitiesList.push_back(new GraphicEntity());
	return m_pEntitiesList.back();
}

//******************************************************************************************************************************
Light* Scene::CreateLight (Light::Type _type)
{
	Light* newLight = NULL;
	
	if (_type == Light::Directional)
		newLight = new DirectionalLight();
	else
	if (_type == Light::Point)
		newLight = new PointLight();
	else
	if (_type == Light::Spot)
		newLight = new SpotLight();

	m_pLightsList.push_back(newLight);
	return newLight;
}

//******************************************************************************************************************************
void Scene::DeleteGraphicEntity (GraphicEntity* _pGraphicEntity)
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