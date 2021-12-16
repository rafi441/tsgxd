#ifndef TSGXD_H
#define TSGXD_H

#include "DEFINE.h"

#include "WorldMobjectScale.h"
#include "RenderStateMgr.h"
#include "TextureStageStateMgr.h"

//-------------------------------------------------------------------------------------------------
//DEFINE_GXD_VERSION
//-------------------------------------------------------------------------------------------------
#define GXD_VERSION													"VER2.69"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_MACRO
//-------------------------------------------------------------------------------------------------
#define F_EPSILON													0.0001f
#define FLOAT_EQUAL( a, b )											( ( ( ( b) - F_EPSILON ) < ( a) ) && ( ( a) < ( ( b) + F_EPSILON ) ) )
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_IMAGE_FOR_GXD
//-------------------------------------------------------------------------------------------------
class IMAGE_FOR_GXD
{

private :

	int GetTwoPowerNumber( int tNumber );

public :

	BOOL mCheckValidState;
	D3DXIMAGE_INFO mTextureInfo;
	D3DFORMAT mLoadFormat;
	IDirect3DTexture9 *mTexture;

	IMAGE_FOR_GXD( void );
    ~IMAGE_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadFromTGA( char *tFileName );
	BOOL LoadFromBMP( char *tFileName );
	BOOL LoadFromJPG( char *tFileName );
	BOOL SaveToTGA( char *tFileName );
	BOOL SaveToBMP( char *tFileName );
	BOOL SaveToJPG( char *tFileName );
	BOOL Save( char *tFileName );
	BOOL Load( char *tFileName );
	void Draw( int tX, int tY, BOOL tCheckExistPartInfo, int iX, int iY, int lX, int lY );
	void Draw( int tX, int tY, float tScaleX, float tScaleY );
	void Draw( int tX, int tY, float tScaleX, float tScaleY, BYTE bAlpha );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_TEXTURE_FOR_GXD
//-------------------------------------------------------------------------------------------------
class TEXTURE_FOR_GXD
{
public:

	BOOL mCheckValidState;
	DWORD mFileDataSize;
	BYTE *mFileData;
	D3DXIMAGE_INFO mTextureInfo;
	int mProcessModeCase;
	int mAlphaModeCase;
  int mOrgAlphaModeCase;
	IDirect3DTexture9 *mTexture;

	BOOL CheckTwoPowerNumber( int tNumber );

	void Init( void );
	void Free( void );
 
	BOOL LoadFromTGA( char *tFileName, int tProcessModeCase, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL LoadFromDDS( char *tFileName, int tProcessModeCase, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL SaveToTGA( char *tFileName );
	BOOL SaveToDDS( char *tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL Skip( HANDLE hFile );
	void Create( BOOL tCheckRemoveFileData );
	void Delete( void );

};

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MESHVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT[2];
}
MESHVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MESHEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BOOL mCheckTwoSide;
	BOOL mCheckRadiation;
	float mRadiationSpeed;
	float mRadiationLowLimit[4];
	float mRadiationHighLimit[4];
	BOOL mCheckLightBright;
	BOOL mCheckCameraSpecularEffect;
	int mCameraSpecularEffectSort;
	float mCameraSpecularEffectMaterialValue[4];
	float mCameraSpecularEffectMaterialPower;
	float mCameraSpecularEffectLightAddValue;
	BOOL mCheckTextureAnimation;
	float mTextureAnimationSpeed;
  int m_iStartFrame;
  int m_iEndFrame;
	BOOL mCheckUVScroll1;
	int mUVScrollSort1;
	float mUVScrollSpeed1;
	BOOL mCheckBillboard;
	int mBillboardSort;
	BOOL mCheckUVScroll2;
	int mUVScrollSort2;
	float mUVScrollSpeed2;
}
MESHEFFECT_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MESHSIZE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mAxis[3][3];
	float mExtent[3];
	float mCenter[3];
	float mRadius;
}
MESHSIZE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_BUMPEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
struct BUMPEFFECT_FOR_GXD
{
	DWORD		dwPass;
	float		fAmdPower;
	float		fSpecPower;
	int			iMetrialType;
	BUMPEFFECT_FOR_GXD( )
		:dwPass( 0L),
		fAmdPower( 2.0f),
		fSpecPower( 20.0f),
		iMetrialType( 0)
	{
	}
};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_ONE_MOBJECTINFO_FOR_MULTIDRAW
//-------------------------------------------------------------------------------------------------
typedef struct _ONE_MESHINFO_FOR_MULTIDRAW
{
	D3DXVECTOR3 vCenter;
	FLOAT fRadius;
	BOOL bIsDraw;
	_ONE_MESHINFO_FOR_MULTIDRAW( )
	:fRadius( 0.0f)
	,bIsDraw( TRUE)
	{
		ZeroMemory( &vCenter , sizeof( D3DXVECTOR3) );
	}
}
ONE_MESHINFO_FOR_MULTIDRAW;
typedef ONE_MESHINFO_FOR_MULTIDRAW* LPONE_MESHINFO_FOR_MULTIDRAW; 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_ONE_MOBJECTINFO_FOR_MULTIDRAW
//-------------------------------------------------------------------------------------------------
typedef struct _ONE_MOBJECTINFO_FOR_MULTIDRAW
{
	float fFrame;
	float fPostTimeForEffect;
	float fMaxScaleRate;
	D3DXMATRIX MObjectMat;	
	D3DXMATRIX ScaletMat;	
	D3DXMATRIX RotationMat;	
	D3DXMATRIX TransMat;	
	LPONE_MESHINFO_FOR_MULTIDRAW pMeshInfo;
	_ONE_MOBJECTINFO_FOR_MULTIDRAW( )
	:fFrame( 0.0f)
	,fPostTimeForEffect( 0.0f)
	,fMaxScaleRate( 1.0f)
	,pMeshInfo( NULL)
	{
		D3DXMatrixIdentity( &MObjectMat );
		D3DXMatrixIdentity( &ScaletMat );
		D3DXMatrixIdentity( &RotationMat );
		D3DXMatrixIdentity( &TransMat );
	}
}
ONE_MOBJECTINFO_FOR_MULTIDRAW;
typedef ONE_MOBJECTINFO_FOR_MULTIDRAW* LPONE_MOBJECTINFO_FOR_MULTIDRAW; 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MOBJECTINFO_FOR_MULTIDRAW
//-------------------------------------------------------------------------------------------------
typedef struct _MOBJECTINFO_FOR_MULTIDRAW
{
	WORD wMObjectNum;
	LPONE_MOBJECTINFO_FOR_MULTIDRAW pOneMObjectInfo;
	_MOBJECTINFO_FOR_MULTIDRAW( )
	:wMObjectNum( 0)
	,pOneMObjectInfo( NULL)
	{
	}
}
MOBJECTINFO_FOR_MULTIDRAW;
typedef MOBJECTINFO_FOR_MULTIDRAW* LPMOBJECTINFO_FOR_MULTIDRAW; 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MESH_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MESH_FOR_GXD
{

private :

	MESHVERTEX_FOR_GXD mVertexBufferForBillboard[4];
	MESHSIZE_FOR_GXD *mSize;

public :

	BOOL mCheckValidState;
	MESHEFFECT_FOR_GXD mEffect;
	int mFrameNum;
	int mVertexNum;
	int mUVNum;
	int mTrisNum;
	float *mVertex;
	float *mNormal;
	float *mUV;
	WORD *mTris;
  float* m_fOpacity;   ///< @see G3D_MESH::m_fOpacity.
	IDirect3DVertexBuffer9 *mVertexBuffer;
	IDirect3DIndexBuffer9 *mIndexBuffer;
	TEXTURE_FOR_GXD mTexture[2];
	//--------------------------------------------------------------------------------------------------------------------
	// SkinForGXD에서 범프맵을 추가 하기 위한 변수 추가
	// 2010.03.10 : 김성수
	///< DDS 파일로 부터 heightmap을 읽어서 bumpmap에 사용할 Normalmap을 생성한다.
	TEXTURE_FOR_GXD			mBumpTexture; ///< bumpmapping을 위한 normap 을 저장하기 위한 변수 : 2008.10.21 김성수
	TEXTURE_FOR_GXD			mSpeculerTexture; ///< speculermapping을 위한 normap 을 저장하기 위한 변수 : 2010.05.17 : 김성수
	BOOL					mbIsUseBumpmap; ///< bumpmapping을 사용할지에 대한 여부 : 2008.11.10 김성수
	BOOL					mbIsUseSpeculer; ///< speculermapping을 사용할지에 대한 여부 : 2010.05.17 : 김성수
	BUMPEFFECT_FOR_GXD		mBumpEffect;
	bool					m_bIsViewBumpLight;
	//--------------------------------------------------------------------------------------------------------------------
	int mTextureAnimationNum;
	TEXTURE_FOR_GXD *mTextureAnimation;

	MESH_FOR_GXD( void );
    ~MESH_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadFromG3O( char *tFileName, char *tTextureName );
	BOOL CalculateOneFrameMeshSize( MESHSIZE_FOR_GXD *tSize, int tVertexNum, float *tVertex );
	BOOL ChangeStructureForAcceleration( void );
	BOOL Save( HANDLE hFile, WORD wMajorVersion, WORD wMinorVersion );
	BOOL Load( HANDLE hFile, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData, WORD wMajorVersion, WORD wMinorVersion );
	BOOL ProcessInvertNormal( void );
	BOOL ProcessTwoSide( BOOL tCheckTwoSide );
	BOOL ProcessRadiation( BOOL tCheckRadiation, float tRadiationSpeed, float tRadiationLowLimit[4], float tRadiationHighLimit[4] );
	BOOL ProcessLightBright( BOOL tCheckLightBright );
	BOOL ProcessCameraSpecularEffect( BOOL tCheckCameraSpecularEffect, int tCameraSpecularEffectSort, float tCameraSpecularEffectMaterialValue[4], float tCameraSpecularEffectMaterialPower, float tCameraSpecularEffectLightAddValue );
	BOOL CreateWithBlankTextureAnimation( int tTextureAnimationNum );
	BOOL ProcessTextureAnimation( BOOL tCheckTextureAnimation, float tTextureAnimationSpeed, int iStartFrame, int iEndFrame );
	BOOL ProcessUVScroll1( BOOL tCheckUVScroll1, int tUVScrollSort1, float tUVScrollSpeed1 );
	BOOL ProcessBillboard( BOOL tCheckBillboard, int tBillboardSort );
	BOOL ProcessUVScroll2( BOOL tCheckUVScroll2, int tUVScrollSort2, float tUVScrollSpeed2 );
	void Draw( int tFrame, float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, TEXTURE_FOR_GXD *tNormalTexture, TEXTURE_FOR_GXD *tSpeculerTexture, BOOL tCheckDrawCameraSpecularEffect, BYTE tBlendValue, LPD3DXMATRIX pScaleMat = NULL, LPD3DXMATRIX pRotationMat = NULL, LPD3DXMATRIX pTransMat = NULL );

	//--------------------------------------------------------------------------------------------------------------------
	// MeshForGXD에서 한번에 동일 데이터를 이용하는 MObject를 그리기 위한 함수
	// 2010.12.09 : 김성수
	void MultiDraw( WORD wMeshIndex , LPMOBJECTINFO_FOR_MULTIDRAW MultiDrawInfo, TEXTURE_FOR_GXD *tTexture , TEXTURE_FOR_GXD *tNormalTexture , TEXTURE_FOR_GXD *tSpeculerTexture , BOOL tCheckDrawCameraSpecularEffect );
	//--------------------------------------------------------------------------------------------------------------------

	void DrawForShadow( int tFrame, TEXTURE_FOR_GXD *tTexture );
	void DrawForSelect( int tFrame );
	BOOL LoadGeometryInfo( void );
	void FreeGeometryInfo( void );
	BOOL GetSizeInfo( int tFrameNum, MESHSIZE_FOR_GXD *tResultSize );	/** mSize를 반환하는 함수. */

	//--------//
	//MOBJECT2//
	//--------//
	int mPostVertexNum;
	MESHVERTEX_FOR_GXD *mPostVertexBuffer;
	int mPostTrisNum;
	WORD *mPostIndexBuffer;

	BOOL SaveToMOBJECT2( HANDLE hFile, int tLODStepNum );
	BOOL AdjustDataForLOD( int tPostLODPolygonNum );
	//--------//
	//--------//
	//--------//

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MOBJECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MOBJECT_FOR_GXD
{

private :

	D3DXVECTOR3 mScaleValue;	/** Scaling 정보 */

	float GetMaxScaleValue_( );	/** Scaling 정보( Scale_X, Scale_Y, Scale_Z) 중 가장 큰 값을 반환하는 함수. */

public :

	BOOL mCheckValidState;
  WORD    m_wMajorVersion;
  WORD    m_wMinorVersion;
	int mMeshNum;
	MESH_FOR_GXD *mMesh;
	MESHSIZE_FOR_GXD *mSize;


	MOBJECT_FOR_GXD( void );
    ~MOBJECT_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL CreateWithBlankMesh( int tMeshNum );
	BOOL Save( char *tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData , LPWORD pLoadIndexes , WORD wLoadCount );
	BOOL Load( HANDLE hFile, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, BYTE tBlendValue );

	//--------------------------------------------------------------------------------------------------------------------
	// MeshForGXD에서 한번에 동일 데이터를 이용하는 MObject를 그리기 위한 함수
	// 2010.12.09 : 김성수
	void MultiDraw( int tDrawSort, LPMOBJECTINFO_FOR_MULTIDRAW MultiDrawInfo, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect  );
	//--------------------------------------------------------------------------------------------------------------------

	void DrawForShadow( float tFrame, float tCoord[3], float tAngle[3] );
	void DrawForSelect( int tSelectMeshIndex, float tFrame, float tCoord[3], float tAngle[3] );
	BOOL GetMeshSize( float tFrame, float tCoord[3], float tAngle[3] );

	BOOL TestCameraInMObject( float tFrame, float tCoord[3], float tAngle[3], float tCameraLook[3], float tCameraEye[3] );
	BOOL SetScale( float x, float y, float z );	/** Scaling 정보( mScaleValue) 설정 함수. */
	BOOL GetMeshSizeAfterScale( int tMeshIndex, int tFrameNum, MESHSIZE_FOR_GXD *tResultSize );	/** Scaling 처리를 하기 전의 Mesh Size를 반환하는 함수. */
	BOOL GetMeshSizeBeforeScale( int tMeshIndex, int tFrameNum, MESHSIZE_FOR_GXD *tResultSize );	/** Scaling 처리를 한 후의 Mesh Size를 반환하는 함수. */
	D3DXVECTOR3 GetScaleValue( );				/** 현재 설정된 Scale 값을 반환하는 함수. */

	//--------//
	//MOBJECT2//
	//--------//
	BOOL SaveToMOBJECT2( HANDLE hFile, int tLODStepNum );
	//--------//
	//--------//
	//--------//

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_OF_MOBJECT2
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//STRUCT_OF_MESHEFFECT2_FOR_GXD
typedef struct
{
	int mAnimationMapInfo[4];
	int mRadiationInfo[10];
	int mUVScrollInfo[3];
	int mBillboardInfo[2];
}
MESHEFFECT2_FOR_GXD;
//STRUCT_OF_MESHSIZE2_FOR_GXD
typedef struct
{
	float mBoxMin[3];
	float mBoxMax[3];
	float mCenter[3];
	float mRadius;
}
MESHSIZE2_FOR_GXD;
//STRUCT_OF_MESHVERTEX2_FOR_GXD
typedef struct
{
	float mV[3];
	float mT[2];
}
MESHVERTEX2_FOR_GXD;
//CLASS_OF_MESH2_FOR_GXD
class MESH2_FOR_GXD
{

public :

	BOOL mCheckValidState;
	MESHEFFECT2_FOR_GXD mEffect;
	int mFrameNum;
	MESHSIZE2_FOR_GXD *mSize;
	float *mOpacity;
	MESHVERTEX2_FOR_GXD mVertexBufferForBillboard[4];
	int mLODStepNum;
	int *mVertexNum;
	IDirect3DVertexBuffer9 **mVertexBuffer;
	int *mTrisNum;
	IDirect3DIndexBuffer9 **mIndexBuffer;
	TEXTURE_FOR_GXD mDiffuseMap;
	int mAnimationMapNum;
	TEXTURE_FOR_GXD *mAnimationMap;

	MESH2_FOR_GXD( void );
    ~MESH2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( HANDLE hFile );

	void Draw( int tDrawSort, float tFrame, TEXTURE_FOR_GXD *tDiffuseMap, BYTE tBlendValue, float tPostTimeForEffect, float tLODRatio );

};
//CLASS_OF_MOBJECT2_FOR_GXD
class MOBJECT2_FOR_GXD
{

public :

	BOOL mCheckValidState;
	int mMeshNum;
	MESH2_FOR_GXD *mMesh;

	MOBJECT2_FOR_GXD( void );
    ~MOBJECT2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( char *tFileName );
	BOOL Load( HANDLE hFile );

	void Draw( float tScale[3], float tCoord[3], float tAngle[3], int tDrawSort, float tFrame, TEXTURE_FOR_GXD *tDiffuseMap, BYTE tBlendValue, float tPostTimeForEffect );

	BOOL TestSegmentInMObject( float tScale[3], float tCoord[3], float tAngle[3], float tFrame, float tSCoord[3], float tECoord[3] );

};
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_MOTION_FOR_GXD
//-------------------------------------------------------------------------------------------------
class MOTION_FOR_GXD
{
public:

	BOOL mCheckValidState;
	int mFrameNum;
	int mBoneNum;
	std::vector<D3DXMATRIX> mKeyMatrix;

	void Init( void );
	void Free( void );

	BOOL LoadFromG3M( char *tFileName, int tLoadSort );
	BOOL Save( char *tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( char *tFileName );
	BOOL Load( BinaryReader* r );

	BOOL SaveToMOTION2( char *tFileName );

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_OF_MOTION2
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//CLASS_OF_MOTION2_FOR_GXD
class MOTION2_FOR_GXD
{

public :

	BOOL mCheckValidState;
	int mFrameNum;
	int mBoneNum;
	D3DXMATRIX *mKeyMatrix;

	MOTION2_FOR_GXD( void );
    ~MOTION2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( char *tFileName );

};
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT[2];
}
SKINVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINWEIGHT_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mBoneIndex[4];
	float mBlendValue[4];
}
SKINWEIGHT_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BOOL mCheckTwoSide;
	BOOL mCheckRadiation;
	float mRadiationSpeed;
	float mRadiationLowLimit[4];
	float mRadiationHighLimit[4];
	BOOL mCheckLightBright;
	BOOL mCheckCameraSpecularEffect;
	int mCameraSpecularEffectSort;
	float mCameraSpecularEffectMaterialValue[4];
	float mCameraSpecularEffectMaterialPower;
	float mCameraSpecularEffectLightAddValue;
	BOOL mCheckTextureAnimation;
	float mTextureAnimationSpeed;
	BOOL mCheckUVScroll1;
	int mUVScrollSort1;
	float mUVScrollSpeed1;
	BOOL mCheckBillboard;
	int mBillboardSort;
	BOOL mCheckUVScroll2;
	int mUVScrollSort2;
	float mUVScrollSpeed2;
}
SKINEFFECT_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINSIZE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mBoxMin[3];
	float mBoxMax[3];
	float mCenter[3];
	float mRadius;
}
SKINSIZE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKINLODVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT[2];
	float mBoneIndex[4];
	float mBlendValue[4];
}
SKINLODVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

typedef struct SKININDEX_FOR_GXD
{
	WORD mFace[3];
} SKININDEX_FOR_GXD;

typedef struct VERTEX
{
	float mV[3];
	VERTEX( float* v )
	{
		mV[0] = v[0];
		mV[1] = v[1];
		mV[2] = v[2];
	}
} VERTEX;


//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_SKIN_FOR_GXD
//-------------------------------------------------------------------------------------------------
class SKIN_FOR_GXD
{

private :

	SKINVERTEX_FOR_GXD mVertexBufferForBillboard[4];

	BOOL mCheckChangeNormalState;
	SKINSIZE_FOR_GXD mSize;

public :
	D3DXVECTOR3 mScaleValue;		/** Scale 값. */
	std::vector<D3DXMATRIX> mScaleKeyMatrix;

	BOOL mCheckValidState;
	SKINEFFECT_FOR_GXD mEffect;
	int mVertexNum;
	int mUVNum;
	int mWeightNum;
	int mTrisNum;
	float *mVertex;
	float *mNormal;
	float *mUV;
	float *mWeight;
	WORD *mTris;
	std::vector<SKINVERTEX_FOR_GXD> mVertexBuffer;
	std::vector<SKINWEIGHT_FOR_GXD> mWeightBuffer;
	std::vector<SKININDEX_FOR_GXD> mIndexBuffer;
	std::vector<VERTEX> mMotionVertex;
	std::vector<VERTEX> mMotionNormal;
	TEXTURE_FOR_GXD mTexture[2];
	int mTextureAnimationNum;
	TEXTURE_FOR_GXD *mTextureAnimation;
  DWORD    m_dwDyeingColor;

	//--------------------------------------------------------------------------------------------------------------------
	// SkinForGXD에서 범프맵을 추가 하기 위한 변수 추가
	// 2010.03.10 : 김성수
	///< DDS 파일로 부터 heightmap을 읽어서 bumpmap에 사용할 Normalmap을 생성한다.
	TEXTURE_FOR_GXD			mBumpTexture; ///< bumpmapping을 위한 normap 을 저장하기 위한 변수 : 2008.10.21 김성수
	TEXTURE_FOR_GXD			mSpeculerTexture; ///< speculermapping을 위한 normap 을 저장하기 위한 변수 : 2010.05.17 : 김성수
	BOOL					mbIsUseBumpmap; ///< bumpmapping을 사용할지에 대한 여부 : 2008.11.10 김성수
	BOOL					mbIsUseSpeculer; ///< speculermapping을 사용할지에 대한 여부 : 2010.05.17 : 김성수
	BUMPEFFECT_FOR_GXD		mBumpEffect;
	bool					m_bIsViewBumpLight;
	//--------------------------------------------------------------------------------------------------------------------

	void Init( void );
	void Free( void );
	
	BOOL LoadFromG3S( char *tFileName, char *tTextureName );
	BOOL ChangeStructureForAcceleration( void );
	BOOL Save( HANDLE hFile );
	BOOL Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void CreateTexture( BOOL tCheckRemoveFileData );
	void DeleteTexture( void );
	BOOL ProcessInvertNormal( void );
	BOOL ProcessTwoSide( BOOL tCheckTwoSide );
	BOOL ProcessRadiation( BOOL tCheckRadiation, float tRadiationSpeed, float tRadiationLowLimit[4], float tRadiationHighLimit[4] );
	BOOL ProcessLightBright( BOOL tCheckLightBright );
	BOOL ProcessCameraSpecularEffect( BOOL tCheckCameraSpecularEffect, int tCameraSpecularEffectSort, float tCameraSpecularEffectMaterialValue[4], float tCameraSpecularEffectMaterialPower, float tCameraSpecularEffectLightAddValue );
	BOOL CreateWithBlankTextureAnimation( int tTextureAnimationNum );
	BOOL ProcessTextureAnimation( BOOL tCheckTextureAnimation, float tTextureAnimationSpeed );
	BOOL ProcessUVScroll1( BOOL tCheckUVScroll1, int tUVScrollSort1, float tUVScrollSpeed1 );
	BOOL ProcessBillboard( BOOL tCheckBillboard, int tBillboardSort );
	BOOL ProcessUVScroll2( BOOL tCheckUVScroll2, int tUVScrollSort2, float tUVScrollSpeed2 );
	
	void ReadyForDraw( int tFrame, MOTION_FOR_GXD *tMotion, BOOL tCheckCalculateNormal );
	void Draw( float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, TEXTURE_FOR_GXD *tNormalTexture, TEXTURE_FOR_GXD *tSpeculerTexture, BOOL tCheckDrawCameraSpecularEffect );
	void DrawForSelect( void );
	
	void GetCenterCoord( float tCoord[3] );
	BOOL SetScale( float x, float y, float z );			/** Scaling 정보( mScaleValue) 설정 함수. */
	D3DXVECTOR3 GetScaleValue( );						/** Scaling 값을 반환하는 함수. */
	BOOL GetBBoxInfo( SKINSIZE_FOR_GXD *tResultSize );	/** Scaling이 적용된 Bounding Box 정보를 반환하는 함수. */

	//--------//
	//SOBJECT2//
	//--------//
	int mPostVertexNum;
	SKINVERTEX_FOR_GXD *mPostVertexBuffer;
	SKINWEIGHT_FOR_GXD *mPostWeightBuffer;
	int mPostTrisNum;
	WORD *mPostIndexBuffer;

	BOOL SaveToSOBJECT2( HANDLE hFile, int tLODStepNum );
	BOOL AdjustDataForLOD( int tPostLODPolygonNum );
};

class SOBJECT_FOR_GXD
{
public:
	BOOL mCheckValidState;
	int mSkinNum;
	std::vector<SKIN_FOR_GXD> mSkin;

	void Init( void );
	void Free( void );

	BOOL CreateWithBlankSkin( int tSkinNum );
	BOOL Save( char *tFileName );
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void CreateTexture( BOOL tCheckRemoveFileData );
	void DeleteTexture( void );

	#ifdef __TROY__
	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, MOTION_FOR_GXD *tMotion, float tRangeForCulling, BOOL tCheckShadow, void *tWorld, BOOL tCheckCalculateNormal , float tValidShadowLength , BOOL tPortrait = FALSE, FLOAT tYPos = 0.0f );
	#else
	void Draw( int tDrawSort, float tFrame, float tCoord[3], float tAngle[3], float tPostTimeForEffect, TEXTURE_FOR_GXD *tTexture, BOOL tCheckDrawCameraSpecularEffect, MOTION_FOR_GXD *tMotion, float tRangeForCulling, BOOL tCheckShadow, void *tWorld, BOOL tCheckCalculateNormal, float tValidShadowLength );
	#endif
	void DrawForSelect( int tSelectSkinIndex, float tFrame, float tCoord[3], float tAngle[3], MOTION_FOR_GXD *tMotion, float tRangeForCulling );

	void GetSkinCoord( int tSelectSkinIndex, float tFrame, float tCoord[3], float tAngle[3], MOTION_FOR_GXD *tMotion, float tSkinCoord[3] );
	BOOL SetScale( float x, float y, float z );

	//--------//
	//SOBJECT2//
	//--------//
	BOOL SaveToSOBJECT2( char *tFileName, int tLODStepNum );
	//--------//
	//--------//
	//--------//
	void TestDraw( MOTION_FOR_GXD* tMotion, int tFrameNum );
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_OF_SOBJECT2
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//STRUCT_OF_SKINEFFECT2_FOR_GXD
typedef struct
{
	int mAnimationMapInfo[2];
	int mRadiationInfo[10];
	int mBillboardInfo[2];
}
SKINEFFECT2_FOR_GXD;
//STRUCT_OF_SKINSIZE2_FOR_GXD
typedef struct
{
	float mBoxSize[3];
}
SKINSIZE2_FOR_GXD;
//STRUCT_OF_SKINVERTEX2_FOR_GXD
typedef struct
{
	float mV[3];
	float mW[4];
	DWORD mB;
	float mN1[3];
	float mN2[3];
	float mN3[3];
	float mT[2];
}
SKINVERTEX2_FOR_GXD;
//STRUCT_OF_SKINSHADOWVERTEX2_FOR_GXD
typedef struct
{
	float mV[3];
	float mW[4];
	DWORD mB;
}
SKINSHADOWVERTEX2_FOR_GXD;
//STRUCT_OF_DRAWSHADOWVERTEX_FOR_GXD
typedef struct
{
	float mV[3];
}
DRAWSHADOWVERTEX_FOR_GXD;
//CLASS_OF_SKIN2_FOR_GXD
class SKIN2_FOR_GXD
{

private :

	void Transform( int tTransformSort, float tCoord[3], D3DXMATRIX *tMatrix, float tResult[3] );

public :

	BOOL mCheckValidState;
	SKINEFFECT2_FOR_GXD mEffect;
	SKINSIZE2_FOR_GXD mSize;
	SKINVERTEX2_FOR_GXD mVertexBufferForBillboard[4];
	int mLODStepNum;
	int *mVertexNum;
	IDirect3DVertexBuffer9 **mVertexBuffer;
	int *mTrisNum;
	IDirect3DIndexBuffer9 **mIndexBuffer;
	SKINSHADOWVERTEX2_FOR_GXD **mShadowVertexBuffer;
	WORD **mShadowIndexBuffer;
	WORD **mShadowEdgeBuffer;
	TEXTURE_FOR_GXD mDiffuseMap;
	TEXTURE_FOR_GXD mNormalMap;
	TEXTURE_FOR_GXD mSpecularMap;
	int mAnimationMapNum;
	TEXTURE_FOR_GXD *mAnimationMap;

	SKIN2_FOR_GXD( void );
    ~SKIN2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( HANDLE hFile );

	void Draw( int tDrawSort, MOTION2_FOR_GXD *tMotion, float tFrame, TEXTURE_FOR_GXD *tDiffuseMap, TEXTURE_FOR_GXD *tNormalMap, TEXTURE_FOR_GXD *tSpecularMap, float tLODRatio );

	void CalculateShadowVolume( MOTION2_FOR_GXD *tMotion, float tFrame, float tLightDirection[3], float tLODRatio, float tValidShadowLength );

};
//CLASS_OF_SOBJECT2_FOR_GXD
class SOBJECT2_FOR_GXD
{

private :

	void Transform( int tTransformSort, float tCoord[3], D3DXMATRIX *tMatrix, float tResult[3] );

public :

	BOOL mCheckValidState;
	int mSkinNum;
	SKIN2_FOR_GXD *mSkin;

	SOBJECT2_FOR_GXD( void );
    ~SOBJECT2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Load( char *tFileName );

	void Draw( float tValidObjectLength, float tScale[3], float tCoord[3], float tAngle[3], int tDrawSort, MOTION2_FOR_GXD *tMotion, float tFrame, TEXTURE_FOR_GXD *tDiffuseMap, TEXTURE_FOR_GXD *tNormalMap, TEXTURE_FOR_GXD *tSpecularMap );
	void DrawForHighShadow( float tValidObjectLength, float tScale[3], float tCoord[3], float tAngle[3], MOTION2_FOR_GXD *tMotion, float tFrame, void *tWorld, float tValidShadowLength );
	void DrawForLowShadow( float tValidObjectLength, float tScale[3], float tCoord[3], float tAngle[3], MOTION2_FOR_GXD *tMotion, float tFrame, void *tWorld, float tValidShadowLength );

	void GetSkinCoord( int tSkinIndex, float tScale[3], float tCoord[3], float tAngle[3], MOTION2_FOR_GXD *tMotion, float tFrame, float tResult[3] );

};
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_PARTICLEVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	DWORD mC;
	float mT[2];
}
PARTICLEVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_PARTICLE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	BOOL mCheckValidState;
	float mOneLifeTime;
	float mLocation[3];
	float mVelocity[3];
	float mWeight;
	float mSize;
	float mColor[4];
}
PARTICLE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_PSYSTEM_FOR_GXD
//-------------------------------------------------------------------------------------------------
class PSYSTEM_FOR_GXD
{

public:

	BOOL mCheckValidState;
	TEXTURE_FOR_GXD mTexture;
	MOTION_FOR_GXD mMotion;
	float mTotalLifeTime;
	float mFrameRatio;
	float mEmitRate;
	float mEmitSort;
	float mEmitRadius;
	float mEmitRange[3];
	float mOneLifeTime;
	float mMinRandomVelocity[3];
	float mMaxRandomVelocity[3];
	float mWeight;
	float mSize;
	float mMinColor[4];
	float mMaxColor[4];
	float mMainForce[3];
	float mMinRandomForce[3];
	float mMaxRandomForce[3];
	float mWeightDelta;
	float mSizeDelta;
	float mColorDelta[4];
	
	bool Read( BinaryReader* r );
	PSYSTEM_FOR_GXD( void );
	~PSYSTEM_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Save( char* tFileName );
	BOOL Save( HANDLE hFile );
	BOOL Load( char* tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL Load( BinaryReader* r, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void Adjust( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_POBJECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
class POBJECT_FOR_GXD
{
private :
	D3DXVECTOR3 mScaleValue;

public :

	BOOL mCheckValidState;
	PSYSTEM_FOR_GXD *mPSystem;
	float mTotalLifeTime;
	float mCoord[3];
	float mAngle[3];
	float mEmitParticleNum;
	int mMaxParticleNum;
	std::vector<PARTICLE_FOR_GXD> mParticle;
	
	POBJECT_FOR_GXD( void );
    ~POBJECT_FOR_GXD( void );

	void Init( void );
	void Free( void );

	void Set( PSYSTEM_FOR_GXD *tPSystem );
	void Update( float tTime, float tCoord[3], float tAngle[3] );
	void Draw( void );

	const D3DXVECTOR3& GetScale( ) const;
	BOOL SetScale( float x, float y, float z );
};
//-------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//CLASS_OF_EFFECT_FOR_GXD
//-----------------------------------------------------------------------------------------------
#define DEF_SIZE_BUFFER												64
#define DEF_LEN_FILE_NAME											256
struct EF_NEXTNODE
{
	int m_iSkinCoord;
	float m_fTime;
	float m_fPos[3];
	POBJECT_FOR_GXD* m_pPObject;
	EF_NEXTNODE( int iSkinCoord = 0, float fTime = 1.0f)
	{
		m_iSkinCoord = iSkinCoord;
		m_fTime = fTime;
		m_fPos[0] = 0;
		m_fPos[1] = 0;
		m_fPos[2] = 0;
		m_pPObject = NULL;
	}
	bool Load( HANDLE hFile );
	bool Save( HANDLE hFile );
};
struct EF_ALPHAKEY
{
	float m_fKeyFrame;
	BYTE m_byteALPHA;
	EF_ALPHAKEY( float fKeyFrame = 0, BYTE byteALPHA = 0)
	{
		Set( fKeyFrame, byteALPHA );
	}
	void Set( float fKeyFrame, BYTE byteALPHA)
	{
		m_fKeyFrame = fKeyFrame;
		m_byteALPHA = byteALPHA;
	}
};
class EFFECTGROUP_FOR_GXD;
class EFFECT_FOR_GXD
{
private:
	int mMObjectSort;

public:
	EFFECT_FOR_GXD( void );
	virtual ~EFFECT_FOR_GXD( void );
	inline PSYSTEM_FOR_GXD* GetSystemPtr( void)
	{
		return m_pSystem;
	}
	inline POBJECT_FOR_GXD* GetObjectPtr( void)
	{
		return m_pPObject;
	}
	inline float* GetPos( void)
	{
		return m_fPos;
	}
	void SetTexturePath( char* pPath)
	{
		m_TextureName = pPath;
	}
	bool Init( );
	bool Free( );
	bool Load( HANDLE hFile, int tMObjectSort, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	bool Save( HANDLE hFile );
	BOOL SaveToEFFECT2( HANDLE hFile, int tLODStepNum );
	void Update( SOBJECT_FOR_GXD* pSObjectDummy, MOTION_FOR_GXD* pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void Update2( SOBJECT2_FOR_GXD* pSObjectDummy, MOTION2_FOR_GXD* pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void DrawMObject( int iSort );
	void DrawPObject( );
	void ReStart( );
	void Stop( bool bIsAfterVisible = false );
	bool AddKeyFrame( float fKey );
	void DelKeyFrame( int ixVecter );
	static bool CompAlphaKey( const EF_ALPHAKEY& alphaKeyLeft, const EF_ALPHAKEY& alphaKeyRight );
	BYTE GetAlpha( int ixVector );
	void EditAlpha( int ixVector, int iAlpha );
	void CalcDrawAlphaVector( );
	void SkinCoordScale( float fPos[3], float fSkinCoord[3], float fScale[3] );
	void SetName( std::string strName )
	{
		m_Name = strName;
	}
	void SetMoveType( int iMoveType );
	void SetMoveType2( int iMoveType2 );
	void SetMobjectRepeat( bool bRepeat)
	{
		m_bMObjectRepeat = bRepeat;
	}
	void InitializeSystem( void );
	void AllClear( );
	bool ReAllocTempNode( );
	void ReCalcTotlaMoveTime( );
	void ReSetVectorSystem( );
	void ParticleUpdateUseScale( POBJECT_FOR_GXD* pPObject, float fElapsedTime, float fPos[3], float fAng[3], float fScale[3] );
	void IncMObject( float fDiffTime );
	void NewParticle( );
	bool NewMOBJECT( char achPath[] );
	void AddNode( int ixSkinCoord );
	void RemoveNode( int ixSkinCoord );
	void SetMoveTime( int ixNode, float fMoveTime );
	int GetChkCount( );
	int GetMoveType( );
	float GetTotalMoveTime( );
	bool CopyFrom( EFFECT_FOR_GXD* pEffect );

	float m_fPosBase[3];
	bool m_bMObjectRepeat;
	int m_aiMoveType[2];
	int m_iCountInterObject;
	float m_fStartFrame;
	float m_fLifeFrame;
	float m_fTotalMoveTimeOrg;
	PSYSTEM_FOR_GXD* m_pSystem;
	MOBJECT_FOR_GXD* m_pMobject;
	MOBJECT2_FOR_GXD* m_pMobject2;
	std::string m_Name;
	std::vector<EF_NEXTNODE> m_vectorNextNode;
	std::vector<EF_ALPHAKEY> m_vectorMObjectAlPha;
	int m_iIsStopAndVisible;
	bool m_bIsCopy;
	float m_fPos[3];
	float m_fAng[3];
	float m_fScale[3];
	std::string m_TextureName;
	float m_fFrame;
	float m_fNowTime;
	float m_fNowInterTime;
	int m_iNowIndex;
	int m_iDirectionRotateMove;
	bool m_bDrawMObject;
	bool m_bDrawPObject;
	bool m_bEndTime;
	float m_fTotalMoveTime;
	POBJECT_FOR_GXD* m_pPObject;
	std::vector<EF_NEXTNODE> m_vectorTempNode;
	std::vector<BYTE> m_vectorMObjectDrawAlpha;
};
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//CLASS_OF_GEFFECTGROUP
//-----------------------------------------------------------------------------------------------
class EFFECTGROUP_FOR_GXD
{
private:
	int mMObjectSort;

public:
	bool mCheckValidState;
	EFFECTGROUP_FOR_GXD( );
	virtual ~EFFECTGROUP_FOR_GXD( );
	bool Init( );
	bool Free( );
	bool Load( char* tFileName, int tMObjectSort, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	bool Load( HANDLE hFile, int tMObjectSort, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void Update( SOBJECT_FOR_GXD* pSObjectDummy, MOTION_FOR_GXD* pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void Update2( SOBJECT2_FOR_GXD* pSObjectDummy, MOTION2_FOR_GXD* pMotionDummy, float fScale[3], float fFrame, float fPos[3], float tFront, float fElapsedTime );
	void DrawMObject( int iSort );
	void DrawPObject( );
	void ReStart( );
	void Stop( bool bIsAfterVisible = false );
	BOOL CopyFrom( EFFECTGROUP_FOR_GXD* pEffectGroup );
	BOOL CheckCollisionForMouseMS( int tX, int tY );
	EFFECT_FOR_GXD* GetGAttachObject( unsigned int index );
	int GetCount( );
	bool IsEnd( );
	BOOL Load( );
	bool Save( char* tFileName );
	bool Save( HANDLE hFile );
	BOOL SaveToEFFECT2( char* tFileName, int tLODStepNum );

	char mFileName[DEF_LEN_FILE_NAME];
	float mLastUsedTime;
	std::vector<EFFECT_FOR_GXD*> m_vecterAttachObject;
	const int m_iVersionEffect;

private:
	BOOL m_bCreateTexture;
	BOOL m_bRemoveFileData;
};
//-----------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_SKYBOXVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mT[2];
}
SKYBOXVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_LENSFLAREVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[4];
	float mT[2];
}
LENSFLAREVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_SKY_FOR_GXD
//-------------------------------------------------------------------------------------------------
class SKY_FOR_GXD
{

public:

	BOOL mCheckValidState;
	TEXTURE_FOR_GXD mTextureForSkyBox[6];
	float mLensFlareShapeRatio;
	TEXTURE_FOR_GXD mTextureForLensFlare[10];
	float mPostFarPlane;
	SKYBOXVERTEX_FOR_GXD mSkyBoxVertexBuffer[24];
	LENSFLAREVERTEX_FOR_GXD mLensFlareVertexBuffer[4];

	SKY_FOR_GXD( void );
	~SKY_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL Save( char* tFileName );
	BOOL Load( char* tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void DrawForSkyBox( void );
	void DrawForLensFlare( void* tWorld );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_WORLDVERTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mV[3];
	float mN[3];
	float mT1[2];
	float mT2[2];
}
WORLDVERTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF__WORLDINTEX_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct _WORLDINTEX_FOR_GXD
{
	DWORD w1, w2, w3;
	_WORLDINTEX_FOR_GXD( )
		:w1( 0), w2( 0), w3( 0)
	{
	}
}
WORLDINTEX_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_G3WTRIS_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mTextureIndex;
	int mVertexIndex[3];
	int mUVIndex[3];
}
G3WTRIS_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_G3WMESH_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	char mName[256];
	int mVertexNum;
	int mUVNum;
	int mTrisNum;
	float *mVertex;
	float *mUV;
	G3WTRIS_FOR_GXD *mTris;
}
G3WMESH_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_WORLDTRIS_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mTextureIndex;
	WORLDVERTEX_FOR_GXD mVertex[3];
	float mPlaneInfo[4];
	float mSphereInfo[4];
}
WORLDTRIS_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_QUADTREENODE_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	float mBoxMin[3];
	float mBoxMax[3];
	int mTrisNum;
	int *mTrisIndex;
	int mChildNodeIndex[4];
}
QUADTREENODE_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_MOBJECTINFO_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mIndex;
	float mCoord[3];
	float mAngle[3];
	float mFrame;
	float mPostTimeForEffect;
}
MOBJECTINFO_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_POBJECTINFO_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef struct
{
	int mIndex;
	float mCoord[3];
	float mAngle[3];
	POBJECT_FOR_GXD mParticle;
}
POBJECTINFO_FOR_GXD;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_WORLD_FVF
//-------------------------------------------------------------------------------------------------
const static DWORD WORLD_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_WORLD_FOR_GXD
//-------------------------------------------------------------------------------------------------
class WORLD_FOR_GXD
{

private :

	int mWaterWaveTextureSize;

	BOOL GetXCoordWithTris( int tTrisIndex, float y, float z, float *x );
	BOOL GetYCoordWithTris( int tTrisIndex, float x, float z, float *y );
	BOOL GetZCoordWithTris( int tTrisIndex, float x, float y, float *z );
	BOOL CheckPointInTris( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInTrisWithoutYCoord( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInWorldWithoutYCoord( float tPoint[3] );
	BOOL CheckRayInTris( int tTrisIndex, float tQ[3], float tV[3], float tCoord[3], BOOL tCheckTwoSide );
	BOOL CheckSegmentInTris( int tTrisIndex, float tQ[3], float tV[3], float tCoord[3], BOOL tCheckTwoSide );

	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9*		m_ppIndexBuffer;	

	LPDWORD						m_dwpIndexNumOfTexture;

	//2010.12.09 : 김성수 : MObject 일괄 랜더링을 위한 정보 변수
	LPMOBJECTINFO_FOR_MULTIDRAW		m_MObjectMultiInfo;

	// WO파일에 있는 MObject 들의 스케일 값을 저장할 클래스
	CWorldMobjectScale m_MObjectScale;

	float GetMinXWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMinYWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMinZWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMaxXWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMaxYWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );
	float GetMaxZWithWorldTris( WORLDTRIS_FOR_GXD *tWorldTris );

public :

	BOOL mCheckValidState;
	int mLoadSort;
	int mTextureNum;
	TEXTURE_FOR_GXD *mTexture;
	IDirect3DTexture9 *mWaterWaveTexture;
	TEXTURE_FOR_GXD mShadowTexture;
	int mG3WMeshNum;
	G3WMESH_FOR_GXD *mG3WMesh;
	int mWorldTrisNum;
	WORLDTRIS_FOR_GXD *mWorldTris;
	int mMObjectNum;
	MOBJECT_FOR_GXD *mMObject;
	char *mMObjectFileName;
	int mMObjectInfoNum;
	MOBJECTINFO_FOR_GXD *mMObjectInfo;
	int mPSystemNum;
	PSYSTEM_FOR_GXD *mPSystem;
	char *mPSystemFileName;
	int mPObjectInfoNum;
	POBJECTINFO_FOR_GXD *mPObjectInfo;
	int mTotalQuadtreeNodeNum;
	int mMaxQuadtreeNodeLeafNum;
	QUADTREENODE_FOR_GXD *mQuadtree;
	int *mTextureTrisPostIndex;
	int mSaveDrawQuadtreeNodeNum;
	int *mSaveDrawQuadtreeNodeIndex;
	int *mSaveDrawWorldTrisFlag;

	WORLD_FOR_GXD( void );
    ~WORLD_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadFromG3W( char *tFileName );
	BOOL CreateQuadtree( void );
	BOOL RecursionForCreateQuadtree( int tParentNodeIndex, int tChildNodeSortIndex, int tMaxQuadtreeDepth, int tPresentQuadtreeDepth );

	BOOL SaveWG( char *tFileName );
	BOOL SaveWG2( char *tFileName );
	BOOL SaveWM( char *tFileName );
	BOOL SaveWM2( char *tFileName );
	BOOL SaveWO( char *tFileName );
	BOOL SaveWO2( char *tFileName, int tLODStepNum );
	BOOL SaveWP( char *tFileName );
	BOOL SaveWP2( char *tFileName );

	BOOL LoadWG( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	BOOL LoadWM( char *tFileName );
	BOOL LoadWO( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );

	//-----------------------//
	//월드내 스케일 정보 관련//
	//-----------------------//
	BOOL LoadWS( char *tFileName );
	BOOL SaveWS( char *tFileName );
	BOOL InitWS(  );
	BOOL InsertMObjectScale( );
	BOOL SetMObjectScale( WORD wIndex , FLOAT fRate );
	VOID ClearLastScaleRate( )
	{
		m_MObjectScale.ClearLastScaleRate( );
		return;
	}
	const FLOAT GetScaleRateX( WORD wIndex)
	{
		return m_MObjectScale.GetScaleRateX( wIndex );
	}
	const FLOAT GetScaleRateY( WORD wIndex)
	{
		return m_MObjectScale.GetScaleRateY( wIndex );
	}
	const FLOAT GetScaleRateZ( WORD wIndex)
	{
		return m_MObjectScale.GetScaleRateZ( wIndex );
	}
	const FLOAT GetLastScaleRateX( )
	{
		return m_MObjectScale.GetLastScaleRateX( );
	}
	const FLOAT GetLastScaleRateY( )
	{
		return m_MObjectScale.GetLastScaleRateY( );
	}
	const FLOAT GetLastScaleRateZ( )
	{
		return m_MObjectScale.GetLastScaleRateZ( );
	}
	//-----------------------//
	//-----------------------//
	//-----------------------//

	void FreeMObjectInfo( void );
	BOOL LoadWP( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData );
	void FreePObjectInfo( void );
	void Update( float tFrameRatio, float tTime );
	void Draw( int tDrawSort, BOOL tCheckDrawWaterEffect, float tWaterEffectValue, BOOL tCheckDrawCameraSpecularEffect, float tPostLimitCoord[3], float tPostLimitLength, float tPostLengthRatioForBlendValue );
	void RecursionForDraw( int tParentNodeIndex );
	void DrawWithWM( void );
	void RecursionForDrawWithWM( int tParentNodeIndex );
	BOOL MakeWaterWaveTexture( void );
	BOOL MakeShadowTexture( char *tFileName );

	BOOL ScreenCoordToWorldCoord( int tX, int tY, int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForScreenCoordToWorldCoord( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL TestRayInWorld( float tSCoord[3], float tECoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForTestRayInWorld( int tParentNodeIndex, float tQ[3], float tV[3], BOOL tCheckTwoSide );
	BOOL FindRayInWorld( float tSCoord[3], float tECoord[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForFindRayInWorld( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL TestSegmentInWorld( float tSCoord[3], float tECoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForTestSegmentInWorld( int tParentNodeIndex, float tQ[3], float tV[3], BOOL tCheckTwoSide );
	BOOL FindSegmentInWorld( float tSCoord[3], float tECoord[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );
	BOOL RecursionForFindSegmentInWorld( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tCoord[3], BOOL tCheckTwoSide );

	BOOL FindCameraInWorld( float tCameraLook[3], float tCameraEye[3], float tCameraRadius, float tCameraCoord[3] );
	BOOL RecursionForFindCameraInWorld( int tParentNodeIndex, float tCameraLook[3], float tCameraEye[3], float tCameraRadius, float tCameraCoord[3] );
	BOOL TestCameraInWorldMObject( float tCameraLook[3], float tCameraEye[3] );

	BOOL GetYCoord( float x, float z, float *y, BOOL tCheckExistPostYCoord, float tPostYCoord, BOOL tCheckTwoSide, BOOL tCheckOnlyOne );
	void Path( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, float tResult[3] );
	BOOL Move( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, BOOL *tCheckArrival );
  BOOL Move2 ( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, BOOL *tCheckArrival );

private:
  bool  SetUpAtlasUV ( D3DXMATRIX& viewmatrix, D3DXMATRIX& projmatrix );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//DEFINITION_OF_WORLD2
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//CLASS_OF_WORLD2_FOR_GXD
class WORLD2_FOR_GXD
{

private :

	BOOL CheckPointInTris( int tTrisIndex, float tPoint[3] );
	BOOL CheckPointInTrisWithoutYCoord( int tTrisIndex, float tPoint[3] );
	BOOL CheckRayInTris( int tTrisIndex, float tQ[3], float tV[3], float tResult[3] );
	BOOL CheckSegmentInTris( int tTrisIndex, float tQ[3], float tV[3], float tResult[3] );

public :

	BOOL mCheckValidState;
	int mLoadSort;
	int mTextureNum;
	TEXTURE_FOR_GXD *mTexture;
	int *mVertexNumForTexture;
	float *mBoxMinForTexture;
	float *mBoxMaxForTexture;
	IDirect3DVertexBuffer9 **mVertexBufferForTexture;
	IDirect3DTexture9 *mWaterWaveTexture;
	int mMObjectNum;
	MOBJECT2_FOR_GXD *mMObject;
	int mMObjectInfoNum;
	MOBJECTINFO_FOR_GXD *mMObjectInfo;
	int mMObjectNum2;
	MOBJECT2_FOR_GXD *mMObject2;
	int mMObjectInfoNum2;
	MOBJECTINFO_FOR_GXD *mMObjectInfo2;
	int mPSystemNum;
	PSYSTEM_FOR_GXD *mPSystem;
	int mPObjectInfoNum;
	POBJECTINFO_FOR_GXD *mPObjectInfo;
	int mPSystemNum2;
	PSYSTEM_FOR_GXD *mPSystem2;
	int mPObjectInfoNum2;
	POBJECTINFO_FOR_GXD *mPObjectInfo2;
	TEXTURE_FOR_GXD mShadowTexture;
	int mWorldTrisNum;
	WORLDTRIS_FOR_GXD *mWorldTris;
	int mTotalQuadtreeNodeNum;
	int mMaxQuadtreeNodeLeafNum;
	QUADTREENODE_FOR_GXD *mQuadtree;

	WORLD2_FOR_GXD( void );
    ~WORLD2_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadWG( char *tFileName );
	void MakeWaterWaveTexture( void );
	BOOL LoadWO( char *tFileName );
	void FreeMObjectInfo( void );
	BOOL LoadWO2( char *tFileName );
	void FreeMObjectInfo2( void );
	BOOL LoadWP( char *tFileName );
	void FreePObjectInfo( void );
	BOOL LoadWP2( char *tFileName );
	void FreePObjectInfo2( void );
	BOOL LoadWM( char *tFileName );

	void Update( float tFrameRatio, float tTime );

	void Draw( int tDrawSort, float tPostLimitCoord[3], float tPostLimitLength, float tPostLengthRatioForBlendValue );

	BOOL GetYCoord( float x, float z, float *y );

	BOOL ScreenCoordToWorldCoord( int tX, int tY, int *tTrisIndex, float tResult[3] );
	BOOL RecursionForScreenCoordToWorldCoord( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tResult[3] );
	BOOL TestPointInWorld( float tPoint[3] );
	BOOL TestPointInWorldWithoutYCoord( float tPoint[3] );
	BOOL FindRayInWorld( float tSCoord[3], float tECoord[3], int *tTrisIndex, float tResult[3] );
	BOOL RecursionForFindRayInWorld( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tResult[3] );
	BOOL FindSegmentInWorld( float tSCoord[3], float tECoord[3], int *tTrisIndex, float tResult[3] );
	BOOL RecursionForFindSegmentInWorld( int tParentNodeIndex, float tQ[3], float tV[3], int *tTrisIndex, float tResult[3] );
	BOOL TestBoxInWorld( float tBoxMin[3], float tBoxMax[3] );
	BOOL RecursionForTestBoxInWorld( int tParentNodeIndex, float tBoxMin[3], float tBoxMax[3] );
	BOOL TestSegmentInWorldMObject( float tSCoord[3], float tECoord[3] );
	BOOL FindCameraInWorld( float tLook[3], float tEye[3], float tResult[3] );

	void Path( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, float tResult[3] );
  BOOL Move( float tSCoord[3], float tECoord[3], float tSpeed, float tPostTime, BOOL *tCheckArrival );

};
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MINIMAP_FOR_GXD
//-------------------------------------------------------------------------------------------------
#define DEF_MINIMAP_VERSION											0x00000002

class MINIMAPIMG_FOR_GXD
{

public:

	BOOL mCheckValidState;
	IMAGE_FOR_GXD mMapImg;
	float mSclaeRate;
	float mCropSize[2][2];
	char mImgFileName[260];

	MINIMAPIMG_FOR_GXD( );
	virtual ~MINIMAPIMG_FOR_GXD( );

	void Init( );
	bool Free( );
	bool Load( const char *tFileName );
	bool Load( HANDLE hFile, const char *tFilePath, const char *tMainFileName );
	bool Save( const char *tFileName );
	bool Save( HANDLE hFile );
	bool ChangeImg( char *tImgFilName );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_SOUNDDATA_FOR_GXD
//-------------------------------------------------------------------------------------------------
class SOUNDDATA_FOR_GXD
{

private :

	DWORD mFileDataSize;
	BYTE *mFileData;

public :

	BOOL mCheckValidState;
	int mLoadSort;
	int mDuplicateNum;
	IDirectSoundBuffer *mSoundData[10];

	SOUNDDATA_FOR_GXD( void );
    ~SOUNDDATA_FOR_GXD( void );

	void Init( void );
	void Free( void );

	BOOL LoadFromOGG( char *tFileName, int tLoadSort, int tDuplicateNum, BOOL tCheckRemoveFileData );
	BOOL SaveToOGG( char *tFileName );
	void Play(  BOOL tCheckLoop, int tVolume, int tPan );
	void Stop( void );
	void ChangeVolumeAndPan( int tVolume, int tPan );
  bool IsPlaying ( void );

};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_COMPRESS_FUNCTION_FOR_GXD
//-------------------------------------------------------------------------------------------------
typedef DWORD ( * FCompressBound )( DWORD tSourceLength );
typedef int ( * FCompress )( BYTE *tDest, DWORD *tDestLength, BYTE *tSource, DWORD tSourceLength, int tLevel );
typedef int ( * FUncompress )( BYTE *tDest, DWORD *tDestLength, BYTE *tSource, DWORD tSourceLength );
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DEFINE_CLASS_OF_GXD
//-------------------------------------------------------------------------------------------------
//MAX_SAVE_SHADOW_VERTEX_NUM
#define MAX_SAVE_SHADOW_VERTEX_NUM									10000
//MAX_DRAW_SHADOW_TRIS_NUM
#define MAX_DRAW_SHADOW_TRIS_NUM									10000
//MAX_DRAW_SHADOW_VERTEX_NUM
#define MAX_DRAW_SHADOW_VERTEX_NUM									100000
//변수
extern D3DVERTEXELEMENT9 mVertexElementForSKIN2[];
extern D3DVERTEXELEMENT9 mVertexElementForSKIN2SHADOW[];
//클래스
class GXD
{

public :

	inline DWORD F2DW( FLOAT f ) { return *( ( DWORD *) &f ); }

	BOOL mCheckInitState;

	//------//
	//OPTION//
	//------//
	int mTextureOptionValue;
	int mSamplerOptionValue;
	int mNormalMapOptionValue;
	float mLODLengthInfo[2];
	int mFilterOptionValue;
	BOOL mCheckDepthBias;
	BOOL mCheckTwoSideStencilFunction;
	//------//
	//------//
	//------//

	BOOL mCheckFullScreen;
	HINSTANCE mInstanceHandle;
	HWND mWindowHandle;
	int mScreenXSize;
	int mScreenYSize;
	float mFovY;
	float mNearPlane;
	float mFarPlane;
	D3DXFONT_DESC mFontInfo;
	int mMaxParticleNum;

	LARGE_INTEGER mHighResolutionTicks;
	double mTicksForRange;
	double mTicksForTime1;
	double mTicksForTime2;

	IDirect3D9 *mDirect3D;
	D3DCAPS9 mGraphicSupportInfo;
	D3DPRESENT_PARAMETERS mGraphicPresentParameters;
	IDirect3DDevice9 *mGraphicDevice;
	ID3DXSprite *mGraphicSprite;
	ID3DXFont *mGraphicFont;
	std::vector<PARTICLEVERTEX_FOR_GXD> mParticleVertexBuffer;

	IDirect3DTexture9 *mFilterTexture[2];
	IDirect3DSurface9 *mFilterSurface[2];

	int mDRAW_POLYGON_NUM;

	D3DVIEWPORT9 mViewport;
	D3DXMATRIX mViewportMatrix;
	D3DXMATRIX mPerspectiveMatrix;
	D3DXVECTOR3 mCameraEye;
	D3DXVECTOR3 mCameraLook;
	D3DXVECTOR3 mCameraForward;
	D3DXMATRIX mViewMatrix;
	D3DXMATRIX mBillboardMatrixInfoForAll;
	D3DXVECTOR3 mBillboardVertexInfoForAll[2];
	D3DXMATRIX mBillboardMatrixInfoForY;
	D3DXVECTOR3 mBillboardVertexInfoForY[2];
	D3DXMATRIX mWorldMatrix;

	D3DMATERIAL9 mMaterial;

	D3DLIGHT9 mLight;
	D3DXVECTOR3 mLightDirectionForShadow;

	float mFrustumPlane[6][4];

	BOOL mCheckValidStateForSound;
	IDirectSound8 *mDirectSound;
	IDirectSoundBuffer *mSoundPrimaryBuffer;
	char mSoundOutBufferForPCM[4096];

	IDirectInput8 *mDirectInput;
	IDirectInputDevice8 *mKeyboard;
	BYTE mKeyboardImmediateData[256];
	DWORD mKeyboardBufferedDataNum;
	DIDEVICEOBJECTDATA mKeyboardBufferedData[32];

#ifdef USE_SILVERLINING
	CAtmosphere m_Atmosphere;
#endif

	//CRenderStateMgr m_RenderStateMgr;
	//CTextureStageStateMgr m_TextureStateMgr;

	HINSTANCE mCompressLibrary;
	FCompressBound mFCompressBound;
	FCompress mFCompress;
	FUncompress mFUncompress;

	BOOL m_bUseMultiDraw;

	//------//
	//SHADOW//
	//------//
	DRAWSHADOWVERTEX_FOR_GXD mSaveShadowVertexBuffer[MAX_SAVE_SHADOW_VERTEX_NUM];
	int mDrawShadowTrisInfo[MAX_DRAW_SHADOW_TRIS_NUM];
	int mDrawShadowVertexNum;
	IDirect3DVertexBuffer9 *mDrawShadowVertexBuffer;
	//------//
	//------//
	//------//

	//--------------//
	//SHADER_PROGRAM//
	//--------------//
	IDirect3DVertexDeclaration9 *mDECLForSKIN2;
	IDirect3DVertexDeclaration9 *mDECLForSKIN2SHADOW;
	//00
	int mPresentShaderProgramNumber;
	//01-[VERTEX_SHADER-01]
	ID3DXConstantTable *mAmbient1_VS_ConstantTable;
	IDirect3DVertexShader9 *mAmbient1_VS_Shader;
	D3DXHANDLE mAmbient1_VS_WorldViewProjMatrix;
	D3DXHANDLE mAmbient1_VS_LightAmbient;
	//02-[PIXEL_SHADER-01]
	ID3DXConstantTable *mAmbient1_PS_ConstantTable;
	IDirect3DPixelShader9 *mAmbient1_PS_Shader;
	D3DXHANDLE mAmbient1_PS_Texture0;
	D3DXCONSTANT_DESC mAmbient1_PS_Texture0_DESC;
	//03-[VERTEX_SHADER-02]
	ID3DXConstantTable *mAmbient2_VS_ConstantTable;
	IDirect3DVertexShader9 *mAmbient2_VS_Shader;
	D3DXHANDLE mAmbient2_VS_KeyMatrix;
	D3DXHANDLE mAmbient2_VS_WorldViewProjMatrix;
	D3DXHANDLE mAmbient2_VS_LightDirection;
	D3DXHANDLE mAmbient2_VS_LightAmbient;
	D3DXHANDLE mAmbient2_VS_LightDiffuse;
	//04-[PIXEL_SHADER-02]
	ID3DXConstantTable *mAmbient2_PS_ConstantTable;
	IDirect3DPixelShader9 *mAmbient2_PS_Shader;
	D3DXHANDLE mAmbient2_PS_Texture0;
	D3DXCONSTANT_DESC mAmbient2_PS_Texture0_DESC;
	//05-[VERTEX_SHADER-03]
	ID3DXConstantTable *mNormal1_VS_ConstantTable;
	IDirect3DVertexShader9 *mNormal1_VS_Shader;
	D3DXHANDLE mNormal1_VS_KeyMatrix;
	D3DXHANDLE mNormal1_VS_WorldViewProjMatrix;
	D3DXHANDLE mNormal1_VS_LightDirection;
	//06-[PIXEL_SHADER-03]
	ID3DXConstantTable *mNormal1_PS_ConstantTable;
	IDirect3DPixelShader9 *mNormal1_PS_Shader;
	D3DXHANDLE mNormal1_PS_Texture0;
	D3DXCONSTANT_DESC mNormal1_PS_Texture0_DESC;
	D3DXHANDLE mNormal1_PS_Texture1;
	D3DXCONSTANT_DESC mNormal1_PS_Texture1_DESC;
	D3DXHANDLE mNormal1_PS_LightAmbient;
	D3DXHANDLE mNormal1_PS_LightDiffuse;
	//07-[VERTEX_SHADER-04]
	ID3DXConstantTable *mNormal2_VS_ConstantTable;
	IDirect3DVertexShader9 *mNormal2_VS_Shader;
	D3DXHANDLE mNormal2_VS_KeyMatrix;
	D3DXHANDLE mNormal2_VS_WorldViewProjMatrix;
	D3DXHANDLE mNormal2_VS_LightDirection;
	D3DXHANDLE mNormal2_VS_CameraEye;
	//08-[PIXEL_SHADER-04]
	ID3DXConstantTable *mNormal2_PS_ConstantTable;
	IDirect3DPixelShader9 *mNormal2_PS_Shader;
	D3DXHANDLE mNormal2_PS_Texture0;
	D3DXCONSTANT_DESC mNormal2_PS_Texture0_DESC;
	D3DXHANDLE mNormal2_PS_Texture1;
	D3DXCONSTANT_DESC mNormal2_PS_Texture1_DESC;
	D3DXHANDLE mNormal2_PS_Texture2;
	D3DXCONSTANT_DESC mNormal2_PS_Texture2_DESC;
	D3DXHANDLE mNormal2_PS_LightAmbient;
	D3DXHANDLE mNormal2_PS_LightDiffuse;
	//09-[VERTEX_SHADER-05]
	ID3DXConstantTable *mAmbient3_VS_ConstantTable;
	IDirect3DVertexShader9 *mAmbient3_VS_Shader;
	D3DXHANDLE mAmbient3_VS_KeyMatrix;
	D3DXHANDLE mAmbient3_VS_WorldViewProjMatrix;
	//10-[PIXEL_SHADER-05]
	//11-[VERTEX_SHADER-06]
	//12-[PIXEL_SHADER-06]
	ID3DXConstantTable *mFilter1_PS_ConstantTable;
	IDirect3DPixelShader9 *mFilter1_PS_Shader;
	D3DXHANDLE mFilter1_PS_Texture0;
	D3DXCONSTANT_DESC mFilter1_PS_Texture0_DESC;
	D3DXHANDLE mFilter1_PS_Texture0PostSize;
	//13-[VERTEX_SHADER-07]
	//14-[PIXEL_SHADER-07]
	ID3DXConstantTable *mFilter2_PS_ConstantTable;
	IDirect3DPixelShader9 *mFilter2_PS_Shader;
	D3DXHANDLE mFilter2_PS_Texture0;
	D3DXCONSTANT_DESC mFilter2_PS_Texture0_DESC;
	D3DXHANDLE mFilter2_PS_Texture0PostSize;
	//15-[VERTEX_SHADER-08]
	ID3DXConstantTable *mShadow1_VS_ConstantTable;
	IDirect3DVertexShader9 *mShadow1_VS_Shader;
	D3DXHANDLE mShadow1_VS_WorldViewProjMatrix;
	//16-[PIXEL_SHADER-08]
	//--------------//
	//--------------//
	//--------------//

	GXD( void );
    ~GXD( void );

	void InitForSound( void );

	BOOL Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, D3DXFONT_DESC *tFontInfo, int *tRESULT );
	void Free( void );

	//--------------//
	//SHADER_PROGRAM//
	//--------------//
	BOOL MakeShaderProgram01( void );
	BOOL MakeShaderProgram02( void );
	BOOL MakeShaderProgram03( void );
	BOOL MakeShaderProgram04( void );
	BOOL MakeShaderProgram05( void );
	BOOL MakeShaderProgram06( void );
	BOOL MakeShaderProgram07( void );
	BOOL MakeShaderProgram08( void );
	BOOL MakeShaderProgram09( void );
	BOOL MakeShaderProgram10( void );
	BOOL MakeShaderProgram11( void );
	BOOL MakeShaderProgram12( void );
	BOOL MakeShaderProgram13( void );
	BOOL MakeShaderProgram14( void );
	BOOL MakeShaderProgram15( void );
	BOOL MakeShaderProgram16( void );
	//--------------//
	//--------------//
	//--------------//

	float GetRandomNumber( float tMinValue, float tMaxValue );

	float GetTotalElapsedSeconds( void );
	float GetTotalElapsedSecondsFromMMT ( void );

	BOOL SetCameraPosition( float tCameraEyeX, float tCameraEyeY, float tCameraEyeZ, float tCameraLookX, float tCameraLookY, float tCameraLookZ );
	void ChangeCameraForHorizon( float tRA );
	void ChangeCameraForVertical( float tRA );
	void ChangeCameraForForward( float tFD );

	void SetDefaultMaterial( void );

	void SetDefaultLight( void );
	void SetAmbientLight( int tAmbientSort, D3DXCOLOR tAmbientValue );

	void SetDefaultTextureSamplerState( void );

	BOOL ReadyForDrawing( int *tRESULT );

	void BeginForDrawing( void );
	void EndForDrawing( void );

	void BeginForHighShadow( void );
	void EndForHighShadow( void );

	void BeginForLowShadow( void );
	void EndForLowShadow( void );

	void BeginForPOBJECT( void );
	void EndForPOBJECT( void );

	void ProcessForFilter( void );

	void BeginFor2D( void );
	void EndFor2D( void );

	BOOL WorldCoordToScreenCoord( float tCoord[3], int *tX, int *tY );

	int GetStringLength( char *tString );
	void DrawString( char *tString, int tX, int tY, D3DCOLOR tColor, int tOutLineSort );

	void SaveScreenToBMP( char *tFileName );
	void SaveScreenToJPG( char *tFileName );

	void CalculateFrustum( void );
	BOOL CheckPointInFrustum( float tPoint[3] );
	BOOL CheckPointInFrustumWithoutFarPlane( float tPoint[3] );
	BOOL CheckSphereInFrustum( float tCenter[3], float tRadius );
	BOOL CheckSphereInFrustumForWorld( float tCenter[3], float tRadius );
	BOOL CheckBoxInFrustum( float tBoxMin[3], float tBoxMax[3] );

	void TrisProjection( float rkD[3], float akV[3][3], float *rfMin, float *rfMax );
	void BoxProjection( float rkAxis[3], float rkOrigin[3], float akAxis[3][3], float afExtent[3], float *rfMin, float *rfMax );

	BOOL CheckCollisionForRayBox( float tQ[3], float tV[3], float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForSegmentBox( float tQ[3], float tV[3], float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForWorldTrisBox( WORLDTRIS_FOR_GXD *tWorldTris, float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForBoxBox( float tBoxMin01[3], float tBoxMax01[3], float tBoxMin02[3], float tBoxMax02[3] );
	BOOL CheckCollisionForMouseBox( int tX, int tY, float tBoxMin[3], float tBoxMax[3] );
	BOOL CheckCollisionForRayMS( float tQ[3], float tV[3], MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForSegmentMS( float tQ[3], float tV[3], MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForWorldTrisMS( WORLDTRIS_FOR_GXD *tWorldTris, MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForMSMS( MESHSIZE_FOR_GXD *tMeshSize01, MESHSIZE_FOR_GXD *tMeshSize02 );
	BOOL CheckCollisionForMouseMS( int tX, int tY, MESHSIZE_FOR_GXD *tMeshSize );
	BOOL CheckCollisionForSphereSphere( float tCenter01[3], float tRadius01, float tCenter02[3], float tRadius02 );

	BOOL GetCompressSize( DWORD tOriginalSize, BYTE *tOriginal, DWORD *tCompressSize );
	BOOL Compress( DWORD tOriginalSize, BYTE *tOriginal, DWORD tCompressSize, BYTE *tCompress );
	BOOL Decompress( DWORD tCompressSize, BYTE *tCompress, DWORD tOriginalSize, BYTE *tOriginal );

	void UpdateForInputSystem( BOOL tApplicationActive );

	bool CreateTextureForRenderTarget( UINT width, UINT height, D3DFORMAT format );
	void DestroyTextureForRenderTarget( void );

	bool SetRenderTarget( void );
	bool SetDepthStencilSurface( void );

	IDirect3DTexture9 * GetRenderTargetTexturePtr( void );
	IDirect3DSurface9 * GetRenderTargetSurfacePtr( void );

	bool RestoreRenderTarget( void );
	bool RestoreDepthStencilSurface( void );

	VOID OnMultiDraw( ){ m_bUseMultiDraw = TRUE; }
	VOID OffMultiDraw( ){ m_bUseMultiDraw = FALSE; }

private:

	DWORD m_dwEngineStartTime;

	IDirect3DSurface9 *m_pOriginalSurface;
	IDirect3DTexture9 *m_pRenderTargetTexture; 
	IDirect3DSurface9 *m_pRenderTargetSurface;
	IDirect3DSurface9 *m_pOriginalDepthStencilSurface;
	IDirect3DSurface9 *m_pRenderTargetDepthStencilSurface;

};
extern GXD mGXD;


#endif TSGXD_H