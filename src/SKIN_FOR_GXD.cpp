#include "GXD.h"

void SKIN_FOR_GXD::Init( void )
{
	this->mCheckValidState = 0;
	this->mVertex = 0;
	this->mNormal = 0;
	this->mUV = 0;
	this->mWeight = 0;
	this->mTris = 0;
	this->mVertexBuffer.clear();
	this->mWeightBuffer.clear();
	this->mIndexBuffer.clear();
	this->mMotionVertex.clear();
	this->mMotionNormal.clear();
	this->mTexture[0].Init();
	this->mTexture[1].Init();
	this->mTextureAnimation = 0;
	this->m_dwDyeingColor = D3DCOLOR_RGBA(255, 0, 0, 0);
	this->mBumpTexture.Init();
	this->mSpeculerTexture.Init();
	this->mbIsUseBumpmap = 0;
	this->mbIsUseSpeculer = 0;
	this->m_bIsViewBumpLight = 0;
	memset( &this->mBumpEffect, 0, sizeof(this->mBumpEffect) );
	this->mBumpEffect.iMetrialType = 1;
	this->mScaleValue.x = 1.0f;
	this->mScaleValue.y = 1.0f;
	this->mScaleValue.z = 1.0f;
	this->mScaleKeyMatrix.clear();
}

void SKIN_FOR_GXD::Free( void )
{
    int i; // [esp+4h] [ebp-4h]

    this->mCheckValidState = 0;
    SAFE_FREE( this->mVertex );
    SAFE_FREE( this->mNormal );
    SAFE_FREE( this->mUV );
    SAFE_FREE( this->mWeight );
    SAFE_FREE( this->mTris );
    this->mVertexBuffer.clear();
    this->mWeightBuffer.clear();
    this->mIndexBuffer.clear();
    //SAFE_FREE( this->mMotionVertex );
    //SAFE_FREE( this->mMotionNormal );
    this->mTexture[0].Free();
    this->mTexture[1].Free();
    this->mBumpTexture.Free();
    this->mSpeculerTexture.Free();
    memset( &this->mBumpEffect, 0, sizeof(this->mBumpEffect) );
    this->mbIsUseBumpmap = 0;
    this->mbIsUseSpeculer = 0;
    if ( this->mTextureAnimation )
    {
        for (i = 0; i < this->mTextureAnimationNum; ++i)
            this->mTextureAnimation[i].Free();
        SAFE_FREE( this->mTextureAnimation );
    }
    this->mScaleValue.x = 1.0f;
    this->mScaleValue.y = 1.0f;
    this->mScaleValue.z = 1.0f;
    this->mScaleKeyMatrix.clear();
}

BOOL SKIN_FOR_GXD::Save( HANDLE hFile )
{
	return TRUE;
}

BOOL SKIN_FOR_GXD::Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData )
{
    int i;
    TRACE();
    if ( this->mCheckValidState )
    {
        TRACE();
        return FALSE;
    }
    TRACE();
    this->mCheckValidState = r->ReadInt();
    TRACE();
    if ( !this->mCheckValidState )
        return 1;
    TRACE();
    this->mCheckValidState = 0;

    auto z = new ZlibDataPtr( r );
    printf( "%d:%d\n", z->tOriginalSize, z->tCompressSize );
    if ( !Zlib::Decompress( z ) )
    {
        TRACE();
        return FALSE;
    }
    
    auto sr = BinaryReader::Scope( __FUNCTION__, z->tOriginal, z->tOriginalSize );
    this->mEffect = sr.ReadStruct<SKINEFFECT_FOR_GXD>();
    this->mVertexNum = sr.ReadInt();
    this->mUVNum = sr.ReadInt();
    this->mWeightNum = sr.ReadInt();
    this->mTrisNum = sr.ReadInt();
    this->mSize = sr.ReadStruct<SKINSIZE_FOR_GXD>();

    printf( "mVertexNum:%d\n", mVertexNum );
    printf( "mUVNum:%d\n", mUVNum );
    printf( "mWeightNum:%d\n", mWeightNum );
    printf( "mTrisNum:%d\n", mTrisNum );
    
    for( i = 0; i < this->mVertexNum; i++ )
        this->mVertexBuffer.push_back( sr.ReadStruct<SKINVERTEX_FOR_GXD>() );
    if ( this->mVertexNum == 4 && this->mUVNum == 4 && this->mTrisNum == 2 )
    {
        auto Src = &this->mVertexBuffer[0];
        float v36[8] = {0};
        memcpy(v36, Src[0].mT, 8u);
        memcpy(&v36[2], Src[1].mT, 8u);
        memcpy(&v36[4], Src[2].mT, 8u);
        memcpy(&v36[6], Src[3].mT, 8u);
        float v41[2] = { v36[0], v36[1] };
        float v43[2] = { v36[0], v36[1] };
        for ( i = 1; i < 4; i++ )
        {
            if ( v36[2 * i] > v41[0] )
                v41[0] = v36[2 * i];
            if ( v36[2 * i] < v43[0] )
                v43[0] = v36[2 * i];
            if (v36[2 * i + 1] > v41[1] )
                v41[1] = v36[2 * i + 1];
            if (v36[2 * i + 1] < v43[1])
                v43[1] = v36[2 * i + 1];
        }
        this->mVertexBufferForBillboard[0].mN[0] = 0.0;
        this->mVertexBufferForBillboard[0].mN[1] = 0.0;
        this->mVertexBufferForBillboard[0].mN[2] = 0.0;
        this->mVertexBufferForBillboard[0].mT[0] = v43[0];
        this->mVertexBufferForBillboard[0].mT[1] = v41[1];
        this->mVertexBufferForBillboard[1].mN[0] = 0.0;
        this->mVertexBufferForBillboard[1].mN[1] = 0.0;
        this->mVertexBufferForBillboard[1].mN[2] = 0.0;
        this->mVertexBufferForBillboard[1].mT[0] = v43[0];
        this->mVertexBufferForBillboard[1].mT[1] = v43[1];
        this->mVertexBufferForBillboard[2].mN[0] = 0.0;
        this->mVertexBufferForBillboard[2].mN[1] = 0.0;
        this->mVertexBufferForBillboard[2].mN[2] = 0.0;
        this->mVertexBufferForBillboard[2].mT[0] = v41[0];
        this->mVertexBufferForBillboard[2].mT[1] = v41[1];
        this->mVertexBufferForBillboard[3].mN[0] = 0.0;
        this->mVertexBufferForBillboard[3].mN[1] = 0.0;
        this->mVertexBufferForBillboard[3].mN[2] = 0.0;
        this->mVertexBufferForBillboard[3].mT[0] = v41[0];
        this->mVertexBufferForBillboard[3].mT[1] = v43[1];
    }
    for( i = 0; i < this->mVertexNum; i++ )
        this->mWeightBuffer.push_back( sr.ReadStruct<SKINWEIGHT_FOR_GXD>() );

    for( i = 0; i < this->mTrisNum; i++ )
        this->mIndexBuffer.push_back( sr.ReadStruct<SKININDEX_FOR_GXD>() );
 
    for( i = 0; i < this->mVertexNum; i++ ){
        this->mMotionVertex.push_back( VERTEX( mVertexBuffer[i].mV ) );
        this->mMotionNormal.push_back( VERTEX( mVertexBuffer[i].mV ) );
    }

    //for (i = 0; i < this->mVertexNum; i++)
    //    memcpy( &this->mMotionVertex[3 * i], &this->mVertexBuffer[i], 12);
    //this->mMotionNormal = (float*)RL_MALLOC( (sizeof(float)*3) * this->mVertexNum );
    //if (!this->mMotionNormal)
    //{
    //    TRACE();
    //    FailAndFree();
    //}
    //for (i = 0; i < this->mVertexNum; i++)
    //    memcpy( &this->mMotionNormal[3 * i], this->mVertexBuffer[i].mN, 12 );

    this->mTexture[0].Init();
    if ( !this->mTexture[0].Load( r, tCheckCreateTexture, tCheckRemoveFileData ) )
    {
        return FALSE;
    }
    this->mTexture[1].Init();
    if ( !this->mTexture[1].Load( r, tCheckCreateTexture, tCheckRemoveFileData ) )
    {
        return FALSE;
    }

    this->mTextureAnimationNum = r->ReadInt();
    //if (this->mTextureAnimationNum > 0)
    //{
    //    v30 = 56 * this->mTextureAnimationNum;
    //    v17 = GetProcessHeap();
    //    this->mTextureAnimation = HeapAlloc(v17, 0, v30);
    //    if (!this->mTextureAnimation)
    //    {
    //    LABEL_65:
    //        SKIN_FOR_GXD::Free(this);
    //        return 0;
    //    }
    //    for (i = 0; i < this->mTextureAnimationNum; ++i)
    //        TEXTURE_FOR_GXD::Init(&this->mTextureAnimation[i]);
    //}
    //for (i = 0; i < this->mTextureAnimationNum; ++i)
    //{
    //    if (!TEXTURE_FOR_GXD::Load(&this->mTextureAnimation[i], hFile, tCheckCreateTexture, tCheckRemoveFileData))
    //        goto LABEL_65;
    //}
    //this->mbIsUseBumpmap = 0;
    //lDistanceToMove = SetFilePointer(hFile, 0, 0, 1u);
    //if (ReadFile(hFile, &this->mbIsUseBumpmap, 4u, &NumberOfBytesRead, 0))
    //{
    //    if (NumberOfBytesRead == 4 && this->mbIsUseBumpmap)
    //    {
    //        if (!TEXTURE_FOR_GXD::Load(&this->mBumpTexture, hFile, tCheckCreateTexture, tCheckRemoveFileData))
    //        {
    //            SetFilePointer(hFile, lDistanceToMove, 0, 0);
    //            this->mbIsUseBumpmap = 0;
    //        }
    //    }
    //    else
    //    {
    //        SetFilePointer(hFile, lDistanceToMove, 0, 0);
    //        this->mbIsUseBumpmap = 0;
    //    }
    //}
    //lDistanceToMove = SetFilePointer(hFile, 0, 0, 1u);
    //if (ReadFile(hFile, &this->mbIsUseSpeculer, 4u, &NumberOfBytesRead, 0))
    //{
    //    if (NumberOfBytesRead == 4 && this->mbIsUseSpeculer)
    //    {
    //        if (!TEXTURE_FOR_GXD::Load(&this->mSpeculerTexture, hFile, tCheckCreateTexture, tCheckRemoveFileData))
    //        {
    //            SetFilePointer(hFile, lDistanceToMove, 0, 0);
    //            this->mbIsUseSpeculer = 0;
    //        }
    //    }
    //    else
    //    {
    //        SetFilePointer(hFile, lDistanceToMove, 0, 0);
    //        this->mbIsUseSpeculer = 0;
    //    }
    //}
    //if ((this->mbIsUseSpeculer || this->mbIsUseBumpmap)
    //    && ReadFile(hFile, &this->mBumpEffect, 0x10u, &NumberOfBytesRead, 0)
    //    && NumberOfBytesRead != 16)
    //{
    //    this->mBumpEffect = *BUMPEFFECT_FOR_GXD::BUMPEFFECT_FOR_GXD(&v32);
    //    SetFilePointer(hFile, lDistanceToMove, 0, 0);
    //}
    this->m_bIsViewBumpLight = 0;
    this->mCheckValidState = TRUE;
    this->mCheckChangeNormalState = 0;


    //mModel = LoadModel("temp.obj");
    ////remove("temp.obj");
    //
    //mModel.meshes[0].animVertices = this->mMotionVertex;
    //mModel.meshes[0].animNormals = this->mMotionNormal;

    TRACE();
    return TRUE;
}

void SKIN_FOR_GXD::ReadyForDraw( int tFrame, MOTION_FOR_GXD* tMotion, BOOL tCheckCalculateNormal )
{
    HANDLE v4; // eax
    const void* v5; // eax
    //SIZE_T v6; // [esp+8h] [ebp-114h]
    D3DXVECTOR3 v8; // [esp+18h] [ebp-104h] BYREF
    D3DXVECTOR3 v9; // [esp+24h] [ebp-F8h] BYREF
    D3DXVECTOR3 v10; // [esp+30h] [ebp-ECh] BYREF
    D3DXVECTOR3 v11; // [esp+3Ch] [ebp-E0h] BYREF
    D3DXVECTOR3 v12; // [esp+48h] [ebp-D4h] BYREF
    D3DXVECTOR3 v13; // [esp+54h] [ebp-C8h] BYREF
    D3DXMATRIX v14; // [esp+60h] [ebp-BCh] BYREF
    D3DXVECTOR3 v15; // [esp+A0h] [ebp-7Ch] BYREF
    D3DXVECTOR3 v16; // [esp+ACh] [ebp-70h] BYREF
    D3DXVECTOR3 v17; // [esp+B8h] [ebp-64h] BYREF
    D3DXVECTOR3 v18; // [esp+C4h] [ebp-58h] BYREF
    D3DXMATRIX* v19; // [esp+D0h] [ebp-4Ch]
    D3DXMATRIX v20; // [esp+D4h] [ebp-48h] BYREF
    int i; // [esp+118h] [ebp-4h]

    if ( !this->mCheckValidState )
    {
        return;
    }
   //if (tMotion->mCheckValidState)
   //{
   //    if ((this->mScaleValue.x <= 0.9998999834060669f
   //        || this->mScaleValue.x >= 1.000100016593933f
   //        || this->mScaleValue.y <= 0.9998999834060669f
   //        || this->mScaleValue.y >= 1.000100016593933f
   //        || this->mScaleValue.z <= 0.9998999834060669f
   //        || this->mScaleValue.z >= 1.000100016593933f)
   //        && tMotion->mCheckValidState
   //        && !this->mScaleKeyMatrix)
   //    {
   //        this->mScaleKeyMatrix = (D3DXMATRIX*)RL_MALLOC( tMotion->mBoneNum << 6 );
   //    }
   //    v19 = &tMotion->mKeyMatrix[tMotion->mBoneNum * tFrame];
   //    if (this->mScaleKeyMatrix)
   //    {
   //        D3DXMatrixScaling( &v20, this->mScaleValue.x, this->mScaleValue.y, this->mScaleValue.z);
   //        for (i = 0; i < tMotion->mBoneNum; ++i)
   //        {
   //            D3DXMATRIX v14 = MatrixIdentity();
   //            v20 = MatrixMultiply( v14, v20 );
   //            memcpy( &this->mScaleKeyMatrix[i], &v20, sizeof(this->mScaleKeyMatrix[i]) );
   //        }
   //        v19 = this->mScaleKeyMatrix;
   //    }
   //    //if (tCheckCalculateNormal)
        //{
        //    for (i = 0; i < this->mVertexNum; ++i)
        //    {
        //        D3DXVec3TransformCoord(&v15, &this->mMotionVertex[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[0]]);
        //        D3DXVec3TransformCoord(&v18, &this->mMotionVertex[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[1]]);
        //        if (this->mWeightBuffer[i].mBlendValue[2] <= 0.0)
        //            v21 = *D3DXVECTOR3::D3DXVECTOR3(&v11, 0.0, 0.0, 0.0);
        //        else
        //            D3DXVec3TransformCoord(&v21, &this->mMotionVertex[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[2]]);
        //        if (this->mWeightBuffer[i].mBlendValue[3] <= 0.0)
        //            v22 = *D3DXVECTOR3::D3DXVECTOR3(&v10, 0.0, 0.0, 0.0);
        //        else
        //            D3DXVec3TransformCoord(&v22, &this->mMotionVertex[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[3]]);
        //        this->mVertexBuffer[i].mV[0] = v15 * this->mWeightBuffer[i].mBlendValue[0]
        //            + v18 * this->mWeightBuffer[i].mBlendValue[1]
        //            + v21.x * this->mWeightBuffer[i].mBlendValue[2]
        //            + v22.x * this->mWeightBuffer[i].mBlendValue[3];
        //        this->mVertexBuffer[i].mV[1] = v16 * this->mWeightBuffer[i].mBlendValue[0]
        //            + v19 * this->mWeightBuffer[i].mBlendValue[1]
        //            + v21.y * this->mWeightBuffer[i].mBlendValue[2]
        //            + v22.y * this->mWeightBuffer[i].mBlendValue[3];
        //        this->mVertexBuffer[i].mV[2] = v17 * this->mWeightBuffer[i].mBlendValue[0]
        //            + v20 * this->mWeightBuffer[i].mBlendValue[1]
        //            + v21.z * this->mWeightBuffer[i].mBlendValue[2]
        //            + v22.z * this->mWeightBuffer[i].mBlendValue[3];
        //        this->mCheckChangeNormalState = 1;
        //        D3DXVec3TransformNormal(&v15, &this->mMotionNormal[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[0]]);
        //        D3DXVec3TransformNormal(&v18, &this->mMotionNormal[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[1]]);
        //        if (this->mWeightBuffer[i].mBlendValue[2] <= 0.0)
        //            v21 = *D3DXVECTOR3::D3DXVECTOR3(&v9, 0.0, 0.0, 0.0);
        //        else
        //            D3DXVec3TransformNormal(&v21, &this->mMotionNormal[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[2]]);
        //        if (this->mWeightBuffer[i].mBlendValue[3] <= 0.0)
        //            v22 = *D3DXVECTOR3::D3DXVECTOR3(&v8, 0.0, 0.0, 0.0);
        //        else
        //            D3DXVec3TransformNormal(&v22, &this->mMotionNormal[3 * i], &v23[this->mWeightBuffer[i].mBoneIndex[3]]);
        //        this->mVertexBuffer[i].mN[0] = v15 * this->mWeightBuffer[i].mBlendValue[0]
        //            + v18 * this->mWeightBuffer[i].mBlendValue[1]
        //            + v21.x * this->mWeightBuffer[i].mBlendValue[2]
        //            + v22.x * this->mWeightBuffer[i].mBlendValue[3];
        //        this->mVertexBuffer[i].mN[1] = v16 * this->mWeightBuffer[i].mBlendValue[0]
        //            + v19 * this->mWeightBuffer[i].mBlendValue[1]
        //            + v21.y * this->mWeightBuffer[i].mBlendValue[2]
        //            + v22.y * this->mWeightBuffer[i].mBlendValue[3];
        //        this->mVertexBuffer[i].mN[2] = v17 * this->mWeightBuffer[i].mBlendValue[0]
        //            + v20 * this->mWeightBuffer[i].mBlendValue[1]
        //            + v21.z * this->mWeightBuffer[i].mBlendValue[2]
        //            + v22.z * this->mWeightBuffer[i].mBlendValue[3];
        //        D3DXVec3Normalize(this->mVertexBuffer[i].mN, this->mVertexBuffer[i].mN);
        //    }
        //}
        //else
   //    {
   //
   //        auto D3DXVec3TransformCoord = []( D3DXVECTOR3* pOut, CONST D3DXVECTOR3* pV, CONST D3DXMATRIX* pM ) -> D3DXVECTOR3* {
   //            *pOut = Vector3Transform( *pV, *pM );
   //            return pOut;
   //        };
   //        //--------------------------
   //        // 3D Vector
   //        //--------------------------
   //        #ifdef __cplusplus
   //        typedef Vector3 D3DVECTOR;
   //        typedef struct D3DXVECTOR3 : public D3DVECTOR
   //        {
   //        public:
   //            D3DXVECTOR3() {};
   //            D3DXVECTOR3( CONST FLOAT * );
   //            D3DXVECTOR3( CONST D3DVECTOR& );
   //            //D3DXVECTOR3( CONST D3DXFLOAT16 * );
   //            D3DXVECTOR3( FLOAT x, FLOAT y, FLOAT z )
   //            {
   //                this->x = x;
   //                this->y = y;
   //                this->z = z;
   //            }
   //            D3DXVECTOR3( double x, double y, double z )
   //            {
   //                this->x = (float)x;
   //                this->y = (float)y;
   //                this->z = (float)z;
   //            }
   //
   //            // casting
   //            operator FLOAT* ();
   //            operator CONST FLOAT* () const;
   //
   //            // assignment operators
   //            D3DXVECTOR3& operator += ( CONST D3DXVECTOR3& );
   //            D3DXVECTOR3& operator -= ( CONST D3DXVECTOR3& );
   //            D3DXVECTOR3& operator *= ( FLOAT );
   //            D3DXVECTOR3& operator /= ( FLOAT );
   //
   //            // unary operators
   //            D3DXVECTOR3 operator + () const;
   //            D3DXVECTOR3 operator - () const;
   //
   //            // binary operators
   //            D3DXVECTOR3 operator + ( CONST D3DXVECTOR3& ) const;
   //            D3DXVECTOR3 operator - ( CONST D3DXVECTOR3& ) const;
   //            D3DXVECTOR3 operator * ( FLOAT ) const;
   //            D3DXVECTOR3 operator / ( FLOAT ) const;
   //
   //            friend D3DXVECTOR3 operator * ( FLOAT, CONST struct D3DXVECTOR3& );
   //
   //            BOOL operator == ( CONST D3DXVECTOR3& ) const;
   //            BOOL operator != ( CONST D3DXVECTOR3& ) const;
   //
   //        } D3DXVECTOR3, *LPD3DXVECTOR3;
   //
   //        #else //!__cplusplus
   //        typedef struct _D3DVECTOR D3DXVECTOR3, *LPD3DXVECTOR3;
   //        #endif //!__cplusplus
   //
   //
   //        for ( i = 0; i < this->mVertexNum; i++ )
   //        {
   //            D3DXVec3TransformCoord( &v15, (D3DXVECTOR3*)&this->mMotionVertex[3 * i], (D3DXMATRIX*)&v19[this->mWeightBuffer[i].mBoneIndex[0]] );
   //            D3DXVec3TransformCoord( &v16, (D3DXVECTOR3*)&this->mMotionVertex[3 * i], (D3DXMATRIX*)&v19[this->mWeightBuffer[i].mBoneIndex[1]] );
   //            if (this->mWeightBuffer[i].mBlendValue[2] <= 0.0f)
   //                v17 = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
   //            else
   //                D3DXVec3TransformCoord( &v17, (D3DXVECTOR3*)&this->mMotionVertex[3 * i], (D3DXMATRIX*)&v19[this->mWeightBuffer[i].mBoneIndex[2]] );
   //            if (this->mWeightBuffer[i].mBlendValue[3] <= 0.0f)
   //                v18 = D3DXVECTOR3( 0.0, 0.0, 0.0 );
   //            else
   //                D3DXVec3TransformCoord( &v18, (D3DXVECTOR3*)&this->mMotionVertex[3 * i], (D3DXMATRIX*)&v19[this->mWeightBuffer[i].mBoneIndex[3]] );
   //            this->mVertexBuffer[i].mV[0] = v15.x * this->mWeightBuffer[i].mBlendValue[0]
   //                + v16.x * this->mWeightBuffer[i].mBlendValue[1]
   //                + v17.x * this->mWeightBuffer[i].mBlendValue[2]
   //                + v18.x * this->mWeightBuffer[i].mBlendValue[3];
   //            this->mVertexBuffer[i].mV[1] = v15.y * this->mWeightBuffer[i].mBlendValue[0]
   //                + v16.y * this->mWeightBuffer[i].mBlendValue[1]
   //                + v17.y * this->mWeightBuffer[i].mBlendValue[2]
   //                + v18.y * this->mWeightBuffer[i].mBlendValue[3];
   //            this->mVertexBuffer[i].mV[2] = v15.z * this->mWeightBuffer[i].mBlendValue[0]
   //                + v16.z * this->mWeightBuffer[i].mBlendValue[1]
   //                + v17.z * this->mWeightBuffer[i].mBlendValue[2]
   //                + v18.z * this->mWeightBuffer[i].mBlendValue[3];
   //            if ( this->mCheckChangeNormalState )
   //            {
   //                this->mCheckChangeNormalState = 0;
   //                memcpy(this->mVertexBuffer[i].mN, &this->mMotionNormal[3 * i], sizeof(this->mVertexBuffer[i].mN));
   //            }
   //        }
   //    }
   //}
   //else
   //{
   //    for (i = 0; i < this->mVertexNum; ++i)
   //    {
   //        memcpy( &this->mVertexBuffer[i].mV[0], &this->mMotionVertex[3 * i], 12 );
   //        memcpy( &this->mVertexBuffer[i].mN[0], &this->mMotionNormal[3 * i], 12 );
   //    }
   //}
}

void SKIN_FOR_GXD::DrawForSelect( void )
{
    if ( !this->mCheckValidState )
    {
        return;
    }
    //if (this->mEffect.mCheckBillboard)
    //{
    //    v1 = D3DXMatrixIdentity(&v6);
    //    ((*mGXD.mGraphicDevice)->SetTransform)(mGXD.mGraphicDevice, 256, v1);
    //    SKIN_FOR_GXD::GetCenterCoord(this, &v3.x);
    //    D3DXVec3TransformCoord(&v3, &v3, &mGXD.mWorldMatrix);
    //    if (this->mEffect.mBillboardSort == 1)
    //        v7 = mGXD.mBillboardVertexInfoForAll;
    //    else
    //        v7 = mGXD.mBillboardVertexInfoForY;
    //    v4 = (this->mSize.mBoxMax[0] - this->mSize.mBoxMin[0]) * 0.5;
    //    v5 = (this->mSize.mBoxMax[1] - this->mSize.mBoxMin[1]) * 0.5;
    //    this->mVertexBufferForBillboard[0].mV[0] = v3.x - v7->x * v4 - v7[1].x * v5;
    //    this->mVertexBufferForBillboard[0].mV[1] = v3.y - v7->y * v4 - v7[1].y * v5;
    //    this->mVertexBufferForBillboard[0].mV[2] = v3.z - v7->z * v4 - v7[1].z * v5;
    //    this->mVertexBufferForBillboard[1].mV[0] = v3.x - v7->x * v4 + v7[1].x * v5;
    //    this->mVertexBufferForBillboard[1].mV[1] = v3.y - v7->y * v4 + v7[1].y * v5;
    //    this->mVertexBufferForBillboard[1].mV[2] = v3.z - v7->z * v4 + v7[1].z * v5;
    //    this->mVertexBufferForBillboard[2].mV[0] = v7->x * v4 + v3.x - v7[1].x * v5;
    //    this->mVertexBufferForBillboard[2].mV[1] = v7->y * v4 + v3.y - v7[1].y * v5;
    //    this->mVertexBufferForBillboard[2].mV[2] = v7->z * v4 + v3.z - v7[1].z * v5;
    //    this->mVertexBufferForBillboard[3].mV[0] = v7->x * v4 + v3.x + v7[1].x * v5;
    //    this->mVertexBufferForBillboard[3].mV[1] = v7->y * v4 + v3.y + v7[1].y * v5;
    //    this->mVertexBufferForBillboard[3].mV[2] = v7->z * v4 + v3.z + v7[1].z * v5;
    //    ((*mGXD.mGraphicDevice)->SetTexture)(mGXD.mGraphicDevice, 0, 0);
    //    CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 7, 0, ".\\S07_GXD.cpp", 2900);
    //    CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 8, 2u, ".\\S07_GXD.cpp", 2901);
    //    ((*mGXD.mGraphicDevice)->DrawPrimitiveUP)(mGXD.mGraphicDevice, 5, 2, this, 32);
    //    CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 8, 3u, ".\\S07_GXD.cpp", 2903);
    //    CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 7, 1u, ".\\S07_GXD.cpp", 2904);
    //    ((*mGXD.mGraphicDevice)->SetTransform)(mGXD.mGraphicDevice, 256, &mGXD.mWorldMatrix);
    //}
    //else
    {
        //((*mGXD.mGraphicDevice)->SetTexture)(mGXD.mGraphicDevice, 0, 0);
        //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 7, 0, ".\\S07_GXD.cpp", 2909);
        //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 8, 2u, ".\\S07_GXD.cpp", 2910);
        //((*mGXD.mGraphicDevice)->DrawIndexedPrimitiveUP)(
        //    mGXD.mGraphicDevice,
        //    4,
        //    0,
        //    this->mVertexNum,
        //    this->mTrisNum,
        //    this->mIndexBuffer,
        //    101,
        //    this->mVertexBuffer,
        //    32);
        //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 8, 3u, ".\\S07_GXD.cpp", 2912);
        //CRenderStateMgr::SetRenderState(&mGXD.m_RenderStateMgr, 7, 1u, ".\\S07_GXD.cpp", 2913);
        
        
        //DrawModel( mModel, Vector3{ 0, 0, 0 }, 1.0f, BLACK );
    }
}