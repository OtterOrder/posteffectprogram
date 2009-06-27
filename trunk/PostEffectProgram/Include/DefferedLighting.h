#pragma once

#include	"PostProcess.h"

class DefferedLighting : public PostProcess
{

public:
	DefferedLighting ();
	virtual ~DefferedLighting ();

	virtual void Create (Vector2i _size);
	virtual void Release ();
	virtual void Destroy ();

	virtual void Apply();
};
