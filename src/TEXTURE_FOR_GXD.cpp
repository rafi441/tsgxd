#include "GXD.h"

void TEXTURE_FOR_GXD::Init( void )
{
	this->mCheckValidState = FALSE;
}

void TEXTURE_FOR_GXD::Free( void )
{
	this->mCheckValidState = FALSE;
}

BOOL TEXTURE_FOR_GXD::Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData )
{
	if( this->mCheckValidState )
		return FALSE;

	this->mFileDataSize = r->ReadInt();
	if( !this->mFileDataSize )
		return TRUE;

	auto z = new ZlibDataPtr( r, FALSE );
	if ( !Zlib::Decompress( z ) )
	{
		this->Free();
		return FALSE;
	}

	auto sr = *new BinaryReader( __FUNCTION__, z->tOriginal, z->tOriginalSize, 0, false );
	this->mFileData = sr.ReadBytes( this->mFileDataSize );
	this->mProcessModeCase = sr.ReadInt();
	this->mAlphaModeCase = sr.ReadInt();

	if ( FAILED( D3DXGetImageInfoFromFileInMemory( this->mFileData, this->mFileDataSize, &this->mTextureInfo ) ) )
	{
		this->Free();
		return FALSE;
	}

	if ( this->mTextureInfo.Format != D3DFMT_DXT1
		&& this->mTextureInfo.Format != D3DFMT_DXT2
		&& this->mTextureInfo.Format != D3DFMT_DXT3
		&& this->mTextureInfo.Format != D3DFMT_DXT5
		|| SUCCEEDED( D3DXCreateTextureFromFileInMemoryEx(
			mGXD.mGraphicDevice,
			this->mFileData,
			this->mFileDataSize,
			this->mTextureInfo.Width,
			this->mTextureInfo.Height,
			0,
			0,
			this->mTextureInfo.Format,
			D3DPOOL_MANAGED,
			1,
			1,
			0,
			0,
			0,
			&this->mTexture ) ) )
	{
		//goto LABEL_93;
	}

	if ( tCheckRemoveFileData )
	{
		delete [] this->mFileData;
		this->mFileData = NULL;
	}

	this->mCheckValidState = TRUE;
	return TRUE;
}