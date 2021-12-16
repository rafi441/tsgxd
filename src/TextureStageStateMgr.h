
#pragma once

#include <Windows.h>
#include <vector>
#include <d3d9.h>
#include <string>
#include <assert.h>

typedef struct {
    DWORD       m_dwState[36];
#ifdef _DEBUG
    std::string m_filename[255];
    int         m_iLine[255];
#endif
} TEXTURESTAGE_STATE_LIST, *PTEXTURESTAGE_STATE_LIST;

class CTextureStageStateMgr
{
public:
    CTextureStageStateMgr(void);
    ~CTextureStageStateMgr(void);

public:
    bool            SetDevicePtr (IDirect3DDevice9* pDevice);
    bool            SetTextureStageState (DWORD dwStage, int iType, DWORD dwValue, char* pFilePath = __FILE__, int iLineNum = __LINE__);
    bool            PushNewState (DWORD dwStage, int iType, DWORD dwFlag, char* pFilePath = __FILE__, int iLineNum = __LINE__);
    bool            PopState (DWORD dwStage);
    bool            RevertState (DWORD dwStage, int iStackPointer);
    void            Dump (DWORD dwStage);

private:
    void            SetInitialState (DWORD dwStage, int iType, DWORD dwValue, char* pFilePath = __FILE__, int iLineNum = __LINE__);

private:
    std::vector<TEXTURESTAGE_STATE_LIST>        m_vState[8];
    IDirect3DDevice9*                           m_pDX9Device;
};
