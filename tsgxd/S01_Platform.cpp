#include "H01_Platform.h"

#include <math.h>


typedef struct
{
    bool mWarningDisplayState;
#ifdef KR
    float mWarningDisplayTime;
#endif
    float mScreenXPosSize;
    float mScreenYPosSize;
    int mScreenSort;
    int mScreenXSize;
    int mScreenYSize;
    int mServerType;
    char uID[14];
    char uPW[33];
#ifndef KR
    int mUseWebPassword;
    char uWebPassword[72];
#endif
    int mUserSort;
    int mGoodFellow;
    int mLoginPlace;
    int mLoginPremium;
    int mSecondLoginSort;
    char uMousePassword[5];
    int SecretCardIndex01;
    int SecretCardIndex02;
    int mWebItem[50];
    //AVATAR_INFO mSelectAvt[3];
    //AVATAR_INFO mCreateAvatar;
    int mGiftItem[10][2];
    //AVATAR_INFO mUseAvatar;
    //BUFF_INFO mBuffInfo;
    //float mElementValue[35];
    BOOL mMoveZoneState;
    int mMoveZoneSort;
    int mMoveZoneValue;
    int mPreviousZoneNumber;
    int mPresentZoneNumber;
    int mNextZoneNumber;
    //ACTION_INFO mAction;
    //BOOL mCheckQuestCall;
    //float mQuestCallPostTime;
    //int mQuestCallPresentState;
    //int mQuestCallNPCNumber;
    //int mQuestCallSpeechIndex;
    //int mMaWhangGungTime;
    //BOOL mCheckSendActionPacket;
    //float mSendActionPacketPostTime;
    //int mCheckSendItemPacket;
    //float mSendItemPacketPostTime;
    //int mDemandGuildInfoSort;
    //int mTeacherStudentState;
    //float mBGMPlayPostTime;
    //int mHotKeyPage;
    //int mHotKeyIndex;
    //int mSelectObjSort;
    //int mSelectObjIndex;
    //int mSelectObjUniqueNumber;
    //int mTotalTargetNum;
    //int mTargetSort[10];
    //int mTargetServerIndex[5];
    //DWORD mTargetUniqueNumber[5];
    //float mSkillRunPostTime1;
    //BOOL mCheckHelpConditionEffect;
    //int mHelpConditionEffectIndex;
    //int mLevelBattleZoneNumberForMove;
    //BOOL mCheckLevelBattleOpenGateEffect;
    //float mLevelBattleOpenGateEffectFrame;
    //BOOL mCheckLevelBattle49TypeOpenEffect;
    //int mLevelBattle49TypeOpenEffectImageIndex;
    //int mLevelBattle49TypeRemainTime;
    //BOOL mCheckLevelBattle49TypeInfo;
    //int mLevelBattle49TypeInfo[4];
    //BOOL mCheckLevelBattle51TypeOpenEffect;
    //int mLevelBattle51TypeOpenEffectImageIndex;
    //BOOL mCheckLevelBattle53TypeOpenEffect;
    //int mLevelBattle53TypeOpenEffectImageIndex;
    //BOOL mCheckLevelBattle53TypeEffect1;
    //float mLevelBattle53TypeEffectFrame1;
    //BOOL mCheckLevelBattle53TypeEffect2;
    //float mLevelBattle53TypeEffectFrame2;
    //BOOL mCheckZone038Effect1;
    //float mZone038EffectFrame1;
    //BOOL mCheckZone038Effect2;
    //float mZone038EffectFrame2;
    //BOOL mCheckZone037Effect1;
    //float mZone037EffectFrame1;
    //BOOL mCheckZone037Effect2;
    //float mZone037EffectFrame2;
    //BOOL mCheckZone175TypeGateEffect1[10];
    //BOOL mCheckZone175TypeGateEffect2[10];
    //float mZone175TypeGateFrame[10];
    //BOOL mCheckZone194BattleOpenGateEffect;
    //float mZone194BattleOpenGateEffectFrame;
    //int mZone194BattleRemainTime;
    //int mZone194BattleInfo[4];
    //BOOL mCheckZone196Effect1;
    //float mZone196EffectFrame1;
    //BOOL mCheckZone196Effect2;
    //float mZone196EffectFrame2;
    //BOOL mCheck267TypeOpenGateEffect;
    //float m267TypeOpenGateEffectFrame;
    //int m267TypeRemainTime;
    //BOOL mCheck267TypeInfo;
    //int m267TypeInfo[4];
    //BOOL mCheckZone291Effect;
    //float mZone291EffectFrame;
    //int mHoisundoZoneNumberForMove;
    //BOOL mCheckZone297TypeGateEffect1[4];
    //BOOL mCheckZone297TypeGateEffect2[4];
    //float mZone297TypeGateFrame1[4];
    //float mZone297TypeGateFrame2[4];
    //BOOL mCheck297TypeInfo;
    //int mZone297TypeMonsterInfo[4];
    //BOOL mCheckZone200TypeGateEffect1[4];
    //BOOL mCheckZone200TypeGateEffect2[4];
    //float mZone200TypeGateFrame1[4];
    //float mZone200TypeGateFrame2[4];
    //BOOL mCheck200TypeInfo;
    //int mZone200TypeMonsterInfo[4];
    //int mEatDrugStateForAuto;
    //int mUseInventoryPage;
    //int mUseInventoryIndex;
    //int iTribeCallType;
    //BOOL bIsUseContinueSkill;
    //BOOL mCheckZone88TypeGateEffect[4];
    //float mZone88TypeGateFrame[4];
    //int mZone88OpenGateState[4];
    //BOOL mZone88TypeCenterEffect[2];
    //float mZone88TypeCenterFrame[2];
    //BOOL mCheckFourGuildTypeGateEffect1;
    //BOOL mCheckFourGuildTypeGateEffect2;
    //BOOL mCheckFourGuildTypeGateEffect3;
    //BOOL mCheckFourGuildTypeGateEffect4;
    //float mZoneFourGuildTypeGateFrame1;
    //float mZoneFourGuildTypeGateFrame2;
    //float mZoneFourGuildTypeGateFrame3;
    //float mZoneFourGuildTypeGateFrame4;
    //BOOL mCheckZone5TypeGateEffect2[10];
    //BOOL mCheckZone5TypeGateEffect1[10];
    //float mZone5TypeGateFrame[10];
    //BOOL mCheckZone54TypeGateEffect[4];
    //float mZone54TypeGateFrame[4];
    //BOOL mCheckLevelBattle319TypeOpenEffect;
    //BOOL mCheckLevelBattle319TypeInfo;
    //int mLevelBattle319TypeOpenEffectImageIndex;
    //int mLevelBattle319TypeRemainTime;
    //int mLevelBattle319TypeInfo[4];
    //int mZone319TypeTop20RankTribe[20];
    //int mZone319TypeTop20RankScore[20];
    //char mZone319TypeTop20RankName[20][13];
    //int mZone319TypeLineUpRank[20];
    //BOOL mCheck319TypeTop20RankState;
    //BOOL mShowTop4Rank;
    //int mGeneralExperienceUpRatio;
    //int mItemDropUpRatio;
    //int mKillOtherTribeAddValue;
    //int mPvPDamageUpRatio;
    //int mPvMDamageUpRatio;
    //int mMaxPotionEventNum;
    //int mPvPDamageUpTribe;
    //int mPvMDamageUpTribe;
    //int mMaxPotionEventTribe;
    //BOOL mbIsPVPDie;
    //int mStatBalance;
    //int mMixSkillWaitingTime[2];
    //int mBottleIndex;
    //int unk_CD8C[4];
    //#ifdef KR
    //int unk_CDFC;
    //int unk_129;
    //int unk_130;
    //int unk_131;
    //int unk_132;
    //#endif
    //int mClientTickNew;
    //int mServerMon;
    //int mServerDay;
    //int mServerHour;
    //int mServerMin;
    //char mServerWDay[20];
    //float mTrapPosition[5][3];
    //int unk_CE10;
    //int unk_CE14;
    //int unk_CE18;
    //int mOnlineAutoTime;
} MYINFO;
MYINFO mMYINFO;


BOOL mFullScreen = FALSE;
float hPresentElapsedSeconds;
HWND hMainWindow;
float hPostSecondsForFrame;
float hPostSecondsForMemory;
HINSTANCE hMainInstance;
float hPostSecondsForLogic;
BOOL hActiveProgram;
BOOL hAbortProgram;
float hPresentFrameSeconds;
static char* aEmptyChar = "";

static int ShowError(const char* lpText, ...)
{
    char tBuffer[1000];
    va_list args;
    va_start(args, lpText);
    vsprintf(tBuffer, lpText, args);
    va_end(args);
    #ifdef WIN32
    MessageBoxA( NULL, tBuffer, PLATFORM_NAME, MB_OK | MB_SYSTEMMODAL );
    #endif
    hAbortProgram = TRUE;
    return 0;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
    TRACR();
    switch ( nMss )
    {
    case WM_MOUSEMOVE:
        printf( "WM_MOUSEMOVE\n" );
        return 0;
    case WM_LBUTTONDOWN:
        printf( "WM_LBUTTONDOWN\n" );
        return 0;
    case WM_LBUTTONUP:
        printf( "WM_LBUTTONUP\n" );
        return 0;
    case WM_RBUTTONDOWN:
        printf( "WM_RBUTTONDOWN\n" );
        return 0;
    case WM_RBUTTONUP:
        printf( "WM_RBUTTONUP\n" );
        return 0;
    case WM_MBUTTONUP:
        printf( "WM_MBUTTONUP\n" );
        return 0;
    case WM_MOUSEWHEEL:
        printf( "WM_MOUSEWHEEL\n" );
        return 0;
    }
    return 0;
}

Vector2 oldPosition;
float oldWheel = 0.0f;
BOOL lMouseDown = FALSE, rMouseDown = FALSE, wMouseDown = FALSE;
BOOL ApplicationInput( void );
BOOL ApplicationInit( void );
void ApplicationFree( void );
void ApplicationMain( void );

#ifndef USE_RAYLIB
BOOL WindowShouldClose()
{
    MSG nMss;
	HACCEL hAccelTable = LoadAcceleratorsA( NULL, "" );
	if ( PeekMessageA( &nMss, NULL, 0, 0, PM_REMOVE ) )
	{
        TranslateMessage( &nMss );
		DispatchMessageA( &nMss );
		if( nMss.message == WM_QUIT )
		{
            return true;
		}
	}
    return false;
}
#endif

int main(void)
{
    if ( !ApplicationInit() )
    {
        return ShowError( "[[ERROR::Application()]]" );
    }

    while ( !WindowShouldClose() )
    {
        if( ApplicationInput() ) continue;
        ApplicationMain();
    }

    return 0;
}

#ifndef USE_RAYLIB
Vector2 GetMousePosition()
{
    return { 0.f, 0.f };
}
float GetMouseWheelMove()
{
    return 0.f;
}

enum MOUSE_BUTTON {
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT = 1,
    MOUSE_BUTTON_MIDDLE = 2,
};
BOOL IsMouseButtonDown( MOUSE_BUTTON mb )
{
    return FALSE;
}
BOOL IsMouseButtonUp( MOUSE_BUTTON mb )
{
    return FALSE;
}
#include <string>
LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
    switch( nMss )
	{
	case WM_CLOSE :
	case WM_DESTROY :
		PostQuitMessage( 0 );
		return 0;
    }
    return DefWindowProcA( hWnd, nMss, wPrm, lPrm );
}
BOOL InitWindow( int width, int height, std::string name )
{
    WNDCLASSEX wCls;
    HWND hWnd;
    MSG nMss;
    HINSTANCE hThis = 0;

    ZeroMemory( &wCls, sizeof(WNDCLASSEX) );

    wCls.cbSize	= sizeof( WNDCLASSEX );
	wCls.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wCls.lpfnWndProc = WinMainProcedure;
	wCls.cbClsExtra = 0;
	wCls.cbWndExtra = 0;
	wCls.hInstance = hThis;
	//wCls.hIcon = LoadIcon( hThis, MAKEINTRESOURCE( IDI_TROY ) );
	//wCls.hCursor = LoadCursor( hThis, MAKEINTRESOURCE( IDC_CURSOR01 ) );
	wCls.hbrBackground = (HBRUSH) GetStockObject( BLACK_BRUSH );
	wCls.lpszMenuName = NULL;
	wCls.lpszClassName = name.c_str();
	wCls.hIconSm = NULL;
	if( !RegisterClassExA( &wCls ) )
	{
		MessageBox( NULL, "[Error::RegisterClassEx()]", PLATFORM_NAME, ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}

    //mGXD.InitForSound();
	if( !mFullScreen ){

		RECT rc;
		HMENU hMenu = NULL;
		DWORD tDwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
		SetRect( &rc, 0, 0, mMYINFO.mScreenXSize, mMYINFO.mScreenYSize );
		AdjustWindowRect( &rc, tDwStyle, FALSE );
		hWnd = CreateWindowEx( NULL, PLATFORM_NAME, PLATFORM_NAME, tDwStyle, ( GetSystemMetrics( SM_CXSCREEN ) / 2 - ( ( rc.right - rc.left ) / 2 ) ),
																						( GetSystemMetrics( SM_CYSCREEN ) / 2 - ( ( rc.bottom - rc.top ) / 2 ) ),
																						(rc.right - rc.left),
																						(rc.bottom - rc.top), HWND_DESKTOP, NULL, hThis, NULL );
	}
	else
	{
		hWnd = CreateWindowEx( WS_EX_APPWINDOW, PLATFORM_NAME, PLATFORM_NAME, WS_POPUP, 0, 0, mMYINFO.mScreenXSize, mMYINFO.mScreenYSize, HWND_DESKTOP, NULL, hThis, NULL );
	}

	if( !hWnd )
	{
		MessageBox( NULL, "[Error::CreateWindowEx()]", PLATFORM_NAME, ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );

    hMainInstance = hThis;
    hMainWindow = hWnd;

    return TRUE;
}
#endif

BOOL ApplicationInput()
{
    Vector2 mousePosition = GetMousePosition();
    float mouseWheel = GetMouseWheelMove();
    if ( oldPosition.x != mousePosition.x || oldPosition.y != mousePosition.y )
    {
        oldPosition = mousePosition;
        WndProc( 0, WM_MOUSEMOVE, 0, 0 );
        return TRUE;
    }
    else if ( !lMouseDown && IsMouseButtonDown( MOUSE_BUTTON_LEFT ) )
    {
        lMouseDown = TRUE;
        WndProc( 0, WM_LBUTTONDOWN, 0, 0 );
        return TRUE;
    }
    else if ( lMouseDown && IsMouseButtonUp( MOUSE_BUTTON_LEFT ) )
    {
        lMouseDown = FALSE;
        WndProc( 0, WM_LBUTTONUP, 0, 0 );
        return TRUE;
    }
    else if ( !rMouseDown && IsMouseButtonDown( MOUSE_BUTTON_RIGHT ) )
    {
        rMouseDown = TRUE;
        WndProc( 0, WM_RBUTTONDOWN, 0, 0 );
        return TRUE;
    }
    else if ( rMouseDown && IsMouseButtonUp( MOUSE_BUTTON_RIGHT ) )
    {
        rMouseDown = FALSE;
        WndProc( 0, WM_RBUTTONUP, 0, 0 );
        return TRUE;
    }
    else if ( !wMouseDown && IsMouseButtonDown( MOUSE_BUTTON_MIDDLE ) )
    {
        wMouseDown = TRUE;
        WndProc( 0, WM_MBUTTONUP, 0, 0 );
        return TRUE;
    }
    else if ( wMouseDown && IsMouseButtonUp( MOUSE_BUTTON_MIDDLE ) )
    {
        wMouseDown = FALSE;
        WndProc( 0, WM_MBUTTONUP, 0, 0 );
        return TRUE;
    }
    else if ( mouseWheel != 0.0f && oldWheel == 0.0f )
    {
        WndProc( 0, WM_MOUSEWHEEL, (WPARAM)mouseWheel, 0);
        oldWheel = mouseWheel;
        return TRUE;
    }
    oldWheel = 0.0f;
    return FALSE;
}

SOBJECT_FOR_GXD sob;
MOTION_FOR_GXD mot;
BOOL ApplicationInit( void )
{
    srand(_time32(0));
    mMYINFO.mScreenSort = 2;
    mMYINFO.mScreenXSize = 1024;
    mMYINFO.mScreenYSize = 768;
    mMYINFO.mScreenXPosSize = 1024.0f;
    mMYINFO.mScreenYPosSize = 768.0f;
    InitWindow( mMYINFO.mScreenXSize, mMYINFO.mScreenYSize, PLATFORM_NAME );

    int tRESULT;
    D3DXFONT_DESC tFontInfo;

    ZeroMemory( &tFontInfo, sizeof( tFontInfo ) );
	HDC tDC = GetDC( hMainWindow );
	tFontInfo.Height = -MulDiv( 10, GetDeviceCaps( tDC, LOGPIXELSY ), 84 );
	tFontInfo.Width = 0;
	tFontInfo.Weight = FW_DONTCARE;
	tFontInfo.MipLevels = D3DX_DEFAULT;
	tFontInfo.Italic = FALSE;
	tFontInfo.CharSet = DEFAULT_CHARSET;
	tFontInfo.OutputPrecision = OUT_TT_PRECIS;
	tFontInfo.Quality = CLEARTYPE_QUALITY;
	tFontInfo.PitchAndFamily = DEFAULT_PITCH;
	ReleaseDC( hMainWindow, tDC );
	strcpy( tFontInfo.FaceName, "MS San Serif" );

    if ( !mGXD.Init( mFullScreen, hMainInstance, hMainWindow, mMYINFO.mScreenXSize, mMYINFO.mScreenYSize, 1.0f, 10000.0f, &tFontInfo, &tRESULT ) )
    {
        printf( "!mGXD.Init(%d)\n", tRESULT );
        return FALSE;
    }
    //if ( !mMAIN.Init() )
    //{
    //    printf( "!mMAIN.Init()\n" );
    //    return FALSE;
    //}

    sob.Init();
    sob.Load( "C001003000.SOBJECT", TRUE, TRUE );

    mot.Init();
    mot.Load( "C001001002.MOTION" );

    hPresentElapsedSeconds = mGXD.GetTotalElapsedSeconds();
    hPostSecondsForLogic = hPresentElapsedSeconds;
    hPostSecondsForMemory = hPresentElapsedSeconds;
    hPostSecondsForFrame = 0.033f;
    hPresentFrameSeconds = 0.0f;
    //mMAIN.Start();

    return TRUE;
}

void ApplicationFree( void )
{
    #ifdef USE_RAYLIB
    CloseWindow();        // Close window and OpenGL context
    #else
    #endif
}

class FrameTime
{
private:
    float frame = 0.0f;
    float maxFrame = 0.0f;
public:
    //set max frame
    void SetMax( float tMaxFrame )
    {
        maxFrame = tMaxFrame;
    }
    void Update( float dTime )
    {
        frame = dTime * 30.0f + frame;
        if( maxFrame != 0.0f && frame >= maxFrame )
            frame = 1.0f;
    }
    //get frame float
    float FrameF() const { return frame; }
    //get frame number
    int FrameI() const { return (int)frame; }
};
FrameTime mActFrame;
void CustomDraw( float dTime )
{
    mActFrame.SetMax( mot.mFrameNum );
    mActFrame.Update( dTime );

    mGXD.BeginForDrawing();

    sob.TestDraw( &mot, mActFrame.FrameI() );

    mGXD.EndForDrawing();
}

void ApplicationMain( void )
{
    
    float dTime;

    hPresentElapsedSeconds = mGXD.GetTotalElapsedSeconds();
    if ( hPresentElapsedSeconds - hPostSecondsForLogic < hPostSecondsForFrame )
    {
        return;
    }
    hPresentFrameSeconds = hPresentElapsedSeconds - hPostSecondsForLogic;
    //CGXD::UpdateForInputSystem(mAPP[0].hActiveProgram);
    //CTS_INPUT::KEYBOARD();
    dTime = 0.0f;
    while ( TRUE )
    {
        //mMAIN.Logic( hPostSecondsForFrame );
        dTime += hPostSecondsForFrame;
        hPostSecondsForLogic += hPostSecondsForFrame;
        if ( hPresentElapsedSeconds - hPostSecondsForLogic < hPostSecondsForFrame )
        {
            break;
        }
    }
    //if (mAPP[0].hActiveProgram)
    {
    //    mMAIN.Draw( dTime );
        CustomDraw( dTime );
    }
    //hPresentFrameSeconds = hPresentElapsedSeconds - hPostSecondsForLogic;//60.0f
    if( hPresentFrameSeconds < 60.0f )
    {
        return;
    }
    hPostSecondsForLogic = hPresentElapsedSeconds;
    //CGDATA::ProcessForMemory(mAPP[0].hPresentElapsedSeconds, 300.0);
}
