#include "GraphicEntity.h"

//******************************************************************************************************************************
GraphicEntity::GraphicEntity(void)
{
	m_pMesh = NULL;
	m_pShader = NULL;
	m_pTexture = NULL;
}

//******************************************************************************************************************************
GraphicEntity::~GraphicEntity(void)
{
	Release ();
}

//******************************************************************************************************************************
void GraphicEntity::Release ()
{
	SAFE_DELETE(m_pMesh);
	SAFE_DELETE(m_pShader);

	SAFE_DELETE(m_pTexture);
}

//******************************************************************************************************************************
HRESULT GraphicEntity::Initialize(PDevice _pDevice, cStr _meshFileName, cStr _vertexShaderFileName, cStr _vertexEntryPoint, cStr _pixelShaderFileName, cStr _pixelEntryPoint)
{
	if(!m_pMesh)
		m_pMesh  = new Mesh();

	if ( FAILED(m_pMesh->LoadFromXFile(_pDevice, _meshFileName)) )
	{
		SAFE_DELETE(m_pMesh);
		return E_FAIL;
	}

	if (_vertexShaderFileName || _pixelShaderFileName)
	{
		if(!m_pShader)
			m_pShader  = new Shader();

		m_pShader->Load(_pDevice, _vertexShaderFileName, _vertexEntryPoint, _pixelShaderFileName, _pixelEntryPoint);
	}

	return S_OK;
}

//******************************************************************************************************************************
void GraphicEntity::Draw (PDevice _pDevice)
{
	if (!m_pMesh)
		return;

	if (m_pShader)
	{
		m_pShader->Activate(_pDevice);

		_pDevice->SetTexture(0, m_pTexture->m_pTexture);	////.
	}

	_pDevice->SetFVF(m_pMesh->m_FVF);

	_pDevice->SetStreamSource(0, m_pMesh->m_pVB, 0, m_pMesh->m_VertexSize);
	_pDevice->SetIndices(m_pMesh->m_pIB);

	_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_pMesh->m_NbVertices, 0, m_pMesh->m_NbFaces);
}

//******************************************************************************************************************************
HRESULT GraphicEntity::SetVertexShader	(PDevice _pDevice, cStr _fileName, cStr _entryPoint)
{
	if(!m_pShader)
		m_pShader = new Shader();

	return m_pShader->LoadVertexShader(_pDevice, _fileName, _entryPoint);
}

//******************************************************************************************************************************
HRESULT GraphicEntity::SetPixelShader	(PDevice _pDevice, cStr _fileName, cStr _entryPoint)
{
	if(!m_pShader)
		m_pShader = new Shader();

	return m_pShader->LoadPixelShader(_pDevice, _fileName, _entryPoint);
}

//******************************************************************************************************************************
HRESULT GraphicEntity::SetTexture	(PDevice _pDevice, cStr _fileName)
{
	if(!m_pTexture)
		m_pTexture = new Texture();

	return m_pTexture->LoadFromDdsFile(_pDevice, _fileName);
}
