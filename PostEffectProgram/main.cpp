
#include <Windows.h>
#include <d3dx9.h>
#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )
#include <strsafe.h>
#pragma warning( default : 4996 )

#include "Camera.h"
#include "Time.h"
#include "Types.h"
#include "GBufferRenderer.h"
#include "PostRenderer.h"
#include "Scene.h"

#define HAUTEUR 800
#define LARGEUR 600

// Variables globales

HWND					g_hWnd;
LPDIRECT3D9             g_pD3D       = NULL; 
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 

GBufferRenderer*		g_GBRenderer;


struct DEFAULT_VERTEX
{
	FLOAT x,y,z;
	DWORD COLOR;
};
#define DEFAULT_FVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)



HRESULT InitD3D( HWND hWnd )
{
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth=LARGEUR;
	d3dpp.BackBufferHeight=HAUTEUR;
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE);


    return S_OK;
}


HRESULT InitGeometry()
{

	// Création de la scène 

	Scene* pScene = Scene::GetSingleton();

	GraphicEntity* pGE1 = pScene->CreateGraphicEntity();
	pGE1->Initialize(g_pd3dDevice, "..\\Datas\\Meshes\\sol.x");

	pGE1->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\sol_diffuse.jpg", Material::Diffuse);
	pGE1->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\sol_normal.jpg", Material::Normal);
	pGE1->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\sol_specular.jpg", Material::Specular);

	GraphicEntity* pGE2 = pScene->CreateGraphicEntity();
	pGE2->Initialize(g_pd3dDevice, "..\\Datas\\Meshes\\mur.X");

	pGE2->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\wall_diffuse.jpg", Material::Diffuse);
	pGE2->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\wall_normal.jpg", Material::Normal);
	pGE2->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\wall_specular.jpg", Material::Specular);

	GraphicEntity* pGE3 = pScene->CreateGraphicEntity();
	pGE3->Initialize(g_pd3dDevice, "..\\Datas\\Meshes\\boite.X");

	pGE3->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\box_diffuse.jpg", Material::Diffuse);
	pGE3->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\box_normal.jpg", Material::Normal);
	pGE3->GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\box_specular.jpg", Material::Specular);

    return S_OK;
}

VOID Cleanup()
{
	Scene::GetSingleton()->Clear();

	GBufferRenderer::GetSingleton()->Release();

    SAFE_RELEASE(g_pd3dDevice);

    SAFE_RELEASE(g_pD3D);

}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
			DestroyWindow(g_hWnd);
            return 0;

		case WM_MOUSEMOVE:
			POINT ptCursor;
            GetCursorPos( &ptCursor );
			g_pd3dDevice->SetCursorPosition( ptCursor.x, ptCursor.y, 0 );
			break;

		 case WM_SETCURSOR:
			SetCursor(NULL);
            g_pd3dDevice->ShowCursor( true );
            break;

		 case WM_KEYDOWN:
         {
            switch( wParam )
            {
                case VK_ESCAPE:
                {
					Cleanup();
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
	g_GBRenderer=GBufferRenderer::GetSingleton();


    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "PostEffectProgram", NULL };
    RegisterClassEx( &wc );

    g_hWnd = CreateWindow( "PostEffectProgram", "PostEffectProgram",
                              WS_OVERLAPPEDWINDOW, 100, 100, HAUTEUR, LARGEUR,
                              NULL, NULL, wc.hInstance, NULL );

    if( SUCCEEDED( InitD3D( g_hWnd ) ) )
    {
		g_GBRenderer->Init(g_pd3dDevice,HAUTEUR, LARGEUR);
        if( SUCCEEDED( InitGeometry() ) )
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
                    g_GBRenderer->RenderScene();

            }
        }
    }

	Scene::GetSingleton()->Destroy();
	GBufferRenderer::GetSingleton()->Destroy();
	PostRenderer::GetSingleton()->Destroy();

    UnregisterClass( "PostEffectProgram", wc.hInstance );
    return 0;
}



