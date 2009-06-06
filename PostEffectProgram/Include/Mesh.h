#pragma once
#include "Types.h"
#include <d3dx9.h>

class Mesh
{
private:

public:

	u32		m_NbVertices;
	u32		m_NbFaces;

	PVertexBuffer	m_pVB;
	PIndexBuffer	m_pIB;

	u32 m_FVF;
	u32 m_VertexSize;

	Mesh(void);
	~Mesh(void);

	void Release ();

	HRESULT LoadFromXFile (PDevice _pDevice, cStr _pFileName);
};
