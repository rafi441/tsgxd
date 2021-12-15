#ifndef TSMAIN_H
#define TSMAIN_H

class MAIN
{
public:

    int mMainMode;
	int mSubMode;
	DWORD mTicks;
	int mLoginType;
	BOOL bIsClick[150];
	//SOUNDDATA_FOR_GXD mSOUND;
	int mGroupBG;
	int mGroupNum;
	int mGroupIndex[200];
	int mWorldNum;
	char mWorldIP[1000][16];
	int mWorldPort[1000];
	int mWorldState[1000];
	int mMaxPlayerNum[1000];
	int mGagePlayerNum[1000];
	int mPresentPlayerNum[1000];
	int mWorldPageInfo;
	int mWorldMin;
	int mWorldMax;
	int mWorldIndex;
	int mSecondPasswordState;
	int mSecondPasswordType;
	int mSecondPasswordInputIndex;
	int mInputNum[3];
	char aInputText[3][5];
	int mSecondPasswordImage[10];
	int mSecondLoginTryNum;
	int mGiftType;
	int unka1a;
	int unka1b;
	int unka1c;
	int unka1d;
	int unka1e;
	int arra1e[200];
	int unk101[101];
	int bTransferState;
	int mTransferIndex;
	int mSelectState;
	int unk1d;
	int bOpenWebStorageState;
	int uCurrentGiftPage;
	int uMaxGiftPage;
	int mWantGiftIndex;
	int bResetInputSecondPassword;
	int unk6;
	int mSelectBG;
	int mSelectType;
	int mSelectAvtIndex;
	int mCreateWeaponType;
	int mActType;
	int mActSort;
	float mActFrame;
	float mActCoord[3];
	float mActAngle[3];
	int mLoadStep;
	int mLoadImg;

	BOOL Init( void );
	void Free( void );
	void Start( void );
	void Logic( float dTime );
	void Draw( float dTime );
	void LBUTTONDOWN( int mX, int mY );
	void LBUTTONUP( int mX, int mY );
	void RBUTTONDOWN( int mX, int mY );
	void RBUTTONUP( int mX, int mY );  
	void Logic1( float dTime );
	void Draw1( float dTime );  
	void Logic2( float dTime );
	void Draw2( float dTime );
	void LBUTTONDOWN2( int mX, int mY );
	void LBUTTONUP2( int mX, int mY );
	void LoadSelectWorldPageInfo();
	void SaveSelectWorldPageInfo();
	int GetWorldUser( char* ip, int port, int* tMaxPlayerNum, int* tGagePlayerNum );
	int ReturnWorldGroupImage( int a1, int a2 );
	int ReturnXCoord( int a1 );
	int ReturnYCoord( int a1 );
	int ReturnWorldNameImage( int a1 );
	int ReturnWorldNameImageForConnect( int a1 );
	void DisplayWorldUserNumber( int a2, int a3 );
	void Logic3( float dTime );
	void Draw3( float dTime );
	void LBUTTONDOWN3( int mX, int mY );
	void LBUTTONUP3( int mX, int mY );
	//void TW_LOGIN_SEND( char tID[MAX_USER_ID_LENGTH], char tPassword[MAX_USER_PW_LENGTH], int tVersion, int *tWorkResult );
	void Logic4( float dTime );
	void Draw4( float dTime );
	void LBUTTONDOWN4( int mX, int mY );
	void LBUTTONUP4( int mX, int mY );
	void DrawAvatarInfo( int tDrawSort, int tIsCreate, void* tAvatar, int tType, int tSort, float tFrame, float tCoord[3], float tAngle[3] );
	void ProcessForDeleteAvatar();
	void TW_CLIENT_OK_FOR_LOGIN_SEND( int* tResult );
	void TW_CREATE_MOUSE_PASSWORD_SEND( void* a1, int* tResult );
	void TW_LOGIN_MOUSE_PASSWORD_SEND( void* a1, int* tResult );
	void TW_CHANGE_MOUSE_PASSWORD_SEND(void* a1, void* a2, int* a3);
	void TW_CREATE_AVATAR_SEND( int tAvatarPost, void* tAvatarInfo, int* tResult );
	void TW_DELETE_AVATAR_SEND( int tGiftType, int tWantGiftIndex, int a3, int* tResult );
	void TW_CHANGE_AVATAR_NAME_SEND( int a1, char* a2, int a3, int a4, int* tResult );
	void TW_WANT_GIFT_SEND( int a1, int a2, int* tResult );
	void TW_DEMAND_ZONE_SERVER_INFO_1( int tAvatarPost, char* tIP, int* tPort, int* tZoneNumber, int* tResult );
	void TW_FAIL_MOVE_ZONE_1_SEND(int* tResult);
	void TW_CHANGE_MASTER_SEND( int a1, void* a2, int* tResult );
	void TW_GIFT_INFO_SEND( int* tResult );
	void Logic5( float dTime );
	void Draw5( float dTime );
	void Logic6( float dTime );
	void Draw6( float dTime );
	void Logic6ForZone( float dTime );
	void Draw6ForZone( int tDrawSort, float dTime );
	void LBUTTONDOWN6( int mX, int mY );
	void LBUTTONUP6( int mX, int mY );
	void RBUTTONDOWN6( int mX, int mY );
	void RBUTTONUP6( int mX, int mY );
	void ProcessForCamera();

};

extern MAIN mMAIN;


#endif TSMAIN_H