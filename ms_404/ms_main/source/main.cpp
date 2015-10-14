//=============================================================================
//
// �G���g���[�|�C���g
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"
#include <Windows.h>

#include "AppDelegate.h"

#include <common/DebugUtil.h>

//=============================================================================
// �G���g���[�|�C���g
// Author : Ryo Kobayashi
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    AppDelegate app;
    // ���b�Z�[�W��Ԃ�
    return CApplication::GetInstance()->Run();
}

// EOF