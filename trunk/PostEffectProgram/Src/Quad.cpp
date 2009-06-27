
#include "Quad.h"
#include "GBufferRenderer.h"

const VertexElement Quad::QUADVERT::Decl[3] =
{
	{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
	{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
	D3DDECL_END()
};

Quad::QUADVERT::QUADVERT(Vector4f _pos, Vector2f _texcoord)
{
	pos=_pos;
	texcoord=_texcoord;
}

Quad::Quad()
{
}

Quad::~Quad()
{
}

void Quad::Create(Vector2i _size)
{
	m_Size = _size;

	getDevice->CreateVertexDeclaration(QUADVERT::Decl, &m_pVertDeclPP);

	m_VBQuad[0]=QUADVERT(Vector4f(0.0f,			   0.0f,		   0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	m_VBQuad[1]=QUADVERT(Vector4f((float)m_Size.x, 0.0f,		   0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	m_VBQuad[2]=QUADVERT(Vector4f(0.0f,			  (float)m_Size.y, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
	m_VBQuad[3]=QUADVERT(Vector4f((float)m_Size.x,(float)m_Size.y, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
}

void Quad::Draw()
{
	getDevice->SetVertexDeclaration( m_pVertDeclPP );
	getDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, m_VBQuad, sizeof(QUADVERT) );
}

void Quad::Release()
{
	SAFE_RELEASE(m_pVertDeclPP);
}