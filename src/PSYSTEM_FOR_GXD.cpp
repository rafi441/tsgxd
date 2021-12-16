#include "GXD.h"

struct Vector3 {
    float x, y, z;
};
struct Vector4 {
    float x, y, z, w;
};

bool PSYSTEM_FOR_GXD::Read( BinaryReader* r )
{
    mTotalLifeTime = r->ReadFloat();
    mFrameRatio = r->ReadFloat();
    mEmitRate = r->ReadFloat();
    mEmitSort = r->ReadFloat();
    mEmitRadius = r->ReadFloat();
    memcpy( mEmitRange, &r->ReadStruct<Vector3>(), sizeof(Vector3) );
    mOneLifeTime = r->ReadFloat();
    memcpy( mMinRandomVelocity, &r->ReadStruct<Vector3>(), sizeof(Vector3) );
    memcpy( mMaxRandomVelocity, &r->ReadStruct<Vector3>(), sizeof(Vector3) );
    mWeight = r->ReadFloat();
    mSize = r->ReadFloat();
    memcpy( mMinColor, &r->ReadStruct<Vector4>(), sizeof(Vector4) );
    memcpy( mMaxColor, &r->ReadStruct<Vector4>(), sizeof(Vector4) );
    memcpy( mMainForce, &r->ReadStruct<Vector3>(), sizeof(Vector3) );
    memcpy( mMinRandomForce, &r->ReadStruct<Vector3>(), sizeof(Vector3) );
    memcpy( mMaxRandomForce, &r->ReadStruct<Vector3>(), sizeof(Vector3) );
    mWeightDelta = r->ReadFloat();
    mSizeDelta = r->ReadFloat();

    return true;
}


PSYSTEM_FOR_GXD::PSYSTEM_FOR_GXD( void )
{
    this->Init();
}

PSYSTEM_FOR_GXD::~PSYSTEM_FOR_GXD( void )
{
    this->Free();
}

void PSYSTEM_FOR_GXD::Init( void )
{
    this->mCheckValidState = FALSE;
    this->mTexture.Init();
    this->mMotion.Init();
}

void PSYSTEM_FOR_GXD::Free( void )
{
    this->mCheckValidState = FALSE;
    this->mTexture.Free();
    this->mMotion.Free();
}

BOOL PSYSTEM_FOR_GXD::Save( char* tFileName ){ return TRUE; }
BOOL PSYSTEM_FOR_GXD::Save( HANDLE hFile ){ return TRUE; }

BOOL PSYSTEM_FOR_GXD::Load( char* tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData )
{
    if( this->mCheckValidState )
        return FALSE;
    BinaryReader r;
    BinaryReader::LoadFile( r, tFileName );
    if( r.isError )
    {
        return FALSE;
    }

    if( !this->mTexture.Load( &r, tCheckCreateTexture, tCheckRemoveFileData ) )
    {
        TRACEI( "texture.load", 0 );
        return FALSE;
    }
    if( !this->mMotion.Load( &r ) )
    {
        TRACEI( "motion.load", 0 );
        return FALSE;
    }

    this->Read( &r );

    this->mCheckValidState = 1;
    return TRUE;
}

BOOL PSYSTEM_FOR_GXD::Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData ){ return TRUE; }

void PSYSTEM_FOR_GXD::Adjust( void )
{
    if ( !this->mCheckValidState )
    {
        return;
    }
    if ( this->mFrameRatio < 0.0f )
      this->mFrameRatio = 0.0f;
    if ( this->mEmitRate < 0.0f )
      this->mEmitRate = 0.0f;
    if ( this->mEmitRadius < 0.0f )
      this->mEmitRadius = 0.0f;
    if ( this->mEmitRange[0] < 0.0f )
      this->mEmitRange[0] = 0.0f;
    if ( this->mEmitRange[1] < 0.0f )
      this->mEmitRange[1] = 0.0f;
    if ( this->mEmitRange[2] < 0.0f )
      this->mEmitRange[2] = 0.0f;
    if ( this->mOneLifeTime < 0.009999999776482582f )
      this->mOneLifeTime = 0.0099999998f;
    if ( this->mWeight < 0.0f )
      this->mWeight = 0.0f;
    if ( this->mSize < 0.0f )
      this->mSize = 0.0f;
    if ( this->mMinColor[0] < 0.0f )
      this->mMinColor[0] = 0.0f;
    if ( this->mMinColor[0] > 255.0f )
      this->mMinColor[0] = 255.0f;
    if ( this->mMinColor[1] < 0.0f )
      this->mMinColor[1] = 0.0f;
    if ( this->mMinColor[1] > 255.0f )
      this->mMinColor[1] = 255.0f;
    if ( this->mMinColor[2] < 0.0f )
      this->mMinColor[2] = 0.0f;
    if ( this->mMinColor[2] > 255.0f )
      this->mMinColor[2] = 255.0f;
    if ( this->mMinColor[3] < 0.0f )
      this->mMinColor[3] = 0.0f;
    if ( this->mMinColor[3] > 255.0f )
      this->mMinColor[3] = 255.0f;
    if ( this->mMaxColor[0] < 0.0f )
      this->mMaxColor[0] = 0.0f;
    if ( this->mMaxColor[0] > 255.0f )
      this->mMaxColor[0] = 255.0f;
    if ( this->mMaxColor[1] < 0.0f )
      this->mMaxColor[1] = 0.0f;
    if ( this->mMaxColor[1] > 255.0f )
      this->mMaxColor[1] = 255.0f;
    if ( this->mMaxColor[2] < 0.0f )
      this->mMaxColor[2] = 0.0f;
    if ( this->mMaxColor[2] > 255.0f )
      this->mMaxColor[2] = 255.0f;
    if ( this->mMaxColor[3] < 0.0f )
      this->mMaxColor[3] = 0.0f;
    if ( this->mMaxColor[3] > 255.0f )
      this->mMaxColor[3] = 255.0f;
    this->mColorDelta[0] = (this->mMaxColor[0] - this->mMinColor[0]) / this->mOneLifeTime;
    this->mColorDelta[1] = (this->mMaxColor[1] - this->mMinColor[1]) / this->mOneLifeTime;
    this->mColorDelta[2] = (this->mMaxColor[2] - this->mMinColor[2]) / this->mOneLifeTime;
    this->mColorDelta[3] = (this->mMaxColor[3] - this->mMinColor[3]) / this->mOneLifeTime;
}