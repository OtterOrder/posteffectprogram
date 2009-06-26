#include "Mesh.h"

//------------------------------------------------------------------------------------------------------------------------------
Mesh::Mesh(void)
{
	m_NbVertices = 0;
	m_NbFaces = 0;
	
	m_pVB = NULL;
	m_pIB = NULL;
	m_pVD = NULL;

}

//------------------------------------------------------------------------------------------------------------------------------
Mesh::~Mesh(void)
{
	Release ();
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void Mesh::Release ()
{
	SAFE_RELEASE(m_pVB);

	SAFE_RELEASE(m_pIB);

	SAFE_RELEASE(m_pVD);
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
HRESULT Mesh::LoadFromXFile (PDevice _pDevice, cStr _pFileName)
{
	HRESULT result;

	LPD3DXMESH pMesh = NULL;

	result = D3DXLoadMeshFromX( _pFileName,
								D3DXMESH_MANAGED,
								_pDevice,
								NULL,				// Adjacency
								NULL,				// Materials
								NULL,				// EffectInstances
								NULL,				// NumMaterials
								&pMesh );			// Mesh

	if( SUCCEEDED(result) )
	{
		Release ();

		pMesh->GetVertexBuffer(&m_pVB);
		m_NbVertices = pMesh->GetNumVertices();

		pMesh->GetIndexBuffer(&m_pIB);
		m_NbFaces = pMesh->GetNumFaces();

		m_VertexSize = pMesh->GetNumBytesPerVertex();


		pMesh->GetDeclaration(m_VertexElements);
		_pDevice->CreateVertexDeclaration(m_VertexElements, &m_pVD);

	}

	SAFE_RELEASE(pMesh);

	return result;
}
