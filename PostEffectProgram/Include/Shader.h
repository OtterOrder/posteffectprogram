#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "Types.h"

using namespace std;

class Shader
{
public:
	typedef enum {
		VertexShader,
		PixelShader
	} ShaderType;

	Shader(void);
	virtual ~Shader(void);

protected:
	LPDIRECT3DVERTEXSHADER9		m_pVertexShader;
	LPDIRECT3DPIXELSHADER9		m_pPixelShader;

	LPD3DXCONSTANTTABLE			m_pVertexConstantTable;
	LPD3DXCONSTANTTABLE			m_pPixelConstantTable;

public:
	HRESULT SetShaderFile (ShaderType _type, IDirect3DDevice9* pDevice, string _fileName, string _entryPoint);

	void Activate (IDirect3DDevice9* pDevice);
};
