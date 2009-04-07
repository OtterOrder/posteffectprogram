#include	"Shader.h"

Shader::Shader(void)
{
	m_pVertexShader	= NULL;
	m_pPixelShader	= NULL;

	m_pVertexConstantTable	= NULL;
	m_pPixelConstantTable	= NULL;
}

Shader::~Shader(void)
{
    SAFE_RELEASE(m_pVertexShader);
    SAFE_RELEASE(m_pPixelShader );
}

HRESULT Shader::SetShaderFile (ShaderType _type, IDirect3DDevice9* pDevice, string _fileName, string _entryPoint)
{
	LPD3DXBUFFER pErrorBuffer = NULL;

    LPD3DXBUFFER pShaderCode = NULL;

	HRESULT res = S_OK;
	if (_type == VertexShader)
	{
		if ( FAILED(D3DXCompileShaderFromFile(_fileName.c_str(), NULL, NULL, _entryPoint.c_str(), "vs_3_0", D3DXSHADER_NO_PRESHADER, &pShaderCode, &pErrorBuffer, &m_pVertexConstantTable) ))
		{
			res = E_FAIL;
			OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
			MessageBox (NULL, "Vertex Shader compilation Error", "Shader Error", MB_OK);
		}

		if (FAILED(pDevice->CreateVertexShader( (DWORD*)pShaderCode->GetBufferPointer(), &m_pVertexShader )))
		{
			res = E_FAIL;
			OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
			MessageBox (NULL, "Vertex Shader creation Error", "Shader Error", MB_OK);
		}
	}
	else
	{
		if ( FAILED(D3DXCompileShaderFromFile(_fileName.c_str(), NULL, NULL, _entryPoint.c_str(), "ps_3_0", D3DXSHADER_NO_PRESHADER, &pShaderCode, &pErrorBuffer, &m_pPixelConstantTable) ))
		{
			res = E_FAIL;
			OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
			MessageBox (NULL, "Pixel Shader compilation Error", "Shader Error", MB_OK);
		}

		if (FAILED(pDevice->CreatePixelShader( (DWORD*)pShaderCode->GetBufferPointer(), &m_pPixelShader )))
		{
			res = E_FAIL;
			OutputDebugString(reinterpret_cast <char*> (pErrorBuffer->GetBufferPointer()));
			MessageBox (NULL, "Pixel Shader creation Error", "Shader Error", MB_OK);
		}
	}

	pErrorBuffer->Release();
	pShaderCode->Release();

	return res;
}

void  Shader::Activate (IDirect3DDevice9* pDevice)
{
        pDevice->SetVertexShader(m_pVertexShader);
		pDevice->SetPixelShader (m_pPixelShader );
}