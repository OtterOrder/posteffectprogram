
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#pragma warning( default : 4996 )

#include "Camera.h"


#define HAUTEUR 800
#define LARGEUR 600

// Variables globales

LPDIRECT3D9             g_pD3D       = NULL; 
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL;
CFirstPersonCamera 	    g_pCamera;
float					g_fTimeElapsed = 0;
float					g_fFrameTime = 0;
float					g_fTime = 0;



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
    DEFAULT_VERTEX sommets[]=
	{
	{-20.f, 0.f, 20.f, 0x00000000}, 
	{20.f, 0.f, 20.f, 0x00000000},
	{-20.f, 0.f, 10.f, 0x00000000}, 
	{20.f, 0.f, 10.f, 0x00000000}, 
	{-20.f, 0.f, 0.f, 0x00000000}, 
	{20.f, 0.f, 0.f, 0x00000000}, 
	{-20.f, 0.f, -10.f, 0x00000000}, 
	{20.f, 0.f, -10.f, 0x00000000}, 
	{-20.f, 0.f, -20.f, 0x00000000}, 
	{20.f, 0.f, -20.f, 0x00000000}, 

	{20.f, 0.f, -20.f, 0x00000000}, 
	{20.f, 0.f, 20.f, 0x00000000},
	{10.f, 0.f, -20.f, 0x00000000}, 
	{10.f, 0.f, 20.f, 0x00000000}, 
	{0.0f, 0.f, -20.f, 0x00000000}, 
	{0.0f, 0.0f, 20.f, 0x00000000}, 
	{-10.f, 0.f, -20.f, 0x00000000}, 
	{-10.f, 0.f, 20.f, 0x00000000}, 
	{-20.f, 0.f, -20.f, 0x00000000}, 
	{-20.f, 0.f, 20.f, 0x00000000}, 
	
	};

	if(FAILED(g_pd3dDevice->CreateVertexBuffer(
		sizeof(sommets),
		D3DUSAGE_WRITEONLY,
		DEFAULT_FVF,
		D3DPOOL_DEFAULT,
		&g_pVB,
		NULL))
	)
		return E_FAIL;

	void * psommets;

	if(FAILED(g_pVB->Lock(0, sizeof(sommets), (void **)&psommets, 0)))
		return E_FAIL;

	memcpy(psommets,sommets,sizeof(sommets));

	g_pVB->Unlock();

    return S_OK;
}

VOID Cleanup()
{
    if( g_pVB != NULL )
        g_pVB->Release();

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


	g_pCamera.SetProjParams(D3DX_PI/4, (float)HAUTEUR/LARGEUR, 2.0f, 4000.f);
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, g_pCamera.GetProjMatrix() );
}



VOID Render()
{
	float time=(timeGetTime()/1000.f);
	g_fTimeElapsed = time-g_fFrameTime;
	g_fTime+=g_fTimeElapsed;
	g_fFrameTime=time;


	g_pCamera.FrameMove(g_fTimeElapsed);

    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {

        SetupMatrices();

		g_pd3dDevice->SetFVF(DEFAULT_FVF);

		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(DEFAULT_VERTEX));

		g_pd3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, 20);

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

	//Initialisation du temps :

	g_fFrameTime = timeGetTime()/1000.f;

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
            }
        }
    }

    UnregisterClass( "PostEffectProgram", wc.hInstance );
    return 0;
}



