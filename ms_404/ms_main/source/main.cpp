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

#include "AppDelegate.h"

#include <common/DebugUtil.h>

//=============================================================================
// エントリーポイント
// Author : Ryo Kobayashi
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    AppDelegate app;
    // メッセージを返す
    return CApplication::GetInstance()->Run();
}

// EOF