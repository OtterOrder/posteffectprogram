

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0500 
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500 
#endif


#include "Camera.h"
#include <Windows.h>
#include <stdio.h>
#include <d3dx9.h>


//===========================================================================//
// Constructeur CBaseCamera					                                 //
//===========================================================================//
CBaseCamera::CBaseCamera()
{
    m_cKeysDown = 0;
    ZeroMemory( m_aKeys, sizeof(BYTE)*CAM_MAX_KEYS );

    // Attributs de la matrice vue
    D3DXVECTOR3 vEyePt    = D3DXVECTOR3(0.0f,0.0f,0.0f);
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3(0.0f,0.0f,1.0f);

    // Matrice de vue
    SetViewParams( &vEyePt, &vLookatPt );

    // Matrice de projection
    SetProjParams( D3DX_PI/4, 1.0f, 1.0f, 1000.0f );

    GetCursorPos( &m_ptLastMousePosition );
    m_bMouseLButtonDown = false;
    m_bMouseMButtonDown = false;
    m_bMouseRButtonDown = false;
    m_nCurrentButtonMask = 0;
    m_nMouseWheelDelta = 100.f;

    m_fCameraYawAngle = 0.0f;
    m_fCameraPitchAngle = 0.0f;

    SetRect( &m_rcDrag, LONG_MIN, LONG_MIN, LONG_MAX, LONG_MAX );
    m_vVelocity     = D3DXVECTOR3(0,0,0);
    m_bMovementDrag = false;
    m_vVelocityDrag = D3DXVECTOR3(0,0,0);
    m_fDragTimer    = 0.0f;
    m_fTotalDragTimeToZero = 0.25;
    m_vRotVelocity = D3DXVECTOR2(0,0);

    m_fRotationScaler = 0.01f;           
    m_fMoveScaler = 5.0f;           

    m_bInvertPitch = false;
    m_bEnableYAxisMovement = true;
    m_bEnablePositionMovement = true;

    m_vMouseDelta   = D3DXVECTOR2(0,0);
    m_fFramesToSmoothMouseData = 2.0f;

    m_bClipToBoundary = false;
    m_vMinBoundary = D3DXVECTOR3(-1,-1,-1);
    m_vMaxBoundary = D3DXVECTOR3(1,1,1);

    m_bResetCursorAfterMove = false;
}

//===========================================================================//
// Le client peut appeller ceci pour changer la position et la direction	 //
// de la caméra.															 //
//===========================================================================//
VOID CBaseCamera::SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt )
{
    if( NULL == pvEyePt || NULL == pvLookatPt )
        return;

    m_vDefaultEye = m_vEye = *pvEyePt;
    m_vDefaultLookAt = m_vLookAt = *pvLookatPt;

    // Calcul de la matrice de vue
    D3DXVECTOR3 vUp(0,1,0);
    D3DXMatrixLookAtLH( &m_mView, pvEyePt, pvLookatPt, &vUp );

    D3DXMATRIX mInvView;
    D3DXMatrixInverse( &mInvView, NULL, &m_mView );

    D3DXVECTOR3* pZBasis = (D3DXVECTOR3*) &mInvView._31;

    m_fCameraYawAngle   = atan2f( pZBasis->x, pZBasis->z );
    float fLen = sqrtf(pZBasis->z*pZBasis->z + pZBasis->x*pZBasis->x);
    m_fCameraPitchAngle = -atan2f( pZBasis->y, fLen );
}

//===========================================================================//
// Calculer la matrice de projection basée sur les paramètres.				 //
//===========================================================================//
VOID CBaseCamera::SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane,
                                   FLOAT fFarPlane )
{
    // Attributs pour la matrice de projection
    m_fFOV        = fFOV;
    m_fAspect     = fAspect;
    m_fNearPlane  = fNearPlane;
    m_fFarPlane   = fFarPlane;

    D3DXMatrixPerspectiveFovLH( &m_mProj, fFOV, fAspect, fNearPlane, fFarPlane );
}

//===========================================================================//
// Ecoute des messages pour la caméra.										 //
//===========================================================================//
LRESULT CBaseCamera::HandleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    UNREFERENCED_PARAMETER( hWnd );
    UNREFERENCED_PARAMETER( lParam );

    switch( uMsg )
    {
        case WM_KEYDOWN:
        {
            D3DUtil_CameraKeys mappedKey = MapKey( (UINT)wParam );
            if( mappedKey != CAM_UNKNOWN )
            {
                if( FALSE == IsKeyDown(m_aKeys[mappedKey]) )
                {
                    m_aKeys[ mappedKey ] = KEY_WAS_DOWN_MASK | KEY_IS_DOWN_MASK;
                    ++m_cKeysDown;
                }
            }
            break;
        }

        case WM_KEYUP:
        {
            D3DUtil_CameraKeys mappedKey = MapKey( (UINT)wParam );
            if( mappedKey != CAM_UNKNOWN && (DWORD)mappedKey < 8 )
            {
                m_aKeys[ mappedKey ] &= ~KEY_IS_DOWN_MASK;
                --m_cKeysDown;
            }
            break;
        }

        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
        case WM_LBUTTONDBLCLK:
        {
            // Calcul le drag rectangle en coordonnées écran
            POINT ptCursor = { (short)LOWORD(lParam), (short)HIWORD(lParam) };

            // Mise à jour variable d'état
            if( ( uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK ) && PtInRect( &m_rcDrag, ptCursor ) )
                { m_bMouseLButtonDown = true; m_nCurrentButtonMask |= MOUSE_LEFT_BUTTON; }
           /* if( ( uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK ) && PtInRect( &m_rcDrag, ptCursor ) )
                { m_bMouseMButtonDown = true; m_nCurrentButtonMask |= MOUSE_MIDDLE_BUTTON; }
            if( ( uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK ) && PtInRect( &m_rcDrag, ptCursor ) )
                { m_bMouseRButtonDown = true; m_nCurrentButtonMask |= MOUSE_RIGHT_BUTTON; }*/

            // Capture la souris, donc si le bouton de la souris est relaché en dehors de la fenêtre 
            // il y a aura un message WM_LBUTTONUP
            SetCapture(hWnd);
            GetCursorPos( &m_ptLastMousePosition );
            return TRUE;
        }

        case WM_RBUTTONUP: 
        case WM_MBUTTONUP: 
        case WM_LBUTTONUP:   
        {
            // Mise à jour variables d'état
            if( uMsg == WM_LBUTTONUP ) { m_bMouseLButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_LEFT_BUTTON; }
            if( uMsg == WM_MBUTTONUP ) { m_bMouseMButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_MIDDLE_BUTTON; }
            if( uMsg == WM_RBUTTONUP ) { m_bMouseRButtonDown = false; m_nCurrentButtonMask &= ~MOUSE_RIGHT_BUTTON; }

            // Arret capture si aucun bouton est appuyé
            if( !m_bMouseLButtonDown  && 
                !m_bMouseRButtonDown &&
                !m_bMouseMButtonDown )
            {
                ReleaseCapture();
            }
            break;
        }

        case WM_CAPTURECHANGED:
        {
            if( (HWND)lParam != hWnd )
            {
                if( (m_nCurrentButtonMask & MOUSE_LEFT_BUTTON) ||
                    (m_nCurrentButtonMask & MOUSE_MIDDLE_BUTTON) ||
                    (m_nCurrentButtonMask & MOUSE_RIGHT_BUTTON) )
                {
                    m_bMouseLButtonDown = false;
                    m_bMouseMButtonDown = false;
                    m_bMouseRButtonDown = false;
                    m_nCurrentButtonMask &= ~MOUSE_LEFT_BUTTON;
                    m_nCurrentButtonMask &= ~MOUSE_MIDDLE_BUTTON;
                    m_nCurrentButtonMask &= ~MOUSE_RIGHT_BUTTON;
                    ReleaseCapture();
                }
            }
            break;
        }

        case WM_MOUSEWHEEL: 
		{
            // Mise à jour variables d'état
			int acc=(short)HIWORD(wParam);
			if(acc<1200.0f)
				m_nMouseWheelDelta += (short)HIWORD(wParam);
			if(m_nMouseWheelDelta<0)
				m_nMouseWheelDelta=40;
            break;
		}
    }

    return FALSE;
}

//===========================================================================//
// Récupération des entrée pour calculer vitesse.    						 //
//===========================================================================//
void CBaseCamera::GetInput( bool bGetKeyboardInput, bool bGetMouseInput, bool bGetGamepadInput, bool bResetCursorAfterMove )
{
    m_vKeyboardDirection = D3DXVECTOR3(0,0,0);
    if( bGetKeyboardInput )
    {
        // Mise à jour accélération basée sur les états clavier
        if( IsKeyDown(m_aKeys[CAM_MOVE_FORWARD]) )
            m_vKeyboardDirection.z += 1.0f;
        if( IsKeyDown(m_aKeys[CAM_MOVE_BACKWARD]) )
            m_vKeyboardDirection.z -= 1.0f;
        if( m_bEnableYAxisMovement )
        {
            if( IsKeyDown(m_aKeys[CAM_MOVE_UP]) )
                m_vKeyboardDirection.y += 1.0f;
            if( IsKeyDown(m_aKeys[CAM_MOVE_DOWN]) )
                m_vKeyboardDirection.y -= 1.0f;
        }
        if( IsKeyDown(m_aKeys[CAM_STRAFE_RIGHT]) )
            m_vKeyboardDirection.x += 1.0f;
        if( IsKeyDown(m_aKeys[CAM_STRAFE_LEFT]) )
            m_vKeyboardDirection.x -= 1.0f;
    }

    if( bGetMouseInput )
    {
        UpdateMouseDelta();
    }
}

//===========================================================================//
// Récupération delta souris basé sur les mouvements   						 //
//===========================================================================//
void CBaseCamera::UpdateMouseDelta()
{
    POINT ptCurMouseDelta;
    POINT ptCurMousePos;
    
    // Position courante de la souris
    GetCursorPos( &ptCurMousePos );

    // Calcul de la distance effectuée depuis la dernière frame
    ptCurMouseDelta.x = ptCurMousePos.x - m_ptLastMousePosition.x;
    ptCurMouseDelta.y = ptCurMousePos.y - m_ptLastMousePosition.y;

    // Enregistre la positon courante pour la prochaine fois
    m_ptLastMousePosition = ptCurMousePos;

   /* if( m_bResetCursorAfterMove)
    {
        POINT ptCenter;

        MONITORINFO mi;
        mi.cbSize = sizeof(MONITORINFO);
        ptCenter.x = (mi.rcMonitor.left + mi.rcMonitor.right) / 2;
        ptCenter.y = (mi.rcMonitor.top + mi.rcMonitor.bottom) / 2;
        SetCursorPos( ptCenter.x, ptCenter.y );
        m_ptLastMousePosition = ptCenter;
    }*/

    // Lissage des données 
    float fPercentOfNew =  1.0f / m_fFramesToSmoothMouseData;
    float fPercentOfOld =  1.0f - fPercentOfNew;
    m_vMouseDelta.x = m_vMouseDelta.x*fPercentOfOld + ptCurMouseDelta.x*fPercentOfNew;
    m_vMouseDelta.y = m_vMouseDelta.y*fPercentOfOld + ptCurMouseDelta.y*fPercentOfNew;

    m_vRotVelocity = m_vMouseDelta * m_fRotationScaler;
}

//===========================================================================//
// Mise à jour vélocité                                						 //
//===========================================================================//
void CBaseCamera::UpdateVelocity( float fElapsedTime )
{
    D3DXMATRIX mRotDelta;

    D3DXVECTOR3 vAccel = m_vKeyboardDirection;

    // Vecteur normalisé, donc si ça bouge selon deux axes, 
    // la caméra ne bougera pas plus vite que si il y avait qu'un axe.
    D3DXVec3Normalize( &vAccel, &vAccel );

    // Mise à l'échelle du vecteur d'accélération
	vAccel *= (m_nMouseWheelDelta)/100.0f;
    vAccel *= m_fMoveScaler;
	

    if( m_bMovementDrag )
    {
        // Est ce qu'il y a eu une accélération cette frame ?
        if( D3DXVec3LengthSq( &vAccel ) > 0 )
        {
            // Si oui, l'utilisateur a appuyé sur un bouton de mouvement
            // on change directement la vélocité en accéleration 
            m_vVelocity = vAccel;
            m_fDragTimer = m_fTotalDragTimeToZero;
            m_vVelocityDrag = vAccel / m_fDragTimer;
        }
        else 
        {
            // Si non aucune touche n'a été appuyée, on décrémente doucement jusqu'à 0
            if( m_fDragTimer > 0 )
            {
                m_vVelocity -= m_vVelocityDrag * fElapsedTime;
                m_fDragTimer -= fElapsedTime;
            }
            else
            {
                m_vVelocity = D3DXVECTOR3(0,0,0);
            }
        }
    }
    else
    {
        // Pas de glissement, on change immédiatement la vélocitée
        m_vVelocity = vAccel;
    }
}

//===========================================================================//
// Clamp de pV entre m_vMinBoundary et m_vMaxBoundary      					 //
//===========================================================================//
void CBaseCamera::ConstrainToBoundary( D3DXVECTOR3* pV )
{ 
    pV->x = __max(pV->x, m_vMinBoundary.x);
    pV->y = __max(pV->y, m_vMinBoundary.y);
    pV->z = __max(pV->z, m_vMinBoundary.z);

    pV->x = __min(pV->x, m_vMaxBoundary.x);
    pV->y = __min(pV->y, m_vMaxBoundary.y);
    pV->z = __min(pV->z, m_vMaxBoundary.z);
}



//===========================================================================//
// Mappe un clavier virtuel windows dans une énum       					 //
//===========================================================================//
D3DUtil_CameraKeys CBaseCamera::MapKey( UINT nKey )
{
    // Ceci peut être amélioré par une méthode redéfinissable par l'utilisateur 
    switch( nKey )
    {
        case VK_CONTROL:  return CAM_CONTROLDOWN;
        case VK_LEFT:  return CAM_STRAFE_LEFT;
        case VK_RIGHT: return CAM_STRAFE_RIGHT;
        case VK_UP:    return CAM_MOVE_FORWARD;
        case VK_DOWN:  return CAM_MOVE_BACKWARD;
        case VK_PRIOR: return CAM_MOVE_UP;        
        case VK_NEXT:  return CAM_MOVE_DOWN;      

        case 'Q':      return CAM_STRAFE_LEFT;
        case 'D':      return CAM_STRAFE_RIGHT;
        case 'Z':      return CAM_MOVE_FORWARD;
        case 'S':      return CAM_MOVE_BACKWARD;
        case 'A':      return CAM_MOVE_DOWN;
        case 'E':      return CAM_MOVE_UP;

        case VK_NUMPAD4: return CAM_STRAFE_LEFT;
        case VK_NUMPAD6: return CAM_STRAFE_RIGHT;
        case VK_NUMPAD8: return CAM_MOVE_FORWARD;
        case VK_NUMPAD2: return CAM_MOVE_BACKWARD;
        case VK_NUMPAD9: return CAM_MOVE_UP;        
        case VK_NUMPAD3: return CAM_MOVE_DOWN;      

        case VK_HOME:   return CAM_RESET;
    }

    return CAM_UNKNOWN;
}

//===========================================================================//
// Remet la position de la caméra par défaut            					 //
//===========================================================================//
VOID CBaseCamera::Reset()
{
    SetViewParams( &m_vDefaultEye, &m_vDefaultLookAt );
}

//===========================================================================//
// Constructeur CFirstPersonCamera			            					 //
//===========================================================================//
CFirstPersonCamera::CFirstPersonCamera() :
    m_nActiveButtonMask( 0x07 )
{
    m_bRotateWithoutButtonDown = false;
}

//===========================================================================//
// Mise à jour matrice de vue basée sur les évènement et le temps			 //
//===========================================================================//
VOID CFirstPersonCamera::FrameMove( FLOAT fElapsedTime )
{
    /*if( DXUTGetGlobalTimer()->IsStopped() )
        fElapsedTime = 1.0f / DXUTGetFPS();*/

    if( IsKeyDown(m_aKeys[CAM_RESET]) )
        Reset();

    // Evenements clavier, souris
    GetInput( m_bEnablePositionMovement, ( m_nActiveButtonMask & m_nCurrentButtonMask ) || m_bRotateWithoutButtonDown, true, m_bResetCursorAfterMove );

    //if( (m_nActiveButtonMask & m_nCurrentButtonMask) || m_bRotateWithoutButtonDown )
    //    UpdateMouseDelta( fElapsedTime );

    // Obtention de la vélocité basée sur les évènements claver
    UpdateVelocity( fElapsedTime );

    // Simple méthode d'euler pour calculer le delta de la position
    D3DXVECTOR3 vPosDelta = m_vVelocity * fElapsedTime;

    // Si il y a rotation de la caméra 
    if( (m_nActiveButtonMask & m_nCurrentButtonMask) ||
        m_bRotateWithoutButtonDown  )
    {
        // Mise à jour pitch & yaw grâce au mouvement de la souris
        float fYawDelta   = m_vRotVelocity.x;
        float fPitchDelta = m_vRotVelocity.y;

        // Invertion pitch si besoin
        if( m_bInvertPitch )
            fPitchDelta = -fPitchDelta;

        m_fCameraPitchAngle += fPitchDelta;
        m_fCameraYawAngle   += fYawDelta;

        // Limitation pitch haut et bas
        m_fCameraPitchAngle = __max( -D3DX_PI/2.0f,  m_fCameraPitchAngle );
        m_fCameraPitchAngle = __min( +D3DX_PI/2.0f,  m_fCameraPitchAngle );
    }

    // On fait une matrice de rotation basée sur les yaw et pitch de la caméra
    D3DXMATRIX mCameraRot;
    D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, m_fCameraPitchAngle, 0 );

    // Transformation des vecteurs basé sur matrice de rotation de la caméra
    D3DXVECTOR3 vWorldUp, vWorldAhead;
    D3DXVECTOR3 vLocalUp    = D3DXVECTOR3(0,1,0);
    D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(0,0,1);
    D3DXVec3TransformCoord( &vWorldUp, &vLocalUp, &mCameraRot );
    D3DXVec3TransformCoord( &vWorldAhead, &vLocalAhead, &mCameraRot );

    // Transforme le delta de la position par la caméra de rotation
    D3DXVECTOR3 vPosDeltaWorld;
    if( !m_bEnableYAxisMovement )
    {
        // Si on restreint le mouvement des Y, on inclut pas le pitch
        // quand on transforme la position du vecteur position delta
        D3DXMatrixRotationYawPitchRoll( &mCameraRot, m_fCameraYawAngle, 0.0f, 0.0f );
    }
    D3DXVec3TransformCoord( &vPosDeltaWorld, &vPosDelta, &mCameraRot );

    // On bouge la position de l'oeil
    m_vEye += vPosDeltaWorld;
    if( m_bClipToBoundary )
        ConstrainToBoundary( &m_vEye );

    // Mise à jour du lookAt grâce à la position de l'oeil 
    m_vLookAt = m_vEye + vWorldAhead;

    // Mise à jour matrice de vue
    D3DXMatrixLookAtLH( &m_mView, &m_vEye, &m_vLookAt, &vWorldUp );

    D3DXMatrixInverse( &m_mCameraWorld, NULL, &m_mView );
}

//===========================================================================//
// Active ou désactive chaque boutons de la souris pour la rotation			 //
//===========================================================================//
void CFirstPersonCamera::SetRotateButtons( bool bLeft, bool bMiddle, bool bRight, bool bRotateWithoutButtonDown )
{
    m_nActiveButtonMask = ( bLeft ? MOUSE_LEFT_BUTTON : 0 ) |
                          ( bMiddle ? MOUSE_MIDDLE_BUTTON : 0 ) |
                          ( bRight ? MOUSE_RIGHT_BUTTON : 0 );
    m_bRotateWithoutButtonDown = bRotateWithoutButtonDown;
}
