#include	"Shader.h"

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
}

//******************************************************************************************************************************
HRESULT Shader::Load (PDevice _pDevice,
					  cStr _vertexShaderFileName, cStr _vertexEntryPoint,
					  cStr _pixelShaderFileName , cStr _pixelEntryPoint )
{
	if(_vertexShaderFileName)
		if(FAILED(LoadVertexShader(_pDevice, _vertexShaderFileName, _vertexEntryPoint)))
			return E_FAIL;

	if(_pixelShaderFileName)
		if(FAILED(LoadPixelShader(_pDevice, _pixelShaderFileName, _pixelEntryPoint)))
			return E_FAIL;

	return S_OK;
}

//******************************************************************************************************************************
HRESULT Shader::LoadVertexShader (PDevice _pDevice, cStr _fileName, cStr _entryPoint)
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

	if (FAILED(_pDevice->CreateVertexShader( (DWORD*)pShaderCode->GetBufferPointer(), &m_pVertexShader )))
	{
		res = E_FAIL;
		OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
	}

	SAFE_RELEASE(pErrorBuffer);
	SAFE_RELEASE(pShaderCode);

	return res;
}

//******************************************************************************************************************************
HRESULT Shader::LoadPixelShader (PDevice _pDevice, cStr _fileName, cStr _entryPoint)
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

	if (FAILED(_pDevice->CreatePixelShader( (DWORD*)pShaderCode->GetBufferPointer(), &m_pPixelShader )))
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
void  Shader::Activate (PDevice _pDevice)
{
	if (m_pVertexShader)
        _pDevice->SetVertexShader(m_pVertexShader);
	if (m_pPixelShader)
		_pDevice->SetPixelShader (m_pPixelShader );
}