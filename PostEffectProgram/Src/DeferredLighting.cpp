#include	"DeferredLighting.h"

#include	"PostRenderer.h"
#include	"Scene.h"
#include	"Light.h"

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
	m_pShader->Activate();

	GBufferRenderer* pGBRenderer = GBufferRenderer::GetSingleton();
	PostRenderer* pPostRenderer = PostRenderer::GetSingleton();

	Vector3f cameraPosition = *(pGBRenderer->GetCamera().GetEyePt());
	m_pShader->SetPSVector3f("gCamPosition", cameraPosition);

	m_pShader->SetPSFloat("gZNear", pGBRenderer->GetCamera().GetNearClip());
	m_pShader->SetPSFloat("gZFar", pGBRenderer->GetCamera().GetFarClip());

	Matrix ViewProjInv;
	MatrixMultiply (&ViewProjInv, pGBRenderer->GetCamera().GetViewMatrix(), pGBRenderer->GetCamera().GetProjMatrix());
	MatrixInverse(&ViewProjInv, NULL, &ViewProjInv);
	m_pShader->SetPSMatrix("gViewProjInv", ViewProjInv);

	m_pShader->SetPSSampler("DiffuseSampler", pPostRenderer->GetGBuffer()->m_pDiffuseMap.GetTexture());
	m_pShader->SetPSSampler("NormalSampler",  pPostRenderer->GetGBuffer()->m_pNormalMap.GetTexture());
	m_pShader->SetPSSampler("DepthSampler",   pPostRenderer->GetGBuffer()->m_pDepthMap.GetTexture());

	getDevice->ColorFill(pPostRenderer->GetBackRenderSurface(), NULL, Vector3fToColor(Vector3f(0.f, 0.f, 0.f)) );

	vector<Light*>* pLightList = Scene::GetSingleton()->GetLightList();
	Light::Iterator LightIt;
	for (LightIt = pLightList->begin(); LightIt < pLightList->end(); LightIt++)
	{
		pPostRenderer->SetRenderTarget(pPostRenderer->GetFrontRenderSurface());

		m_pShader->SetPSSampler("RenderSampler", pPostRenderer->GetBackRenderTexture());

		m_pShader->SetPSVector3f("gLightPosition", (*LightIt)->GetPosition());
		//m_pShader->SetPSVector3f("gLightDirection", lightDirection);
		m_pShader->SetPSVector3f("gLightDiffuse", (*LightIt)->GetDiffuse());
		m_pShader->SetPSVector3f("gLightSpecular", (*LightIt)->GetSpecular());

		pPostRenderer->DrawScreenQuad();

		pPostRenderer->SwapSceneRender();
	}

	pPostRenderer->SwapSceneRender();
}