#include	"Shader.h"
#include	<assert.h>

#define		DEFAULT_VS_PATH		"..\\Datas\\Shaders\\Defaults\\DefaultVS.vsh"
#define		DEFAULT_PS_PATH		"..\\Datas\\Shaders\\Defaults\\DefaultPS.psh"

#define		DEFAULT_VS_ENTRY	"VSMain"
#define		DEFAULT_PS_ENTRY	"PSMain"

//******************************************************************************************************************************
Shader::Shader(void)
{
	m_pVertexShader	= NULL;
	m_pPixelShader	= NULL;

	m_pVertexConstantTable	= NULL;
	m_pPixelConstantTable	= NULL;
}

//******************************************************************************************************************************
Shader::~Shader(void)
{
    SAFE_RELEASE(m_pVertexShader);
    SAFE_RELEASE(m_pPixelShader );
	SAFE_RELEASE(m_pVertexConstantTable);
	SAFE_RELEASE(m_pPixelConstantTable);
}

//******************************************************************************************************************************
HRESULT Shader::Load (cStr _vertexShaderFileName, cStr _vertexEntryPoint,
					  cStr _pixelShaderFileName , cStr _pixelEntryPoint )
{
	if(_vertexShaderFileName)
	{
		if ( FAILED(LoadVertexShader(_vertexShaderFileName, _vertexEntryPoint)) )
			return E_FAIL;
	}
	else
	{
		if ( FAILED(LoadVertexShader(DEFAULT_VS_PATH, DEFAULT_VS_ENTRY)) )
			return E_FAIL;
	}

	if(_pixelShaderFileName)
	{
		if ( FAILED(LoadPixelShader(_pixelShaderFileName, _pixelEntryPoint)) )
			return E_FAIL;
	}
	else
	{
		if ( FAILED(LoadPixelShader(DEFAULT_PS_PATH, DEFAULT_PS_ENTRY)) )
			return E_FAIL;
	}

	return S_OK;
}

//******************************************************************************************************************************
HRESULT Shader::LoadVertexShader (cStr _fileName, cStr _entryPoint)
{
	LPD3DXBUFFER pErrorBuffer = NULL;
	LPD3DXBUFFER pShaderCode = NULL;

	HRESULT res = S_OK;

	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pVertexConstantTable);

	if ( FAILED(D3DXCompileShaderFromFile(_fileName, NULL, NULL, _entryPoint, "vs_3_0", 0, &pShaderCode, &pErrorBuffer, &m_pVertexConstantTable) ))
	{
		res = E_FAIL;
		OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
		MessageBox (NULL, "Vertex Shader compilation Error", "Shader Error", MB_OK);
	}

	if (FAILED(getDevice->CreateVertexShader( (DWORD*)pShaderCode->GetBufferPointer(), &m_pVertexShader )))
	{
		res = E_FAIL;
		OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
	}

	SAFE_RELEASE(pErrorBuffer);
	SAFE_RELEASE(pShaderCode);

	return res;
}

//******************************************************************************************************************************
HRESULT Shader::LoadPixelShader (cStr _fileName, cStr _entryPoint)
{
	LPD3DXBUFFER pErrorBuffer = NULL;
	LPD3DXBUFFER pShaderCode = NULL;

	HRESULT res = S_OK;

	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pPixelConstantTable);

	if ( FAILED(D3DXCompileShaderFromFile(_fileName, NULL, NULL, _entryPoint, "ps_3_0", 0, &pShaderCode, &pErrorBuffer, &m_pPixelConstantTable) ))
	{
		res = E_FAIL;
		OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
		MessageBox (NULL, "Pixel Shader compilation Error", "Shader Error", MB_OK);
	}

	if (FAILED(getDevice->CreatePixelShader( (DWORD*)pShaderCode->GetBufferPointer(), &m_pPixelShader )))
	{
		res = E_FAIL;
		OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
		MessageBox (NULL, "Pixel Shader creation Error", "Shader Error", MB_OK);
	}

	SAFE_RELEASE(pErrorBuffer);
	SAFE_RELEASE(pShaderCode);

	return res;
}

//******************************************************************************************************************************
void Shader::Activate ()
{
	if (m_pVertexShader)
        getDevice->SetVertexShader(m_pVertexShader);
	if (m_pPixelShader)
		getDevice->SetPixelShader (m_pPixelShader );
}

//******************************************************************************************************************************
void Shader::SetSampler (PConstantTable& _constTable, cStr _name, const PTexture _texture)
{
	assert(_constTable);

	Handle textureHdl = _constTable->GetConstantByName(0, _name);
	WarningReturn(textureHdl != NULL, "Pixel Constant Table. Variable handle not found.");

	ConstantDesc textureDesc;
	u32 count;

	_constTable->GetConstantDesc(textureHdl, &textureDesc, &count);
	getDevice->SetTexture(textureDesc.RegisterIndex, _texture);
}

//******************************************************************************************************************************
void Shader::SetInt (PConstantTable& _constTable, cStr _name, const u32& _value)
{
	assert(_constTable);

	Handle varHdl = _constTable->GetConstantByName(0, _name);
	WarningReturn(varHdl != NULL, "Pixel Constant Table. Variable handle not found.");

	_constTable->SetInt(getDevice, varHdl, _value);
}

//******************************************************************************************************************************
void Shader::SetFloat (PConstantTable& _constTable, cStr _name, const float& _value)
{
	assert(_constTable);

	Handle varHdl = _constTable->GetConstantByName(0, _name);
	WarningReturn(varHdl != NULL, "Pixel Constant Table. Variable handle not found.");

	_constTable->SetFloat(getDevice, varHdl, _value);
}

//******************************************************************************************************************************
void Shader::SetMatrix (PConstantTable& _constTable, cStr _name, const Matrix& _matrix)
{
	assert(_constTable);

	Handle varHdl = _constTable->GetConstantByName(0, _name);
	WarningReturn(varHdl != NULL, "Pixel Constant Table. Variable handle not found.");

	_constTable->SetMatrix(getDevice, varHdl, &_matrix);
}
