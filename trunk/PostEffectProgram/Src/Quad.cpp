
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
	m_width = 800;
	m_height = 600;
}

Quad::~Quad()
{
}

void Quad::Create(PDevice _pDevice)
{
	m_width = GBufferRenderer::GetSingleton()->GetBackbufferWidth();
	m_height = GBufferRenderer::GetSingleton()->GetBackbufferWidth();

	m_pDevice=_pDevice;
	m_pDevice->CreateVertexDeclaration(QUADVERT::Decl, &m_pVertDeclPP);

	m_VBQuad[0]=QUADVERT(Vector4f(0.0f,			   0.0f,		   0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	m_VBQuad[1]=QUADVERT(Vector4f((float)m_width,  0.0f,		   0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	m_VBQuad[2]=QUADVERT(Vector4f(0.0f,			  (float)m_height, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
	m_VBQuad[3]=QUADVERT(Vector4f((float)m_width, (float)m_height, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
}

void Quad::Draw()
{
	m_pDevice->SetVertexDeclaration( m_pVertDeclPP );
	m_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, m_VBQuad, sizeof(QUADVERT) );
}

void Quad::Release()
{
	SAFE_RELEASE(m_pVertDeclPP);
}