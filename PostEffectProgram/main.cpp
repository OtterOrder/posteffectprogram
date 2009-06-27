
#include <Windows.h>
#include <strsafe.h>
#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )
#pragma warning( default : 4996 )

#include "Camera.h"
#include "Time.h"
#include "Types.h"
#include "GBufferRenderer.h"
#include "PostRenderer.h"
#include "Scene.h"

HWND      g_hWnd;


HRESULT InitGeometry()
{

	// Cr�ation de la sc�ne 

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

	GraphicEntity* pGE3 = pScene->CreateGraphicEntity();
	pGE3->Initialize("..\\Datas\\Meshes\\boite.X");

	pGE3->GetMaterial()->SetTexture("..\\Datas\\Textures\\box_diffuse.jpg", Material::Diffuse);
	pGE3->GetMaterial()->SetTexture("..\\Datas\\Textures\\box_normal.jpg", Material::Normal);
	pGE3->GetMaterial()->SetTexture("..\\Datas\\Textures\\box_specular.jpg", Material::Specular);

    return S_OK;
}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            GBufferRenderer::GetSingleton()->Destroy();
			Scene::GetSingleton()->Destroy();
            PostQuitMessage( 0 );
			DestroyWindow(g_hWnd);
            return 0;

		case WM_MOUSEMOVE:
			POINT ptCursor;
            GetCursorPos( &ptCursor );
			//g_pd3dDevice->SetCursorPosition( ptCursor.x, ptCursor.y, 0 );
			break;

		 case WM_SETCURSOR:
			SetCursor(NULL);
            //g_pd3dDevice->ShowCursor( true );
            break;

		 case WM_KEYDOWN:
         {
            switch( wParam )
            {
                case VK_ESCAPE:
                {
					GBufferRenderer::GetSingleton()->Destroy();
					Scene::GetSingleton()->Destroy();
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
	// Initialisation GBufferRenderer

	GBufferRenderer* pGBRenderer = GBufferRenderer::GetSingleton();
	PostRenderer*	 pPostRenderer = PostRenderer::GetSingleton();


    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "PostEffectProgram", NULL };
    RegisterClassEx( &wc );

    g_hWnd = CreateWindow( "PostEffectProgram", "PostEffectProgram",
                              WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
                              NULL, NULL, wc.hInstance, NULL );

   
	pGBRenderer->Initialize(g_hWnd, 800, 600);

	pPostRenderer->Initialize(GBufferRenderer::GetSingleton()->GetBackbufferSize());
	pPostRenderer->EnablePostProcess(PostRenderer::PE_DefferedLighting);


    if( SUCCEEDED( InitGeometry() ) )
    {
        ShowWindow( g_hWnd, SW_SHOWDEFAULT );
        UpdateWindow( g_hWnd );
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
				PostRenderer::GetSingleton()->RenderPostProcesses();
			}

        }
    }


	Scene::GetSingleton()->DestroySingleton();
	GBufferRenderer::GetSingleton()->DestroySingleton();
	PostRenderer::GetSingleton()->DestroySingleton();

    UnregisterClass( "PostEffectProgram", wc.hInstance );
    return 0;
}



