#include "GXD.h"

void MOTION_FOR_GXD::Init( void )
{
	this->mCheckValidState = 0;
    this->mKeyMatrix.clear();
}

BinaryReader* motion_reader;
void MOTION_FOR_GXD::Free( void )
{
	this->mCheckValidState = 0;
    this->mKeyMatrix.clear();
    if( motion_reader )
    {
        delete motion_reader;
        motion_reader = NULL;
    }
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

BOOL MOTION_FOR_GXD::Load( char* tFileName )
{
    int i;
    if ( this->mCheckValidState )
        return FALSE;

    auto r = motion_reader = BinaryReader::LoadFile( tFileName );

    auto z = new ZlibDataPtr( r );
    if ( !Zlib::Decompress( z ) )
    {
        this->Free();
        return FALSE;
    }

    TRACE();
    auto sr = *new BinaryReader( __FUNCTION__, z->tOriginal, z->tOriginalSize );
    this->mFrameNum = sr.ReadInt();
    this->mBoneNum = sr.ReadInt();
    TRACE();
    typedef struct {
        D3DXQUATERNION pQuaternion;
        D3DXVECTOR3 pPosition;
    } TSAnimation;
    TSAnimation anim;

    for ( i = 0; i < (this->mBoneNum * this->mFrameNum); i++ )
    {
        this->mKeyMatrix.push_back( D3DXMATRIX() );
        anim = sr.ReadStruct<TSAnimation>();
        D3DXMatrixRotationQuaternion( &this->mKeyMatrix[i], &anim.pQuaternion );
        this->mKeyMatrix[i].m[3][0] = anim.pPosition.x;
        this->mKeyMatrix[i].m[3][1] = anim.pPosition.y;
        this->mKeyMatrix[i].m[3][2] = anim.pPosition.z;
    }
    TRACE();
    this->mCheckValidState = 1;
    delete motion_reader;
    return TRUE;
}

BOOL MOTION_FOR_GXD::Load( HANDLE hFile )
{
	return TRUE;
}