
//******************************************************************************************************************************
#define SAFE_DELETE(p)		{					\
								if (p)			\
								{				\
									delete p;	\
									p = NULL;	\
								}				\
							}					\

//******************************************************************************************************************************
#define SAFE_RELEASE(p)		{						\
								if (p)				\
								{					\
									p->Release();	\
									p = NULL;		\
								}					\
							}						\

//******************************************************************************************************************************
typedef unsigned char	u8;
typedef signed char		s8;
typedef unsigned short	u16;
typedef signed short	s16;
typedef unsigned int	u32;
typedef signed int		s32;
typedef unsigned long	u64;
typedef signed long		s64;

typedef const char*		cStr;

//******************************************************************************************************************************
#define PDevice			LPDIRECT3DDEVICE9

#define PVertexBuffer	LPDIRECT3DVERTEXBUFFER9
#define PIndexBuffer	LPDIRECT3DINDEXBUFFER9

#define	PVertexShader	LPDIRECT3DVERTEXSHADER9
#define PPixelShader	LPDIRECT3DPIXELSHADER9

#define PTexture		LPDIRECT3DTEXTURE9
#define ImageInfo		D3DXIMAGE_INFO