#include "GXD.h"

void MOTION_FOR_GXD::Init( void )
{
	this->mCheckValidState = 0;
    this->mKeyMatrix.clear();
}

void MOTION_FOR_GXD::Free( void )
{
	this->mCheckValidState = 0;
    this->mKeyMatrix.clear();
}

BOOL MOTION_FOR_GXD::LoadFromG3M( char *tFileName, int tLoadSort )
{
	return TRUE;
}

BOOL MOTION_FOR_GXD::Save( char *tFileName )
{
	return TRUE;
}

BOOL MOTION_FOR_GXD::Save( HANDLE hFile )
{
	return TRUE;
}

typedef struct {
    D3DXQUATERNION pQuaternion;
    D3DXVECTOR3 pPosition;
} TSQuanVec;
BOOL MOTION_FOR_GXD::Load( char* tFileName )
{
    int i;
    if ( this->mCheckValidState )
        return FALSE;

    BinaryReader r;
    BinaryReader::LoadFile(r, tFileName );

    auto z = new ZlibDataPtr( &r );
    if ( !Zlib::Decompress( z ) )
    {
        this->Free();
        return FALSE;
    }

    auto sr = *new BinaryReader( __FUNCTION__, z->tOriginal, z->tOriginalSize );
    this->mFrameNum = sr.ReadInt();
    this->mBoneNum = sr.ReadInt();
    for ( i = 0; i < (this->mBoneNum * this->mFrameNum); i++ )
    {
        this->mKeyMatrix.push_back( D3DXMATRIX() );
        auto qv = sr.ReadStruct<TSQuanVec>();
        D3DXMatrixRotationQuaternion( &this->mKeyMatrix[i], &qv.pQuaternion );
        this->mKeyMatrix[i].m[3][0] = qv.pPosition.x;
        this->mKeyMatrix[i].m[3][1] = qv.pPosition.y;
        this->mKeyMatrix[i].m[3][2] = qv.pPosition.z;
    }
    this->mCheckValidState = 1;
    return TRUE;
}

BOOL MOTION_FOR_GXD::Load( BinaryReader* r )
{
    int i;

    this->mCheckValidState = r->ReadInt();
    if ( !this->mCheckValidState )
        return true;
    this->mCheckValidState = false;

    this->mFrameNum = r->ReadInt();
    this->mBoneNum = r->ReadInt();
    for ( i = 0; i < (this->mBoneNum * this->mFrameNum); i++ )
    {
        this->mKeyMatrix.push_back( D3DXMATRIX() );
        auto qv = r->ReadStruct<TSQuanVec>();
        D3DXMatrixRotationQuaternion( &this->mKeyMatrix[i], &qv.pQuaternion );
        this->mKeyMatrix[i].m[3][0] = qv.pPosition.x;
        this->mKeyMatrix[i].m[3][1] = qv.pPosition.y;
        this->mKeyMatrix[i].m[3][2] = qv.pPosition.z;
    }
    this->mCheckValidState = 1;
	return TRUE;
}