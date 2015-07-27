//=============================================================================
//
// DirectXヘッダ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DIRECTX_H__
#define __DIRECTX_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <d3d9.h>
//#include <d3dx9.h>
#include <DxErr.h>
#include "common.h"

//*****************************************************************************
// スタティックライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")    // 描画処理に必要
//#pragma comment (lib, "d3dx9.lib")    // 上の拡張ライブラリ
#pragma comment (lib, "dxguid.lib")    // DirectXのコンポーネント使用に必要
#pragma comment (lib, "winmm.lib")    // これが無いとtime~関数が使えない
#pragma comment (lib, "dxerr.lib")    // エラーを検出してくれる関数などを使えるライブラリ

// DirectXによるデバッグトレース
#if    defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                        \
    {                                                \
        if(FAILED( (x) ))                                \
        {                                            \
        DXTrace(__FILE__, __LINE__, x, "エラー", TRUE);    \
        }                                            \
    }
#endif
#else
#ifndef HR
#define HR(x) x
#endif
#endif

#endif    // __DIRECTX_H__

// EOF