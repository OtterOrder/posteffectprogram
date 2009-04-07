
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 )
#include <strsafe.h>
#pragma warning( default : 4996 ) 


#define HAUTEUR 800
#define LARGEUR 600

// Variables globales

LPDIRECT3D9             g_pD3D       = NULL; 
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; 
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL;

struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; 
    D3DXVECTOR3 normal;   
};


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)




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
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    for( DWORD i=0; i<50; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(50-1);
        pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
        pVertices[2*i+0].normal   = D3DXVECTOR3( sinf(theta), 0.0f, cosf(theta) );
        pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
        pVertices[2*i+1].normal   = D3DXVECTOR3( sinf(theta), 0.0f, cosf(theta) );
    }
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

    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, HAUTEUR/LARGEUR, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}



VOID Render()
{
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {

        SetupMatrices();

        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*50-2 );

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
    }

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
            }
        }
    }

    UnregisterClass( "PostEffectProgram", wc.hInstance );
    return 0;
}



