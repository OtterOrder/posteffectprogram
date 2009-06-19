
#include <Windows.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#pragma warning( default : 4996 )

#include "Camera.h"
#include "Time.h"


#define HAUTEUR 800
#define LARGEUR 600

// Variables globales

LPDIRECT3D9             g_pD3D       = NULL; 
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 
CFirstPersonCamera 	    g_pCamera;
Time					g_Timer;

////. Test
#include "GraphicEntity.h"
GraphicEntity g_GraphicEntity;
////.

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
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );


    return S_OK;
}


HRESULT InitGeometry()
{
	////. Test ////////////////////////////////////////////////
	g_GraphicEntity.Initialize(g_pd3dDevice, "..\\Datas\\Meshes\\bat.x");

	g_GraphicEntity.GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\batalbedo.dds", Material::Diffuse);
	g_GraphicEntity.GetMaterial()->SetTexture(g_pd3dDevice, "..\\Datas\\Textures\\normal.jpg", Material::Normal);

	g_GraphicEntity.GetMaterial()->SetPixelShader(g_pd3dDevice, "..\\Datas\\Shaders\\PSTest.fs", "PSTextureDisplay");
	////. /////////////////////////////////////////////////////

    return S_OK;
}

VOID Cleanup()
{
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

VOID SetupMatrices()
{
    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity( &matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	g_pd3dDevice->SetTransform(D3DTS_VIEW, g_pCamera.GetViewMatrix());


	g_pCamera.SetProjParams(D3DX_PI/4, (float)HAUTEUR/LARGEUR, 0.1f, 100.f);
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, g_pCamera.GetProjMatrix() );
}



VOID Render()
{

	g_pCamera.FrameMove(g_Timer.GetDeltaTimeF());

    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0,0,125), 1.0f, 0 );

	g_pd3dDevice->SetVertexShader(NULL);
	g_pd3dDevice->SetPixelShader (NULL);

    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {

        SetupMatrices();

		////. Test ////////////////////////////////////////////////
		
		g_GraphicEntity.Draw(g_pd3dDevice);
		////.//////////////////////////////////////////////////////

        g_pd3dDevice->EndScene();
    }

    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
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
					PostQuitMessage( 0 );
					return 0;
				}
			}
		 }
		    

    }

	g_pCamera.HandleMessages(hWnd, msg, wParam, lParam);

    return DefWindowProc( hWnd, msg, wParam, lParam );
} 



INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "PostEffectProgram", NULL };
    RegisterClassEx( &wc );

    HWND hWnd = CreateWindow( "PostEffectProgram", "PostEffectProgram",
                              WS_OVERLAPPEDWINDOW, 100, 100, HAUTEUR, LARGEUR,
                              NULL, NULL, wc.hInstance, NULL );

    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        if( SUCCEEDED( InitGeometry() ) )
        {
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();

				g_Timer.EndF();
				g_Timer.EndE();
            }
        }
    }

    UnregisterClass( "PostEffectProgram", wc.hInstance );
    return 0;
}


