#include "GXD.h"
BinaryReader* skinReader;
void ClearSkinReader()
{
    if( skinReader )
    {
        delete skinReader;
        skinReader = NULL;
    }
}

void SOBJECT_FOR_GXD::Init( void )
{
    this->mCheckValidState = 0;
    this->mSkinNum = 0;
    this->mSkin.clear();
}

void SOBJECT_FOR_GXD::Free( void )
{
    this->mCheckValidState = 0;
    this->mSkinNum = 0;
    this->mSkin.clear();
    ClearSkinReader();
}

BOOL CreateWithBlankSkin( int tSkinNum );
BOOL Save( char *tFileName );
BOOL SOBJECT_FOR_GXD::Load( char* tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData )
{
    if ( this->mCheckValidState )
    {
        TRACE();
        return FALSE;
    }

    auto r = skinReader = BinaryReader::LoadFile( tFileName );
    if( r == NULL )
        return FALSE;

    this->mSkinNum = r->ReadInt();
    printf( "%d\n", this->mSkinNum );
    if ( this->mSkinNum < 1 )
    {
        return TRUE;
    }
    int i;
    for ( i = 0; i < this->mSkinNum; ++i )
    {
        SKIN_FOR_GXD skin;
        skin.Init();
        if ( !skin.Load( r, tCheckCreateTexture, tCheckRemoveFileData ) )
        {
            TRACE();
            this->Free();
            return FALSE;
        }
        this->mSkin.push_back( skin );
    }
    this->mCheckValidState = TRUE;
    delete skinReader;
    return TRUE;
}

void SOBJECT_FOR_GXD::CreateTexture( BOOL tCheckRemoveFileData )
{
}

void SOBJECT_FOR_GXD::DeleteTexture( void )
{
}

void SOBJECT_FOR_GXD::Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, MOTION_FOR_GXD *tMotion, float tRangeForCulling, BOOL tCheckShadow, void *tWorld, BOOL tCheckCalculateNormal, float tValidShadowLength )
{

}

void SOBJECT_FOR_GXD::DrawForSelect( int tSelectSkinIndex, float tFrame, float tCoord[3], float tAngle[3], MOTION_FOR_GXD *tMotion, float tRangeForCulling )
{
    if ( !mCheckValidState )
    {
        return;
    }
    for ( int i = 0; i < mSkinNum; i++ )
    {
        if ( i == tSelectSkinIndex )
        {
            mSkin[i].ReadyForDraw( (int)tFrame, tMotion, FALSE );
            mSkin[i].DrawForSelect();
        }
    }
}

void SOBJECT_FOR_GXD::GetSkinCoord( int tSelectSkinIndex, float tFrame, float tCoord[3], float tAngle[3], MOTION_FOR_GXD *tMotion, float tSkinCoord[3] )
{
}

BOOL SOBJECT_FOR_GXD::SetScale( float x, float y, float z )
{
    return TRUE;
}

BOOL SOBJECT_FOR_GXD::SaveToSOBJECT2( char *tFileName, int tLODStepNum )
{
    return TRUE;
}

void SOBJECT_FOR_GXD::TestDraw( MOTION_FOR_GXD* tMotion, int tFrameNum )
{
    if( !this->mCheckValidState )
        return;
    
    if( !this->mSkinNum )
        return;

    if( !tMotion || !tMotion->mCheckValidState || tFrameNum < 1 || tFrameNum >= tMotion->mFrameNum )
        return;

    if ( ( this->mSkin[0].mScaleValue.x <= 0.9998999834060669f
        || this->mSkin[0].mScaleValue.x >= 1.000100016593933f
        || this->mSkin[0].mScaleValue.y <= 0.9998999834060669f
        || this->mSkin[0].mScaleValue.y >= 1.000100016593933f
        || this->mSkin[0].mScaleValue.z <= 0.9998999834060669f
        || this->mSkin[0].mScaleValue.z >= 1.000100016593933f )
        && tMotion->mCheckValidState
        && !this->mSkin[0].mScaleKeyMatrix.size() )
    {
        for( int a = 0; a < tMotion->mBoneNum << 6; a++ )
            this->mSkin[0].mScaleKeyMatrix.push_back( D3DXMATRIX() );
    }

    int i;
    D3DXVECTOR3 v15, v16;
    D3DXVECTOR3 v17, v18;
    D3DXMATRIX* v19 = &tMotion->mKeyMatrix[ tMotion->mBoneNum * tFrameNum ];
    D3DXMATRIX v20;
    if ( this->mSkin[0].mScaleKeyMatrix.size()  )
    {
        FLOAT* v = (FLOAT*)&this->mSkin[0].mScaleValue;
        D3DXMatrixScaling( &v20, v[0], v[1], v[2] );
        for ( i = 0; i < tMotion->mBoneNum; ++i )
        {
            v19[i] *= v20;
            this->mSkin[0].mScaleKeyMatrix[i] = v19[i];
        }
        v19 = &this->mSkin[0].mScaleKeyMatrix[0];
    }
    for ( i = 0; i < this->mSkin[0].mVertexNum; i++ )
    {
        D3DXVECTOR3* x = (D3DXVECTOR3*)&this->mSkin[0].mMotionVertex[i];
        float* wf = &this->mSkin[0].mWeightBuffer[i].mBlendValue[0];
        int* wi = &this->mSkin[0].mWeightBuffer[i].mBoneIndex[0];
        float* vert = &this->mSkin[0].mVertexBuffer[i].mV[0];
    
        D3DXVec3TransformCoord( &v15, x, &v19[wi[0]] );
        D3DXVec3TransformCoord( &v16, x, &v19[wi[1]] );
        if ( wf[2] <= 0.0f )
            v17 = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
        else
            D3DXVec3TransformCoord( &v17, x, &v19[wi[2]] );
        if ( wf[3] <= 0.0f )
            v18 = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
        else
            D3DXVec3TransformCoord( &v18, x, &v19[wi[3]] );
        vert[0] = v15.x * wf[0]
            + v16.x * wf[1]
            + v17.x * wf[2]
            + v18.x * wf[3];
        vert[1] = v15.y * wf[0]
            + v16.y * wf[1]
            + v17.y * wf[2]
            + v18.y * wf[3];
        vert[2] = v15.z * wf[0]
            + v16.z * wf[1]
            + v17.z * wf[2]
            + v18.z * wf[3];
    };

    if ( this->mSkin[0].mTexture[0].mTexture )
    {
        if (this->mSkin[0].mTexture[0].mAlphaModeCase != 1 && this->mSkin[0].mTexture[0].mAlphaModeCase)
        {
            if ( this->mSkin[0].mTexture[0].mAlphaModeCase == 2 )
            {
                //v30 = 1;
                //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 14, 0, ".\\S07_GXD.cpp", 2639);
                //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 27, 1u, ".\\S07_GXD.cpp", 2640);
            }
            else if (this->mSkin[0].mTexture[0].mAlphaModeCase == 3)
            {
                //v29 = 1;
                D3DMATERIAL9 v22;
                memset(&v22, 0, sizeof(v22));
                v22.Ambient.r = 1.0f;
                v22.Diffuse.r = 1.0f;
                v22.Ambient.g = 1.0f;
                v22.Diffuse.g = 1.0f;
                v22.Ambient.b = 1.0f;
                v22.Diffuse.b = 1.0f;
                v22.Ambient.a = 1.0f;
                v22.Diffuse.a = 1.0f;
                mGXD.mGraphicDevice->SetMaterial( &v22 );
                //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 27, 1u, ".\\S07_GXD.cpp", 2652);
                //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 60, this->m_dwDyeingColor, ".\\S07_GXD.cpp", 2653);
                //CTextureStageStateMgr::PushNewState(&mGXD.m_TextureStateMgr, 0, 1, 0xDu, ".\\S07_GXD.cpp", 2654);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 0, 3, 3u, ".\\S07_GXD.cpp", 2655);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 0, 5, 0, ".\\S07_GXD.cpp", 2656);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 0, 6, 0, ".\\S07_GXD.cpp", 2657);
                //CTextureStageStateMgr::PushNewState(&mGXD.m_TextureStateMgr, 1u, 1, 4u, ".\\S07_GXD.cpp", 2658);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 1u, 2, 1u, ".\\S07_GXD.cpp", 2659);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 1u, 3, 0, ".\\S07_GXD.cpp", 2660);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 1u, 4, 2u, ".\\S07_GXD.cpp", 2661);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 1u, 5, 1u, ".\\S07_GXD.cpp", 2662);
                //CTextureStageStateMgr::SetTextureStageState(&mGXD.m_TextureStateMgr, 1u, 11, 0, ".\\S07_GXD.cpp", 2663);
            }
        }
        else
        {
            //v23 = 1;
            //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 15, 1u, ".\\S07_GXD.cpp", 2633);
            //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 24, 0x80u, ".\\S07_GXD.cpp", 2634);
        }
        mGXD.mGraphicDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1);
        mGXD.mGraphicDevice->SetRenderState(D3DRS_ALPHAREF, 128);
        mGXD.mGraphicDevice->SetTexture( 0, this->mSkin[0].mTexture[0].mTexture );
    }
    else
    {
        mGXD.mGraphicDevice->SetTexture( 0, 0 );
    }
 
    //D3DXMATRIX* lookAtMat = &mGXD.mViewMatrix;
    //D3DXMatrixIdentity(lookAtMat);
    //D3DXVECTOR3 eyePos(0, 15, -28.f);
    //D3DXVECTOR3 lookPos(0, 5, 0.0f);
    //D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
    //D3DXMatrixLookAtLH(lookAtMat, &eyePos, &lookPos, &upVec);
    //
    //D3DXMATRIX* mProjectionMatrix = &mGXD.mPerspectiveMatrix;
    //D3DXMatrixIdentity(mProjectionMatrix);
    //float fAspectRatio = (float)mGXD.mViewport.Width / mGXD.mViewport.Height;
    //D3DXMatrixPerspectiveFovLH(mProjectionMatrix, 45.0f, fAspectRatio, 1.0f, 10000.0f);

    mGXD.mCameraEye = D3DXVECTOR3(0, 5, -28.f);
    mGXD.mCameraLook = D3DXVECTOR3(0, 10, 0.f);

    const DWORD fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

    //mGXD.mGraphicDevice->SetRenderState(D3DRS_ALPHAFUNC, 8);

    auto getDelta = []() {
        static float d = 0;
        d += mGXD.GetRandomNumber(0,1);
        return d;
    };

    D3DXMATRIX d3dmat = mGXD.mWorldMatrix;
    D3DXMatrixIdentity( &d3dmat );
    float a3[3] = {1,1,1};
    float a4[3] = {0,0,0};
    float a5[3] = {0,getDelta(),0};
    float v11, v12, v13;
    D3DXMATRIX v24, v25, v26, v27, v28;
    D3DXMatrixTranslation( &v24, a4[0], a4[1], a4[2]);
    v13 = a5[0] * 0.01745329238474369f;
    D3DXMatrixRotationX( &v25, v13 );
    v12 = a5[1] * 0.01745329238474369f;
    D3DXMatrixRotationY( &v26, v12 );
    v11 = a5[2] * 0.01745329238474369f;
    D3DXMatrixRotationZ( &v27, v11 );
    D3DXMatrixScaling( &v28, a3[0], a3[1], a3[2] );    
    v27 *= v25;
    v27 *= v26;
    d3dmat *= v28 * v27 * v24;
    //mGXD.mWorldMatrix = d3dmat;
    //mGXD.mGraphicDevice->SetTransform( D3DTS_TEXTURE0, &d3dmat );
    //mGXD.mGraphicDevice->SetTransform( D3DTS_TEXTURE1, &d3dmat );
    mGXD.mGraphicDevice->SetTransform( D3DTS_WORLD, &d3dmat );
    //mGXD.mWorldMatrix = d3dmat;

//   IDirect3DVertexBuffer9* vBuffer;
//   IDirect3DIndexBuffer9* iBuffer;
//   void* pVoid;
//   mGXD.mGraphicDevice->CreateVertexBuffer(this->mSkin[0].mVertexBuffer.size() * sizeof(SKINVERTEX_FOR_GXD),
//       0,
//       fvf,
//       D3DPOOL_MANAGED,
//       &vBuffer,
//       NULL);
//   vBuffer->Lock(0, 0, (void**)&pVoid, 0);
//   memcpy(pVoid, &this->mSkin[0].mVertexBuffer[0], sizeof(SKINVERTEX_FOR_GXD)* this->mSkin[0].mVertexBuffer.size());
//   vBuffer->Unlock();
//   mGXD.mGraphicDevice->CreateIndexBuffer(this->mSkin[0].mIndexBuffer.size() * sizeof(short),
//       0,
//       D3DFMT_INDEX16,
//       D3DPOOL_MANAGED,
//       &iBuffer,
//       NULL);
//   iBuffer->Lock( 0, 0, (void**)&pVoid, 0 );
//   memcpy( pVoid, &this->mSkin[0].mIndexBuffer[0], sizeof(short) * this->mSkin[0].mIndexBuffer.size() );
//   iBuffer->Unlock();
//
//   mGXD.mGraphicDevice->SetFVF( fvf );
//   mGXD.mGraphicDevice->SetVertexShader(NULL);
//   mGXD.mGraphicDevice->SetStreamSource(0, vBuffer, 0, sizeof(SKINVERTEX_FOR_GXD));
//   mGXD.mGraphicDevice->SetIndices(iBuffer);
//   mGXD.mGraphicDevice->DrawIndexedPrimitive(
//       D3DPT_TRIANGLELIST,
//       0,
//       0,
//       this->mSkin[0].mVertexBuffer.size(),
//       0,
//       this->mSkin[0].mIndexBuffer.size()/3);
    
    std::vector<short> indices;
    indices.clear();
    for( auto i : this->mSkin[0].mIndexBuffer )
    {
        indices.push_back( i.mFace[0] );
        indices.push_back( i.mFace[1] );
        indices.push_back( i.mFace[2] );
    }

    mGXD.mGraphicDevice->SetFVF( fvf );
    BOOL b = mGXD.mGraphicDevice->DrawIndexedPrimitiveUP(
        D3DPT_TRIANGLELIST,
        0,
        this->mSkin[0].mVertexBuffer.size(),
        this->mSkin[0].mIndexBuffer.size(),
        indices.data(),
        D3DFMT_INDEX16,
        &this->mSkin[0].mVertexBuffer[0],
        32 ) < 0;
    //mGXD.mGraphicDevice->SetTransform( D3DTS_WORLD, &mGXD.mWorldMatrix );
    mGXD.SetDefaultLight();
}