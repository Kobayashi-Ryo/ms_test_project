//=============================================================================
//
// エントリーポイント
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"
#include <Windows.h>

#include "system/CSystem.h"

#include "DebugUtil.h"

//=============================================================================
// エントリーポイント
//=============================================================================
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
#ifdef _DEBUG
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // メッセージを返す
    return CSystem::Run(lpCmdLine);
}

// EOF
