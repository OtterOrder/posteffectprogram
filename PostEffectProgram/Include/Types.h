#include <d3d9.h>
#include <d3dx9.h>

//******************************************************************************************************************************
typedef 	unsigned char			u8;
typedef 	signed char				s8;
typedef 	unsigned short			u16;
typedef 	signed short			s16;
typedef 	unsigned int			u32;
typedef 	signed int				s32;
typedef 	unsigned long			u64;
typedef 	signed long				s64;

typedef 	const char*				cStr;

//******************************************************************************************************************************
#define 	PDevice					LPDIRECT3DDEVICE9

//-------------------------------------------------------------
#define 	PVertexBuffer			LPDIRECT3DVERTEXBUFFER9
#define 	PIndexBuffer			LPDIRECT3DINDEXBUFFER9

//-------------------------------------------------------------
#define		PVertexShader			LPDIRECT3DVERTEXSHADER9
#define 	PPixelShader			LPDIRECT3DPIXELSHADER9
#define 	PConstantTable			LPD3DXCONSTANTTABLE
#define 	ConstantDesc			D3DXCONSTANT_DESC
#define 	Handle					D3DXHANDLE

//-------------------------------------------------------------
#define 	PTexture				LPDIRECT3DTEXTURE9
#define 	PSurface				LPDIRECT3DSURFACE9
#define 	ImageInfo				D3DXIMAGE_INFO

//-------------------------------------------------------------
typedef		D3DXMATRIX				Matrix;
#define 	MatrixMultiply			D3DXMatrixMultiply
#define 	MatrixIdentity			D3DXMatrixIdentity

//-------------------------------------------------------------
/*
#define		Vector3f				D3DXVECTOR3
#define		Vector4f				D3DXVECTOR4
*/
typedef		D3DXVECTOR3				Vector3f;
typedef		D3DXVECTOR4				Vector4f;