#pragma once

#include	"PostEffect.h"

class DefferedLighting : public PostEffect
{

public:
	DefferedLighting ();
	virtual ~DefferedLighting ();

	virtual void Create (Vector2i _size);
	virtual void Release ();
	virtual void Destroy ();

	virtual void Apply();
};
