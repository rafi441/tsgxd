#include "GXD.h"

BinaryReader* textureReader;
void ClearTextureReader()
{
	if ( textureReader )
	{
		delete textureReader;
		textureReader = NULL;
	}
}

void TEXTURE_FOR_GXD::Init( void )
{
	this->mCheckValidState = FALSE;
}

void TEXTURE_FOR_GXD::Free( void )
{
	this->mCheckValidState = FALSE;
	ClearTextureReader();
}

BOOL TEXTURE_FOR_GXD::Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData )
{
	if( this->mCheckValidState )
		return FALSE;

	this->mFileDataSize = r->ReadInt();
	if( !this->mFileDataSize )
		return TRUE;

	auto z = new ZlibDataPtr( r );
	if ( !Zlib::Decompress( z ) )
	{
		TRACE();
		this->Free();
		return FALSE;
	}

	auto sr = BinaryReader::Scope( __FUNCTION__, z->tOriginal, z->tOriginalSize, 0, false );
	this->mFileData = sr.ReadBytes( this->mFileDataSize );
	this->mProcessModeCase = sr.ReadInt();
	this->mAlphaModeCase = sr.ReadInt();

	TRACE();
	if ( D3DXGetImageInfoFromFileInMemory( this->mFileData, this->mFileDataSize, &this->mTextureInfo ) < 0 )
	{
		this->Free();
		return FALSE;
	}
	TRACE();

	if ( this->mTextureInfo.Format != D3DFMT_DXT1
		&& this->mTextureInfo.Format != D3DFMT_DXT2
		&& this->mTextureInfo.Format != D3DFMT_DXT3
		&& this->mTextureInfo.Format != D3DFMT_DXT5
		|| D3DXCreateTextureFromFileInMemoryEx(
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
			&this->mTexture) >= 0 )
	{
		TRACE();
		//goto LABEL_93;
	}
	TRACE();

	if ( tCheckRemoveFileData )
	{
		delete [] this->mFileData;
		this->mFileData = NULL;
	}

	this->mCheckValidState = TRUE;
	ClearTextureReader();
	return TRUE;
}