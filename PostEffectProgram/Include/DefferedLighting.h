#pragma once

#include	"PostProcess.h"

class DefferedLighting : public PostProcess
{

public:
	DefferedLighting ();
	~DefferedLighting ();

	void Create (Vector2i _size);
	void Release ();
	void Destroy ();

	void Apply();
};
