#pragma once

#include "Types.h"


class Quad
{
public:
	Quad();
	~Quad();

	void Create(PDevice _pDevice);
	void Draw();
	void Release();

protected:
	struct QUADVERT
	{
		QUADVERT(){}
		QUADVERT		(Vector4f _pos, Vector2f _texcoord);
		Vector4f		pos;
		Vector2f		texcoord;
		const static	VertexElement Decl[3];
		void operator=	(const QUADVERT& quad){ pos=quad.pos; texcoord=quad.texcoord;}
	};

	u32		m_width;
	u32		m_height;

	PDevice				m_pDevice;
	PVertexDeclaration  m_pVertDeclPP;
	QUADVERT			m_VBQuad[4];

};