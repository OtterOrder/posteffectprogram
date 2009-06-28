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
HRESULT Mesh::LoadFromXFile (cStr _pFileName)
{
	HRESULT result;

	LPD3DXMESH pMesh = NULL;

	result = D3DXLoadMeshFromX( _pFileName,
								D3DXMESH_MANAGED,
								getDevice,
								NULL,				// Adjacency
								NULL,				// Materials
								NULL,				// EffectInstances
								NULL,				// NumMaterials
								&pMesh );			// Mesh

	if( SUCCEEDED(result) )
	{
		Release ();

		//create a new vert decleration
		VertexElement vertDecl[] = 
		{
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
			{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
			D3DDECL_END()
		};

		LPD3DXMESH pMeshTemp = pMesh;
		pMesh = NULL;
		pMeshTemp->CloneMesh(D3DXMESH_VB_MANAGED, vertDecl, getDevice, &pMesh);

		SAFE_RELEASE(pMeshTemp);
		pMeshTemp = pMesh;
		pMesh = NULL;

		D3DXComputeTangentFrameEx(	pMeshTemp, D3DDECLUSAGE_TEXCOORD, 0, D3DDECLUSAGE_TANGENT, 0,
									D3DX_DEFAULT, 0, D3DDECLUSAGE_NORMAL, 0,
									D3DXTANGENT_CALCULATE_NORMALS,
									NULL, -1, 0, -1, &pMesh, NULL );

		SAFE_RELEASE(pMeshTemp);

		pMesh->GetVertexBuffer(&m_pVB);
		m_NbVertices = pMesh->GetNumVertices();

		pMesh->GetIndexBuffer(&m_pIB);
		m_NbFaces = pMesh->GetNumFaces();

		m_VertexSize = pMesh->GetNumBytesPerVertex();

		pMesh->GetDeclaration(m_VertexElements);
		getDevice->CreateVertexDeclaration(m_VertexElements, &m_pVD);
	}

	SAFE_RELEASE(pMesh);

	return result;
}
