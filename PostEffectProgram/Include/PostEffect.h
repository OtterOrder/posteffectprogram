#pragma once

#include	"Shader.h"
#include	"RenderTarget.h"

class PostEffect
{
protected:
	Shader*	m_pShader;

public:
	PostEffect ();
	virtual ~PostEffect ();

	virtual void Create (Vector2i _size) =0;
	virtual void Release () =0;
	virtual void Destroy () =0;

	virtual void Apply() = 0;

protected:
	void SetShader (cStr _vertexShaderFileName, cStr _vertexEntryPoint,
					cStr _pixelShaderFileName,  cStr _pixelEntryPoint);
};
