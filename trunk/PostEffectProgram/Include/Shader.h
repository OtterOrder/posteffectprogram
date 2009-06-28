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

	HRESULT Load (cStr _vertexShaderFileName = NULL, cStr _vertexEntryPoint = NULL,
				  cStr _pixelShaderFileName  = NULL, cStr _pixelEntryPoint  = NULL);

	HRESULT LoadVertexShader (cStr _fileName, cStr _entryPoint);
	HRESULT LoadPixelShader (cStr _fileName, cStr _entryPoint);

	void Activate ();

// Sampler
public:
	inline void SetVSSampler (cStr _name, const PTexture _texture)	{ SetSampler (m_pVertexConstantTable, _name, _texture); };
	inline void SetPSSampler (cStr _name, const PTexture _texture)	{ SetSampler (m_pPixelConstantTable,  _name, _texture); };

private:
	void SetSampler (PConstantTable& _constTable, cStr _name, const PTexture _texture);

// u32
public:
	inline void SetVSInt (cStr _name, const u32& _value)	{ SetInt (m_pVertexConstantTable, _name, _value); };
	inline void SetPSInt (cStr _name, const u32& _value)	{ SetInt (m_pPixelConstantTable,  _name, _value); };

private:
	void SetInt (PConstantTable& _constTable, cStr _name, const u32& _value);

// Float
public:
	inline void SetVSFloat (cStr _name, const float& _value)	{ SetFloat (m_pVertexConstantTable, _name, _value); };
	inline void SetPSFloat (cStr _name, const float& _value)	{ SetFloat (m_pPixelConstantTable,  _name, _value); };

private:
	void SetFloat (PConstantTable& _constTable, cStr _name, const float& _value);

// Vector2f
public:
	inline void SetVSVector2f (cStr _name, const Vector2f& _value)	{ SetVector2f (m_pVertexConstantTable, _name, _value); };
	inline void SetPSVector2f (cStr _name, const Vector2f& _value)	{ SetVector2f (m_pPixelConstantTable,  _name, _value); };

private:
	void SetVector2f (PConstantTable& _constTable, cStr _name, const Vector2f& _value);

// Vector3f
public:
	inline void SetVSVector3f (cStr _name, const Vector3f& _value)	{ SetVector3f (m_pVertexConstantTable, _name, _value); };
	inline void SetPSVector3f (cStr _name, const Vector3f& _value)	{ SetVector3f (m_pPixelConstantTable,  _name, _value); };

private:
	void SetVector3f (PConstantTable& _constTable, cStr _name, const Vector3f& _value);

// Vector4f
public:
	inline void SetVSVector4f (cStr _name, const Vector4f& _value)	{ SetVector4f (m_pVertexConstantTable, _name, _value); };
	inline void SetPSVector4f (cStr _name, const Vector4f& _value)	{ SetVector4f (m_pPixelConstantTable,  _name, _value); };

private:
	void SetVector4f (PConstantTable& _constTable, cStr _name, const Vector4f& _value);

// Matrix
public:
	inline void SetVSMatrix (cStr _name, const Matrix& _matrix)	{ SetMatrix (m_pVertexConstantTable, _name, _matrix); };
	inline void SetPSMatrix (cStr _name, const Matrix& _matrix)	{ SetMatrix (m_pPixelConstantTable,  _name, _matrix); };

private:
	void SetMatrix (PConstantTable& _constTable, cStr _name, const Matrix& _matrix);
};
