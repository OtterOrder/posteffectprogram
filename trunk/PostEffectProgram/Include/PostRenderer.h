#pragma once

#include	"Types.h"
#include	"Singleton.h"

#include	"RenderTarget.h"
#include	"PostProcess.h"
#include	"Quad.h"

#include	"GBufferRenderer.h"


#include	"DeferredLighting.h"


#include	<assert.h>
#include	<vector>
using namespace std;

class PostRenderer: public Singleton <PostRenderer>
{
public:
	enum PostProcessType
	{
		PE_DeferredLighting = 1 << 0
	};

public:
	PostRenderer(void);
	virtual ~PostRenderer(void);

private:
	Vector2i	m_ScreenSize;
	RECT		m_ScreenRect;

	PSurface	m_pBackBuffer;

	RenderTarget*		m_pFrontRenderTarget;
	RenderTarget*		m_pBackRenderTarget;

	u32		m_PostProcesses;
	vector <PostProcess*> m_pPostProcesses;

	GBuffer*	m_GBuffer;

	Quad		m_ScreenQuad;

public:
	HRESULT Initialize (Vector2i _size);
	void Release ();
	void Destroy ();

	void RenderPostProcesses ();

	inline PSurface GetBackBuffer () { return m_pBackBuffer; };

	inline PTexture GetFrontRenderTexture ()	{ return m_pFrontRenderTarget->GetTexture(); };
	inline PSurface GetFrontRenderSurface ()	{ return m_pFrontRenderTarget->GetSurface(); };

	inline PTexture GetBackRenderTexture ()		{ return m_pBackRenderTarget->GetTexture(); };
	inline PSurface GetBackRenderSurface ()		{ return m_pBackRenderTarget->GetSurface(); };

	void SwapSceneRender ();

	void SetRenderTarget (PSurface _pRenderTarget);
	PSurface GetRenderTarget ();

	void SetRenderTarget (u32 _level, PSurface _pRenderTarget);
	PSurface GetRenderTarget (u32 _level);

	void SetGBuffer (GBuffer* _GBuffer)		{ assert(_GBuffer), m_GBuffer = _GBuffer; };
	inline GBuffer* GetGBuffer ()			{ return m_GBuffer; };

	void EnablePostProcess	(PostProcessType _postProcess)	{ m_PostProcesses = m_PostProcesses | _postProcess; };
	void DisablePostProcess	(PostProcessType _postProcess)	{ m_PostProcesses = (m_PostProcesses & ~_postProcess); };

	inline void DrawScreenQuad ()	{ m_ScreenQuad.Draw(); };
};