#include "H01_Platform.h"
MAIN mMAIN;

BOOL MAIN::Init( void )
{
    int i; // [esp+4h] [ebp-4h]

    mMainMode = 0;
    mSubMode = 0;
    mTicks = 0;
    for (i = 0; i < 150; i++)
        bIsClick[i] = 0;
    mLoginType = 1;
    //CSOUNDDATA_FOR_GXD::Init(&This->mSOUND);
    return TRUE;
}

void MAIN::Free( void )
{
    //CSOUNDDATA_FOR_GXD::Free(&v0->mSOUND);
}

void MAIN::Start( void )
{
    int i; // [esp+4h] [ebp-4h]

    //CUTIL::AdjustViewEnvironment1();
    mMainMode = 1;
    mSubMode = 0;
    mTicks = 0;
    for (i = 0; i < 150; i++)
        mMAIN.bIsClick[i] = 0;
    //CSOUNDDATA_FOR_GXD::Free(&This->mSOUND);
}

void MAIN::Logic( float dTime )
{
    switch ( mMainMode )
    {
    case 1:
        Logic1( dTime );
        break;
    case 2:
        Logic2( dTime );
        break;
    case 3:
        Logic3( dTime );
        break;
    case 4:
        Logic4( dTime );
        break;
    case 5:
        Logic5( dTime );
        break;
    case 6:
        Logic6( dTime );
        //CCInnerAuto::Update();
        break;
    }
}

void MAIN::Draw( float dTime )
{
    if ( mMainMode < 1 || mMainMode > 6 ) return;

    mGXD.BeginForDrawing();
    switch ( mMainMode )
    {
    case 1:
        Draw1( dTime );
        break;
    case 2:
        Draw2( dTime );
        break;
    case 3:
        Draw3( dTime );
        break;
    case 4:
        Draw4( dTime );
        break;
    case 5:
        Draw5( dTime );
        break;
    case 6:
        Draw6( dTime );
        break;
    }
    mGXD.EndForDrawing();
}
