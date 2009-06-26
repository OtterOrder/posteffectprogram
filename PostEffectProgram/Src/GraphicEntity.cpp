#include "GraphicEntity.h"

#include "Camera.h"

//------------------------------------------------------------------------------------------------------------------------------
GraphicEntity::GraphicEntity(void)
{
	m_pMesh		= NULL;
	m_pMaterial	= NULL;

	MatrixIdentity(&m_WorldMatrix);
}

//------------------------------------------------------------------------------------------------------------------------------
GraphicEntity::~GraphicEntity(void)
{
	Release ();
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void GraphicEntity::Release ()
{
	SAFE_DELETE(m_pMesh);
	SAFE_DELETE(m_pMaterial);
}

//------------------------------------------------------------------------------------------------------------------------------
HRESULT GraphicEntity::Initialize(PDevice _pDevice, cStr _meshFileName, cStr _vertexShaderFileName, cStr _vertexEntryPoint, cStr _pixelShaderFileName, cStr _pixelEntryPoint)
{
	SAFE_NEW(m_pMesh, Mesh);

	if ( FAILED(m_pMesh->LoadFromXFile(_pDevice, _meshFileName)) )
	{
		SAFE_DELETE(m_pMesh);
		return E_FAIL;
	}

	SAFE_NEW(m_pMaterial, Material);
	m_pMaterial->SetShader(_pDevice, _vertexShaderFileName, _vertexEntryPoint, _pixelShaderFileName, _pixelEntryPoint);

	return S_OK;
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void GraphicEntity::Draw (PDevice _pDevice)
{
	if (!m_pMesh)
		return;

	if (m_pMaterial)
	{
		m_pMaterial->Apply(_pDevice);
	}

	_pDevice->SetVertexDeclaration(m_pMesh->m_pVD);

	_pDevice->SetStreamSource(0, m_pMesh->m_pVB, 0, m_pMesh->m_VertexSize);
	_pDevice->SetIndices(m_pMesh->m_pIB);

	_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_pMesh->m_NbVertices, 0, m_pMesh->m_NbFaces);
}

//------------------------------------------------------------------------------------------------------------------------------
void GraphicEntity::DrawWithoutMaterial (PDevice _pDevice)
{
	_pDevice->SetVertexDeclaration(m_pMesh->m_pVD);

	_pDevice->SetStreamSource(0, m_pMesh->m_pVB, 0, m_pMesh->m_VertexSize);
	_pDevice->SetIndices(m_pMesh->m_pIB);

	_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_pMesh->m_NbVertices, 0, m_pMesh->m_NbFaces);
}
