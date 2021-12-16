#ifndef TS_DEFINE_H
#define TS_DEFINE_H

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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <vector>
#include <string>


#define TRACE() printf( "%s:%d\n", __FUNCTION__, __LINE__ )
#define TRACEI( text, value ) printf( "%s:%d, %s,%d\n", __FUNCTION__, __LINE__, text, value )

#define TSAPI extern

#define FALSE 0
#define TRUE 1

#define CFUNC(ret, name) ret (*name)
#define CLS_FUNC(cls, name) .name = &cls##__##name

#define PLATFORM_NAME "TwelveSky"

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
    bool isError;
    BinaryReader() : data(NULL), size(0), pos(0), type(0), refCount(0), autodelete(true), isError(true)
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
        autodelete = oautodelete;
        isError = FALSE;
        refCount = binaryRefCount++;
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

    static BinaryReader& LoadFile(BinaryReader& n, char* tFileName )
    {
        n.isError = TRUE;
        HANDLE hFile = CreateFileA( tFileName, 0x80000000, 1u, 0, 3u, 0x80u, 0 );
        if( hFile == INVALID_HANDLE_VALUE )
            return n;

        n.size = GetFileSize( hFile, 0 );
        if( n.size != INVALID_FILE_SIZE )
        {
            DWORD read;
            n.data = (BYTE*)GlobalAlloc( GMEM_FIXED, n.size );
            if ( n.data )
            {
                n.type = 1;
                if ( ReadFile( hFile, n.data, n.size, &read, 0 ) && read == n.size && CloseHandle( hFile ) )
                {
                    n.isError = FALSE;
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
    BOOL IsAutoDelete;
    ZlibDataPtr( BinaryReader* r, BOOL autoDelete = TRUE )
    {
        IsAutoDelete = autoDelete;
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
            if ( IsError || IsAutoDelete )
            {
                delete[] this->tCompress;
                this->tCompress = NULL;
            }
        }
        if ( this->tOriginal )
        {
            if ( IsError || IsAutoDelete )
            {
                delete[] this->tOriginal;
                this->tOriginal = NULL;
            }
        }
    }
};
class Zlib
{
public:
    static BOOL Decompress( ZlibDataPtr* z );
};

#endif //TS_DEFINE_H