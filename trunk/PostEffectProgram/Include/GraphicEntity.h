#pragma once

#include "Types.h"

#include "Mesh.h"
#include "Material.h"

class GraphicEntity
{
public:
	DefineVectorIterator(GraphicEntity, Iterator);

private:
	Mesh*		m_pMesh;
	Material*	m_pMaterial;

public:
	GraphicEntity(void);
	~GraphicEntity(void);

	void Release ();

	HRESULT Initialize (PDevice _pDevice, cStr _meshFileName, cStr _vertexShaderFileName = NULL, cStr _vertexEntryPoint = NULL, cStr _pixelShaderFileName = NULL, cStr _pixelEntryPoint = NULL);
	void Draw (PDevice _pDevice);

	Material*	GetMaterial()	{ SAFE_NEW(m_pMaterial, Material); return m_pMaterial; };
};
