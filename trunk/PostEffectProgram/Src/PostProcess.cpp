#include	"PostProcess.h"

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
PostProcess::PostProcess(void)
{
	m_pShader = NULL;
}

//----------------------------------------------------------------------------------------------
PostProcess::~PostProcess(void)
{
	SAFE_DELETE(m_pShader);
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
void PostProcess::SetShader (cStr _vertexShaderFileName, cStr _vertexEntryPoint,
							 cStr _pixelShaderFileName,  cStr _pixelEntryPoint)
{
	SAFE_NEW(m_pShader, Shader);
	m_pShader->Load(_vertexShaderFileName, _vertexEntryPoint, _pixelShaderFileName, _pixelEntryPoint);
}