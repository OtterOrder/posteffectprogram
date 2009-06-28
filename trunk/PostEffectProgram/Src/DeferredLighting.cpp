#include	"DeferredLighting.h"

#include	"PostRenderer.h"

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
DeferredLighting::DeferredLighting()
{
}

//------------------------------------------------------------------------------------------------------------------------------
DeferredLighting::~DeferredLighting()
{
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void DeferredLighting::Create (Vector2i _size)
{
	SetShader(NULL, NULL, "..\\Datas\\Shaders\\PSDeferredLighting.psh", "PSMain");
}

//------------------------------------------------------------------------------------------------------------------------------
void DeferredLighting::Release ()
{
}

//------------------------------------------------------------------------------------------------------------------------------
void DeferredLighting::Destroy ()
{
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void DeferredLighting::Apply()
{
	PostRenderer::GetSingleton()->SetRenderTarget(PostRenderer::GetSingleton()->GetFrontRenderSurface());

	m_pShader->Activate();

	Vector3f cameraPosition = *(GBufferRenderer::GetSingleton()->GetCamera().GetEyePt());
	m_pShader->SetPSVector3f("gCamPosition", cameraPosition);

	Matrix ViewProjInv;
	MatrixMultiply (&ViewProjInv, GBufferRenderer::GetSingleton()->GetCamera().GetViewMatrix(), GBufferRenderer::GetSingleton()->GetCamera().GetProjMatrix());
	MatrixInverse(&ViewProjInv, NULL, &ViewProjInv);
	m_pShader->SetPSMatrix("gViewProjInv", ViewProjInv);

	m_pShader->SetPSSampler("DiffuseSampler", PostRenderer::GetSingleton()->GetGBuffer()->m_pDiffuseMap.GetTexture());
	m_pShader->SetPSSampler("NormalSampler", PostRenderer::GetSingleton()->GetGBuffer()->m_pNormalMap.GetTexture());
	m_pShader->SetPSSampler("DepthSampler", PostRenderer::GetSingleton()->GetGBuffer()->m_pDepthMap.GetTexture());

	Vector3f lightPosition = Vector3f (-20.f, 20.f, 10.f);
	m_pShader->SetPSVector3f("gLightPosition", lightPosition);
	Vector3f lightDirection = Vector3f (0.f, 0.f, 1.f);
	//m_pShader->SetPSVector3f("gLightDirection", lightDirection);
	Vector3f lightDiffuse = Vector3f (0.8f, 0.8f, 0.8f);
	m_pShader->SetPSVector3f("gLightDiffuse", lightDiffuse);
	Vector3f lightSpecular = Vector3f (1.f, 1.f, 1.f);
	m_pShader->SetPSVector3f("gLightSpecular", lightSpecular);

	PostRenderer::GetSingleton()->DrawScreenQuad();
}