#pragma once

#include	"PostProcess.h"

class DeferredLighting : public PostProcess
{

public:
	DeferredLighting ();
	~DeferredLighting ();

	void Create (Vector2i _size);
	void Release ();
	void Destroy ();

	void Apply();
};
