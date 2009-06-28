#include "Material.h"

#define		DEFAULT_VS_PATH		"..\\Datas\\Shaders\\Defaults\\DefaultVS.vsh"
#define		DEFAULT_PS_PATH		"..\\Datas\\Shaders\\Defaults\\DefaultPS.psh"

#define		DEFAULT_VS_ENTRY	"VSMain"
#define		DEFAULT_PS_ENTRY	"PSMain"

//------------------------------------------------------------------------------------------------------------------------------
Material::Material(void)
{
	m_pDiffuseMap	= NULL;
	m_pNormalMap	= NULL;
	m_pSpecularMap	= NULL;
	m_pShader		= NULL;

	m_BumpCoefficient = 1.f;
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
void Material::SetTextureSampler (cStr _name, const Texture* _pTexture)
{
	if (_pTexture)
		m_pShader->SetPSSampler(_name, _pTexture->m_pTexture);
	else
		m_pShader->SetPSSampler(_name, NULL);
}

//------------------------------------------------------------------------------------------------------------------------------
void Material::Apply ()
{
	if (!m_pShader)
		return;

	m_pShader->Activate();

	SetTextureSampler ("DiffuseSampler", m_pDiffuseMap);
	SetTextureSampler ("NormalSampler", m_pNormalMap);
	SetTextureSampler ("SpecularSampler", m_pSpecularMap);

	m_pShader->SetPSFloat("gBumpCoef", m_BumpCoefficient);
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

	if (!_vertexShaderFileName)
	{
		_vertexShaderFileName = DEFAULT_VS_PATH;
		_vertexEntryPoint = DEFAULT_VS_ENTRY;
	}

	if (!_pixelShaderFileName)
	{
		_pixelShaderFileName = DEFAULT_PS_PATH;
		_pixelEntryPoint = DEFAULT_PS_ENTRY;
	}

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
