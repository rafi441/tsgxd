#ifndef TSGXD_H
#define TSGXD_H

#include "DEFINE.h"

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
	BOOL Load( HANDLE hFile );
};

typedef struct SKINVERTEX_FOR_GXD {
	float mV[3];
	float mN[3];
	float mT[2];
} SKINVERTEX_FOR_GXD;

typedef struct SKINWEIGHT_FOR_GXD {
	int mBoneIndex[4];
	float mBlendValue[4];
} SKINWEIGHT_FOR_GXD;

typedef struct SKINEFFECT_FOR_GXD {
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
} SKINEFFECT_FOR_GXD;

typedef struct SKINSIZE_FOR_GXD {
	float mBoxMin[3];
	float mBoxMax[3];
	float mCenter[3];
	float mRadius;
} SKINSIZE_FOR_GXD;

typedef struct SKINLODVERTEX_FOR_GXD {
	float mV[3];
	float mN[3];
	float mT[2];
	float mBoneIndex[4];
	float mBlendValue[4];
} SKINLODVERTEX_FOR_GXD;

//-------------------------------------------------------------------------------------------------
//DEFINE_STRUCT_OF_BUMPEFFECT_FOR_GXD
//-------------------------------------------------------------------------------------------------
struct BUMPEFFECT_FOR_GXD
{
	DWORD		dwPass;
	float		fAmdPower;
	float		fSpecPower;
	int			iMetrialType;
	BUMPEFFECT_FOR_GXD()
		:dwPass(0L),
		fAmdPower(2.0f),
		fSpecPower(20.0f),
		iMetrialType(0)
	{
	}
};
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
    DWORD       m_dwDyeingColor;

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
	BOOL SetScale( float x, float y, float z );			/** Scaling 정보(mScaleValue) 설정 함수. */
	D3DXVECTOR3 GetScaleValue();						/** Scaling 값을 반환하는 함수. */
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
	BOOL Load( char *tFileName, BOOL tCheckCreateTexture, BOOL tCheckRemoveFileData);
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

typedef struct
{
	float mV[3];
	DWORD mC;
	float mT[2];
} PARTICLEVERTEX_FOR_GXD;
typedef struct
{
	float mV[3];
} DRAWSHADOWVERTEX_FOR_GXD;

typedef DWORD(*FCompressBound)(DWORD tSourceLength);
typedef int (*FCompress)(BYTE* tDest, DWORD* tDestLength, BYTE* tSource, DWORD tSourceLength, int tLevel);
typedef int (*FUncompress)(BYTE* tDest, DWORD* tDestLength, BYTE* tSource, DWORD tSourceLength);

#define MAX_SAVE_SHADOW_VERTEX_NUM									10000
#define MAX_DRAW_SHADOW_TRIS_NUM									10000
#define MAX_DRAW_SHADOW_VERTEX_NUM									100000
extern D3DVERTEXELEMENT9 mVertexElementForSKIN2[];
extern D3DVERTEXELEMENT9 mVertexElementForSKIN2SHADOW[];
class GXD
{
public:

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


	#ifdef USE_RAYLIB
    Camera mMainCamera;
	BOOL Init( void );

	#else
	D3DXFONT_DESC mFontInfo;
	HINSTANCE mInstanceHandle;
	HWND mWindowHandle;
	LARGE_INTEGER mHighResolutionTicks;

	IDirect3D9* mDirect3D;
	D3DCAPS9 mGraphicSupportInfo;
	D3DPRESENT_PARAMETERS mGraphicPresentParameters;
	IDirect3DDevice9* mGraphicDevice;
	ID3DXSprite* mGraphicSprite;
	ID3DXFont* mGraphicFont;
	PARTICLEVERTEX_FOR_GXD* mParticleVertexBuffer;

	IDirect3DTexture9* mFilterTexture[2];
	IDirect3DSurface9* mFilterSurface[2];


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

	

	BOOL Init( BOOL tCheckFullScreen, HINSTANCE tInstanceHandle, HWND tWindowHandle, int tScreenXSize, int tScreenYSize, float tNearPlane, float tFarPlane, D3DXFONT_DESC *tFontInfo, int *tRESULT );
	void Free( void );
	#endif

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


	BOOL mCheckFullScreen;
	int mScreenXSize;
	int mScreenYSize;
	float mFovY;
	float mNearPlane;
	float mFarPlane;
	int mMaxParticleNum;

    double mTicksForRange;
    double mTicksForTime1;
    double mTicksForTime2;

	D3DMATERIAL9 mMaterial;

	D3DLIGHT9 mLight;
	D3DXVECTOR3 mLightDirectionForShadow;

	float mFrustumPlane[6][4];

	BOOL mCheckValidStateForSound;
	IDirectSound8* mDirectSound;
	IDirectSoundBuffer* mSoundPrimaryBuffer;
	char mSoundOutBufferForPCM[4096];

	IDirectInput8* mDirectInput;
	IDirectInputDevice8* mKeyboard;
	BYTE mKeyboardImmediateData[256];
	DWORD mKeyboardBufferedDataNum;
	DIDEVICEOBJECTDATA mKeyboardBufferedData[32];


	HINSTANCE mCompressLibrary;
	FCompressBound mFCompressBound;
	FCompress mFCompress;
	FUncompress mFUncompress;

	int mDRAW_POLYGON_NUM;

	BOOL m_bUseMultiDraw;

	
	void InitForSound( void );

	float GetRandomNumber( float tMinValue, float tMaxValue );
	float GetTotalElapsedSeconds( void );

	#ifndef USE_RAYLIB

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


	BOOL GetCompressSize( DWORD tOriginalSize, BYTE *tOriginal, DWORD *tCompressSize );
	BOOL Compress( DWORD tOriginalSize, BYTE *tOriginal, DWORD tCompressSize, BYTE *tCompress );
	BOOL Decompress( DWORD tCompressSize, BYTE *tCompress, DWORD tOriginalSize, BYTE *tOriginal );
	
private:

	DWORD m_dwEngineStartTime;

	IDirect3DSurface9 *m_pOriginalSurface;
	IDirect3DTexture9 *m_pRenderTargetTexture; 
	IDirect3DSurface9 *m_pRenderTargetSurface;
	IDirect3DSurface9 *m_pOriginalDepthStencilSurface;
	IDirect3DSurface9 *m_pRenderTargetDepthStencilSurface;

	#endif

};
extern GXD mGXD;


#endif TSGXD_H