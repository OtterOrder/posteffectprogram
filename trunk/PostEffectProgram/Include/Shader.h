#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Types.h"

class Shader
{
public:
	Shader(void);
	virtual ~Shader(void);

//protected:
	PVertexShader		m_pVertexShader;
	PPixelShader		m_pPixelShader;

	LPD3DXCONSTANTTABLE			m_pVertexConstantTable;
	LPD3DXCONSTANTTABLE			m_pPixelConstantTable;

public:
	HRESULT Load				(PDevice _pDevice,
								 cStr _vertexShaderFileName = NULL, cStr _vertexEntryPoint = NULL,
								 cStr _pixelShaderFileName  = NULL, cStr _pixelEntryPoint  = NULL);

	HRESULT LoadVertexShader	(PDevice _pDevice, cStr _fileName, cStr _entryPoint);
	HRESULT LoadPixelShader		(PDevice _pDevice, cStr _fileName, cStr _entryPoint);

	void Activate (PDevice _pDevice);
};
