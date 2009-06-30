
#include <Windows.h>
#include <strsafe.h>
#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )
#pragma warning( default : 4996 )

#include "Types.h"
#include "GBufferRenderer.h"
#include "PostRenderer.h"
#include "Scene.h"

HWND      g_hWnd;


HRESULT CreateScene()
{

	// Création de la scène 

	Scene* pScene = Scene::GetSingleton();

	GraphicEntity* pGE1 = pScene->CreateGraphicEntity();
	pGE1->Initialize("..\\Datas\\Meshes\\sol.x");

	pGE1->GetMaterial()->SetTexture("..\\Datas\\Textures\\sol_diffuse.jpg", Material::Diffuse);
	pGE1->GetMaterial()->SetTexture("..\\Datas\\Textures\\sol_normal.jpg", Material::Normal);
	pGE1->GetMaterial()->SetTexture("..\\Datas\\Textures\\sol_specular.jpg", Material::Specular);

	GraphicEntity* pGE2 = pScene->CreateGraphicEntity();
	pGE2->Initialize("..\\Datas\\Meshes\\mur.X");

	pGE2->GetMaterial()->SetTexture("..\\Datas\\Textures\\wall_diffuse.jpg", Material::Diffuse);
	pGE2->GetMaterial()->SetTexture("..\\Datas\\Textures\\wall_normal.jpg", Material::Normal);
	pGE2->GetMaterial()->SetTexture("..\\Datas\\Textures\\wall_specular.jpg", Material::Specular);

	GraphicEntity* pGE4 = pScene->CreateGraphicEntity();
	pGE4->Initialize("..\\Datas\\Meshes\\plafond.X");

	pGE4->GetMaterial()->SetTexture("..\\Datas\\Textures\\celling_diffuse.jpg", Material::Diffuse);
	pGE4->GetMaterial()->SetTexture("..\\Datas\\Textures\\celling_normal.jpg", Material::Normal);
	pGE4->GetMaterial()->SetTexture("..\\Datas\\Textures\\celling_specular.jpg", Material::Specular);

	Light* pLight = NULL;

	pLight = pScene->CreateLight(Light::Point);
	pLight->SetPosition( Vector3f(-20.f, 20.f, -30.f) );
	pLight->SetDiffuse( Vector3f(0.6f, 0.5f, 0.5f) );
	pLight->SetSpecular( Vector3f(1.f, 0.8f, 0.8f) );

/*
	pLight = pScene->CreateLight(Light::Point);
	pLight->SetPosition( Vector3f(-20.f, 20.f, 30.f) );
	pLight->SetDiffuse( Vector3f(0.8f, 0.8f, 0.8f) );
	pLight->SetSpecular( Vector3f(1.f, 1.f, 1.f) );


	pLight = pScene->CreateLight(Light::Point);
	pLight->SetPosition( Vector3f(-20.f, 20.f, 30.f) );
	pLight->SetDiffuse( Vector3f(0.8f, 0.8f, 0.8f) );
	pLight->SetSpecular( Vector3f(1.f, 1.f, 1.f) );
*/


	pLight = pScene->CreateLight(Light::Point);
	pLight->SetPosition( Vector3f(0.f, 20.f, 30.f) );
	pLight->SetDiffuse( Vector3f(0.8f, 0.8f, 0.8f) );
	pLight->SetSpecular( Vector3f(1.f, 1.f, 1.f) );


	pLight = pScene->CreateLight(Light::Point);
	pLight->SetPosition( Vector3f(40.f, 20.f, 0.f) );
	pLight->SetDiffuse( Vector3f(0.2f, 0.2f, 0.8f) );
	pLight->SetSpecular( Vector3f(1.f, 1.f, 1.f) );

	char _name[32];
	for(int i=0; i<7; i++)
	{
		sprintf_s(_name, 32, "..\\Datas\\Meshes\\boite0%d.X", i);

		GraphicEntity* pGE3 = pScene->CreateGraphicEntity();
		pGE3->Initialize(_name);

		pGE3->GetMaterial()->SetTexture("..\\Datas\\Textures\\box_diffuse.jpg", Material::Diffuse);
		pGE3->GetMaterial()->SetTexture("..\\Datas\\Textures\\box_normal.jpg", Material::Normal);
		pGE3->GetMaterial()->SetTexture("..\\Datas\\Textures\\box_specular.jpg", Material::Specular);
	}

    return S_OK;
}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
		case WM_DESTROY:
			Scene::GetSingleton()->Destroy();
			PostRenderer::GetSingleton()->Destroy();
            GBufferRenderer::GetSingleton()->Destroy();
            PostQuitMessage( 0 );
			DestroyWindow(g_hWnd);
            return 0;

		 case WM_SETCURSOR:
			SetCursor(NULL);
            break;

		 case WM_KEYDOWN:
         {
            switch( wParam )
            {
                case VK_ESCAPE:
				{
					Scene::GetSingleton()->Destroy();
					PostRenderer::GetSingleton()->Destroy();
					GBufferRenderer::GetSingleton()->Destroy();
					DestroyWindow(g_hWnd);
					PostQuitMessage( 0 );
					return 0;
				}
			}
		 }
    }

	GBufferRenderer::GetSingleton()->HandleMessage(hWnd, msg, wParam, lParam);

    return DefWindowProc( hWnd, msg, wParam, lParam );
} 



INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{

	//Création de la fenêtre windows
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "PostEffectProgram", NULL };
    RegisterClassEx( &wc );

	Vector2i screenSize (1024, 1024);

    g_hWnd = CreateWindow( "PostEffectProgram", "PostEffectProgram",
                              WS_OVERLAPPEDWINDOW, 0, 0, screenSize.x, screenSize.y,
                              NULL, NULL, wc.hInstance, NULL );


	// Initialisation des modules
	GBufferRenderer* pGBRenderer = GBufferRenderer::GetSingleton();
	PostRenderer*	 pPostRenderer = PostRenderer::GetSingleton();
	Scene*			 pScene = Scene::GetSingleton();

	pGBRenderer->Initialize(g_hWnd, screenSize.x, screenSize.y);
	pPostRenderer->Initialize(pGBRenderer->GetBackbufferSize());
	pPostRenderer->SetGBuffer(pGBRenderer->GetGBuffer());
	pPostRenderer->EnablePostProcess(PostRenderer::PE_DeferredLighting);


    if( SUCCEEDED( CreateScene() ) )
    {
        ShowWindow( g_hWnd, SW_SHOWDEFAULT );
        UpdateWindow( g_hWnd );

        MSG msg;
        ZeroMemory( &msg, sizeof(msg) );

		// Boucle principale
        while( msg.message!=WM_QUIT )
        {
            if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );

			}
			else
			{
				pGBRenderer->RenderScene();
				pPostRenderer->RenderPostProcesses();
			}

        }
    }

	pScene->DestroySingleton();
	pGBRenderer->DestroySingleton();
	pPostRenderer->DestroySingleton();

    UnregisterClass( "PostEffectProgram", wc.hInstance );
    return 0;
}



