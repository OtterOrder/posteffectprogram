#pragma once

#include <d3d9.h>

class Shader
{
public:
	Shader(void);
	virtual ~Shader(void);

protected:
	LPDIRECT3DVERTEXSHADER9		m_pVertexShader;
	LPDIRECT3DPIXELSHADER9		m_pPixelShader;

public:
	//SetShaderFile
};
