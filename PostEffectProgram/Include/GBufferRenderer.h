#pragma once

#include "GraphicEntity.h"
#include <list>


class GBufferRenderer
{
public:
	GBufferRenderer() {}
	~GBufferRenderer() {}

protected:

	std::list<GraphicEntity *> m_pEntityList;    // Liste des entités graphiques


};