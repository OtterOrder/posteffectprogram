#include "Material.h"

//------------------------------------------------------------------------------------------------------------------------------
Material::Material(void)
{
	m_pDiffuseMap	= NULL;
	m_pNormalMap	= NULL;
	m_pSpecularMap	= NULL;
	m_pShader		= NULL;
}

//------------------------------------------------------------------------------------------------------------------------------
Material::~Material(void)
{
	Release ();
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void Material::Release ()
{
	SAFE_DELETE(m_pDiffuseMap);
	SAFE_DELETE(m_pNormalMap);
	SAFE_DELETE(m_pSpecularMap);
	SAFE_DELETE(m_pShader);
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void Material::Apply ()
{
	if (!m_pShader)
		return;

	m_pShader->Activate();

	if (m_pDiffuseMap)
		m_pShader->SetPSSampler("DiffuseSampler", m_pDiffuseMap->m_pTexture);
	else
		m_pShader->SetPSSampler("DiffuseSampler", NULL);

	if (m_pNormalMap)
		m_pShader->SetPSSampler("NormalSampler", m_pNormalMap->m_pTexture);
	else
		m_pShader->SetPSSampler("NormalSampler", NULL);

	if (m_pSpecularMap)
		m_pShader->SetPSSampler("SpecularSampler", m_pSpecularMap->m_pTexture);
	else
		m_pShader->SetPSSampler("SpecularSampler", NULL);
}

//------------------------------------------------------------------------------------------------------------------------------
HRESULT Material::SetTexture (cStr _fileName, TextureType _type)
{
	if (_type == Diffuse)
	{
		SAFE_NEW(m_pDiffuseMap, Texture);
		return m_pDiffuseMap->Load(_fileName);
	}
	else
	if (_type == Normal)
	{
		SAFE_NEW(m_pNormalMap, Texture);
		return m_pNormalMap->Load(_fileName);
	}
	else
	if(_type == Specular)
	{
		SAFE_NEW(m_pSpecularMap, Texture);
		return m_pSpecularMap->Load(_fileName);
	}

	return E_UNEXPECTED;
}

//------------------------------------------------------------------------------------------------------------------------------
HRESULT Material::SetShader(cStr _vertexShaderFileName, cStr _vertexEntryPoint, cStr _pixelShaderFileName, cStr _pixelEntryPoint)
{
	SAFE_NEW(m_pShader, Shader);

	return m_pShader->Load(_vertexShaderFileName, _vertexEntryPoint, _pixelShaderFileName, _pixelEntryPoint);
}

//------------------------------------------------------------------------------------------------------------------------------
HRESULT Material::SetVertexShader	(cStr _fileName, cStr _entryPoint)
{
	SAFE_NEW(m_pShader, Shader);

	return m_pShader->LoadVertexShader(_fileName, _entryPoint);
}

//------------------------------------------------------------------------------------------------------------------------------
HRESULT Material::SetPixelShader	(cStr _fileName, cStr _entryPoint)
{
	SAFE_NEW(m_pShader, Shader);

	return m_pShader->LoadPixelShader(_fileName, _entryPoint);
}