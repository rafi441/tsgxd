#include "GXD.h"

POBJECT_FOR_GXD::POBJECT_FOR_GXD( void )
{
	this->Init();
}

POBJECT_FOR_GXD::~POBJECT_FOR_GXD( void )
{
	this->Free();
}

void POBJECT_FOR_GXD::Init( void )
{
	this->mCheckValidState = 0;
	this->mPSystem = 0;
	this->mParticle.clear();
	this->mScaleValue.x = 1.0f;
	this->mScaleValue.y = 1.0f;
	this->mScaleValue.z = 1.0f;
}

void POBJECT_FOR_GXD::Free( void )
{
	this->mCheckValidState = 0;
	this->mPSystem = 0;
	//if ( this->mParticle )
	//{
	//	delete this->mParticle;
	//	this->mParticle = 0;
	//}
    this->mParticle.clear();
	this->mScaleValue.x = 1.0f;
	this->mScaleValue.y = 1.0f;
	this->mScaleValue.z = 1.0f;
}

void POBJECT_FOR_GXD::Set( PSYSTEM_FOR_GXD* tPSystem )
{
    if ( this->mCheckValidState )
        return;
    if ( !mGXD.mParticleVertexBuffer.size() )
        return;
    if( !tPSystem || !tPSystem->mCheckValidState )
        return;
    tPSystem->Adjust();
    this->mPSystem = tPSystem;
    this->mTotalLifeTime = 0.0f;
    this->mEmitParticleNum = 0.0f;
    this->mMaxParticleNum = (int)(tPSystem->mEmitRate * tPSystem->mOneLifeTime);
    if ( this->mMaxParticleNum >= 1 )
    {
        for ( int i = 0; i < this->mMaxParticleNum; i++ )
        {
            this->mParticle.push_back( PARTICLE_FOR_GXD() );
            this->mParticle[i].mCheckValidState = 0;
        }
		this->mCheckValidState = TRUE;
    }
}

void POBJECT_FOR_GXD::Update( float tTime, float tCoord[3], float tAngle[3] )
{
    PSYSTEM_FOR_GXD* v4; // esi
    PSYSTEM_FOR_GXD* v5; // esi
    PSYSTEM_FOR_GXD* v6; // esi
    float v7; // [esp+4Ch] [ebp-330h]
    float Anglea; // [esp+4Ch] [ebp-330h]
    float Angleb; // [esp+4Ch] [ebp-330h]
    float Anglec; // [esp+4Ch] [ebp-330h]
    float Angled; // [esp+4Ch] [ebp-330h]
    float Anglee; // [esp+4Ch] [ebp-330h]
    float Anglef; // [esp+4Ch] [ebp-330h]
    float Angleg; // [esp+4Ch] [ebp-330h]
    float Angleh; // [esp+4Ch] [ebp-330h]
    float v16; // [esp+58h] [ebp-324h]
    float v17; // [esp+5Ch] [ebp-320h]
    float v18; // [esp+60h] [ebp-31Ch]
    float v19; // [esp+64h] [ebp-318h]
    float v20; // [esp+68h] [ebp-314h]
    float v21; // [esp+6Ch] [ebp-310h]
    float v22; // [esp+70h] [ebp-30Ch]
    float v23; // [esp+74h] [ebp-308h]
    float v24; // [esp+78h] [ebp-304h]
    float v25; // [esp+7Ch] [ebp-300h]
    float v26; // [esp+80h] [ebp-2FCh]
    float v27; // [esp+84h] [ebp-2F8h]
    float v28; // [esp+88h] [ebp-2F4h]
    float v29; // [esp+8Ch] [ebp-2F0h]
    float v30; // [esp+90h] [ebp-2ECh]
    float v31; // [esp+94h] [ebp-2E8h]
    float v32; // [esp+98h] [ebp-2E4h]
    float v33; // [esp+9Ch] [ebp-2E0h]
    float v34; // [esp+A0h] [ebp-2DCh]
    float v35; // [esp+A4h] [ebp-2D8h]
    FLOAT v36; // [esp+ACh] [ebp-2D0h]
    FLOAT v37; // [esp+B0h] [ebp-2CCh]
    FLOAT Angle; // [esp+B4h] [ebp-2C8h]
    D3DXMATRIX v40; // [esp+BCh] [ebp-2C0h] BYREF
    D3DXMATRIX v41; // [esp+FCh] [ebp-280h] BYREF
    D3DXMATRIX v42; // [esp+13Ch] [ebp-240h] BYREF
    D3DXMATRIX v43; // [esp+17Ch] [ebp-200h] BYREF
    D3DXVECTOR3 pV; // [esp+1BCh] [ebp-1C0h] BYREF
    D3DXVECTOR3 v45; // [esp+1C8h] [ebp-1B4h] BYREF
    float v46; // [esp+1D4h] [ebp-1A8h]
    float v47; // [esp+1D8h] [ebp-1A4h]
    float v48; // [esp+1DCh] [ebp-1A0h]
    float v49; // [esp+1E0h] [ebp-19Ch]
    D3DXVECTOR2 v50; // [esp+1E4h] [ebp-198h] BYREF
    D3DXVECTOR2 v51; // [esp+1ECh] [ebp-190h]
    int i; // [esp+1F4h] [ebp-188h]
    int v53; // [esp+1F8h] [ebp-184h]
    D3DXMATRIX v55; // [esp+23Ch] [ebp-140h] BYREF
    D3DXMATRIX pOut; // [esp+27Ch] [ebp-100h] BYREF
    D3DXMATRIX v57; // [esp+2BCh] [ebp-C0h] BYREF
    D3DXMATRIX v58; // [esp+2FCh] [ebp-80h] BYREF
    D3DXMATRIX pM; // [esp+33Ch] [ebp-40h] BYREF

    //TRACEI("pobj.mGXD.mParticleVertexBuffer.size()", mGXD.mParticleVertexBuffer.size());
    if ( !this->mCheckValidState || !mGXD.mParticleVertexBuffer.size() )
    {
        return;
    }
    this->mTotalLifeTime = this->mTotalLifeTime + tTime;
    memcpy(this->mCoord, tCoord, sizeof(this->mCoord));
    memcpy(this->mAngle, tAngle, sizeof(this->mAngle));
    v53 = 0;
    v4 = v5 = v6 = this->mPSystem;
    v46 = mGXD.GetRandomNumber( v4->mMinRandomForce[0], v4->mMaxRandomForce[0]) + v4->mMainForce[0];
    v47 = mGXD.GetRandomNumber( v5->mMinRandomForce[1], v5->mMaxRandomForce[1]) + v5->mMainForce[1];
    v48 = mGXD.GetRandomNumber( v6->mMinRandomForce[2], v6->mMaxRandomForce[2]) + v6->mMainForce[2];
    for (i = 0; i < this->mMaxParticleNum; ++i)
    {
        if (this->mParticle[i].mCheckValidState)
        {
            this->mParticle[i].mOneLifeTime = this->mParticle[i].mOneLifeTime + tTime;
            if (this->mPSystem->mOneLifeTime >= this->mParticle[i].mOneLifeTime)
            {
                this->mParticle[i].mLocation[0] = this->mParticle[i].mVelocity[0] * tTime + this->mParticle[i].mLocation[0];
                this->mParticle[i].mLocation[1] = this->mParticle[i].mVelocity[1] * tTime + this->mParticle[i].mLocation[1];
                this->mParticle[i].mLocation[2] = this->mParticle[i].mVelocity[2] * tTime + this->mParticle[i].mLocation[2];
                if (this->mParticle[i].mWeight > 0.0f)
                {
                    v49 = 1.0f / this->mParticle[i].mWeight;
                    this->mParticle[i].mVelocity[0] = v49 * v46 * tTime + this->mParticle[i].mVelocity[0];
                    this->mParticle[i].mVelocity[1] = v49 * v47 * tTime + this->mParticle[i].mVelocity[1];
                    this->mParticle[i].mVelocity[2] = v49 * v48 * tTime + this->mParticle[i].mVelocity[2];
                }
                this->mParticle[i].mWeight = this->mPSystem->mWeightDelta * tTime + this->mParticle[i].mWeight;
                if (this->mParticle[i].mWeight < 0.0f)
                    this->mParticle[i].mWeight = 0.0f;
                this->mParticle[i].mSize = this->mPSystem->mSizeDelta * tTime + this->mParticle[i].mSize;
                if (this->mParticle[i].mSize < 0.0f)
                    this->mParticle[i].mSize = 0.0f;
                this->mParticle[i].mColor[0] = this->mPSystem->mColorDelta[0] * tTime + this->mParticle[i].mColor[0];
                this->mParticle[i].mColor[1] = this->mPSystem->mColorDelta[1] * tTime + this->mParticle[i].mColor[1];
                this->mParticle[i].mColor[2] = this->mPSystem->mColorDelta[2] * tTime + this->mParticle[i].mColor[2];
                this->mParticle[i].mColor[3] = this->mPSystem->mColorDelta[3] * tTime + this->mParticle[i].mColor[3];
                ++v53;
            }
            else
            {
                this->mParticle[i].mCheckValidState = 0;
            }
        }
    }
    if (this->mPSystem->mTotalLifeTime <= 0.0f || this->mPSystem->mTotalLifeTime >= this->mTotalLifeTime)
    {
        this->mEmitParticleNum = this->mPSystem->mEmitRate * tTime + this->mEmitParticleNum;
        if (this->mEmitParticleNum >= 1.0f)
        {
            D3DXMATRIX* pMatWorld = &mGXD.mWorldMatrix;
            D3DXMATRIX MatTemp;  // Temp matrix for rotations.
            D3DXMATRIX MatRot;   // Final rotation matrix, applied to 
                                 // pMatWorld.
            if (this->mPSystem->mMotion.mCheckValidState)
                memcpy(
                    &MatRot,
                    &this->mPSystem->mMotion.mKeyMatrix[(int)(this->mPSystem->mFrameRatio * this->mTotalLifeTime)
                    % this->mPSystem->mMotion.mFrameNum],
                    sizeof(MatRot));
            else
                D3DXMatrixIdentity(&MatRot);


            D3DXMatrixTranslation(&v55, this->mCoord[0], this->mCoord[1], this->mCoord[2]);
            Angle = this->mAngle[0] * 0.01745329238474369f;
            //D3DXMatrixRotationX(&pOut, Angle);
            //D3DXMatrixMultiply( &pOut,  );
            v37 = this->mAngle[1] * 0.01745329238474369f;
            //D3DXMatrixRotationY(&v57, v37);
            v36 = this->mAngle[2] * 0.01745329238474369f;
            //D3DXMatrixRotationZ(&v58, v36);
            //v54 *= v58;
            //v54 *= v57;
            //v54 *= pOut;
            //v54 *= v55;
            //memcpy( &pM, v54, sizeof(pM) );


            // Produce and combine the rotation matrices.
            D3DXMatrixRotationX(&MatTemp, Angle);         // Pitch
            D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
            D3DXMatrixRotationY(&MatTemp, v37);           // Yaw
            D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
            D3DXMatrixRotationZ(&MatTemp, v36);          // Roll
            D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);

            D3DXMatrixMultiply(pMatWorld, &MatRot, pMatWorld);
            pM = *pMatWorld;

            for (i = 0; i < this->mMaxParticleNum; ++i)
            {
                if (!this->mParticle[i].mCheckValidState)
                {
                    switch ( (int)this->mPSystem->mEmitSort)
                    {
                    case 1:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        pV.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.z = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec3Normalize(&pV, &pV);
                        pV *= this->mPSystem->mEmitRadius;
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, & pV, & pM );
                        v45.x = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[2],
                            this->mPSystem->mMaxRandomVelocity[2]);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 2:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        pV.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.z = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec3Normalize(&pV, &pV);
                        v45 = pV;
                        v45 *=(this->mPSystem->mEmitRadius);
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        v7 = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45 *=(v7);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 3:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        pV.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.z = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec3Normalize(&pV, &pV);
                        Anglea = mGXD.GetRandomNumber( 0.0f, this->mPSystem->mEmitRadius );
                        pV *=(Anglea);
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        v45.x = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[2],
                            this->mPSystem->mMaxRandomVelocity[2]);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 4:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        pV.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        pV.z = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec3Normalize(&pV, &pV);
                        v45 = pV;
                        Angleb = mGXD.GetRandomNumber( 0.0f, this->mPSystem->mEmitRadius );
                        v45 *=(Angleb);
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        Anglec = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45 *=(Anglec);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 5:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        v35 = this->mPSystem->mEmitRange[0] * 0.5f;
                        v34 = this->mPSystem->mEmitRange[0] * -0.5f;
                        pV.x = mGXD.GetRandomNumber( v34, v35 );
                        v33 = this->mPSystem->mEmitRange[1] * 0.5f;
                        v32 = this->mPSystem->mEmitRange[1] * -0.5f;
                        pV.y = mGXD.GetRandomNumber( v32, v33 );
                        v31 = this->mPSystem->mEmitRange[2] * 0.5f;
                        v30 = this->mPSystem->mEmitRange[2] * -0.5f;
                        pV.z = mGXD.GetRandomNumber( v30, v31 );
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        v45.x = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[2],
                            this->mPSystem->mMaxRandomVelocity[2]);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;

                        printf("(int)POBJECT_FOR_GXD::Update()->this->mPSystem->mEmitSort=%d\n", (int)this->mPSystem->mEmitSort );
                        printf("(int)POBJECT_FOR_GXD::Update()->mEmitParticleNum=%d\n", (int)this->mEmitParticleNum );
                        break;
                    case 6:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        v29 = this->mPSystem->mEmitRange[0] * 0.5f;
                        v28 = this->mPSystem->mEmitRange[0] * -0.5f;
                        pV.x = mGXD.GetRandomNumber( v28, v29 );
                        v27 = this->mPSystem->mEmitRange[1] * 0.5f;
                        v26 = this->mPSystem->mEmitRange[1] * -0.5f;
                        pV.y = mGXD.GetRandomNumber( v26, v27 );
                        v25 = this->mPSystem->mEmitRange[2] * 0.5f;
                        v24 = this->mPSystem->mEmitRange[2] * -0.5f;
                        pV.z = mGXD.GetRandomNumber( v24, v25 );
                        D3DXVec3Normalize(&v45, &pV);
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        Angled = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        pV *=(Angled);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 7:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        v50.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        v50.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec2Normalize(&v50, &v50);
                        v50 *=(this->mPSystem->mEmitRadius);
                        pV.x = v50.x;
                        v23 = this->mPSystem->mEmitRange[1] * 0.5f;
                        v22 = this->mPSystem->mEmitRange[1] * -0.5f;
                        pV.y = mGXD.GetRandomNumber( v22, v23);
                        pV.z = v50.y;
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        v45.x = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[2],
                            this->mPSystem->mMaxRandomVelocity[2]);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 8:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        v50.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        v50.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec2Normalize(&v50, &v50);
                        Anglee = mGXD.GetRandomNumber( 0.0f, this->mPSystem->mEmitRadius );
                        v50 *=(Anglee);
                        pV.x = v50.x;
                        v21 = this->mPSystem->mEmitRange[1] * 0.5f;
                        v20 = this->mPSystem->mEmitRange[1] * -0.5f;
                        pV.y = mGXD.GetRandomNumber( v20, v21);
                        pV.z = v50.y;
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        v45.x = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[2],
                            this->mPSystem->mMaxRandomVelocity[2]);
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 9:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        v50.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        v50.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec2Normalize(&v50, &v50);
                        v51 = v50;
                        v51 *=(this->mPSystem->mEmitRadius);
                        pV.x = v50.x;
                        v19 = this->mPSystem->mEmitRange[1] * 0.5f;
                        v18 = this->mPSystem->mEmitRange[1] * -0.5f;
                        pV.y = mGXD.GetRandomNumber( v18, v19);
                        pV.z = v50.y;
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        Anglef = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v51 *=(Anglef);
                        v45.x = v51.x;
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = v51.y;
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    case 10:
                        this->mParticle[i].mCheckValidState = 1;
                        this->mParticle[i].mOneLifeTime = 0.0f;
                        v50.x = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        v50.y = mGXD.GetRandomNumber( -100.0f, 100.0f );
                        D3DXVec2Normalize(&v50, &v50);
                        v51 = v50;
                        Angleg = mGXD.GetRandomNumber( 0.0f, this->mPSystem->mEmitRadius );
                        v51 *=(Angleg);
                        pV.x = v50.x;
                        v17 = this->mPSystem->mEmitRange[1] * 0.5f;
                        v16 = this->mPSystem->mEmitRange[1] * -0.5f;
                        pV.y = mGXD.GetRandomNumber( v16, v17);
                        pV.z = v50.y;
                        D3DXVec3TransformCoord( (D3DXVECTOR3*)this->mParticle[i].mLocation, &pV, &pM );
                        Angleh = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[0],
                            this->mPSystem->mMaxRandomVelocity[0]);
                        v51 *=(Angleh);
                        v45.x = v51.x;
                        v45.y = mGXD.GetRandomNumber(
                            this->mPSystem->mMinRandomVelocity[1],
                            this->mPSystem->mMaxRandomVelocity[1]);
                        v45.z = v51.y;
                        D3DXVec3TransformNormal( (D3DXVECTOR3*)this->mParticle[i].mVelocity, &v45, &pM );
                        this->mParticle[i].mWeight = this->mPSystem->mWeight;
                        this->mParticle[i].mSize = this->mPSystem->mSize;
                        memcpy(this->mParticle[i].mColor, this->mPSystem->mMinColor, sizeof(this->mParticle[i].mColor));
                        this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
                        break;
                    default:
                        break;
                    }
                    if ( this->mEmitParticleNum < 1.0f )
                        break;
                }
            }
            while ( this->mEmitParticleNum > 1.0f )
                this->mEmitParticleNum = this->mEmitParticleNum - 1.0f;
        }
    }
    else if ( !v53 )
    {
        this->Free();
    }
}

void POBJECT_FOR_GXD::Draw( void )
{
    float X; // [esp+38h] [ebp-58h]
    float v3; // [esp+40h] [ebp-50h]
    float v4; // [esp+44h] [ebp-4Ch]
    float v5; // [esp+48h] [ebp-48h]
    float v6; // [esp+4Ch] [ebp-44h]
    float v7; // [esp+50h] [ebp-40h]
    float v8; // [esp+54h] [ebp-3Ch]
    float v9; // [esp+58h] [ebp-38h]
    float v10; // [esp+5Ch] [ebp-34h]
    float v11; // [esp+60h] [ebp-30h]
    float v12; // [esp+64h] [ebp-2Ch]
    float v13; // [esp+68h] [ebp-28h]
    float v14; // [esp+6Ch] [ebp-24h]
    int i; // [esp+70h] [ebp-20h]
    int j; // [esp+70h] [ebp-20h]
    int v17; // [esp+74h] [ebp-1Ch]
    float v18; // [esp+78h] [ebp-18h]
    float v19; // [esp+7Ch] [ebp-14h]
    int v20; // [esp+80h] [ebp-10h]
    int v21; // [esp+80h] [ebp-10h]
    int v22; // [esp+88h] [ebp-8h]
    float v23; // [esp+8Ch] [ebp-4h]

    if ( this->mCheckValidState && mGXD.mParticleVertexBuffer.size() && mGXD.CheckPointInFrustum( this->mCoord ) )
    {
        X = (this->mCoord[0] - mGXD.mCameraEye.x) * (this->mCoord[0] - mGXD.mCameraEye.x)
            + (this->mCoord[1] - mGXD.mCameraEye.y) * (this->mCoord[1] - mGXD.mCameraEye.y)
            + (this->mCoord[2] - mGXD.mCameraEye.z) * (this->mCoord[2] - mGXD.mCameraEye.z);
        v23 = sqrtf(X);
        v19 = 1.0f - (v23 - mGXD.mLODLengthInfo[0]) / (mGXD.mLODLengthInfo[1] - mGXD.mLODLengthInfo[0]);
        if ( v19 < 0.0f )
             v19 = 0.0f ;
        if ( v19 > 1.0f )
             v19 = 1.0f ;
        v20 = 0;
        for (i = 0; i < this->mMaxParticleNum; ++i)
        {
            if (this->mParticle[i].mCheckValidState)
                ++v20;
        }
        v21 = (v20 * v19);
        v17 = 0;
        for (j = 0; j < this->mMaxParticleNum; ++j)
        {
            if (this->mParticle[j].mCheckValidState)
            {
                if (v17 <= v21 - 1)
                {
                    v18 = this->mParticle[j].mSize;
                    v22 = (int)this->mParticle[j].mColor[2] | ((int)this->mParticle[j].mColor[1] << 8) | ((int)this->mParticle[j].mColor[0] << 16) | ((int)this->mParticle[j].mColor[3] << 24);
                    v3 = -mGXD.mBillboardVertexInfoForAll[0].x * v18 + mGXD.mBillboardVertexInfoForAll[1].x * v18;
                    v4 = -mGXD.mBillboardVertexInfoForAll[0].y * v18 + mGXD.mBillboardVertexInfoForAll[1].y * v18;
                    v5 = -mGXD.mBillboardVertexInfoForAll[0].z * v18 + mGXD.mBillboardVertexInfoForAll[1].z * v18;
                    v6 = mGXD.mBillboardVertexInfoForAll[0].x * v18 + mGXD.mBillboardVertexInfoForAll[1].x * v18;
                    v7 = mGXD.mBillboardVertexInfoForAll[0].y * v18 + mGXD.mBillboardVertexInfoForAll[1].y * v18;
                    v8 = mGXD.mBillboardVertexInfoForAll[0].z * v18 + mGXD.mBillboardVertexInfoForAll[1].z * v18;
                    v9 = mGXD.mBillboardVertexInfoForAll[0].x * v18 - mGXD.mBillboardVertexInfoForAll[1].x * v18;
                    v10 = mGXD.mBillboardVertexInfoForAll[0].y * v18 - mGXD.mBillboardVertexInfoForAll[1].y * v18;
                    v11 = mGXD.mBillboardVertexInfoForAll[0].z * v18 - mGXD.mBillboardVertexInfoForAll[1].z * v18;
                    v12 = -mGXD.mBillboardVertexInfoForAll[0].x * v18 - mGXD.mBillboardVertexInfoForAll[1].x * v18;
                    v13 = -mGXD.mBillboardVertexInfoForAll[0].y * v18 - mGXD.mBillboardVertexInfoForAll[1].y * v18;
                    v14 = -mGXD.mBillboardVertexInfoForAll[0].z * v18 - mGXD.mBillboardVertexInfoForAll[1].z * v18;
                    mGXD.mParticleVertexBuffer[6 * v17 + 0].mV[0] = this->mParticle[j].mLocation[0] * this->mScaleValue.x + v3;
                    mGXD.mParticleVertexBuffer[6 * v17 + 0].mV[1] = this->mParticle[j].mLocation[1] * this->mScaleValue.y + v4;
                    mGXD.mParticleVertexBuffer[6 * v17 + 0].mV[2] = this->mParticle[j].mLocation[2] * this->mScaleValue.z + v5;
                    mGXD.mParticleVertexBuffer[6 * v17 + 0].mC = v22;
                    mGXD.mParticleVertexBuffer[6 * v17 + 1].mV[0] = this->mParticle[j].mLocation[0] * this->mScaleValue.x + v6;
                    mGXD.mParticleVertexBuffer[6 * v17 + 1].mV[1] = this->mParticle[j].mLocation[1] * this->mScaleValue.y + v7;
                    mGXD.mParticleVertexBuffer[6 * v17 + 1].mV[2] = this->mParticle[j].mLocation[2] * this->mScaleValue.z + v8;
                    mGXD.mParticleVertexBuffer[6 * v17 + 1].mC = v22;
                    mGXD.mParticleVertexBuffer[6 * v17 + 2].mV[0] = this->mParticle[j].mLocation[0] * this->mScaleValue.x + v12;
                    mGXD.mParticleVertexBuffer[6 * v17 + 2].mV[1] = this->mParticle[j].mLocation[1] * this->mScaleValue.y + v13;
                    mGXD.mParticleVertexBuffer[6 * v17 + 2].mV[2] = this->mParticle[j].mLocation[2] * this->mScaleValue.z + v14;
                    mGXD.mParticleVertexBuffer[6 * v17 + 2].mC = v22;
                    mGXD.mParticleVertexBuffer[6 * v17 + 3].mV[0] = this->mParticle[j].mLocation[0] * this->mScaleValue.x + v12;
                    mGXD.mParticleVertexBuffer[6 * v17 + 3].mV[1] = this->mParticle[j].mLocation[1] * this->mScaleValue.y + v13;
                    mGXD.mParticleVertexBuffer[6 * v17 + 3].mV[2] = this->mParticle[j].mLocation[2] * this->mScaleValue.z + v14;
                    mGXD.mParticleVertexBuffer[6 * v17 + 3].mC = v22;
                    mGXD.mParticleVertexBuffer[6 * v17 + 4].mV[0] = this->mParticle[j].mLocation[0] * this->mScaleValue.x + v6;
                    mGXD.mParticleVertexBuffer[6 * v17 + 4].mV[1] = this->mParticle[j].mLocation[1] * this->mScaleValue.y + v7;
                    mGXD.mParticleVertexBuffer[6 * v17 + 4].mV[2] = this->mParticle[j].mLocation[2] * this->mScaleValue.z + v8;
                    mGXD.mParticleVertexBuffer[6 * v17 + 4].mC = v22;
                    mGXD.mParticleVertexBuffer[6 * v17 + 5].mV[0] = this->mParticle[j].mLocation[0] * this->mScaleValue.x + v9;
                    mGXD.mParticleVertexBuffer[6 * v17 + 5].mV[1] = this->mParticle[j].mLocation[1] * this->mScaleValue.y + v10;
                    mGXD.mParticleVertexBuffer[6 * v17 + 5].mV[2] = this->mParticle[j].mLocation[2] * this->mScaleValue.z + v11;
                    mGXD.mParticleVertexBuffer[6 * v17 + 5].mC = v22;
                    v17++;
                    if (v17 == mGXD.mMaxParticleNum)
                        break;
                }
            }
        }
        if (v17)
        {
            mGXD.mGraphicDevice->SetTexture( 0, this->mPSystem->mTexture.mTexture );
            mGXD.mGraphicDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 2 * v17, &mGXD.mParticleVertexBuffer[0], 24 );
        }
    }
}

const D3DXVECTOR3& POBJECT_FOR_GXD::GetScale() const
{
    return this->mScaleValue;
}
BOOL POBJECT_FOR_GXD::SetScale( float x, float y, float z )
{
    this->mScaleValue.x = x;
    this->mScaleValue.y = y;
    this->mScaleValue.z = z;
    return TRUE;

    /*
      if ( !this->mCheckValidState )
    return 0;
  if ( a2 <= 0.00009999999747378752 || a3 <= 0.00009999999747378752 || a4 <= 0.00009999999747378752 )
    return 0;
  if ( a2 > -0.00009999999747378752 && a2 < 0.00009999999747378752
    || a3 > -0.00009999999747378752 && a3 < 0.00009999999747378752
    || a4 > -0.00009999999747378752 && a4 < 0.00009999999747378752 )
  {
    return 0;
  }
  this->mScaleValue.x = a2;
  this->mScaleValue.y = a3;
  this->mScaleValue.z = a4;
  return 1;
    */
}