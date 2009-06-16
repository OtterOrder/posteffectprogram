#pragma once

#include "Types.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class GraphicEntity
{
	Mesh*		m_pMesh;
	Shader*		m_pShader;
	Texture*	m_pTexture;

	// ToDo : Use material containing all textures

public:
	GraphicEntity(void);
	~GraphicEntity(void);

	void Release ();

	HRESULT Initialize (PDevice _pDevice, cStr _meshFileName, cStr _vertexShaderFileName = NULL, cStr _vertexEntryPoint = NULL, cStr _pixelShaderFileName = NULL, cStr _pixelEntryPoint = NULL);
	void Draw (PDevice _pDevice);

	HRESULT SetVertexShader	(PDevice _pDevice, cStr _fileName, cStr _entryPoint);
	HRESULT SetPixelShader	(PDevice _pDevice, cStr _fileName, cStr _entryPoint);

	HRESULT SetTexture	(PDevice _pDevice, cStr _fileName);
};