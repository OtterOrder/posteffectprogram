#pragma once

#include "Types.h"
#include "Singleton.h"

#include "RenderTarget.h"
#include	"PostEffect.h"

#include	"GBufferRenderer.h"


#include	<assert.h>
#include	<vector>
using namespace std;

class PostRenderer: public Singleton< PostRenderer >
{
public:
	typedef enum
	{
		//PE_MotionBlur = 1 << 0
	} PostEffectType;

public:
	PostRenderer(void);
	virtual ~PostRenderer(void);

private:
	Vector2i	m_ScreenSize;
	RECT		m_ScreenRect;

	PSurface	m_pBackBuffer;
	PDevice		m_pDevice;

	RenderTarget*		m_pFrontRenderTarget;
	RenderTarget*		m_pBackRenderTarget;

	u32		m_PostEffects;
	vector <PostEffect*> m_pPostEffects;

	GBuffer*	m_GBuffer;

public:
	void RenderPostEffects ();

	void SetBackBuffer (PSurface _pBackBuffer);
	inline PSurface GetBackBuffer () { return m_pBackBuffer; };

	inline PTexture GetFrontRenderTexture ()	{ return m_pFrontRenderTarget->GetTexture(); };
	inline PSurface GetFrontRenderSurface ()	{ return m_pFrontRenderTarget->GetSurface(); };

	inline PTexture GetBackRenderTexture ()		{ return m_pBackRenderTarget->GetTexture(); };
	inline PSurface GetBackRenderSurface ()		{ return m_pBackRenderTarget->GetSurface(); };

	HRESULT Create (PDevice _pDevice, u32 _width, u32 _height);
	void Release ();
	void DestroyPostPorcesses ();

	void SwapSceneRender ();

	void SetRenderTarget (PSurface _pRenderTarget);
	PSurface GetRenderTarget ();

	void SetRenderTarget (u32 _level, PSurface _pRenderTarget);
	PSurface GetRenderTarget (u32 _level);

	void SetGBuffer (GBuffer* _GBuffer)		{ assert(_GBuffer), m_GBuffer = _GBuffer; };
	inline GBuffer* GetGBuffer ()			{ return m_GBuffer; };

	void EnablePostEffect	(PostEffectType _postEffect)	{ m_PostEffects = m_PostEffects | (1 << _postEffect); };
	void DisablePostEffect	(PostEffectType _postEffect)	{ m_PostEffects = !(!m_PostEffects | (1 << _postEffect)); };
};