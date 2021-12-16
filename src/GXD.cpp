#include "GXD.h"

GXD mGXD;
int binaryRefCount = 0;

GXD::GXD( void )
{
}

GXD::~GXD( void )
{
}

BOOL Zlib::Decompress( ZlibDataPtr* z )
{
    if( !z || z->IsError ) return FALSE;
    return mGXD.mFUncompress( z->tOriginal, &z->tOriginalSize, z->tCompress, z->tCompressSize ) == 0;
}
/*
D3DVERTEXELEMENT9 mVertexElementForSKIN[] = {
    {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};
*/
D3DVERTEXELEMENT9 mVertexElementForSKIN2[] = {
    {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0},
    {0, 28, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
    {0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
    {0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
    {0, 56, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 68, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};
D3DVERTEXELEMENT9 mVertexElementForSKIN2SHADOW[] = {
    {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0},
    {0, 28, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
};

D3DXVECTOR3* WINAPI D3DXVec3Normalize( D3DVECTOR *pOut, CONST D3DVECTOR*pV )
{
    return ::D3DXVec3Normalize( (D3DXVECTOR3*)pOut, (D3DXVECTOR3*)pV );
}

BOOL GXD::Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, D3DXFONT_DESC *tFontInfo, int *tRESULT )
{
    int index01;
    DIPROPDWORD dipdw;
    DEVMODEA dm;

    if ( this->mCheckInitState )
    {
        *tRESULT = 1;
        return 0;
    }
    this->mTextureOptionValue = 0;
    this->mSamplerOptionValue = 0;
    this->mNormalMapOptionValue = 2;
    this->mLODLengthInfo[0] = tFarPlane - 1.0f;
    this->mLODLengthInfo[1] = tFarPlane;
    this->mFilterOptionValue = 1;
    this->mCheckDepthBias = 1;
    this->mCheckTwoSideStencilFunction = 1;
    this->mCheckFullScreen = tCheckFullScreen;
    this->mInstanceHandle = tInstanceHandle;
    this->mWindowHandle = tWindowHandle;
    this->mScreenXSize = tScreenXSize;
    this->mScreenYSize = tScreenYSize;
    this->mFovY = 45.0f;
    this->mNearPlane = tNearPlane;
    this->mFarPlane = tFarPlane;
    memcpy(&this->mFontInfo, tFontInfo, sizeof(this->mFontInfo));
    this->mMaxParticleNum = 1000;
    srand(time(0));
    if ( !QueryPerformanceFrequency( &this->mHighResolutionTicks ) )
    {
        *tRESULT = 2;
        return 0;
    }
    this->mTicksForRange = this->mHighResolutionTicks.QuadPart;
    QueryPerformanceCounter( &this->mHighResolutionTicks );
    this->mTicksForTime1 = this->mHighResolutionTicks.QuadPart;
    this->mTicksForTime2 = this->mHighResolutionTicks.QuadPart;
    this->m_dwEngineStartTime = timeGetTime();
    if ( tCheckFullScreen )
    {
        memset( &dm, 0, sizeof(dm));
        dm.dmSize = 156;
        dm.dmBitsPerPel = 32;
        dm.dmPelsWidth = tScreenXSize;
        dm.dmPelsHeight = tScreenYSize;
        dm.dmFields = 1835008;
        if (ChangeDisplaySettingsA(&dm, 4u))
        {
            *tRESULT = 3;
            return 0;
        }
    }
    this->mDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
    if (!this->mDirect3D)
    {
        *tRESULT = 4;
        return 0;
    }
    if ( this->mDirect3D->GetDeviceCaps( 0, D3DDEVTYPE_HAL, &this->mGraphicSupportInfo ) < 0 )
    {
        *tRESULT = 5;
        return 0;
    }
    if ( 
        FAILED( this->mDirect3D->CheckDeviceFormat( 0, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_TEXTURE, D3DFMT_DXT1 ) ) || 
        FAILED( this->mDirect3D->CheckDeviceFormat( 0, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_TEXTURE, D3DFMT_DXT3 ) ) || 
        FAILED( this->mDirect3D->CheckDeviceFormat( 0, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_TEXTURE, D3DFMT_DXT5 ) )
        )
    {
        MessageBoxA( 0, "[INVALID_TEXTURE_FORMAT]", "GXD(ERROR)", 0x1000u );
        *tRESULT = 6;
        return 0;
    }
    if ( this->mGraphicSupportInfo.VertexShaderVersion < 0xFFFE0200 )
    {
        MessageBoxA( 0, "[INVALID_VERTEX_SHADER_VERSION]", "GXD(ERROR)", 0x1000u );
        *tRESULT = 6;
        return 0;
    }
    if ( this->mGraphicSupportInfo.PixelShaderVersion < 0xFFFF0200 )
    {
        MessageBoxA( 0, "[INVALID_PIXEL_SHADER_VERSION]", "GXD(ERROR)", 0x1000u );
        *tRESULT = 6;
        return 0;
    }
    if ( ( this->mGraphicSupportInfo.RasterCaps & 0x4000000 ) == 0 )
        this->mCheckDepthBias = 0;
    if ( ( this->mGraphicSupportInfo.StencilCaps & 0x100 ) == 0 )
        this->mCheckTwoSideStencilFunction = 0;
    memset( &this->mGraphicPresentParameters, 0, sizeof( this->mGraphicPresentParameters ) );
    this->mGraphicPresentParameters.BackBufferWidth = tScreenXSize;
    this->mGraphicPresentParameters.BackBufferHeight = tScreenYSize;
    this->mGraphicPresentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
    this->mGraphicPresentParameters.BackBufferCount = 1;
    this->mGraphicPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
    this->mGraphicPresentParameters.MultiSampleQuality = 0;
    this->mGraphicPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    this->mGraphicPresentParameters.hDeviceWindow = tWindowHandle;
    this->mGraphicPresentParameters.Windowed = TRUE;
    this->mGraphicPresentParameters.EnableAutoDepthStencil = TRUE;
    this->mGraphicPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
    this->mGraphicPresentParameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
    this->mGraphicPresentParameters.FullScreen_RefreshRateInHz = 0;
    this->mGraphicPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    if ( FAILED( this->mDirect3D->CreateDevice(
        0,
        D3DDEVTYPE_HAL,
        tWindowHandle,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &this->mGraphicPresentParameters,
        &this->mGraphicDevice ) ) )
    {
        *tRESULT = 7;
        return 0;
    }
    if ( FAILED( D3DXCreateSprite( this->mGraphicDevice, &this->mGraphicSprite ) ) )
    {
        *tRESULT = 8;
        return 0;
    }
    if ( FAILED( D3DXCreateFontIndirectA( this->mGraphicDevice, tFontInfo, &this->mGraphicFont ) ) )
    {
        *tRESULT = 9;
        return 0;
    }
    this->mParticleVertexBuffer.clear();
    if ( this->mMaxParticleNum > 0 )
    {
        for ( index01 = 0; index01 < this->mMaxParticleNum*6; index01++ )
        {
            this->mParticleVertexBuffer.push_back( PARTICLEVERTEX_FOR_GXD() );
        }
        if ( this->mParticleVertexBuffer.size() != this->mMaxParticleNum*6 )
        {
            *tRESULT = 10;
            return 0;
        }
        for ( index01 = 0; index01 < this->mMaxParticleNum; index01++ )
        {
            this->mParticleVertexBuffer[6 * index01 + 0].mT[0] = 0.0f;
            this->mParticleVertexBuffer[6 * index01 + 0].mT[1] = 0.0f;
            this->mParticleVertexBuffer[6 * index01 + 1].mT[0] = 1.0f;
            this->mParticleVertexBuffer[6 * index01 + 1].mT[1] = 0.0f;
            this->mParticleVertexBuffer[6 * index01 + 2].mT[0] = 0.0f;
            this->mParticleVertexBuffer[6 * index01 + 2].mT[1] = 1.0f;
            this->mParticleVertexBuffer[6 * index01 + 3].mT[0] = 0.0f;
            this->mParticleVertexBuffer[6 * index01 + 3].mT[1] = 1.0f;
            this->mParticleVertexBuffer[6 * index01 + 4].mT[0] = 1.0f;
            this->mParticleVertexBuffer[6 * index01 + 4].mT[1] = 0.0f;
            this->mParticleVertexBuffer[6 * index01 + 5].mT[0] = 1.0f;
            this->mParticleVertexBuffer[6 * index01 + 5].mT[1] = 1.0f;
        }
    }
    this->mViewport.X = 0.f;
    this->mViewport.Y = 0.f;
    this->mViewport.Width = tScreenXSize;
    this->mViewport.Height = tScreenYSize;
    this->mViewport.MinZ = 0.0f;
    this->mViewport.MaxZ = 1.0f;
    this->mViewportMatrix._11 = tScreenXSize * 0.5f;
    this->mViewportMatrix._12 = 0.0f;
    this->mViewportMatrix._13 = 0.0f;
    this->mViewportMatrix._14 = 0.0f;
    this->mViewportMatrix._21 = 0.0f;
    this->mViewportMatrix._22 = -tScreenYSize * 0.5f;
    this->mViewportMatrix._23 = 0.0f;
    this->mViewportMatrix._24 = 0.0f;
    this->mViewportMatrix._31 = 0.0f;
    this->mViewportMatrix._32 = 0.0f;
    this->mViewportMatrix._33 = 1.0f;
    this->mViewportMatrix._34 = 0.0f;
    this->mViewportMatrix._41 = tScreenXSize * 0.5f;
    this->mViewportMatrix._42 = tScreenYSize * 0.5f;
    this->mViewportMatrix._43 = 0.0f;
    this->mViewportMatrix._44 = 1.0f;
    float Aspect = (float)(tScreenXSize / tScreenYSize);
    float fovy = this->mFovY * 0.01745329238474369f;
    D3DXMatrixPerspectiveFovLH(&this->mPerspectiveMatrix, fovy, Aspect, tNearPlane, tFarPlane);
    this->mCameraEye = D3DXVECTOR3::D3DXVECTOR3( 0.0f, 0.0f, -10.0f );
    this->mCameraLook = D3DXVECTOR3::D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXMatrixLookAtLH( &this->mViewMatrix, &this->mCameraEye, &this->mCameraLook, &D3DXVECTOR3::D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
    D3DXMatrixIdentity( &this->mWorldMatrix );
    memset( &this->mMaterial, 0, sizeof(this->mMaterial) );
    this->mMaterial.Diffuse = D3DXCOLOR::D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
    this->mMaterial.Ambient = D3DXCOLOR::D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
    this->mMaterial.Specular = D3DXCOLOR::D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
    this->mMaterial.Emissive = D3DXCOLOR::D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
    this->mMaterial.Power = 0.0f;
    memset( &this->mLight, 0, sizeof(this->mLight) );
    this->mLight.Type = D3DLIGHT_DIRECTIONAL;
    this->mLight.Ambient = D3DXCOLOR::D3DXCOLOR( 0.30000001f, 0.30000001f, 0.30000001f, 1.0f );
    this->mLight.Diffuse = D3DXCOLOR::D3DXCOLOR( 0.69999999f, 0.69999999f, 0.69999999f, 1.0f );
    this->mLight.Specular = D3DXCOLOR::D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
    this->mLight.Position = D3DXVECTOR3::D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    this->mLight.Direction = D3DXVECTOR3::D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
    D3DXVec3Normalize( &this->mLight.Direction, &this->mLight.Direction );
    this->mLight.Range = 0.0f;
    this->mLight.Falloff = 0.0f;
    this->mLight.Attenuation0 = 0.0f;
    this->mLight.Attenuation1 = 0.0f;
    this->mLight.Attenuation2 = 0.0f;
    this->mLight.Theta = 0.0f;
    this->mLight.Phi = 0.0f;

    //if ( this->mGraphicDevice->CreateVertexBuffer( 1200000, 520, 2, D3DPOOL_DEFAULT, &this->mDrawShadowVertexBuffer, 0) < 0 )
    //{
    //    *tRESULT = 10;
    //    return 0;
    //}
    //if ( this->mGraphicDevice->CreateVertexDeclaration( mVertexElementForSKIN2, &this->mDECLForSKIN2 ) < 0 )
    //{
    //    *tRESULT = 11;
    //    return 0;
    //}
    //if ( this->mGraphicDevice->CreateVertexDeclaration( mVertexElementForSKIN2SHADOW, &this->mDECLForSKIN2SHADOW ) < 0 )
    //{
    //    *tRESULT = 12;
    //    return 0;
    //}
    if ( !this->MakeShaderProgram01()
        || !this->MakeShaderProgram02()
        || !this->MakeShaderProgram03()
        || !this->MakeShaderProgram04()
        || !this->MakeShaderProgram05()
        || !this->MakeShaderProgram06()
        || !this->MakeShaderProgram07()
        || !this->MakeShaderProgram08()
        || !this->MakeShaderProgram09()
        || !this->MakeShaderProgram10()
        || !this->MakeShaderProgram11()
        || !this->MakeShaderProgram12()
        || !this->MakeShaderProgram13()
        || !this->MakeShaderProgram14()
        || !this->MakeShaderProgram15()
        || !this->MakeShaderProgram16()
        )
    {
        *tRESULT = 13;
        return 0;
    }

    this->mCompressLibrary = LoadLibraryA( "GXDCompress.dll" );
    if ( !this->mCompressLibrary )
    {
        *tRESULT = 21;
        return 0;
    }
    this->mFCompressBound = (FCompressBound)GetProcAddress( this->mCompressLibrary, "compressBound" );
    if ( !this->mFCompressBound )
    {
        *tRESULT = 22;
        return 0;
    }
    this->mFCompress = (FCompress)GetProcAddress( this->mCompressLibrary, "compress2" );
    if ( !this->mFCompress )
    {
        *tRESULT = 23;
        return 0;
    }
     this->mFUncompress = (FUncompress)GetProcAddress( this->mCompressLibrary, "uncompress" );
     if ( !this->mFUncompress )
     {
         *tRESULT = 24;
         return 0;
     }
     //if ( !CBillBoardStringMgr::Init(&g_BillBoardStringMgr, this->mGraphicDevice, tFontInfo))
     //{
     //    *tRESULT = 25;
     //    return 0;
     //}

     this->mCheckInitState = 1;
     this->m_bUseMultiDraw = 1;
     
     return 1;
}

void GXD::Free( void )
{
}


BOOL GXD::MakeShaderProgram01( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram02( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram03( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram04( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram05( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram06( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram07( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram08( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram09( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram10( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram11( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram12( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram13( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram14( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram15( void ){ return TRUE; }
BOOL GXD::MakeShaderProgram16( void ){ return TRUE; }

float GXD::GetRandomNumber( float tMinValue, float tMaxValue )
{
    if ( tMaxValue <= tMinValue )
    {
        return (float)( (rand() % 10001 ) / 10000.0f * ( tMinValue - tMaxValue ) + tMaxValue );
    }
    return (float)( (rand() % 10001) / 10000.0f * ( tMaxValue - tMinValue ) + tMinValue );
}

float GXD::GetTotalElapsedSeconds( void )
{
    QueryPerformanceCounter( &mHighResolutionTicks );
    this->mTicksForTime2 = (double)this->mHighResolutionTicks.QuadPart;
    return (float)( ( mTicksForTime2 - mTicksForTime1 ) / mTicksForRange );
}

void GXD::BeginForDrawing( void )
{
    D3DXVECTOR3 v3; // [esp+2Ch] [ebp-58h] BYREF
    D3DXVECTOR3 v4; // [esp+38h] [ebp-4Ch] BYREF
    D3DXMATRIX v5; // [esp+44h] [ebp-40h] BYREF

    this->mDRAW_POLYGON_NUM = 0;
    this->mGraphicDevice->Clear( 0, 0, 7, 0, 1.0f, 0 );
    this->mCameraForward -= this->mCameraEye;
    D3DXVec3Normalize( &this->mCameraForward, &this->mCameraForward );
    D3DXMatrixLookAtLH( &this->mViewMatrix, &this->mCameraEye, &this->mCameraLook, &D3DXVECTOR3::D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
    D3DXMatrixIdentity( &this->mWorldMatrix );
    this->mGraphicDevice->SetViewport( &this->mViewport );
    this->mGraphicDevice->SetTransform( D3DTS_PROJECTION, &this->mPerspectiveMatrix );
    this->mGraphicDevice->SetTransform( D3DTS_VIEW, &this->mViewMatrix );
    this->mGraphicDevice->SetTransform( D3DTS_WORLD, &this->mWorldMatrix );
    this->SetDefaultMaterial();
    this->SetDefaultLight();
    this->SetDefaultTextureSamplerState();
    //(*(*dword_15CB4 + 228))(dword_15CB4, dword_15CB4, 26, 1);
    this->CalculateFrustum();
    D3DXMatrixInverse( &this->mBillboardMatrixInfoForAll, 0, &this->mViewMatrix );
    this->mBillboardVertexInfoForAll[0].x = this->mBillboardMatrixInfoForAll._11;
    this->mBillboardVertexInfoForAll[0].y = this->mBillboardMatrixInfoForAll._12;
    this->mBillboardVertexInfoForAll[0].z = this->mBillboardMatrixInfoForAll._13;
    *this->mBillboardVertexInfoForAll[1] = *&this->mBillboardMatrixInfoForAll.m[1][0];
    D3DXVec3Normalize( this->mBillboardVertexInfoForAll, this->mBillboardVertexInfoForAll );
    D3DXVec3Normalize( &this->mBillboardVertexInfoForAll[1], &this->mBillboardVertexInfoForAll[1] );
    D3DXMatrixIdentity(&v5);
    v5._11 = this->mViewMatrix._11;
    v5._13 = this->mViewMatrix._13;
    v5._31 = this->mViewMatrix._31;
    v5._33 = this->mViewMatrix._33;
    D3DXMatrixInverse( &this->mBillboardMatrixInfoForY, 0, &v5 );
    this->mBillboardVertexInfoForY[0].x = this->mBillboardMatrixInfoForY._11;
    this->mBillboardVertexInfoForY[0].y = this->mBillboardMatrixInfoForY._12;
    this->mBillboardVertexInfoForY[0].z = this->mBillboardMatrixInfoForY._13;
    *this->mBillboardVertexInfoForY[1] = *&this->mBillboardMatrixInfoForY.m[1][0];
    D3DXVec3Normalize(this->mBillboardVertexInfoForY, this->mBillboardVertexInfoForY);
    D3DXVec3Normalize(&this->mBillboardVertexInfoForY[1], &this->mBillboardVertexInfoForY[1]);
    this->mGraphicDevice->BeginScene();
    mDrawShadowVertexBuffer = NULL;//*(&mShader[0].mDrawShadowVertexBuffer.GetDevice + this) = 0;
    this->mGraphicDevice->SetVertexShader( 0 );
    this->mGraphicDevice->SetPixelShader( 0 );
}
void GXD::EndForDrawing( void )
{
    this->mGraphicDevice->EndScene();
    this->mGraphicDevice->Present( 0, 0, 0, 0 );
}

void GXD::BeginForPOBJECT( void )
{
    this->mGraphicDevice->SetRenderState( D3DRS_ZWRITEENABLE, 0 );
    this->mGraphicDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, 1 );
    this->mGraphicDevice->SetRenderState( D3DRS_SRCBLEND, 5 );
    this->mGraphicDevice->SetRenderState( D3DRS_DESTBLEND, 6 );
    this->mGraphicDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, 4 );
    this->SetAmbientLight( 1, D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.0f ) );
    //*(&mShader[0].mDrawShadowVertexBuffer.GetDevice + this) = 0;
    this->mGraphicDevice->SetVertexShader( 0 );
    this->mGraphicDevice->SetPixelShader( 0 );
    const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0 | D3DFVF_TEX1;//position, color, texcoord
    this->mGraphicDevice->SetFVF( fvf );
    D3DXMatrixIdentity( &this->mWorldMatrix );
    this->mGraphicDevice->SetTransform( D3DTS_WORLD, &this->mWorldMatrix );
}

void GXD::EndForPOBJECT( void )
{
    this->SetDefaultLight();
    this->mGraphicDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, 2 );
    this->mGraphicDevice->SetRenderState( D3DRS_DESTBLEND, 1 );
    this->mGraphicDevice->SetRenderState( D3DRS_SRCBLEND, 2 );
    this->mGraphicDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, 0 );
    this->mGraphicDevice->SetRenderState( D3DRS_ZWRITEENABLE, 1 );
}

void GXD::SetDefaultMaterial( void )
{
    this->mGraphicDevice->SetMaterial( &this->mMaterial );
}

void GXD::SetDefaultLight( void )
{
    this->mGraphicDevice->LightEnable( 0, 1 );
    this->mGraphicDevice->SetLight( 0, &this->mLight );
}

void GXD::SetAmbientLight( int tAmbientSort, D3DXCOLOR tAmbientValue )
{
    float r;
    float g;
    float b;
    D3DLIGHT9 tAmbientLight;

    this->mGraphicDevice->LightEnable( 0, 1 );
    memset( &tAmbientLight, 0, sizeof( tAmbientLight ) );
    tAmbientLight.Type = D3DLIGHT_DIRECTIONAL;
    tAmbientLight.Diffuse = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
    tAmbientLight.Specular = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
    if ( tAmbientSort == 1 )
    {
        r = this->mLight.Diffuse.r * 0.5 + this->mLight.Ambient.r;
        g = this->mLight.Diffuse.g * 0.5 + this->mLight.Ambient.g;
        b = this->mLight.Diffuse.b * 0.5 + this->mLight.Ambient.b;
        tAmbientLight.Ambient = D3DXCOLOR( r, g, b, 1.0f );
    }
    else if ( tAmbientSort == 2 )
    {
        tAmbientLight.Ambient = tAmbientValue;
    }
    tAmbientLight.Position = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    tAmbientLight.Direction = D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
    tAmbientLight.Range = 0.0f;
    tAmbientLight.Falloff = 0.0f;
    tAmbientLight.Attenuation0 = 0.0f;
    tAmbientLight.Attenuation1 = 0.0f;
    tAmbientLight.Attenuation2 = 0.0f;
    tAmbientLight.Theta = 0.0f;
    tAmbientLight.Phi = 0.0f;
    this->mGraphicDevice->SetLight( 0, &tAmbientLight );
}

void GXD::SetDefaultTextureSamplerState( void )
{
    if ( this->mSamplerOptionValue )
    {
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, 1 );
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, 1 );
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MINFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MAGFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MIPFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_ADDRESSU, 1 );
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_ADDRESSV, 1 );
        this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MINFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MAGFILTER, 2 );
        this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MIPFILTER, 2 );
    }
    else
    {
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, 3 );
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, 3 );
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, 3 );
        //this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_MAXANISOTROPY, dword_15BB8);
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, 1);
        this->mGraphicDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, 1);
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MINFILTER, 3);
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MAGFILTER, 3);
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MIPFILTER, 3);
        //this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_MAXANISOTROPY, dword_15BB8);
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_ADDRESSU, 1);
        this->mGraphicDevice->SetSamplerState( 1, D3DSAMP_ADDRESSV, 1);
        this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MINFILTER, 3);
        this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MAGFILTER, 3);
        this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MIPFILTER, 3);
        //this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_MAXANISOTROPY, dword_15BB8);
    }
    this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_ADDRESSU, 1 );
    this->mGraphicDevice->SetSamplerState( 2, D3DSAMP_ADDRESSV, 1 );
}

void GXD::CalculateFrustum( void )
{
    float v1; // [esp+4h] [ebp-64h]
    float v2; // [esp+8h] [ebp-60h]
    float v3; // [esp+Ch] [ebp-5Ch]
    float v4; // [esp+10h] [ebp-58h]
    float v5; // [esp+14h] [ebp-54h]
    float X; // [esp+18h] [ebp-50h]
    D3DXMATRIX v8; // [esp+20h] [ebp-48h] BYREF
    float v9; // [esp+64h] [ebp-4h]

    D3DXMatrixMultiply(&v8, &this->mViewMatrix, &this->mPerspectiveMatrix );
    this->mFrustumPlane[0][0] = v8._14 + v8._11;
    this->mFrustumPlane[0][1] = v8._24 + v8._21;
    this->mFrustumPlane[0][2] = v8._34 + v8._31;
    this->mFrustumPlane[0][3] = v8._44 + v8._41;
    X = this->mFrustumPlane[0][0] * this->mFrustumPlane[0][0]
        + this->mFrustumPlane[0][1] * this->mFrustumPlane[0][1]
        + this->mFrustumPlane[0][2] * this->mFrustumPlane[0][2];
    v9 = 1.0f / sqrtf(X);
    this->mFrustumPlane[0][0] = this->mFrustumPlane[0][0] * v9;
    this->mFrustumPlane[0][1] = this->mFrustumPlane[0][1] * v9;
    this->mFrustumPlane[0][2] = this->mFrustumPlane[0][2] * v9;
    this->mFrustumPlane[0][3] = this->mFrustumPlane[0][3] * v9;
    this->mFrustumPlane[1][0] = v8._14 - v8._11;
    this->mFrustumPlane[1][1] = v8._24 - v8._21;
    this->mFrustumPlane[1][2] = v8._34 - v8._31;
    this->mFrustumPlane[1][3] = v8._44 - v8._41;
    v5 = this->mFrustumPlane[1][0] * this->mFrustumPlane[1][0]
        + this->mFrustumPlane[1][1] * this->mFrustumPlane[1][1]
        + this->mFrustumPlane[1][2] * this->mFrustumPlane[1][2];
    v9 = 1.0f / sqrtf(v5);
    this->mFrustumPlane[1][0] = this->mFrustumPlane[1][0] * v9;
    this->mFrustumPlane[1][1] = this->mFrustumPlane[1][1] * v9;
    this->mFrustumPlane[1][2] = this->mFrustumPlane[1][2] * v9;
    this->mFrustumPlane[1][3] = this->mFrustumPlane[1][3] * v9;
    this->mFrustumPlane[2][0] = v8._14 + v8._12;
    this->mFrustumPlane[2][1] = v8._24 + v8._22;
    this->mFrustumPlane[2][2] = v8._34 + v8._32;
    this->mFrustumPlane[2][3] = v8._44 + v8._42;
    v4 = this->mFrustumPlane[2][0] * this->mFrustumPlane[2][0]
        + this->mFrustumPlane[2][1] * this->mFrustumPlane[2][1]
        + this->mFrustumPlane[2][2] * this->mFrustumPlane[2][2];
    v9 = 1.0f / sqrtf(v4);
    this->mFrustumPlane[2][0] = this->mFrustumPlane[2][0] * v9;
    this->mFrustumPlane[2][1] = this->mFrustumPlane[2][1] * v9;
    this->mFrustumPlane[2][2] = this->mFrustumPlane[2][2] * v9;
    this->mFrustumPlane[2][3] = this->mFrustumPlane[2][3] * v9;
    this->mFrustumPlane[3][0] = v8._14 - v8._12;
    this->mFrustumPlane[3][1] = v8._24 - v8._22;
    this->mFrustumPlane[3][2] = v8._34 - v8._32;
    this->mFrustumPlane[3][3] = v8._44 - v8._42;
    v3 = this->mFrustumPlane[3][0] * this->mFrustumPlane[3][0]
        + this->mFrustumPlane[3][1] * this->mFrustumPlane[3][1]
        + this->mFrustumPlane[3][2] * this->mFrustumPlane[3][2];
    v9 = 1.0f / sqrtf(v3);
    this->mFrustumPlane[3][0] = this->mFrustumPlane[3][0] * v9;
    this->mFrustumPlane[3][1] = this->mFrustumPlane[3][1] * v9;
    this->mFrustumPlane[3][2] = this->mFrustumPlane[3][2] * v9;
    this->mFrustumPlane[3][3] = this->mFrustumPlane[3][3] * v9;
    this->mFrustumPlane[4][0] = v8._13;
    this->mFrustumPlane[4][1] = v8._23;
    this->mFrustumPlane[4][2] = v8._33;
    this->mFrustumPlane[4][3] = v8._43;
    v2 = this->mFrustumPlane[4][0] * this->mFrustumPlane[4][0]
        + this->mFrustumPlane[4][1] * this->mFrustumPlane[4][1]
        + this->mFrustumPlane[4][2] * this->mFrustumPlane[4][2];
    v9 = 1.0f / sqrtf(v2);
    this->mFrustumPlane[4][0] = this->mFrustumPlane[4][0] * v9;
    this->mFrustumPlane[4][1] = this->mFrustumPlane[4][1] * v9;
    this->mFrustumPlane[4][2] = this->mFrustumPlane[4][2] * v9;
    this->mFrustumPlane[4][3] = this->mFrustumPlane[4][3] * v9;
    this->mFrustumPlane[5][0] = v8._14 - v8._13;
    this->mFrustumPlane[5][1] = v8._24 - v8._23;
    this->mFrustumPlane[5][2] = v8._34 - v8._33;
    this->mFrustumPlane[5][3] = v8._44 - v8._43;
    v1 = this->mFrustumPlane[5][0] * this->mFrustumPlane[5][0]
        + this->mFrustumPlane[5][1] * this->mFrustumPlane[5][1]
        + this->mFrustumPlane[5][2] * this->mFrustumPlane[5][2];
    v9 = 1.0f / sqrtf(v1);
    this->mFrustumPlane[5][0] = this->mFrustumPlane[5][0] * v9;
    this->mFrustumPlane[5][1] = this->mFrustumPlane[5][1] * v9;
    this->mFrustumPlane[5][2] = this->mFrustumPlane[5][2] * v9;
    this->mFrustumPlane[5][3] = this->mFrustumPlane[5][3] * v9;
}

BOOL GXD::GetCompressSize( DWORD tOriginalSize, BYTE *tOriginal, DWORD *tCompressSize )
{
    return FALSE;
}
BOOL GXD::Compress( DWORD tOriginalSize, BYTE *tOriginal, DWORD tCompressSize, BYTE *tCompress )
{
    return FALSE;
}
BOOL GXD::Decompress( DWORD tCompressSize, BYTE *tCompress, DWORD tOriginalSize, BYTE *tOriginal )
{
    try
    {
        return this->mFUncompress( tOriginal, &tOriginalSize, tCompress, tCompressSize ) == 0;
    }
    catch ( std::exception& e )
    {
        printf( "%s\n", e.what() );
    }
    return FALSE;
}

BOOL GXD::CheckPointInFrustum( float tPoint[3] )
{
    if ( this->mFrustumPlane[0][0] * tPoint[0]
        + this->mFrustumPlane[0][1] * tPoint[1]
        + this->mFrustumPlane[0][2] * tPoint[2]
        + this->mFrustumPlane[0][3] < 0.0f )
        return 0;
    if ( this->mFrustumPlane[1][0] * tPoint[0]
        + this->mFrustumPlane[1][1] * tPoint[1]
        + this->mFrustumPlane[1][2] * tPoint[2]
        + this->mFrustumPlane[1][3] < 0.0f )
        return 0;
    if ( this->mFrustumPlane[2][0] * tPoint[0]
        + this->mFrustumPlane[2][1] * tPoint[1]
        + this->mFrustumPlane[2][2] * tPoint[2]
        + this->mFrustumPlane[2][3] < 0.0f )
        return 0;
    if ( this->mFrustumPlane[3][0] * tPoint[0]
        + this->mFrustumPlane[3][1] * tPoint[1]
        + this->mFrustumPlane[3][2] * tPoint[2]
        + this->mFrustumPlane[3][3] < 0.0f )
        return 0;
    if ( this->mFrustumPlane[4][0] * tPoint[0]
        + this->mFrustumPlane[4][1] * tPoint[1]
        + this->mFrustumPlane[4][2] * tPoint[2]
        + this->mFrustumPlane[4][3] >= 0.0f )
        return this->mFrustumPlane[5][0] * tPoint[0]
        + this->mFrustumPlane[5][1] * tPoint[1]
        + this->mFrustumPlane[5][2] * tPoint[2]
        + this->mFrustumPlane[5][3] >= 0.0f;
    return 0;
}