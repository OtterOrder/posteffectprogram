#pragma once

#include	"Shader.h"
#include	"RenderTarget.h"

using namespace std;

class PostEffect
{
protected:
	Shader*	m_pShader;

public:
	PostEffect(void);
	virtual ~PostEffect(void);

	virtual void Create (PDevice _pDevice, Vector2i _size) =0;
	virtual void Release () =0;
	virtual void Destroy () =0;

	virtual void Apply() = 0;

protected:
	void SetShader (PDevice _pDevice,
					cStr _vertexShaderFileName, cStr _vertexEntryPoint,
					cStr _pixelShaderFileName,  cStr _pixelEntryPoint);
};
