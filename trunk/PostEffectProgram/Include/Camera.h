#pragma once

#include <d3dx9.h>

enum D3DUtil_CameraKeys
{
    CAM_STRAFE_LEFT = 0,
    CAM_STRAFE_RIGHT,
    CAM_MOVE_FORWARD,
    CAM_MOVE_BACKWARD,
    CAM_MOVE_UP,
    CAM_MOVE_DOWN,
    CAM_RESET,
    CAM_CONTROLDOWN,
    CAM_MAX_KEYS,
    CAM_UNKNOWN = 0xFF
};

#define KEY_WAS_DOWN_MASK 0x80
#define KEY_IS_DOWN_MASK  0x01

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08

//===========================================================================//
// Classe abstraite pour une caméra de base : rotations et mouvements        //
//===========================================================================//
class CBaseCamera
{
public:
    CBaseCamera();

	//===========================================================================//
    // Fonctions à appeler par l'utilisateur									 //
	//===========================================================================//
    virtual LRESULT HandleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual void    FrameMove( FLOAT fElapsedTime ) = 0;

	//===========================================================================//
    // Fonctions pour spécifier les paramètres des matrices						 //
	//===========================================================================//
    virtual void Reset(); 
    virtual void SetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt );
    virtual void SetProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane );

	//===========================================================================//
    // Fonctions pour changer les comportements									 //
	//===========================================================================//
    virtual void SetDragRect( RECT &rc ) { m_rcDrag = rc; }
    void SetInvertPitch( bool bInvertPitch ) { m_bInvertPitch = bInvertPitch; }
    void SetDrag( bool bMovementDrag, FLOAT fTotalDragTimeToZero = 0.25f ) { m_bMovementDrag = bMovementDrag; m_fTotalDragTimeToZero = fTotalDragTimeToZero; }
    void SetEnableYAxisMovement( bool bEnableYAxisMovement ) { m_bEnableYAxisMovement = bEnableYAxisMovement; }
    void SetEnablePositionMovement( bool bEnablePositionMovement ) { m_bEnablePositionMovement = bEnablePositionMovement; }
    void SetClipToBoundary( bool bClipToBoundary, D3DXVECTOR3* pvMinBoundary, D3DXVECTOR3* pvMaxBoundary ) { m_bClipToBoundary = bClipToBoundary; if( pvMinBoundary ) m_vMinBoundary = *pvMinBoundary; if( pvMaxBoundary ) m_vMaxBoundary = *pvMaxBoundary; }
    void SetScalers( FLOAT fRotationScaler = 0.01f, FLOAT fMoveScaler = 5.0f )  { m_fRotationScaler = fRotationScaler; m_fMoveScaler = fMoveScaler; }
    void SetNumberOfFramesToSmoothMouseData( int nFrames ) { if( nFrames > 0 ) m_fFramesToSmoothMouseData = (float)nFrames; }
    void SetResetCursorAfterMove( bool bResetCursorAfterMove ) { m_bResetCursorAfterMove = bResetCursorAfterMove; }

	//===========================================================================//
    // Obtention des états														 //
	//===========================================================================//
    const D3DXMATRIX*  GetViewMatrix() const { return &m_mView; }
    const D3DXMATRIX*  GetProjMatrix() const { return &m_mProj; }
    const D3DXVECTOR3* GetEyePt() const      { return &m_vEye; }
    const D3DXVECTOR3* GetLookAtPt() const   { return &m_vLookAt; }
    float GetNearClip() const { return m_fNearPlane; }
    float GetFarClip() const { return m_fFarPlane; }

    bool IsBeingDragged() const         { return (m_bMouseLButtonDown || m_bMouseMButtonDown || m_bMouseRButtonDown); }
    bool IsMouseLButtonDown() const     { return m_bMouseLButtonDown; } 
    bool IsMouseMButtonDown() const     { return m_bMouseMButtonDown; } 
    bool IsMouseRButtonDown() const     { return m_bMouseRButtonDown; } 

protected:

	//===========================================================================//
    // Fonctions pour mapper le WM_KEYDOWN pour un enum D3DUtil_CameraKeys 		 //
	//===========================================================================//
    virtual D3DUtil_CameraKeys MapKey( UINT nKey );    
    bool IsKeyDown( BYTE key ) const { return( (key & KEY_IS_DOWN_MASK) == KEY_IS_DOWN_MASK ); }
    bool WasKeyDown( BYTE key ) const { return( (key & KEY_WAS_DOWN_MASK) == KEY_WAS_DOWN_MASK ); }

    void ConstrainToBoundary( D3DXVECTOR3* pV );
    void UpdateMouseDelta();
    void UpdateVelocity( float fElapsedTime );
    void GetInput( bool bGetKeyboardInput, bool bGetMouseInput, bool bGetGamepadInput, bool bResetCursorAfterMove );

    D3DXMATRIX            m_mView;                		// Matrice de vue 
    D3DXMATRIX            m_mProj;                		// Matrice de projection

    int                   m_cKeysDown;            		// Nombre de touches appuyées
    BYTE                  m_aKeys[CAM_MAX_KEYS];  		// Etat de l'entrée - KEY_WAS_DOWN_MASK|KEY_IS_DOWN_MASK
    D3DXVECTOR3           m_vKeyboardDirection;   		// Vecteur de direction de l'entrée clavier
    POINT                 m_ptLastMousePosition;  		// Dernière position absolue du curseur
    bool                  m_bMouseLButtonDown;    		// Vrai si le bouton gauche est appuyé 
    bool                  m_bMouseMButtonDown;    		// Vrai si le bouton du milieu est appuyé 
    bool                  m_bMouseRButtonDown;    		// Vrai si le bouton droit est appuyé 
    int                   m_nCurrentButtonMask;   		// Masque pour savoir quel bouton est appuyé
    int                   m_nMouseWheelDelta;     		// Niveau de la molette
    D3DXVECTOR2           m_vMouseDelta;          		// Delta relatif de la souris lissé sur quelques frames
    float                 m_fFramesToSmoothMouseData;	// Nombre de frames à lisser

    D3DXVECTOR3           m_vDefaultEye;          		// Position caméra par défaut
    D3DXVECTOR3           m_vDefaultLookAt;       		// LookAt par défaut
    D3DXVECTOR3           m_vEye;                 		// Position caméra
    D3DXVECTOR3           m_vLookAt;              		// LookAt
    float                 m_fCameraYawAngle;      		// Yaw angle
    float                 m_fCameraPitchAngle;    		// Pitch angle

    RECT                  m_rcDrag;               		// Rectangle où l'on peut initialiser le glissement
    D3DXVECTOR3           m_vVelocity;            		// Vitesse caméra
    bool                  m_bMovementDrag;        		// Si vrai, alors le mouvement de caméra s'arrête
    D3DXVECTOR3           m_vVelocityDrag;        		// Force glissement
    FLOAT                 m_fDragTimer;           		// Timer décompte pour appliquer le glissement
    FLOAT                 m_fTotalDragTimeToZero; 		// Temps prit pour que la vitesse aille de 0 à son max
    D3DXVECTOR2           m_vRotVelocity;         		// Vitesse caméra

    float                 m_fFOV;                 		// FOV
    float                 m_fAspect;              		// Aspect ratio
    float                 m_fNearPlane;           		// Near plane
    float                 m_fFarPlane;            		// Far plane

    float                 m_fRotationScaler;      		// Scaler rotation
    float                 m_fMoveScaler;          		// Scaler mouvement

    bool                  m_bInvertPitch;         		// Invertion pitch axis
    bool                  m_bEnablePositionMovement;	// Si vrai, alors l'utilisateur peut translater la camera 
    bool                  m_bEnableYAxisMovement; 		// Si vrai, alors la camera peut bouger sur l'axe des y

    bool                  m_bClipToBoundary;      		// Si vrai, alors la caméra sera clippée
    D3DXVECTOR3           m_vMinBoundary;         		// Point minimum 
    D3DXVECTOR3           m_vMaxBoundary;         		// Poinr maximum

    bool                  m_bResetCursorAfterMove;		// Si vrai, la classe redémarerra la position du curseur 
};

//===========================================================================//
// Classe caméra vue à la première personne.						 		 //
//===========================================================================//
class CFirstPersonCamera : public CBaseCamera
{
public:
    CFirstPersonCamera();

	//===========================================================================//
	// A appeler par l'utilisateur										 		 //
	//===========================================================================//
    virtual void FrameMove( FLOAT fElapsedTime );

    //===========================================================================//
	// Fonctions pour changer le comportement							 		 //
	//===========================================================================//
    void SetRotateButtons( bool bLeft, bool bMiddle, bool bRight, bool bRotateWithoutButtonDown = false );

    //===========================================================================//
	// Fonctions pour obtenir les états									 		 //
	//===========================================================================//
    D3DXMATRIX*  GetWorldMatrix()            { return &m_mCameraWorld; }

    const D3DXVECTOR3* GetWorldRight() const { return (D3DXVECTOR3*)&m_mCameraWorld._11; } 
    const D3DXVECTOR3* GetWorldUp() const    { return (D3DXVECTOR3*)&m_mCameraWorld._21; }
    const D3DXVECTOR3* GetWorldAhead() const { return (D3DXVECTOR3*)&m_mCameraWorld._31; }
    const D3DXVECTOR3* GetEyePt() const      { return (D3DXVECTOR3*)&m_mCameraWorld._41; }

protected:
    D3DXMATRIX m_mCameraWorld;       // Matrice monde de la caméra

    int        m_nActiveButtonMask;  // Masque pour savoir quel bouton est appuyé
    bool       m_bRotateWithoutButtonDown;
};