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

#include "system/CSystem.h"

#include "DebugUtil.h"

//=============================================================================
// �G���g���[�|�C���g
//=============================================================================
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
#ifdef _DEBUG
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // ���b�Z�[�W��Ԃ�
    return CSystem::Run(lpCmdLine);
}

// EOF
