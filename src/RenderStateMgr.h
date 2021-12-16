
#pragma once

#include <Windows.h>
#include <vector>
#include <d3d9.h>
#include <string>
#include <assert.h>

// 간단하게 이런 매크로로 정의해도 된다.
//#define dSetRenderState(type, flag, device) \
//    if( RenderStateMng.m_dwRenderState[type] != flag ) \
//    { \
//        device->SetRenderState( type,   flag); \
//        RenderStateMng.m_dwRenderState[type] = flag; \
//    }     

typedef struct {
    DWORD       m_dwState[255];
#ifdef _DEBUG
    std::string m_filename[255];
    int         m_iLine[255];
#endif
} RENDER_STATE_LIST, *PRRENDER_STATE_LIST;

class CRenderStateMgr
{
public:
    CRenderStateMgr(void);
    ~CRenderStateMgr(void);

public:
    bool            SetDevicePtr (IDirect3DDevice9* pDevice);
    bool            SetRenderState (int iType, DWORD dwFlag, char* pFilePath = __FILE__, int iLineNum = __LINE__);
    bool            PushNewState (int iType, DWORD dwFlag, char* pFilePath = __FILE__, int iLineNum = __LINE__);
    bool            PopState (void);
    bool            RevertState (int iStackPointer);
    void            Dump (void);

private:
    void            SetInitialState (int iType, DWORD dwFlag, char* pFilePath = __FILE__, int iLineNum = __LINE__);

private:
    static const int                m_iMaxSize = 255;
    std::vector<RENDER_STATE_LIST>  m_vState;
    IDirect3DDevice9*               m_pDX9Device;
};
