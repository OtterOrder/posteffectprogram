#pragma once

#include "Misc.h"

class Shader
{
private:
	PVertexShader				m_pVertexShader;
	PPixelShader				m_pPixelShader;

	PConstantTable				m_pVertexConstantTable;
	PConstantTable				m_pPixelConstantTable;

public:
	Shader(void);
	virtual ~Shader(void);

	HRESULT Load (PDevice _pDevice,
				  cStr _vertexShaderFileName = NULL, cStr _vertexEntryPoint = NULL,
				  cStr _pixelShaderFileName  = NULL, cStr _pixelEntryPoint  = NULL);

	HRESULT LoadVertexShader (PDevice _pDevice, cStr _fileName, cStr _entryPoint);
	HRESULT LoadPixelShader (PDevice _pDevice, cStr _fileName, cStr _entryPoint);

	void Activate (PDevice _pDevice);

// Sampler
public:
	inline void SetVSSampler (PDevice _pDevice, cStr _name, const PTexture _texture)	{ SetSampler (_pDevice, m_pVertexConstantTable, _name, _texture); };
	inline void SetPSSampler (PDevice _pDevice, cStr _name, const PTexture _texture)	{ SetSampler (_pDevice, m_pPixelConstantTable,  _name, _texture); };

private:
	void SetSampler (PDevice _pDevice, PConstantTable& _constTable, cStr _name, const PTexture _texture);

// u32
public:
	inline void SetVSInt (PDevice _pDevice, cStr _name, const u32& _value)	{ SetInt (_pDevice, m_pVertexConstantTable, _name, _value); };
	inline void SetPSInt (PDevice _pDevice, cStr _name, const u32& _value)	{ SetInt (_pDevice, m_pPixelConstantTable,  _name, _value); };

private:
	void SetInt (PDevice _pDevice, PConstantTable& _constTable, cStr _name, const u32& _value);

// Float
public:
	inline void SetVSFloat (PDevice _pDevice, cStr _name, const float& _value)	{ SetFloat (_pDevice, m_pVertexConstantTable, _name, _value); };
	inline void SetPSFloat (PDevice _pDevice, cStr _name, const float& _value)	{ SetFloat (_pDevice, m_pPixelConstantTable,  _name, _value); };

private:
	void SetFloat (PDevice _pDevice, PConstantTable& _constTable, cStr _name, const float& _value);

// Matrix
public:
	inline void SetVSMatrix (PDevice _pDevice, cStr _name, const Matrix& _matrix)	{ SetMatrix (_pDevice, m_pVertexConstantTable, _name, _matrix); };
	inline void SetPSMatrix (PDevice _pDevice, cStr _name, const Matrix& _matrix)	{ SetMatrix (_pDevice, m_pPixelConstantTable,  _name, _matrix); };

private:
	void SetMatrix (PDevice _pDevice, PConstantTable& _constTable, cStr _name, const Matrix& _matrix);
};
