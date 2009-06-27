#pragma once

#include <d3dx9.h>

#include "Types.h"
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	enum TextureType
	{
		Diffuse,
		Normal,
		Specular
	};

	Texture*	m_pDiffuseMap;
	Texture*	m_pNormalMap;
	Texture*    m_pSpecularMap;

	Shader*		m_pShader;

	Material(void);
	~Material(void);

	void Release ();

	void Apply ();

	HRESULT SetTexture (cStr _fileName, TextureType _type);

	HRESULT SetShader(cStr _vertexShaderFileName = NULL, cStr _vertexEntryPoint = NULL, cStr _pixelShaderFileName = NULL, cStr _pixelEntryPoint = NULL);
	HRESULT SetVertexShader	(cStr _fileName, cStr _entryPoint);
	HRESULT SetPixelShader	(cStr _fileName, cStr _entryPoint);
};