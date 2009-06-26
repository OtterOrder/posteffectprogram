#pragma once

#include <d3dx9.h>

#include "Misc.h"

class Mesh
{
public:

	u32		m_NbVertices;
	u32		m_NbFaces;

	PVertexBuffer		m_pVB;
	PIndexBuffer		m_pIB;
	VertexElement		m_VertexElements[MaxDecLength];	
	PVertexDeclaration  m_pVD;

	u32 m_VertexSize;

	Mesh(void);
	~Mesh(void);

	void Release ();

	HRESULT LoadFromXFile (PDevice _pDevice, cStr _pFileName);
};
