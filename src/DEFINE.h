#ifndef TS_DEFINE_H
#define TS_DEFINE_H

#ifdef USE_RAYLIB
#include "raylib.h"
#include "raymath.h"
#pragma comment( lib, "raylib.lib" )
#else
#define _WIN32_WINDOWS												0x0500
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION											0x0800
#include <Windows.h>
#include <time.h>
#include <timeapi.h>
#include <Mmreg.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
#include <dinput.h>

#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <vector>

#define TRACE() printf( "%s:%d\n", __FUNCTION__, __LINE__ )
#define TRACEI( text, value ) printf( "%s:%d, %s,%d\n", __FUNCTION__, __LINE__, text, value )

#define TSAPI extern

#define FALSE 0
#define TRUE 1

#define CFUNC(ret, name) ret (*name)
#define CLS_FUNC(cls, name) .name = &cls##__##name

#define PLATFORM_NAME "TwelveSky"

#ifdef USE_RAYLIB
typedef Vector2 POINT;
typedef Vector3 D3DXVECTOR3;
typedef Matrix D3DXMATRIX;

typedef Texture IDirect3DTexture9;
typedef Image D3DXIMAGE_INFO;


#define CALLBACK
#define MB_OK                       0x00000000L
#define MB_SYSTEMMODAL              0x00001000L

typedef int INT_PTR, * PINT_PTR;
typedef unsigned int UINT_PTR, * PUINT_PTR;

typedef long LONG_PTR, * PLONG_PTR;
typedef unsigned long ULONG_PTR, * PULONG_PTR;

#define far
#define near
#define FAR                 far
#define NEAR                near
#define CONST

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT* PFLOAT;
typedef WORD near* PWORD;
typedef WORD far* LPWORD;
typedef long far* LPLONG;
typedef DWORD near* PDWORD;
typedef DWORD far* LPDWORD;
typedef void far* LPVOID;
typedef void* PVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int* PUINT;


/* Types use for passing & returning polymorphic values */
typedef unsigned int        UINT;
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#ifdef STRICT
typedef void* HANDLE;
#if 0 && (_MSC_VER > 1000)
#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
#else
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif
#else
typedef struct GHANDLE {
    unsigned int Size;
    unsigned int Pos;
    unsigned char* Data;
} GHANDLE;
typedef GHANDLE* HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE* PHANDLE;

DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HINSTANCE);

#define WM_ACTIVATEAPP              0x001C
#define WM_KEYDOWN                  0x0100
#define WM_MOUSEMOVE                0x0200
#define WM_LBUTTONDOWN              0x0201
#define WM_LBUTTONUP                0x0202
#define WM_RBUTTONDOWN              0x0204
#define WM_RBUTTONUP                0x0205
#define WM_MBUTTONUP                0x0207
#define WM_MOUSEWHEEL               0x020A



static LRESULT DefWinProcA( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
    return 0;
}







// D3DCOLOR is equivalent to D3DFMT_A8R8G8B8
#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

// maps unsigned 8 bits/channel to D3DCOLOR
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

#define D3DCOLOR_XYUV(y,u,v)   D3DCOLOR_ARGB(0xff,y,u,v)
#define D3DCOLOR_AYUV(a,y,u,v) D3DCOLOR_ARGB(a,y,u,v)

// maps floating point channels (0.f to 1.f range) to D3DCOLOR
#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))



#endif


/* FILE HANDLE */
#define Fail() return FALSE;
#define FailAndClose() CloseHandle( hFile ); Fail()
#define FailAndFree() Free(); Fail()
#define FailAll() CloseHandle( hFile ); Free(); Fail()

#ifdef USE_RAYLIB
#include "utils.h"
static BOOL CheckFile( HANDLE hFile )
{
    if( hFile == NULL )
    {
        return FALSE;
    }
    if ( hFile->Size < 1 || hFile->Data == NULL )
    {
        hFile = NULL;
        return FALSE;
    }
    return TRUE;
}
static HANDLE LoadFile( char* tFileName )
{
    HANDLE gHandle = (HANDLE)RL_MALLOC( sizeof(HANDLE) + 4 );
    if ( !gHandle )
        return NULL;
    gHandle->Data = LoadFileData( tFileName, &gHandle->Size );
    if( gHandle->Data  == NULL )
    {
        SAFE_FREE( gHandle );
        return NULL;
    }
    TRACELOG( LOG_INFO, "FILEIO: [%s] File size : %ld", tFileName, gFileHandleSize );
    gHandle->Pos = 0;
    return gHandle;
}
static BOOL ReadFile( HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead )
{
    if( !CheckFile( hFile ) )
        return FALSE;
    if( hFile->Pos + nNumberOfBytesToRead > hFile->Size )
        return FALSE;
    if( lpBuffer == NULL )
        return FALSE;
    memcpy( lpBuffer, &hFile->Data[hFile->Pos], nNumberOfBytesToRead );
    hFile->Pos += nNumberOfBytesToRead;
    return TRUE;
}

static BOOL CloseHandle( HANDLE hFile )
{
    if( hFile == NULL )
        return TRUE;
    UnloadFileData( hFile->Data );
    //RL_FREE( hFile );
    hFile = NULL;
    return TRUE;
}

#else

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXMATRIX Matrix;

typedef IDirect3DTexture9 Texture;
typedef D3DXIMAGE_INFO Image;

extern int binaryRefCount;
class BinaryReader
{
public:
    BYTE* data;
    DWORD size;
    DWORD pos;
    int type;
    int refCount;
    bool autodelete;
    BinaryReader() : data(NULL), size(0), pos(0), type(0), refCount(0), autodelete(true)
    {
        refCount = binaryRefCount++;
        TRACEI( "base -> ref", refCount );
    }
    BinaryReader( char* from, BYTE* odata, DWORD osize, int otype = 0, bool oautodelete = true )
    {
        data = odata;
        size = osize;
        pos = 0;
        type = otype;
        refCount = binaryRefCount++;
        autodelete = oautodelete;
        printf( "%s:%d :: %s -> ref:%d\n", __FUNCTION__, __LINE__, from, refCount );
    }

    ~BinaryReader()
    {
        if ( autodelete )
        {
            if ( type && data )
            {
                GlobalFree( data );
            }
            else if ( data )
            {
                delete[] data;
            }
            data = NULL;
        }
        TRACEI( "destroy -> ref", refCount );
    }

    static BinaryReader* LoadFile( char* tFileName )
    {
        HANDLE hFile = CreateFileA( tFileName, 0x80000000, 1u, 0, 3u, 0x80u, 0 );
        if( hFile == INVALID_HANDLE_VALUE )
            return NULL;

        auto n = new BinaryReader();
        n->size = GetFileSize( hFile, 0 );
        if( n->size == INVALID_FILE_SIZE )
        {
            n = NULL;
        }
        else
        {
            DWORD read;
            n->data = (BYTE*)GlobalAlloc( GMEM_FIXED, n->size );
            if ( n->data )
            {
                n->type = 1;
                if ( !ReadFile( hFile, n->data, n->size, &read, 0 ) || read != n->size || !CloseHandle( hFile ) )
                {
                    delete n;
                    n = NULL;
                }
            }
        }
        return n;
    }

    static BinaryReader& Scope( char* from, BYTE* odata, DWORD osize, int otype = 0, bool autodelete = false )
    {
        return *new BinaryReader( from, odata, osize, otype, autodelete );
    }

    byte ReadByte()
    {
        return this->Read<byte>();
    }
    BYTE ReadUByte()
    {
        return this->Read<BYTE>();
    }
    BYTE* ReadBytes( int count )
    {
        assert(this->pos + count <= this->size);

        BYTE* value = &this->data[this->pos];
        this->pos += count;

        return value;
    }
    
    short ReadShort()
    {
        return this->Read<short>();
    }
    USHORT ReadUShort()
    {
        return this->Read<USHORT>();
    }
    WORD ReadWORD()
    {
        return this->Read<WORD>();
    }

    int ReadInt()
    {
        return this->Read<int>();
    }
    float ReadFloat()
    {
        return this->Read<float>();
    }
    DWORD ReadDWORD()
    {
        return this->Read<DWORD>();
    }
    template<typename T> T ReadStruct() { return Read<T>(); }

private:
    template<typename T> T Read()
    {
        int t = sizeof(T);
        assert(this->pos + t <= this->size);

        T value = *(T*)&this->data[this->pos];
        this->pos += t;
        return value;
    }
};

#include <eh.h>
#include <exception>
struct ZlibDataPtr
{
    DWORD tOriginalSize;
    DWORD tCompressSize;
    BYTE* tCompress;
    BYTE* tOriginal;
    BOOL IsError;
    ZlibDataPtr( BinaryReader* r )
    {
        TRACE();
        try {
            this->tOriginalSize = r->ReadInt();
            this->tCompressSize = r->ReadInt();
            this->tCompress = r->ReadBytes( this->tCompressSize );
            this->tOriginal = new BYTE[ this->tOriginalSize ];
            if ( this->tCompress && this->tOriginal )
            {
                IsError = FALSE;
                return;
            }
        }
        catch( std::exception& e )
        {
        }
        IsError = TRUE;
    }
    ~ZlibDataPtr()
    {
        TRACE();
        if ( this->tCompress )
        {
            delete[] this->tCompress;
            this->tCompress = NULL;
        }
        if ( this->tOriginal )
        {
            delete[] this->tOriginal;
            this->tOriginal = NULL;
        }
    }
};
class Zlib
{
public:
    static BOOL Decompress( ZlibDataPtr* z );
};


#define HEAP(type, size) (type*)HeapAlloc( GetProcessHeap(), 0, size )

#endif


#ifdef USE_RAYLIB
#define TRACR() TraceLog( LOG_INFO, "%s:%d", __FUNCTION__, __LINE__ )

#define SAFE_FREE( ptr ) \
if ( ptr ) \
{ \
    RL_FREE( ptr ); \
    ptr = 0; \
} \


#else
#define TRACR() printf( "%s:%d\n", __FUNCTION__, __LINE__ )

#define SAFE_FREE( ptr ) \
if ( ptr ) \
{ \
    GlobalFree( ptr ); \
    ptr = 0; \
} \

#endif


#endif