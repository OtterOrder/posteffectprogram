#pragma once

#include "Types.h"


class Quad
{
public:
	Quad();
	~Quad();

	void Create(Vector2i _size);
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

	Vector2i	m_Size;

	PVertexDeclaration  m_pVertDeclPP;
	QUADVERT			m_VBQuad[4];

};